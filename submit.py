#!/usr/bin/env python
import os, re, subprocess
import commands
import math, time
import sys

outputpath = "/vols/cms/snwebb/InvisibleOutput/" #where the output will be stored
cmsswdir = "/home/hep/snwebb/invisible/CMSSW_9_4_10/src" #where the CMSSW release you are using is stored
analysisdir = "/home/hep/snwebb/invisible/analysis" #where the analysis code is stored

InputDirList = [ 

# #NLO W 1 JET 

# "sawebb/200127/W1JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8/200127_095105",
# "sawebb/200127/W1JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1/200127_095145",
# "sawebb/200127/W1JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8/200127_095225",
# "sawebb/200127/W1JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1/200127_095304",
# "sawebb/190904/W1JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1/190904_092817",
# "sawebb/190904/W1JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8/190904_092852",
# "sawebb/190904/W1JetsToLNu_LHEWpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8/190904_092927",
# "sawebb/190904/W1JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8/190904_093001",
# "sawebb/190904/W1JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1/190904_093037",

# #NLO W 2 JETS

# "sawebb/200127/W2JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8/200127_094944",
# "sawebb/200127/W2JetsToLNu_LHEWpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1/200127_095024",
# "sawebb/200127/W2JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8/200127_095400",
# "sawebb/200127/W2JetsToLNu_LHEWpT_100-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1/200127_095441",
# "sawebb/190904/W2JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8/190904_093226",
# "sawebb/190904/W2JetsToLNu_LHEWpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1/190904_093301",
# "sawebb/190904/W2JetsToLNu_LHEWpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8-ext1/190904_093337",
# "sawebb/190904/W2JetsToLNu_LHEWpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_W2JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1/190904_093412",

# #NLO DY 1 JET

# "sawebb/200127/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200127_095520",
# "sawebb/200127/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1/200127_095602",
# "sawebb/190904/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/190904_093447",
# "sawebb/190904/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/190904_093523",
# "sawebb/190904/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/190904_093600",
# "sawebb/190904/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1/190904_093635",
# "sawebb/190904/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/190904_093711",
# "sawebb/190904/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1/190904_093750",

# #NLO DY 2 JETS

# "sawebb/200127/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200127_095646",
# "sawebb/200127/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1/200127_095728",
# "sawebb/190904/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/190904_093937",
# "sawebb/190904/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/190904_094013",
# "sawebb/190904/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/190904_094050",
# "sawebb/190904/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1/190904_094124",
# "sawebb/190904/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/190904_094158",
# "sawebb/190904/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1/190904_094232",

# #NLO Z 1 JET

# "sawebb/200302/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/200302_155153",
# "sawebb/200302/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/200302_155228",
# "sawebb/200302/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/200302_155302",
# "sawebb/200302/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_250-400-amcnloFXFX-pythia8-ext1/200305_114506",
# "sawebb/200302/Z1JetsToNuNu_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/200302_155413",
# "sawebb/200302/Z1JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200302_155449",

# #NLO Z 2 JETS

# "sawebb/200302/Z2JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1/200302_155522",
# "sawebb/200302/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/200302_155557",
# "sawebb/200302/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1/200302_155632",
# "sawebb/200302/Z2JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/200302_155708",
# "sawebb/200302/Z2JetsToNuNU_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/200310_140222",

# #LO W JETS 2017
# #NEW SAMPLES
# "sawebb/CHIP_skim_mc_2017_20210707/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-100To200_RunIISummer20UL17NanoAODv2/210707_153152",
# "sawebb/CHIP_skim_mc_2017_20210707/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-200To400_RunIISummer20UL17NanoAODv2/210707_153338",
# "sawebb/CHIP_skim_mc_2017_20210707/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-400To600_RunIISummer20UL17NanoAODv2/210707_153511",
# "sawebb/CHIP_skim_mc_2017_20210707/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-600To800_RunIISummer20UL17NanoAODv2/210707_153645",
# "sawebb/CHIP_skim_mc_2017_20210707/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-800To1200_RunIISummer20UL17NanoAODv2/210707_154024",
# "sawebb/CHIP_skim_mc_2017_20210707/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-1200To2500_RunIISummer20UL17NanoAODv2/210707_155849",
# "sawebb/CHIP_skim_mc_2017_20210629/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-2500ToInf_lathomas/210629_150510",

# #OLD SAMPLES
# # "sawebb/200107/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-70To100_madgraphMLM_pythia8/200107_132905",
# # "sawebb/200107/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-100To200_madgraphMLM_pythia8/200107_132535",
# # "sawebb/200107/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-600To800_madgraphMLM_pythia8/200107_132831",
# # "sawebb/200107/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-400To600_madgraphMLM_pythia8/200107_132756",
# # "sawebb/200107/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-2500ToInf_madgraphMLM_pythia8/200107_132721",
# # "sawebb/200107/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-800To1200_madgraphMLM_pythia8/200107_132941",
# # "sawebb/200107/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-200To400_madgraphMLM_pythia8/200107_132646",
# # "sawebb/200107/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu_HT-1200To2500_madgraphMLM_pythia8/200107_132611",

# #LO DY JETS 2017
# #NEW SAMPLES
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-70to100_RunIISummer20UL17NanoAODv2/210707_163445",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_RunIISummer20UL17NanoAODv2/210707_163559",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_RunIISummer20UL17NanoAODv2/210707_163752",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_RunIISummer20UL17NanoAODv2/210707_163921",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600to800_RunIISummer20UL17NanoAODv2/210707_164145",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-800to1200_RunIISummer20UL17NanoAODv2/210707_164336",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-1200to2500_RunIISummer20UL17NanoAODv2/210707_164540",
# "sawebb/CHIP_skim_mc_2017_20210707/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-2500toInf_RunIISummer20UL17NanoAODv2/210707_164722",

# #OLD SAMPLES
# # "sawebb/200107/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-70to100_madgraphMLM_pythia8/200107_132424",
# # "sawebb/200107/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-100to200_madgraphMLM_pythia8/200107_131944",
# # "sawebb/200107/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-100to200_madgraphMLM_pythia8-ext1/200107_131908",   
# # "sawebb/200107/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-200to400_madgraphMLM_pythia8/200107_132055",
# # "sawebb/200107/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-200to400_madgraphMLM_pythia8-ext1/200107_132130",
# # "sawebb/200107/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-400to600_madgraphMLM_pythia8/200107_132314",
# # "sawebb/200107/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-400to600_madgraphMLM_pythia8-ext1/200107_132239",
# # "sawebb/200107/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-600to800_madgraphMLM_pythia8/200107_132349",
# # "sawebb/200107/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-800to1200_madgraphMLM_pythia8/200107_132459",
# # "sawebb/200107/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-1200to2500_madgraphMLM_pythia8/200107_132021",
# # "sawebb/200107/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL_M-50_HT-2500toInf_madgraphMLM_pythia8/200107_132205",


# #LO Z JETS 2017
# #NEW SAMPLES
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-100To200_RunIISummer20UL17NanoAODv2/210707_164901/",
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-200To400_RunIISummer20UL17NanoAODv2/210707_165035/",
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-400To600_RunIISummer20UL17NanoAODv2/210707_165218/",
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-600To800_RunIISummer20UL17NanoAODv2/210707_165341/",
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-800To1200_RunIISummer20UL17NanoAODv2/210707_165506/",
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-1200To2500_RunIISummer20UL17NanoAODv2/210707_165643/",
# "sawebb/CHIP_skim_mc_2017_20210707/ZJetsToNuNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-2500ToInf_RunIISummer20UL17NanoAODv2/210707_165818/",

# #OLD SAMPLES
# # "sawebb/200302/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu_HT-100To200-madgraph/200302_154542",
# # "sawebb/200302/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu_HT-200To400-madgraph/200302_154854",
# # "sawebb/200302/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu_HT-400To600-madgraph/200302_155005",
# # "sawebb/200302/ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu_HT-600To800-madgraph/200302_155041",
# # "sawebb/200302/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu_HT-800To1200-madgraph/200302_155117",
# # "sawebb/200302/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu_HT-1200To2500-madgraph/200302_154818",
# # "sawebb/200302/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu_HT-2500ToInf-madgraph/200302_154930",


# #LO W JETS 2016

# "sawebb/201123/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-70To100/201123_131824",
# "sawebb/201123/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-100To200/201123_131905",
# "sawebb/201123/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-100To200-ext1/201123_131945",
# "sawebb/201123/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-100To200-ext2/201123_132027",
# "sawebb/201123/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-200To400/201123_132106",
# "sawebb/201123/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-200To400-ext1/201123_132146",
# "sawebb/201123/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-200To400-ext2/201123_132227",
# "sawebb/201123/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-400To600/201123_132308",
# "sawebb/201123/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-400To600-ext1/201123_132351",
# "sawebb/201123/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-600To800/201123_132432",
# "sawebb/201123/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-600To800-ext1/201123_132513",
# "sawebb/201123/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-800To1200/201123_132554",
# "sawebb/201123/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-800To1200-ext1/201123_132636",
# "sawebb/201123/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-1200To2500/201123_132721",
# "sawebb/201123/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-1200To2500-ext1/201123_132807",
# "sawebb/201123/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-2500ToInf/201123_132849",
# "sawebb/201123/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu16_HT-2500ToInf-ext1/201123_132934",

# # #LO DY JETS 2016

# "sawebb/201123/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-70To100/201123_131203",
# "sawebb/201123/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-100To200/201123_131239",   
# "sawebb/201123/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-100To200-ext1/201123_131311",   
# "sawebb/201123/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-200To400/201123_131343",
# "sawebb/201123/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-200To400-ext1/201123_131416",
# "sawebb/201123/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-400To600/201123_131449",
# "sawebb/201123/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-400To600-ext1/201123_131522",
# "sawebb/201123/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-600To800/201123_131556",
# "sawebb/201123/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-800To1200/201123_131632",
# "sawebb/201123/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-1200To2500/201123_131709",
# "sawebb/201123/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL16_M-50_HT-2500ToInf/201123_131745",

# # #LO Z JETS 2016

# "sawebb/201123/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu16_HT-100To200/201123_133009",
# "sawebb/201123/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu16_HT-100To200-ext1/201123_133106",
# "sawebb/201123/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu16_HT-200To400/201123_133205",
# "sawebb/201123/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu16_HT-200To400-ext1/201123_133303",
# "sawebb/201123/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu16_HT-400To600/201123_133403",
# "sawebb/201123/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu16_HT-400To600-ext1/201123_133459",
# "sawebb/201123/ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu16_HT-600To800/201123_133554",
# "sawebb/201123/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu16_HT-800To1200/201123_133650",
# "sawebb/201123/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu16_HT-1200To2500/201123_133745",
# "sawebb/201123/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu16_HT-1200To2500-ext1/201123_133832",
# "sawebb/201123/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu16_HT-2500ToInf/201123_133930",

# # #LO W JETS 2018

#NEW SAMPLES

# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-70To100_RunIISummer20UL18NanoAODv2/210707_152828",   
# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-100To200_RunIISummer20UL18NanoAODv2/210707_151710",  
# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-200To400_RunIISummer20UL18NanoAODv2/210707_152140",  
# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-400To600_RunIISummer20UL18NanoAODv2/210707_152354",  
# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-600To800_RunIISummer20UL18NanoAODv2/210707_152614",  
# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-800To1200_RunIISummer20UL18NanoAODv2/210707_153035",
# "nckw/CHIP_skim_mc_2018_20210707/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-1200To2500_RunIISummer20UL18NanoAODv2/210707_151934",
# "sawebb/CHIP_skim_mc_2018_20210629/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_HT-2500ToInf_lathomas/210630_072026",

# #OLD SAMPLES
# # "sawebb/201123/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-70To100/210106_103217",
# # "sawebb/201123/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-100To200/210106_103250",
# # "sawebb/201123/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-200To400/210106_103322",
# # "sawebb/201123/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-400To600/210106_103355",
# # "sawebb/201123/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-600To800/210106_103428",
# # "sawebb/201123/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-800To1200/210106_103500",
# # "sawebb/201123/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-1200To2500/210106_103533",
# # "sawebb/201123/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MC_WJetsToLNu18_HT-2500ToInf/210106_103605",
#

# # #LO DY JETS 2018

#NEW SAMPLES

# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-70to100_RunIISummer20UL18NanoAODv2/210707_161835",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_RunIISummer20UL18NanoAODv2/210707_161942",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_RunIISummer20UL18NanoAODv2/210707_162122",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_RunIISummer20UL18NanoAODv2/210707_162234",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600to800_RunIISummer20UL18NanoAODv2/210707_162342",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-800to1200_RunIISummer20UL18NanoAODv2/210707_162447",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-1200to2500_RunIISummer20UL18NanoAODv2/210707_162626",
# "nckw/CHIP_skim_mc_2018_20210707/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-2500toInf_RunIISummer20UL18NanoAODv2/210707_162743",

# # OLD SAMPLES

# # "sawebb/201123/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-70to100/210106_104030",
# # "sawebb/201123/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-100to200/210106_104102",
# # "sawebb/201123/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-200to400/210106_104135",
# # "sawebb/201123/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-400to600/210106_104207",
# # "sawebb/201123/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-400to600-ext1/210106_104240",
# # "sawebb/201123/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-600to800/210106_104312",
# # "sawebb/201123/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-800to1200/210106_104345",
# # "sawebb/201123/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-1200to2500/210106_104416",
# # "sawebb/201123/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/MC_DYJetsToLL18_M-50_HT-2500toInf/210106_104449",
# 
# # #LO Z JETS 2018

#NEW SAMPLES

# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-100To200_RunIISummer20UL18NanoAODv2/210707_162846/",
# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-200To400_RunIISummer20UL18NanoAODv2/210707_162955/",
# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-400To600_RunIISummer20UL18NanoAODv2/210707_163140/",
# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-600To800_RunIISummer20UL18NanoAODv2/210707_163301/",
# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-800To1200_RunIISummer20UL18NanoAODv2/210707_163406/",
# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-1200To2500_RunIISummer20UL18NanoAODv2/210707_163510/",
# "nckw/CHIP_skim_mc_2018_20210707/ZJetsToNuNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ZJetsToNuNu_HT-2500ToInf_RunIISummer20UL18NanoAODv2/210707_163657/",

# # OLD SAMPLES

# # "sawebb/201123/ZJetsToNuNu_HT-100To200_13TeV-madgraph/MC_ZJetsToNuNu18_HT-100To200/210106_103640",
# # "sawebb/201123/ZJetsToNuNu_HT-200To400_13TeV-madgraph/MC_ZJetsToNuNu18_HT-200To400/210106_103712",
# # "sawebb/201123/ZJetsToNuNu_HT-400To600_13TeV-madgraph/MC_ZJetsToNuNu18_HT-400To600/210106_103746",
# # "sawebb/201123/ZJetsToNuNu_HT-600To800_13TeV-madgraph/MC_ZJetsToNuNu18_HT-600To800/210106_103818",
# # "sawebb/201123/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/MC_ZJetsToNuNu18_HT-800To1200/210106_103852",
# # "sawebb/201123/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/MC_ZJetsToNuNu18_HT-1200To2500/210106_103924",
# # "sawebb/201123/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/MC_ZJetsToNuNu18_HT-2500ToInf/210106_103957",

# #NLO DY 1 JETS 2018

# "sawebb/210106/DY1JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_141030",
# "sawebb/210106/DY1JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_141108",
# "sawebb/210106/DY1JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_141145",
# "sawebb/210106/DY1JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY1JetsToLL18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_141222",

# #NLO DY 2 JETS 2018

# "sawebb/210106/DY2JetsToLL_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_141259",
# "sawebb/210106/DY2JetsToLL_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_141336",
# "sawebb/210106/DY2JetsToLL_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_141419",
# "sawebb/210106/DY2JetsToLL_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_DY2JetsToLL18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_141504",

# #NLO Z 1 JET 2018

# "sawebb/210106/Z1JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_140452",
# "sawebb/210106/Z1JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_140529",
# "sawebb/210106/Z1JetsToNuNu_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_140620",
# "sawebb/210106/Z1JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z1JetsToNuNu18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_140659",

# #NLO Z 2 JETS 2018

# "sawebb/210106/Z2JetsToNuNu_M-50_LHEZpT_150-250_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_150-250_amcnloFXFX-pythia8/210106_140735",
# "sawebb/210106/Z2JetsToNuNu_M-50_LHEZpT_250-400_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_250-400_amcnloFXFX-pythia8/210106_140825",
# "sawebb/210106/Z2JetsToNuNU_M-50_LHEZpT_400-inf_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8/210106_140940",
# "sawebb/210106/Z2JetsToNuNu_M-50_LHEZpT_50-150_TuneCP5_13TeV-amcnloFXFX-pythia8/MC_Z2JetsToNuNu18_M-50_LHEZpT_50-150_amcnloFXFX-pythia8/210106_140903",

#    ]


OutputDirList=[ outputpath + i.split("/")[3] for i in InputDirList ]


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
      numdir = commands.getoutput("srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/"+  indir  );

      print ( "srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/"+ indir )
      print (numdir)

      NumberOfDirs = int(numdir.count('\n')) - 2
      NumberOfJobs = 0
      
      for d in range(0, NumberOfDirs): #Find out how many files there are in the directories - submit one job for each file as default
         numjobs = commands.getoutput("srmls srm://gfe02.grid.hep.ph.ic.ac.uk/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/"+ indir + "/000"+str(d) );         
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
            #fout.write("./FillHistograms --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/"+indir + "/000"+s_dirnum+"/tree_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
            fout.write("./FillHistograms --filein root://gfe02.grid.hep.ph.ic.ac.uk:1097//store/user/"+indir + "/000"+s_dirnum+"/tree_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
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
