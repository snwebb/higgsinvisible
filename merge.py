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

OutputDirList = [ outputpath + i.split("/")[3] for i in InputDirList ]

for outdir in OutputDirList :
   os.system("hadd -f " + outputpath + "/Merged/" + outdir.split("/")[5] + ".root " + outdir + "/root/*root" )  

print
print 'End merging'
print
