/******************************************************************************
 HGC analysis code
 Samuel Webb
 Imperial College
***************************************************************************/

// Time-stamp: <2021-07-15 09:52:51 (snwebb)>

#include "HiggsInvisible.h"

void HiggsInvisible::MakeAllHistograms( std::vector<std::string> &HistoSets){

  std::cout << "Creating All Histograms" << std::endl;

  for (auto& names : HistoSets ){

    _fout->mkdir(names.c_str());
    _fout->cd(names.c_str());

    LoadHistoTemplates ( names );
  }

}

void HiggsInvisible::LoadHistoTemplates( std::string name ){

  //Create empty histograms. The histograms created depend on the "name" variable (which is defined in the HistoSets vector in HiggsInvisible.cxx).
  //The histograms are stored in a 2D map, either called _cloned_hists (for 1D histograms) or _cloned_hists2D (for 2D histograms)

  //Bin definitions for histograms with variable bin widths
  double mjjbins[7] = {0,200,500,1000,1500,2000,5000};
  double mjjbins_a[9] = {200,400,600,900,1200,1500,2000,2700,3500};
  int nmjjbins_a = 8;
  int nmjjbins = 6;
  double vtrmjjbins[4] = {0,600,900,5000};
  double jetptbins[5] = {0,200,400,600,1200};
  double njetbins[8] = {-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5};
  double ptbins[15] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 400, 520, 640, 760, 880,1100}; //andreas's binnings
  double ptbins_a[10] = {200, 240, 260, 280, 300, 340, 400, 500, 740, 1000}; //andreas's binnings
  int nptbins = 14;
  int nptbins_a = 9;
  double etabins[7] = {0,0.5,1.0,1.5,2.0,3.0,5.0};

  if ( name.find("Default")!=std::string::npos ||  name == "All"){

    if ( name == "Default_VTR" ){
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj").c_str(), ";Boson p_{T};M_{jj}", nptbins, ptbins,3,vtrmjjbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_a").c_str(), ";Boson p_{T};M_{jj}", nptbins_a, ptbins_a,3,vtrmjjbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta" ] = new TH2D ( (name + "_gen_boson_pt_gen_boson_eta").c_str(), ";Boson p_{T};Boson #eta", nptbins, ptbins, 6, etabins);  
    }
    else{
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj").c_str(), ";Boson p_{T};M_{jj}", nptbins, ptbins,nmjjbins,mjjbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_a").c_str(), ";Boson p_{T};M_{jj}", nptbins_a, ptbins_a,nmjjbins_a,mjjbins_a);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta" ] = new TH2D ( (name + "_gen_boson_pt_gen_boson_eta").c_str(), ";Boson p_{T};Boson #eta", nptbins, ptbins, 6, etabins);  
    }

    _cloned_hists[ name ] [ "gen_dilep_pt_bare" ] = new TH1D ( (name + "_gen_dilep_pt_bare").c_str(), ";Di lep p_{T};Number of Events", 120,0,1200 );  
    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    _cloned_hists[ name ] [ "gen_boson_eta" ] = new TH1D ( (name + "_gen_boson_eta").c_str(), ";Boson #eta;Number of Events", 40,-8,8 );  
    _cloned_hists[ name ] [ "gen_boson_mass" ] = new TH1D ( (name + "_gen_boson_mass").c_str(), ";Boson Mass;Number of Events", 200,0,200);  
    _cloned_hists[ name ] [ "gen_mjj" ] = new TH1D ( (name + "_gen_mjj").c_str(), ";M_{jj};Number of Events", 10000,0,10000 );  
    _cloned_hists[ name ] [ "gen_detajj" ] = new TH1D ( (name + "_gen_detajj").c_str(), ";#Delta#eta_{jj};Number of Events", 50,0,7 );  
    _cloned_hists[ name ] [ "gen_dphijj" ] = new TH1D ( (name + "_gen_dphijj").c_str(), ";#Delta#phi_{jj};Number of Events", 50,0, M_PI );  
    _cloned_hists[ name ] [ "gen_mindphi_jetmet" ] = new TH1D ( (name + "_gen_mindphi_jetmet").c_str(), ";min-#Delta#phi(j,p_{T}^{V});Number of Events", 50,0, M_PI );  
    _cloned_hists[ name ] [ "LHE_HT" ] = new TH1D ( (name + "_LHE_HT").c_str(), ";HT;Number of Events",5000,0,5000);  
    _cloned_hists[ name ] [ "LHE_Vpt" ] = new TH1D ( (name + "_LHE_Vpt").c_str(), ";LHE Vp_{T};Number of Events",5000,0,5000);  
    _cloned_hists[ name ] [ "gen_weight" ] = new TH1D ( (name + "_gen_weight").c_str(), ";weight;Number of Events",100,-100000,100000);  
    _cloned_hists[ name ] [ "gen_jetpt0" ] = new TH1D ( (name + "_gen_jetpt0").c_str(), ";jet 0 p_{T};Number of Events", 300,0,600 );  
    _cloned_hists[ name ] [ "n_jets" ] = new TH1D ( (name + "_n_jets").c_str(), ";nJets;Number of Events", 10,-0.5,9.5 );  
    _cloned_hists[ name ] [ "gen_dressed_lepton_eta" ] = new TH1D ( (name + "_gen_dressed_lepton_eta").c_str(), ";Leading lepton #eta;Number of Events",100,-8,8);  
    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] = new TH1D ( (name + "_gen_dressed_lepton_pt").c_str(), ";Leading lepton p_{T};Number of Events",120,0,1200);  
    _cloned_hists[ name ] [ "gen_lepton_eta0" ] = new TH1D ( (name + "_gen_lepton_eta0").c_str(), ";Leading lepton #eta;Number of Events",100,-8,8);  
    _cloned_hists[ name ] [ "gen_lepton_eta1" ] = new TH1D ( (name + "_gen_lepton_eta1").c_str(), ";Sub-leading lepton #eta;Number of Events",100,-8,8);  
    _cloned_hists[ name ] [ "gen_lepton_pt0" ] = new TH1D ( (name + "_gen_lepton_pt0").c_str(), ";Leading lepton p_{T};Number of Events",120,0,1200);  
    _cloned_hists[ name ] [ "gen_lepton_pt1" ] = new TH1D ( (name + "_gen_lepton_pt1").c_str(), ";Sub-leading lepton p_{T};Number of Events",120,0,1200);  

  }

  if ( name == "All" ){
    _cloned_hists[ name ] [ "gen_events" ] = new TH1D ( (name + "_gen_events").c_str(), ";;Number of Events",3,0.5,3.5 );  
  }

  if ( name.find("MJJ")!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
  }

  //Histograms for the scale and PDF uncertainties for the 1D histograms
  if ( name.find("Default")!=std::string::npos || name.find("MJJ")!=std::string::npos){

    for ( int i = 0;i<9;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    }

    for ( int i = 0;i<102;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    }

  }

  //Histograms for the scale and PDF uncertainties for the 2D histograms
  if ( name.find("Default")!=std::string::npos){

    if ( name == "Default_VTR" ){
      for ( int i = 0;i<9;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins, ptbins,3,vtrmjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_a_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins_a, ptbins_a,3,vtrmjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta_Scale_"+std::to_string(i)] = new TH2D ( (name + "_gen_boson_pt_gen_boson_eta_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};Boson #eta", nptbins, ptbins, 6, etabins);  
      }
      for ( int i = 0;i<102;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins ,ptbins,3,vtrmjjbins );  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_a_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins_a ,ptbins_a, 3, vtrmjjbins );  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta_PDF_"+std::to_string(i)] = new TH2D ( (name + "_gen_boson_pt_gen_boson_eta_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};Boson #eta", nptbins, ptbins, 6, etabins);  
      }
    }else{
      for ( int i = 0;i<9;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins, ptbins,nmjjbins,mjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_a_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins_a, ptbins_a,nmjjbins_a,mjjbins_a);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta_Scale_"+std::to_string(i)] = new TH2D ( (name + "_gen_boson_pt_gen_boson_eta_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};Boson #eta", nptbins, ptbins, 6, etabins);  
      }
      for ( int i = 0;i<102;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins, ptbins,nmjjbins,mjjbins );  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_a_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", nptbins_a, ptbins_a,nmjjbins_a,mjjbins_a );  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta_PDF_"+std::to_string(i)] = new TH2D ( (name + "_gen_boson_pt_gen_boson_eta_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};Boson #eta", nptbins, ptbins, 6, etabins);  
      }
    }
  }

  if ( name == "non-VBF" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    _cloned_hists[ name ] [ "gen_jetpt0" ] = new TH1D ( (name + "_gen_jetpt0").c_str(), ";jet 0 p_{T};Number of Events", 120,0,1200 );  
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0" ] = new TH2D ( (name + "_gen_boson_pt_gen_jetpt0").c_str(), ";Boson p_{T};jet 0 p_{T}", nptbins, ptbins,4,jetptbins);  
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity" ] = new TH2D ( (name + "_gen_boson_pt_gen_jet_multiplicity").c_str(), ";Boson p_{T};n jet", nptbins, ptbins, 7, njetbins);  

    for ( int i = 0;i<9;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists[ name ] [ "gen_jetpt0_Scale_"+std::to_string(i) ] = new TH1D ( (name + "_gen_jetpt0_Scale_" + std::to_string(i) ).c_str(), ";jet 0 p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jetpt0_Scale_"+std::to_string(i)).c_str(), ";Boson p_{T};jet 0 p_{T}", nptbins, ptbins,4,jetptbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jet_multiplicity_Scale_"+std::to_string(i)).c_str(), ";Boson p_{T};n jet", nptbins, ptbins, 7, njetbins);
    }
    for ( int i = 0;i<102;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists[ name ] [ "gen_jetpt0_PDF_"+std::to_string(i) ] = new TH1D ( (name + "_gen_jetpt0_PDF_" + std::to_string(i) ).c_str(), ";jet 0 p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jetpt0_PDF_"+std::to_string(i)).c_str(), ";Boson p_{T};jet 0 p_{T}", nptbins, ptbins,4,jetptbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jet_multiplicity_PDF_"+std::to_string(i)).c_str(), ";Boson p_{T};n jet 0", nptbins, ptbins, 7, njetbins);
    }
     
   
  }
      
}

//The function whereby the histograms created in MakeAllHistograms are filled with the relevant variable
void HiggsInvisible::FillAllHists( std::string name ){

  double weight = genWeight;

  if ( name == "Default" ||  name == "All" || name == "Default_VTR"){

    if ( name == "Default" || name == "Default_VTR" || name == "All"){
      _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
      _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( _event_variables["gen_boson_eta"], weight);
      _cloned_hists[ name ] [ "gen_boson_mass" ] -> Fill( _event_variables["gen_boson_mass"], weight );

      if ( name == "Default" || name == "Default_VTR"){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], weight );
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a" ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], weight );
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta" ] -> Fill( _event_variables["gen_boson_pt"], std::abs(_event_variables["gen_boson_eta"]), weight );
      }
    }

    _cloned_hists[ name ] [ "gen_dilep_pt_bare" ] -> Fill( _event_variables["gen_dilep_pt_bare"], weight );
    _cloned_hists[ name ] [ "gen_mjj" ] -> Fill( _event_variables["gen_mjj"], weight);
    _cloned_hists[ name ] [ "gen_detajj" ] -> Fill( _event_variables["gen_detajj"], weight );
    _cloned_hists[ name ] [ "gen_dphijj" ] -> Fill( _event_variables["gen_dphijj"], weight );
    _cloned_hists[ name ] [ "gen_mindphi_jetmet" ] -> Fill( gen_mindphi_jetmet, weight );
    _cloned_hists[ name ] [ "LHE_HT" ] -> Fill( LHE_HT, weight );
    _cloned_hists[ name ] [ "LHE_Vpt" ] -> Fill( LHE_Vpt, weight );
    _cloned_hists[ name ] [ "gen_weight" ] -> Fill( genWeight );
    _cloned_hists[ name ] [ "gen_dressed_lepton_eta" ] -> Fill( GenDressedLepton_eta[0], genWeight );
    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] -> Fill( GenDressedLepton_pt[0], genWeight );
    _cloned_hists[ name ] [ "gen_lepton_eta0" ]->Fill( _event_variables["gen_lepton_eta0" ],genWeight );
    _cloned_hists[ name ] [ "gen_lepton_eta1" ]->Fill( _event_variables["gen_lepton_eta1" ],genWeight );
    _cloned_hists[ name ] [ "gen_lepton_pt0" ]->Fill( _event_variables["gen_lepton_pt0" ],genWeight );
    _cloned_hists[ name ] [ "gen_lepton_pt1" ]->Fill( _event_variables["gen_lepton_pt1" ],genWeight );
    _cloned_hists[ name ] [ "n_jets" ] -> Fill( LHE_Njets , genWeight );

    if ( GenJet_pt_or.size()>0 ){
      _cloned_hists[ name ] [ "gen_jetpt0" ] -> Fill( GenJet_pt_or[0], genWeight );     
    }

  }
  if ( name == "All" ){
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 1 );
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 2, weight );
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 3, double(nRuns) );
  }

  if ( name.find("Default")!=std::string::npos || name.find("MJJ")!=std::string::npos ){

    for ( int i = 0;i<9;i++){
      double scaled_weight = weight;
      if (nLHEScaleWeight > 0){
	scaled_weight *= LHEScaleWeight[i];
      }
      else{
	scaled_weight *= 0.5; //To fix a bug where the scaled samples are exactly a factor of 2 too small
      }
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      if ( name.find("Default")!=std::string::npos){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"],  _event_variables["gen_mjj"],scaled_weight );
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"],  _event_variables["gen_mjj"],scaled_weight );
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"],  std::abs(_event_variables["gen_boson_eta"]),scaled_weight );
      }
    }
    for ( int i = 0;i<102;i++){
      double scaled_weight = weight;
      if (nLHEPdfWeight > 0){
	scaled_weight *= LHEPdfWeight[i];
      }
      else{
	scaled_weight *= 0.5; //To fix a bug where the scaled samples are exactly a factor of 2 too small
      }

      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      if ( name.find("Default")!=std::string::npos){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], scaled_weight );
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_a_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], scaled_weight );
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_boson_eta_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], std::abs(_event_variables["gen_boson_eta"]), scaled_weight );
      }
    }

  }

  if (name.find("MJJ")!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
  }

  if ( name.find( "non-VBF" )!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
    _cloned_hists[ name ] [ "gen_jetpt0" ] -> Fill( GenJet_pt_or[0], weight );
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0" ] -> Fill( _event_variables["gen_boson_pt"], GenJet_pt_or[0], weight );
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity" ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["nJetNonVBF"], weight );
    for ( int i = 0;i<9;i++){
      double scaled_weight = weight;
      if (nLHEScaleWeight > 0){
	scaled_weight *= LHEScaleWeight[i];
      }
      else{
	scaled_weight *= 0.5; //To fix a bug where the scaled samples are exactly a factor of 2 too small
      }
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      _cloned_hists[ name ] [ "gen_jetpt0_Scale_"+std::to_string(i) ] -> Fill( GenJet_pt_or[0], scaled_weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], GenJet_pt_or[0], scaled_weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["nJetNonVBF"], scaled_weight );
    }
    for ( int i = 0;i<102;i++){
      double scaled_weight = weight;
      if (nLHEPdfWeight > 0){
	scaled_weight *= LHEPdfWeight[i];
      }
      else{
	scaled_weight *= 0.5; //To fix a bug where the scaled samples are exactly a factor of 2 too small
      }

      _cloned_hists[ name ] [ "gen_jetpt0_PDF_"+std::to_string(i) ] -> Fill( GenJet_pt_or[0], scaled_weight );
      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], GenJet_pt_or[0], scaled_weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["nJetNonVBF"], scaled_weight );
    }

  }


}

void HiggsInvisible::ResetVariables(){
  //Reset variables to 0 or clear vectors after each event

  for ( int i = 0; i < 4; i++ ){
    GenDressedLepton_eta[i] = 0;
    GenDressedLepton_pt[i] = 0;
  }

  GenJet_eta_or.clear();
  GenJet_phi_or.clear();
  GenJet_pt_or.clear();
  GenJet_mass_or.clear();

}

void HiggsInvisible::CalculateVariables(){
  //The code which finds the boson, and calculates the generator level boson quantities

  //Reset various quantities
  _event_variables.clear();

  int mother = 0;
  double boson_pt_born = -1;
  double dilep_pt_bare = -1;

  double boson_mass_born = -1;
  double boson_phi_born = -999;
  double boson_eta_born = -999;

  bool boson_found = false;
  bool lep1_found = false;
  bool lep2_found = false;
  bool lep1_isnu = false;
  bool lep2_isnu = false;

  TLorentzVector lep1;
  TLorentzVector lep2;

  for (unsigned int part = 0; part < nGenPart; part++){

    if ( 
	(std::abs(GenPart_pdgId[part])>10 
	 && std::abs(GenPart_pdgId[part]) < 17)

	&& ( 
	    (GenPart_status[part] == 1 && (GenPart_statusFlags[part] & 0x1)>0) 
	    || ((GenPart_statusFlags[part] & 0x1)>0 && (GenPart_statusFlags[part] & 0x2)>0) ) 
	 ){

      if (GenPart_genPartIdxMother[part]>=0){

	mother = GenPart_genPartIdxMother[part];
	//Find the top of the tree
	while (true){

	  if (GenPart_pdgId[mother] == 23 || std::abs(GenPart_pdgId[mother]) == 24){
	    break;
	  }
	  else mother = GenPart_genPartIdxMother[mother];
	  if ( mother < 0  ) break;
	}

	if (GenPart_pdgId[mother] == 23 || std::abs(GenPart_pdgId[mother]) == 24){

	  boson_pt_born = GenPart_pt[mother];
	  boson_phi_born = GenPart_phi[mother];
	  boson_mass_born = GenPart_mass[mother];
	  boson_eta_born = GenPart_eta[mother];
	  boson_found = true;

	  if (GenPart_pdgId[part]>0){//positive lepton
	    lep1.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep1_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16){
	      lep1_isnu = true;
	    }
	  }
	  else{//negative lepton
	    lep2.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep2_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16){
	      lep2_isnu = true;
	    }

	  }

	}
	else{
	  if (GenPart_pdgId[part]>0){
	    lep1.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep1_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16){
	      lep1_isnu = true;
	    }

	  }	  
	  else{
	    lep2.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep2_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16){
	      lep2_isnu = true;
	    }

	  }
	}
      }
      else{//Never happens (no mother)
	if (GenPart_pdgId[part]>0){
	  lep1.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	  lep1_found = true;
	  if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16){
	    lep1_isnu = true;
	  }

	}
	else{
	  lep2.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	  lep2_found = true;
	  if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16){
	    lep2_isnu = true;
	  }

	}	
      }  

    }
  }

  if (!boson_found){
    boson_pt_born = (lep1+lep2).Pt();
    boson_phi_born = (lep1+lep2).Phi();
    boson_eta_born = (lep1+lep2).Eta();
    boson_mass_born = (lep1+lep2).M();
    boson_found = true;
  }
  if ( lep1_found && lep2_found ){
    dilep_pt_bare = (lep1+lep2).Pt();
  }

  _event_variables["gen_boson_phi"] = boson_phi_born;
  _event_variables["gen_boson_eta"] = boson_eta_born;
  _event_variables["gen_boson_pt"] = boson_pt_born;
  _event_variables["gen_boson_mass"] = boson_mass_born;
  _event_variables["gen_dilep_pt_bare"] = dilep_pt_bare;

  if ( lep1.Pt() > lep2.Pt() ){
    _event_variables["gen_lepton_eta0"] = lep1.Eta();
    _event_variables["gen_lepton_eta1"] = lep2.Eta();
    _event_variables["gen_lepton_pt0"] = lep1.Pt();
    _event_variables["gen_lepton_pt1"] = lep2.Pt();
  }
  else{
    _event_variables["gen_lepton_eta0"] = lep2.Eta();
    _event_variables["gen_lepton_eta1"] = lep1.Eta();
    _event_variables["gen_lepton_pt0"] = lep2.Pt();
    _event_variables["gen_lepton_pt1"] = lep1.Pt();
  }

  //Loop over jets and remove if overlap with leptons
  TLorentzVector jet;
  for (unsigned int g = 0; g < nGenJet; g++){

    jet.SetPtEtaPhiM( GenJet_pt[g], GenJet_eta[g], GenJet_phi[g], GenJet_mass[g] );
    if ( !lep1_isnu ){
      if ( jet.DeltaR(lep1) < 0.4 ) continue;
    }
    if ( !lep2_isnu ){
      if ( jet.DeltaR(lep2) < 0.4 ) continue;
    }

    GenJet_eta_or.push_back( GenJet_eta[g] );
    GenJet_phi_or.push_back( GenJet_phi[g] );
    GenJet_pt_or.push_back( GenJet_pt[g] );
    GenJet_mass_or.push_back( GenJet_mass[g] );

  }  

  TLorentzVector jet0;
  TLorentzVector jet1;
  if (GenJet_pt_or.size()>1){
    jet0.SetPtEtaPhiM( GenJet_pt_or[0], GenJet_eta_or[0], GenJet_phi_or[0], GenJet_mass_or[0] );
    jet1.SetPtEtaPhiM( GenJet_pt_or[1], GenJet_eta_or[1], GenJet_phi_or[1], GenJet_mass_or[1] );
    _event_variables["gen_mjj"] = (jet0+jet1).M();
    _event_variables["gen_detajj"] = std::abs(jet0.Eta()-jet1.Eta());
    _event_variables["gen_dphijj"] = std::abs(jet0.DeltaPhi(jet1));
  }
  
  //For Non-VBF k-factors calculate the number of jets with pT>30, and everything above 6 jets set to 6 jets
  int nJetNonVBF = 0;
  for (unsigned int g = 0; g<(GenJet_pt_or.size()); g++){
    if ( GenJet_pt_or[g] > 30 ){
      nJetNonVBF++;
    }
  }
  if (nJetNonVBF > 6) nJetNonVBF = 6;
  _event_variables["nJetNonVBF"] = nJetNonVBF;

}


//Calculate whether an event passes based on the HistoSet in question ("name")
bool HiggsInvisible::CalculateCuts( std::string name ){

  bool passcut = false;

  TLorentzVector boson, jet;
  bool pass_mindphi_jetbos = true;
  bool pass_mindphi_jetbos_1p8 = true;

  if ( name.find("Default")!=std::string::npos || name.find("MJJ")!=std::string::npos){  

    //Delta phi between jet and boson
    boson.SetPtEtaPhiM( _event_variables["gen_boson_pt"], _event_variables["gen_boson_eta"], _event_variables["gen_boson_phi"], _event_variables["gen_boson_mass"] );
    int counter = 0;
    for (unsigned int g = 0; g<(GenJet_pt_or.size()); g++){
      if ( std::abs(GenJet_eta_or.at(g)) > 5 ) continue;
      if ( GenJet_pt_or[g] > 30 ){//the first 4 jets with pT > 30
	counter++;
	jet.SetPtEtaPhiM( GenJet_pt_or[g], GenJet_eta_or[g], GenJet_phi_or[g], GenJet_mass_or[g] );
	if ( std::abs(boson.DeltaPhi( jet )) < 0.5 ){ 
	  pass_mindphi_jetbos = false;
	  break;
	}
      }
    }

    counter = 0;
    for (unsigned int g = 0; g<(GenJet_pt_or.size()); g++){
      if ( std::abs(GenJet_eta_or.at(g)) > 5 ) continue;
      if ( GenJet_pt_or[g] > 30 ){//the first 4 jets with pT > 30
	counter++;
	jet.SetPtEtaPhiM( GenJet_pt_or[g], GenJet_eta_or[g], GenJet_phi_or[g], GenJet_mass_or[g] );
	if ( std::abs(boson.DeltaPhi( jet )) < 1.8 ){ 
	  pass_mindphi_jetbos_1p8 = false;
	  break;
	}
      }
    }

    if ( name.find("VTR")==std::string::npos){//Not VTR (i.e. MTR)
      bool cut1 = false;
      bool cut2 = false;
      bool cut3 = false;
      bool cut4 = false;
      //      bool cut10 = false;

      if ( GenJet_pt_or.size() > 1 ){
	cut1 = ( GenJet_pt_or[0] > 80 );
	cut2 = ( GenJet_pt_or[1] > 40 );
	cut3 = ( (GenJet_eta_or[0] *  GenJet_eta_or[1]) < 0 );
	cut4 = ( std::abs(GenJet_eta_or[0]) < 5 && std::abs(GenJet_eta_or[1])< 5 );
	//	cut10 = ( std::abs(GenJet_eta_or[0]) < 3.0 || std::abs(GenJet_eta_or[1]) < 3.0  );      //Remove HF-HF events
      }

      bool cut5 = ( pass_mindphi_jetbos );
      bool cut6 = ( _event_variables["gen_dphijj"] < 1.5 );
      bool cut7 = ( _event_variables["gen_mjj"] > 200 );
      bool cut8 = ( _event_variables["gen_detajj"] > 1 );
      bool cut9 = ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true );

      if ( cut1 && cut2 && cut3 && cut4 && cut5 && cut6 && cut7 && cut8 && cut9){
	passcut = true;
      }

    }
    else{//If VTR

      bool cut1 = false;
      bool cut2 = false;
      bool cut3 = false;
      bool cut4 = false;
      //      bool cut10 = false;

      if ( GenJet_pt_or.size() > 1 ){
	cut1 = ( GenJet_pt_or[0] > 140 );
	cut2 = ( GenJet_pt_or[1] > 70 );
	cut3 = ( (GenJet_eta_or[0] *  GenJet_eta_or[1]) < 0 );
	cut4 = ( std::abs(GenJet_eta_or[0]) < 5 && std::abs(GenJet_eta_or[1]) < 5 ) ;
	//	cut10 =  (  std::abs(GenJet_eta_or[0]) < 3.0 || std::abs(GenJet_eta_or[1]) < 3.0 );//Remove HF-HF events
      }

      bool cut5 = ( pass_mindphi_jetbos_1p8 );
      bool cut6 = (_event_variables["gen_dphijj"] < 1.8 ); //Change on 11.06.2020 
      bool cut8 = ( _event_variables["gen_detajj"] > 1 );
      bool cut9 = ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true );

      if ( cut1 && cut2 && cut3 && cut4 && cut5 && cut6 && cut8 && cut9){
	passcut = true;
      }

    }
  
    if ( name .find( "200-500" )!=std::string::npos){
      if (  _event_variables["gen_mjj"] < 200 || _event_variables["gen_mjj"] > 500 ) passcut = false;
    }
    if ( name .find( "500-1000")!=std::string::npos ){
      if (  _event_variables["gen_mjj"] < 500 || _event_variables["gen_mjj"] > 1000 ) passcut = false;
    }
    if ( name .find( "1000-1500")!=std::string::npos ){
      if (  _event_variables["gen_mjj"] < 1000 || _event_variables["gen_mjj"] > 1500 ) passcut = false;
    }
    if ( name .find( "1500-2000")!=std::string::npos ){
      if (  _event_variables["gen_mjj"] < 1500 || _event_variables["gen_mjj"] > 2000 ) passcut = false;
    }
    if ( name .find( "2000-5000")!=std::string::npos ){
      if (  _event_variables["gen_mjj"] < 2000 || _event_variables["gen_mjj"] > 5000 ) passcut = false;
    }
    if ( name .find( "1500-5000")!=std::string::npos ){
      if (  _event_variables["gen_mjj"] < 1500 || _event_variables["gen_mjj"] > 5000 ) passcut = false;
    }
       
  }

  //Non-VBF selection
  if ( name == "non-VBF" ){

    TLorentzVector jet,ht;
    for (unsigned int g = 0; g<GenJet_pt_or.size(); g++){
      if ( GenJet_pt_or[g] > 30 ){
    	jet.SetPtEtaPhiM( GenJet_pt_or[g], GenJet_eta_or[g], GenJet_phi_or[g], GenJet_mass_or[g] );
	ht+=jet;
      }
    }
    
    bool cut1 = false;
    bool cut2 = false;
    bool cut3 = false;
    bool cut4 = false;
    bool cut5 = false;

    if ( GenJet_pt_or.size() > 0 ){
      cut1 = ( GenJet_pt_or[0] > 40 );
      cut2 = ( _event_variables["gen_boson_pt"] > 100 );
      cut3 = ( ht.Pt() > 200 );
      cut4 = ( ht.Pt()/_event_variables["gen_boson_pt"]  < 1.2 );
      cut5 = ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true );
    }

    if ( cut1 && cut2 && cut3 && cut4 && cut5){
      passcut = true;
    }
    else{
      passcut = false;
    }

  }

  //Select all events
  if ( name == "All" ){
    passcut = true;
  }

  return passcut;

}
