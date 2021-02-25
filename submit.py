#!/usr/bin/env python
import os, re, subprocess
import commands
import math, time
import sys

outputpath = "/vols/cms/snwebb/InvisibleOutput/" #where the output will be stored
cmsswdir = "/home/hep/snwebb/invisible/CMSSW_9_4_10/src" #where the CMSSW release you are using is stored
analysisdir = "/home/hep/snwebb/invisible/analysis" #where the analysis code is stored

InputDirList = [ 

#NLO W 1 JET 

"200127/W1JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8/200127_095105",
"200127/W1JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1/200127_095145",
"200127/W1JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8/200127_095225",
"200127/W1JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1/200127_095304",
"190904/W1JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1/190904_092817",
"190904/W1JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8/190904_092852",
"190904/W1JetsToLNu_LHEWpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8/190904_092927",
"190904/W1JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8/190904_093001",
"190904/W1JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1/190904_093037",

#NLO W 2 JETS

"200127/W2JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8/200127_094944",
"200127/W2JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1/200127_095024",
"200127/W2JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8/200127_095400",
"200127/W2JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1/200127_095441",
"190904/W2JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8/190904_093226",
"190904/W2JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1/190904_093301",
"190904/W2JetsToLNu_LHEWpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8-ext1/190904_093337",
"190904/W2JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1/190904_093412",

#NLO DY 1 JET

"200127/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200127_095520",
"200127/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1/200127_095602",
"190904/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/190904_093447",
"190904/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/190904_093523",
"190904/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/190904_093600",
"190904/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1/190904_093635",
"190904/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/190904_093711",
"190904/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1/190904_093750",

#NLO DY 2 JETS

"200127/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200127_095646",
"200127/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1/200127_095728",
"190904/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/190904_093937",
"190904/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/190904_094013",
"190904/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/190904_094050",
"190904/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1/190904_094124",
"190904/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/190904_094158",
"190904/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1/190904_094232",

#NLO Z 1 JET

"200302/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/200302_155153",
"200302/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/200302_155228",
"200302/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/200302_155302",
"200302/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_250-400-amcnloFXFX-pythia8-ext1/200305_114506",
"200302/Z1JetsToNuNu_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/200302_155413",
"200302/Z1JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200302_155449",

#NLO Z 2 JETS

"200302/Z2JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/200302_155522",
"200302/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/200302_155557",
"200302/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1/200302_155632",
"200302/Z2JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200302_155708",
"200302/Z2JetsToNuNU_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/200310_140222",

#LO W JETS 2017

"200107/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-70To100_madgraphMLM_pythia8/200107_132905",
"200107/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-100To200_madgraphMLM_pythia8/200107_132535",
"200107/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-600To800_madgraphMLM_pythia8/200107_132831",
"200107/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-400To600_madgraphMLM_pythia8/200107_132756",
"200107/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-2500ToInf_madgraphMLM_pythia8/200107_132721",
"200107/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-800To1200_madgraphMLM_pythia8/200107_132941",
"200107/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-200To400_madgraphMLM_pythia8/200107_132646",
"200107/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-1200To2500_madgraphMLM_pythia8/200107_132611",

#LO DY JETS 2017

"200107/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-70to100_madgraphMLM_pythia8/200107_132424",
"200107/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-100to200_madgraphMLM_pythia8/200107_131944",
"200107/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-100to200_madgraphMLM_pythia8-ext1/200107_131908",   
"200107/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-200to400_madgraphMLM_pythia8/200107_132055",
"200107/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-200to400_madgraphMLM_pythia8-ext1/200107_132130",
"200107/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-400to600_madgraphMLM_pythia8/200107_132314",
"200107/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-400to600_madgraphMLM_pythia8-ext1/200107_132239",
"200107/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-600to800_madgraphMLM_pythia8/200107_132349",
"200107/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-800to1200_madgraphMLM_pythia8/200107_132459",
"200107/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-1200to2500_madgraphMLM_pythia8/200107_132021",
"200107/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-2500toInf_madgraphMLM_pythia8/200107_132205",


#LO Z JETS 2017

"200302/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu_HT-100To200-madgraph/200302_154542",
"200302/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu_HT-200To400-madgraph/200302_154854",
"200302/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu_HT-400To600-madgraph/200302_155005",
"200302/ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu_HT-600To800-madgraph/200302_155041",
"200302/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu_HT-800To1200-madgraph/200302_155117",
"200302/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu_HT-1200To2500-madgraph/200302_154818",
"200302/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu_HT-2500ToInf-madgraph/200302_154930",


#LO W JETS 2016

"201123/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-70To100/201123_131824",
"201123/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-100To200/201123_131905",
"201123/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-100To200-ext1/201123_131945",
"201123/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-100To200-ext2/201123_132027",
"201123/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-200To400/201123_132106",
"201123/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-200To400-ext1/201123_132146",
"201123/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-200To400-ext2/201123_132227",
"201123/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-400To600/201123_132308",
"201123/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-400To600-ext1/201123_132351",
"201123/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-600To800/201123_132432",
"201123/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-600To800-ext1/201123_132513",
"201123/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-800To1200/201123_132554",
"201123/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-800To1200-ext1/201123_132636",
"201123/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-1200To2500/201123_132721",
"201123/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-1200To2500-ext1/201123_132807",
"201123/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-2500ToInf/201123_132849",
"201123/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-2500ToInf-ext1/201123_132934",

#LO DY JETS 2016

"201123/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-70To100/201123_131203",
"201123/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-100To200/201123_131239",   
"201123/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-100To200-ext1/201123_131311",   
"201123/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-200To400/201123_131343",
"201123/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-200To400-ext1/201123_131416",
"201123/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-400To600/201123_131449",
"201123/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-400To600-ext1/201123_131522",
"201123/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-600To800/201123_131556",
"201123/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-800To1200/201123_131632",
"201123/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-1200To2500/201123_131709",
"201123/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-2500ToInf/201123_131745",

#LO Z JETS 2016

"201123/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu16_HT-100To200/201123_133009",
"201123/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu16_HT-100To200-ext1/201123_133106",
"201123/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu16_HT-200To400/201123_133205",
"201123/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu16_HT-200To400-ext1/201123_133303",
"201123/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu16_HT-400To600/201123_133403",
"201123/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu16_HT-400To600-ext1/201123_133459",
"201123/ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu16_HT-600To800/201123_133554",
"201123/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu16_HT-800To1200/201123_133650",
"201123/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu16_HT-1200To2500/201123_133745",
"201123/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu16_HT-1200To2500-ext1/201123_133832",
"201123/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu16_HT-2500ToInf/201123_133930",

#LO W JETS 2018

"201123/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-70To100/210106_103217",
"201123/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-100To200/210106_103250",
"201123/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-200To400/210106_103322",
"201123/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-400To600/210106_103355",
"201123/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-600To800/210106_103428",
"201123/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-800To1200/210106_103500",
"201123/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-1200To2500/210106_103533",
"201123/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-2500ToInf/210106_103605",

#LO DY JETS 2018

"201123/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-70to100/210106_104030",
"201123/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-100to200/210106_104102",
"201123/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-200to400/210106_104135",
"201123/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-400to600/210106_104207",
"201123/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-400to600-ext1/210106_104240",
"201123/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-600to800/210106_104312",
"201123/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-800to1200/210106_104345",
"201123/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-1200to2500/210106_104416",
"201123/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-2500toInf/210106_104449",

#LO Z JETS 2018

"201123/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu18_HT-100To200/210106_103640",
"201123/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu18_HT-200To400/210106_103712",
"201123/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu18_HT-400To600/210106_103746",
"201123/ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu18_HT-600To800/210106_103818",
"201123/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu18_HT-800To1200/210106_103852",
"201123/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu18_HT-1200To2500/210106_103924",
"201123/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu18_HT-2500ToInf/210106_103957",

#NLO DY 1 JETS 2018

"210106/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_141030",
"210106/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_141108",
"210106/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_141145",
"210106/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_141222",

#NLO DY 2 JETS 2018

"210106/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_141259",
"210106/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_141336",
"210106/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_141419",
"210106/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_141504",

#NLO Z 1 JET 2018

"210106/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_140452",
"210106/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_140529",
"210106/Z1JetsToNuNu_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_140620",
"210106/Z1JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_140659",

#NLO Z 2 JETS 2018

"210106/Z2JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_140735",
"210106/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_140825",
"210106/Z2JetsToNuNU_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_140940",
"210106/Z2JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_140903",

   ]


OutputDirList=[ outputpath + i.split("/")[2] for i in InputDirList ]


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
      os.system("rm -r " + outdir + "/root")
      os.system("mkdir -p " + outdir + "/tmp")
      os.system("mkdir -p " + outdir + "/root")
      if subprocess.call(["voms-proxy-info",'--exists']) == 1: #check if you have a valid grid proxy
         print "Voms proxy does not exist:"
         os.system("voms-proxy-init -voms cms -valid 96:00")
      else:
         print "Voms proxy exists"
      print

      os.chdir(outdir+"/tmp/")

      #Find out how many directories there are (i.e. 0000/, 0001/, 0002/ etc)
      numdir = commands.getoutput("srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/sawebb/"+  indir  );

      print ( "srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/sawebb/"+ indir )
      print (numdir)

      NumberOfDirs = int(numdir.count('\n')) - 2
      NumberOfJobs = 0
      
      for d in range(0, NumberOfDirs): #Find out how many files there are in the directories - submit one job for each file as default
         numjobs = commands.getoutput("srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/sawebb/"+ indir + "/000"+str(d) );         
         NumberOfJobs += int(numjobs.count('\n')) - 1

      print ("ndirs = " + str(NumberOfDirs))
      print ("njobs = " + str(NumberOfJobs))

      dirnum = 0
      ##### loop for creating and sending jobs #####
      for x in range(1, int(NumberOfJobs)+1):

         if ( x % 1000 == 0 ):
            dirnum+=1
         s_dirnum = str(dirnum);

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

            fout.write("cd " + cmsswdir + "\n")
            fout.write("eval `scramv1 runtime -sh`\n")
            fout.write("cd "+analysisdir+"\n")
            fout.write("./FillHistograms --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/sawebb/"+indir + "/000"+s_dirnum+"/tree_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
            fout.write("echo 'STOP---------------'\n")
            fout.write("echo\n")
            fout.write("echo\n")

         os.system("chmod 755 job_"+str(x)+".sh")

         os.system("qsub -cwd -q hep.q -l h_vmem=4G -l s_vmem=3.5G -l h_rt=1:0:0 -l s_rt=0:50:0 job_"+str(x)+".sh")
         print "job nr " + str(x) + " submitted"


   print
   print "your jobs:"
   os.system("qstat")
   print
   print 'END'
   print


if __name__ == '__main__':
  main()
