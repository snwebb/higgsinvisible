#!/usr/bin/env python
import os, re, subprocess
import commands
import math, time
import sys
from submit import InputDirList

print 
print 'START'
print 
########   YOU ONLY NEED TO FILL THE AREA BELOW   #########
########   customization  area #########
NumberOfJobs= 30
# number of jobs to be submitted
interval = 1 # number files to be processed in a single job, take care to split your file so that you run on all files. The last job might be with smaller number of files (the ones that remain).
Date = "190708"

#count = 0;
# OutputDirList=[]
# for i in InputDirList:
#    OutputDirList.append( "/vols/cms/snwebb/InvisibleOutput/" + i.split("/")[1] + str(count) )
#    count+=1;

OutputDirList = [
   "/vols/cms/snwebb/InvisibleOutput/" + i.split("/")[2] for i in InputDirList
 ]

#FileList = "filelist.txt" # list with all the file directories
########   customization end   #########


##### loop for creating and sending jobs #####
for outdir in OutputDirList :
   os.system("hadd -f /vols/cms/snwebb/InvisibleOutput/Merged/" + outdir.split("/")[5] + ".root " + outdir + "/root/*root" )  




print
print 'End merging'
print
