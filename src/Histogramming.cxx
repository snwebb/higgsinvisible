/******************************************************************************
 HGC analysis code
 Samuel Webb
 Imperial College
***************************************************************************/

// Time-stamp: <2020-11-16 13:18:43 (snwebb)>

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

  double mjjbins[7] = {0,200,500,1000,1500,2000,5000};
  double vtrmjjbins[4] = {0,600,900,5000};
  double jetptbins[5] = {0,200,400,600,1200};
  double njetbins[8] = {-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5}
  double ptbins[15] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 400, 520, 640, 760, 880,1100}; //andreas's binnings

  if ( name.find("Default")!=std::string::npos ||  name == "1JPt150" || name == "All" || name.find("ZNN")!=std::string::npos){
    _cloned_hists[ name ] [ "gen_dilep_pt_bare" ] = new TH1D ( (name + "_gen_dilep_pt_bare").c_str(), ";Di lep p_{T};Number of Events", 120,0,1200 );  
    //    _cloned_hists[ name ] [ "gen_dilep_pt_dressed" ] = new TH1D ( (name + "_gen_dilep_pt_dressed").c_str(), ";Di lep p_{T};Number of Events", 120,0,1200 );  
    // _cloned_hists[ name ] [ "gen_dilep_eta_bare" ] = new TH1D ( (name + "_gen_dilep_eta_bare").c_str(), ";Di lep #eta;Number of Events", 120,0,1200 );  
    // _cloned_hists[ name ] [ "gen_dilep_mass_bare" ] = new TH1D ( (name + "_gen_dilep_mass_bare").c_str(), ";Di lep Mass;Number of Events", 120,0,1200 );  

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  


    if ( name == "Default_VTR" ){
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj").c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,3,vtrmjjbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_HeavyQuark" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_HeavyQuark" ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,3,vtrmjjbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_NoHeavyQuark" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_NoHeavyQuark" ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,3,vtrmjjbins);  

    }
    else{
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj").c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,6,mjjbins);  

      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_HeavyQuark" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_HeavyQuark" ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,6,mjjbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_NoHeavyQuark" ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_NoHeavyQuark" ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,6,mjjbins);  
    }

    _cloned_hists[ name ] [ "gen_boson_eta" ] = new TH1D ( (name + "_gen_boson_eta").c_str(), ";Boson #eta;Number of Events", 40,-8,8 );  
    _cloned_hists[ name ] [ "gen_boson_mass" ] = new TH1D ( (name + "_gen_boson_mass").c_str(), ";Boson Mass;Number of Events", 200,0,200);  
    _cloned_hists[ name ] [ "gen_mjj" ] = new TH1D ( (name + "_gen_mjj").c_str(), ";M_{jj};Number of Events", 3500,0,3500 );  
    _cloned_hists[ name ] [ "gen_detajj" ] = new TH1D ( (name + "_gen_detajj").c_str(), ";#Delta#eta_{jj};Number of Events", 50,0,7 );  
    _cloned_hists[ name ] [ "gen_dphijj" ] = new TH1D ( (name + "_gen_dphijj").c_str(), ";#Delta#phi_{jj};Number of Events", 50,0, M_PI );  
    _cloned_hists[ name ] [ "gen_mindphi_jetmet" ] = new TH1D ( (name + "_gen_mindphi_jetmet").c_str(), ";min-#Delta#phi(j,p_{T}^{V});Number of Events", 50,0, M_PI );  
    _cloned_hists[ name ] [ "LHE_HT" ] = new TH1D ( (name + "_LHE_HT").c_str(), ";HT;Number of Events",5000,0,5000);  
    _cloned_hists[ name ] [ "gen_weight" ] = new TH1D ( (name + "_gen_weight").c_str(), ";weight;Number of Events",100,-100000,100000);  
    _cloned_hists[ name ] [ "gen_jetpt0" ] = new TH1D ( (name + "_gen_jetpt0").c_str(), ";jet 0 p_{T};Number of Events", 300,0,600 );  

    _cloned_hists[ name ] [ "n_jets" ] = new TH1D ( (name + "_n_jets").c_str(), ";nJets;Number of Events", 10,-0.5,9.5 );  

    _cloned_hists[ name ] [ "gen_dressed_lepton_eta" ] = new TH1D ( (name + "_gen_dressed_lepton_eta").c_str(), ";Leading lepton #eta;Number of Events",100,-8,8);  
    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] = new TH1D ( (name + "_gen_dressed_lepton_pt").c_str(), ";Leading lepton p_{T};Number of Events",120,0,1200);  


    _cloned_hists[ name ] [ "gen_lepton_eta0" ] = new TH1D ( (name + "_gen_lepton_eta0").c_str(), ";Leading lepton #eta;Number of Events",100,-8,8);  
    _cloned_hists[ name ] [ "gen_lepton_eta1" ] = new TH1D ( (name + "_gen_lepton_eta1").c_str(), ";Sub-leading lepton #eta;Number of Events",100,-8,8);  

    _cloned_hists[ name ] [ "gen_lepton_pt0" ] = new TH1D ( (name + "_gen_lepton_pt0").c_str(), ";Leading lepton p_{T};Number of Events",120,0,1200);  
    _cloned_hists[ name ] [ "gen_lepton_pt1" ] = new TH1D ( (name + "_gen_lepton_pt1").c_str(), ";Sub-leading lepton p_{T};Number of Events",120,0,1200);  


    //    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] = new TH1D ( (name + "_gen_dressed_lepton_pt").c_str(), ";Leading lepton p_{T};Number of Events",120,0,1200);  

  }

  if ( name == "All" ){
    _cloned_hists[ name ] [ "gen_events" ] = new TH1D ( (name + "_gen_events").c_str(), ";;Number of Events",3,0.5,3.5 );  
    //    _cloned_hists[ name ] [ "nRuns" ] = new TH1D ( (name + "_nRuns").c_str(), ";;Number of Events",1,0.5,1.5 );  
    // _cloned_hists[ name ] [ "LHE_HT" ] = new TH1D ( (name + "_LHE_HT").c_str(), ";HT;Number of Events",5000,0,5000);  
    // _cloned_hists[ name ] [ "gen_weight" ] = new TH1D ( (name + "_gen_weight").c_str(), ";weight;Number of Events",100,-15000,15000);  
    // _cloned_hists[ name ] [ "gen_boson_eta" ] = new TH1D ( (name + "_gen_boson_eta").c_str(), ";Boson #eta;Number of Events", 40,-8,8 );  
  }
  if ( name == "Default2ndLep" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  

  }

  if ( name.find("Mjj")!=std::string::npos || name.find("MJJ")!=std::string::npos ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    //    _cloned_hists[ name ] [ "gen_dilep_pt_bare" ] = new TH1D ( (name + "_gen_dilep_pt").c_str(), ";Di lep p_{T};Number of Events", 120,0,1200 );  

  }
  if ( name.find("NJET")!=std::string::npos ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  

  }
  if ( name.find("Default")!=std::string::npos || name.find("MJJ")!=std::string::npos){

    for ( int i = 0;i<9;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  

    }

    for ( int i = 0;i<102;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    }

  }
  if ( name.find("Default")!=std::string::npos){

    if ( name == "Default_VTR" ){
      for ( int i = 0;i<9;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,3,vtrmjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_HeavyQuark_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_HeavyQuark_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,3,vtrmjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,3,vtrmjjbins);  
      }
      for ( int i = 0;i<102;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14,ptbins,3,vtrmjjbins );  
      }
    }else{
      for ( int i = 0;i<9;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,6,mjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_HeavyQuark_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_HeavyQuark_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,6,mjjbins);  
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14, ptbins,6,mjjbins);  
      }
      for ( int i = 0;i<102;i++){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_mjj_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};M_{jj}", 14,ptbins,6,mjjbins );  
      }
    }
  }

  if ( name == "non-VBF" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
    _cloned_hists[ name ] [ "gen_jetpt0" ] = new TH1D ( (name + "_gen_jetpt0").c_str(), ";jet 0 p_{T};Number of Events", 120,0,1200 );  
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0" ] = new TH2D ( (name + "_gen_boson_pt_gen_jetpt0").c_str(), ";Boson p_{T};jet 0 p_{T}", 14, ptbins,4,jetptbins);  
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity" ] = new TH2D ( (name + "_gen_boson_pt_gen_jet_multiplicity").c_str(), ";Boson p_{T};n jet", 14, ptbins, 7, njetbins);  

    for ( int i = 0;i<9;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_Scale_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists[ name ] [ "gen_jetpt0_Scale_"+std::to_string(i) ] = new TH1D ( (name + "_gen_jetpt0_Scale_" + std::to_string(i) ).c_str(), ";jet 0 p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jetpt0_Scale_"+std::to_string(i)).c_str(), ";Boson p_{T};jet 0 p_{T}", 14, ptbins,4,jetptbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity_Scale_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jet_multiplicity_Scale_"+std::to_string(i)).c_str(), ";Boson p_{T};n jet", 14, ptbins, 7, njetbins);
    }
    for ( int i = 0;i<102;i++){
      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] = new TH1D ( (name + "_gen_boson_pt_PDF_" + std::to_string(i) ).c_str(), ";Boson p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists[ name ] [ "gen_jetpt0_PDF_"+std::to_string(i) ] = new TH1D ( (name + "_gen_jetpt0_PDF_" + std::to_string(i) ).c_str(), ";jet 0 p_{T};Number of Events", 120,0,1200 );  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jetpt0_PDF_"+std::to_string(i)).c_str(), ";Boson p_{T};jet 0 p_{T}", 14, ptbins,4,jetptbins);  
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jet_multiplicity_PDF_"+std::to_string(i) ] = new TH2D ( (name + "_gen_boson_pt_gen_jet_multiplicity_PDF_"+std::to_string(i)).c_str(), ";Boson p_{T};n jet 0", 14, ptbins, 7, njetbins);
    }
     
   
  }
   
   
}




void HiggsInvisible::FillAllHists( std::string name ){

  double weight = genWeight;
  //  double weight = 1;

  //  if ( name == "Default" ||  name == "1JPt150" ){
  if ( name == "Default" ||  name == "1JPt150" || name == "All" || name == "Default_BARE" || name == "Default_DRESSED" || name == "Default_VTR" || name.find("ZNN")!=std::string::npos){
    //  if ( name == "Default" ){

    // _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( gen_boson_pt, weight );
    // _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( gen_boson_eta, weight);

    if ( name == "Default" || name == "Default_VTR" || name.find("ZNN")!=std::string::npos || name == "All"){
      _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
      _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( _event_variables["gen_boson_eta"], weight);
      _cloned_hists[ name ] [ "gen_boson_mass" ] -> Fill( _event_variables["gen_boson_mass"], weight );
      if ( name == "Default" || name == "Default_VTR"){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], weight );
	if ( std::abs(_event_variables["gen_part_incoming1"]) == 4  || std::abs(_event_variables["gen_part_incoming2"]) == 4 || std::abs(_event_variables["gen_part_incoming1"]) == 5  || std::abs(_event_variables["gen_part_incoming2"]) == 5 ){//Contains Heavy Quark (
	  _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_HeavyQuark" ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], weight );
	}
	else{
	  _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_NoHeavyQuark" ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], weight );
	}
      }
    }
    if ( name == "Default_BARE" ){
      _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_dilep_pt_bare"], weight );
      _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( _event_variables["gen_dilep_eta_bare"], weight);
      _cloned_hists[ name ] [ "gen_boson_mass" ] -> Fill( _event_variables["gen_dilep_mass_bare"], weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] -> Fill( _event_variables["gen_dilep_pt_bare"], _event_variables["gen_mjj"], weight );
    }
    if ( name == "Default_DRESSED" ){
      _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_dilep_pt_dressed"], weight );
      _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( _event_variables["gen_dilep_eta_dressed"], weight);
      _cloned_hists[ name ] [ "gen_boson_mass" ] -> Fill( _event_variables["gen_dilep_mass_dressed"], weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj" ] -> Fill( _event_variables["gen_dilep_pt_dressed"], _event_variables["gen_mjj"], weight );
    }

    _cloned_hists[ name ] [ "gen_dilep_pt_bare" ] -> Fill( _event_variables["gen_dilep_pt_bare"], weight );
    //    _cloned_hists[ name ] [ "gen_dilep_pt_dressed" ] -> Fill( _event_variables["gen_dilep_pt_dressed"], weight );
    // _cloned_hists[ name ] [ "gen_dilep_eta_bare" ] -> Fill( _event_variables["gen_dilep_eta_bare"], weight );
    // _cloned_hists[ name ] [ "gen_dilep_mass_bare" ] -> Fill( _event_variables["gen_dilep_mass_bare"], weight );
    _cloned_hists[ name ] [ "gen_mjj" ] -> Fill( _event_variables["gen_mjj"], weight);

    //    _cloned_hists[ name ] [ "gen_mjj" ] -> Fill( _event_variables["gen_mjj"], 1);
    _cloned_hists[ name ] [ "gen_detajj" ] -> Fill( _event_variables["gen_detajj"], weight );
    _cloned_hists[ name ] [ "gen_dphijj" ] -> Fill( _event_variables["gen_dphijj"], weight );
    _cloned_hists[ name ] [ "gen_mindphi_jetmet" ] -> Fill( gen_mindphi_jetmet, weight );
    _cloned_hists[ name ] [ "LHE_HT" ] -> Fill( LHE_HT, weight );
    _cloned_hists[ name ] [ "gen_weight" ] -> Fill( genWeight );
    _cloned_hists[ name ] [ "gen_dressed_lepton_eta" ] -> Fill( GenDressedLepton_eta[0], genWeight );
    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] -> Fill( GenDressedLepton_pt[0], genWeight );


    _cloned_hists[ name ] [ "gen_lepton_eta0" ]->Fill( _event_variables["gen_lepton_eta0" ],genWeight );
    _cloned_hists[ name ] [ "gen_lepton_eta1" ]->Fill( _event_variables["gen_lepton_eta1" ],genWeight );
    _cloned_hists[ name ] [ "gen_lepton_pt0" ]->Fill( _event_variables["gen_lepton_pt0" ],genWeight );
    _cloned_hists[ name ] [ "gen_lepton_pt1" ]->Fill( _event_variables["gen_lepton_pt1" ],genWeight );

    if ( GenJet_pt_or.size()>0 ){
      _cloned_hists[ name ] [ "gen_jetpt0" ] -> Fill( GenJet_pt_or[0], genWeight );     
    }
    _cloned_hists[ name ] [ "n_jets" ] -> Fill( LHE_Njets , genWeight );

  }
  if ( name == "All" ){
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 1 );
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 2, weight );
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 3, double(nRuns) );
    // _cloned_hists[ name ] [ "LHE_HT" ] -> Fill( LHE_HT, weight );
    // _cloned_hists[ name ] [ "gen_weight" ] -> Fill( genWeight );
    // _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( gen_boson_eta, weight );
  }

  if ( name == "Default2ndLep" ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
  }

  if ( name.find( "Mjj" )!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill(_event_variables["gen_boson_pt"], weight );
    _cloned_hists[ name ] [ "gen_dilep_pt_bare" ] -> Fill(_event_variables["gen_dilep_pt_bare"], weight );
    //    _cloned_hists[ name ] [ "gen_dilep_pt_dressed" ] -> Fill(_event_variables["gen_dilep_pt_dressed"], weight );
  }


  if ( name.find( "NJET" )!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
  }

  if ( name.find( "non-VBF" )!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
    _cloned_hists[ name ] [ "gen_jetpt0" ] -> Fill( GenJet_pt_or[0], weight );
    _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0" ] -> Fill( _event_variables["gen_boson_pt"], GenJet_pt_or[0], weight );
    for ( int i = 0;i<9;i++){
      double scaled_weight = weight;
      if (nLHEScaleWeight > 0){
	scaled_weight *= LHEScaleWeight[i];
      }
      else{
	scaled_weight *= 0.5;
      }
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      _cloned_hists[ name ] [ "gen_jetpt0_Scale_"+std::to_string(i) ] -> Fill( GenJet_pt_or[0], scaled_weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], GenJet_pt_or[0], scaled_weight );
    }
    for ( int i = 0;i<102;i++){
      double scaled_weight = weight;
      if (nLHEPdfWeight > 0){
	scaled_weight *= LHEPdfWeight[i];
      }
      else{
	scaled_weight *= 0.5;
      }

      _cloned_hists[ name ] [ "gen_jetpt0_PDF_"+std::to_string(i) ] -> Fill( GenJet_pt_or[0], scaled_weight );
      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      _cloned_hists2D[ name ] [ "gen_boson_pt_gen_jetpt0_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], GenJet_pt_or[0], scaled_weight );
    }

  }

  if ( name.find("Default")!=std::string::npos || name.find("MJJ")!=std::string::npos ){

    for ( int i = 0;i<9;i++){
      double scaled_weight = weight;
      if (nLHEScaleWeight > 0){
	scaled_weight *= LHEScaleWeight[i];
      }
      else{
	scaled_weight *= 0.5;
      }
      _cloned_hists[ name ] [ "gen_boson_pt_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      if ( name.find("Default")!=std::string::npos){
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"],  _event_variables["gen_mjj"],scaled_weight );
	if ( std::abs(_event_variables["gen_part_incoming1"]) == 4  || std::abs(_event_variables["gen_part_incoming2"]) == 4 || std::abs(_event_variables["gen_part_incoming1"]) == 5  || std::abs(_event_variables["gen_part_incoming2"]) == 5 ){//Contains Heavy Quark (
	  _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_HeavyQuark_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"],  _event_variables["gen_mjj"],scaled_weight );
	}
	else{
	  _cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_Scale_NoHeavyQuark_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"],  _event_variables["gen_mjj"],scaled_weight );
	}
      }
    }
    for ( int i = 0;i<102;i++){
      double scaled_weight = weight;
      if (nLHEPdfWeight > 0){
	scaled_weight *= LHEPdfWeight[i];
      }
      else{
	scaled_weight *= 0.5;
      }

      _cloned_hists[ name ] [ "gen_boson_pt_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], scaled_weight );
      if ( name.find("Default")!=std::string::npos)
	_cloned_hists2D[ name ] [ "gen_boson_pt_gen_mjj_PDF_"+std::to_string(i) ] -> Fill( _event_variables["gen_boson_pt"], _event_variables["gen_mjj"], scaled_weight );
    }

  }

  if (name.find("MJJ")!=std::string::npos ){
    if ( name.find("BARE")!=std::string::npos ) _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_dilep_pt_bare"], weight );
    //    else if ( name.find("DRESSED")!=std::string::npos ) _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_dilep_pt_dressed"], weight );
    else  _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( _event_variables["gen_boson_pt"], weight );
  }

}

void HiggsInvisible::ResetVariables(){

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

  //Reset various quantities
  _event_variables.clear();
  //Boson phi
  // int lep1 = 0;
  // int lep2 = 0;
  int mother = 0;
  double boson_pt_born = -1;
  double dilep_pt_bare = -1;
  //  double dilep_pt_dressed = -1;

  double boson_mass_born = -1;
  double boson_phi_born = -999;
  double boson_eta_born = -999;

  double dilep_mass_bare = -1;
  double dilep_phi_bare = -999;
  double dilep_eta_bare = -999;

  // double dilep_mass_dressed = -1;
  // double dilep_phi_dressed = -999;
  // double dilep_eta_dressed = -999;

  bool boson_found = false;
  bool lep1_found = false;
  bool lep2_found = false;
  bool lep1_isnu = false;
  bool lep2_isnu = false;

  TLorentzVector lep1;
  TLorentzVector lep2;

  int incoming1 = -1;
  int incoming2 = -1;

  for (unsigned int part = 0; part < nGenPart; part++){

    if ( GenPart_status[part] == 21 ){
      if (incoming1 == -1) incoming1 = GenPart_pdgId[part];
      else if (incoming2 == -1) incoming2 = GenPart_pdgId[part];
      else std::cout << "More than 2 incoming particles" << std::endl;
    }

    if ( 
	(std::abs(GenPart_pdgId[part])>10 
	 && std::abs(GenPart_pdgId[part]) < 17)


	&& ( 
	    (GenPart_status[part] == 1 && (GenPart_statusFlags[part] & 0x1)>0) 
	    || ((GenPart_statusFlags[part] & 0x1)>0 && (GenPart_statusFlags[part] & 0x2)>0) ) 
	 ){

      //      c++;      
      //      std::cout << GenPart_pt[part] << std::endl;

      if (GenPart_genPartIdxMother[part]>=0){

	mother = GenPart_genPartIdxMother[part];
	//something wrong
	//Find the top of the tree
	//	 for (int i = 0; i < 100; i++){
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

	  //	  std::cout << "mother found " << std::endl;

	  if (GenPart_pdgId[part]>0){//positive
	    lep1.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep1_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16)
	      lep1_isnu = true;
	  }
	  else{//negative lepton
	    lep2.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep2_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16)
	      lep2_isnu = true;

	  }

	  //break;
	}
	else{
	  //	  std::cout << "mother not correct is: " << GenPart_pdgId[mother]<< " - " << event << std::endl;
	  if (GenPart_pdgId[part]>0){
	    lep1.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep1_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16)
	      lep1_isnu = true;

	  }	  
	  else{
	    lep2.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	    lep2_found = true;
	    if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16)
	      lep2_isnu = true;

	  }
	}
      }
      else{//Never happens
	//		std::cout << "no mother" << std::endl;
	if (GenPart_pdgId[part]>0){
	  lep1.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	  lep1_found = true;
	  if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16)
	    lep1_isnu = true;

	}
	else{
	  lep2.SetPtEtaPhiM( GenPart_pt[part], GenPart_eta[part], GenPart_phi[part], GenPart_mass[part]  );
	  lep2_found = true;
	  if ( std::abs(GenPart_pdgId[part]) == 12 || std::abs(GenPart_pdgId[part]) == 14 || std::abs(GenPart_pdgId[part]) == 16)
	    lep2_isnu = true;

	}	
      }  


    }
  }

  //  if ( c > 2 ) std::cout << "Problem" << std::endl;

  //  if (!boson_found && (  lep1_found && lep2_found ) ){

  if (!boson_found){
    boson_pt_born = (lep1+lep2).Pt();
    boson_phi_born = (lep1+lep2).Phi();
    boson_eta_born = (lep1+lep2).Eta();
    boson_mass_born = (lep1+lep2).M();
    boson_found = true;
  }
  if ( lep1_found && lep2_found ){
    dilep_pt_bare = (lep1+lep2).Pt();
    dilep_eta_bare = (lep1+lep2).Eta();
    dilep_phi_bare = (lep1+lep2).Phi();
    dilep_mass_bare = (lep1+lep2).M();
  }


  _event_variables["gen_boson_phi"] = boson_phi_born;
  _event_variables["gen_boson_eta"] = boson_eta_born;
  _event_variables["gen_boson_pt"] = boson_pt_born;
  _event_variables["gen_boson_mass"] = boson_mass_born;
  /*
    if ( std::abs(incoming1) < 4 || std::abs(incoming2) < 4 ){

    if ( std::abs(incoming1) < 4 && std::abs(incoming2) < 4 ){
    std::cout << "LIGHTQ - LIGHTQ" << std::endl;
    }
    else{
    std::cout << "LIGHTQ - HEAVYQ" << std::endl;
    }

    }

    if ( std::abs(incoming1) == 21 ){

    if ( std::abs(incoming2) < 4 ){
    std::cout << "LIGHTQ - GLUON"<< std::endl;
    }
    else{
    std::cout << "HEAVYQ - GLUON"<< std::endl;
    }
    }
    else if ( std::abs(incoming2) == 21 ){

    if ( std::abs(incoming1) < 4 ){
    std::cout << "LIGHTQ - GLUON"<< std::endl;
    }
    else{
    std::cout << "HEAVYQ - GLUON"<< std::endl;
    }

    }

    if ( std::abs(incoming1) >= 4 && std::abs(incoming2) >= 4 && std::abs(incoming1) < 7 && std::abs(incoming2) < 7 ){
    std::cout << "HEAVYQ - HEAVYQ"<< std::endl;
    }
  */

  _event_variables["gen_part_incoming1"] = incoming1;
  _event_variables["gen_part_incoming2"] = incoming2;

  _event_variables["gen_dilep_pt_bare"] = dilep_pt_bare;
  _event_variables["gen_dilep_eta_bare"] = dilep_eta_bare;
  _event_variables["gen_dilep_phi_bare"] = dilep_phi_bare;
  _event_variables["gen_dilep_mass_bare"] = dilep_mass_bare;

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


}

bool HiggsInvisible::CalculateCuts( std::string name ){

  bool passcut = false;

  TLorentzVector boson, jet;
  bool pass_mindphi_jetbos = true;
  bool pass_mindphi_jetbos_1p8 = true;

  if ( name.find("Default")!=std::string::npos || name.find("MJJ")!=std::string::npos || name.find("NJET")!=std::string::npos){  


    //Delta phi between jet and boson
    //    std::string truth = "born";
    //
    boson.SetPtEtaPhiM( _event_variables["gen_boson_pt"], _event_variables["gen_boson_eta"], _event_variables["gen_boson_phi"], _event_variables["gen_boson_mass"] );

    if (name.find("BARE")){
      boson.SetPtEtaPhiM( _event_variables["gen_dilep_pt_bare"], _event_variables["gen_dilep_eta_bare"], _event_variables["gen_dilep_phi_bare"], _event_variables["gen_dilep_mass_bare"] );
    }

    int counter = 0;
    for (unsigned int g = 0; g<(GenJet_pt_or.size()); g++){//Switch 14.01.20 to using the first 4 jets with pT > 30
      if ( std::abs(GenJet_eta_or.at(g)) > 5 ) continue;
      if ( GenJet_pt_or[g] > 30 ){
	counter++;
	jet.SetPtEtaPhiM( GenJet_pt_or[g], GenJet_eta_or[g], GenJet_phi_or[g], GenJet_mass_or[g] );
	if ( std::abs(boson.DeltaPhi( jet )) < 0.5 ){ 
	  pass_mindphi_jetbos = false;
	  break;
	}
      }
    }

    counter = 0;
    for (unsigned int g = 0; g<(GenJet_pt_or.size()); g++){//Switch 14.01.20 to using the first 4 jets with pT > 30
      if ( std::abs(GenJet_eta_or.at(g)) > 5 ) continue;
      if ( GenJet_pt_or[g] > 30 ){
	counter++;
	jet.SetPtEtaPhiM( GenJet_pt_or[g], GenJet_eta_or[g], GenJet_phi_or[g], GenJet_mass_or[g] );
	if ( std::abs(boson.DeltaPhi( jet )) < 1.8 ){ 
	  pass_mindphi_jetbos_1p8 = false;
	  break;
	}
      }
    }

    if ( name.find("VTR")==std::string::npos){
      bool cut1 = false;
      bool cut2 = false;
      bool cut3 = false;
      bool cut4 = false;
      bool cut10 = false;

      if ( GenJet_pt_or.size() > 1 ){
	cut1 = ( GenJet_pt_or[0] > 80 );
	cut2 = ( GenJet_pt_or[1] > 40 );
	cut3 = ( (GenJet_eta_or[0] *  GenJet_eta_or[1]) < 0 );
	cut4 = ( std::abs(GenJet_eta_or[0]) < 5 && std::abs(GenJet_eta_or[1])< 5 );
	cut10 = ( std::abs(GenJet_eta_or[0]) < 3.0 || std::abs(GenJet_eta_or[1]) < 3.0  );      //Remove HF-HF events
      }

      bool cut5 = ( pass_mindphi_jetbos);
      bool cut6 = ( _event_variables["gen_dphijj"] < 1.5 );
      bool cut7 = ( _event_variables["gen_mjj"] > 200 );
      bool cut8 = ( _event_variables["gen_detajj"] > 1 );
      bool cut9 = ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true );

      // //for k-factors	 
      // //	 (  (_zll||_wln) ? (std::abs(GenDressedLepton_eta[0]) < 2.4) : true) 
      // //	 GenDressedLepton_pt[0] > 20//think

      //	 && LHE_HT>70
      //	 && boson.Pt()>70

      if ( cut1 && cut2 && cut3 && cut4 && cut5 && cut6 && cut7 && cut8 && cut9 && cut10)
	passcut = true;


    }
    else{

      bool cut1 = false;
      bool cut2 = false;
      bool cut3 = false;
      bool cut4 = false;
      bool cut10 = false;

      if ( GenJet_pt_or.size() > 1 ){
	cut1 = ( GenJet_pt_or[0] > 140 );
	cut2 = ( GenJet_pt_or[1] > 70 );
	cut3 = ( (GenJet_eta_or[0] *  GenJet_eta_or[1]) < 0 );
	cut4 = (std::abs(GenJet_eta_or[0]) < 5 && std::abs(GenJet_eta_or[1]) < 5 ) ;
	cut10 =  (  std::abs(GenJet_eta_or[0]) < 3.0 || std::abs(GenJet_eta_or[1]) < 3.0 );//Remove HF-HF events
      }
      //&& _event_variables["gen_mjj"] > 900
      bool cut5 = ( pass_mindphi_jetbos_1p8 );
      bool cut6 = (_event_variables["gen_dphijj"] < 1.8 ); //Change on 11.06.2020 
      bool cut8 = ( _event_variables["gen_detajj"] > 1 );
      bool cut9 = ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true );

      // && _event_variables["gen_boson_pt"] < 250 
      // && _event_variables["gen_boson_pt"] >= 160

      if ( cut1 && cut2 && cut3 && cut4 && cut5 && cut6 && cut8 && cut9 && cut10){
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
    
    
    if ( name == "NJET1" ){
      if (  LHE_Njets !=1 ) passcut = false;
    }
    if ( name == "NJET2" ){
      if (  LHE_Njets !=2 ) passcut = false;
    }
    if ( name == "NJET3" ){
      if (  LHE_Njets !=3 ) passcut = false;
    }

  }



  //Ignore from here onwards  
  /*
    if ( name == "1JPt150" ){
    
    TLorentzVector boson, jet;
    bool pass_mindphi_jetbos = true;
    
    boson.SetPtEtaPhiM( _event_variables["gen_boson_pt"], _event_variables["gen_boson_eta"], _event_variables["gen_boson_phi"], _event_variables["boson_mass"] );

    for (unsigned int g = 0; g<(nGenJet<3?nGenJet:3); g++){
    if ( GenJet_pt[g] > 30 ){
    jet.SetPtEtaPhiM( GenJet_pt[g], GenJet_eta[g], GenJet_phi[g], GenJet_mass[g] );
    if ( std::abs(boson.DeltaPhi( jet )) < 0.5 ){ 
    pass_mindphi_jetbos = false;
    break;
    }
    }
    }

    if ( GenJet_pt[0] > 80
	 
    && GenJet_eta[0] *  GenJet_eta[1] < 0
    //	 (std::abs(GenJet_eta[0]) < 3 ) &&
    //       	 (gen_mindphi_jetmet) > 0.5 &&
	 
    && pass_mindphi_jetbos
    && gen_dphijj < 1.5 && 
    gen_mjj > 200 && 
    gen_detajj > 1 

    ){
    passcut = true;

    }
    

    if ( name == "Default2ndLep" ){
    bool pass_additional = false;
    if  (  _zll ? (std::abs(GenDressedLepton_eta[1]) < 2.4) : true )
    pass_additional = true;
      
    passcut = passcut && pass_additional;
    }

    if ( name == "Default-Mjj-200-500" ){
    bool pass_additional = false;
    pass_additional = false;
    if ( gen_mjj > 200 && gen_mjj <= 500 )
    pass_additional = true;
    passcut = passcut && pass_additional;
    }
    if ( name == "Default-Mjj-500-1000" ){
    bool pass_additional = false;
    pass_additional = false;
    if ( gen_mjj > 500 && gen_mjj <= 1000 )
    pass_additional = true;
    passcut = passcut && pass_additional;
    }
    if ( name == "Default-Mjj-1000-1500" ){
    bool pass_additional = false;
    pass_additional = false;
    if ( gen_mjj > 1000 && gen_mjj <= 1500 )
    pass_additional = true;
    passcut = passcut && pass_additional;
    }
    if ( name == "Default-Mjj-1500-5000" ){
    bool pass_additional = false;
    pass_additional = false;
    if ( gen_mjj > 1500 && gen_mjj <= 5000 )
    pass_additional = true;
    passcut = passcut && pass_additional;
    }

    }
  */
  ////////
  
  if ( name == "non-VBF" ){

    TLorentzVector jet,ht;
    for (unsigned int g = 0; g<GenJet_pt_or.size(); g++){
      if ( GenJet_pt_or[g] > 30 ){
    	jet.SetPtEtaPhiM( GenJet_pt_or[g], GenJet_eta_or[g], GenJet_phi_or[g], GenJet_mass_or[g] );
	ht+=jet;
      }
    }

    if ( GenJet_pt_or.size() > 0 ){
      if ( //GenJet_pt_or[0] > 80
	  GenJet_pt_or[0] > 40
	  //	 && _event_variables["gen_boson_pt"] > 200
	  && _event_variables["gen_boson_pt"] > 100
	  &&  ht.Pt() > 200
	  &&  ht.Pt()/_event_variables["gen_boson_pt"]  < 1.2
	  && ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true )      
	   ){
	passcut = true;
	
      }
    }
    else{
      passcut = false;
    }
  }

  // if ( name.find("ZNN")!=std::string::npos){
  //     bool cut1 = ( GenJet_pt_or[0] > 80 );
  //     bool cut2 = ( GenJet_pt_or[1] > 40 );
  //     bool cut3 = ( (GenJet_eta_or[0] *  GenJet_eta_or[1]) < 0 );
  //     bool cut4 = ( std::abs(GenJet_eta_or[0]) < 5 && std::abs(GenJet_eta_or[1])< 5 );
  //     bool cut5 = ( pass_mindphi_jetbos);
  //     bool cut6 = ( _event_variables["gen_dphijj"] < 1.5 );
  //     bool cut8 = ( _event_variables["gen_detajj"] > 1 );
  //     bool cut9 = ( _zll ? (_event_variables["gen_boson_mass"] > 60 && _event_variables["gen_boson_mass"] < 120 ) : true );

  //     if ( name == "ZNN-No_gen_mjj" ){
  // 	passcut = false;
  // 	if ( cut1 && cut2 && cut3 && cut4 && cut5 && cut6 && cut8 && cut9 )
  // 	  passcut = true;
  //     }
  //     else if ( name == "ZNN-2Jets" ){
  // 	passcut = false;
  // 	if ( cut1 && cut2 )
  // 	  passcut = true;
  //     }
  //     else if ( name == "ZNN-2JetsEta" ){
  // 	passcut = false;
  // 	if ( cut1 && cut2 && cut3 && cut4 )
  // 	  passcut = true;
  //     }
  //     else if ( name == "ZNN-2JetsEtaDeltaEta" ){
  // 	passcut = false;
  // 	if ( cut1 && cut2 && cut3 && cut4 && cut8 )
  // 	  passcut = true;
  //     }
  //     else if ( name == "ZNN-2JetsEtaDeltaEtaDeltaPhi" ){
  // 	passcut = false;
  // 	if ( cut1 && cut2 && cut3 && cut4 && cut6 && cut8 )
  // 	  passcut = true;
  //     }

  // }

  if ( name == "All" ){
    // if (  LHE_HT>100 
    // 	  &&   _event_variables["gen_boson_pt"]>100
    // 	  ){
    passcut = true;
    //    }
  }

  return passcut;

}
