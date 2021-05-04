#!/usr/bin/env python
import os, re, subprocess
import commands
import math, time
import sys
from submit import InputDirList
from submit import outputpath

print 
print 'START'
print 

OutputDirList = [ outputpath + i.split("/")[2] for i in InputDirList ]
try:
    os.mkdir(outputpath + "/Merged")
except OSError:
    pass

for outdir in OutputDirList :
   os.system("hadd -f " + outputpath + "/Merged/" + outdir.split("/")[-1] + ".root " + outdir + "/root/*root" )

print
print 'End merging'
print
