#2019 sept 16
#import various modules 
import glob, string, pickle 
import numpy as np 
import pandas as pd
#use glob to grab the whole report folder and read those report file one by one
#it will create a list which look like :  

rf = glob.glob('/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_**-1.report') 

#define the data dictionary 
dd={ }

#sort the list for consistency 
rf.sort()


#define a report file dictionary : where we will store the several values
#from the report files 
 
rfd={ 'rn' : [], # run number  
      'shms_bcm1_beam_cut_current'   : [], #SHMS 3/4 Trigger Rate  line 133  //added     
      'shms_bcm2_beam_cut_current'  : [], # SSHMS 3/4 Trigger Rate line 124  //added
      'shms_bcm4A_beam_cut_current' : [], # current as measured by bcm 4A
      'shms_bcm4B_beam_cut_current' : [],  # current as measured by bcm 4B 
      'shms_bcm4C_beam_cut_current' : [], # current as measured by 4C
      'shms_unser_beam_cut_current' : [] # current as measured by Unser

     }
for index, run in enumerate(rf):
    with open(rf[index]) as fobj:
        for line in fobj:
            report_data = line.split(':')
            if('Run #' in report_data[0]) : rfd['rn'].append(report_data[1].strip())  # [1] is for 
            if('SHMS BCM1 Beam Cut Current' in report_data[0]) : rfd['shms_bcm1_beam_cut_current'].append(report_data[1][:7].strip())  # [1][:7] is for 
            if('SHMS BCM2 Beam Cut Current' in report_data[0]) : rfd['shms_bcm2_beam_cut_current'].append(report_data[1][:7].strip())
            if('SHMS BCM4A Beam Cut Current' in report_data[0]) : rfd['shms_bcm4A_beam_cut_current'].append(report_data[1][:7].strip())
            if('SHMS BCM4B Beam Cut Current' in report_data[0]) : rfd['shms_bcm4B_beam_cut_current'].append(report_data[1][:7].strip())
            if('SHMS BCM4C Beam Cut Current' in report_data[0]) : rfd['shms_bcm4C_beam_cut_current'].append(report_data[1][:7].strip())
            if('SHMS Unser Beam Cut Current' in report_data[0]) : rfd['shms_unser_beam_cut_current'].append(report_data[1][:7].strip())

#print(rfd)

for var_str, var in rfd.items(): #var_str : keys, var : list of values
    #print(var)
    dd[var_str]=[]
    for index, var  in enumerate(rfd['rn']):
        dd[var_str].append(rfd[var_str][index])

for rfd_var, rfd_list in dd.items():
    print(rfd_list)
    rfd_array = np.asarray(rfd_list, dtype='float')
    dd[rfd_var] = rfd_array

#print(dd)
pickle.dump(dd,open('bcm_unser_cut_current.pkl','wb'))

file = open("shms_bcm.txt","w")
for index in range(len(rfd['rn'])):
    file.write(str(rfd['rn'][index]) + " " +   str(rfd['shms_bcm1_beam_cut_current'][index])  + "   " +  str(rfd['shms_bcm2_beam_cut_current'][index]) + "     " + str(rfd['shms_bcm4A_beam_cut_current'][index])+ " " + str(rfd['shms_bcm4B_beam_cut_current'][index])+ " "+str(rfd['shms_bcm4C_beam_cut_current'][index])+" " +str(rfd['shms_unser_beam_cut_current'][index]) + "\n")


file.close()




