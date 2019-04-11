#!/usr/bin/env python
import os, re, subprocess
import commands
import math, time
import sys

########   YOU ONLY NEED TO FILL THE AREA BELOW   #########
########   customization  area #########
NumberOfJobs= 1
# number of jobs to be submitted
interval = 5 # number files to be processed in a single job, take care to split your file so that you run on all files. The last job might be with smaller number of files (the ones that remain).
Date = "190312"

InputDirList = [ 

"ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu_HT-800To1200/190312_143831/0000",
"ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu_HT-600To800-new-pmx/190312_143807/0000",
"ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu_HT-400To600-new-pmx/190312_143741/0000",
"ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu_HT-2500ToInf/190312_143713/0000",
"ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu_HT-200To400/190312_143646/0000",
"ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu_HT-1200To2500-new-pmx/190312_143621/0000",
"ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu_HT-100To200/190312_143554/0000",

"WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8/MC_WJetsToLNu_0J_TuneCP5-amcatnloFXFX/190312_143531/0000",
"WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/MC_WJetsToLNu_2J_TuneCP5-amcatnloFXFX/190312_143507/0000",

"WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-800To1200_TuneCP5/190312_143442/0000",
"WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-70To100_TuneCP5/190312_143418/0000",
"WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-600To800_TuneCP5/190312_143353/0000",
"WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-400To600_TuneCP5/190312_143327/0000",
"WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-2500ToInf_TuneCP5/190312_143303/0000",
"WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-200To400_TuneCP5/190312_143231/0000",
"WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-1200To2500_TuneCP5/190312_143205/0000",
"WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-100To200_TuneCP5/190312_143141/0000",

"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MC_DYJetsToLL_M-50-amcatnloFXFX/190312_143114/0000",
"DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MC_DYJetsToLL_M-50-amcatnloFXFX-ext/190312_143051/0000",

"DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-800to1200/190312_143025/0000",
"DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-70to100/190312_142955/0000",
"DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-600to800/190312_142925/0000",
"DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-400to600/190312_142857/0000",
"DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-400to600-ext/190312_142828/0000",
"DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-2500toInf/190312_142757/0000",
"DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-200to400/190312_142731/0000",
"DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-200to400-ext/190312_142702/0000",
"DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-1200to2500/190312_142636/0000",
"DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-100to200/190312_142610/0000",
"DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-100to200-ext/190312_142547/0000",   
   ]


OutputDirList = [
   "/vols/cms/snwebb/InvisibleOutput/" + i.split("/")[1] for i in InputDirList
 ]

#FileList = "filelist.txt" # list with all the file directories
########   customization end   #########


def main():
   print 
   print 'START'
   print 

   ##### loop for creating and sending jobs #####
   for indir, outdir in zip( InputDirList, OutputDirList ):
      OutputFileNames = outdir + "/root/hist" # base of the output file name, they will be saved in res directory
      path = os.getcwd()
      print
      print 'do not worry about folder creation:'
      os.system("rm -r " + outdir + "/tmp")
      os.system("mkdir -p " + outdir + "/tmp")
      os.system("mkdir -p " + outdir + "/root")
      if subprocess.call(["voms-proxy-info",'--exists']) == 1:
         print "Voms proxy does not exist:"
         os.system("voms-proxy-init -voms cms -valid 96:00")
      else:
         print "Voms proxy exists"
      print

      os.chdir(outdir+"/tmp/")

#      numjobs = subprocess.check_output("srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/sawebb/"+ Date + "/" + indir + " | wc -l");
      numjobs = commands.getoutput("srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/sawebb/"+ Date + "/" + indir );
      intnum =  numjobs.count('\n')

      NumberOfJobs = int(numjobs.count('\n'))

   ##### loop for creating and sending jobs #####
      for x in range(1, int(NumberOfJobs)+1):
      ##### creates directory and file list for job #######
   #      os.system("mkdir "+outdir+"/tmp/"+str(x))

#         os.system("sed '"+str(1+interval*(x-1))+","+str(interval*x)+"!d' ../../"+FileList+" > list.txt ")
#         os.system("sed '"+str(1+interval*(x-1))+","+str(interval*x)+"!d' ../../"+" > list.txt ")

      ##### creates jobs #######
         with open('job_'+str(x)+'.sh', 'w') as fout:                  

            fout.write("#!/bin/sh\n")
            fout.write("echo\n")
            fout.write("echo\n")
            fout.write("ulimit -c 0\n")
            fout.write("echo 'START---------------'\n")
            fout.write("echo 'WORKDIR ' ${PWD}\n")

            fout.write("trap \"echo SIGINT seen\"  SIGINT\n")
            fout.write("trap \"echo SIGUSR1 seen\" SIGUSR1\n")
            fout.write("trap \"echo SIGUSR2 seen\" SIGUSR2\n")
            fout.write("trap \"echo SIGTERM seen\" SIGTERM\n")
            fout.write("trap \"echo SIGXCPU seen\" SIGXCPU\n")

            fout.write("cd /home/hep/snwebb/invisible/CMSSW_9_4_10/src\n")
            fout.write("eval `scramv1 runtime -sh`\n")
            fout.write("cd /home/hep/snwebb/invisible/analysis\n")
            fout.write("./FillHistograms --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/sawebb/"+ Date +"/"+indir + "/tree_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
            fout.write("echo 'STOP---------------'\n")
            fout.write("echo\n")
            fout.write("echo\n")

         os.system("chmod 755 job_"+str(x)+".sh")

      ###### sends bjobs ######
      #os.system("bsub -q "+queue+" -o logs job.sh")
         os.system("qsub -cwd -q hep.q -l h_vmem=4G -l s_vmem=3.5G -l h_rt=1:0:0 -l s_rt=0:50:0 job_"+str(x)+".sh")
         print "job nr " + str(x) + " submitted"

   #      os.chdir("../..")

   print
   print "your jobs:"
   os.system("qstat")
   print
   print 'END'
   print


if __name__ == '__main__':
  main()
