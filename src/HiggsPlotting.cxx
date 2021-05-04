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

  //LO W JETS 2017
  filenames[ "WLN-LO-70-100" ] = "MC_WJetsToLNu_HT-70To100_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-100-200" ] = "MC_WJetsToLNu_HT-100To200_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-200-400" ] = "MC_WJetsToLNu_HT-200To400_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-400-600" ] = "MC_WJetsToLNu_HT-400To600_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-600-800" ] = "MC_WJetsToLNu_HT-600To800_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-800-1200" ] = "MC_WJetsToLNu_HT-800To1200_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-1200-2500" ] = "MC_WJetsToLNu_HT-1200To2500_madgraphMLM_pythia8.root";
  filenames[ "WLN-LO-2500-Inf" ] = "MC_WJetsToLNu_HT-2500ToInf_madgraphMLM_pythia8.root";

  //LO DY JETS 2017
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

  //LO Z JETS 2017
  filenames[ "ZNN-LO-100-200" ] = "MC_ZJetsToNuNu_HT-100To200-madgraph.root";
  filenames[ "ZNN-LO-200-400" ] = "MC_ZJetsToNuNu_HT-200To400-madgraph.root";
  filenames[ "ZNN-LO-400-600" ] = "MC_ZJetsToNuNu_HT-400To600-madgraph.root";
  filenames[ "ZNN-LO-600-800" ] = "MC_ZJetsToNuNu_HT-600To800-madgraph.root";
  filenames[ "ZNN-LO-800-1200" ] = "MC_ZJetsToNuNu_HT-800To1200-madgraph.root";
  filenames[ "ZNN-LO-1200-2500" ] = "MC_ZJetsToNuNu_HT-1200To2500-madgraph.root";
  filenames[ "ZNN-LO-2500-Inf" ] = "MC_ZJetsToNuNu_HT-2500ToInf-madgraph.root";

  //LO W JETS 2016
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

  //LO DY JETS 2016
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

  //LO Z JETS 2016
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

  //LO W JETS 2018
  filenames[ "WLN18-LO-70-100" ] = "MC_WJetsToLNu18_HT-70To100.root";
  filenames[ "WLN18-LO-100-200" ] = "MC_WJetsToLNu18_HT-100To200.root";
  filenames[ "WLN18-LO-200-400" ] = "MC_WJetsToLNu18_HT-200To400.root";
  filenames[ "WLN18-LO-400-600" ] = "MC_WJetsToLNu18_HT-400To600.root";
  filenames[ "WLN18-LO-600-800" ] = "MC_WJetsToLNu18_HT-600To800.root";
  filenames[ "WLN18-LO-800-1200" ] = "MC_WJetsToLNu18_HT-800To1200.root";
  filenames[ "WLN18-LO-1200-2500" ] = "MC_WJetsToLNu18_HT-1200To2500.root";
  filenames[ "WLN18-LO-2500-Inf" ] = "MC_WJetsToLNu18_HT-2500ToInf.root";

  //LO DY JETS 2018
  filenames[ "ZLL18-LO-70-100" ] = "MC_DYJetsToLL18_M-50_HT-70to100.root";
  filenames[ "ZLL18-LO-100-200" ] = "MC_DYJetsToLL18_M-50_HT-100to200.root";
  filenames[ "ZLL18-LO-200-400" ] = "MC_DYJetsToLL18_M-50_HT-200to400.root";
  filenames[ "ZLL18-LO-400-600" ] = "MC_DYJetsToLL18_M-50_HT-400to600.root";
  filenames[ "ZLL18-LO-400-600-ext1" ] = "MC_DYJetsToLL18_M-50_HT-400to600-ext1.root";
  filenames[ "ZLL18-LO-600-800" ] = "MC_DYJetsToLL18_M-50_HT-600to800.root";
  filenames[ "ZLL18-LO-800-1200" ] = "MC_DYJetsToLL18_M-50_HT-800to1200.root";
  filenames[ "ZLL18-LO-1200-2500" ] = "MC_DYJetsToLL18_M-50_HT-1200to2500.root";
  filenames[ "ZLL18-LO-2500-Inf" ] = "MC_DYJetsToLL18_M-50_HT-2500toInf.root";

  //LO Z JETS 2018
  filenames[ "ZNN18-LO-100-200" ] = "MC_ZJetsToNuNu18_HT-100To200.root";
  filenames[ "ZNN18-LO-200-400" ] = "MC_ZJetsToNuNu18_HT-200To400.root";
  filenames[ "ZNN18-LO-400-600" ] = "MC_ZJetsToNuNu18_HT-400To600.root";
  filenames[ "ZNN18-LO-600-800" ] = "MC_ZJetsToNuNu18_HT-600To800.root";
  filenames[ "ZNN18-LO-800-1200" ] = "MC_ZJetsToNuNu18_HT-800To1200.root";
  filenames[ "ZNN18-LO-1200-2500" ] = "MC_ZJetsToNuNu18_HT-1200To2500.root";
  filenames[ "ZNN18-LO-2500-Inf" ] = "MC_ZJetsToNuNu18_HT-2500ToInf.root";

  //NLO W 1 JET

  filenames[ "WLN-NLO-LHEPt-1J-50-150" ]     = "MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-50-150-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-1J-100-150" ]     = "MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-100-150-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-1J-150-250" ]     = "MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-150-250-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-1J-250-400" ]     = "MC_W1JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-400-Inf" ]     = "MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-1J-400-Inf-ext1" ]     = "MC_W1JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1.root";

  //NLO W 2 JETS

  filenames[ "WLN-NLO-LHEPt-2J-50-150" ]     = "MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-2J-50-150-ext1" ]     ="MC_W2JetsToLNu_LHEWpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-100-150" ]     = "MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-2J-100-150-ext1" ]     ="MC_W2JetsToLNu_LHEWpT_100-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-150-250" ]     = "MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-LHEPt-2J-150-250-ext1" ]     ="MC_W2JetsToLNu_LHEWpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-250-400" ]     = "MC_W2JetsToLNu_LHEWpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-LHEPt-2J-400-Inf" ]     = "MC_W2JetsToLNu_LHEWpT_400-inf_amcnloFXFX-pythia8-ext1.root";

  //NLO DY 1 JET

  filenames[ "ZLL-NLO-LHEPt-1J-50-150" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-50-150-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-1J-150-250" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-150-250-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-1J-250-400" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-250-400-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-1J-400-Inf" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-1J-400-Inf-ext1" ]     = "MC_DY1JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1.root";

  //NLO DY 2 JETS

  filenames[ "ZLL-NLO-LHEPt-2J-50-150" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-50-150-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_50-150_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-150-250" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-150-250-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-250-400" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-250-400-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZLL-NLO-LHEPt-2J-400-Inf" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";
  filenames[ "ZLL-NLO-LHEPt-2J-400-Inf-ext1" ]     = "MC_DY2JetsToLL_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8-ext1.root";

  //NLO Z 1 JET

  filenames[ "ZNN-NLO-LHEPt-1J-50-150" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-1J-150-250" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-1J-150-250-ext1" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZNN-NLO-LHEPt-1J-250-400" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-1J-250-400-ext1" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_250-400-amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZNN-NLO-LHEPt-1J-400-Inf" ]     = "MC_Z1JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";

  //NLO Z 2 JETS

  filenames[ "ZNN-NLO-LHEPt-2J-50-150" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_50-150_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-2J-150-250" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_150-250_amcnloFXFX-pythia8-ext1.root";
  filenames[ "ZNN-NLO-LHEPt-2J-250-400" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8.root";
  filenames[ "ZNN-NLO-LHEPt-2J-250-400-ext1" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_250-400_amcnloFXFX-pythia8-ext1.root";  
  filenames[ "ZNN-NLO-LHEPt-2J-400-Inf" ]     = "MC_Z2JetsToNuNu_M-50_LHEZpT_400-inf_amcnloFXFX-pythia8.root";

  //List of 1D plots you wish to produce
  std::vector<std::string> plots = {"gen_boson_pt", "gen_boson_eta", "gen_events", "gen_jetpt0","LHE_HT", "gen_boson_mass","gen_mjj", "gen_lepton_eta0", "gen_lepton_eta1", "gen_lepton_pt0", "gen_lepton_pt1", "gen_dphijj"};

  //List of 2D plots you wish to produce (need to include the ones you are producing k-factors for)
  std::vector<std::string> plots2D = {"gen_boson_pt_gen_mjj","gen_boson_pt_gen_jetpt0","gen_boson_pt_gen_jet_multiplicity","gen_boson_pt_gen_boson_eta"};

  //Correponds to the HistoSets defined when the histograms were filled. Each HistoSet corresponds to a different selection criteria
  std::vector<std::string> histoSets = { "Default", "All" , "Default_VTR", "MJJ-200-500",  "MJJ-500-1000",  "MJJ-1000-1500", "MJJ-1500-5000", "non-VBF"};

  //Load histograms into a 2D map with a short name

  TH1D * loadHist = 0;
  TH2D * loadHist2D = 0;
  TFile * loadFile = 0;

  //TString filepath = "/vols/cms/snwebb/InvisibleOutput/Merged/";
  TString filepath = _cmd->string_val( "--indir" );

  for (auto const& filename : filenames){
    
    loadFile = new TFile ( filepath + filename.second, "READ" );
    
    for ( auto histoset : histoSets ){
      std::string getname = histoset;

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
      std::vector<std::string> systplots = {"gen_boson_pt", "gen_jetpt0"};//1D plots that have associate systematic uncertainties (to produce 1D k-factors)
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
	int maxpdfs = 33;
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
	}
      
	int maxpdfs = 33;
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

  double bins[15] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 400, 520, 640, 760, 880,1100}; //Default boson pT k-factor binnings in 1D
  //  double bins[51] = {0, 40, 80,100, 120,130,140,150, 160,170,180,190, 200,210,220,230, 240,250,260,270, 280,290,300,310, 320,340,360,380, 400,420,440,460,480,500, 520,540,560,580,600,620, 640,680,720,760,800,840,880,950,1000,1050,1100}; //fine binnings for mjj if needed
  double bins_nonvbf_bosonpt[18] = {0,70,100,120,150,170,200,225,250,275,300,350,400,450,600,750,900,1050};

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
	  plot.second->Scale( 1,"width" );
	}

      }
      else if ( std::string(plot.first).find("gen_jetpt0")!=std::string::npos ){
	plot.second->Rebin( 2 );
      }
    }
  }
  
}

//This function is quite long, but simply adds together the various sub-samples with the correct cross-section such that we have one histogram per sample (i.e. NLO W, NLO Z, LO W etc) per plot 
void HiggsPlotting::CombineHistograms(){

  std::map<TString, double> _xs;
  std::map<TString, double> _sum;  

  std::map<TString, double> _stitchdy;
  std::map<TString, double> _stitchw;
  std::map<TString, double> _stitchznn;

  for (auto & histset : _cloned_hists ){
    _sum[ histset.first ] = ((histset.second)[ "All_gen_events" ])->GetBinContent( 2 );
  }

  //////////////////
  //     NLO      // 
  //////////////////

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

  _sum["WLN-NLO-LHEPt-1J-50-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-50-150" ]  +   _sum["WLN-NLO-LHEPt-1J-50-150-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-100-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-100-150" ]  +   _sum["WLN-NLO-LHEPt-1J-100-150-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-150-250-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-150-250" ]  +   _sum["WLN-NLO-LHEPt-1J-150-250-ext1" ];
  _sum["WLN-NLO-LHEPt-1J-250-400-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-250-400" ]  ;
  _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _sum["WLN-NLO-LHEPt-1J-400-Inf" ]  +   _sum["WLN-NLO-LHEPt-1J-400-Inf-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-50-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-50-150" ]  +   _sum["WLN-NLO-LHEPt-2J-50-150-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-100-150-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-100-150" ]  +   _sum["WLN-NLO-LHEPt-2J-100-150-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-150-250-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-150-250" ]  +   _sum["WLN-NLO-LHEPt-2J-150-250-ext1" ];
  _sum["WLN-NLO-LHEPt-2J-250-400-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-250-400" ]  ;
  _sum["WLN-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _sum["WLN-NLO-LHEPt-2J-400-Inf" ]  ;

  //1D
  for (auto const& histset : _cloned_hists["WLN-NLO-LHEPt-1J-50-150"]){
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-NLO-LHEPt-1J-100-150_" + histset.first  );   
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Reset();
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-50-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-50-150"     ] / _sum["WLN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-50-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-50-150"     ] / _sum["WLN-NLO-LHEPt-1J-50-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-50-150" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-50-150"     ] / _sum["WLN-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-50-150-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-50-150"     ] / _sum["WLN-NLO-LHEPt-2J-50-150-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-150-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-150-250"     ] / _sum["WLN-NLO-LHEPt-1J-150-250-TOT"     ] ); 
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-150-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-150-250"     ] / _sum["WLN-NLO-LHEPt-1J-150-250-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-150-250" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-150-250"     ] / _sum["WLN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-150-250-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-150-250"     ] / _sum["WLN-NLO-LHEPt-2J-150-250-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-250-400"     ] / _sum["WLN-NLO-LHEPt-1J-250-400-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-250-400" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-250-400"     ] / _sum["WLN-NLO-LHEPt-2J-250-400-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-400-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-1J-400-Inf-ext1" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-1J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-1J-400-Inf-TOT"     ] );
    _cloned_hists["WLN-NLO-LHEPt"][ histset.first ]->Add( _cloned_hists["WLN-NLO-LHEPt-2J-400-Inf" ][histset.first]  , 1E3 * _xs["WLN-NLO-LHEPt-2J-400-Inf"     ] / _sum["WLN-NLO-LHEPt-2J-400-Inf-TOT"     ] );
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


  ///////  DY  /////////

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

  _sum["ZLL-NLO-LHEPt-1J-50-150-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-50-150" ]  +   _sum["ZLL-NLO-LHEPt-1J-50-150-ext1" ];
  _sum["ZLL-NLO-LHEPt-1J-150-250-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-150-250" ]  +   _sum["ZLL-NLO-LHEPt-1J-150-250-ext1" ];
  _sum["ZLL-NLO-LHEPt-1J-250-400-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-250-400" ]  +   _sum["ZLL-NLO-LHEPt-1J-250-400-ext1" ];
  _sum["ZLL-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _sum["ZLL-NLO-LHEPt-1J-400-Inf" ]  +   _sum["ZLL-NLO-LHEPt-1J-400-Inf-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-50-150-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-50-150" ]  +   _sum["ZLL-NLO-LHEPt-2J-50-150-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-150-250-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-150-250" ]  +   _sum["ZLL-NLO-LHEPt-2J-150-250-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-250-400-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-250-400" ]  +   _sum["ZLL-NLO-LHEPt-2J-250-400-ext1" ];
  _sum["ZLL-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _sum["ZLL-NLO-LHEPt-2J-400-Inf" ]  +   _sum["ZLL-NLO-LHEPt-2J-400-Inf-ext1" ];

  //1D
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


  ///////  ZNN  /////////

  _xs[ "ZNN-NLO-LHEPt-1J-50-150" ] = 602.9;     
  _xs[ "ZNN-NLO-LHEPt-2J-50-150" ] = 328.9;     
  _xs[ "ZNN-NLO-LHEPt-1J-150-250" ] = 18.12;     
  _xs[ "ZNN-NLO-LHEPt-2J-150-250" ] = 29.74;     
  _xs[ "ZNN-NLO-LHEPt-1J-250-400" ] = 2.045;     
  _xs[ "ZNN-NLO-LHEPt-2J-250-400" ] = 5.23;     
  _xs[ "ZNN-NLO-LHEPt-1J-400-Inf" ] = 0.2256;     
  _xs[ "ZNN-NLO-LHEPt-2J-400-Inf" ] = 0.8433;     

  _sum["ZNN-NLO-LHEPt-1J-50-150-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-50-150" ] ;
  _sum["ZNN-NLO-LHEPt-1J-150-250-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-150-250" ]  +   _sum["ZNN-NLO-LHEPt-1J-150-250-ext1" ];
  _sum["ZNN-NLO-LHEPt-1J-250-400-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-250-400" ]  +   _sum["ZNN-NLO-LHEPt-1J-250-400-ext1" ];
  _sum["ZNN-NLO-LHEPt-1J-400-Inf-TOT" ]  =    _sum["ZNN-NLO-LHEPt-1J-400-Inf" ] ;
  _sum["ZNN-NLO-LHEPt-2J-50-150-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-50-150" ] ;
  _sum["ZNN-NLO-LHEPt-2J-150-250-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-150-250" ]  ;
  _sum["ZNN-NLO-LHEPt-2J-250-400-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-250-400" ]  +   _sum["ZNN-NLO-LHEPt-2J-250-400-ext1" ];
  _sum["ZNN-NLO-LHEPt-2J-400-Inf-TOT" ]  =    _sum["ZNN-NLO-LHEPt-2J-400-Inf" ];

  //1D
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
  
  ////////////////////////////////////////////////////////

  ////////////////////
  //  LO HT Binned  // 
  ////////////////////


  ///////  DY  /////////  
  //Same cross-sections as in the note (2017)

  _xs[ "ZLL-LO-70-100" ] = 146.9;
  _xs[ "ZLL-LO-100-200"] = 161.3;
  _xs[ "ZLL-LO-100-200-ext"] = 160.9;
  _xs[ "ZLL-LO-200-400"] = 48.68;
  _xs[ "ZLL-LO-200-400-ext"] = 48.52;
  _xs[ "ZLL-LO-200-400-ext1"] = 48.52;
  _xs[ "ZLL-LO-400-600"] = 7.033;
  _xs[ "ZLL-LO-400-600-ext"] = 6.998;
  _xs[ "ZLL-LO-600-800"] = 1.745;
  _xs[ "ZLL-LO-800-1200"] = 0.8077;
  _xs[ "ZLL-LO-1200-2500"] = 0.1923;
  _xs[ "ZLL-LO-2500-Inf"] = 0.003477;

  //Ad hoc stitching weights
  _stitchdy[ "ZLL-LO-70-100" ] = 1.0;
  _stitchdy[ "ZLL-LO-100-200"] = 1.0;
  _stitchdy[ "ZLL-LO-100-200-ext"] = 1.0;
  _stitchdy[ "ZLL-LO-200-400"] = 0.999;
  _stitchdy[ "ZLL-LO-200-400-ext"] = 0.999;
  _stitchdy[ "ZLL-LO-400-600"] = 0.99;
  _stitchdy[ "ZLL-LO-400-600-ext"] = 0.99;
  _stitchdy[ "ZLL-LO-600-800"] = 1.0;
  _stitchdy[ "ZLL-LO-800-1200"] = 1.0;
  _stitchdy[ "ZLL-LO-1200-2500"] = 1.03;
  _stitchdy[ "ZLL-LO-2500-Inf"] = 1.26;

  //If stitching required, set stitch_samplesdy to true
  bool stitch_samplesdy = false;
  if ( !stitch_samplesdy ){
    for (auto& stitch:_stitchdy){
      stitch.second = 1;
    }
  }
  
  _sum["ZLL-LO-100-200-TOT"    ] =  _sum["ZLL-LO-100-200"    ] + _sum["ZLL-LO-100-200-ext"]; 
  _sum["ZLL-LO-200-400-TOT"    ] =  _sum["ZLL-LO-200-400"    ] + _sum["ZLL-LO-200-400-ext"];
  _sum["ZLL-LO-400-600-TOT"    ] =  _sum["ZLL-LO-400-600"    ] + _sum["ZLL-LO-400-600-ext"];

  for (auto const& histset : _cloned_hists["ZLL-LO-70-100"]){
    
    _cloned_hists["ZLL-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-LO_" + histset.first );   
    _cloned_hists["ZLL-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-70-100"     ][histset.first], 1E3* _stitchdy["ZLL-LO-70-100"     ] * _xs["ZLL-LO-70-100"     ] / _sum["ZLL-LO-70-100"     ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200"    ][histset.first], 1E3* _stitchdy["ZLL-LO-100-200"    ] * _xs["ZLL-LO-100-200"    ] / _sum["ZLL-LO-100-200-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200-ext"][histset.first], 1E3* _stitchdy["ZLL-LO-100-200-ext"] * _xs["ZLL-LO-100-200-ext"] / _sum["ZLL-LO-100-200-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400"    ][histset.first], 1E3* _stitchdy["ZLL-LO-200-400"    ] * _xs["ZLL-LO-200-400"    ] / _sum["ZLL-LO-200-400-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400-ext"][histset.first], 1E3* _stitchdy["ZLL-LO-200-400-ext"] * _xs["ZLL-LO-200-400-ext"] / _sum["ZLL-LO-200-400-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600"    ][histset.first], 1E3* _stitchdy["ZLL-LO-400-600"    ] * _xs["ZLL-LO-400-600"    ] / _sum["ZLL-LO-400-600-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600-ext"][histset.first], 1E3* _stitchdy["ZLL-LO-400-600-ext"] * _xs["ZLL-LO-400-600-ext"] / _sum["ZLL-LO-400-600-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-600-800"    ][histset.first], 1E3* _stitchdy["ZLL-LO-600-800"    ] * _xs["ZLL-LO-600-800"    ] / _sum["ZLL-LO-600-800"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-800-1200"   ][histset.first], 1E3* _stitchdy["ZLL-LO-800-1200"   ] * _xs["ZLL-LO-800-1200"   ] / _sum["ZLL-LO-800-1200"   ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-1200-2500"  ][histset.first], 1E3* _stitchdy["ZLL-LO-1200-2500"  ] * _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL-LO-1200-2500"  ]); 
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-2500-Inf"   ][histset.first], 1E3* _stitchdy["ZLL-LO-2500-Inf"   ] * _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL-LO-2500-Inf"   ]);

  }


  //2D
  for (auto const& histset : _cloned_hists2D["ZLL-LO-70-100"]){
    
    _cloned_hists2D["ZLL-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL-LO_" + histset.first );   
    _cloned_hists2D["ZLL-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-70-100"     ][histset.first], 1E3* _stitchdy["ZLL-LO-70-100"     ] * _xs["ZLL-LO-70-100"     ] / _sum["ZLL-LO-70-100"     ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-100-200"    ][histset.first], 1E3* _stitchdy["ZLL-LO-100-200"    ] * _xs["ZLL-LO-100-200"    ] / _sum["ZLL-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-100-200-ext"][histset.first], 1E3* _stitchdy["ZLL-LO-100-200-ext"] * _xs["ZLL-LO-100-200-ext"] / _sum["ZLL-LO-100-200-TOT"]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-200-400"    ][histset.first], 1E3* _stitchdy["ZLL-LO-200-400"    ] * _xs["ZLL-LO-200-400"    ] / _sum["ZLL-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-200-400-ext"][histset.first], 1E3* _stitchdy["ZLL-LO-200-400-ext"] * _xs["ZLL-LO-200-400-ext"] / _sum["ZLL-LO-200-400-TOT"]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-400-600"    ][histset.first], 1E3* _stitchdy["ZLL-LO-400-600"    ] * _xs["ZLL-LO-400-600"    ] / _sum["ZLL-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-400-600-ext"][histset.first], 1E3* _stitchdy["ZLL-LO-400-600-ext"] * _xs["ZLL-LO-400-600-ext"] / _sum["ZLL-LO-400-600-TOT"]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-600-800"    ][histset.first], 1E3* _stitchdy["ZLL-LO-600-800"    ] * _xs["ZLL-LO-600-800"    ] / _sum["ZLL-LO-600-800"    ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-800-1200"   ][histset.first], 1E3* _stitchdy["ZLL-LO-800-1200"   ] * _xs["ZLL-LO-800-1200"   ] / _sum["ZLL-LO-800-1200"   ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-1200-2500"  ][histset.first], 1E3* _stitchdy["ZLL-LO-1200-2500"  ] * _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL-LO-1200-2500"  ]);
    _cloned_hists2D["ZLL-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL-LO-2500-Inf"   ][histset.first], 1E3* _stitchdy["ZLL-LO-2500-Inf"   ] * _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL-LO-2500-Inf"   ]);

  }


  ///////  Z NU NU  /////////  

  //Update to the same as the note (2017)
  _xs[ "ZNN-LO-100-200"] = 305.3;
  _xs[ "ZNN-LO-200-400"] = 91.86;
  _xs[ "ZNN-LO-400-600"] = 13.13;
  _xs[ "ZNN-LO-600-800"] = 3.242;
  _xs[ "ZNN-LO-800-1200"] = 1.501;
  _xs[ "ZNN-LO-1200-2500"] = 0.3431;
  _xs[ "ZNN-LO-2500-Inf"] = 0.005146;

  //Ad hoc stitching weights
  _stitchznn[ "ZNN-LO-100-200"] = 0.994;
  _stitchznn[ "ZNN-LO-200-400"] = 1.01;
  _stitchznn[ "ZNN-LO-400-600"] = 0.995;
  _stitchznn[ "ZNN-LO-600-800"] = 1.0;
  _stitchznn[ "ZNN-LO-800-1200"] = 1.01;
  _stitchznn[ "ZNN-LO-1200-2500"] = 1.07;
  _stitchznn[ "ZNN-LO-2500-Inf"] = 1.5;


  //If stitching required, set stitch_samplesznn to true
  bool stitch_samplesznn = false;
  if ( !stitch_samplesznn ){
    for (auto& stitch:_stitchznn){
      stitch.second = 1;
    }
  }

  

  for (auto const& histset : _cloned_hists["ZNN-LO-100-200"]){
    
    _cloned_hists["ZNN-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZNN-LO_" + histset.first );   
    _cloned_hists["ZNN-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-100-200"    ][histset.first], 1E3* _stitchznn["ZNN-LO-100-200"    ] * _xs["ZNN-LO-100-200"    ] / _sum["ZNN-LO-100-200"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-200-400"    ][histset.first], 1E3* _stitchznn["ZNN-LO-200-400"    ] * _xs["ZNN-LO-200-400"    ] / _sum["ZNN-LO-200-400"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-400-600"    ][histset.first], 1E3* _stitchznn["ZNN-LO-400-600"    ] * _xs["ZNN-LO-400-600"    ] / _sum["ZNN-LO-400-600"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-600-800"    ][histset.first], 1E3* _stitchznn["ZNN-LO-600-800"    ] * _xs["ZNN-LO-600-800"    ] / _sum["ZNN-LO-600-800"    ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-800-1200"   ][histset.first], 1E3* _stitchznn["ZNN-LO-800-1200"   ] * _xs["ZNN-LO-800-1200"   ] / _sum["ZNN-LO-800-1200"   ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-1200-2500"  ][histset.first], 1E3* _stitchznn["ZNN-LO-1200-2500"  ] * _xs["ZNN-LO-1200-2500"  ] / _sum["ZNN-LO-1200-2500"  ]);
    _cloned_hists["ZNN-LO"][ histset.first ]->Add( _cloned_hists["ZNN-LO-2500-Inf"   ][histset.first], 1E3* _stitchznn["ZNN-LO-2500-Inf"   ] * _xs["ZNN-LO-2500-Inf"   ] / _sum["ZNN-LO-2500-Inf"   ]);

  }


  //2D

  for (auto const& histset : _cloned_hists2D["ZNN-LO-100-200"]){
    
    _cloned_hists2D["ZNN-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZNN-LO_" + histset.first );   
    _cloned_hists2D["ZNN-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-100-200"    ][histset.first], 1E3* _stitchznn["ZNN-LO-100-200"    ] * _xs["ZNN-LO-100-200"    ] / _sum["ZNN-LO-100-200"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-200-400"    ][histset.first], 1E3* _stitchznn["ZNN-LO-200-400"    ] * _xs["ZNN-LO-200-400"    ] / _sum["ZNN-LO-200-400"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-400-600"    ][histset.first], 1E3* _stitchznn["ZNN-LO-400-600"    ] * _xs["ZNN-LO-400-600"    ] / _sum["ZNN-LO-400-600"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-600-800"    ][histset.first], 1E3* _stitchznn["ZNN-LO-600-800"    ] * _xs["ZNN-LO-600-800"    ] / _sum["ZNN-LO-600-800"    ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-800-1200"   ][histset.first], 1E3* _stitchznn["ZNN-LO-800-1200"   ] * _xs["ZNN-LO-800-1200"   ] / _sum["ZNN-LO-800-1200"   ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-1200-2500"  ][histset.first], 1E3* _stitchznn["ZNN-LO-1200-2500"  ] * _xs["ZNN-LO-1200-2500"  ] / _sum["ZNN-LO-1200-2500"  ]);
    _cloned_hists2D["ZNN-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN-LO-2500-Inf"   ][histset.first], 1E3* _stitchznn["ZNN-LO-2500-Inf"   ] * _xs["ZNN-LO-2500-Inf"   ] / _sum["ZNN-LO-2500-Inf"   ]);

  }


  ///////  W  /////////

  //Update to the same as the note (2017)
  _xs[ "WLN-LO-70-100" ] = 1296.0;
  _xs[ "WLN-LO-100-200"] = 1392.0;
  _xs[ "WLN-LO-200-400"] = 410.2;
  _xs[ "WLN-LO-400-600"] = 57.95;
  _xs[ "WLN-LO-600-800"] = 12.98;
  _xs[ "WLN-LO-800-1200"] = 5.39;
  _xs[ "WLN-LO-1200-2500"] = 1.08;
  _xs[ "WLN-LO-2500-Inf"] = 0.008098;

  //Ad hoc stitching weights
  _stitchw[ "WLN-LO-70-100" ] = 1.0;
  _stitchw[ "WLN-LO-100-200"] = 0.993;
  _stitchw[ "WLN-LO-200-400"] = 1.002;
  _stitchw[ "WLN-LO-400-600"] = 1.009;
  _stitchw[ "WLN-LO-600-800"] = 1.12;
  _stitchw[ "WLN-LO-800-1200"] = 1.202;
  _stitchw[ "WLN-LO-1200-2500"] = 1.332;
  _stitchw[ "WLN-LO-2500-Inf"] = 4.2;

  //If stitching required, set stitch_samplesw to true
  bool stitch_samplesw = false;
  if ( !stitch_samplesw ){
    for (auto& stitch:_stitchw){
      stitch.second = 1;
    }
  }

  for (auto const& histset : _cloned_hists["WLN-LO-70-100"]){ 
    
    _cloned_hists["WLN-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-LO_" + histset.first );   
    _cloned_hists["WLN-LO"][ histset.first ] ->Reset();
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-70-100"     ][histset.first],  1E3 * _stitchw["WLN-LO-70-100"     ] * _xs["WLN-LO-70-100"     ] / _sum["WLN-LO-70-100"     ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-100-200"    ][histset.first],  1E3 * _stitchw["WLN-LO-100-200"    ] * _xs["WLN-LO-100-200"    ] / _sum["WLN-LO-100-200"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-200-400"    ][histset.first],  1E3 * _stitchw["WLN-LO-200-400"    ] * _xs["WLN-LO-200-400"    ] / _sum["WLN-LO-200-400"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-400-600"    ][histset.first],  1E3 * _stitchw["WLN-LO-400-600"    ] * _xs["WLN-LO-400-600"    ] / _sum["WLN-LO-400-600"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-600-800"    ][histset.first],  1E3 * _stitchw["WLN-LO-600-800"    ] * _xs["WLN-LO-600-800"    ] / _sum["WLN-LO-600-800"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-800-1200"   ][histset.first],  1E3 * _stitchw["WLN-LO-800-1200"   ] * _xs["WLN-LO-800-1200"   ] / _sum["WLN-LO-800-1200"   ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-1200-2500"  ][histset.first],  1E3 * _stitchw["WLN-LO-1200-2500"  ] * _xs["WLN-LO-1200-2500"  ] / _sum["WLN-LO-1200-2500"  ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-2500-Inf"   ][histset.first],  1E3 * _stitchw["WLN-LO-2500-Inf"   ] * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN-LO-2500-Inf"   ]);

  }

  //2D
  for (auto const& histset : _cloned_hists2D["WLN-LO-70-100"]){ 
    
    _cloned_hists2D["WLN-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN-LO_" + histset.first );   
    _cloned_hists2D["WLN-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-70-100"     ][histset.first],  1E3 * _stitchw["WLN-LO-70-100"     ] * _xs["WLN-LO-70-100"     ] / _sum["WLN-LO-70-100"     ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-100-200"    ][histset.first],  1E3 * _stitchw["WLN-LO-100-200"    ] * _xs["WLN-LO-100-200"    ] / _sum["WLN-LO-100-200"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-200-400"    ][histset.first],  1E3 * _stitchw["WLN-LO-200-400"    ] * _xs["WLN-LO-200-400"    ] / _sum["WLN-LO-200-400"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-400-600"    ][histset.first],  1E3 * _stitchw["WLN-LO-400-600"    ] * _xs["WLN-LO-400-600"    ] / _sum["WLN-LO-400-600"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-600-800"    ][histset.first],  1E3 * _stitchw["WLN-LO-600-800"    ] * _xs["WLN-LO-600-800"    ] / _sum["WLN-LO-600-800"    ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-800-1200"   ][histset.first],  1E3 * _stitchw["WLN-LO-800-1200"   ] * _xs["WLN-LO-800-1200"   ] / _sum["WLN-LO-800-1200"   ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-1200-2500"  ][histset.first],  1E3 * _stitchw["WLN-LO-1200-2500"  ] * _xs["WLN-LO-1200-2500"  ] / _sum["WLN-LO-1200-2500"  ]);
    _cloned_hists2D["WLN-LO"][ histset.first ]->Add( _cloned_hists2D["WLN-LO-2500-Inf"   ][histset.first],  1E3 * _stitchw["WLN-LO-2500-Inf"   ] * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN-LO-2500-Inf"   ]);

  }
  

  ////////////////////////////////////////////////////////

  /////////////////////////
  //  LO HT Binned 2016  // 
  /////////////////////////


  ///////  DY  /////////  

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

  _sum["ZLL16-LO-100-200-TOT"    ] =  _sum["ZLL16-LO-100-200"    ] + _sum["ZLL16-LO-100-200-ext1"]; 
  _sum["ZLL16-LO-200-400-TOT"    ] =  _sum["ZLL16-LO-200-400"    ] + _sum["ZLL16-LO-200-400-ext1"];
  _sum["ZLL16-LO-400-600-TOT"    ] =  _sum["ZLL16-LO-400-600"    ] + _sum["ZLL16-LO-400-600-ext1"];

  for (auto const& histset : _cloned_hists["ZLL16-LO-70-100"]){
    
    _cloned_hists["ZLL16-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL16-LO_" + histset.first );   
    _cloned_hists["ZLL16-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-70-100"     ][histset.first], 1E3 * _xs["ZLL16-LO-70-100"     ] / _sum["ZLL16-LO-70-100"     ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-100-200"    ][histset.first], 1E3 * _xs["ZLL16-LO-100-200"    ] / _sum["ZLL16-LO-100-200-TOT"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-100-200-ext1"][histset.first], 1E3 * _xs["ZLL16-LO-100-200-ext1"] / _sum["ZLL16-LO-100-200-TOT"]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-200-400"    ][histset.first], 1E3 * _xs["ZLL16-LO-200-400"    ] / _sum["ZLL16-LO-200-400-TOT"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-200-400-ext1"][histset.first], 1E3 * _xs["ZLL16-LO-200-400-ext1"] / _sum["ZLL16-LO-200-400-TOT"]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-400-600"    ][histset.first], 1E3 * _xs["ZLL16-LO-400-600"    ] / _sum["ZLL16-LO-400-600-TOT"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-400-600-ext1"][histset.first], 1E3 * _xs["ZLL16-LO-400-600-ext1"] / _sum["ZLL16-LO-400-600-TOT"]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-600-800"    ][histset.first], 1E3 * _xs["ZLL16-LO-600-800"    ] / _sum["ZLL16-LO-600-800"    ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-800-1200"   ][histset.first], 1E3 * _xs["ZLL16-LO-800-1200"   ] / _sum["ZLL16-LO-800-1200"   ]);
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-1200-2500"  ][histset.first], 1E3 * _xs["ZLL16-LO-1200-2500"  ] / _sum["ZLL16-LO-1200-2500"  ]); 
    _cloned_hists["ZLL16-LO"][ histset.first ]->Add( _cloned_hists["ZLL16-LO-2500-Inf"   ][histset.first], 1E3 * _xs["ZLL16-LO-2500-Inf"   ] / _sum["ZLL16-LO-2500-Inf"   ]);

  }

  //2D
  for (auto const& histset : _cloned_hists2D["ZLL16-LO-70-100"]){
    
    _cloned_hists2D["ZLL16-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL16-LO_" + histset.first );   
    _cloned_hists2D["ZLL16-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-70-100"     ][histset.first], 1E3 * _xs["ZLL16-LO-70-100"     ] / _sum["ZLL16-LO-70-100"     ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-100-200"    ][histset.first], 1E3 * _xs["ZLL16-LO-100-200"    ] / _sum["ZLL16-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-100-200-ext1"][histset.first], 1E3 * _xs["ZLL16-LO-100-200-ext1"] / _sum["ZLL16-LO-100-200-TOT"]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-200-400"    ][histset.first], 1E3 * _xs["ZLL16-LO-200-400"    ] / _sum["ZLL16-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-200-400-ext1"][histset.first], 1E3 * _xs["ZLL16-LO-200-400-ext1"] / _sum["ZLL16-LO-200-400-TOT"]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-400-600"    ][histset.first], 1E3 * _xs["ZLL16-LO-400-600"    ] / _sum["ZLL16-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-400-600-ext1"][histset.first], 1E3 * _xs["ZLL16-LO-400-600-ext1"] / _sum["ZLL16-LO-400-600-TOT"]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-600-800"    ][histset.first], 1E3 * _xs["ZLL16-LO-600-800"    ] / _sum["ZLL16-LO-600-800"    ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-800-1200"   ][histset.first], 1E3 * _xs["ZLL16-LO-800-1200"   ] / _sum["ZLL16-LO-800-1200"   ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-1200-2500"  ][histset.first], 1E3 * _xs["ZLL16-LO-1200-2500"  ] / _sum["ZLL16-LO-1200-2500"  ]);
    _cloned_hists2D["ZLL16-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL16-LO-2500-Inf"   ][histset.first], 1E3 * _xs["ZLL16-LO-2500-Inf"   ] / _sum["ZLL16-LO-2500-Inf"   ]);

  }

  ///////  ZNN  /////////  

  //Cross-sections taken from Esh
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

  for (auto const& histset : _cloned_hists["ZNN16-LO-100-200"]){
    
    _cloned_hists["ZNN16-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZNN16-LO_" + histset.first );   
    _cloned_hists["ZNN16-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-100-200"    ][histset.first], 1E3 * _xs["ZNN16-LO-100-200"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-100-200-ext1"    ][histset.first], 1E3 * _xs["ZNN16-LO-100-200-ext1"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-200-400"    ][histset.first], 1E3 * _xs["ZNN16-LO-200-400"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-200-400-ext1"    ][histset.first], 1E3 * _xs["ZNN16-LO-200-400-ext1"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-400-600"    ][histset.first], 1E3 * _xs["ZNN16-LO-400-600"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-400-600-ext1"    ][histset.first], 1E3 * _xs["ZNN16-LO-400-600-ext1"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-600-800"    ][histset.first], 1E3 * _xs["ZNN16-LO-600-800"    ] / _sum["ZNN16-LO-600-800"    ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-800-1200"   ][histset.first], 1E3 * _xs["ZNN16-LO-800-1200"   ] / _sum["ZNN16-LO-800-1200"   ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-1200-2500"  ][histset.first], 1E3 * _xs["ZNN16-LO-1200-2500"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-1200-2500-ext1"  ][histset.first], 1E3 * _xs["ZNN16-LO-1200-2500-ext1"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["ZNN16-LO"][ histset.first ]->Add( _cloned_hists["ZNN16-LO-2500-Inf"   ][histset.first], 1E3 * _xs["ZNN16-LO-2500-Inf"   ] / _sum["ZNN16-LO-2500-Inf"   ]);

  }

  //2D
  for (auto const& histset : _cloned_hists2D["ZNN16-LO-100-200"]){    
    _cloned_hists2D["ZNN16-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZNN16-LO_" + histset.first );   
    _cloned_hists2D["ZNN16-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-100-200"    ][histset.first], 1E3 * _xs["ZNN16-LO-100-200"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-100-200-ext1"    ][histset.first], 1E3 * _xs["ZNN16-LO-100-200-ext1"    ] / _sum["ZNN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-200-400"    ][histset.first], 1E3 * _xs["ZNN16-LO-200-400"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-200-400-ext1"    ][histset.first], 1E3 * _xs["ZNN16-LO-200-400-ext1"    ] / _sum["ZNN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-400-600"    ][histset.first], 1E3 * _xs["ZNN16-LO-400-600"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-400-600-ext1"    ][histset.first], 1E3 * _xs["ZNN16-LO-400-600-ext1"    ] / _sum["ZNN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-600-800"    ][histset.first], 1E3 * _xs["ZNN16-LO-600-800"    ] / _sum["ZNN16-LO-600-800"    ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-800-1200"   ][histset.first], 1E3 * _xs["ZNN16-LO-800-1200"   ] / _sum["ZNN16-LO-800-1200"   ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-1200-2500"  ][histset.first], 1E3 * _xs["ZNN16-LO-1200-2500"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-1200-2500-ext1"  ][histset.first], 1E3 * _xs["ZNN16-LO-1200-2500-ext1"  ] / _sum["ZNN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["ZNN16-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN16-LO-2500-Inf"   ][histset.first], 1E3 * _xs["ZNN16-LO-2500-Inf"   ] / _sum["ZNN16-LO-2500-Inf"   ]);

  }


  ///////  W  /////////

  //Cross-sections take from Andreas's list
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

  _sum["WLN16-LO-100-200-TOT"    ] =  _sum["WLN16-LO-100-200"    ] + _sum["WLN16-LO-100-200-ext1"] + _sum["WLN16-LO-100-200-ext2"];
  _sum["WLN16-LO-200-400-TOT"    ] =  _sum["WLN16-LO-200-400"    ] + _sum["WLN16-LO-200-400-ext1"] + _sum["WLN16-LO-200-400-ext2"];
  _sum["WLN16-LO-400-600-TOT"    ] =  _sum["WLN16-LO-400-600"    ] + _sum["WLN16-LO-400-600-ext1"];
  _sum["WLN16-LO-600-800-TOT"    ] =  _sum["WLN16-LO-600-800"    ] + _sum["WLN16-LO-600-800-ext1"];
  _sum["WLN16-LO-800-1200-TOT"    ] =  _sum["WLN16-LO-800-1200"    ] + _sum["WLN16-LO-800-1200-ext1"];
  _sum["WLN16-LO-1200-2500-TOT"    ] =  _sum["WLN16-LO-1200-2500"    ] + _sum["WLN16-LO-1200-2500-ext1"];
  _sum["WLN16-LO-2500-Inf-TOT"    ] =  _sum["WLN16-LO-2500-Inf"    ] + _sum["WLN16-LO-2500-Inf-ext1"];

  
  //1D
  for (auto const& histset : _cloned_hists["WLN16-LO-70-100"]){ 
    _cloned_hists["WLN16-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN16-LO_" + histset.first );   
    _cloned_hists["WLN16-LO"][ histset.first ] ->Reset();
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-70-100"     ][histset.first],  1E3 * _xs["WLN16-LO-70-100"     ] / _sum["WLN16-LO-70-100"     ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-100-200"    ][histset.first],  1E3 * _xs["WLN16-LO-100-200"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-100-200-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-100-200-ext1"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-100-200-ext2"    ][histset.first],  1E3 * _xs["WLN16-LO-100-200-ext2"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-200-400"    ][histset.first],  1E3 * _xs["WLN16-LO-200-400"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-200-400-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-200-400-ext1"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-200-400-ext2"    ][histset.first],  1E3 * _xs["WLN16-LO-200-400-ext2"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-400-600"    ][histset.first],  1E3 * _xs["WLN16-LO-400-600"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-400-600-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-400-600-ext1"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-600-800"    ][histset.first],  1E3  * _xs["WLN16-LO-600-800"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-600-800-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-600-800-ext1"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-800-1200"   ][histset.first],  1E3  * _xs["WLN16-LO-800-1200"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-800-1200-ext1"   ][histset.first],  1E3 * _xs["WLN16-LO-800-1200-ext1"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-1200-2500"  ][histset.first],  1E3 * _xs["WLN16-LO-1200-2500"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-1200-2500-ext1"  ][histset.first],  1E3 * _xs["WLN16-LO-1200-2500-ext1"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-2500-Inf"   ][histset.first],  1E3 * _xs["WLN16-LO-2500-Inf"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);
    _cloned_hists["WLN16-LO"][ histset.first ]->Add( _cloned_hists["WLN16-LO-2500-Inf-ext1"   ][histset.first],  1E3 * _xs["WLN16-LO-2500-Inf-ext1"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);
  }

  //2D
  for (auto const& histset : _cloned_hists2D["WLN16-LO-70-100"]){ 
    _cloned_hists2D["WLN16-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN16-LO_" + histset.first );   
    _cloned_hists2D["WLN16-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-70-100"     ][histset.first],  1E3 * _xs["WLN16-LO-70-100"     ] / _sum["WLN16-LO-70-100"     ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-100-200"    ][histset.first],  1E3 * _xs["WLN16-LO-100-200"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-100-200-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-100-200-ext1"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-100-200-ext2"    ][histset.first],  1E3 * _xs["WLN16-LO-100-200-ext2"    ] / _sum["WLN16-LO-100-200-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-200-400"    ][histset.first],  1E3 * _xs["WLN16-LO-200-400"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-200-400-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-200-400-ext1"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-200-400-ext2"    ][histset.first],  1E3 * _xs["WLN16-LO-200-400-ext2"    ] / _sum["WLN16-LO-200-400-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-400-600"    ][histset.first],  1E3 * _xs["WLN16-LO-400-600"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-400-600-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-400-600-ext1"    ] / _sum["WLN16-LO-400-600-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-600-800"    ][histset.first],  1E3 * _xs["WLN16-LO-600-800"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-600-800-ext1"    ][histset.first],  1E3 * _xs["WLN16-LO-600-800-ext1"    ] / _sum["WLN16-LO-600-800-TOT"    ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-800-1200"   ][histset.first],  1E3 * _xs["WLN16-LO-800-1200"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-800-1200-ext1"   ][histset.first],  1E3 * _xs["WLN16-LO-800-1200-ext1"   ] / _sum["WLN16-LO-800-1200-TOT"   ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-1200-2500"  ][histset.first],  1E3 * _xs["WLN16-LO-1200-2500"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-1200-2500-ext1"  ][histset.first],  1E3 * _xs["WLN16-LO-1200-2500-ext1"  ] / _sum["WLN16-LO-1200-2500-TOT"  ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-2500-Inf"   ][histset.first],  1E3 * _xs["WLN16-LO-2500-Inf"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);
    _cloned_hists2D["WLN16-LO"][ histset.first ]->Add( _cloned_hists2D["WLN16-LO-2500-Inf-ext1"   ][histset.first],  1E3 * _xs["WLN16-LO-2500-Inf-ext1"   ] / _sum["WLN16-LO-2500-Inf-TOT"   ]);
  }


  ////////////////////////////////////////////////////////

  /////////////////////////
  //  LO HT Binned 2018  // 
  /////////////////////////

  //Use same cross section as for 2017

  ///////  W  /////////

  //1D
  for (auto const& histset : _cloned_hists["WLN18-LO-70-100"]){ 
    _cloned_hists["WLN18-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN18-LO_" + histset.first );   
    _cloned_hists["WLN18-LO"][ histset.first ] ->Reset();
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-70-100"     ][histset.first],  1E3 * _xs["WLN-LO-70-100"     ] / _sum["WLN18-LO-70-100"     ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-100-200"    ][histset.first],  1E3 * _xs["WLN-LO-100-200"    ] / _sum["WLN18-LO-100-200"    ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-200-400"    ][histset.first],  1E3 * _xs["WLN-LO-200-400"    ] / _sum["WLN18-LO-200-400"    ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-400-600"    ][histset.first],  1E3 * _xs["WLN-LO-400-600"    ] / _sum["WLN18-LO-400-600"    ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-600-800"    ][histset.first],  1E3 * _xs["WLN-LO-600-800"    ] / _sum["WLN18-LO-600-800"    ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-800-1200"   ][histset.first],  1E3 * _xs["WLN-LO-800-1200"   ] / _sum["WLN18-LO-800-1200"   ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-1200-2500"  ][histset.first],  1E3 * _xs["WLN-LO-1200-2500"  ] / _sum["WLN18-LO-1200-2500"  ]);
    _cloned_hists["WLN18-LO"][ histset.first ]->Add( _cloned_hists["WLN18-LO-2500-Inf"   ][histset.first],  1E3 * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN18-LO-2500-Inf"   ]);
  }

  //2D
  for (auto const& histset : _cloned_hists2D["WLN18-LO-70-100"]){    
    _cloned_hists2D["WLN18-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "WLN18-LO_" + histset.first );   
    _cloned_hists2D["WLN18-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-70-100"     ][histset.first],  1E3 * _xs["WLN-LO-70-100"     ] / _sum["WLN18-LO-70-100"     ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-100-200"    ][histset.first],  1E3 * _xs["WLN-LO-100-200"    ] / _sum["WLN18-LO-100-200"    ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-200-400"    ][histset.first],  1E3 * _xs["WLN-LO-200-400"    ] / _sum["WLN18-LO-200-400"    ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-400-600"    ][histset.first],  1E3 * _xs["WLN-LO-400-600"    ] / _sum["WLN18-LO-400-600"    ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-600-800"    ][histset.first],  1E3 * _xs["WLN-LO-600-800"    ] / _sum["WLN18-LO-600-800"    ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-800-1200"   ][histset.first],  1E3 * _xs["WLN-LO-800-1200"   ] / _sum["WLN18-LO-800-1200"   ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-1200-2500"  ][histset.first],  1E3 * _xs["WLN-LO-1200-2500"  ] / _sum["WLN18-LO-1200-2500"  ]);
    _cloned_hists2D["WLN18-LO"][ histset.first ]->Add( _cloned_hists2D["WLN18-LO-2500-Inf"   ][histset.first],  1E3 * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN18-LO-2500-Inf"   ]);

  }
  
  ///////  DY  /////////

  _sum["ZLL18-LO-400-600-TOT"    ] =  _sum["ZLL18-LO-400-600"    ] + _sum["ZLL18-LO-400-600-ext1"];

  //1D
  for (auto const& histset : _cloned_hists["ZLL18-LO-70-100"]){   
    _cloned_hists["ZLL18-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL18-LO_" + histset.first );   
    _cloned_hists["ZLL18-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-70-100"     ][histset.first], 1E3*  _xs["ZLL-LO-70-100"     ] / _sum["ZLL18-LO-70-100"     ]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-100-200"    ][histset.first], 1E3*  _xs["ZLL-LO-100-200"    ] / _sum["ZLL18-LO-100-200"    ]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-200-400"    ][histset.first], 1E3*  _xs["ZLL-LO-200-400"    ] / _sum["ZLL18-LO-200-400"    ]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-400-600"    ][histset.first], 1E3*  _xs["ZLL-LO-400-600"    ] / _sum["ZLL18-LO-400-600-TOT"    ]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-400-600-ext1"][histset.first], 1E3* _xs["ZLL-LO-400-600"] / _sum["ZLL18-LO-400-600-TOT"]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-600-800"    ][histset.first], 1E3*  _xs["ZLL-LO-600-800"    ] / _sum["ZLL18-LO-600-800"    ]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-800-1200"   ][histset.first], 1E3*  _xs["ZLL-LO-800-1200"   ] / _sum["ZLL18-LO-800-1200"   ]);
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-1200-2500"  ][histset.first], 1E3*  _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL18-LO-1200-2500"  ]); 
    _cloned_hists["ZLL18-LO"][ histset.first ]->Add( _cloned_hists["ZLL18-LO-2500-Inf"   ][histset.first], 1E3*  _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL18-LO-2500-Inf"   ]);

  }

  //2D
  for (auto const& histset : _cloned_hists2D["ZLL18-LO-70-100"]){
    _cloned_hists2D["ZLL18-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZLL18-LO_" + histset.first );   
    _cloned_hists2D["ZLL18-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-70-100"     ][histset.first], 1E3*  _xs["ZLL-LO-70-100"     ] / _sum["ZLL18-LO-70-100"     ]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-100-200"    ][histset.first], 1E3*  _xs["ZLL-LO-100-200"    ] / _sum["ZLL18-LO-100-200"    ]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-200-400"    ][histset.first], 1E3*  _xs["ZLL-LO-200-400"    ] / _sum["ZLL18-LO-200-400"    ]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-400-600"    ][histset.first], 1E3*  _xs["ZLL-LO-400-600"    ] / _sum["ZLL18-LO-400-600-TOT"    ]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-400-600-ext1"][histset.first], 1E3* _xs["ZLL-LO-400-600"] / _sum["ZLL18-LO-400-600-TOT"]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-600-800"    ][histset.first], 1E3*  _xs["ZLL-LO-600-800"    ] / _sum["ZLL18-LO-600-800"    ]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-800-1200"   ][histset.first], 1E3*  _xs["ZLL-LO-800-1200"   ] / _sum["ZLL18-LO-800-1200"   ]);
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-1200-2500"  ][histset.first], 1E3*  _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL18-LO-1200-2500"  ]); 
    _cloned_hists2D["ZLL18-LO"][ histset.first ]->Add( _cloned_hists2D["ZLL18-LO-2500-Inf"   ][histset.first], 1E3*  _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL18-LO-2500-Inf"   ]);
  }


  ///////  Z NU NU  /////////  

  //1D
  for (auto const& histset : _cloned_hists["ZNN18-LO-100-200"]){
    _cloned_hists["ZNN18-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZNN18-LO_" + histset.first );   
    _cloned_hists["ZNN18-LO"][ histset.first ] ->Reset();
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-100-200"    ][histset.first], 1E3* _xs["ZNN-LO-100-200"    ] / _sum["ZNN18-LO-100-200"    ]);
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-200-400"    ][histset.first], 1E3* _xs["ZNN-LO-200-400"    ] / _sum["ZNN18-LO-200-400"    ]);
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-400-600"    ][histset.first], 1E3* _xs["ZNN-LO-400-600"    ] / _sum["ZNN18-LO-400-600"    ]);
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-600-800"    ][histset.first], 1E3* _xs["ZNN-LO-600-800"    ] / _sum["ZNN18-LO-600-800"    ]);
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-800-1200"   ][histset.first], 1E3* _xs["ZNN-LO-800-1200"   ] / _sum["ZNN18-LO-800-1200"   ]);
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-1200-2500"  ][histset.first], 1E3* _xs["ZNN-LO-1200-2500"  ] / _sum["ZNN18-LO-1200-2500"  ]);
    _cloned_hists["ZNN18-LO"][ histset.first ]->Add( _cloned_hists["ZNN18-LO-2500-Inf"   ][histset.first], 1E3* _xs["ZNN-LO-2500-Inf"   ] / _sum["ZNN18-LO-2500-Inf"   ]);
  }

  //2D
  for (auto const& histset : _cloned_hists2D["ZNN18-LO-100-200"]){
    _cloned_hists2D["ZNN18-LO"][ histset.first ] = (TH2D*) histset.second->Clone( "ZNN18-LO_" + histset.first );   
    _cloned_hists2D["ZNN18-LO"][ histset.first ] ->Reset();
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-100-200"    ][histset.first], 1E3* _xs["ZNN-LO-100-200"    ] / _sum["ZNN18-LO-100-200"    ]);
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-200-400"    ][histset.first], 1E3* _xs["ZNN-LO-200-400"    ] / _sum["ZNN18-LO-200-400"    ]);
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-400-600"    ][histset.first], 1E3* _xs["ZNN-LO-400-600"    ] / _sum["ZNN18-LO-400-600"    ]);
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-600-800"    ][histset.first], 1E3* _xs["ZNN-LO-600-800"    ] / _sum["ZNN18-LO-600-800"    ]);
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-800-1200"   ][histset.first], 1E3* _xs["ZNN-LO-800-1200"   ] / _sum["ZNN18-LO-800-1200"   ]);
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-1200-2500"  ][histset.first], 1E3* _xs["ZNN-LO-1200-2500"  ] / _sum["ZNN18-LO-1200-2500"  ]);
    _cloned_hists2D["ZNN18-LO"][ histset.first ]->Add( _cloned_hists2D["ZNN18-LO-2500-Inf"   ][histset.first], 1E3* _xs["ZNN-LO-2500-Inf"   ] / _sum["ZNN18-LO-2500-Inf"   ]);
  }


}


//Evaluate the uncertainties on the 1D k-factors
void HiggsPlotting::EvaluateUncertainties(){

  std::vector<TString> histoSets = { "Default" , "Default_VTR", "MJJ-200-500",  "MJJ-500-1000",  "MJJ-1000-1500", "MJJ-1500-5000", "non-VBF"};

  for ( auto histoset : histoSets ){
    std::vector<std::string> systplots = {"gen_boson_pt", "gen_jetpt0"};
    
    for ( auto syst : systplots ){      
      if ( syst == "gen_jetpt0" && histoset != "non-VBF") continue;
      
      ////////////////////////////////////////////
      //                                        //
      //           SCALE UNCERTAINTIES          //
      //                                        //
      ////////////////////////////////////////////

      std::vector<TString> list = {"1","3","4","6"};//Labels for renormalisation and factorisation scales up and down
      
      for ( auto &j : list ) {
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleUncorrelated_LHEPt" + j);
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleCorrelated_LHEPt" + j);
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleZup_LHEPt" + j);
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH1D*) _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleWup_LHEPt" + j);
	  
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Reset();
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Reset();
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Reset();
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Reset();
	  
	TString nominal = "";

	for ( int i = 1;i<_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetNbinsX()+1;i++){      
	    
	  double r = 1;
	  if ( _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->GetBinContent(i) != 0 ){
	      
	    double wu = _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i);
	    double zu = _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i);
	    double wnom = _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetBinContent(i);
	    double znom = _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetBinContent(i);	    
	      
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
	      
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, val_uncorrelated );
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, val_correlated );
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, val_zup );
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, val_wup );
	      
	  }
	  else{
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, 1 );
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, 1 );
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, 1 );
	    _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, 1 );
	  }
	    
	}
      }

      ////////////////////////////////////////////
      //                                        //
      //            PDF UNCERTAINTIES           //
      //                                        //
      ////////////////////////////////////////////
          
      _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH1D*)_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_WLN");
      _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH1D*)_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_ZLL");
      _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH1D*)_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_WZ");
      _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
      _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
      _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
      
      ////////    W    ////////
      
      for ( int i = 1;i<_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	double sum2_pdf = 0;
	for ( int j = 1; j < 31; j++){	    
	  sum2_pdf += std::pow( 2*_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) - 2*_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i), 2);
	}
	double sd_alphas = 2*(_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i) - _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i))/2;
	
	double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	
	if ( _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 ){
	  _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	}

      }
	  
      ////////    DY    ////////
      
      for ( int i = 1;i<_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	double sum2_pdf = 0;
	for ( int j = 1; j < 31; j++){
	  sum2_pdf += std::pow( 2*_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) - 2*_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i), 2);
	}
	double sd_alphas = 2*(_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i) - _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i))/2;
	double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );

	if ( _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 ){
	  _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
	}
	
      }
	  
      ////////     W/Z     ////////

      for ( int i = 1;i<_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	double sum2_pdf = 0;
	for ( int j = 1; j < 31; j++){
	  sum2_pdf += std::pow( _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) - _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i), 2);
	}
	double sd_alphas = (_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i) - _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i))/2;
	double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	if ( _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i) != 0 )    
	  _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,sd);
      }      
	  
      //Create dummy PDF up and down histograms for the LO samples, which are just set to the central values (for simplicity)
      _cloned_hists["WLN-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WLN16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "16_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WLN18-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN18-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL18-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL18-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists["ZLL-LO"][ histoset + "_" + syst ]);
      _cloned_hists["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists["ZLL-LO"][ histoset + "_" + syst ]);
      
      //Create the final PDF Up and PDF Down systematic histograms for the NLO samples
      _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH1D*)_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up_WZ"));
      _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH1D*)_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down_WZ"));
      
      //Fill those histograms with the correct values (to mirror the format for the scale uncertainties, i.e. uncertainty histogram is central_val+sigma_deviation)
      for ( int i = 1;i<_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetNbinsX()+1;i++){
	
	double centralw = _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i);
	double centralz = _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i);
	double centralwz = _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i)/_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i);
	
	_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i, centralw + _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i, centralw - _cloned_hists["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i, centralz + _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i, centralz - _cloned_hists["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i, centralwz + _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	_cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i, centralwz - _cloned_hists["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i)   );
	
      }
    }
  }
}


//Evaluate the uncertainties on the 2D k-factors
void HiggsPlotting::EvaluateUncertainties2D(){

  std::vector<TString> histoSets = { "Default" , "Default_VTR","non-VBF"};

  for ( auto histoset : histoSets ){
    std::vector<std::string> systplots = {"gen_boson_pt_gen_mjj", "gen_boson_pt_gen_boson_eta"};
    if ( histoset == "non-VBF" ) systplots = {"gen_boson_pt_gen_jetpt0", "gen_boson_pt_gen_jet_multiplicity"};

    for ( auto syst : systplots ){

      ////////////////////////////////////////////
      //                                        //
      //           SCALE UNCERTAINTIES          //
      //                                        //
      ////////////////////////////////////////////
	
      std::vector<TString> list = {"1","3","4","6"}; //Labels for renormalisation and factorisation scales up and down
	
      for ( auto &j : list ) {
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleUncorrelated_LHEPt" + j);
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleCorrelated_LHEPt" + j);
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleZup_LHEPt" + j);
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->Clone("WZ-ScaleWup_LHEPt" + j);

	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst ]->Clone("WZ-ScaleUncorrelated_LHEPt" + j);
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst  ]->Clone("WZ-ScaleCorrelated_LHEPt" + j);
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst  ]->Clone("WZ-ScaleZup_LHEPt" + j);
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN-LO"][ histoset + "_" + syst ]->Clone("WZ-ScaleWup_LHEPt" + j);


	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst ]->Clone("WZ16-ScaleUncorrelated_LHEPt" + j);
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst  ]->Clone("WZ16-ScaleCorrelated_LHEPt" + j);
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst  ]->Clone("WZ16-ScaleZup_LHEPt" + j);
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN16-LO"][ histoset + "_" + syst ]->Clone("WZ16-ScaleWup_LHEPt" + j);

	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN18-LO"][ histoset + "_" + syst ]->Clone("WZ18-ScaleUncorrelated_LHEPt" + j);
	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ] = (TH2D*) _cloned_hists2D["WLN18-LO"][ histoset + "_" + syst  ]->Clone("WZ18-ScaleCorrelated_LHEPt" + j);
	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ] = (TH2D*) _cloned_hists2D["WLN18-LO"][ histoset + "_" + syst  ]->Clone("WZ18-ScaleZup_LHEPt" + j);
	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ] = (TH2D*) _cloned_hists2D["WLN18-LO"][ histoset + "_" + syst ]->Clone("WZ18-ScaleWup_LHEPt" + j);

	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Reset();
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Reset();
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Reset();
	_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Reset();
	  
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);

	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);

	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->Divide(_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->Divide(_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleWup_" + j ]->Divide(_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst ]);
	_cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_ScaleZup_" + j ]->Divide(_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst ]);
	  
	TString nominal = "";

	for ( int i = 1;i<_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetNbinsX()+1;i++){      
	  for ( int k = 1;k<_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetNbinsY()+1;k++){      
	      
	    double r = 1;
	    if ( _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_4" ]->GetBinContent(i,k) != 0 ){
	      
	      double wu = _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i,k);
	      double zu = _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_Scale_" + j ]->GetBinContent(i,k);
	      double wnom = _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetBinContent(i,k);
	      double znom = _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + nominal ]->GetBinContent(i,k);	    

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
		
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, k, val_uncorrelated );
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, k, val_correlated );
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, k, val_zup );
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, k, val_wup );
		
	    }
	    else{
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleUncorrelated_" + j ]->SetBinContent(i, k, 1 );
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleCorrelated_" + j ]->SetBinContent(i, k, 1 );
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleZup_" + j ]->SetBinContent(i, k, 1 );
	      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_ScaleWup_" + j ]->SetBinContent(i, k, 1 );

	    }
	      
	  }
	}
      }

      ////////////////////////////////////////////
      //                                        //
      //            PDF UNCERTAINTIES           //
      //                                        //
      ////////////////////////////////////////////

      _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_WLN");
      _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_ZLL");
      _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_ZNN");
      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ] = (TH2D*)_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->Clone( histoset + "_gen_boson_LHEPt_PDF_SD_WZ");

      _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
      _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
      _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();
      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Reset();

      ////////    W    ////////

      for ( int i = 1;i<_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	for ( int k = 1;k<_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	  double sum2_pdf = 0;
	  for ( int j = 1; j < 31; j++){	    
	    sum2_pdf += std::pow( 2*_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - 2*_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	  }
	  double sd_alphas = 2*(_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	  
	  double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	  
	  if ( _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
	    _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	}
      }

      ////////    DY    ////////
      
      for ( int i = 1;i<_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	for ( int k = 1;k<_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	  double sum2_pdf = 0;
	  for ( int j = 1; j < 31; j++){
	    sum2_pdf += std::pow( 2*_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - 2*_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	  }
	  double sd_alphas = 2*(_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	  double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	  if ( _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
	    _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	} 
      }

      ////////     ZNN     ////////


      for ( int i = 1;i<_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	for ( int k = 1;k<_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	  double sum2_pdf = 0;
	  for ( int j = 1; j < 31; j++){
	    sum2_pdf += std::pow( 2*_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - 2*_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	  }
	  double sd_alphas = 2*(_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	  double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	  if ( _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
	    _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	} 
      }

      ////////     W/Z     ////////
      
      for ( int i = 1;i<_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsX()+1;i++){
	for ( int k = 1;k<_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetNbinsY()+1;k++){
	  double sum2_pdf = 0;
	  for ( int j = 1; j < 31; j++){
	    sum2_pdf += std::pow( _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_0" ]->GetBinContent(i,k), 2);
	  }
	  double sd_alphas = (_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_32" ]->GetBinContent(i,k) - _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_31" ]->GetBinContent(i,k))/2;
	  double sd =  std::sqrt( sum2_pdf + sd_alphas*sd_alphas );
	  if ( _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k) != 0 )    
	    _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->SetBinContent(i,k,sd);
	}
      }
      
      //Create dummy PDF up and down histograms for the LO samples, which are just set to the central values (for simplicity)
            
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

      _cloned_hists2D["WLN18-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["WLN18-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Down"));
      _cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Down"));
      _cloned_hists2D["ZNN18-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZNN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["ZNN18-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZNN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "18_" + syst + "_PDF_SD_Down"));

      _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));

      _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);
      _cloned_hists2D["WZ-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists2D["ZLL-LO"][ histoset + "_" + syst ]);

      _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN16-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));

      _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);
      _cloned_hists2D["WZ16-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists2D["ZLL16-LO"][ histoset + "_" + syst ]);

      _cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN18-LO"][ histoset + "_" + syst + "" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));

      _cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_PDF_Up" ]->Divide(_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst ]);
      _cloned_hists2D["WZ18-LO"][ histoset + "_" + syst + "_PDF_Down" ]->Divide(_cloned_hists2D["ZLL18-LO"][ histoset + "_" + syst ]);

      //Create the final PDF Up and PDF Down systematic histograms for the NLO samples
      _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up"));
      _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down"));
      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]=(TH2D*)_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Up_WZ"));
      _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]=(TH2D*)_cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->Clone((histoset + "_" + syst + "_PDF_SD_Down_WZ"));
		
      //Fill those histograms with the correct values (to mirror the format for the scale uncertainties, i.e. uncertainty histogram is central_val+sigma_deviation)	
      for ( int i = 1;i<_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetNbinsX()+1;i++){
	for ( int k = 1;k<_cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetNbinsY()+1;k++){
	    
	  double centralw = _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	  double centralz = _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	  double centralznn = _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	  double centralwz = _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k)/_cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "" ]->GetBinContent(i,k);
	    
	  _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralw + _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralw - _cloned_hists2D["WLN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralz + _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralz - _cloned_hists2D["ZLL-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralznn + _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralznn - _cloned_hists2D["ZNN-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Up" ]->SetBinContent(i,k, centralwz + _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	  _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_Down" ]->SetBinContent(i,k, centralwz - _cloned_hists2D["WZ-NLO-LHEPt"][ histoset + "_" + syst + "_PDF_SD" ]->GetBinContent(i,k)   );
	    
	}
      }
    }
  }     
}

//Plot the various generator-level control distributions and evaluate the 1D and 2D k-factors
void HiggsPlotting::PlotAllHistograms(){

  Plotter plotter(_cmd, _helper);
  
  //By default some histograms are also saved to a .ROOT file, as well as being plotted as .png or .pdf
  std::string filename = "ROOT_histograms.root";

  //Loop over all LO DY samples, plot the histograms, and save to the .ROOT file 
  //(skipping the PDF and Scale uncertainty plots, which are dummy anyway)
  for (auto const& histset : _cloned_hists["ZLL-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first, true );
    plotter.SaveToFile(histset.second ,histset.first, filename, "ZLL-LO" );
  }

  //Do the same for the LO ZNN samples
  for (auto const& histset : _cloned_hists["ZNN-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZNN-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZNN-LO-" + histset.first, true );
    plotter.SaveToFile(histset.second ,histset.first, filename, "ZNN-LO" );
  }

  //Do the same for the LO W samples
  for (auto const& histset : _cloned_hists["WLN-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "WLN-LO-" + histset.first );
    plotter.Draw( histset.second , "", "WLN-LO-" + histset.first, true );
  }

  //Do the same for the NLO W samples
  for (auto const& histset : _cloned_hists["WLN-NLO-LHEPt"]){
    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "WLN-NLO-LHEPt-" + histset.first );
    plotter.Draw( histset.second , "", "WLN-NLO-LHEPt-" + histset.first,true );
  }

  //Do the same for the NLO DY samples
  for (auto const& histset : _cloned_hists["ZLL-NLO-LHEPt"]){
    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-NLO-LHEPt-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-NLO-LHEPt-" + histset.first,true );
    plotter.SaveToFile(histset.second , histset.first, filename, "ZLL-NLO-LHEPt" );
  }

  //Do the same for the NLO ZNN samples
  for (auto const& histset : _cloned_hists["ZNN-NLO-LHEPt"]){
    if ( histset.first.SubString("PDF_")!= "" ) continue;
    plotter.Draw( histset.second , "", "ZNN-NLO-LHEPt-" + histset.first );
    plotter.Draw( histset.second , "", "ZNN-NLO-LHEPt-" + histset.first,true );
    plotter.SaveToFile(histset.second , histset.first, filename, "ZNN-NLO-LHEPt" );
  }


  /////////////////////////////////////////////////
  //                                             //
  //            EVALUATE THE K-FACTORS           //
  //                                             //
  /////////////////////////////////////////////////


  //// LHE PT k-factors
  std::vector<TString> processes = {"WLN","ZLL","ZNN"};
  std::vector<TString> analyses = {"vbf", "nonvbf", "VTR"};

  //1D k-factors. Kept here as useful tools for understanding, but not eventually used in the analysis
  for ( auto analysis : analyses  ){
    for ( auto process : processes  ){

      ////////////////////////////////
      //Select the correct histograms for the correct analysis and set the correct names for the output histograms, based on the analysis in question

      for (auto const& histset : _cloned_hists[ process + "-NLO-LHEPt"]){
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

	if (hist.find("PDF")!=std::string::npos && hist.find("PDF_Up")==std::string::npos && hist.find("PDF_Down")==std::string::npos) continue;

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
	if ( hist.find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	else if ( hist.find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	else if ( hist.find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
	else if ( hist.find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
	else if (  hist.find("Scale" )!=std::string::npos ) continue;
	if ( hist.find("Scale" )!=std::string::npos ) histset.second->Scale(2); //To correct for the factor 2 bug in the generator samples
	
	if ( hist.find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
	else if ( hist.find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";
	

	std::string saveprocess = "zjet";
	std::string saveanalysis = "VBF";
	if ( process == "WLN" ) saveprocess = "wjet";
	if ( process == "ZNN" ) saveprocess = "znn";
	if ( process == "WZ" ) saveprocess = "wz";
	if ( analysis == "nonvbf" ) saveanalysis = "nonVBF";
	if ( analysis == "VTR" ) saveanalysis = "VTR";

	////////////////////////////////
	
	//Calculate the k-factor ("ratio") and save it to file
	
	TH1D * ratio = plotter.DrawRatio( histset.second , _cloned_hists[process+"-LO"][ histset.first ], "", "Ratio-"+process+"-LHEPt-" + histset.first );
	
	plotter.SaveToFile(ratio, savename, "kfactor_"+saveanalysis+"_"+saveprocess, systname );
      }      
    }
  }
  
  //2D k-factors, the main set of k-factors used in the analysis
  processes = {"WLN","ZLL","ZNN","WZ"};
  for ( auto analysis : analyses  ){
    for ( auto process : processes  ){

      ////////////////////////////////
      //Select the correct histograms for the correct analysis and set the correct names for the output histograms, based on the analysis in question

      for (auto const& histset : _cloned_hists2D[ process + "-NLO-LHEPt"]){
	std::string hist = std::string(histset.first);	
	if (analysis == "nonvbf" && hist.find("non-VBF")==std::string::npos){
	    continue;
	}

	if (analysis == "VTR" && !(hist.find("VTR")!=std::string::npos && (hist.find("gen_boson_pt_gen_mjj")!=std::string::npos||hist.find("gen_boson_pt_gen_boson_eta")!=std::string::npos))){
	  continue;
	}

	if (analysis == "vbf"     
	    && !((hist.find("Default")!=std::string::npos&&hist.find("Default_VTR")==std::string::npos) && (hist.find("gen_boson_pt_gen_mjj")!=std::string::npos||hist.find("gen_boson_pt_gen_boson_eta")!=std::string::npos))){
	  continue;
	}
	
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
	
	
	if ( hist.find("Scale" )!=std::string::npos ){
	  if ( hist.find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	  else if ( hist.find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	  else if ( hist.find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
	  else if ( hist.find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
	  else continue;
	  histset.second->Scale(2); //To correct for the factor 2 bug in the generator samples
	}	  
	  
	if ( hist.find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
	else if ( hist.find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";

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
	else{
	  if (hist.find("gen_boson_eta")!=std::string::npos)
	    saveanalysis = saveanalysis + "_gen_boson_eta";
	}

	////////////////////////////////
	
	//Calculate the k-factor ("ratio") and save it to file.
	//The k-factors are also evaluated using the 2016 and 2018 LO samples	
	//Another k-factor is evaluted (ratio_zll_over_znn) where the NLO DY sample (x1.98) is divided by the LO ZNN sample (as a cross-check)

	TH2D * ratio = plotter.DrawRatio( histset.second , _cloned_hists2D[process+"-LO"][ histset.first ], "", "Ratio-"+process+"-LHEPt-" + histset.first );
	TH2D * ratio16 = plotter.DrawRatio( histset.second , _cloned_hists2D[process+"16-LO"][ histset.first ], "", "Ratio-"+process+"16-LHEPt-" + histset.first );
	TH2D * ratio18 = plotter.DrawRatio( histset.second , _cloned_hists2D[process+"18-LO"][ histset.first ], "", "Ratio-"+process+"18-LHEPt-" + histset.first );
	TH2D * ratio_zll_over_znn = 0;
	if ( process == "ZNN" ){
	  TH2D * scaled_hist = (TH2D*)_cloned_hists2D["ZLL-NLO-LHEPt"][ histset.first ]->Clone( "ZLL-NLO-LHEPt" + histset.first + "_scaled" );
	  scaled_hist->Scale(1.98);
	  ratio_zll_over_znn = plotter.DrawRatio( scaled_hist , _cloned_hists2D[process+"-LO"][ histset.first ], "", "Ratio-"+process+"-LHEPt-" + histset.first );  
	}
	
	if ( analysis == "VTR" ) saveanalysis = "VTR";
	    plotter.SaveToFile(ratio, savename, "2Dkfactor_"+saveanalysis+"_"+saveprocess, systname );
	    plotter.SaveToFile(ratio16, savename, "2Dkfactor16_"+saveanalysis+"_"+saveprocess, systname );
	    plotter.SaveToFile(ratio18, savename, "2Dkfactor18_"+saveanalysis+"_"+saveprocess, systname );
	    if ( process == "ZNN" ){
	      plotter.SaveToFile(ratio_zll_over_znn, savename, "2Dkfactor_"+saveanalysis+"_"+saveprocess + "_zll", systname );
	    }
	}

    }
  }
  
  //Some further interesting comparison plots, but not relevant for the main k-factor production

  std::vector< TH1D*> zlhe = {_cloned_hists["ZLL-LO"]["Default_gen_boson_pt"], _cloned_hists["ZLL-NLO-LHEPt"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> wlhe = {_cloned_hists["WLN-LO"]["Default_gen_boson_pt"], _cloned_hists["WLN-NLO-LHEPt"]["Default_gen_boson_pt"]};
  std::vector< TH1D*>  wz_scale_LHEPt;
  std::vector<TH2D*> wz_scale_LHEPt2D;
  for ( int i = 0;i<9;i++){
    if ( i == 1 || i == 3 || i == 4 || i == 6 ){
      wz_scale_LHEPt.push_back( _cloned_hists["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_ScaleUncorrelated_" + std::to_string(i) ]);
      wz_scale_LHEPt2D.push_back( _cloned_hists2D["WZ-NLO-LHEPt"][ "Default_gen_boson_pt_gen_mjj_ScaleUncorrelated_" + std::to_string(i) ]);
    }   
  }

  plotter.SetLegendXY( 0.65, 0.5, 0.75, 0.8 );
  std::vector< TString > zleg = {"LO", "NLO"};
  plotter.Draw( zlhe , zleg, "z-lhept" , true, true);
  plotter.Draw( wlhe , zleg, "w-lhept" , true, true);

  std::vector<TString> wzuncert = {"WZRatioUncorr-Renorm-Down","WZRatioUncorr-Fact-Down","WZRatioUncorr-Fact-Up", "WZRatioUncorr-Renorm-Up"};
  plotter.SaveToFile( wz_scale_LHEPt, wzuncert,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt2D, wzuncert,"2D-wz-ratio-uncertainty","kfactors_shape");
 


}
