import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import argparse
import glob
from sklearn.preprocessing import MaxAbsScaler

def standardize(x):
    '''
    Standardization rescales the data to have a mean of 0
    and a standard deviation of 1 (unit variance).
    '''
    mean, std = np.mean(x), np.std(x)
    out = (x-mean)/std
    return out, mean, std

def apply_save_log(x):
    epsilon = 1e-10
    minimum = np.min(x)
    if minimum <= 0:
        x = x-minimum+epsilon
    else:
        minimum = 0
        epsilon = 0
    return np.log10(x), minimum, epsilon

def dictVariables(step):
    dict = {}
    if step == 'calib':
        dict = {
            "r_e_calculated" : 0,
            "eventNumber" : 1,
            "jetCnt" : 2,
            "clusterE" : 3,
            "clusterEta" : 4,
            "cluster_SIGNIFICANCE" : 5,
            "cluster_time" : 6,
            "cluster_SECOND_TIME" : 7,
            "cluster_CENTER_LAMBDA" : 8,
            "cluster_CENTER_MAG" : 9,
            "cluster_ENG_FRAC_EM_INCL" : 10,
            "cluster_FIRST_ENG_DENS" : 11,
            "cluster_LONGITUDINAL" : 12,
            "cluster_LATERAL" : 13,
            "cluster_PTD" : 14,
            "cluster_ISOLATION" : 15,
            "nPrimVtx" : 16,
            "avgMu" : 17
        }
        return dict
    elif step == 'pu':
        dict = {
            "labels" : 0,
            "eventNumber" : 1,
            "jetCnt" : 2,
            "clusterE" : 3,
            "clusterEta" : 4,
            "cluster_time" : 5,
            "cluster_CENTER_LAMBDA" : 6,
            "cluster_CENTER_MAG" : 7,
            "cluster_ENG_FRAC_EM_INCL" : 8,
            "cluster_FIRST_ENG_DENS" : 9,
            "cluster_LATERAL" : 10,
            "cluster_LONGITUDINAL" : 11,
            "cluster_PTD" : 12,
            "cluster_ISOLATION" : 13,
            "cluster_SECOND_TIME" : 14,
            "cluster_SIGNIFICANCE" : 15,
            "nPrimVtx" : 16,
            "avgMu" : 17,
            "clusterPhi" : 18,
            "diffEta" : 19,
            "zT" : 20,
            "zL" : 21,
            "zRel" : 22,
            "cluster_nCells" : 23,
            "jetRawE" : 24,
        }
        return dict
    else:
        print('Problem here in the dictionary')
        return dict

def preprocessing(step, variable_name, arr_before, scales):

    arr_after = arr_before
    if variable_name == "r_e_calculated":
        x = np.log10(arr_before)
        scales[variable_name] = ("Normalize", mean, std)
        return x

    elif variable_name in ['clusterEta', 'cluster_CENTER_MAG', 'nPrimVtx', 'avgMu', 'cluster_LATERAL', 'cluster_LONGITUDINAL', 'cluster_PTD', 'cluster_ISOLATION', 'clusterPhi' ]:
        x, mean, std = standardize(arr_before)
        scales[variable_name] = ("Normalize", mean, std)
        return x

    elif variable_name in ['clusterE', 'cluster_CENTER_LAMBDA', 'cluster_FIRST_ENG_DENS', 'cluster_SECOND_TIME', 'cluster_SIGNIFICANCE' ]:
        x, minimum, epsilon = apply_save_log(arr_before)
        x, mean, std = standardize(x)
        scales[variable_name] = ("SaveLog / Normalize", minimum, epsilon, mean, std)
        return x

    elif variable_name in ["cluster_time"]:
        scale = max(abs(arr_before))
        Maxabsscaler = MaxAbsScaler()
        x = np.squeeze(Maxabsscaler.fit_transform(arr_before[:, None]))
        scales[variable_name] = ("MaxScaler", float(Maxabsscaler.max_abs_))
        return x

    elif variable_name in ["cluster_ENG_FRAC_EM_INCL"]:
        x = arr_before
        xmin = np.min(x)
        xmax = np.max(x)
        xx = (x-xmin)/(xmax-xmin)
        scales[variable_name] = ("Min / Max", xmin, xmax)
        return xx

    elif variable_name in ["diffEta", "zT", "zL", "zRel", "cluster_nCells", "jetRawE"]:
        return arr_after

    else :
        print ("There is a problem :/")
        return arr_before
    # return arr_after

def main():
    parser = argparse.ArgumentParser(description='Derive transformations for CalibPU studies')
    parser.add_argument('--step',   dest='step',   type=str, default='', help='calib or pu')
    args = parser.parse_args()
    columns = []
    if args.step == 'calib':
        columns = ["r_e_calculated", "eventNumber", "jetCnt",
                    "clusterE", "clusterEta", "cluster_SIGNIFICANCE", "cluster_time",
                    "cluster_SECOND_TIME", "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG", "cluster_ENG_FRAC_EM_INCL",
                    "cluster_FIRST_ENG_DENS", "cluster_LONGITUDINAL", "cluster_LATERAL", "cluster_PTD",
                    "cluster_ISOLATION", "nPrimVtx", "avgMu"
                  ]
    elif args.step == 'pu':
        columns = [
                    "labels",
                    "eventNumber", "jetCnt",
                    "clusterE",
                    "clusterEta",
                    "cluster_time",
                    "cluster_CENTER_LAMBDA", "cluster_CENTER_MAG", "cluster_ENG_FRAC_EM_INCL",
                    "cluster_FIRST_ENG_DENS", "cluster_LATERAL", "cluster_LONGITUDINAL",
                    "cluster_PTD", "cluster_ISOLATION", "cluster_SECOND_TIME", "cluster_SIGNIFICANCE",
                    "nPrimVtx",
                    "avgMu",
                    "clusterPhi", "diffEta",
                    "zT",
                    "zL", "zRel",
                    "cluster_nCells", "jetRawE",
                  ]
    else:
        print('Choose calib or pu')
        return

    files = glob.glob('/data/jmsardain/CalibPU/datasets/'+args.step+'/train_*_0.npy')
    # files += glob.glob('/data/jmsardain/CalibPU/datasets/'+args.step+'/val_*_0.npy')

    dict_variables = dictVariables(args.step)
    scales = {}

    train_dataset = []
    
    with PdfPages("plots/"+args.step+"/all_figures.pdf") as pdf:

        for icol in range(len(columns)):
            variable_name = columns[icol]
            print(f'Doing {variable_name}')
            arr_before = []
            for f in files:
                arr = np.load(f, mmap_mode='r')
                arr_before.append(arr[:, dict_variables[variable_name]])

            arr_before = np.concatenate(arr_before)

            arr_after = preprocessing(args.step, variable_name, arr_before, scales)


            # -- Define 100 bins between min and max
            bins_before = np.linspace(np.min(arr_before), np.max(arr_before), 101, endpoint=True)
            bins_after  = np.linspace(np.min(arr_after),  np.max(arr_after), 101, endpoint=True)

            bins_before = np.linspace(np.min(arr_before), np.max(arr_before), 101, endpoint=True)
            bins_after  = np.linspace(np.min(arr_after),  np.max(arr_after), 101, endpoint=True)

            fig, ax = plt.subplots(1, 2)
            # -- Up: distribution before transformation
            ax[0].hist(arr_before, bins=bins_before, color='b', alpha=0.75)
            ax[0].set_yscale('log')
            ax[0].set_xlabel(variable_name)
            ax[0].set_ylabel('Count')

            # # -- Down: distribution after transformation
            ax[1].hist(arr_after, bins=bins_after, color='r', alpha=0.75)
            ax[1].set_yscale('log')
            ax[1].set_xlabel(variable_name)
            ax[1].set_ylabel('Count')

            # Show the graph
            fig.tight_layout()
            pdf.savefig()
            plt.close()

            # plt.savefig('plots/'+args.step+'/'+variable_name+'.png')
            # plt.clf()

    with open("plots/"+args.step+"/scales.txt", "w") as f:
        f.write(str(scales))


    return

if __name__ == "__main__":
    main()
    pass
