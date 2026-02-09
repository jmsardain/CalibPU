
## train 
python training.py --train --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb42026

## test 
python training.py --test --ckpt /data/jmsardain/CalibPU/trainings/pu/ckpts/Jan272026/DNN_e050_losstrain13789.956_lossval3000.239.pt --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb32026/ 

## merge ROOT files
python training.py --merge --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Feb42026/