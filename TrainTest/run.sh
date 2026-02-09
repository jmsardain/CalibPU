
## train 
python training.py --train --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb52026

## test 
python training.py --test --ckpt /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb52026/DNN_e100_losstrain6868.216_lossval1497.316.pt --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb52026/ 

## merge ROOT files
python training.py --merge --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb52026/