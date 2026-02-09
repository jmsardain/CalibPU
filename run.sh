cd /home/jmsardain/CalibPU/MakeData/
python makeData_JetTree.py --step test 

cd /home/jmsardain/CalibPU/TrainTest/
python training.py --test --ckpt /data/jmsardain/CalibPU/trainings/pu/ckpts/Jan272026/DNN_e050_losstrain13789.956_lossval3000.239.pt --outdir /data/jmsardain/CalibPU/trainings/pu/ckpts/Jan302026/
