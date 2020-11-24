#include "HiggsPlotting.h"

HiggsPlotting::HiggsPlotting( CmdLine * cmd ){

  _cmd = cmd;
  _origDir = gDirectory ;
  TH1::SetDefaultSumw2();  
  TH1::AddDirectory(kFALSE);
}


HiggsPlotting::~HiggsPlotting() {

  gDirectory = _origDir ;

  for(auto &it1 : _cloned_hists) {
    for(auto &it2 : it1.second) {
      if (it2.second)  it2.second->Delete();
    }
  }
  for(auto &it1 : _cloned_hists2D) {
    for(auto &it2 : it1.second) {
      if (it2.second)  it2.second->Delete();
    }
  }
  
}

void HiggsPlotting::LoadAllHistograms(){

  //map of short name and filename
  std::map<TString,TString> filenames;

  //  filenames[ "ZLL-NLO-orig" ]     = "MC_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8-Skimmed.root";
  // filenames[ "ZLL-NLO-orig" ]     = "MC_DYJetsToLL_M-50-amcatnloFXFX.root";
  // filenames[ "ZLL-NLO-ext" ] = "MC_DYJetsToLL_M-50-amcatnloFXFX-ext.root";

  //LEADING ORDER
  //OLD
  // filenames[ "ZLL-LO-70-100" ] = "MC_DYJetsToLL_M-50_HT-70to100.root";
  // filenames[ "ZLL-LO-100-200" ] = "MC_DYJetsToLL_M-50_HT-100to200.root";
  // filenames[ "ZLL-LO-100-200-ext" ] = "MC_DYJetsToLL_M-50_HT-100to200-ext.root";
  // filenames[ "ZLL-LO-200-400" ] = "MC_DYJetsToLL_M-50_HT-200to400.root";
  // filenames[ "ZLL-LO-200-400-ext" ] = "MC_DYJetsToLL_M-50_HT-200to400-ext.root";
  // filenames[ "ZLL-LO-400-600" ] = "MC_DYJetsToLL_M-50_HT-400to600.root";
  // filenames[ "ZLL-LO-400-600-ext" ] = "MC_DYJetsToLL_M-50_HT-400to600-ext.root";
  // filenames[ "ZLL-LO-600-800" ] = "MC_DYJetsToLL_M-50_HT-600to800.root";
  // filenames[ "ZLL-LO-800-1200" ] = "MC_DYJetsToLL_M-50_HT-800to1200.root";
  // filenames[ "ZLL-LO-1200-2500" ] = "MC_DYJetsToLL_M-50_HT-1200to2500.root";
  // filenames[ "ZLL-LO-2500-Inf" ] = "MC_DYJetsToLL_M-50_HT-2500toInf.root";

  // filenames[ "WLN-LO-70-100" ] = "MC_WJetsToLNu_HT-70To100_TuneCP5.root";
  // filenames[ "WLN-LO-100-200" ] = "MC_WJetsToLNu_HT-100To200_TuneCP5.root";
  // filenames[ "WLN-LO-200-400" ] = "MC_WJetsToLNu_HT-200To400_TuneCP5.root";
  // filenames[ "WLN-LO-400-600" ] = "MC_WJetsToLNu_HT-400To600_TuneCP5.root";
  // filenames[ "WLN-LO-600-800" ] = "MC_WJetsToLNu_HT-600To800_TuneCP5.root";
  // filenames[ "WLN-LO-800-1200" ] = "MC_WJetsToLNu_HT-800To1200_TuneCP5.root";
  // filenames[ "WLN-LO-1200-2500" ] = "MC_WJetsToLNu_HT-1200To2500_TuneCP5.root";
  // filenames[ "WLN-LO-2500-Inf" ] = "MC_WJetsToLNu_HT-2500ToInf_TuneCP5.root";

  //LEADING ORDER
  //ANDREAS

  filenames[ "ZLL-LO-70-100" ] = "MC_DYJetsToLL_M-50_HT-70to100_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-100-200" ] = "MC_DYJetsToLL_M-50_HT-100to200_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-100-200-ext" ] = "MC_DYJetsToLL_M-50_HT-100to200_madgraphMLM_pythia8-ext1.root";
  filenames[ "ZLL-LO-200-400" ] = "MC_DYJetsToLL_M-50_HT-200to400_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-200-400-ext" ] = "MC_DYJetsToLL_M-50_HT-200to400_madgraphMLM_pythia8-ext1.root";
  filenames[ "ZLL-LO-400-600" ] = "MC_DYJetsToLL_M-50_HT-400to600_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-400-600-ext" ] = "MC_DYJetsToLL_M-50_HT-400to600_madgraphMLM_pythia8-ext1.root";
  filenames[ "ZLL-LO-600-800" ] = "MC_DYJetsToLL_M-50_HT-600to800_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-800-1200" ] = "MC_DYJetsToLL_M-50_HT-800to1200_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-1200-2500" ] = "MC_DYJetsToLL_M-50_HT-1200to2500_madgraphMLM_pythia8.root";
  filenames[ "ZLL-LO-2500-Inf" ] = "MC_DYJetsToLL_M-50_HT-2500toInf_madgraphMLM_pythia8.root";

  filenames[ "WLN-LO-70-100" ] = "MC_WJetsToLNu_HT-70To100_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-100-200" ] = "MC_WJetsToLNu_HT-100To200_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-200-400" ] = "MC_WJetsToLNu_HT-200To400_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-400-600" ] = "MC_WJetsToLNu_HT-400To600_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-600-800" ] = "MC_WJetsToLNu_HT-600To800_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-800-1200" ] = "MC_WJetsToLNu_HT-800To1200_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-1200-2500" ] = "MC_WJetsToLNu_HT-1200To2500_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-2500-Inf" ] = "MC_WJetsToLNu_HT-2500ToInf_madgraphMLM_pythia8.root";



  filenames[ "ZNN-LO-100-200" ] = "MC_ZJetsToNuNu_HT-100To200-madgraph.root";
  filenames[ "ZNN-LO-200-400" ] = "MC_ZJetsToNuNu_HT-200To400-madgraph.root";
  filenames[ "ZNN-LO-400-600" ] = "MC_ZJetsToNuNu_HT-400To600-madgraph.root";
  filenames[ "ZNN-LO-600-800" ] = "MC_ZJetsToNuNu_HT-600To800-madgraph.root";
  filenames[ "ZNN-LO-800-1200" ] = "MC_ZJetsToNuNu_HT-800To1200-madgraph.root";
  filenames[ "ZNN-LO-1200-2500" ] = "MC_ZJetsToNuNu_HT-1200To2500-madgraph.root";
  filenames[ "ZNN-LO-2500-Inf" ] = "MC_ZJetsToNuNu_HT-2500ToInf-madgraph.root";

  //2016 files
  filenames[ "ZLL16-LO-70-100" ] = "MC_DYJetsToLL16_M-50_HT-70To100.root";
  filenames[ "ZLL16-LO-100-200" ] = "MC_DYJetsToLL16_M-50_HT-100To200.root";
  filenames[ "ZLL16-LO-100-200-ext1" ] = "MC_DYJetsToLL16_M-50_HT-100To200-ext1.root";
  filenames[ "ZLL16-LO-200-400" ] = "MC_DYJetsToLL16_M-50_HT-200To400.root";
  filenames[ "ZLL16-LO-200-400-ext1" ] = "MC_DYJetsToLL16_M-50_HT-200To400-ext1.root";
  filenames[ "ZLL16-LO-400-600" ] = "MC_DYJetsToLL16_M-50_HT-400To600.root";
  filenames[ "ZLL16-LO-400-600-ext1" ] = "MC_DYJetsToLL16_M-50_HT-400To600-ext1.root";
  filenames[ "ZLL16-LO-600-800" ] = "MC_DYJetsToLL16_M-50_HT-600To800.root";
  filenames[ "ZLL16-LO-800-1200" ] = "MC_DYJetsToLL16_M-50_HT-800To1200.root";
  filenames[ "ZLL16-LO-1200-2500" ] = "MC_DYJetsToLL16_M-50_HT-1200To2500.root";
  filenames[ "ZLL16-LO-2500-Inf" ] = "MC_DYJetsToLL16_M-50_HT-2500ToInf.root";

  filenames[ "WLN16-LO-70-100" ] = "MC_WJetsToLNu16_HT-70To100.root";
  filenames[ "WLN16-LO-100-200" ] = "MC_WJetsToLNu16_HT-100To200.root";
  filenames[ "WLN16-LO-100-200-ext1" ] = "MC_WJetsToLNu16_HT-100To200-ext1.root";
  filenames[ "WLN16-LO-100-200-ext2" ] = "MC_WJetsToLNu16_HT-100To200-ext2.root";
  filenames[ "WLN16-LO-200-400" ] = "MC_WJetsToLNu16_HT-200To400.root";
  filenames[ "WLN16-LO-200-400-ext1" ] = "MC_WJetsToLNu16_HT-200To400-ext1.root";
  filenames[ "WLN16-LO-200-400-ext2" ] = "MC_WJetsToLNu16_HT-200To400-ext2.root";
  filenames[ "WLN16-LO-400-600" ] = "MC_WJetsToLNu16_HT-400To600.root";
  filenames[ "WLN16-LO-400-600-ext1" ] = "MC_WJetsToLNu16_HT-400To600-ext1.root";
  filenames[ "WLN16-LO-600-800" ] = "MC_WJetsToLNu16_HT-600To800.root";
  filenames[ "WLN16-LO-600-800-ext1" ] = "MC_WJetsToLNu16_HT-600To800-ext1.root";
  filenames[ "WLN16-LO-800-1200" ] = "MC_WJetsToLNu16_HT-800To1200.root";
  filenames[ "WLN16-LO-800-1200-ext1" ] = "MC_WJetsToLNu16_HT-800To1200-ext1.root";
  filenames[ "WLN16-LO-1200-2500" ] = "MC_WJetsToLNu16_HT-1200To2500.root";
  filenames[ "WLN16-LO-1200-2500-ext1" ] = "MC_WJetsToLNu16_HT-1200To2500-ext1.root";
  filenames[ "WLN16-LO-2500-Inf" ] = "MC_WJetsToLNu16_HT-2500ToInf.root";
  filenames[ "WLN16-LO-2500-Inf-ext1" ] = "MC_WJetsToLNu16_HT-2500ToInf-ext1.root";

  filenames[ "ZNN16-LO-100-200" ] = "MC_ZJetsToNuNu16_HT-100To200.root";
  filenames[ "ZNN16-LO-100-200-ext1" ] = "MC_ZJetsToNuNu16_HT-100To200-ext1.root";
  filenames[ "ZNN16-LO-200-400" ] = "MC_ZJetsToNuNu16_HT-200To400.root";
  filenames[ "ZNN16-LO-200-400-ext1" ] = "MC_ZJetsToNuNu16_HT-200To400-ext1.root";
  filenames[ "ZNN16-LO-400-600" ] = "MC_ZJetsToNuNu16_HT-400To600.root";
  filenames[ "ZNN16-LO-400-600-ext1" ] = "MC_ZJetsToNuNu16_HT-400To600-ext1.root";
  filenames[ "ZNN16-LO-600-800" ] = "MC_ZJetsToNuNu16_HT-600To800.root";
  filenames[ "ZNN16-LO-800-1200" ] = "MC_ZJetsToNuNu16_HT-800To1200.root";
  filenames[ "ZNN16-LO-1200-2500" ] = "MC_ZJetsToNuNu16_HT-1200To2500.root";
  filenames[ "ZNN16-LO-1200-2500-ext1" ] = "MC_ZJetsToNuNu16_HT-1200To2500-ext1.root";
  filenames[ "ZNN16-LO-2500-Inf" ] = "MC_ZJetsToNuNu16_HT-2500ToInf.root";


  //NEXT TO LEADING ORDER
  filenames[ "ZLL-NLO-Pt-100-250-ext1" ]     = "MC_DYJetsToLL_Pt-100To250-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-Pt-100-250-ext2" ]     = "MC_DYJetsToLL_Pt-100To250-amcatnloFXFX-pythia8-ext2.root";
  filenames[ "ZLL-NLO-Pt-100-250-ext5" ]     = "MC_DYJetsToLL_Pt-100To250-amcatnloFXFX-pythia8-ext5.root";
  filenames[ "ZLL-NLO-Pt-250-400" ]     = "MC_DYJetsToLL_Pt-250To400-amcatnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-Pt-250-400-ext1" ]     = "MC_DYJetsToLL_Pt-250To400-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-Pt-250-400-ext2" ]     = "MC_DYJetsToLL_Pt-250To400-amcatnloFXFX-pythia8-ext2.root";
  filenames[ "ZLL-NLO-Pt-250-400-ext5" ]     = "MC_DYJetsToLL_Pt-250To400-amcatnloFXFX-pythia8-ext5.root";
  filenames[ "ZLL-NLO-Pt-400-650" ]     = "MC_DYJetsToLL_Pt-400To650-amcatnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-Pt-400-650-ext1" ]     = "MC_DYJetsToLL_Pt-400To650-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-Pt-400-650-ext2" ]     = "MC_DYJetsToLL_Pt-400To650-amcatnloFXFX-pythia8-ext2.root";
  filenames[ "ZLL-NLO-Pt-650-Inf" ]     = "MC_DYJetsToLL_Pt-650ToInf-amcatnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-Pt-650-Inf-ext1" ]     = "MC_DYJetsToLL_Pt-650ToInf-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-Pt-650-Inf-ext2" ]     = "MC_DYJetsToLL_Pt-650ToInf-amcatnloFXFX-pythia8-ext2.root";
  
  // filenames[ "WLN-NLO-0J" ] = "MC_WJetsToLNu_0J_TuneCP5-amcatnloFXFX.root";
  // filenames[ "WLN-NLO-1J" ] = "MC_WJetsToLNu_1J_TuneCP5-amcatnloFXFX-Skimmed.root";
  // filenames[ "WLN-NLO-2J" ] = "MC_WJetsToLNu_2J_TuneCP5-amcatnloFXFX.root";
  
  filenames[ "WLN-NLO-Pt-100-250" ] = "MC_WJetsToLNu_Pt-100To250-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-250-400" ] = "MC_WJetsToLNu_Pt-250To400-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-400-600" ] = "MC_WJetsToLNu_Pt-400To600-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-600-Inf" ] = "MC_WJetsToLNu_Pt-600ToInf-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-100-250-ext1" ] = "MC_WJetsToLNu_Pt-100To250-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-Pt-250-400-ext1" ] = "MC_WJetsToLNu_Pt-250To400-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-Pt-400-600-ext1" ] = "MC_WJetsToLNu_Pt-400To600-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-Pt-600-Inf-ext1" ] = "MC_WJetsToLNu_Pt-600ToInf-amcatnloFXFX-pythia8-ext1.root";


  // // filenames[ "WLN-LO-Pt-100-200" ] = "MC_WJetsToLNu_Pt-100To200-madgraphMLM-pythia8.root";
  // // filenames[ "WLN-LO-Pt-200-Inf" ] = "MC_WJetsToLNu_Pt-200ToInf-madgraphMLM-pythia8.root";

  //NEW ANDREAS VERSION


  filenames[ "ZLL-NLO-LHEPt-1J-50-150" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-50-150-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-50-150" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-50-150-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-1J-150-250" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-150-250-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-150-250" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-150-250-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-1J-250-400" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-250-400-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-250-400" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-250-400-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-1J-400-Inf" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-400-Inf-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-400-Inf" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-400-Inf-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1.root";

  filenames[ "WLN-NLO-LHEPt-1J-50-150" ]     = "MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-50-150-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-50-150" ]     = "MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-2J-50-150-ext1" ]     ="MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1.root";

  filenames[ "WLN-NLO-LHEPt-1J-100-150" ]     = "MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-100-150-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-100-150" ]     = "MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-2J-100-150-ext1" ]     ="MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-1J-150-250" ]     = "MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-150-250-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-150-250" ]     = "MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-2J-150-250-ext1" ]     ="MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-1J-250-400" ]     = "MC_W1JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8.root";
  //  filenames[ "WLN-NLO-LHEPt-1J-250-400-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-250-400" ]     = "MC_W2JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8-ext1.root";
  //  filenames[ "WLN-NLO-LHEPt-2J-250-400-ext1" ]     = "MC_W2JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-1J-400-Inf" ]     = "MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-400-Inf-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-400-Inf" ]     = "MC_W2JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1.root";
  //  filenames[ "WLN-NLO-LHEPt-2J-400-Inf-ext1" ]     = "MC_W2JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1.root";



  filenames[ "ZNN-NLO-LHEPt-1J-50-150" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-2J-50-150" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";

  filenames[ "ZNN-NLO-LHEPt-1J-150-250" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-1J-150-250-ext1" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZNN-NLO-LHEPt-2J-150-250" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";

  filenames[ "ZNN-NLO-LHEPt-1J-250-400" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-1J-250-400-ext1" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_250-400-amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZNN-NLO-LHEPt-2J-250-400" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-2J-250-400-ext1" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1.root";  

  filenames[ "ZNN-NLO-LHEPt-1J-400-Inf" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-2J-400-Inf" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";







  //  std::vector<std::string> plots = {"gen_boson_pt", "gen_boson_eta", "gen_mjj", "gen_detajj", "gen_dphijj", "gen_mindphi_jetmet", "LHE_HT", "gen_events","n_jets", "gen_jetpt0"};

  //  std::vector<std::string> plots = {"gen_boson_pt", "gen_events", "gen_jetpt0","LHE_HT", "gen_boson_mass","gen_mjj"};
  std::vector<std::string> plots = {"gen_boson_pt", "gen_events", "gen_jetpt0","LHE_HT", "gen_boson_mass","gen_mjj", "gen_lepton_eta0", "gen_lepton_eta1", "gen_lepton_pt0", "gen_lepton_pt1", "gen_dphijj"};
  //std::vector<std::string> plots2D = {"gen_boson_pt_gen_mjj","gen_boson_pt_gen_jetpt0","gen_boson_pt_gen_mjj_NoHeavyQuark","gen_boson_pt_gen_mjj_HeavyQuark"};
  std::vector<std::string> plots2D = {"gen_boson_pt_gen_mjj","gen_boson_pt_gen_jetpt0","gen_boson_pt_gen_jet_multiplicity","gen_boson_pt_gen_mjj_NoHeavyQuark","gen_boson_pt_gen_mjj_HeavyQuark"};

  //  std::vector<std::string> histoSets = { "Default", "All", "Default-Mjj-200-500" };
  std::vector<std::string> histoSets = { "Default", "All" , "Default_VTR", "MJJ-200-500",  "MJJ-500-1000",  "MJJ-1000-1500", "MJJ-1500-5000", "non-VBF"};
  //  std::vector<std::string> histoSets = { "Default","All","ZNN-No_gen_mjj", "ZNN-2Jets", "ZNN-2JetsEta", "ZNN-2JetsEtaDeltaEta", "ZNN-2JetsEtaDeltaEtaDeltaPhi"};

  //then load into clonemap with short name and list of hists

  TH1D * loadHist = 0;
  TH2D * loadHist2D = 0;
  TFile * loadFile = 0;

  TString filepath = "/vols/cms/snwebb/InvisibleOutput/Merged/";

  for (auto const& filename : filenames){
    
    loadFile = new TFile ( filepath + filename.second, "READ" );
    
    for ( auto histoset : histoSets ){
      std::string getname = histoset;
      //The commented lines are likely incorrect
      // if ( histoset == "Default" ) getname = "Default_BARE";
      // if ( histoset == "MJJ-200-500" ) getname = "MJJ-200-500_BARE";
      // if ( histoset == "MJJ-500-1000" ) getname = "MJJ-500-1000_BARE";
      // if ( histoset == "MJJ-1000-1500" ) getname = "MJJ-1000-1500_BARE";
      // if ( histoset == "MJJ-1500-5000" ) getname = "MJJ-1500-5000_BARE";

      for ( auto plotname : plots ){
	loadHist = 0;
	loadHist = (TH1D*) loadFile->Get( (getname + "/" + getname + "_" + plotname).c_str() );
	if ( loadHist != 0 ){ 
	  _cloned_hists[ filename.first ][ histoset + "_" + plotname ]  = (TH1D*) loadHist->Clone( ( filename.first + "_" + histoset + "_" + plotname   )  ) ;
	}
	
      }     
      for ( auto plotname : plots2D ){
	loadHist2D = 0;
	loadHist2D = (TH2D*) loadFile->Get( (getname + "/" + getname + "_" + plotname).c_str() );
	if ( loadHist2D != 0 ){ 
	  _cloned_hists2D[ filename.first ][ histoset + "_" + plotname ]  = (TH2D*) loadHist2D->Clone( ( filename.first + "_" + histoset + "_" + plotname   )  ) ;
	}
	
      }     

      
      //Uncertainties    
      loadHist = 0;
      loadHist2D = 0;
      std::string loadname = "";
      std::vector<std::string> systplots = {"gen_boson_pt", "gen_jetpt0"};
      for ( auto syst : systplots ){
	if ( syst == "gen_jetpt0" && histoset != "non-VBF") continue;
	for ( int i = 0;i<9;i++){
	  loadname = (getname + "/" + getname + "_"+syst+"_Scale_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist = (TH1D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist != 0 ){ 
	    _cloned_hists[ filename.first ][ histoset + "_" + syst+ "_Scale_" + std::to_string(i) ]  = (TH1D*) loadHist->Clone( ( filename.first + histoset + "_"+syst+"_Scale_" + std::to_string(i) ) );
	  }
	}

	int maxpdfs = 102;
	if ( std::string(filename.first).find("LHEPt")!=std::string::npos ) maxpdfs = 33;
	for ( int i = 0;i<maxpdfs;i++){
	  loadname = (getname + "/" + getname + "_"+syst+"_PDF_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist = (TH1D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist != 0 ){ 
	    _cloned_hists[ filename.first ][ histoset + "_"+syst+"_PDF_" + std::to_string(i) ]  = (TH1D*) loadHist->Clone( ( filename.first + histoset + "_"+syst+"_PDF_" + std::to_string(i) ) );
	  }
	}
      }
      for ( auto syst : plots2D ){
	for ( int i = 0;i<9;i++){
	  loadname = (getname + "/" + getname + "_"+syst+"_Scale_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist2D = (TH2D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist2D != 0 ){ 
	    _cloned_hists2D[ filename.first ][ histoset + "_" + syst+"_Scale_" + std::to_string(i) ]  = (TH2D*) loadHist2D->Clone( ( filename.first + histoset + "_"+syst+"_Scale_" + std::to_string(i) ) );
	  }
	  loadname = (getname + "/" + getname + "_"+syst+"_Scale_HeavyQuark_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist2D = (TH2D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist2D != 0 ){ 
	    _cloned_hists2D[ filename.first ][ histoset + "_" + syst+"_Scale_HeavyQuark_" + std::to_string(i) ]  = (TH2D*) loadHist2D->Clone( ( filename.first + histoset + "_"+syst+"_Scale_HeavyQuark_" + std::to_string(i) ) );
	  }
	  loadname = (getname + "/" + getname + "_"+syst+"_Scale_NoHeavyQuark_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist2D = (TH2D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist2D != 0 ){ 
	    _cloned_hists2D[ filename.first ][ histoset + "_" + syst+"_Scale_NoHeavyQuark_" + std::to_string(i) ]  = (TH2D*) loadHist2D->Clone( ( filename.first + histoset + "_"+syst+"_Scale_NoHeavyQuark_" + std::to_string(i) ) );
	  }
	}
      
	int maxpdfs = 102;
	if ( std::string(filename.first).find("LHEPt")!=std::string::npos ) maxpdfs = 33;
	for ( int i = 0;i<maxpdfs;i++){
	  loadname = (getname + "/" + getname + "_"+syst+"_PDF_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist2D = (TH2D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist2D != 0 ){ 
	    _cloned_hists2D[ filename.first ][ histoset + "_"+syst+"_PDF_" + std::to_string(i) ]  = (TH2D*) loadHist2D->Clone( ( filename.first + histoset + "_"+syst+"_PDF_" + std::to_string(i) ) );
	  }
	}

      }
    }
    
  }
}

void HiggsPlotting::Rebin(){

  std::map<TString,int> RebinValues;

  RebinValues[ "Default_gen_boson_pt" ] = 1;
  RebinValues[ "Default_gen_boson_eta" ] = 1;
  RebinValues[ "Default_gen_mjj" ] = 1;
  RebinValues[ "Default_gen_boson_detajj" ] = 1;
  RebinValues[ "Default_gen_boson_dphijj" ] = 1;
  RebinValues[ "Default_gen_mindphi_jetmet" ] = 1;
  RebinValues[ "Default_LHE_HT" ] = 20;

  RebinValues[ "1JPt150_gen_boson_pt" ] = 1;
  RebinValues[ "1JPt150_gen_boson_eta" ] = 1;
  RebinValues[ "1JPt150_gen_mjj" ] = 1;
  RebinValues[ "1JPt150_gen_boson_detajj" ] = 1;
  RebinValues[ "1JPt150_gen_boson_dphijj" ] = 1;
  RebinValues[ "1JPt150_gen_mindphi_jetmet" ] = 1;
  RebinValues[ "1JPt150_LHE_HT" ] = 20;

  //  RebinValues[ "All_LHE_HT" ] = 1;

  //  RebinValues[ "non-VBF_gen_jetpt0"] = 2;

  //  double bins[13] = {0,70,120,170,220,270,320,370,470,600,750,900,1050};

  double bins[15] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 400, 520, 640, 760, 880,1100}; //andreas's binnings
  double binsHT[10] = {0, 70, 100, 200, 400, 600, 800, 1200, 2500, 3000}; 

  //  double bins[15] = {0,70,100,120,150,170,220,270,320,370,470,600,750,900,1050};

  //  double bins[51] = {0, 40, 80,100, 120,130,140,150, 160,170,180,190, 200,210,220,230, 240,250,260,270, 280,290,300,310, 320,340,360,380, 400,420,440,460,480,500, 520,540,560,580,600,620, 640,680,720,760,800,840,880,950,1000,1050,1100}; //fine binnings


  //  double bins[40] = {0, 40, 80,100, 120,130,140,150, 160,170,180,190, 200,210,220,230, 240,250,260,270, 280,290,300,310, 320,340,360,380, 400,420,440,460,480,500,600,700,800,900,1000,1100}; //fine binnings


  //  double bins[33] = {0, 40, 80,100,120,130,140,150, 160,170,180,190, 200,210,220,230, 240,250,260,270, 280,290,300,350,400,450,500,600,700,800,900,1000,1100}; //fine binnings

  //double bins[22] = {0, 40, 80,100,120,140,160,180,200,225,250,300,350,400,450,500,600,700,800,900,1000,1100}; //fine binnings
  //First of all find the peak then this is the "split" value
  double bins_nonvbf_bosonpt[18] = {0,70,100,120,150,170,200,225,250,275,300,350,400,450,600,750,900,1050};
  //  double bins_nonvbf_jetpt[] = {};
  //  double binsmjj[12] = {0,100,200,300,400,500,750,1000,1500,2000,3000,3500};

  for(auto &histsets : _cloned_hists2D) {
    for(auto &plot : histsets.second) {
      if ( std::string(plot.first).find("VTR")==std::string::npos ) continue;
      //      plot.second =  (TH2D*) plot.second->Rebin( 14/, plot.first + "_rebinnned" , bins ) ;
      plot.second =  (TH2D*)plot.second->Clone( plot.first + "_rebinnned" );
      //      plot.second->RebinY(plot.second->GetNbinsY());
    }
  }
    
  for(auto &histsets : _cloned_hists) {
    for(auto &plot : histsets.second) {

      if ( std::string(plot.first).find("gen_boson_pt")==std::string::npos && std::string(plot.first).find("gen_jetpt0")==std::string::npos && plot.first != "Default_gen_mjj" && std::string(plot.first).find("LHE_HT")==std::string::npos){
	if ( RebinValues.count(plot.first)>0 )   plot.second->Rebin( RebinValues[ plot.first ]  ) ;
      }
      
      else if ( std::string(plot.first).find("gen_boson_pt")!=std::string::npos ){
	
	if ( std::string(plot.first).find("non-VBF")!=std::string::npos ){
	  plot.second =  (TH1D*) plot.second->Rebin( 17, plot.first + "_rebinnned" , bins_nonvbf_bosonpt ) ;
	  plot.second->Scale( 1,"width" );
	}
	else{
	  	  plot.second =  (TH1D*) plot.second->Rebin( 14, plot.first + "_rebinnned" , bins ) ;
	  //	  plot.second =  (TH1D*) plot.second->Rebin( 50, plot.first + "_rebinnned" , bins ) ;
	  //	  plot.second =  (TH1D*) plot.second->Rebin( 39, plot.first + "_rebinnned" , bins ) ;
	  //	  plot.second =  (TH1D*) plot.second->Rebin( 32, plot.first + "_rebinnned" , bins ) ;
	  //	  plot.second =  (TH1D*) plot.second->Rebin( 21, plot.first + "_rebinnned" , bins ) ;
		  	  plot.second->Scale( 1,"width" );
		  //  plot.second->Scale( 1,"" );
	}

      }
      else if ( plot.first == "Default_gen_mjj" ){
	  //	  plot.second =  (TH1D*) plot.second->Rebin( 11, plot.first + "_rebinnned" , binsmjj ) ;
	  //	  plot.second->Scale( 1,"width" );
      }
      else if ( plot.first == "All_LHE_HT" ){
	// plot.second =  (TH1D*) plot.second->Rebin( 9, plot.first + "_rebinnned" , binsHT ) ;
	// plot.second->Scale( 1,"width" );
      }

      else if ( std::string(plot.first).find("gen_jetpt0")!=std::string::npos ){
	plot.second->Rebin( 2 );
      }
    }
  }
  
  
}

void HiggsPlotting::CombineHistograms(){

  std::map<TString, double> _xs;
  std::map<TString, double> _sum;
  std::map<TString, double> _num;

  std::map<TString, double> _stitch;

  for (auto & histset : _cloned_hists ){
    _sum[ histset.first ] = ((histset.second)[ "All_gen_events" ])->GetBinContent( 2 );
    _num[ histset.first ] = ((histset.second)[ "All_gen_events" ])->GetBinContent( 1 );
  }

  

  //Andreas's cross-sections (NLO)

  //////////////////
  //  NLO LHE Pt  // 
  //////////////////

  ///////  Z  /////////

  _xs[ "ZLL-NLO-LHEPt-1J-50-150" ] = 312.3;     
  _xs[ "ZLL-NLO-LHEPt-2J-50-150" ] = 167.9;     
  _xs[ "ZLL-NLO-LHEPt-1J-150-250" ] = 9.555;     
  _xs[ "ZLL-NLO-LHEPt-2J-150-250" ] = 15.68;     
  _xs[ "ZLL-NLO-LHEPt-1J-250-400" ] = 1.098;     
  _xs[ "ZLL-NLO-LHEPt-2J-250-400" ] = 2.717;     
  _xs[ "ZLL-NLO-LHEPt-1J-400-Inf" ] = 0.1202;     
  _xs[ "ZLL-NLO-LHEPt-2J-400-Inf" ] = 0.446;     

  _xs[ "ZLL-NLO-LHEPt-1J-50-150-TOT" ] = 312.3;     
  _xs[ "ZLL-NLO-LHEPt-2J-50-150-TOT" ] = 167.9;     
  _xs[ "ZLL-NLO-LHEPt-1J-150-250-TOT" ] = 9.555;     
  _xs[ "ZLL-NLO-LHEPt-2J-150-250-TOT" ] = 15.68;     
  _xs[ "ZLL-NLO-LHEPt-1J-250-400-TOT" ] = 1.098;     
  _xs[ "ZLL-NLO-LHEPt-2J-250-400-TOT" ] = 2.717;     
  _xs[ "ZLL-NLO-LHEPt-1J-400-Inf-TOT" ] = 0.1202;     
  _xs[ "ZLL-NLO-LHEPt-2J-400-Inf-TOT" ] = 0.446;     

  _num["ZLL-NLO-LHEPt-1J-50-150-TOT" ]  =    _num["ZLL-NLO-LHEPt-1J-50-150" ]  +   _num["ZLL-NLO-LHEPt-1J-50-150-ext1" ];
  _num["ZLL-NLO-LHEPt-1J-150-250-TOT" ]  =    _num["ZLL-NLO-LHEPt-1J-150-250" ]  +   _num["ZLL-NLO-LHEPt-1J-150-250-ext1" ];
  _num["ZLL-NLO-LHEPt-1J-250-400-TOT" ]  =    _num["ZLL-NLO-LHEPt-1J-250-400" ]  +   _num["ZLL-NLO-LHEPt-1J-250-400-ext1" ];
  _num["ZLL-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _num["ZLL-NLO-LHEPt-1J-400-Inf" ]  +   _num["ZLL-NLO-LHEPt-1J-400-Inf-ext1" ];
  _num["ZLL-NLO-LHEPt-2J-50-150-TOT" ]  =    _num["ZLL-NLO-LHEPt-2J-50-150" ]  +   _num["ZLL-NLO-LHEPt-2J-50-150-ext1" ];
  _num["ZLL-NLO-LHEPt-2J-150-250-TOT" ]  =    _num["ZLL-NLO-LHEPt-2J-150-250" ]  +   _num["ZLL-NLO-LHEPt-2J-150-250-ext1" ];
  _num["ZLL-NLO-LHEPt-2J-250-400-TOT" ]  =    _num["ZLL-NLO-LHEPt-2J-250-400" ]  +   _num["ZLL-NLO-LHEPt-2J-250-400-ext1" ];
  _num["ZLL-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _num["ZLL-NLO-LHEPt-2J-400-Inf" ]  +   _num["ZLL-NLO-LHEPt-2J-400-Inf-ext1" ];

  _sum["ZLL-NLO-LHEPt-1J-50-150-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-50-150" ]  +   _sum["ZLL-NLO-LHEPt-1J-50-150-ext1" ];
  _sum["ZLL-NLO-LHEPt-1J-150-250-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-150-250" ]  +   _sum["ZLL-NLO-LHEPt-1J-150-250-ext1" ];
  _sum["ZLL-NLO-LHEPt-1J-250-400-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-250-400" ]  +   _sum["ZLL-NLO-LHEPt-1J-250-400-ext1" ];
  _sum["ZLL-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-400-Inf" ]  +   _sum["ZLL-NLO-LHEPt-1J-400-Inf-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-50-150-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-50-150" ]  +   _sum["ZLL-NLO-LHEPt-2J-50-150-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-150-250-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-150-250" ]  +   _sum["ZLL-NLO-LHEPt-2J-150-250-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-250-400-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-250-400" ]  +   _sum["ZLL-NLO-LHEPt-2J-250-400-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-400-Inf" ]  +   _sum["ZLL-NLO-LHEPt-2J-400-Inf-ext1" ];


  for (auto const& histset : _cloned_hists["ZLL-NLO-LHEPt-1J-50-150"]){
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-NLO-LHEPt-1J-50-150_" + histset.first  );   
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Reset();

    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-50-150"     ] / _sum["ZLL-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-50-150-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-50-150"     ] / _sum["ZLL-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-50-150"     ] / _sum["ZLL-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-50-150-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-50-150"     ] / _sum["ZLL-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-150-250"     ] / _sum["ZLL-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-150-250"     ] / _sum["ZLL-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-150-250"     ] / _sum["ZLL-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-150-250-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-150-250"     ] / _sum["ZLL-NLO-LHEPt-2J-150-250-TOT"     ] );

    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-250-400"     ] / _sum["ZLL-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-250-400"     ] / _sum["ZLL-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-250-400"     ] / _sum["ZLL-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-250-400"     ] / _sum["ZLL-NLO-LHEPt-2J-250-400-TOT"     ] );
   
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-1J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-2J-400-Inf-TOT"     ] );
    _cloned_hists["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-LHEPt-2J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-2J-400-Inf-TOT"     ] );

  }





  //2D
  for (auto const& histset : _cloned_hists2D["ZLL-NLO-LHEPt-1J-50-150"]){
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL-NLO-LHEPt-1J-50-150_" + histset.first  );   
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Reset();

    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-50-150"     ] / _sum["ZLL-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-50-150-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-50-150"     ] / _sum["ZLL-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-50-150"     ] / _sum["ZLL-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-50-150-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-50-150"     ] / _sum["ZLL-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-150-250"     ] / _sum["ZLL-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-150-250"     ] / _sum["ZLL-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-150-250"     ] / _sum["ZLL-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-150-250-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-150-250"     ] / _sum["ZLL-NLO-LHEPt-2J-150-250-TOT"     ] );

    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-250-400"     ] / _sum["ZLL-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-250-400"     ] / _sum["ZLL-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-250-400"     ] / _sum["ZLL-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-250-400"     ] / _sum["ZLL-NLO-LHEPt-2J-250-400-TOT"     ] );
   
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-1J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-1J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-2J-400-Inf-TOT"     ] );
    _cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-LHEPt-2J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-LHEPt-2J-400-Inf"     ] / _sum["ZLL-NLO-LHEPt-2J-400-Inf-TOT"     ] );

  }





  ///////  ZNUNU  /////////

  _xs[ "ZNN-NLO-LHEPt-1J-50-150" ] = 602.9;     
  _xs[ "ZNN-NLO-LHEPt-2J-50-150" ] = 328.9;     

  _xs[ "ZNN-NLO-LHEPt-1J-150-250" ] = 18.12;     
  _xs[ "ZNN-NLO-LHEPt-2J-150-250" ] = 29.74;     

  _xs[ "ZNN-NLO-LHEPt-1J-250-400" ] = 2.045;     
  _xs[ "ZNN-NLO-LHEPt-2J-250-400" ] = 5.23;     

  _xs[ "ZNN-NLO-LHEPt-1J-400-Inf" ] = 0.2256;     
  _xs[ "ZNN-NLO-LHEPt-2J-400-Inf" ] = 0.8433;     


  _num["ZNN-NLO-LHEPt-1J-50-150-TOT" ]  =    _num["ZNN-NLO-LHEPt-1J-50-150" ] ;
  _num["ZNN-NLO-LHEPt-1J-150-250-TOT" ]  =    _num["ZNN-NLO-LHEPt-1J-150-250" ]  +   _num["ZNN-NLO-LHEPt-1J-150-250-ext1" ];
  _num["ZNN-NLO-LHEPt-1J-250-400-TOT" ]  =    _num["ZNN-NLO-LHEPt-1J-250-400" ]  +   _num["ZNN-NLO-LHEPt-1J-250-400-ext1" ];
  _num["ZNN-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _num["ZNN-NLO-LHEPt-1J-400-Inf" ] ;
  _num["ZNN-NLO-LHEPt-2J-50-150-TOT" ]  =    _num["ZNN-NLO-LHEPt-2J-50-150" ] ;
  _num["ZNN-NLO-LHEPt-2J-150-250-TOT" ]  =    _num["ZNN-NLO-LHEPt-2J-150-250" ]  ;
  _num["ZNN-NLO-LHEPt-2J-250-400-TOT" ]  =    _num["ZNN-NLO-LHEPt-2J-250-400" ]  +   _num["ZNN-NLO-LHEPt-2J-250-400-ext1" ];
  _num["ZNN-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _num["ZNN-NLO-LHEPt-2J-400-Inf" ] ;

  _sum["ZNN-NLO-LHEPt-1J-50-150-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-50-150" ] ;
  _sum["ZNN-NLO-LHEPt-1J-150-250-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-150-250" ]  +   _sum["ZNN-NLO-LHEPt-1J-150-250-ext1" ];
  _sum["ZNN-NLO-LHEPt-1J-250-400-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-250-400" ]  +   _sum["ZNN-NLO-LHEPt-1J-250-400-ext1" ];
  _sum["ZNN-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-400-Inf" ] ;
  _sum["ZNN-NLO-LHEPt-2J-50-150-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-50-150" ] ;
  _sum["ZNN-NLO-LHEPt-2J-150-250-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-150-250" ]  ;
  _sum["ZNN-NLO-LHEPt-2J-250-400-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-250-400" ]  +   _sum["ZNN-NLO-LHEPt-2J-250-400-ext1" ];
  _sum["ZNN-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-400-Inf" ];


  for (auto const& histset : _cloned_hists["ZNN-NLO-LHEPt-1J-50-150"]){
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ] = (TH1D*) histset.second->Clone( "ZNN-NLO-LHEPt-1J-50-150_" + histset.first  );   
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Reset();
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-50-150"     ] / _sum["ZNN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-50-150"     ] / _sum["ZNN-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-150-250"     ] / _sum["ZNN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-150-250"     ] / _sum["ZNN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-150-250"     ] / _sum["ZNN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-250-400"     ] / _sum["ZNN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-1J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-250-400"     ] / _sum["ZNN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-250-400"     ] / _sum["ZNN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-2J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-250-400"     ] / _sum["ZNN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-400-Inf"     ] / _sum["ZNN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["ZNN-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-400-Inf"     ] / _sum["ZNN-NLO-LHEPt-2J-400-Inf-TOT"     ] );

  }


  //2D
  for (auto const& histset : _cloned_hists2D["ZNN-NLO-LHEPt-1J-50-150"]){
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ] = (TH2D*) histset.second->Clone( "ZNN-NLO-LHEPt-1J-50-150_" + histset.first  );   
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Reset();

    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-50-150"     ] / _sum["ZNN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-50-150"     ] / _sum["ZNN-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-150-250"     ] / _sum["ZNN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-150-250"     ] / _sum["ZNN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-150-250"     ] / _sum["ZNN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-250-400"     ] / _sum["ZNN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-1J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-250-400"     ] / _sum["ZNN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-250-400"     ] / _sum["ZNN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-2J-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-250-400"     ] / _sum["ZNN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-1J-400-Inf"     ] / _sum["ZNN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists2D["ZNN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["ZNN-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["ZNN-NLO-LHEPt-2J-400-Inf"     ] / _sum["ZNN-NLO-LHEPt-2J-400-Inf-TOT"     ] );
  }




  
  ///////  W  /////////

  _xs[ "WLN-NLO-LHEPt-1J-50-150" ] = 2675.79;     
  _xs[ "WLN-NLO-LHEPt-1J-100-150" ] = 284.06;     
  _xs[ "WLN-NLO-LHEPt-1J-150-250" ] = 71.71;     
  _xs[ "WLN-NLO-LHEPt-1J-250-400" ] = 8.06;     
  _xs[ "WLN-NLO-LHEPt-1J-400-Inf" ] = 0.89;     
  _xs[ "WLN-NLO-LHEPt-2J-50-150" ] = 1345.61;
  _xs[ "WLN-NLO-LHEPt-2J-100-150" ] = 281.63;
  _xs[ "WLN-NLO-LHEPt-2J-150-250" ] = 108.59;     
  _xs[ "WLN-NLO-LHEPt-2J-250-400" ] = 18.03;     
  _xs[ "WLN-NLO-LHEPt-2J-400-Inf" ] = 3.0;     
 
  _xs[ "WLN-NLO-LHEPt-1J-50-150-TOT" ] = 2675.79;     
  _xs[ "WLN-NLO-LHEPt-1J-100-150-TOT" ] = 284.06;     
  _xs[ "WLN-NLO-LHEPt-1J-150-250-TOT" ] = 71.71;     
  _xs[ "WLN-NLO-LHEPt-1J-250-400-TOT" ] = 8.06;     
  _xs[ "WLN-NLO-LHEPt-1J-400-Inf-TOT" ] = 0.89;     
  _xs[ "WLN-NLO-LHEPt-2J-50-150-TOT" ] = 1345.61;
  _xs[ "WLN-NLO-LHEPt-2J-100-150-TOT" ] = 281.63;
  _xs[ "WLN-NLO-LHEPt-2J-150-250-TOT" ] = 108.59;     
  _xs[ "WLN-NLO-LHEPt-2J-250-400-TOT" ] = 18.03;     
  _xs[ "WLN-NLO-LHEPt-2J-400-Inf-TOT" ] = 3.0;     

  _num["WLN-NLO-LHEPt-1J-50-150-TOT" ]  =    _num["WLN-NLO-LHEPt-1J-50-150" ]  +   _num["WLN-NLO-LHEPt-1J-50-150-ext1" ];
  _num["WLN-NLO-LHEPt-1J-100-150-TOT" ]  =    _num["WLN-NLO-LHEPt-1J-100-150" ]  +   _num["WLN-NLO-LHEPt-1J-100-150-ext1" ];
  _num["WLN-NLO-LHEPt-1J-150-250-TOT" ]  =    _num["WLN-NLO-LHEPt-1J-150-250" ]  +   _num["WLN-NLO-LHEPt-1J-150-250-ext1" ];
  _num["WLN-NLO-LHEPt-1J-250-400-TOT" ]  =    _num["WLN-NLO-LHEPt-1J-250-400" ]  ;//+   _num["WLN-NLO-LHEPt-1J-250-400-ext1" ];
  _num["WLN-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _num["WLN-NLO-LHEPt-1J-400-Inf" ]  +   _num["WLN-NLO-LHEPt-1J-400-Inf-ext1" ];
  _num["WLN-NLO-LHEPt-2J-50-150-TOT" ]  =    _num["WLN-NLO-LHEPt-2J-50-150" ]  +   _num["WLN-NLO-LHEPt-2J-50-150-ext1" ];
  _num["WLN-NLO-LHEPt-2J-100-150-TOT" ]  =    _num["WLN-NLO-LHEPt-2J-100-150" ]  +   _num["WLN-NLO-LHEPt-2J-100-150-ext1" ];
  _num["WLN-NLO-LHEPt-2J-150-250-TOT" ]  =    _num["WLN-NLO-LHEPt-2J-150-250" ]  +   _num["WLN-NLO-LHEPt-2J-150-250-ext1" ];
  _num["WLN-NLO-LHEPt-2J-250-400-TOT" ]  =    _num["WLN-NLO-LHEPt-2J-250-400" ]  ;//+   _num["WLN-NLO-LHEPt-2J-250-400-ext1" ];
  _num["WLN-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _num["WLN-NLO-LHEPt-2J-400-Inf" ]  ;//+   _num["WLN-NLO-LHEPt-2J-400-Inf-ext1" ];


  _sum["WLN-NLO-LHEPt-1J-50-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-50-150" ]  +   _sum["WLN-NLO-LHEPt-1J-50-150-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-100-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-100-150" ]  +   _sum["WLN-NLO-LHEPt-1J-100-150-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-150-250-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-150-250" ]  +   _sum["WLN-NLO-LHEPt-1J-150-250-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-250-400-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-250-400" ]  ;//+   _sum["WLN-NLO-LHEPt-1J-250-400-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-400-Inf" ]  +   _sum["WLN-NLO-LHEPt-1J-400-Inf-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-50-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-50-150" ]  +   _sum["WLN-NLO-LHEPt-2J-50-150-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-100-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-100-150" ]  +   _sum["WLN-NLO-LHEPt-2J-100-150-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-150-250-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-150-250" ]  +   _sum["WLN-NLO-LHEPt-2J-150-250-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-250-400-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-250-400" ]  ;//+   _sum["WLN-NLO-LHEPt-2J-250-400-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-400-Inf" ]  ;//+   _sum["WLN-NLO-LHEPt-2J-400-Inf-ext1" ];

  for (auto const& histset : _cloned_hists["WLN-NLO-LHEPt-1J-50-150"]){
    //    std::cout << histset.first << std::endl;    
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-NLO-LHEPt-1J-100-150_" + histset.first  );   
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Reset();
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-50-150"     ] / _sum["WLN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-50-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-50-150"     ] / _sum["WLN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-50-150"     ] / _sum["WLN-NLO-LHEPt-2J-50-150-TOT"     ] );
       _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-50-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-50-150"     ] / _sum["WLN-NLO-LHEPt-2J-50-150-TOT"     ] );
    // _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-100-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-100-150"     ] / _sum["WLN-NLO-LHEPt-1J-100-150-TOT"     ] );
    // _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-100-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-100-150"     ] / _sum["WLN-NLO-LHEPt-1J-100-150-TOT"     ] );
    // _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-100-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-100-150"     ] / _sum["WLN-NLO-LHEPt-2J-100-150-TOT"     ] );
    //    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-100-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-100-150"     ] / _sum["WLN-NLO-LHEPt-2J-100-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-150-250"     ] / _sum["WLN-NLO-LHEPt-1J-150-250-TOT"     ] ); 
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-150-250"     ] / _sum["WLN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-150-250"     ] / _sum["WLN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-150-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-150-250"     ] / _sum["WLN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-250-400"     ] / _sum["WLN-NLO-LHEPt-1J-250-400-TOT"     ] );
    //    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-250-400-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-250-400"     ] / _sum["WLN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-250-400"     ] / _sum["WLN-NLO-LHEPt-2J-250-400-TOT"     ] );
    //    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-250-400-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-250-400"     ] / _sum["WLN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-2J-400-Inf-TOT"     ] );
    //    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-2J-400-Inf-TOT"     ] );
  }


  //2D



  for (auto const& histset : _cloned_hists2D["WLN-NLO-LHEPt-1J-50-150"]){
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN-NLO-LHEPt-1J-100-150_" + histset.first  );   
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Reset();
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-50-150"     ] / _sum["WLN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-50-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-50-150"     ] / _sum["WLN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-50-150"     ] / _sum["WLN-NLO-LHEPt-2J-50-150-TOT"     ] );
       _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-2J-50-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-50-150"     ] / _sum["WLN-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-150-250"     ] / _sum["WLN-NLO-LHEPt-1J-150-250-TOT"     ] ); 
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-150-250"     ] / _sum["WLN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-150-250"     ] / _sum["WLN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-2J-150-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-150-250"     ] / _sum["WLN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-250-400"     ] / _sum["WLN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-250-400"     ] / _sum["WLN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-1J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists2D["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-2J-400-Inf-TOT"     ] );
  }



  /////////////////////
  //  NLO Pt binned  // 
  /////////////////////

  ///////  Z  /////////

 //Presentation
 _xs[ "ZLL-NLO-Pt-100-250-ext1"] = 84.015;
 _xs[ "ZLL-NLO-Pt-100-250-ext2"] = 84.015;
 _xs[ "ZLL-NLO-Pt-100-250-ext5"] = 84.015;
 _xs[ "ZLL-NLO-Pt-250-400"] = 3.2283;
 // _xs[ "ZLL-NLO-Pt-250-400-ext1"] = 3.2283;
 _xs[ "ZLL-NLO-Pt-250-400-ext2"] = 3.2283;
 _xs[ "ZLL-NLO-Pt-250-400-ext5"] = 3.2283;
 _xs[ "ZLL-NLO-Pt-400-650"] = 0.43604;
 _xs[ "ZLL-NLO-Pt-400-650-ext1"] = 0.43604;
 _xs[ "ZLL-NLO-Pt-400-650-ext2"] = 0.43604;
 _xs[ "ZLL-NLO-Pt-650-Inf"] = 0.04098;
 _xs[ "ZLL-NLO-Pt-650-Inf-ext1"] = 0.04098;
 _xs[ "ZLL-NLO-Pt-650-Inf-ext2"] = 0.04098;

 _sum["ZLL-NLO-Pt-100-250-TOT"     ] = _sum["ZLL-NLO-Pt-100-250-ext1"     ] + _sum["ZLL-NLO-Pt-100-250-ext2"     ] +_sum["ZLL-NLO-Pt-100-250-ext5"     ] ;
 _sum["ZLL-NLO-Pt-250-400-TOT"     ] =  _sum["ZLL-NLO-Pt-250-400"     ] + _sum["ZLL-NLO-Pt-250-400-ext2"     ] +_sum["ZLL-NLO-Pt-250-400-ext5"     ] ;
 _sum["ZLL-NLO-Pt-400-650-TOT"     ] =  _sum["ZLL-NLO-Pt-400-650"     ] + _sum["ZLL-NLO-Pt-400-650-ext1"     ] +_sum["ZLL-NLO-Pt-400-650-ext2"     ] ;
 _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] =  _sum["ZLL-NLO-Pt-650-Inf"     ] + _sum["ZLL-NLO-Pt-650-Inf-ext1"     ] +_sum["ZLL-NLO-Pt-650-Inf-ext2"     ] ;
  _num["ZLL-NLO-Pt-100-250-TOT"     ] = _num["ZLL-NLO-Pt-100-250-ext1"     ] + _num["ZLL-NLO-Pt-100-250-ext2"     ] +_num["ZLL-NLO-Pt-100-250-ext5"     ] ;
 _num["ZLL-NLO-Pt-250-400-TOT"     ] =  _num["ZLL-NLO-Pt-250-400"     ] + _num["ZLL-NLO-Pt-250-400-ext2"     ] +_num["ZLL-NLO-Pt-250-400-ext5"     ] ;
 _num["ZLL-NLO-Pt-400-650-TOT"     ] =  _num["ZLL-NLO-Pt-400-650"     ] + _num["ZLL-NLO-Pt-400-650-ext1"     ] +_num["ZLL-NLO-Pt-400-650-ext2"     ] ;
 _num["ZLL-NLO-Pt-650-Inf-TOT"     ] =  _num["ZLL-NLO-Pt-650-Inf"     ] + _num["ZLL-NLO-Pt-650-Inf-ext1"     ] +_num["ZLL-NLO-Pt-650-Inf-ext2"     ] ;
 
 for (auto const& histset : _cloned_hists["ZLL-NLO-Pt-100-250-ext1"]){
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-NLO-Pt-100-250_" + histset.first  );   
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Reset();
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-100-250-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-100-250-ext1"     ] / _sum["ZLL-NLO-Pt-100-250-TOT"     ] );
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-100-250-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-100-250-ext2"     ] / _sum["ZLL-NLO-Pt-100-250-TOT"     ] );
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-100-250-ext5" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-100-250-ext5"     ] / _sum["ZLL-NLO-Pt-100-250-TOT"     ] );
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-250-400" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400"     ] / _sum["ZLL-NLO-Pt-250-400-TOT"     ] );
  //    _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400-ext1"     ] / _sum["ZLL-NLO-Pt-250-400-ext1"     ] );
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-250-400-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400-ext2"     ] / _sum["ZLL-NLO-Pt-250-400-TOT"     ] );
  
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-250-400-ext5" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400-ext5"     ] / _sum["ZLL-NLO-Pt-250-400-TOT"     ] );
  
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-400-650" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-400-650"     ] / _sum["ZLL-NLO-Pt-400-650-TOT"     ] );
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-400-650-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-400-650-ext1"     ] / _sum["ZLL-NLO-Pt-400-650-TOT"     ] );
  
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-400-650-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-400-650-ext2"     ] / _sum["ZLL-NLO-Pt-400-650-TOT"     ] );
  
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-650-Inf" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-650-Inf"     ] / _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] );
  
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-650-Inf-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-650-Inf-ext1"     ] / _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] );
  
  _cloned_hists["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-Pt-650-Inf-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-650-Inf-ext2"     ] / _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] );

  }



 //2D

 for (auto const& histset : _cloned_hists2D["ZLL-NLO-Pt-100-250-ext1"]){
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL-NLO-Pt-100-250_" + histset.first  );   
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Reset();
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-100-250-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-100-250-ext1"     ] / _sum["ZLL-NLO-Pt-100-250-TOT"     ] );
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-100-250-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-100-250-ext2"     ] / _sum["ZLL-NLO-Pt-100-250-TOT"     ] );
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-100-250-ext5" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-100-250-ext5"     ] / _sum["ZLL-NLO-Pt-100-250-TOT"     ] );
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-250-400" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400"     ] / _sum["ZLL-NLO-Pt-250-400-TOT"     ] );
  //    _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-250-400-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400-ext1"     ] / _sum["ZLL-NLO-Pt-250-400-ext1"     ] );
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-250-400-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400-ext2"     ] / _sum["ZLL-NLO-Pt-250-400-TOT"     ] );
  
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-250-400-ext5" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-250-400-ext5"     ] / _sum["ZLL-NLO-Pt-250-400-TOT"     ] );
  
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-400-650" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-400-650"     ] / _sum["ZLL-NLO-Pt-400-650-TOT"     ] );
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-400-650-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-400-650-ext1"     ] / _sum["ZLL-NLO-Pt-400-650-TOT"     ] );
  
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-400-650-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-400-650-ext2"     ] / _sum["ZLL-NLO-Pt-400-650-TOT"     ] );
  
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-650-Inf" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-650-Inf"     ] / _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] );
  
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-650-Inf-ext1" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-650-Inf-ext1"     ] / _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] );
  
  _cloned_hists2D["ZLL-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-Pt-650-Inf-ext2" ][histset.first]  , 1E3 * _xs["ZLL-NLO-Pt-650-Inf-ext2"     ] / _sum["ZLL-NLO-Pt-650-Inf-TOT"     ] );

  }



 ///////  W  /////////

  _xs[ "WLN-NLO-Pt-100-250"] = 689.749632 ;
  _xs[ "WLN-NLO-Pt-250-400"] = 24.5069015 ;
  _xs[ "WLN-NLO-Pt-400-600"] = 3.110130566 ;
  _xs[ "WLN-NLO-Pt-600-Inf"] = 0.4683178368 ;

  _sum["WLN-NLO-Pt-100-250-TOT"     ] = _sum["WLN-NLO-Pt-100-250"     ] + _sum["WLN-NLO-Pt-100-250-ext1"      ];
  _sum["WLN-NLO-Pt-250-400-TOT"     ] =  _sum["WLN-NLO-Pt-250-400"     ] + _sum["WLN-NLO-Pt-250-400-ext1"     ];
  _sum["WLN-NLO-Pt-400-600-TOT"     ] =  _sum["WLN-NLO-Pt-400-600"     ] + _sum["WLN-NLO-Pt-400-600-ext1"     ];
  _sum["WLN-NLO-Pt-600-Inf-TOT"     ] =  _sum["WLN-NLO-Pt-600-Inf"     ] + _sum["WLN-NLO-Pt-600-Inf-ext1"     ];
 
  for (auto const& histset : _cloned_hists["WLN-NLO-Pt-100-250"]){
    
    _cloned_hists["WLN-NLO-Pt"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-NLO-Pt-100-250_" + histset.first  );   
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Reset();

    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-100-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-100-250"     ] / _sum["WLN-NLO-Pt-100-250-TOT"     ] );
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-250-400"     ] / _sum["WLN-NLO-Pt-250-400-TOT"     ] );
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-400-600" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-400-600"     ] / _sum["WLN-NLO-Pt-400-600-TOT"     ] );
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-600-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-600-Inf"     ] / _sum["WLN-NLO-Pt-600-Inf-TOT"     ] );

    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-100-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-100-250"     ] / _sum["WLN-NLO-Pt-100-250-TOT"     ] );
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-250-400-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-250-400"     ] / _sum["WLN-NLO-Pt-250-400-TOT"     ] );
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-400-600-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-400-600"     ] / _sum["WLN-NLO-Pt-400-600-TOT"     ] );
    _cloned_hists["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-Pt-600-Inf-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-600-Inf"     ] / _sum["WLN-NLO-Pt-600-Inf-TOT"     ] );

  }
  
  //2D
  for (auto const& histset : _cloned_hists2D["WLN-NLO-Pt-100-250"]){
    
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN-NLO-Pt-100-250_" + histset.first  );   
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Reset();

    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-100-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-100-250"     ] / _sum["WLN-NLO-Pt-100-250-TOT"     ] );
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-250-400"     ] / _sum["WLN-NLO-Pt-250-400-TOT"     ] );
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-400-600" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-400-600"     ] / _sum["WLN-NLO-Pt-400-600-TOT"     ] );
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-600-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-600-Inf"     ] / _sum["WLN-NLO-Pt-600-Inf-TOT"     ] );

    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-100-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-100-250"     ] / _sum["WLN-NLO-Pt-100-250-TOT"     ] );
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-250-400-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-250-400"     ] / _sum["WLN-NLO-Pt-250-400-TOT"     ] );
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-400-600-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-400-600"     ] / _sum["WLN-NLO-Pt-400-600-TOT"     ] );
    _cloned_hists2D["WLN-NLO-Pt"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-Pt-600-Inf-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-Pt-600-Inf"     ] / _sum["WLN-NLO-Pt-600-Inf-TOT"     ] );

  }
  


  /////////////////
  //  NLO Other  // 
  /////////////////


  ///////  Z  /////////  

 _xs[ "ZLL-NLO-orig"] = 6529;
 _xs[ "ZLL-NLO-ext"] = 6529;

 _sum["ZLL-NLO-TOT"] = _sum["ZLL-NLO-orig" ]  + _sum["ZLL-NLO-ext" ];
 _num["ZLL-NLO-TOT"] = _num["ZLL-NLO-orig" ]  + _num["ZLL-NLO-ext" ];
 
 for (auto const& histset : _cloned_hists["ZLL-NLO-orig"]){
  
    _cloned_hists["ZLL-NLO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-NLO-orig_" + histset.first  );   
    _cloned_hists["ZLL-NLO"][ histset.first ]->Reset();
    _cloned_hists["ZLL-NLO"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-orig"][histset.first]  ,  1E3 * _xs["ZLL-NLO-orig"     ] / _sum["ZLL-NLO-TOT"     ] );
    _cloned_hists["ZLL-NLO"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-ext" ][histset.first]  ,  1E3 * _xs["ZLL-NLO-ext"      ] / _sum["ZLL-NLO-TOT"      ] );
    
  }
 
 //2D
 for (auto const& histset : _cloned_hists2D["ZLL-NLO-orig"]){
  
    _cloned_hists2D["ZLL-NLO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL-NLO-orig_" + histset.first  );   
    _cloned_hists2D["ZLL-NLO"][ histset.first ]->Reset();
    _cloned_hists2D["ZLL-NLO"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-orig"][histset.first]  ,  1E3 * _xs["ZLL-NLO-orig"     ] / _sum["ZLL-NLO-TOT"     ] );
    _cloned_hists2D["ZLL-NLO"][ histset.first ]->Add( _cloned_hists2D["ZLL-NLO-ext" ][histset.first]  ,  1E3 * _xs["ZLL-NLO-ext"      ] / _sum["ZLL-NLO-TOT"      ] );
    
  }
 

  ///////  W  /////////  
  //From Presentation (and DB?)
 _xs[ "WLN-NLO-0J"] = 50131.98 ;
 _xs[ "WLN-NLO-1J"] = 8426.09 ;
 _xs[ "WLN-NLO-2J"] = 3172.96 ;
 
  for (auto const& histset : _cloned_hists["WLN-NLO-0J"]){
    
    _cloned_hists["WLN-NLO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-NLO-0J_" + histset.first  );   
    _cloned_hists["WLN-NLO"][ histset.first ]->Reset();
    _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-0J" ][histset.first]  , 1E3 * _xs["WLN-NLO-0J"     ] / _sum["WLN-NLO-0J"     ] );
    _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-1J" ][histset.first]  , 1E3 * _xs["WLN-NLO-1J"      ] / _sum["WLN-NLO-1J"      ] );
    _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-2J" ][histset.first]  , 1E3 * _xs["WLN-NLO-2J"      ] / _sum["WLN-NLO-2J"      ]  );
    
  }

  //2D
 
  for (auto const& histset : _cloned_hists2D["WLN-NLO-0J"]){
    
    _cloned_hists2D["WLN-NLO"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN-NLO-0J_" + histset.first  );   
    _cloned_hists2D["WLN-NLO"][ histset.first ]->Reset();
    _cloned_hists2D["WLN-NLO"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-0J" ][histset.first]  , 1E3 * _xs["WLN-NLO-0J"     ] / _sum["WLN-NLO-0J"     ] );
    _cloned_hists2D["WLN-NLO"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-1J" ][histset.first]  , 1E3 * _xs["WLN-NLO-1J"      ] / _sum["WLN-NLO-1J"      ] );
    _cloned_hists2D["WLN-NLO"][ histset.first ]->Add( _cloned_hists2D["WLN-NLO-2J" ][histset.first]  , 1E3 * _xs["WLN-NLO-2J"      ] / _sum["WLN-NLO-2J"      ]  );
    
  }

 ////////////////////////////////////////////////////////

  ////////////////////
  //  LO HT Binned  // 
  ////////////////////


  ///////  Z  /////////  
  //ORGINAL
  // _xs[ "ZLL-LO-70-100" ] = 1.47E+02;
  // _xs[ "ZLL-LO-100-200"] = 1.62E+02;
  // _xs[ "ZLL-LO-100-200-ext"] = 1.61E+02;
  // _xs[ "ZLL-LO-200-400"] = 4.84E+01;
  // _xs[ "ZLL-LO-200-400-ext"] = 4.85E+01;
  // _xs[ "ZLL-LO-400-600"] = 7.06E+00;
  // _xs[ "ZLL-LO-400-600-ext"] = 7.03E+00;
  // _xs[ "ZLL-LO-600-800"] = 1.75E+00;
  // _xs[ "ZLL-LO-800-1200"] = 7.96E-01;
  // _xs[ "ZLL-LO-1200-2500"] = 1.93E-01;
  // _xs[ "ZLL-LO-2500-Inf"] = 3.47E-03;

  //ANDREAS
  // _xs[ "ZLL-LO-70-100" ] = 147.0;
  // _xs[ "ZLL-LO-100-200"] = 161.3;
  // _xs[ "ZLL-LO-100-200-ext"] = 160.7;
  // _xs[ "ZLL-LO-200-400"] = 48.61;
  // _xs[ "ZLL-LO-200-400-ext"] = 48.44;
  // _xs[ "ZLL-LO-400-600"] = 7.033;
  // _xs[ "ZLL-LO-400-600-ext"] = 7.033;
  // _xs[ "ZLL-LO-600-800"] = 1.745;
  // _xs[ "ZLL-LO-800-1200"] = 0.8077;
  // _xs[ "ZLL-LO-1200-2500"] = 0.192;
  // _xs[ "ZLL-LO-2500-Inf"] = 0.003477;

  //Update to the same as the note (2017)
  _xs[ "ZLL-LO-70-100" ] = 146.9;
  _xs[ "ZLL-LO-100-200"] = 161.3;
  _xs[ "ZLL-LO-100-200-ext"] = 160.9;
  _xs[ "ZLL-LO-200-400"] = 48.68;
  _xs[ "ZLL-LO-200-400-ext"] = 48.52;
  _xs[ "ZLL-LO-400-600"] = 7.033;
  _xs[ "ZLL-LO-400-600-ext"] = 6.998;
  _xs[ "ZLL-LO-600-800"] = 1.745;
  _xs[ "ZLL-LO-800-1200"] = 0.8077;
  _xs[ "ZLL-LO-1200-2500"] = 0.1923;
  _xs[ "ZLL-LO-2500-Inf"] = 0.003477;

  //NORMAL
  // _stitch[ "ZLL-LO-70-100" ] = 1.0;
  // _stitch[ "ZLL-LO-100-200"] = 1.0;
  // _stitch[ "ZLL-LO-100-200-ext"] = 1.0;
  // _stitch[ "ZLL-LO-200-400"] = 0.999;
  // _stitch[ "ZLL-LO-200-400-ext"] = 0.999;
  // _stitch[ "ZLL-LO-400-600"] = 0.99;
  // _stitch[ "ZLL-LO-400-600-ext"] = 0.99;
  // _stitch[ "ZLL-LO-600-800"] = 0.975;
  // _stitch[ "ZLL-LO-800-1200"] = 0.907;
  // _stitch[ "ZLL-LO-1200-2500"] = 0.833;
  // _stitch[ "ZLL-LO-2500-Inf"] = 1.015;

  //AD HOC
  _stitch[ "ZLL-LO-70-100" ] = 1.0;
  _stitch[ "ZLL-LO-100-200"] = 1.0;
  _stitch[ "ZLL-LO-100-200-ext"] = 1.0;
  _stitch[ "ZLL-LO-200-400"] = 0.999;
  _stitch[ "ZLL-LO-200-400-ext"] = 0.999;
  _stitch[ "ZLL-LO-400-600"] = 0.99;
  _stitch[ "ZLL-LO-400-600-ext"] = 0.99;
  _stitch[ "ZLL-LO-600-800"] = 1.0;
  _stitch[ "ZLL-LO-800-1200"] = 1.0;
  _stitch[ "ZLL-LO-1200-2500"] = 1.03;
  _stitch[ "ZLL-LO-2500-Inf"] = 1.26;


  //If no stitching
  for (auto& stitch:_stitch){
    stitch.second = 1;
  }
  

  _sum["ZLL-LO-100-200-TOT"    ] =  _sum["ZLL-LO-100-200"    ] + _sum["ZLL-LO-100-200-ext"]; 
  _sum["ZLL-LO-200-400-TOT"    ] =  _sum["ZLL-LO-200-400"    ] + _sum["ZLL-LO-200-400-ext"];
  _sum["ZLL-LO-400-600-TOT"    ] =  _sum["ZLL-LO-400-600"    ] + _sum["ZLL-LO-400-600-ext"];
  // _num["ZLL-LO-100-200-TOT"    ] =  _num["ZLL-LO-100-200"    ] + _num["ZLL-LO-100-200-ext"];
  // _num["ZLL-LO-200-400-TOT"    ] =  _num["ZLL-LO-200-400"    ] + _num["ZLL-LO-200-400-ext"];
  // _num["ZLL-LO-400-600-TOT"    ] =  _num["ZLL-LO-400-600"    ] + _num["ZLL-LO-400-600-ext"];

  for (auto const& histset : _cloned_hists["ZLL-LO-70-100"]){
    
    _cloned_hists["ZLL-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-LO_" + histset.first );   
    _cloned_hists["ZLL-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-70-100"     ][histset.first], 1E3* _stitch["ZLL-LO-70-100"     ] * _xs["ZLL-LO-70-100"     ] / _sum["ZLL-LO-70-100"     ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200"    ][histset.first], 1E3* _stitch["ZLL-LO-100-200"    ] * _xs["ZLL-LO-100-200"    ] / _sum["ZLL-LO-100-200-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200-ext"][histset.first], 1E3* _stitch["ZLL-LO-100-200-ext"] * _xs["ZLL-LO-100-200-ext"] / _sum["ZLL-LO-100-200-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400"    ][histset.first], 1E3* _stitch["ZLL-LO-200-400"    ] * _xs["ZLL-LO-200-400"    ] / _sum["ZLL-LO-200-400-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400-ext"][histset.first], 1E3* _stitch["ZLL-LO-200-400-ext"] * _xs["ZLL-LO-200-400-ext"] / _sum["ZLL-LO-200-400-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600"    ][histset.first], 1E3* _stitch["ZLL-LO-400-600"    ] * _xs["ZLL-LO-400-600"    ] / _sum["ZLL-LO-400-600-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600-ext"][histset.first], 1E3* _stitch["ZLL-LO-400-600-ext"] * _xs["ZLL-LO-400-600-ext"] / _sum["ZLL-LO-400-600-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-600-800"    ][histset.first], 1E3* _stitch["ZLL-LO-600-800"    ] * _xs["ZLL-LO-600-800"    ] / _sum["ZLL-LO-600-800"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-800-1200"   ][histset.first], 1E3* _stitch["ZLL-LO-800-1200"   ] * _xs["ZLL-LO-800-1200"   ] / _sum["ZLL-LO-800-1200"   ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZLL-LO-1200-2500"  ] * _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL-LO-1200-2500"  ]); 
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZLL-LO-2500-Inf"   ] * _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL-LO-2500-Inf"   ]);

  }


  //2D

  for (auto const& histset : _cloned_hists2D["ZLL-LO-70-100"]){
    
    _cloned_hists2D["ZLL-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL-LO_" + histset.first );   
    _cloned_hists2D["ZLL-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-70-100"     ][histset.first], 1E3* _stitch["ZLL-LO-70-100"     ] * _xs["ZLL-LO-70-100"     ] / _sum["ZLL-LO-70-100"     ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-100-200"    ][histset.first], 1E3* _stitch["ZLL-LO-100-200"    ] * _xs["ZLL-LO-100-200"    ] / _sum["ZLL-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-100-200-ext"][histset.first], 1E3* _stitch["ZLL-LO-100-200-ext"] * _xs["ZLL-LO-100-200-ext"] / _sum["ZLL-LO-100-200-TOT"]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-200-400"    ][histset.first], 1E3* _stitch["ZLL-LO-200-400"    ] * _xs["ZLL-LO-200-400"    ] / _sum["ZLL-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-200-400-ext"][histset.first], 1E3* _stitch["ZLL-LO-200-400-ext"] * _xs["ZLL-LO-200-400-ext"] / _sum["ZLL-LO-200-400-TOT"]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-400-600"    ][histset.first], 1E3* _stitch["ZLL-LO-400-600"    ] * _xs["ZLL-LO-400-600"    ] / _sum["ZLL-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-400-600-ext"][histset.first], 1E3* _stitch["ZLL-LO-400-600-ext"] * _xs["ZLL-LO-400-600-ext"] / _sum["ZLL-LO-400-600-TOT"]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-600-800"    ][histset.first], 1E3* _stitch["ZLL-LO-600-800"    ] * _xs["ZLL-LO-600-800"    ] / _sum["ZLL-LO-600-800"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-800-1200"   ][histset.first], 1E3* _stitch["ZLL-LO-800-1200"   ] * _xs["ZLL-LO-800-1200"   ] / _sum["ZLL-LO-800-1200"   ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZLL-LO-1200-2500"  ] * _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL-LO-1200-2500"  ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZLL-LO-2500-Inf"   ] * _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL-LO-2500-Inf"   ]);

  }


  ///////  Z NU NU  /////////  

  //ANDREAS
  // _xs[ "ZNN-LO-100-200"] = 306.2;
  // _xs[ "ZNN-LO-200-400"] = 91.38;
  // _xs[ "ZNN-LO-400-600"] = 13.19;
  // _xs[ "ZNN-LO-600-800"] = 3.272;
  // _xs[ "ZNN-LO-800-1200"] = 1.5;
  // _xs[ "ZNN-LO-1200-2500"] = 0.3431;
  // _xs[ "ZNN-LO-2500-Inf"] = 0.005146;

  //Update to the same as the note (2017)
  _xs[ "ZNN-LO-100-200"] = 305.3;
  _xs[ "ZNN-LO-200-400"] = 91.86;
  _xs[ "ZNN-LO-400-600"] = 13.13;
  _xs[ "ZNN-LO-600-800"] = 3.242;
  _xs[ "ZNN-LO-800-1200"] = 1.501;
  _xs[ "ZNN-LO-1200-2500"] = 0.3431;
  _xs[ "ZNN-LO-2500-Inf"] = 0.005146;

  //NORMAL
  // _stitch[ "ZNN-LO-100-200"] = 0.994;
  // _stitch[ "ZNN-LO-200-400"] = 0.981;
  // _stitch[ "ZNN-LO-400-600"] = 0.977;
  // _stitch[ "ZNN-LO-600-800"] = 0.975;
  // _stitch[ "ZNN-LO-800-1200"] = 0.916;
  // _stitch[ "ZNN-LO-1200-2500"] = 0.88;
  // _stitch[ "ZNN-LO-2500-Inf"] = 1.276;

  //AD HOC
  _stitch[ "ZNN-LO-100-200"] = 0.994;
  _stitch[ "ZNN-LO-200-400"] = 1.01;
  _stitch[ "ZNN-LO-400-600"] = 0.995;
  _stitch[ "ZNN-LO-600-800"] = 1.0;
  _stitch[ "ZNN-LO-800-1200"] = 1.01;
  _stitch[ "ZNN-LO-1200-2500"] = 1.07;
  _stitch[ "ZNN-LO-2500-Inf"] = 1.5;

  //If no stitching
  for (auto& stitch:_stitch){
    stitch.second = 1;
  }
  

  for (auto const& histset : _cloned_hists["ZNN-LO-100-200"]){
    
    _cloned_hists["ZNN-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZNN-LO_" + histset.first );   
    _cloned_hists["ZNN-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-100-200"    ][histset.first], 1E3* _stitch["ZNN-LO-100-200"    ] * _xs["ZNN-LO-100-200"    ] / _sum["ZNN-LO-100-200"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-200-400"    ][histset.first], 1E3* _stitch["ZNN-LO-200-400"    ] * _xs["ZNN-LO-200-400"    ] / _sum["ZNN-LO-200-400"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-400-600"    ][histset.first], 1E3* _stitch["ZNN-LO-400-600"    ] * _xs["ZNN-LO-400-600"    ] / _sum["ZNN-LO-400-600"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-600-800"    ][histset.first], 1E3* _stitch["ZNN-LO-600-800"    ] * _xs["ZNN-LO-600-800"    ] / _sum["ZNN-LO-600-800"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-800-1200"   ][histset.first], 1E3* _stitch["ZNN-LO-800-1200"   ] * _xs["ZNN-LO-800-1200"   ] / _sum["ZNN-LO-800-1200"   ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZNN-LO-1200-2500"  ] * _xs["ZNN-LO-1200-2500"  ] / _sum["ZNN-LO-1200-2500"  ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZNN-LO-2500-Inf"   ] * _xs["ZNN-LO-2500-Inf"   ] / _sum["ZNN-LO-2500-Inf"   ]);

  }


  //2D

  for (auto const& histset : _cloned_hists2D["ZNN-LO-100-200"]){
    
    _cloned_hists2D["ZNN-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZNN-LO_" + histset.first );   
    _cloned_hists2D["ZNN-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-100-200"    ][histset.first], 1E3* _stitch["ZNN-LO-100-200"    ] * _xs["ZNN-LO-100-200"    ] / _sum["ZNN-LO-100-200"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-200-400"    ][histset.first], 1E3* _stitch["ZNN-LO-200-400"    ] * _xs["ZNN-LO-200-400"    ] / _sum["ZNN-LO-200-400"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-400-600"    ][histset.first], 1E3* _stitch["ZNN-LO-400-600"    ] * _xs["ZNN-LO-400-600"    ] / _sum["ZNN-LO-400-600"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-600-800"    ][histset.first], 1E3* _stitch["ZNN-LO-600-800"    ] * _xs["ZNN-LO-600-800"    ] / _sum["ZNN-LO-600-800"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-800-1200"   ][histset.first], 1E3* _stitch["ZNN-LO-800-1200"   ] * _xs["ZNN-LO-800-1200"   ] / _sum["ZNN-LO-800-1200"   ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZNN-LO-1200-2500"  ] * _xs["ZNN-LO-1200-2500"  ] / _sum["ZNN-LO-1200-2500"  ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZNN-LO-2500-Inf"   ] * _xs["ZNN-LO-2500-Inf"   ] / _sum["ZNN-LO-2500-Inf"   ]);

  }


  ///////  W  /////////

  //ORIGINAL
  // _xs[ "WLN-LO-70-100" ] = 1.47E+01;
  // _xs[ "WLN-LO-100-200"] = 1.39E+03;
  // _xs[ "WLN-LO-200-400"] = 4.03E+02;
  // _xs[ "WLN-LO-400-600"] = 5.82E+01;
  // _xs[ "WLN-LO-600-800"] = 1.29E+01;
  // _xs[ "WLN-LO-800-1200"] = 5.49E+00;
  // _xs[ "WLN-LO-1200-2500"] = 1.092E+00;
  // _xs[ "WLN-LO-2500-Inf"] = 8.19E-03;

  //ANDREAS
  // _xs[ "WLN-LO-70-100" ] = 1291.0;
  // _xs[ "WLN-LO-100-200"] = 1405.0;
  // _xs[ "WLN-LO-200-400"] = 411.1;
  // _xs[ "WLN-LO-400-600"] = 57.96;
  // _xs[ "WLN-LO-600-800"] = 13.06;
  // _xs[ "WLN-LO-800-1200"] = 5.419;
  // _xs[ "WLN-LO-1200-2500"] = 1.082;
  // _xs[ "WLN-LO-2500-Inf"] = 0.008111;

  //Update to the same as the note (2017)
  _xs[ "WLN-LO-70-100" ] = 1296.0;
  _xs[ "WLN-LO-100-200"] = 1392.0;
  _xs[ "WLN-LO-200-400"] = 410.2;
  _xs[ "WLN-LO-400-600"] = 57.95;
  _xs[ "WLN-LO-600-800"] = 12.98;
  _xs[ "WLN-LO-800-1200"] = 5.39;
  _xs[ "WLN-LO-1200-2500"] = 1.08;
  _xs[ "WLN-LO-2500-Inf"] = 0.008098;

  _stitch[ "WLN-LO-70-100" ] = 1.0;
  _stitch[ "WLN-LO-100-200"] = 0.993;
  _stitch[ "WLN-LO-200-400"] = 1.002;
  _stitch[ "WLN-LO-400-600"] = 1.009;
  _stitch[ "WLN-LO-600-800"] = 1.12;
  _stitch[ "WLN-LO-800-1200"] = 1.202;
  _stitch[ "WLN-LO-1200-2500"] = 1.332;
  _stitch[ "WLN-LO-2500-Inf"] = 4.2;


  //If no stitching

  for (auto& stitch:_stitch){
    stitch.second = 1;
  }

  for (auto const& histset : _cloned_hists["WLN-LO-70-100"]){ 
    
    _cloned_hists["WLN-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-LO_" + histset.first );   
    _cloned_hists["WLN-LO"][ histset.first ] ->Reset();
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-70-100"     ][histset.first],  1E3 * _stitch["WLN-LO-70-100"     ] * _xs["WLN-LO-70-100"     ] / _sum["WLN-LO-70-100"     ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-100-200"    ][histset.first],  1E3 * _stitch["WLN-LO-100-200"    ] * _xs["WLN-LO-100-200"    ] / _sum["WLN-LO-100-200"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-200-400"    ][histset.first],  1E3 * _stitch["WLN-LO-200-400"    ] * _xs["WLN-LO-200-400"    ] / _sum["WLN-LO-200-400"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-400-600"    ][histset.first],  1E3 * _stitch["WLN-LO-400-600"    ] * _xs["WLN-LO-400-600"    ] / _sum["WLN-LO-400-600"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-600-800"    ][histset.first],  1E3 * _stitch["WLN-LO-600-800"    ] * _xs["WLN-LO-600-800"    ] / _sum["WLN-LO-600-800"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-800-1200"   ][histset.first],  1E3 * _stitch["WLN-LO-800-1200"   ] * _xs["WLN-LO-800-1200"   ] / _sum["WLN-LO-800-1200"   ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-1200-2500"  ][histset.first],  1E3 * _stitch["WLN-LO-1200-2500"  ] * _xs["WLN-LO-1200-2500"  ] / _sum["WLN-LO-1200-2500"  ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-2500-Inf"   ][histset.first],  1E3 * _stitch["WLN-LO-2500-Inf"   ] * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN-LO-2500-Inf"   ]);

  }

  //2D

  for (auto const& histset : _cloned_hists2D["WLN-LO-70-100"]){ 
    
    _cloned_hists2D["WLN-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN-LO_" + histset.first );   
    _cloned_hists2D["WLN-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-70-100"     ][histset.first],  1E3 * _stitch["WLN-LO-70-100"     ] * _xs["WLN-LO-70-100"     ] / _sum["WLN-LO-70-100"     ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-100-200"    ][histset.first],  1E3 * _stitch["WLN-LO-100-200"    ] * _xs["WLN-LO-100-200"    ] / _sum["WLN-LO-100-200"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-200-400"    ][histset.first],  1E3 * _stitch["WLN-LO-200-400"    ] * _xs["WLN-LO-200-400"    ] / _sum["WLN-LO-200-400"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-400-600"    ][histset.first],  1E3 * _stitch["WLN-LO-400-600"    ] * _xs["WLN-LO-400-600"    ] / _sum["WLN-LO-400-600"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-600-800"    ][histset.first],  1E3 * _stitch["WLN-LO-600-800"    ] * _xs["WLN-LO-600-800"    ] / _sum["WLN-LO-600-800"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-800-1200"   ][histset.first],  1E3 * _stitch["WLN-LO-800-1200"   ] * _xs["WLN-LO-800-1200"   ] / _sum["WLN-LO-800-1200"   ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-1200-2500"  ][histset.first],  1E3 * _stitch["WLN-LO-1200-2500"  ] * _xs["WLN-LO-1200-2500"  ] / _sum["WLN-LO-1200-2500"  ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-2500-Inf"   ][histset.first],  1E3 * _stitch["WLN-LO-2500-Inf"   ] * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN-LO-2500-Inf"   ]);

  }
  

  // for (auto const& histset : _cloned_hists["WLN-LO-Pt-100-200"]){
    
  //   _cloned_hists["WLN-LO-Pt"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-LO-Pt-100-200_" + histset.first  );   
  //   _cloned_hists["WLN-LO-Pt"][ histset.first ]->Reset();

  //   _cloned_hists["WLN-LO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-LO-Pt-100-200" ][histset.first]  , 1E0 * _xs["WLN-LO-Pt-100-200"     ] / _sum["WLN-LO-Pt-100-200"     ] );
  //   _cloned_hists["WLN-LO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-LO-Pt-200-Inf" ][histset.first]  , 1E0 * _xs["WLN-LO-Pt-200-Inf"     ] / _sum["WLN-LO-Pt-200-Inf"     ] );
   
  // }
  










 ////////////////////////////////////////////////////////

  ////////////////////
  //  LO HT Binned 2016  // 
  ////////////////////


  ///////  Z  /////////  

  //Andreas
  _xs[ "ZLL16-LO-70-100" ] = 170.4;
  _xs[ "ZLL16-LO-100-200"] = 147.7;
  _xs[ "ZLL16-LO-100-200-ext1"] = 149.2;
  _xs[ "ZLL16-LO-200-400"] = 40.98;
  _xs[ "ZLL16-LO-200-400-ext1"] = 40.96;
  _xs[ "ZLL16-LO-400-600"] = 5.675;
  _xs[ "ZLL16-LO-400-600-ext1"] = 5.689;
  _xs[ "ZLL16-LO-600-800"] = 1.357;
  _xs[ "ZLL16-LO-800-1200"] = 0.6243;
  _xs[ "ZLL16-LO-1200-2500"] = 0.1511;
  _xs[ "ZLL16-LO-2500-Inf"] = 0.003659;

  //If no stitching
  for (auto& stitch:_xs){
    _stitch[stitch.first] = 1;
  }

  _sum["ZLL16-LO-100-200-TOT"    ] =  _sum["ZLL16-LO-100-200"    ] + _sum["ZLL16-LO-100-200-ext1"]; 
  _sum["ZLL16-LO-200-400-TOT"    ] =  _sum["ZLL16-LO-200-400"    ] + _sum["ZLL16-LO-200-400-ext1"];
  _sum["ZLL16-LO-400-600-TOT"    ] =  _sum["ZLL16-LO-400-600"    ] + _sum["ZLL16-LO-400-600-ext1"];

  for (auto const& histset : _cloned_hists["ZLL16-LO-70-100"]){
    
    _cloned_hists["ZLL16-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL16-LO_" + histset.first );   
    _cloned_hists["ZLL16-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-70-100"     ][histset.first], 1E3* _stitch["ZLL16-LO-70-100"     ] * _xs["ZLL16-LO-70-100"     ] / _sum["ZLL16-LO-70-100"     ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-100-200"    ][histset.first], 1E3* _stitch["ZLL16-LO-100-200"    ] * _xs["ZLL16-LO-100-200"    ] / _sum["ZLL16-LO-100-200-TOT"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-100-200-ext1"][histset.first], 1E3* _stitch["ZLL16-LO-100-200-ext1"] * _xs["ZLL16-LO-100-200-ext1"] / _sum["ZLL16-LO-100-200-TOT"]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-200-400"    ][histset.first], 1E3* _stitch["ZLL16-LO-200-400"    ] * _xs["ZLL16-LO-200-400"    ] / _sum["ZLL16-LO-200-400-TOT"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-200-400-ext1"][histset.first], 1E3* _stitch["ZLL16-LO-200-400-ext1"] * _xs["ZLL16-LO-200-400-ext1"] / _sum["ZLL16-LO-200-400-TOT"]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-400-600"    ][histset.first], 1E3* _stitch["ZLL16-LO-400-600"    ] * _xs["ZLL16-LO-400-600"    ] / _sum["ZLL16-LO-400-600-TOT"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-400-600-ext1"][histset.first], 1E3* _stitch["ZLL16-LO-400-600-ext1"] * _xs["ZLL16-LO-400-600-ext1"] / _sum["ZLL16-LO-400-600-TOT"]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-600-800"    ][histset.first], 1E3* _stitch["ZLL16-LO-600-800"    ] * _xs["ZLL16-LO-600-800"    ] / _sum["ZLL16-LO-600-800"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-800-1200"   ][histset.first], 1E3* _stitch["ZLL16-LO-800-1200"   ] * _xs["ZLL16-LO-800-1200"   ] / _sum["ZLL16-LO-800-1200"   ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZLL16-LO-1200-2500"  ] * _xs["ZLL16-LO-1200-2500"  ] / _sum["ZLL16-LO-1200-2500"  ]); 
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZLL16-LO-2500-Inf"   ] * _xs["ZLL16-LO-2500-Inf"   ] / _sum["ZLL16-LO-2500-Inf"   ]);

  }

  //2D

  for (auto const& histset : _cloned_hists2D["ZLL16-LO-70-100"]){
    
    _cloned_hists2D["ZLL16-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL16-LO_" + histset.first );   
    _cloned_hists2D["ZLL16-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-70-100"     ][histset.first], 1E3* _stitch["ZLL16-LO-70-100"     ] * _xs["ZLL16-LO-70-100"     ] / _sum["ZLL16-LO-70-100"     ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-100-200"    ][histset.first], 1E3* _stitch["ZLL16-LO-100-200"    ] * _xs["ZLL16-LO-100-200"    ] / _sum["ZLL16-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-100-200-ext1"][histset.first], 1E3* _stitch["ZLL16-LO-100-200-ext1"] * _xs["ZLL16-LO-100-200-ext1"] / _sum["ZLL16-LO-100-200-TOT"]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-200-400"    ][histset.first], 1E3* _stitch["ZLL16-LO-200-400"    ] * _xs["ZLL16-LO-200-400"    ] / _sum["ZLL16-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-200-400-ext1"][histset.first], 1E3* _stitch["ZLL16-LO-200-400-ext1"] * _xs["ZLL16-LO-200-400-ext1"] / _sum["ZLL16-LO-200-400-TOT"]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-400-600"    ][histset.first], 1E3* _stitch["ZLL16-LO-400-600"    ] * _xs["ZLL16-LO-400-600"    ] / _sum["ZLL16-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-400-600-ext1"][histset.first], 1E3* _stitch["ZLL16-LO-400-600-ext1"] * _xs["ZLL16-LO-400-600-ext1"] / _sum["ZLL16-LO-400-600-TOT"]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-600-800"    ][histset.first], 1E3* _stitch["ZLL16-LO-600-800"    ] * _xs["ZLL16-LO-600-800"    ] / _sum["ZLL16-LO-600-800"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-800-1200"   ][histset.first], 1E3* _stitch["ZLL16-LO-800-1200"   ] * _xs["ZLL16-LO-800-1200"   ] / _sum["ZLL16-LO-800-1200"   ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZLL16-LO-1200-2500"  ] * _xs["ZLL16-LO-1200-2500"  ] / _sum["ZLL16-LO-1200-2500"  ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZLL16-LO-2500-Inf"   ] * _xs["ZLL16-LO-2500-Inf"   ] / _sum["ZLL16-LO-2500-Inf"   ]);

  }


  ///////  Z NU NU  /////////  

  //Taken from Esh
  _xs[ "ZNN16-LO-100-200"] = 302.8;
  _xs[ "ZNN16-LO-100-200-ext1"] = 302.8;
  _xs[ "ZNN16-LO-200-400"] = 92.59;
  _xs[ "ZNN16-LO-200-400-ext1"] = 92.59;
  _xs[ "ZNN16-LO-400-600"] = 13.18;
  _xs[ "ZNN16-LO-400-600-ext1"] = 13.18;
  _xs[ "ZNN16-LO-600-800"] = 3.257;
  _xs[ "ZNN16-LO-800-1200"] = 1.49;
  _xs[ "ZNN16-LO-1200-2500"] = 0.3419;
  _xs[ "ZNN16-LO-1200-2500-ext1"] = 0.3419;
  _xs[ "ZNN16-LO-2500-Inf"] = 0.005146;

  _sum["ZNN16-LO-100-200-TOT"    ] =  _sum["ZNN16-LO-100-200"    ] + _sum["ZNN16-LO-100-200-ext1"]; 
  _sum["ZNN16-LO-200-400-TOT"    ] =  _sum["ZNN16-LO-200-400"    ] + _sum["ZNN16-LO-200-400-ext1"];
  _sum["ZNN16-LO-400-600-TOT"    ] =  _sum["ZNN16-LO-400-600"    ] + _sum["ZNN16-LO-400-600-ext1"];
  _sum["ZNN16-LO-1200-2500-TOT"    ] =  _sum["ZNN16-LO-1200-2500"    ] + _sum["ZNN16-LO-1200-2500-ext1"];

  //If no stitching
  for (auto& stitch:_xs){
    _stitch[stitch.first] = 1;
  }

  for (auto const& histset : _cloned_hists["ZNN16-LO-100-200"]){
    
    _cloned_hists["ZNN16-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZNN16-LO_" + histset.first );   
    _cloned_hists["ZNN16-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-100-200"    ][histset.first], 1E3* _stitch["ZNN16-LO-100-200"    ] * _xs["ZNN16-LO-100-200"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-100-200-ext1"    ][histset.first], 1E3* _stitch["ZNN16-LO-100-200-ext1"    ] * _xs["ZNN16-LO-100-200-ext1"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-200-400"    ][histset.first], 1E3* _stitch["ZNN16-LO-200-400"    ] * _xs["ZNN16-LO-200-400"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-200-400-ext1"    ][histset.first], 1E3* _stitch["ZNN16-LO-200-400-ext1"    ] * _xs["ZNN16-LO-200-400-ext1"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-400-600"    ][histset.first], 1E3* _stitch["ZNN16-LO-400-600"    ] * _xs["ZNN16-LO-400-600"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-400-600-ext1"    ][histset.first], 1E3* _stitch["ZNN16-LO-400-600-ext1"    ] * _xs["ZNN16-LO-400-600-ext1"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-600-800"    ][histset.first], 1E3* _stitch["ZNN16-LO-600-800"    ] * _xs["ZNN16-LO-600-800"    ] / _sum["ZNN16-LO-600-800"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-800-1200"   ][histset.first], 1E3* _stitch["ZNN16-LO-800-1200"   ] * _xs["ZNN16-LO-800-1200"   ] / _sum["ZNN16-LO-800-1200"   ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZNN16-LO-1200-2500"  ] * _xs["ZNN16-LO-1200-2500"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-1200-2500-ext1"  ][histset.first], 1E3* _stitch["ZNN16-LO-1200-2500-ext1"  ] * _xs["ZNN16-LO-1200-2500-ext1"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZNN16-LO-2500-Inf"   ] * _xs["ZNN16-LO-2500-Inf"   ] / _sum["ZNN16-LO-2500-Inf"   ]);

  }


  //2D

  for (auto const& histset : _cloned_hists2D["ZNN16-LO-100-200"]){
    
    _cloned_hists2D["ZNN16-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZNN16-LO_" + histset.first );   
    _cloned_hists2D["ZNN16-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-100-200"    ][histset.first], 1E3* _stitch["ZNN16-LO-100-200"    ] * _xs["ZNN16-LO-100-200"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-100-200-ext1"    ][histset.first], 1E3* _stitch["ZNN16-LO-100-200-ext1"    ] * _xs["ZNN16-LO-100-200-ext1"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-200-400"    ][histset.first], 1E3* _stitch["ZNN16-LO-200-400"    ] * _xs["ZNN16-LO-200-400"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-200-400-ext1"    ][histset.first], 1E3* _stitch["ZNN16-LO-200-400-ext1"    ] * _xs["ZNN16-LO-200-400-ext1"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-400-600"    ][histset.first], 1E3* _stitch["ZNN16-LO-400-600"    ] * _xs["ZNN16-LO-400-600"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-400-600-ext1"    ][histset.first], 1E3* _stitch["ZNN16-LO-400-600-ext1"    ] * _xs["ZNN16-LO-400-600-ext1"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-600-800"    ][histset.first], 1E3* _stitch["ZNN16-LO-600-800"    ] * _xs["ZNN16-LO-600-800"    ] / _sum["ZNN16-LO-600-800"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-800-1200"   ][histset.first], 1E3* _stitch["ZNN16-LO-800-1200"   ] * _xs["ZNN16-LO-800-1200"   ] / _sum["ZNN16-LO-800-1200"   ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-1200-2500"  ][histset.first], 1E3* _stitch["ZNN16-LO-1200-2500"  ] * _xs["ZNN16-LO-1200-2500"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-1200-2500-ext1"  ][histset.first], 1E3* _stitch["ZNN16-LO-1200-2500-ext1"  ] * _xs["ZNN16-LO-1200-2500-ext1"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-2500-Inf"   ][histset.first], 1E3* _stitch["ZNN16-LO-2500-Inf"   ] * _xs["ZNN16-LO-2500-Inf"   ] / _sum["ZNN16-LO-2500-Inf"   ]);

  }


  ///////  W  /////////

  //ANDREAS
  _xs[ "WLN16-LO-70-100" ] = 1353.0;
  _xs[ "WLN16-LO-100-200"] = 1348.0;
  _xs[ "WLN16-LO-100-200-ext1"] = 1348.0;
  _xs[ "WLN16-LO-100-200-ext2"] = 1340.0;
  _xs[ "WLN16-LO-200-400"] = 359.6;
  _xs[ "WLN16-LO-200-400-ext1"] = 359.7;
  _xs[ "WLN16-LO-200-400-ext2"] = 358.8;
  _xs[ "WLN16-LO-400-600"] = 48.85;
  _xs[ "WLN16-LO-400-600-ext1"] = 48.74;
  _xs[ "WLN16-LO-600-800"] = 48.74;
  _xs[ "WLN16-LO-600-800-ext1"] = 12.04;
  _xs[ "WLN16-LO-800-1200"] = 5.47;
  _xs[ "WLN16-LO-800-1200-ext1"] = 5.499;
  _xs[ "WLN16-LO-1200-2500"] = 1.329;
  _xs[ "WLN16-LO-1200-2500-ext1"] = 1.324;
  _xs[ "WLN16-LO-2500-Inf"] = 0.03219;
  _xs[ "WLN16-LO-2500-Inf-ext1"] = 0.03212;

  //If no stitching
  for (auto& stitch:_xs){
    _stitch[stitch.first] = 1;
  }


  _sum["WLN16-LO-100-200-TOT"    ] =  _sum["WLN16-LO-100-200"    ] + _sum["WLN16-LO-100-200-ext1"] + _sum["WLN16-LO-100-200-ext2"];
  _sum["WLN16-LO-200-400-TOT"    ] =  _sum["WLN16-LO-200-400"    ] + _sum["WLN16-LO-200-400-ext1"] + _sum["WLN16-LO-200-400-ext2"];
  _sum["WLN16-LO-400-600-TOT"    ] =  _sum["WLN16-LO-400-600"    ] + _sum["WLN16-LO-400-600-ext1"];
  _sum["WLN16-LO-600-800-TOT"    ] =  _sum["WLN16-LO-600-800"    ] + _sum["WLN16-LO-600-800-ext1"];
  _sum["WLN16-LO-800-1200-TOT"    ] =  _sum["WLN16-LO-800-1200"    ] + _sum["WLN16-LO-800-1200-ext1"];
  _sum["WLN16-LO-1200-2500-TOT"    ] =  _sum["WLN16-LO-1200-2500"    ] + _sum["WLN16-LO-1200-2500-ext1"];
  _sum["WLN16-LO-2500-Inf-TOT"    ] =  _sum["WLN16-LO-2500-Inf"    ] + _sum["WLN16-LO-2500-Inf-ext1"];


  for (auto const& histset : _cloned_hists["WLN16-LO-70-100"]){ 
    
    _cloned_hists["WLN16-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN16-LO_" + histset.first );   
    _cloned_hists["WLN16-LO"][ histset.first ] ->Reset();
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-70-100"     ][histset.first],  1E3 * _stitch["WLN16-LO-70-100"     ] * _xs["WLN16-LO-70-100"     ] / _sum["WLN16-LO-70-100"     ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-100-200"    ][histset.first],  1E3 * _stitch["WLN16-LO-100-200"    ] * _xs["WLN16-LO-100-200"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-100-200-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-100-200-ext1"    ] * _xs["WLN16-LO-100-200-ext1"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-100-200-ext2"    ][histset.first],  1E3 * _stitch["WLN16-LO-100-200-ext2"    ] * _xs["WLN16-LO-100-200-ext2"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-200-400"    ][histset.first],  1E3 * _stitch["WLN16-LO-200-400"    ] * _xs["WLN16-LO-200-400"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-200-400-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-200-400-ext1"    ] * _xs["WLN16-LO-200-400-ext1"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-200-400-ext2"    ][histset.first],  1E3 * _stitch["WLN16-LO-200-400-ext2"    ] * _xs["WLN16-LO-200-400-ext2"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-400-600"    ][histset.first],  1E3 * _stitch["WLN16-LO-400-600"    ] * _xs["WLN16-LO-400-600"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-400-600-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-400-600-ext1"    ] * _xs["WLN16-LO-400-600-ext1"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-600-800"    ][histset.first],  1E3 * _stitch["WLN16-LO-600-800"    ] * _xs["WLN16-LO-600-800"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-600-800-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-600-800-ext1"    ] * _xs["WLN16-LO-600-800-ext1"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-800-1200"   ][histset.first],  1E3 * _stitch["WLN16-LO-800-1200"   ] * _xs["WLN16-LO-800-1200"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-800-1200-ext1"   ][histset.first],  1E3 * _stitch["WLN16-LO-800-1200-ext1"   ] * _xs["WLN16-LO-800-1200-ext1"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-1200-2500"  ][histset.first],  1E3 * _stitch["WLN16-LO-1200-2500"  ] * _xs["WLN16-LO-1200-2500"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-1200-2500-ext1"  ][histset.first],  1E3 * _stitch["WLN16-LO-1200-2500-ext1"  ] * _xs["WLN16-LO-1200-2500-ext1"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-2500-Inf"   ][histset.first],  1E3 * _stitch["WLN16-LO-2500-Inf"   ] * _xs["WLN16-LO-2500-Inf"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-2500-Inf-ext1"   ][histset.first],  1E3 * _stitch["WLN16-LO-2500-Inf-ext1"   ] * _xs["WLN16-LO-2500-Inf-ext1"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);

  }

  //2D

  for (auto const& histset : _cloned_hists2D["WLN16-LO-70-100"]){ 
    
    _cloned_hists2D["WLN16-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN16-LO_" + histset.first );   
    _cloned_hists2D["WLN16-LO"][ histset.first ] ->Reset();


    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-70-100"     ][histset.first],  1E3 * _stitch["WLN16-LO-70-100"     ] * _xs["WLN16-LO-70-100"     ] / _sum["WLN16-LO-70-100"     ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-100-200"    ][histset.first],  1E3 * _stitch["WLN16-LO-100-200"    ] * _xs["WLN16-LO-100-200"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-100-200-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-100-200-ext1"    ] * _xs["WLN16-LO-100-200-ext1"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-100-200-ext2"    ][histset.first],  1E3 * _stitch["WLN16-LO-100-200-ext2"    ] * _xs["WLN16-LO-100-200-ext2"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-200-400"    ][histset.first],  1E3 * _stitch["WLN16-LO-200-400"    ] * _xs["WLN16-LO-200-400"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-200-400-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-200-400-ext1"    ] * _xs["WLN16-LO-200-400-ext1"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-200-400-ext2"    ][histset.first],  1E3 * _stitch["WLN16-LO-200-400-ext2"    ] * _xs["WLN16-LO-200-400-ext2"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-400-600"    ][histset.first],  1E3 * _stitch["WLN16-LO-400-600"    ] * _xs["WLN16-LO-400-600"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-400-600-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-400-600-ext1"    ] * _xs["WLN16-LO-400-600-ext1"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-600-800"    ][histset.first],  1E3 * _stitch["WLN16-LO-600-800"    ] * _xs["WLN16-LO-600-800"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-600-800-ext1"    ][histset.first],  1E3 * _stitch["WLN16-LO-600-800-ext1"    ] * _xs["WLN16-LO-600-800-ext1"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-800-1200"   ][histset.first],  1E3 * _stitch["WLN16-LO-800-1200"   ] * _xs["WLN16-LO-800-1200"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-800-1200-ext1"   ][histset.first],  1E3 * _stitch["WLN16-LO-800-1200-ext1"   ] * _xs["WLN16-LO-800-1200-ext1"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-1200-2500"  ][histset.first],  1E3 * _stitch["WLN16-LO-1200-2500"  ] * _xs["WLN16-LO-1200-2500"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-1200-2500-ext1"  ][histset.first],  1E3 * _stitch["WLN16-LO-1200-2500-ext1"  ] * _xs["WLN16-LO-1200-2500-ext1"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-2500-Inf"   ][histset.first],  1E3 * _stitch["WLN16-LO-2500-Inf"   ] * _xs["WLN16-LO-2500-Inf"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-2500-Inf-ext1"   ][histset.first],  1E3 * _stitch["WLN16-LO-2500-Inf-ext1"   ] * _xs["WLN16-LO-2500-Inf-ext1"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);

  }
  

}



void HiggsPlotting::EvaluateUncertainties(){

  std::vector<TString> sets = {"Pt","LHEPt"};
  //   std::vector<TString> sets = {"LHEPt"};
  for ( auto setname : sets  ){
    
    
    std::vector<TString> histoSets = { "Default" , "Default_VTR", "MJJ-200-500",  "MJJ-500-1000",  "MJJ-1000-1500", "MJJ-1500-5000", "non-VBF"};
    //    std::vector<TString> histoSets = { "Default"};
    for ( auto histoset : histoSets ){
      std::vector<std::string> systplots = {"gen_boson_pt", "gen_jetpt0"};
      for ( auto syst : systplots ){
      	if ( syst == "gen_jetpt0" && histoset != "non-VBF") continue;

	for ( int i = 0;i<9;i++){
	  
	  if ( i ==4 ) continue;
	  //    _cloned_hists["WLN-NLO-Pt"][ histoset + "_gen_boson_pt_Scale_" + std::to_string(i) ] ->Divide(_cloned_hists["WLN-NLO-Pt"][ histoset + "_gen_boson_pt_Scale_4" ]);
	  //    _cloned_hists["ZLL-NLO-Pt"][ histoset + "_gen_boson_pt_Scale_" + std::to_string(i) ] ->Divide(_cloned_hists["ZLL-NLO-Pt"][ histoset + "_gen_boson_pt_Scale_4" ]);
	  // _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_gen_boson_pt_Scale_" + std::to_string(i) ] ->Divide(_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_gen_boson_pt_Scale_4" ]);
	  // _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_gen_boson_pt_Scale_" + std::to_string(i) ] ->Divide(_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_gen_boson_pt_Scale_4" ]);
	}  
	
	std::vector<TString> list = {"1","3","5","7"};
	if ( setname == "LHEPt" )
	  list = {"1","3","4","6"};
	if ( setname == "Pt" )
	  list = {"1","3","5","7"};
	
	for ( auto &j : list ) {
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleUncorrelated_" + setname + j);
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleCorrelated_" + setname + j);
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleZup_" + setname + j);
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleWup_" + setname + j);
	  
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Reset();
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Reset();
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->Reset();
	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->Reset();
	  
	  TString nominal = "";
	  if ( histoset == "Pt" ) nominal = "_Scale_4";
	  for ( int i = 1;i<_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetNbinsX()+1;i++){      
	    
	    double r = 1;
	    if ( _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->GetBinContent(i) != 0 ){
	      
	      double wu = _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i);
	      double zu = _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i);
	      double wnom = _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetBinContent(i);
	      double znom = _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetBinContent(i);	    
	      
	      r = wnom / znom;
	      double r_zup = (wnom/2) / zu;
	      double r_wup = wu / (znom/2);
	      
	      double val_uncorrelated = 1;
	      double val_correlated = 1;
	      double val_zup = 1;
	      double val_wup = 1;
	      if ( j == "1" || j == "3" ){
		val_uncorrelated = 1 - ( std::sqrt( std::pow(r_wup-r,2) + std::pow(r_zup-r,2) ) ) / r; 
		val_correlated = ((wu/zu) / r);
		val_zup = ((wnom/(zu*2)) / r);
		val_wup = (((2*wu)/znom) / r);
	      }
	      else{
		val_uncorrelated = 1 + ( std::sqrt( std::pow(r_wup-r,2) + std::pow(r_zup-r,2) ) ) / r;
		val_correlated = ((wu/zu) / r);
		val_zup = ((wnom/(zu*2)) / r);
		val_wup = (((2*wu)/znom) / r);
	      }
	      
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, val_uncorrelated );
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, val_correlated );
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, val_zup );
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, val_wup );
	      
	    }
	    else{
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, 1 );
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, 1 );
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, 1 );
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, 1 );
	    }
	    
	    
	  }
	  
	}
      	
	//PDF uncertainty
	_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH1D*)_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_WLN");
	_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH1D*)_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_ZLL");
	_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH1D*)_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_WZ");
	_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
	_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
	_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
	
	if ( setname == "Pt" ){                 
	  
	  _cloned_hists["Zero"][ "Zero" ] = (TH1D*)_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->Clone( "Zero");
	  
	  
	  for ( int i = 1;i<_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    
	    _cloned_hists["Zero"][ "Zero" ]->SetBinContent(i,0);
	    _cloned_hists["Zero"][ "Zero" ]->SetBinError(i,0);
	
	    double sum = 0;
	    double sum2 = 0;
	    for ( int j = 0; j < 100; j++){
	      sum += _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i);
	      sum2 += std::pow(_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i),2);
	    }
	    double sd_pdf = std::sqrt( (sum2/100) - (sum/100)*(sum/100) );
	    
	    double sd_alphas = (_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i) - _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i))/2;
	    double sd =  std::sqrt( sd_pdf*sd_pdf + sd_alphas*sd_alphas );
	    //double sd =  std::sqrt( sd_pdf*sd_pdf  );
	  
	    if ( _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	      _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	  }
	  
	  for ( int i = 1;i<_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    
	    double sum = 0;
	    double sum2 = 0;
	    for ( int j = 0; j < 100; j++){
	      sum += _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i);
	      sum2 += std::pow(_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i),2);
	    }
	    
	    double sd_pdf = std::sqrt( (sum2/100) - (sum/100)*(sum/100) );
	    double sd_alphas = (_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i) - _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i))/2;
	    double sd =  std::sqrt( sd_pdf*sd_pdf + sd_alphas*sd_alphas );
	    
	    if ( _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	      _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	  }
	  
	  for ( int i = 1;i<_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    
	    double sum = 0;
	    double sum2 = 0;
	    for ( int j = 0; j < 100; j++){
	      sum += _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) / _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i);
	      sum2 += std::pow(_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i),2);
	    }
	    
	    double sd_pdf = std::sqrt( (sum2/100) - (sum/100)*(sum/100) );
	    double sd_alphas = (_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i) - _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i))/2;
	    double sd =  std::sqrt( sd_pdf*sd_pdf + sd_alphas*sd_alphas );
	    
	    
	    if ( _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	      //	  _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd/(_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i)));
	      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	//	_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinError(i,0);
	  }
	  
	}else if ( setname == "LHEPt" ){                 
	  
	  for ( int i = 1;i<_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    double sum2_pdf = 0;
	    for ( int j = 1; j < 31; j++){	    
	      sum2_pdf += std::pow( 2*_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) - 2*_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i), 2);
	    }
	    double sd_alphas = 2*(_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i) - _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i))/2;
	    
	    double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	    
	    // double sd =  std::sqrt( sum2_pdf  );
	    
	    //	  double sd =  std::sqrt( sum2_pdf );
	    if ( _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	      _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	    
	}
	  
	  for ( int i = 1;i<_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    double sum2_pdf = 0;
	    for ( int j = 1; j < 31; j++){
	      sum2_pdf += std::pow( 2*_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) - 2*_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i), 2);
	    }
	    double sd_alphas = 2*(_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i) - _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i))/2;
	    double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	    //	    	  double sd =  std::sqrt( sum2_pdf);
	    if ( _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	      _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	    
	  }
	  
	  for ( int i = 1;i<_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    double sum2_pdf = 0;
	    for ( int j = 1; j < 31; j++){
	      sum2_pdf += std::pow( _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) - _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i), 2);
	  }
	    double sd_alphas = (_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i) - _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i))/2;
	  double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	  if ( _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	    _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	  }
	  
	  
	}

      
	_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up_WZ"));
      _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down_WZ"));


      _cloned_hists["WLN-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WLN16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists["ZLL-LO"][ histoset + "_" + syst ]);
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists["ZLL-LO"][ histoset + "_" + syst ]);
      
    
      for ( int i = 1;i<_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetNbinsX()+1;i++){
	
	double centralw = _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i);
	double centralz = _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i);
	double centralwz = _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i);
	
	_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i, centralw + _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i, centralw - _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i, centralz + _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i, centralz - _cloned_hists["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i, centralwz + _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i, centralwz - _cloned_hists["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	
      }
    }
  }
  
  }


 
}






void HiggsPlotting::EvaluateUncertainties2D(){

  //  std::vector<TString> sets = {"Pt","LHEPt"};
  std::vector<TString> sets = {"LHEPt"};
  for ( auto setname : sets  ){
    
    std::vector<TString> histoSets = { "Default" , "Default_VTR","non-VBF"};
    //std::vector<TString> histoSets = { "Default"};
    for ( auto histoset : histoSets ){
      std::vector<std::string> systplots = {"gen_boson_pt_gen_mjj"};
      if ( histoset == "non-VBF" ) systplots = {"gen_boson_pt_gen_jetpt0", "gen_boson_pt_gen_jet_multiplicity"};
      for ( auto syst : systplots ){

	for ( int i = 0;i<9;i++){
	  if ( i ==4 ) continue;
	}  
	
	std::vector<TString> list = {"1","3","5","7"};
	if ( setname == "LHEPt" )
	  list = {"1","3","4","6"};
	if ( setname == "Pt" )
	  list = {"1","3","5","7"};
	
	for ( auto &j : list ) {
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleUncorrelated_" + setname + j);
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleCorrelated_" + setname + j);
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleZup_" + setname + j);
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleWup_" + setname + j);

	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleFlavourSeparated_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleFlavourSeparated_" + setname + j);

	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleLightCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleLightCorrelated_" + setname + j);
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedW_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleHeavyUncorrelatedW_" + setname + j);
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedZ_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleHeavyUncorrelatedZ_" + setname + j);

	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst ]->Clone("WZ-ScaleUncorrelated_" + setname + j);
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst  ]->Clone("WZ-ScaleCorrelated_" + setname + j);
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst  ]->Clone("WZ-ScaleZup_" + setname + j);
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst ]->Clone("WZ-ScaleWup_" + setname + j);


	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst ]->Clone("WZ16-ScaleUncorrelated_" + setname + j);
	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst  ]->Clone("WZ16-ScaleCorrelated_" + setname + j);
	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst  ]->Clone("WZ16-ScaleZup_" + setname + j);
	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst ]->Clone("WZ16-ScaleWup_" + setname + j);


	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Reset();
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Reset();
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->Reset();
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->Reset();
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleFlavourSeparated_" + j ]->Reset();
	  
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleLightCorrelated_" + j ]->Reset();
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedW_" + j ]->Reset();
	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedZ_" + j ]->Reset();
	  
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
	  _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);

	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	  _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	  
	  TString nominal = "";
	  TString nominal_heavy = "_HeavyQuark";
	  TString nominal_light = "_NoHeavyQuark";
	  if ( histoset == "Pt" ) nominal = "_Scale_4";
	  for ( int i = 1;i<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetNbinsX()+1;i++){      
	    for ( int k = 1;k<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetNbinsY()+1;k++){      
	      
	      double r = 1;
	      if ( _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_Scale_4" ]->GetBinContent(i,k) != 0 ){
	      
		double wu = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i,k);
		double zu = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i,k);
		double wnom = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetBinContent(i,k);
		double znom = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + nominal ]->GetBinContent(i,k);	    

		// double wu_heavy = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_HeavyQuark_" + j ]->GetBinContent(i,k);
		// double zu_heavy = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_Scale_HeavyQuark_" + j ]->GetBinContent(i,k);
		// double wnom_heavy = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + nominal_heavy ]->GetBinContent(i,k);
		// double znom_heavy = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + nominal_heavy ]->GetBinContent(i,k);	    
		
		// double wu_light = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_Scale_NoHeavyQuark_" + j ]->GetBinContent(i,k);
		// double zu_light = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_Scale_NoHeavyQuark_" + j ]->GetBinContent(i,k);
		// double wnom_light = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + nominal_light ]->GetBinContent(i,k);
		// double znom_light = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + nominal_light ]->GetBinContent(i,k);	    
		
		r = wnom / znom;
		double r_zup = (wnom/2) / zu;
		double r_wup = wu / (znom/2);
		
		double val_uncorrelated = 1;
		double val_correlated = 1;
		double val_zup = 1;
		double val_wup = 1;
		// double val_light_correlated = 1;
		// double val_heavy_uncorrelated = 1;

		// double val_heavy_uncorrelated_w = 1;
		// double val_heavy_uncorrelated_z = 1;

		// double val_flavour_separated = 1;

		// double r_light = wnom_light / znom_light;
		// double r_heavy = wnom_heavy / znom_heavy;
		// double r_heavy_zup = (wnom_heavy/2) / zu_heavy;
		// double r_heavy_wup = wu_heavy / (znom_heavy/2);

		if ( j == "1" || j == "3" ){
		  val_uncorrelated = 1 - ( std::sqrt( std::pow(r_wup-r,2) + std::pow(r_zup-r,2) ) ) / r; 
		  val_correlated = ((wu/zu) / r);
		  val_zup = ((wnom/(zu*2)) / r);
		  val_wup = (((2*wu)/znom) / r);

		  // // val_light_correlated = ((wu_light/zu_light) / r_light) - 1;
		  // // val_heavy_uncorrelated = ( std::sqrt( std::pow(r_heavy_wup-r_heavy,2) + std::pow(r_heavy_zup-r_heavy,2) ) ) / r_heavy; 
		  // // val_flavour_separated = 1 + std::sqrt(val_light_correlated*val_light_correlated + val_heavy_uncorrelated*val_heavy_uncorrelated);
		  // val_light_correlated = ((wu_light+wnom_heavy/2)/(zu_light+znom_heavy/2)) / r ;
		  // val_heavy_uncorrelated_w = ((wnom_light/2+wu_heavy)/(znom_light/2+znom_heavy/2)) / r ;
		  // val_heavy_uncorrelated_z = ((wnom_light/2+wnom_heavy/2)/(znom_light/2+zu_heavy)) / r ;

		}
		else{
		  val_uncorrelated = 1 + ( std::sqrt( std::pow(r_wup-r,2) + std::pow(r_zup-r,2) ) ) / r;
		  val_correlated = ((wu/zu) / r);
		  val_zup = ((wnom/(zu*2)) / r);
		  val_wup = (((2*wu)/znom) / r);

		  // // val_light_correlated = ((wu_light/zu_light) / r_light) - 1;
		  // // val_heavy_uncorrelated = ( std::sqrt( std::pow(r_heavy_wup-r_heavy,2) + std::pow(r_heavy_zup-r_heavy,2) ) ) / r_heavy; 
		  // // val_flavour_separated = 1 - std::sqrt(val_light_correlated*val_light_correlated + val_heavy_uncorrelated*val_heavy_uncorrelated);

		  // val_light_correlated = ((wu_light+wnom_heavy/2)/(zu_light+znom_heavy/2)) / r ;
		  // val_heavy_uncorrelated_w = ((wnom_light/2+wu_heavy)/(znom_light/2+znom_heavy/2)) / r ;
		  // val_heavy_uncorrelated_z = ((wnom_light/2+wnom_heavy/2)/(znom_light/2+zu_heavy)) / r ;

		}
		
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, k, val_uncorrelated );
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, k, val_correlated );
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, k, val_zup );
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, k, val_wup );

		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, k, val_uncorrelated );
		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, k, val_correlated );
		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, k, val_zup );
		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, k, val_wup );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleFlavourSeparated_" + j ]->SetBinContent(i, k, val_flavour_separated );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleLightCorrelated_" + j ]->SetBinContent(i, k, val_light_correlated );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedW_" + j ]->SetBinContent(i, k, val_heavy_uncorrelated_w );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedZ_" + j ]->SetBinContent(i, k, val_heavy_uncorrelated_z );
		
	      }
	      else{
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, k, 1 );
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, k, 1 );
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, k, 1 );
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, k, 1 );

		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ16-NLO-" + setname][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleFlavourSeparated_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleLightCorrelated_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedW_" + j ]->SetBinContent(i, k, 1 );
		// _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_ScaleHeavyUncorrelatedZ_" + j ]->SetBinContent(i, k, 1 );

	      }
	      
	    }
	  }
	}

	//PDF uncertainty
	_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_WLN");
	_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_ZLL");
	_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_ZNN");
	_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_"+setname+"_PDF_SD_WZ");

	_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
	_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
	_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
	_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Reset();

	if ( setname == "Pt" ){                 
	  
	  _cloned_hists2D["Zero"][ "Zero" ] = (TH2D*)_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->Clone( "Zero");
	  
	  
	  for ( int i = 1;i<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	    
	      _cloned_hists2D["Zero"][ "Zero" ]->SetBinContent(i,k,0);
	      _cloned_hists2D["Zero"][ "Zero" ]->SetBinError(i,k,0);
	
	      double sum = 0;
	      double sum2 = 0;
	      for ( int j = 0; j < 100; j++){
		sum += _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k);
		sum2 += std::pow(_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k),2);
	      }
	      double sd_pdf = std::sqrt( (sum2/100) - (sum/100)*(sum/100) );
	    
	      double sd_alphas = (_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i,k))/2;
	      double sd =  std::sqrt( sd_pdf*sd_pdf + sd_alphas*sd_alphas );
	  
	      if ( _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
		_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    }
	  }
	  for ( int i = 1;i<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	      double sum = 0;
	      double sum2 = 0;
	      for ( int j = 0; j < 100; j++){
		sum += _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k);
		sum2 += std::pow(_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k),2);
	      }
	    
	      double sd_pdf = std::sqrt( (sum2/100) - (sum/100)*(sum/100) );
	      double sd_alphas = (_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i,k) - _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i,k))/2;
	      double sd =  std::sqrt( sd_pdf*sd_pdf + sd_alphas*sd_alphas );
	      
	      if ( _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
		_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    }
	  }
	  for ( int i = 1;i<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	    
	      double sum = 0;
	      double sum2 = 0;
	      for ( int j = 0; j < 100; j++){
		sum += _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) / _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k);
		sum2 += std::pow(_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k),2);
	    }
	    
	    double sd_pdf = std::sqrt( (sum2/100) - (sum/100)*(sum/100) );
	    double sd_alphas = (_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_101" ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_100" ]->GetBinContent(i,k))/2;
	    double sd =  std::sqrt( sd_pdf*sd_pdf + sd_alphas*sd_alphas );
	    
	    
	    if ( _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	      //	  _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd/(_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i)));
	      _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    //	_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinError(i,0);
	    }
	  }
	}else if ( setname == "LHEPt" ){                 
	  
	  for ( int i = 1;i<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	      double sum2_pdf = 0;
	      for ( int j = 1; j < 31; j++){	    
		sum2_pdf += std::pow( 2*_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - 2*_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	      }
	      double sd_alphas = 2*(_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	    
	      double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	      
	      if ( _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
		_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    }
	  }

	  for ( int i = 1;i<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	      double sum2_pdf = 0;
	      for ( int j = 1; j < 31; j++){
		sum2_pdf += std::pow( 2*_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - 2*_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	      }
	      double sd_alphas = 2*(_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	      double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	      if ( _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
		_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    } 
	  }
	  for ( int i = 1;i<_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	      double sum2_pdf = 0;
	      for ( int j = 1; j < 31; j++){
		sum2_pdf += std::pow( 2*_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - 2*_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	      }
	      double sd_alphas = 2*(_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	      double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	      if ( _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
		_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    } 
	  }
	  
	  for ( int i = 1;i<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	    for ( int k = 1;k<_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	      double sum2_pdf = 0;
	      for ( int j = 1; j < 31; j++){
		sum2_pdf += std::pow( _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	      }
	      double sd_alphas = (_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	      double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	      if ( _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
		_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	    }
	  }

	}

	_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up_WZ"));
	_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down_WZ"));
	
	
	_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["ZNN-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZNN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["ZNN-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZNN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));

	_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));
	_cloned_hists2D["ZNN16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZNN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["ZNN16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZNN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));

	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));

      _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
      _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);

	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));

      _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
      _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	
	for ( int i = 1;i<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetNbinsX()+1;i++){
	  for ( int k = 1;k<_cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetNbinsY()+1;k++){
	    
	    double centralw = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	    double centralz = _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	    double centralznn = _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	    double centralwz = _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	    
	    _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralw + _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralw - _cloned_hists2D["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralz + _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralz - _cloned_hists2D["ZLL-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralznn + _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralznn - _cloned_hists2D["ZNN-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralwz + _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralwz - _cloned_hists2D["WZ-NLO-" + setname][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    
	  }
	}
      }
    }
  }
   
}









void HiggsPlotting::PlotAllHistograms(){

  Plotter plotter(_cmd, _helper);

  std::string filename = "Znn_studies.root";

  for (auto const& histset : _cloned_hists["ZLL-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first, true );

    plotter.SaveToFile(histset.second ,histset.first, filename, "ZLL-LO" );
  }

  for (auto const& histset : _cloned_hists["ZNN-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZNN-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZNN-LO-" + histset.first, true );

    plotter.SaveToFile(histset.second ,histset.first, filename, "ZNN-LO" );
  }

  for (auto const& histset : _cloned_hists["ZLL16-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZLL16-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL16-LO-" + histset.first, true );
  }

  for (auto const& histset : _cloned_hists["ZNN16-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZNN16-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZNN16-LO-" + histset.first, true );
  }

  plotter.SaveToFile(_cloned_hists["ZNN-LO-100-200"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-100-200" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-200-400"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-200-400" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-400-600"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-400-600" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-600-800"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-600-800" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-800-1200"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-800-1200" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-1200-2500"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-1200-2500" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-2500-Inf"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZNN-LO-2500-Inf" );

  plotter.SaveToFile(_cloned_hists["ZLL-LO-100-200"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-100-200" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-200-400"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-200-400" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-400-600"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-400-600" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-600-800"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-600-800" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-800-1200"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-800-1200" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-1200-2500"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-1200-2500" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-2500-Inf"]["All_LHE_HT"] ,"All_LHE_HT", filename, "ZLL-LO-2500-Inf" );

  plotter.SaveToFile(_cloned_hists["ZNN-LO-100-200"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-100-200" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-200-400"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-200-400" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-400-600"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-400-600" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-600-800"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-600-800" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-800-1200"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-800-1200" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-1200-2500"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-1200-2500" );
  plotter.SaveToFile(_cloned_hists["ZNN-LO-2500-Inf"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZNN-LO-2500-Inf" );

  plotter.SaveToFile(_cloned_hists["ZLL-LO-100-200"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-100-200" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-200-400"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-200-400" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-400-600"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-400-600" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-600-800"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-600-800" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-800-1200"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-800-1200" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-1200-2500"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-1200-2500" );
  plotter.SaveToFile(_cloned_hists["ZLL-LO-2500-Inf"]["All_gen_boson_pt"] ,"All_gen_boson_pt", filename, "ZLL-LO-2500-Inf" );

  for (auto const& histset : _cloned_hists["ZLL-NLO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-NLO-" + histset.first );

    plotter.SaveToFile(histset.second , histset.first, filename, "ZLL-NLO" );
  }

  for (auto const& histset : _cloned_hists["ZLL-NLO"]){
    if ( histset.first == "Default_gen_boson_pt" || histset.first == "Default_gen_mjj" ){
      plotter.DrawRatio( histset.second , _cloned_hists["ZLL-LO"][ histset.first ], "", "Ratio-ZLL-" + histset.first );
    }
  }  
    
  for (auto const& histset : _cloned_hists["WLN-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "WLN-LO-" + histset.first );
    plotter.Draw( histset.second , "", "WLN-LO-" + histset.first, true );
  }
  for (auto const& histset : _cloned_hists["WLN16-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "WLN16-LO-" + histset.first );
    plotter.Draw( histset.second , "", "WLN16-LO-" + histset.first, true );
  }
  for (auto const& histset : _cloned_hists["WLN-NLO"]){
    if ( histset.first.SubString("Scale_") != "" ) continue;
    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "WLN-NLO-" + histset.first );
  }
  for (auto const& histset : _cloned_hists["WLN-NLO-Pt"]){
    if ( histset.first.SubString("PDF_")!= "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "WLN-NLO-Pt-" + histset.first );
    plotter.Draw( histset.second , "", "WLN-NLO-Pt-" + histset.first,true );
  }
  for (auto const& histset : _cloned_hists["ZLL-NLO-Pt"]){

    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-NLO-Pt-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-NLO-Pt-" + histset.first,true );
  }
  
  for (auto const& histset : _cloned_hists["WLN-NLO-LHEPt"]){
    //    if ( histset.first.SubString("Scale_") != "" ) continue;
    if ( histset.first.SubString("PDF_")!= "" ) continue;

    plotter.Draw( histset.second , "", "WLN-NLO-LHEPt-" + histset.first );
    plotter.Draw( histset.second , "", "WLN-NLO-LHEPt-" + histset.first,true );
  }
  for (auto const& histset : _cloned_hists["ZLL-NLO-LHEPt"]){

    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-NLO-LHEPt-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-NLO-LHEPt-" + histset.first,true );
    plotter.SaveToFile(histset.second , histset.first, filename, "ZLL-NLO-LHEPt" );
  }
  for (auto const& histset : _cloned_hists["ZNN-NLO-LHEPt"]){

    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "ZNN-NLO-LHEPt-" + histset.first );
    plotter.Draw( histset.second , "", "ZNN-NLO-LHEPt-" + histset.first,true );
    plotter.SaveToFile(histset.second , histset.first, filename, "ZNN-NLO-LHEPt" );
  }

  for (auto const& histset : _cloned_hists["WLN-NLO"]){
    if ( histset.first == "Default_gen_boson_pt" || histset.first == "Default_gen_mjj"){
      plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "Ratio-WLN-" + histset.first );
    }
  }


  //// LHE PT k-factors
  std::vector<TString> sets = {"LHEPt","Pt"};
  //    std::vector<TString> sets = {"LHEPt"};
  std::vector<TString> processes = {"WLN","ZLL","ZNN"};

  std::vector<TString> analyses = {"vbf", "nonvbf", "VTR"};
  //   std::vector<TString> analyses = {"nonvbf"};

  for ( auto analysis : analyses  ){
    for ( auto process : processes  ){
      for ( auto setname : sets  ){

	if ( process == "ZNN" && setname == "Pt" ) continue;

	for (auto const& histset : _cloned_hists[ process + "-NLO-" + setname]){
	  std::string hist = std::string(histset.first);
	  if (analysis == "nonvbf" && hist.find("non-VBF")==std::string::npos){
	    continue;
	  }
	  if (analysis == "VTR" && !(hist.find("VTR")!=std::string::npos && hist.find("gen_boson_pt")!=std::string::npos)){
	    continue;
	  }
	  if (analysis == "vbf"     

	      && !((hist.find("MJJ")!=std::string::npos||(hist.find("Default")!=std::string::npos&&hist.find("Default_VTR")==std::string::npos)) && hist.find("gen_boson_pt")!=std::string::npos)){

	    continue;
	  }
	  //	if ( (hist.find("MJJ")!=std::string::npos||hist.find("Default")!=std::string::npos) && hist.find("gen_boson_pt")!=std::string::npos){
	  if (hist.find("PDF")!=std::string::npos && hist.find("PDF_Up")==std::string::npos && hist.find("PDF_Down")==std::string::npos) continue;

	  //temporary add back LO errors qwerty
	  // for (int i = 1;i<_cloned_hists[process+"-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	  //   _cloned_hists[process+"-LO"][ histset.first ]->SetBinError(i,0);
	  std::string savename = "";

	  if ( analysis == "vbf" ){
	    savename = "kfactor_vbf_mjj_";
	    if ( hist.find("MJJ-200-500_gen_boson_pt" )!=std::string::npos ) savename += "200_500";
	    if ( hist.find("MJJ-500-1000_gen_boson_pt" )!=std::string::npos ) savename += "500_1000";
	    if ( hist.find("MJJ-1000-1500_gen_boson_pt" )!=std::string::npos ) savename += "1000_1500";
	    if ( hist.find("MJJ-1500-5000_gen_boson_pt" )!=std::string::npos ) savename += "1500_5000";
	    if ( hist.find("Default_gen_boson_pt" )!=std::string::npos ) savename = "kfactor_vbf_inclusive";
	  }
	  else if ( analysis == "nonvbf" ){

	    savename = "kfactor_nonvbf_";
	    if ( hist.find("gen_boson_pt")!=std::string::npos) savename += "boson_pt";
	    if ( hist.find("gen_jetpt0")!=std::string::npos) savename += "gen_jetp0";

	  }
	  else if ( analysis == "VTR" ){

	    savename = "kfactor_VTR_";
	    if ( hist.find("gen_boson_pt")!=std::string::npos) savename += "boson_pt";

	  }
	  std::string systname = "kfactors_shape";
	  
	  if ( setname == "LHEPt" ){
	    if ( hist.find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	    else if ( hist.find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	    else if ( hist.find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
	    else if ( hist.find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
	    else if (  hist.find("Scale" )!=std::string::npos ) continue;
	    if ( hist.find("Scale" )!=std::string::npos ) histset.second->Scale(2);
	  }
	  if ( setname == "Pt" ){
	    if ( hist.find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	    else if ( hist.find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	    else if ( hist.find("Scale_5" )!=std::string::npos ) systname += "_Fact_Up";
	    else if ( hist.find("Scale_7" )!=std::string::npos ) systname += "_Renorm_Up";
	    else if (  hist.find("Scale" )!=std::string::npos ) continue;
	  }
	  
	  
	  if ( hist.find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
	  else if ( hist.find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";
	  
	  //Get smoothed histos
	  //std::cout << histset.second->GetName() << " - " << _cloned_hists[process+"-LO"][ histset.first ]->GetName() << " - " << process << " - " << setname << " - " << histset.first << std::endl;
	  TH1D * ratio = plotter.DrawRatio( histset.second , _cloned_hists[process+"-LO"][ histset.first ], "", "Ratio-"+process+"-"+setname+"-" + histset.first );
	  //	  TH1D * ratio_zll_over_znn = 0;
	  
	  // if ( process == "ZNN" ){
	  //   ratio_zll_over_znn = plotter.DrawRatio( histset.second , _cloned_hists["ZLL-LO"][ histset.first ], "", "Ratio-"+process+"-"+setname+"-" + histset.first );
	  // }

	  // if ( process == "WLN" && setname ==  "LHEPt" && histset.first == "MJJ-200-500_gen_boson_pt"){
	  //   std::cout << "HERE" << std::endl;
	  //   plotter.SaveToFile( ratio, "VBF-MJJ-200-500" , "NLO_plots" , "OrigRatio");
	  //	  }

	  //TH1D * histo_smoothed =  (TH1D*)ratio->Clone( process+"-NLO-" + setname + "_" +  histset.first + "_smoothed" );
	  //TH1D * histo_fit =  (TH1D*)ratio->Clone( process+"-NLO-" + setname + "_" +  histset.first + "_fit" );
	  //	  TH1D * histo_fit2 =  (TH1D*)ratio->Clone( process+"-NLO-" + setname + "_" +  histset.first + "_fit2" );
	  //histo_smoothed->Smooth(1,"");
	  
	  //double split = 190;
	  //	  double split = 370;
	  //	  double split = 190;

	  //ratio->GetXaxis()->SetRange(2,15);
	  //	  split	= ratio->GetBinLowEdge(ratio->GetMaximumBin()+1);
	  //	  ratio->GetXaxis()->SetRange(1,ratio->GetNbinsX());
	  //	  double split = 120;
	  //	  double start = 40;
	  //	  double start = 40;
	  // double split1 = 170;
	  // double split2 = 300;
	  // if ( hist.find("Scale")!=std::string::npos )
	  //   start = 150;
	  // TF1 * pol3 = new TF1("pol3","pol3",start,split);
	  // TF1 * pol2 = new TF1("pol2","pol2",start,split);
	  // TF1 * pol22 = new TF1("pol22","pol2",start,split);
	  // TF1 * pol23 = new TF1("pol23","pol2",start,split);
	  // TF1 * landau = new TF1("landau","landau",start,split);
	  // TF1 * pol32 = new TF1("pol32","pol3",split,1050);
	  // TF1 * pol0 = new TF1("pol0","pol0",split,1050);     

	  //	  TF1 * polcomb = new TF1("Fit", "(x<="+TString(std::to_string(split))+")*([0]+[1]*x+[2]*x*x) + (x>"+TString(std::to_string(split))+")*([3]+[4]*x+[5]*x*x+[6]*x*x*x)", start, 1100);

	  //	  TF1 * pol_nonvbf_pt = new TF1("NonVBFFitPt", "pol2",200, 1050);
	  //	  double split_nonvbf = 200;
	  //	  TF1 * pol_nonvbf_jetpt = new TF1("NonVBFFitLeadingJet","(x<"+TString(std::to_string(split_nonvbf))+")*([0]+[1]*x+[2]*x*x) + (x>"+TString(std::to_string(split_nonvbf))+")*([3]+[4]*x+[5]*x*x)", start, 1050);
	  
	  // if (  analysis == "vbf" ){
	  //   ratio->Fit(polcomb, "RQ"); 
	  //   ratio->Fit(polcomb, "RQ"); 
	  // }
	  // else if ( analysis == "nonvbf" ){
	  //   if ( hist.find("gen_boson_pt")!=std::string::npos){
	  //     ratio->Fit(pol_nonvbf_pt, "LRQ"); 
	  //   }
	  //   else if ( hist.find("gen_jetpt0")!=std::string::npos) {
	  //     ratio->Fit(pol_nonvbf_jetpt, "LRQ"); 
	  //   }
	  // }
	  std::string saveprocess = "zjet";
	  std::string saveanalysis = "VBF";
	  if ( process == "WLN" ) saveprocess = "wjet";
	  if ( process == "ZNN" ) saveprocess = "znn";
	  if ( process == "WZ" ) saveprocess = "wz";
	  if ( analysis == "nonvbf" ) saveanalysis = "nonVBF";
	  if ( analysis == "VTR" ) saveanalysis = "VTR";
	  if ( setname == "LHEPt" ){	
	    plotter.SaveToFile(ratio, savename, "kfactor_"+saveanalysis+"_"+saveprocess, systname );
	    
	    // if ( process == "ZNN" )
	    //   plotter.SaveToFile(ratio_zll_over_znn, savename, "kfactor_"+saveanalysis+"_"+saveprocess + "_zll", systname );
	  }
	  else if ( setname == "Pt" ){
	    plotter.SaveToFile(ratio, savename, "PtBinned_kfactor_"+saveanalysis+"_" + saveprocess, systname );
	    //	    plotter.SaveToFile(histo_smoothed, savename+"_smoothed", "PtBinned_kfactor_"+saveanalysis+"_" + saveprocess, systname );	  
	    //	    if ( hist.find("Scale")==std::string::npos  ){
	      //	      plotter.SaveToFile(histo_fit, savename+"_fit", "PtBinned_kfactor_"+saveanalysis+"_" + saveprocess, systname );	  
	    //	      plotter.SaveToFile(polcomb, savename+"_fitfunc", "PtBinned_kfactor_"+saveanalysis+"_" + saveprocess, systname );
	    //	    }
	  }
	}
      }
    }
  }

  //2D  
  processes = {"WLN","ZLL","ZNN","WZ"};
  for ( auto analysis : analyses  ){
    for ( auto process : processes  ){
      for ( auto setname : sets  ){
	if ( process == "ZNN" && setname == "Pt" ) continue;
	//2D copy for now
	for (auto const& histset : _cloned_hists2D[ process + "-NLO-" + setname]){
	  std::string hist = std::string(histset.first);
	  //	  std::cout << histset.second->GetName() <<std::endl;
	  if (analysis == "nonvbf" && hist.find("non-VBF")==std::string::npos){
	    continue;
	  }
	  if (analysis == "VTR" && !(hist.find("VTR")!=std::string::npos && hist.find("gen_boson_pt_gen_mjj")!=std::string::npos)){
	    continue;
	  }
	  if (analysis == "vbf"     
	      && !((hist.find("Default")!=std::string::npos&&hist.find("Default_VTR")==std::string::npos) && hist.find("gen_boson_pt_gen_mjj")!=std::string::npos)){
	    continue;
	  }



	  if ( hist.find("Heavy")!=std::string::npos ) {
	    continue;
	  }
	  // if ( hist.find("PDF")!=std::string::npos ) {
	  //   continue;
	  // }

	  if (hist.find("PDF")!=std::string::npos && hist.find("PDF_Up")==std::string::npos && hist.find("PDF_Down")==std::string::npos) continue;

	  std::string savename = "";

	  if ( analysis == "vbf" ){
	    savename = "kfactor_vbf";
	  }
	  else if ( analysis == "nonvbf" ){
	    savename = "kfactor_nonvbf";
	  }
	  else if ( analysis == "VTR" ){
	    savename = "kfactor_VTR";
	  }
	  std::string systname = "kfactors_shape";
	  
	  if ( setname == "LHEPt" ){
	    if ( hist.find("Scale" )!=std::string::npos ){

	      if ( hist.find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	      else if ( hist.find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	      else if ( hist.find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
	      else if ( hist.find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
	      else continue;
	      	      
	      histset.second->Scale(2);
	      	     
	      // if ( hist.find("Uncorrelated" )!=std::string::npos ) systname += "_Uncorrelated";	      
	      // else if ( hist.find("Correlated" )!=std::string::npos ) systname += "_Correlated";	      
	      // else if ( hist.find("Zup" )!=std::string::npos ) systname += "_Zup";	      
	      // else if ( hist.find("Wup" )!=std::string::npos ) systname += "_Wup";	      

	    }
	    //if ( hist.find("Scale" )!=std::string::npos ) histset.second->Scale(2);

	  
	  }
	  if ( setname == "Pt" ){
	    if ( hist.find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	    else if ( hist.find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	    else if ( hist.find("Scale_5" )!=std::string::npos ) systname += "_Fact_Up";
	    else if ( hist.find("Scale_7" )!=std::string::npos ) systname += "_Renorm_Up";
	    else if (  hist.find("Scale" )!=std::string::npos ) continue;
	  }
	  
	  
	  if ( hist.find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
	  else if ( hist.find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";
	  

	  TH2D * ratio = plotter.DrawRatio( histset.second , _cloned_hists2D[process+"-LO"][ histset.first ], "", "Ratio-"+process+"-"+setname+"-" + histset.first );
	  TH2D * ratio16 = plotter.DrawRatio( histset.second , _cloned_hists2D[process+"16-LO"][ histset.first ], "", "Ratio-"+process+"16-"+setname+"-" + histset.first );
	  TH2D * ratio_zll_over_znn = 0;
	  if ( process == "ZNN" ){
	    TH2D * scaled_hist = (TH2D*)_cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Clone( "ZLL-NLO-LHEPt" + histset.first + "_scaled" );
	    scaled_hist->Scale(1.98);
	    ratio_zll_over_znn = plotter.DrawRatio( scaled_hist , _cloned_hists2D[process+"-LO"][ histset.first ], "", "Ratio-"+process+"-"+setname+"-" + histset.first );

	  }

	  std::string saveprocess = "zjet";
	  std::string saveanalysis = "VBF";
	  if ( process == "WLN" ) saveprocess = "wjet";
	  if ( process == "ZNN" ) saveprocess = "znn";
	  if ( process == "WZ" ) saveprocess = "wz";
	  if ( analysis == "nonvbf" ) {
	    saveanalysis = "nonVBF";
	    if (hist.find("jet_multiplicity")!=std::string::npos)
	      saveanalysis = "nonVBF_njet";
	  }
	  if ( analysis == "VTR" ) saveanalysis = "VTR";
	  if ( setname == "LHEPt" ){	
	    //std::cout << savename << " - " << saveanalysis << " - " << saveprocess << " - " << systname << std::endl;
	    plotter.SaveToFile(ratio, savename, "2Dkfactor_"+saveanalysis+"_"+saveprocess, systname );
	    plotter.SaveToFile(ratio16, savename, "2Dkfactor16_"+saveanalysis+"_"+saveprocess, systname );
	    if ( process == "ZNN" )
	      plotter.SaveToFile(ratio_zll_over_znn, savename, "2Dkfactor_"+saveanalysis+"_"+saveprocess + "_zll", systname );
	  }
	  else if ( setname == "Pt" ){
	    plotter.SaveToFile(ratio, savename, "2DPtBinned_kfactor_"+saveanalysis+"_" + saveprocess, systname );
	  }
	}
      }
    }
  }
  


  std::vector< TH1D*> z_mjj = {_cloned_hists["ZLL-LO"]["Default_gen_mjj"], _cloned_hists["ZLL-NLO-Pt"]["Default_gen_mjj"]};
  std::vector< TH1D*> w_mjj = {_cloned_hists["WLN-LO"]["Default_gen_mjj"], _cloned_hists["WLN-NLO-Pt"]["Default_gen_mjj"]};

  std::vector< TH1D*> z = {_cloned_hists["ZLL-LO"]["Default_gen_boson_pt"], _cloned_hists["ZLL-NLO-Pt"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> w = {_cloned_hists["WLN-LO"]["Default_gen_boson_pt"], _cloned_hists["WLN-NLO-Pt"]["Default_gen_boson_pt"]};

  std::vector< TH1D*> zlhe = {_cloned_hists["ZLL-LO"]["Default_gen_boson_pt"], _cloned_hists["ZLL-NLO-LHEPt"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> wlhe = {_cloned_hists["WLN-LO"]["Default_gen_boson_pt"], _cloned_hists["WLN-NLO-LHEPt"]["Default_gen_boson_pt"]};

  std::vector< TH1D*> zerr = {_cloned_hists["Zero"][ "Zero" ],_cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD" ]};
  std::vector< TH1D*> werr = {_cloned_hists["Zero"][ "Zero" ],_cloned_hists["WLN-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD" ]};

  std::vector< TH1D*> z_orig = {_cloned_hists["ZLL-LO"]["Default_gen_boson_pt"], _cloned_hists["ZLL-NLO"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> w_orig = {_cloned_hists["WLN-LO"]["Default_gen_boson_pt"], _cloned_hists["WLN-NLO"]["Default_gen_boson_pt"]};


  std::vector< TH1D*> lo = {_cloned_hists["ZLL-LO"]["Default_gen_boson_pt"], _cloned_hists["WLN-LO"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> nlo = {_cloned_hists["ZLL-NLO"]["Default_gen_boson_pt"], _cloned_hists["WLN-NLO"]["Default_gen_boson_pt"]};

  
std::vector< TString > zleg = {"LO", "NLO"};
  std::vector< TString > loleg = {"z", "w"};

  std::vector< TH1D*> z_scale, z_pdf, z_scale_LHEPt;
  std::vector< TString> z_scaleleg, z_pdfleg;
  std::vector< TH1D*> w_scale, w_pdf, w_scale_LHEPt;
  std::vector< TH1D*> wz_scale, wz_pdf, wz_scale_LHEPt, wz_scale_LHEPt_Correlated, wz_scale_LHEPt_Zup, wz_scale_LHEPt_Wup;
  std::vector< TString> w_scaleleg = {"Renorm Down", "Fact Down", "Fact Up", "Renorm Up", "PDFUp", "PDFDown"};
  std::vector< TString> wz_scaleleg = {"Renorm Down", "Fact Down", "Fact Up", "Renorm Up"};
  std::vector< TString> w_pdfleg;
  std::vector<TH2D*> wz_scale_LHEPt2D,  wz_scale_LHEPt2D_Correlated, wz_scale_LHEPt2D_Zup, wz_scale_LHEPt2D_Wup, wz_pdf_LHEPt2D, wz_scale_LHEPt2D_FlavourSeparated;
  std::vector<TH2D*> wz_scale_LHEPt2D_FlavourSeparated_Light,wz_scale_LHEPt2D_FlavourSeparated_HeavyW,wz_scale_LHEPt2D_FlavourSeparated_HeavyZ;
  std::vector<TH2D*> w_scale_HeavyFlavour;
  std::vector<TH2D*> z_scale_HeavyFlavour;
  std::vector<TH2D*> w_scale_LightFlavour;
  std::vector<TH2D*> z_scale_LightFlavour;
  //  std::vector<TString> sets = {"Pt","LHEPt"};

  w_scale_HeavyFlavour.push_back( _cloned_hists2D["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_HeavyQuark" ]);
  z_scale_HeavyFlavour.push_back( _cloned_hists2D["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_HeavyQuark" ]);
  w_scale_LightFlavour.push_back( _cloned_hists2D["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_NoHeavyQuark" ]);
  z_scale_LightFlavour.push_back( _cloned_hists2D["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_NoHeavyQuark" ]);

  for ( int i = 0;i<9;i++){
    if ( i == 1 || i == 3 || i == 5 || i == 7 ){
      w_scale.push_back( _cloned_hists["WLN-NLO-Pt"][ "Default_gen_boson_pt_Scale_" + std::to_string(i) ]);
      z_scale.push_back( _cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_Scale_" + std::to_string(i) ]);
      wz_scale.push_back( _cloned_hists["WZ-NLO-Pt"][ "Default_gen_boson_pt_ScaleUncorrelated_" + std::to_string(i) ]);
    }
    if ( i == 1 || i == 3 || i == 4 || i == 6 ){
      w_scale_LHEPt.push_back( _cloned_hists["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_Scale_" + std::to_string(i) ]);
      z_scale_LHEPt.push_back( _cloned_hists["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_Scale_" + std::to_string(i) ]);
      wz_scale_LHEPt.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_ScaleUncorrelated_" + std::to_string(i) ]);
      wz_scale_LHEPt_Correlated.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_ScaleCorrelated_" + std::to_string(i) ]);
      wz_scale_LHEPt_Wup.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_ScaleWup_" + std::to_string(i) ]);
      wz_scale_LHEPt_Zup.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_ScaleZup_" + std::to_string(i) ]);

      wz_scale_LHEPt2D.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleUncorrelated_" + std::to_string(i) ]);
      wz_scale_LHEPt2D_Correlated.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleCorrelated_" + std::to_string(i) ]);
      wz_scale_LHEPt2D_Wup.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleWup_" + std::to_string(i) ]);
      wz_scale_LHEPt2D_Zup.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleZup_" + std::to_string(i) ]);
      wz_scale_LHEPt2D_FlavourSeparated.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleFlavourSeparated_" + std::to_string(i) ]);

      wz_scale_LHEPt2D_FlavourSeparated_Light.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleLightCorrelated_" + std::to_string(i) ]);
      wz_scale_LHEPt2D_FlavourSeparated_HeavyW.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleHeavyUncorrelatedW_" + std::to_string(i) ]);
      wz_scale_LHEPt2D_FlavourSeparated_HeavyZ.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleHeavyUncorrelatedZ_" + std::to_string(i) ]);

      w_scale_HeavyFlavour.push_back( _cloned_hists2D["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_Scale_HeavyQuark_" + std::to_string(i) ]);
      z_scale_HeavyFlavour.push_back( _cloned_hists2D["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_Scale_HeavyQuark_" + std::to_string(i) ]);
      w_scale_LightFlavour.push_back( _cloned_hists2D["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_" + std::to_string(i) ]);
      z_scale_LightFlavour.push_back( _cloned_hists2D["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_" + std::to_string(i) ]);
    }   
  }

  
  w_scale.push_back( _cloned_hists["WLN-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD_Up" ]);
  w_scale.push_back( _cloned_hists["WLN-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD_Down" ]);
  w_scale_LHEPt.push_back( _cloned_hists["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_PDF_SD_Up" ]);
  w_scale_LHEPt.push_back( _cloned_hists["WLN-NLO-LHEPt"][ "Default_gen_boson_pt_PDF_SD_Down" ]);

  z_scale.push_back( _cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD_Up" ]);
  z_scale.push_back( _cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD_Down" ]);
  z_scale_LHEPt.push_back( _cloned_hists["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_PDF_SD_Up" ]);
  z_scale_LHEPt.push_back( _cloned_hists["ZLL-NLO-LHEPt"][ "Default_gen_boson_pt_PDF_SD_Down" ]);
  
  wz_scale.push_back( _cloned_hists["WZ-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD_Up" ]);
  wz_scale.push_back( _cloned_hists["WZ-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD_Down" ]);
  // wz_scale_LHEPt.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_PDF_SD_Up" ]);
  // wz_scale_LHEPt.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_PDF_SD_Down" ]);


  plotter.SetLegendXY( 0.65, 0.5, 0.75, 0.8 );
  // plotter.Draw( z , zleg, "z-pt" , true, true);
  // plotter.Draw( w , zleg, "w-pt" , true, true);

  plotter.Draw( zlhe , zleg, "z-lhept" , true, true);
  plotter.Draw( wlhe , zleg, "w-lhept" , true, true);

  
  Plotter plotter_uncertainties(_cmd, _helper);
  
  plotter_uncertainties.SetRangeUser( 0.7, 1.2 );
  plotter_uncertainties.SetLegendXY( 0.5, 0.12, 0.8, 0.32 );
  //  plotter_uncertainties.SetLegendXY( 0.1, 0.1, 0.2, 0.3 );

  // w_scale[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} variation");
  // z_scale[0]->SetTitle(";Boson p_{T}; d#sigma^{Z}/dp_{T} variation");
  // wz_scale[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} / d#sigma^{Z}/dp _{T} variation");
  w_scale_LHEPt[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} variation");
  z_scale_LHEPt[0]->SetTitle(";Boson p_{T}; d#sigma^{Z}/dp_{T} variation");
  wz_scale_LHEPt[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} / d#sigma^{Z}/dp _{T} variation");
  wz_scale_LHEPt_Correlated[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} / d#sigma^{Z}/dp _{T} variation");
  wz_scale_LHEPt_Wup[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} / d#sigma^{Z}/dp _{T} variation");
  wz_scale_LHEPt_Zup[0]->SetTitle(";Boson p_{T}; d#sigma^{W}/dp_{T} / d#sigma^{Z}/dp _{T} variation");



  plotter_uncertainties.SetLegendXY( 0.5, 0.12, 0.8, 0.32 );
  
  std::vector<TString> wuncert = {"W-Renorm-Down","W-Fact-Down","W-Fact-Up", "W-Renorm-Up", "W-PDF-Up", "W-PDF-Down"};
  std::vector<TString> zuncert = {"Z-Renorm-Down","Z-Fact-Down","Z-Fact-Up", "Z-Renorm-Up", "Z-PDF-Up", "Z-PDF-Down"};
///  std::vector<TString> wzuncert = {"WZRatio-Renorm-Down","WZRatio-Fact-Down","WZRatio-Fact-Up", "WZRatio-Fact-Down", "WZRatio-PDF-Up", "WZRatio-PDF-Down"};


  std::vector<TString> wzuncert = {"WZRatioUncorr-Renorm-Down","WZRatioUncorr-Fact-Down","WZRatioUncorr-Fact-Up", "WZRatioUncorr-Renorm-Up"};
  std::vector<TString> wzuncert_corr = {"WZRatioCorr-Renorm-Down","WZRatioCorr-Fact-Down","WZRatioCorr-Fact-Up", "WZRatioCorr-Renorm-Up"};
  std::vector<TString> wzuncert_wup = {"WZRatioWup-Renorm-Down","WZRatioWup-Fact-Down","WZRatioWup-Fact-Up", "WZRatioWup-Renorm-Up"};
  std::vector<TString> wzuncert_zup = {"WZRatioZup-Renorm-Down","WZRatioZup-Fact-Down","WZRatioZup-Fact-Up", "WZRatioZup-Renorm-Up"};
  std::vector<TString> wzuncert_flavourseparated = {"WZRatioFlavourSep-Renorm-Down","WZRatioFlavourSep-Fact-Down","WZRatioFlavourSep-Fact-Up", "WZRatioFlavourSep-Renorm-Up"};


  std::vector<TString> wuncert_flav = {"W-Nominal","W-Renorm-Down","W-Fact-Down","W-Fact-Up", "W-Renorm-Up"};
  std::vector<TString> zuncert_flav = {"Z-Nominal","Z-Renorm-Down","Z-Fact-Down","Z-Fact-Up", "Z-Renorm-Up"};
  
  // plotter.SaveToFile( z_scale_LHEPt, zuncert, "kfactor_VBF_wjet");
  // plotter.SaveToFile( w_scale_LHEPt, wuncert,"kfactor_VBF_wjet");


  plotter.SaveToFile( wz_scale_LHEPt, wzuncert,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt_Correlated, wzuncert_corr,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt_Wup, wzuncert_wup,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt_Zup, wzuncert_zup,"wz-ratio-uncertainty","kfactors_shape");




  plotter.SaveToFile( wz_scale_LHEPt2D, wzuncert,"2D-wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt2D_Correlated, wzuncert_corr,"2D-wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt2D_Wup, wzuncert_wup,"2D-wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt2D_Zup, wzuncert_zup,"2D-wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt2D_FlavourSeparated, wzuncert_flavourseparated,"2D-wz-ratio-uncertainty","kfactors_shape");

  plotter.SaveToFile( wz_scale_LHEPt2D_FlavourSeparated_Light, wzuncert_flavourseparated,"2D-wz-ratio-uncertainty-split","light");
  plotter.SaveToFile( wz_scale_LHEPt2D_FlavourSeparated_HeavyW, wzuncert_flavourseparated,"2D-wz-ratio-uncertainty-split","heavy-w");
  plotter.SaveToFile( wz_scale_LHEPt2D_FlavourSeparated_HeavyZ, wzuncert_flavourseparated,"2D-wz-ratio-uncertainty-split","heavy-z");


  plotter.SaveToFile( w_scale_HeavyFlavour, wuncert_flav,"FlavourScaleUncertainty","w-heavy");
  plotter.SaveToFile( z_scale_HeavyFlavour, zuncert_flav,"FlavourScaleUncertainty","z-heavy");
  plotter.SaveToFile( w_scale_LightFlavour, wuncert_flav,"FlavourScaleUncertainty","w-light");
  plotter.SaveToFile( z_scale_LightFlavour, zuncert_flav,"FlavourScaleUncertainty","z-light");
  
  
  for ( int i = 0;i<102;i++){
    z_pdf.push_back( _cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_PDF_" + std::to_string(i) ]);
    z_pdfleg.push_back( TString(std::to_string(i) ));
  }   




  // plotter_uncertainties.Draw( z_scale , w_scaleleg, "z-scale", false, false, "HIST");
  // plotter_uncertainties.Draw( wz_scale , w_scaleleg, "wz-scale", false, false, "HIST");
  // plotter_uncertainties.Draw( w_scale , w_scaleleg, "w-scale", false, false,"HIST");

  //  plotter.Draw( z_pdf , z_pdfleg, "z-pdf");

  // plotter.Draw( z_mjj , zleg, "z-mjj" , true, true);
  // plotter.Draw( w_mjj , zleg, "w-mjj" , true, true);
  
  // plotter.Draw( z_orig , zleg, "z-pt-orig" , true, true);
  // plotter.Draw( w_orig , zleg, "w-pt-orig" , true, true);
  
  // plotter.Draw( z , zleg, "z-pt", true );
  // plotter.Draw( w , zleg, "w-pt", true );


  
  //Andreas studies
  /*
  std::vector<TH1D*> vec1 = {_cloned_hists["WLN-NLO-Pt"]["Default_gen_boson_pt"],_cloned_hists["WLN-NLO-LHEPt"]["Default_gen_boson_pt"]};
  std::vector<TH1D*> vec5 = {_cloned_hists["WLN-NLO-Pt"]["All_gen_boson_pt"],_cloned_hists["WLN-NLO-LHEPt"]["All_gen_boson_pt"]};
  std::vector<TString> leg1 = {"pt binned","pt+jet binned"};
  plotter.Draw( vec1, leg1, "w-nlo-ratio" , true, true);
  plotter.Draw( vec1, leg1, "w-nlo-ratio" , true, false);
  plotter.Draw( vec5, leg1, "w-nlo-ratio-all" , true, true);
  plotter.Draw( vec5, leg1, "w-nlo-ratio-all" , true, false);
  */

  // std::vector<TH1D*> vec2 = {_cloned_hists["WLN-NLO-Pt"]["Default_n_jets"],_cloned_hists["WLN-NLO-LHEPt"]["Default_n_jets"]};
  // plotter.Draw( vec2, leg1, "w-nlo-njetratio" , true, false);


  // std::vector<TH1D*> vec3 = {_cloned_hists["WLN-NLO-Pt"]["NJET2_gen_boson_pt"],_cloned_hists["WLN-NLO-LHEPt"]["NJET2_gen_boson_pt"]};
  // plotter.Draw( vec3, leg1, "w-nlo-ratio-njet2" , true, false);

  // std::vector<TH1D*> vec4 = {_cloned_hists["WLN-NLO-Pt"]["NJET3_gen_boson_pt"],_cloned_hists["WLN-NLO-LHEPt"]["NJET3_gen_boson_pt"]};
  // plotter.Draw( vec4, leg1, "w-nlo-ratio-njet3" , true,false);



  //  TH1D * zerr =  _cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_PDF_SD" ];

  // plotter.DrawError( z , zerr, zleg, "z-pt", true );
  // plotter.DrawError( z , zerr, zleg, "z-pt", true, true );


  //  plotter.Draw( w , zleg, "w-pt", true );






  // plotter.Draw( lo , loleg, "lo-pt" , true);
  // plotter.Draw( lo , loleg, "lo-pt" );

  // plotter.Draw( nlo , loleg, "nlo-pt" , true);
  // plotter.Draw( nlo , loleg, "nlo-pt" );




  // plotter.SaveToFile( _cloned_hists[ "WLN-LO" ][ "MJJ-200-500_gen_boson_pt" ], "VBF_MJJ_200_500" , "NLO_plots" , "W_Nominal_LO");
  // plotter.SaveToFile( _cloned_hists[ "WLN-LO" ][ "MJJ-500-1000_gen_boson_pt" ], "VBF_MJJ_500_1000" , "NLO_plots" , "W_Nominal_LO");
  // plotter.SaveToFile( _cloned_hists[ "WLN-LO" ][ "MJJ-1000-1500_gen_boson_pt" ], "VBF_MJJ_1000_1500" , "NLO_plots" , "W_Nominal_LO");
  // plotter.SaveToFile( _cloned_hists[ "WLN-LO" ][ "MJJ-1500-5000_gen_boson_pt" ], "VBF_MJJ_1500_5000" , "NLO_plots" , "W_Nominal_LO");

  // plotter.SaveToFile( _cloned_hists[ "WLN-NLO-LHEPt" ][ "MJJ-200-500_gen_boson_pt" ], "VBF_MJJ_200_500" , "NLO_plots" , "W_Nominal_NLO");
  // plotter.SaveToFile( _cloned_hists[ "WLN-NLO-LHEPt" ][ "MJJ-500-1000_gen_boson_pt" ], "VBF_MJJ_500_1000" , "NLO_plots" , "W_Nominal_NLO");
  // plotter.SaveToFile( _cloned_hists[ "WLN-NLO-LHEPt" ][ "MJJ-1000-1500_gen_boson_pt" ], "VBF_MJJ_1000_1500" , "NLO_plots" , "W_Nominal_NLO");
  // plotter.SaveToFile( _cloned_hists[ "WLN-NLO-LHEPt" ][ "MJJ-1500-5000_gen_boson_pt" ], "VBF_MJJ_1500_5000" , "NLO_plots" , "W_Nominal_NLO");

  // plotter.SaveToFile( _cloned_hists[ "ZLL-LO" ][ "MJJ-200-500_gen_boson_pt" ], "VBF_MJJ_200_500" , "NLO_plots" , "Z_Nominal_LO");
  // plotter.SaveToFile( _cloned_hists[ "ZLL-LO" ][ "MJJ-500-1000_gen_boson_pt" ], "VBF_MJJ_500_1000" , "NLO_plots" , "Z_Nominal_LO");
  // plotter.SaveToFile( _cloned_hists[ "ZLL-LO" ][ "MJJ-1000-1500_gen_boson_pt" ], "VBF_MJJ_1000_1500" , "NLO_plots" , "Z_Nominal_LO");
  // plotter.SaveToFile( _cloned_hists[ "ZLL-LO" ][ "MJJ-1500-5000_gen_boson_pt" ], "VBF_MJJ_1500_5000" , "NLO_plots" , "Z_Nominal_LO");

  // plotter.SaveToFile( _cloned_hists[ "ZLL-NLO-LHEPt" ][ "MJJ-200-500_gen_boson_pt" ], "VBF_MJJ_200_500" , "NLO_plots" , "Z_Nominal_NLO");
  // plotter.SaveToFile( _cloned_hists[ "ZLL-NLO-LHEPt" ][ "MJJ-500-1000_gen_boson_pt" ], "VBF_MJJ_500_1000" , "NLO_plots" , "Z_Nominal_NLO");
  // plotter.SaveToFile( _cloned_hists[ "ZLL-NLO-LHEPt" ][ "MJJ-1000-1500_gen_boson_pt" ], "VBF_MJJ_1000_1500" , "NLO_plots" , "Z_Nominal_NLO");
  // plotter.SaveToFile( _cloned_hists[ "ZLL-NLO-LHEPt" ][ "MJJ-1500-5000_gen_boson_pt" ], "VBF_MJJ_1500_5000" , "NLO_plots" , "Z_Nominal_NLO");



  //  plotter.SaveToFile( plotter.DrawRatio(_cloned_hists[ "WLN-NLO-LHEPt" ][ "MJJ-200-500_gen_boson_pt" ],_cloned_hists[ "WLN-LO" ][ "MJJ-200-500_gen_boson_pt" ]), "VBF-MJJ-200-500" , "NLO_plots" , "Ratio");
  //  output->Close();



}
