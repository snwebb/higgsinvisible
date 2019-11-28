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
  
}

void HiggsPlotting::LoadAllHistograms(){

  //map of short name and filename
  std::map<TString,TString> filenames;

  //  filenames[ "ZLL-NLO-orig" ]     = "MC_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8-Skimmed.root";
  filenames[ "ZLL-NLO-orig" ]     = "MC_DYJetsToLL_M-50-amcatnloFXFX.root";
  filenames[ "ZLL-NLO-ext" ] = "MC_DYJetsToLL_M-50-amcatnloFXFX-ext.root";
  filenames[ "ZLL-LO-70-100" ] = "MC_DYJetsToLL_M-50_HT-70to100.root";
  filenames[ "ZLL-LO-100-200" ] = "MC_DYJetsToLL_M-50_HT-100to200.root";
  filenames[ "ZLL-LO-100-200-ext" ] = "MC_DYJetsToLL_M-50_HT-100to200-ext.root";
  filenames[ "ZLL-LO-200-400" ] = "MC_DYJetsToLL_M-50_HT-200to400.root";
  filenames[ "ZLL-LO-200-400-ext" ] = "MC_DYJetsToLL_M-50_HT-200to400-ext.root";
  filenames[ "ZLL-LO-400-600" ] = "MC_DYJetsToLL_M-50_HT-400to600.root";
  filenames[ "ZLL-LO-400-600-ext" ] = "MC_DYJetsToLL_M-50_HT-400to600-ext.root";
  filenames[ "ZLL-LO-600-800" ] = "MC_DYJetsToLL_M-50_HT-600to800.root";
  filenames[ "ZLL-LO-800-1200" ] = "MC_DYJetsToLL_M-50_HT-800to1200.root";
  filenames[ "ZLL-LO-1200-2500" ] = "MC_DYJetsToLL_M-50_HT-1200to2500.root";
  filenames[ "ZLL-LO-2500-Inf" ] = "MC_DYJetsToLL_M-50_HT-2500toInf.root";

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
  
  filenames[ "WLN-NLO-0J" ] = "MC_WJetsToLNu_0J_TuneCP5-amcatnloFXFX.root";
  filenames[ "WLN-NLO-1J" ] = "MC_WJetsToLNu_1J_TuneCP5-amcatnloFXFX-Skimmed.root";
  filenames[ "WLN-NLO-2J" ] = "MC_WJetsToLNu_2J_TuneCP5-amcatnloFXFX.root";
  
  filenames[ "WLN-NLO-Pt-100-250" ] = "MC_WJetsToLNu_Pt-100To250-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-250-400" ] = "MC_WJetsToLNu_Pt-250To400-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-400-600" ] = "MC_WJetsToLNu_Pt-400To600-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-600-Inf" ] = "MC_WJetsToLNu_Pt-600ToInf-amcatnloFXFX-pythia8.root";
  filenames[ "WLN-NLO-Pt-100-250-ext1" ] = "MC_WJetsToLNu_Pt-100To250-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-Pt-250-400-ext1" ] = "MC_WJetsToLNu_Pt-250To400-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-Pt-400-600-ext1" ] = "MC_WJetsToLNu_Pt-400To600-amcatnloFXFX-pythia8-ext1.root";
  filenames[ "WLN-NLO-Pt-600-Inf-ext1" ] = "MC_WJetsToLNu_Pt-600ToInf-amcatnloFXFX-pythia8-ext1.root";

  filenames[ "WLN-LO-70-100" ] = "MC_WJetsToLNu_HT-70To100_TuneCP5.root";
  filenames[ "WLN-LO-100-200" ] = "MC_WJetsToLNu_HT-100To200_TuneCP5.root";
  filenames[ "WLN-LO-200-400" ] = "MC_WJetsToLNu_HT-200To400_TuneCP5.root";
  filenames[ "WLN-LO-400-600" ] = "MC_WJetsToLNu_HT-400To600_TuneCP5.root";
  filenames[ "WLN-LO-600-800" ] = "MC_WJetsToLNu_HT-600To800_TuneCP5.root";
  filenames[ "WLN-LO-800-1200" ] = "MC_WJetsToLNu_HT-800To1200_TuneCP5.root";
  filenames[ "WLN-LO-1200-2500" ] = "MC_WJetsToLNu_HT-1200To2500_TuneCP5.root";
  filenames[ "WLN-LO-2500-Inf" ] = "MC_WJetsToLNu_HT-2500ToInf_TuneCP5.root";

  // filenames[ "WLN-LO-Pt-100-200" ] = "MC_WJetsToLNu_Pt-100To200-madgraphMLM-pythia8.root";
  // filenames[ "WLN-LO-Pt-200-Inf" ] = "MC_WJetsToLNu_Pt-200ToInf-madgraphMLM-pythia8.root";

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


  std::vector<std::string> plots = {"gen_boson_pt", "gen_boson_eta", "gen_mjj", "gen_detajj", "gen_dphijj", "gen_mindphi_jetmet", "LHE_HT", "gen_events","n_jets", "gen_jetpt0"};

  //  std::vector<std::string> histoSets = { "Default", "All", "Default-Mjj-200-500" };
  std::vector<std::string> histoSets = { "Default", "All" ,  "MJJ-200-500",  "MJJ-500-1000",  "MJJ-1000-1500", "MJJ-1500-5000", "non-VBF"};
  //  std::vector<std::string> histoSets = { "Default", "All"};

  //then load into clonemap with short name and list of hists

  TH1D * loadHist = 0;
  TFile * loadFile = 0;

  TString filepath = "/vols/cms/snwebb/InvisibleOutput/Merged/";

  for (auto const& filename : filenames){
    
    loadFile = new TFile ( filepath + filename.second, "READ" );
    
    for ( auto histoset : histoSets ){
      std::string getname = histoset;
      //      if ( histoset == "Default" ) getname = "Default_BARE";
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

      
      //Uncertainties    
      loadHist = 0;
      std::string loadname = "";
      std::vector<std::string> systplots = {"gen_boson_pt", "gen_jetpt0"};
      for ( auto syst : systplots ){
	if ( syst == "gen_jetpt0" && histoset != "non-VBF") continue;
	for ( int i = 0;i<9;i++){
	  loadname = (getname + "/" + getname + "_"+syst+"_Scale_" + std::to_string(i) );
	  if ( std::string(filename.first).find("-LO-")!=std::string::npos ) loadname = (getname + "/" + getname + "_" + syst );
	  loadHist = (TH1D*) loadFile->Get( loadname.c_str() );
	  if ( loadHist != 0 ){ 
	    _cloned_hists[ filename.first ][ histoset + "_" + syst+"_Scale_" + std::to_string(i) ]  = (TH1D*) loadHist->Clone( ( filename.first + histoset + "_"+syst+"_Scale_" + std::to_string(i) ) );
	  }
	  else{
	    
	    //	    std::cout << "getname err = " << loadname << " - " << filename.first << std::endl;
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

  RebinValues[ "All_LHE_HT" ] = 1;

  //  double bins[13] = {0,70,120,170,220,270,320,370,470,600,750,900,1050};


  double bins[15] = {0,70,100,120,150,170,220,270,320,370,470,600,750,900,1050};

  //  double binsmjj[12] = {0,100,200,300,400,500,750,1000,1500,2000,3000,3500};
  for(auto &histsets : _cloned_hists) {
    for(auto &plot : histsets.second) {

      if ( std::string(plot.first).find("gen_boson_pt")==std::string::npos &&  plot.first != "Default_gen_mjj"){
	if ( RebinValues.count(plot.first)>0 )   plot.second->Rebin( RebinValues[ plot.first ]  ) ;
      }
      
      else if ( std::string(plot.first).find("gen_boson_pt")!=std::string::npos ){
	plot.second =  (TH1D*) plot.second->Rebin( 14, plot.first + "_rebinnned" , bins ) ;
	plot.second->Scale( 1,"width" );
      }
      else if ( plot.first == "Default_gen_mjj" ){
	  //	  plot.second =  (TH1D*) plot.second->Rebin( 11, plot.first + "_rebinnned" , binsmjj ) ;
	  //	  plot.second->Scale( 1,"width" );
      }

    }
  }
  
  
}

void HiggsPlotting::CombineHistograms(){

  std::map<TString, double> _xs;
  std::map<TString, double> _sum;
  std::map<TString, double> _num;

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



std::cout << std::fixed <<  "ZLL-NLO-LHEPt-1J-50-150-TOT "       <<     _num[      "ZLL-NLO-LHEPt-1J-50-150-TOT"  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-1J-150-250-TOT "	 << 	_num[   "ZLL-NLO-LHEPt-1J-150-250-TOT"	  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-1J-250-400-TOT "	 << 	_num[   "ZLL-NLO-LHEPt-1J-250-400-TOT"	  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-1J-400-Inf-TOT "	 << 	_num[   "ZLL-NLO-LHEPt-1J-400-Inf-TOT"	  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-2J-50-150-TOT " 	 << 	_num[   "ZLL-NLO-LHEPt-2J-50-150-TOT" 	  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-2J-150-250-TOT "	 << 	_num[   "ZLL-NLO-LHEPt-2J-150-250-TOT"	  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-2J-250-400-TOT "	 << 	_num[   "ZLL-NLO-LHEPt-2J-250-400-TOT"	  ]  << std::endl;
std::cout << std::fixed <<  "ZLL-NLO-LHEPt-2J-400-Inf-TOT "      <<     _num[     "ZLL-NLO-LHEPt-2J-400-Inf-TOT"  ]  << std::endl;

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

  std::cout << std::fixed << "WLN-NLO-LHEPt-1J-50-150-TOT " << _num["WLN-NLO-LHEPt-1J-50-150-TOT" ]  << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-1J-100-150-TOT "<< _num["WLN-NLO-LHEPt-1J-100-150-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-1J-150-250-TOT "<< _num["WLN-NLO-LHEPt-1J-150-250-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-1J-250-400-TOT "<< _num["WLN-NLO-LHEPt-1J-250-400-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-1J-400-Inf-TOT "<< _num["WLN-NLO-LHEPt-1J-400-Inf-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-2J-50-150-TOT " << _num["WLN-NLO-LHEPt-2J-50-150-TOT" ]  << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-2J-100-150-TOT "<< _num["WLN-NLO-LHEPt-2J-100-150-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-2J-150-250-TOT "<< _num["WLN-NLO-LHEPt-2J-150-250-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-2J-250-400-TOT "<< _num["WLN-NLO-LHEPt-2J-250-400-TOT" ] << std::endl;
  std::cout << std::fixed << "WLN-NLO-LHEPt-2J-400-Inf-TOT "<< _num["WLN-NLO-LHEPt-2J-400-Inf-TOT" ] << std::endl;


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

 ////////////////////////////////////////////////////////

  ////////////////////
  //  LO HT Binned  // 
  ////////////////////


  ///////  Z  /////////  

  _xs[ "ZLL-LO-70-100" ] = 1.47E+02;
  _xs[ "ZLL-LO-100-200"] = 1.62E+02;
  _xs[ "ZLL-LO-100-200-ext"] = 1.61E+02;
  _xs[ "ZLL-LO-200-400"] = 4.84E+01;
  _xs[ "ZLL-LO-200-400-ext"] = 4.85E+01;
  _xs[ "ZLL-LO-400-600"] = 7.06E+00;
  _xs[ "ZLL-LO-400-600-ext"] = 7.03E+00;
  _xs[ "ZLL-LO-600-800"] = 1.75E+00;
  _xs[ "ZLL-LO-800-1200"] = 7.96E-01;
  _xs[ "ZLL-LO-1200-2500"] = 1.93E-01;
  _xs[ "ZLL-LO-2500-Inf"] = 3.47E-03;

  _sum["ZLL-LO-100-200-TOT"    ] =  _sum["ZLL-LO-100-200"    ] + _sum["ZLL-LO-100-200-ext"];
  _sum["ZLL-LO-200-400-TOT"    ] =  _sum["ZLL-LO-200-400"    ] + _sum["ZLL-LO-200-400-ext"];
  _sum["ZLL-LO-400-600-TOT"    ] =  _sum["ZLL-LO-400-600"    ] + _sum["ZLL-LO-400-600-ext"];
  _num["ZLL-LO-100-200-TOT"    ] =  _num["ZLL-LO-100-200"    ] + _num["ZLL-LO-100-200-ext"];
  _num["ZLL-LO-200-400-TOT"    ] =  _num["ZLL-LO-200-400"    ] + _num["ZLL-LO-200-400-ext"];
  _num["ZLL-LO-400-600-TOT"    ] =  _num["ZLL-LO-400-600"    ] + _num["ZLL-LO-400-600-ext"];

  for (auto const& histset : _cloned_hists["ZLL-LO-70-100"]){
    
    _cloned_hists["ZLL-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-LO_" + histset.first );   
    _cloned_hists["ZLL-LO"][ histset.first ] ->Reset();
    //    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-70-100"     ][histset.first], 1E3* _xs["ZLL-LO-70-100"     ] / _sum["ZLL-LO-70-100"     ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200"    ][histset.first], 1E3* _xs["ZLL-LO-100-200"    ] / _sum["ZLL-LO-100-200-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200-ext"][histset.first], 1E3* _xs["ZLL-LO-100-200-ext"] / _sum["ZLL-LO-100-200-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400"    ][histset.first], 1E3* _xs["ZLL-LO-200-400"    ] / _sum["ZLL-LO-200-400-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400-ext"][histset.first], 1E3* _xs["ZLL-LO-200-400-ext"] / _sum["ZLL-LO-200-400-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600"    ][histset.first], 1E3* _xs["ZLL-LO-400-600"    ] / _sum["ZLL-LO-400-600-TOT"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600-ext"][histset.first], 1E3* _xs["ZLL-LO-400-600-ext"] / _sum["ZLL-LO-400-600-TOT"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-600-800"    ][histset.first], 1E3* _xs["ZLL-LO-600-800"    ] / _sum["ZLL-LO-600-800"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-800-1200"   ][histset.first], 1E3* _xs["ZLL-LO-800-1200"   ] / _sum["ZLL-LO-800-1200"   ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-1200-2500"  ][histset.first], 1E3* _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL-LO-1200-2500"  ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-2500-Inf"   ][histset.first], 1E3* _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL-LO-2500-Inf"   ]);

  }

  ///////  W  /////////

  _xs[ "WLN-LO-70-100" ] = 1.47E+01;
  _xs[ "WLN-LO-100-200"] = 1.39E+03;
  _xs[ "WLN-LO-200-400"] = 4.03E+02;
  _xs[ "WLN-LO-400-600"] = 5.82E+01;
  _xs[ "WLN-LO-600-800"] = 1.29E+01;
  _xs[ "WLN-LO-800-1200"] = 5.49E+00;
  _xs[ "WLN-LO-1200-2500"] = 1.092E+00;
  _xs[ "WLN-LO-2500-Inf"] = 8.19E-03;

  for (auto const& histset : _cloned_hists["WLN-LO-70-100"]){ 
    
    _cloned_hists["WLN-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-LO_" + histset.first );   
    _cloned_hists["WLN-LO"][ histset.first ] ->Reset();
    //    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-70-100"     ][histset.first],  1E3 * _xs["WLN-LO-70-100"     ] / _sum["WLN-LO-70-100"     ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-100-200"    ][histset.first],  1E3 * _xs["WLN-LO-100-200"    ] / _sum["WLN-LO-100-200"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-200-400"    ][histset.first],  1E3 * _xs["WLN-LO-200-400"    ] / _sum["WLN-LO-200-400"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-400-600"    ][histset.first],  1E3 * _xs["WLN-LO-400-600"    ] / _sum["WLN-LO-400-600"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-600-800"    ][histset.first],  1E3 * _xs["WLN-LO-600-800"    ] / _sum["WLN-LO-600-800"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-800-1200"   ][histset.first],  1E3 * _xs["WLN-LO-800-1200"   ] / _sum["WLN-LO-800-1200"   ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-1200-2500"  ][histset.first],  1E3 * _xs["WLN-LO-1200-2500"  ] / _sum["WLN-LO-1200-2500"  ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-2500-Inf"   ][histset.first],  1E3 * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN-LO-2500-Inf"   ]);

  }
  

  // for (auto const& histset : _cloned_hists["WLN-LO-Pt-100-200"]){
    
  //   _cloned_hists["WLN-LO-Pt"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-LO-Pt-100-200_" + histset.first  );   
  //   _cloned_hists["WLN-LO-Pt"][ histset.first ]->Reset();

  //   _cloned_hists["WLN-LO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-LO-Pt-100-200" ][histset.first]  , 1E0 * _xs["WLN-LO-Pt-100-200"     ] / _sum["WLN-LO-Pt-100-200"     ] );
  //   _cloned_hists["WLN-LO-Pt"][ histset.first ]->Add( _cloned_hists["WLN-LO-Pt-200-Inf" ][histset.first]  , 1E0 * _xs["WLN-LO-Pt-200-Inf"     ] / _sum["WLN-LO-Pt-200-Inf"     ] );
   
  // }
  



}



void HiggsPlotting::EvaluateUncertainties(){

  std::vector<TString> sets = {"Pt","LHEPt"};
  //  std::vector<TString> sets = {"LHEPt"};
  for ( auto setname : sets  ){
    
    
    std::vector<TString> histoSets = { "Default" ,  "MJJ-200-500",  "MJJ-500-1000",  "MJJ-1000-1500", "MJJ-1500-5000", "non-VBF"};
    //std::vector<TString> histoSets = { "Default"};
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
	//	std::cout << setname << " - " << histoset + "_" + syst + "_ScaleUncorrelated_" + j << " - " << std::endl;	
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

	    // std::cout << setname << " - " << histoset + "_" + syst + nominal << " - " << j << std::endl;
	    // std::cout << "bin " << i << " - ratio " << r << " ( "<<wnom/2<<"/"<<(znom/2)<<" ) " << " , " << r_wup << " ( "<<wu<<"/"<<zu<<" ) " << std::endl;



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
	  
	  // std::cout << "WLN-NLO-" + setname << " - " <<  histoset + "_" + syst + "_PDF" << std::endl;	  
	  // std::cout << "PT:::: sumpdf, alhpas " << sd_pdf << " - " << sd_alphas << std::endl;
	  
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
	    //	    std::cout << "aaaaaaa: " << 2*_cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "_PDF_" + std::to_string(j) ]->GetBinContent(i) << " - " << _cloned_hists["WLN-NLO-" + setname][ histoset + "_" + syst + "" ]->GetBinContent(i) << std::endl;
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


void HiggsPlotting::PlotAllHistograms(){

  Plotter plotter(_cmd, _helper);

  for (auto const& histset : _cloned_hists["ZLL-LO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    if ( histset.first.SubString("Scale_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first, true );
  }

  for (auto const& histset : _cloned_hists["ZLL-NLO"]){
    if ( histset.first.SubString("PDF_") != "" ) continue;
    plotter.Draw( histset.second , "", "ZLL-NLO-" + histset.first );
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
  }

  for (auto const& histset : _cloned_hists["WLN-NLO"]){
    if ( histset.first == "Default_gen_boson_pt" || histset.first == "Default_gen_mjj"){
      plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "Ratio-WLN-" + histset.first );
    }
  }
  /*  
  for (auto const& histset : _cloned_hists["WLN-NLO-Pt"]){
    if ( histset.first == "Default_gen_boson_pt" || histset.first == "Default_gen_mjj" || histset.first == "MJJ-200-500"){
      //Set LO stats to zero
      for (int i = 1;i<_cloned_hists["WLN-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	_cloned_hists["WLN-LO"][ histset.first ]->SetBinError(i,0);
      //    plotter.SaveToFile(plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "Ratio-WLN-Pt-" + histset.first ), "NLO_kFac_WLN-Pt-binned-" +  histset.first );
    }
  }

  for (auto const& histset : _cloned_hists["WLN-NLO-Pt"]){
    if ( histset.first == "MJJ-200-500"){
      for (int i = 1;i<_cloned_hists["WLN-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	_cloned_hists["WLN-LO"][ histset.first ]->SetBinError(i,0);
      //      plotter.SaveToFile(plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "RatioMJJ200-WLN-Pt-" + histset.first ), "kfactor_vbf_mjj_200_500" );
    }
  }

  for (auto const& histset : _cloned_hists["ZLL-NLO-Pt"]){
    if ( histset.first == "Default_gen_boson_pt" || histset.first == "Default_gen_mjj"){
      
      for (int i = 1;i<_cloned_hists["WLN-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	_cloned_hists["ZLL-LO"][ histset.first ]->SetBinError(i,0);
      //      plotter.SaveToFile(plotter.DrawRatio( histset.second , _cloned_hists["ZLL-LO"][ histset.first ], "", "Ratio-ZLL-Pt-" + histset.first ), "NLO_kFac_ZLL-Pt-binned-" +  histset.first );
      
    }
  }

  */
  //// LHE PT k-factors
  //  std::vector<TString> sets = {"LHEPt"};
  std::vector<TString> sets = {"Pt", "LHEPt"};
  //  std::vector<TString> sets = {"Pt"};
  for ( auto setname : sets  ){
    for (auto const& histset : _cloned_hists["WLN-NLO-" + setname]){
      if (std::string(histset.first).find("non-VBF")!=std::string::npos) continue;
      //      if ( std::string(histset.first).find("MJJ")!=std::string::npos && std::string(histset.first).find("gen_boson_pt")!=std::string::npos){
      if ( (std::string(histset.first).find("MJJ")!=std::string::npos||std::string(histset.first).find("Default")!=std::string::npos) && std::string(histset.first).find("gen_boson_pt")!=std::string::npos){
	if (std::string(histset.first).find("PDF")!=std::string::npos && std::string(histset.first).find("PDF_Up")==std::string::npos && std::string(histset.first).find("PDF_Down")==std::string::npos) continue;
	
	for (int i = 1;i<_cloned_hists["WLN-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	  _cloned_hists["WLN-LO"][ histset.first ]->SetBinError(i,0);
	std::string savename = "kfactor_vbf_mjj_";
	if ( std::string(histset.first).find("MJJ-200-500_gen_boson_pt" )!=std::string::npos ) savename += "200_500";
	if ( std::string(histset.first).find("MJJ-500-1000_gen_boson_pt" )!=std::string::npos ) savename += "500_1000";
	if ( std::string(histset.first).find("MJJ-1000-1500_gen_boson_pt" )!=std::string::npos ) savename += "1000_1500";
	if ( std::string(histset.first).find("MJJ-1500-5000_gen_boson_pt" )!=std::string::npos ) savename += "1500_5000";
	if ( std::string(histset.first).find("Default_gen_boson_pt" )!=std::string::npos ) savename = "kfactor_vbf_inclusive";
	std::string systname = "kfactors_shape";

	if ( setname == "LHEPt" ){
	  if ( std::string(histset.first).find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	  else if ( std::string(histset.first).find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	  else if ( std::string(histset.first).find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
	  else if ( std::string(histset.first).find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
	  else if (  std::string(histset.first).find("Scale" )!=std::string::npos ) continue;
	  if ( std::string(histset.first).find("Scale" )!=std::string::npos ) histset.second->Scale(2);
	}
	if ( setname == "Pt" ){
	  if ( std::string(histset.first).find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	  else if ( std::string(histset.first).find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	  else if ( std::string(histset.first).find("Scale_5" )!=std::string::npos ) systname += "_Fact_Up";
	  else if ( std::string(histset.first).find("Scale_7" )!=std::string::npos ) systname += "_Renorm_Up";
	  else if (  std::string(histset.first).find("Scale" )!=std::string::npos ) continue;
	}

	
	if ( std::string(histset.first).find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
	else if ( std::string(histset.first).find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";
	
	//Get smoothed histos
	TH1D * ratio = plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "Ratio-WLN-"+setname+"-" + histset.first );
	TH1D * histo_smoothed =  (TH1D*)ratio->Clone( "WLN-NLO-" + setname + "_" +  histset.first + "_smoothed" );
	TH1D * histo_fit =  (TH1D*)ratio->Clone( "WLN-NLO-" + setname + "_" +  histset.first + "_fit" );
	histo_smoothed->Smooth(1,"");


      double split = 370;
      double start = 70;
      if ( std::string(histset.first).find("Scale")!=std::string::npos )
	start = 150;
      TF1 * pol3 = new TF1("pol3","pol3",start,split);
      TF1 * pol0 = new TF1("pol0","pol0",split,1050);
      histo_fit->Fit(pol0, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)>split)
	  histo_fit->SetBinContent(i,pol0->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }
      histo_fit->Fit(pol3, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)<split)
	  histo_fit->SetBinContent(i,pol3->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }


	if ( setname == "LHEPt" ){	
	  plotter.SaveToFile(ratio, savename, "kfactor_VBF_wjet", systname );
	  plotter.SaveToFile(histo_smoothed, savename+"_smoothed", "kfactor_VBF_wjet", systname );
	  if ( std::string(histset.first).find("Scale")==std::string::npos  )
	    plotter.SaveToFile(histo_fit, savename+"_fit", "kfactor_VBF_wjet", systname );
	}
	else if ( setname == "Pt" ){
	  plotter.SaveToFile(ratio, savename, "PtBinned_kfactor_VBF_wjet", systname );
	  plotter.SaveToFile(histo_smoothed, savename+"_smoothed", "PtBinned_kfactor_VBF_wjet", systname );	  
	  if ( std::string(histset.first).find("Scale")==std::string::npos  )
	    plotter.SaveToFile(histo_fit, savename+"_fit", "PtBinned_kfactor_VBF_wjet", systname );	  
	}
      }
    }
  }



  for (auto const& histset : _cloned_hists["WLN-NLO-LHEPt"]){
    if (std::string(histset.first).find("non-VBF")!=std::string::npos){
      if (std::string(histset.first).find("PDF")!=std::string::npos && std::string(histset.first).find("PDF_Up")==std::string::npos && std::string(histset.first).find("PDF_Down")==std::string::npos) continue;

      for (int i = 1;i<_cloned_hists["WLN-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	_cloned_hists["WLN-LO"][ histset.first ]->SetBinError(i,0);
      std::string savename = "kfactor_nonvbf_";
      if ( std::string(histset.first).find("gen_boson_pt")!=std::string::npos) savename += "boson_pt";
      if ( std::string(histset.first).find("gen_jetpt0")!=std::string::npos) savename += "gen_jetp0";

      std::string systname = "kfactors_shape";
      if ( std::string(histset.first).find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
      else if ( std::string(histset.first).find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
      else if ( std::string(histset.first).find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
      else if ( std::string(histset.first).find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
      else if (  std::string(histset.first).find("Scale" )!=std::string::npos ) continue;
      if ( std::string(histset.first).find("Scale" )!=std::string::npos ) histset.second->Scale(2);

      if ( std::string(histset.first).find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
      else if ( std::string(histset.first).find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";

      //Get smoothed histos

      //	TF1 * pol2 = new TF1("pol2","1/([0]*(x^2)+[1]*(x)+[2])",170,1050);
      //      TF1 * pol2 = new TF1("pol2","([0]*1/x)+[1])",170,1050);
      TH1D * ratio = plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "Ratio-WLN-LHEPt-" + histset.first );

      TH1D * histo_smoothed = (TH1D*)ratio->Clone( "WLN-NLO-LHEPt" +  histset.first + "_smoothed" );
      TH1D * histo_fit =  (TH1D*)ratio->Clone( "WLN-NLO-LHEPt" + histset.first + "_fit" );
      histo_smoothed->Smooth(1,"");

      double split = 370;
      double start = 70;
      if ( std::string(histset.first).find("Scale")!=std::string::npos )
	start = 150;

      TF1 * pol3 = new TF1("pol3","pol3",start,split);
      TF1 * pol0 = new TF1("pol0","pol0",split,1050);
      histo_fit->Fit(pol0, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)>split)
	  histo_fit->SetBinContent(i,pol0->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }
      histo_fit->Fit(pol3, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)<split)
	  histo_fit->SetBinContent(i,pol3->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }


      plotter.SaveToFile(ratio, savename, "kfactor_nonVBF_wjet", systname );
      plotter.SaveToFile(histo_smoothed, savename + "_smoothed", "kfactor_nonVBF_wjet", systname );
      if ( std::string(histset.first).find("Scale")==std::string::npos  )  plotter.SaveToFile(histo_fit, savename+"_fit", "kfactor_nonVBF_wjet", systname );
    }
  }

  for ( auto setname : sets  ){
    for (auto const& histset : _cloned_hists["ZLL-NLO-" + setname]){
    if (std::string(histset.first).find("non-VBF")!=std::string::npos) continue;
    //    if ( std::string(histset.first).find("MJJ")!=std::string::npos && std::string(histset.first).find("gen_boson_pt")!=std::string::npos){
      if ( (std::string(histset.first).find("MJJ")!=std::string::npos||std::string(histset.first).find("Default")!=std::string::npos) && std::string(histset.first).find("gen_boson_pt")!=std::string::npos){
      if (std::string(histset.first).find("PDF")!=std::string::npos && std::string(histset.first).find("PDF_Up")==std::string::npos && std::string(histset.first).find("PDF_Down")==std::string::npos) continue;

      for (int i = 1;i<_cloned_hists["ZLL-LO"][ histset.first ]->GetNbinsX()+1;i++)    	
	_cloned_hists["ZLL-LO"][ histset.first ]->SetBinError(i,0);
      std::string savename = "kfactor_vbf_mjj_";
      if ( std::string(histset.first).find("MJJ-200-500_gen_boson_pt" )!=std::string::npos ) savename += "200_500";
      if ( std::string(histset.first).find("MJJ-500-1000_gen_boson_pt" )!=std::string::npos ) savename += "500_1000";
      if ( std::string(histset.first).find("MJJ-1000-1500_gen_boson_pt" )!=std::string::npos ) savename += "1000_1500";
      if ( std::string(histset.first).find("MJJ-1500-5000_gen_boson_pt" )!=std::string::npos ) savename += "1500_5000";
      if ( std::string(histset.first).find("Default_gen_boson_pt" )!=std::string::npos ) savename = "kfactor_vbf_inclusive";

      std::string systname = "kfactors_shape";
      if ( setname == "LHEPt" ){
	if ( std::string(histset.first).find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	else if ( std::string(histset.first).find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	else if ( std::string(histset.first).find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
	else if ( std::string(histset.first).find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
	else if (  std::string(histset.first).find("Scale" )!=std::string::npos ) continue;
	  if ( std::string(histset.first).find("Scale" )!=std::string::npos ) histset.second->Scale(2);
      }
      if ( setname == "Pt" ){
	if ( std::string(histset.first).find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
	else if ( std::string(histset.first).find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
	else if ( std::string(histset.first).find("Scale_5" )!=std::string::npos ) systname += "_Fact_Up";
	else if ( std::string(histset.first).find("Scale_7" )!=std::string::npos ) systname += "_Renorm_Up";
	else if (  std::string(histset.first).find("Scale" )!=std::string::npos ) continue;
      }


      if ( std::string(histset.first).find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
      else if ( std::string(histset.first).find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";
      //	TF1 * pol2 = new TF1("pol2","([0]*1/x)+[1])",170,1050);
	//      	TF1 * pol2 = new TF1("pol2","1/([0]*(x^2)+[1]*(x)+[2])",170,1050);
      //		TF1 * pol2 = new TF1("pol2","pol2",170,1050);


      TH1D * ratio = plotter.DrawRatio( histset.second , _cloned_hists["ZLL-LO"][ histset.first ], "", "Ratio-ZLL-"+setname+"-" + histset.first );
      TH1D * histo_smoothed =  (TH1D*)ratio->Clone( "ZLL-NLO-" + setname +  histset.first + "_smoothed" );
      TH1D * histo_fit =  (TH1D*)ratio->Clone( "ZLL-NLO-" + setname + "_" +  histset.first + "_fit" );
      histo_smoothed->Smooth(1,"");

      double split = 370;
      double start = 70;
      if ( std::string(histset.first).find("Scale")!=std::string::npos )
	start = 150;

      TF1 * pol3 = new TF1("pol3","pol3",start,split);
      TF1 * pol0 = new TF1("pol0","pol0",split,1050);
      histo_fit->Fit(pol0, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)>split)
	  histo_fit->SetBinContent(i,pol0->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }
      histo_fit->Fit(pol3, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)<split)
	  histo_fit->SetBinContent(i,pol3->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }


	if ( setname == "LHEPt" ){	
	  plotter.SaveToFile(ratio, savename, "kfactor_VBF_zjet", systname );
	  plotter.SaveToFile(histo_smoothed, savename+"_smoothed", "kfactor_VBF_zjet", systname );
	  if ( std::string(histset.first).find("Scale")==std::string::npos  )
	    plotter.SaveToFile(histo_fit, savename+"_fit", "kfactor_VBF_zjet", systname );
	}
	else if ( setname == "Pt" ){
	  plotter.SaveToFile(ratio, savename, "PtBinned_kfactor_VBF_zjet", systname );
	  plotter.SaveToFile(histo_smoothed, savename+"_smoothed", "PtBinned_kfactor_VBF_zjet", systname );	  
	  if ( std::string(histset.first).find("Scale")==std::string::npos  )
	    plotter.SaveToFile(histo_fit, savename+"_fit", "PtBinned_kfactor_VBF_zjet", systname );	  
	}


    }
  }
  }
  for (auto const& histset : _cloned_hists["ZLL-NLO-LHEPt"]){
    if (std::string(histset.first).find("non-VBF")!=std::string::npos){
      if (std::string(histset.first).find("PDF")!=std::string::npos && std::string(histset.first).find("PDF_Up")==std::string::npos && std::string(histset.first).find("PDF_Down")==std::string::npos) continue;

      for (int i = 1;i<_cloned_hists["ZLL-LO"][ histset.first ]->GetNbinsX()+1;i++)    
	_cloned_hists["ZLL-LO"][ histset.first ]->SetBinError(i,0);
      std::string savename = "kfactor_nonvbf_";
      if ( std::string(histset.first).find("gen_boson_pt")!=std::string::npos) savename += "boson_pt";
      if ( std::string(histset.first).find("gen_jetpt0")!=std::string::npos) savename += "gen_jetp0";

      std::string systname = "kfactors_shape";
      if ( std::string(histset.first).find("Scale_1" )!=std::string::npos ) systname += "_Renorm_Down";
      else if ( std::string(histset.first).find("Scale_3" )!=std::string::npos ) systname += "_Fact_Down";
      else if ( std::string(histset.first).find("Scale_4" )!=std::string::npos ) systname += "_Fact_Up";
      else if ( std::string(histset.first).find("Scale_6" )!=std::string::npos ) systname += "_Renorm_Up";
      else if (  std::string(histset.first).find("Scale" )!=std::string::npos ) continue;

      if ( std::string(histset.first).find("Scale" )!=std::string::npos ) histset.second->Scale(2);

      if ( std::string(histset.first).find("PDF_Up" )!=std::string::npos ) systname += "_PDF_Up";
      else if ( std::string(histset.first).find("PDF_Down" )!=std::string::npos ) systname += "_PDF_Down";
      //	TF1 * pol2 = new TF1("pol2","([0]*1/x)+[1])",170,1050);
	//	TF1 * pol2 = new TF1("pol2","1/([0]*(x^2)+[1]*(x)+[2])",170,1050);
      //		TF1 * pol2 = new TF1("pol2","pol2",170,1050);

      TH1D * ratio = plotter.DrawRatio( histset.second , _cloned_hists["ZLL-LO"][ histset.first ], "", "Ratio-ZLL-LHEPt-" + histset.first );
      TH1D * histo_smoothed =  (TH1D*)ratio->Clone( "ZLL-NLO-LHEPt" +  histset.first + "_smoothed" );
      TH1D * histo_fit =  (TH1D*)ratio->Clone( "ZLL-NLO-LHEPt" +  histset.first + "_fit" );

      histo_smoothed->Smooth(1,"");


      double split =370;
      double start = 70;
      if ( std::string(histset.first).find("Scale")!=std::string::npos )
	start = 150;

      TF1 * pol3 = new TF1("pol3","pol3",start,split);
      TF1 * pol0 = new TF1("pol0","pol0",split,1050);
      histo_fit->Fit(pol0, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)>split)
	  histo_fit->SetBinContent(i,pol0->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }
      histo_fit->Fit(pol3, "LRQ0"); 
      for (int i = 2;i<histo_fit->GetNbinsX()+1;i++){
	if ( histo_fit->GetXaxis()->GetBinLowEdge(i+1)<split)
	  histo_fit->SetBinContent(i,pol3->Eval(histo_fit->GetXaxis()->GetBinCenter(i)));
      }


      plotter.SaveToFile(ratio, savename, "kfactor_nonVBF_zjet", systname );
      plotter.SaveToFile(histo_smoothed, savename + "_smoothed", "kfactor_nonVBF_zjet", systname);
      if ( std::string(histset.first).find("Scale")==std::string::npos  )
	plotter.SaveToFile(histo_fit, savename+"_fit", "kfactor_nonVBF_zjet", systname );
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

  //  std::vector<TString> sets = {"Pt","LHEPt"};


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
  
  // plotter.SaveToFile( z_scale_LHEPt, zuncert, "kfactor_VBF_wjet");
  // plotter.SaveToFile( w_scale_LHEPt, wuncert,"kfactor_VBF_wjet");
  plotter.SaveToFile( wz_scale_LHEPt, wzuncert,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt_Correlated, wzuncert_corr,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt_Wup, wzuncert_wup,"wz-ratio-uncertainty","kfactors_shape");
  plotter.SaveToFile( wz_scale_LHEPt_Zup, wzuncert_zup,"wz-ratio-uncertainty","kfactors_shape");
  
  // plotter_uncertainties.Draw( z_scale , w_scaleleg, "z-scale", false, false, "HIST");
  // plotter_uncertainties.Draw( wz_scale , w_scaleleg, "wz-scale", false, false, "HIST");
  // plotter_uncertainties.Draw( w_scale , w_scaleleg, "w-scale", false, false,"HIST");
  
  for ( int i = 0;i<102;i++){
    z_pdf.push_back( _cloned_hists["ZLL-NLO-Pt"][ "Default_gen_boson_pt_PDF_" + std::to_string(i) ]);
    z_pdfleg.push_back( TString(std::to_string(i) ));
  }   
  //  plotter.Draw( z_pdf , z_pdfleg, "z-pdf");



  plotter.Draw( z_mjj , zleg, "z-mjj" , true, true);
  plotter.Draw( w_mjj , zleg, "w-mjj" , true, true);
  
  plotter.Draw( z_orig , zleg, "z-pt-orig" , true, true);
  plotter.Draw( w_orig , zleg, "w-pt-orig" , true, true);
  
  plotter.Draw( z , zleg, "z-pt", true );
  plotter.Draw( w , zleg, "w-pt", true );


  
  //Andreas studies
  std::vector<TH1D*> vec1 = {_cloned_hists["WLN-NLO-Pt"]["Default_gen_boson_pt"],_cloned_hists["WLN-NLO-LHEPt"]["Default_gen_boson_pt"]};
  std::vector<TH1D*> vec5 = {_cloned_hists["WLN-NLO-Pt"]["All_gen_boson_pt"],_cloned_hists["WLN-NLO-LHEPt"]["All_gen_boson_pt"]};
  std::vector<TString> leg1 = {"pt binned","pt+jet binned"};
  plotter.Draw( vec1, leg1, "w-nlo-ratio" , true, true);
  plotter.Draw( vec1, leg1, "w-nlo-ratio" , true, false);
  plotter.Draw( vec5, leg1, "w-nlo-ratio-all" , true, true);
  plotter.Draw( vec5, leg1, "w-nlo-ratio-all" , true, false);


  std::vector<TH1D*> vec2 = {_cloned_hists["WLN-NLO-Pt"]["Default_n_jets"],_cloned_hists["WLN-NLO-LHEPt"]["Default_n_jets"]};
  plotter.Draw( vec2, leg1, "w-nlo-njetratio" , true, false);


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


  


  //  output->Close();



}
