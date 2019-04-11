/******************************************************************************
HGC analysis code
Samuel Webb
Imperial College
***************************************************************************/

// Time-stamp: <2019-03-29 16:01:11 (snwebb)>

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

  if ( name == "Default" ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 110,0,1100 );  
    _cloned_hists[ name ] [ "gen_boson_eta" ] = new TH1D ( (name + "_gen_boson_eta").c_str(), ";Boson #eta;Number of Events", 40,-8,8 );  
    _cloned_hists[ name ] [ "gen_boson_mass" ] = new TH1D ( (name + "_gen_boson_mass").c_str(), ";Boson Mass;Number of Events", 200,0,200 );  
    _cloned_hists[ name ] [ "gen_mjj" ] = new TH1D ( (name + "_gen_mjj").c_str(), ";M_{jj};Number of Events", 3500,0,3500 );  
    _cloned_hists[ name ] [ "gen_detajj" ] = new TH1D ( (name + "_gen_detajj").c_str(), ";#Delta#eta_{jj};Number of Events", 50,0,7 );  
    _cloned_hists[ name ] [ "gen_dphijj" ] = new TH1D ( (name + "_gen_dphijj").c_str(), ";#Delta#phi_{jj};Number of Events", 50,0, M_PI );  
    _cloned_hists[ name ] [ "gen_mindphi_jetmet" ] = new TH1D ( (name + "_gen_mindphi_jetmet").c_str(), ";min-#Delta#phi(j,p_{T}^{V});Number of Events", 50,0, M_PI );  
    _cloned_hists[ name ] [ "LHE_HT" ] = new TH1D ( (name + "_LHE_HT").c_str(), ";HT;Number of Events",3000,0,3000);  
    _cloned_hists[ name ] [ "gen_weight" ] = new TH1D ( (name + "_gen_weight").c_str(), ";weight;Number of Events",100,-15000,15000);  
    _cloned_hists[ name ] [ "gen_jetpt0" ] = new TH1D ( (name + "_gen_jetpt0").c_str(), ";jet 0 p_{T};Number of Events", 100,0,200 );  

    _cloned_hists[ name ] [ "gen_dressed_lepton_eta" ] = new TH1D ( (name + "_gen_dressed_lepton_eta").c_str(), ";Leading lepton #eta;Number of Events",100,-8,8);  
    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] = new TH1D ( (name + "_gen_dressed_lepton_pt").c_str(), ";Leading lepton p_{T};Number of Events",110,0,1100);  

  }

  if ( name == "All" ){
    _cloned_hists[ name ] [ "gen_events" ] = new TH1D ( (name + "_gen_events").c_str(), ";;Number of Events",2,0.5,2.5 );  
    _cloned_hists[ name ] [ "LHE_HT" ] = new TH1D ( (name + "_LHE_HT").c_str(), ";HT;Number of Events",3000,0,3000);  
    _cloned_hists[ name ] [ "gen_weight" ] = new TH1D ( (name + "_gen_weight").c_str(), ";weight;Number of Events",100,-15000,15000);  
    _cloned_hists[ name ] [ "gen_boson_eta" ] = new TH1D ( (name + "_gen_boson_eta").c_str(), ";Boson #eta;Number of Events", 40,-8,8 );  
  }
  if ( name == "Default2ndLep" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 110,0,1100 );  
    
  }

  if ( name.find("Mjj")!=std::string::npos ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), ";Boson p_{T};Number of Events", 110,0,1100 );  
    
  }



}


// void HiggsInvisible::CalculateTriggerCellVariables(  ){

//   _event_variables[  "ex_sum_forward"  ] = exsum_forward;

// }



void HiggsInvisible::FillAllHists( std::string name ){
  
  //  CalculateTriggerCellVariables();
  
  double weight = genWeight;


  if ( name == "Default" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( gen_boson_pt, weight );
    _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( gen_boson_eta, weight);
    _cloned_hists[ name ] [ "gen_boson_mass" ] -> Fill( _event_variables["gen_boson_mass"], weight );
    _cloned_hists[ name ] [ "gen_mjj" ] -> Fill( gen_mjj, weight);
    _cloned_hists[ name ] [ "gen_detajj" ] -> Fill( gen_detajj, weight );
    _cloned_hists[ name ] [ "gen_dphijj" ] -> Fill( gen_dphijj, weight );
    _cloned_hists[ name ] [ "gen_mindphi_jetmet" ] -> Fill( gen_mindphi_jetmet, weight );
    _cloned_hists[ name ] [ "LHE_HT" ] -> Fill( LHE_HT, weight );
    _cloned_hists[ name ] [ "gen_weight" ] -> Fill( genWeight );
    _cloned_hists[ name ] [ "gen_dressed_lepton_eta" ] -> Fill( GenDressedLepton_eta[0], genWeight );
    _cloned_hists[ name ] [ "gen_dressed_lepton_pt" ] -> Fill( GenDressedLepton_pt[0], genWeight );
    _cloned_hists[ name ] [ "gen_jetpt0" ] -> Fill( GenJet_pt[0], genWeight );

  }
  if ( name == "All" ){
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 1 );
    _cloned_hists[ name ] [ "gen_events" ] -> Fill( 2, weight );
    _cloned_hists[ name ] [ "LHE_HT" ] -> Fill( LHE_HT, weight );
    _cloned_hists[ name ] [ "gen_weight" ] -> Fill( genWeight );
    _cloned_hists[ name ] [ "gen_boson_eta" ] -> Fill( gen_boson_eta, weight );
  }

  if ( name == "Default2ndLep" ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( gen_boson_pt, weight );
  }

  if ( name.find( "Mjj" )!=std::string::npos ){
    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( gen_boson_pt, weight );
  }

}

void HiggsInvisible::CalculateVariables(){

  //Reset various quantities
  _event_variables.clear();
  

  //Boson phi
  int lep1 = 0;
  int lep2 = 0;
  int mother = 0;
  double boson_pt = 0;
  double boson_mass = 0;
  for (unsigned int part = 0; part < nGenPart; part++){
    
    //    if ( (std::abs(GenPart_pdgId[part])>10 and abs(GenPart_pdgId[part]) < 17) and ( (GenPart_status[part] == 1 and (GenPart_statusFlags[part] & 0x1)>0) or ((GenPart_statusFlags[part] & 0x1)>0 and (GenPart_statusFlags[part] & 0x2)>0) ) ){

    if ( (std::abs(GenPart_pdgId[part])>10 && abs(GenPart_pdgId[part]) < 17) && ( (GenPart_status[part] == 1 && (GenPart_statusFlags[part] & 0x1)>0) || ((GenPart_statusFlags[part] & 0x1)>0 && (GenPart_statusFlags[part] & 0x2)>0) ) ){
      
    //    if ( (std::abs(GenPart_pdgId[part])>10 and abs(GenPart_pdgId[part]) < 17)){

      if (GenPart_genPartIdxMother[part]>=0){
	 mother = GenPart_genPartIdxMother[part];

	 if (GenPart_pdgId[mother] == 23 || std::abs(GenPart_pdgId[mother]) == 24){
	   _event_variables["gen_boson_phi"] = GenPart_phi[mother];
	   boson_mass = GenPart_mass[mother];

	   std::cout << "bos mass = " << GenPart_mass[mother] << std::endl;
	   //	   boson_found = True;
	   break;
	 }
	 else{
	   if (GenPart_pdgId[part]>0){
	     lep1 = part;
	   }	  
	   else{
	     lep2 = part;
	   }

	 }
      }
      else{
	if (GenPart_pdgId[part]>0){
	  lep1 = part;
	}
	else{
	  lep2 = part;
	}

	
      }    
    }
  }
    std::cout << nGenPart << " - " << mother << " - " << lep1 << " - " << lep2 <<  " - " << _event_variables["gen_boson_phi"] << std::endl;


}

bool HiggsInvisible::CalculateCuts( std::string name ){

  bool passcut = 0;
  
  
  //  std::cout << _zll << " - " << _wln << std::endl;
  //  if ( name.find ("Default") !=std::string::npos ){
  if ( name == "Default" ){

    //Delta phi between jet and boson

    //
    TLorentzVector boson, jet;
    double boson_mass = 91.18;
    if ( _wln ) boson_mass = 80.37;
    bool pass_mindphi_jetbos = true;

    boson.SetPtEtaPhiM( gen_boson_pt, gen_boson_eta, _event_variables["gen_boson_phi"], boson_mass );
    _event_variables["gen_boson_mass"] = boson.M();

    for (unsigned int g = 0; g<(nGenJet<3?nGenJet:3); g++){
      if ( GenJet_pt[g] > 30 ){
    	jet.SetPtEtaPhiM( GenJet_pt[g], GenJet_eta[g], GenJet_phi[g], GenJet_mass[g] );
	//	std::cout << std::abs(boson.DeltaPhi( jet )) << std::endl;
    	if ( std::abs(boson.DeltaPhi( jet )) < 0.5 ){ 
	  pass_mindphi_jetbos = false;
	  //	  std::cout << g << " - " <<  GenJet_pt[g] << std::endl;
	  break;
	}
      }
    }
    //      std::cout << "888 " << pass_mindphi_jetbos << " - " << gen_mindphi_jetmet <<std::endl;

   
    if ( GenJet_pt[0] > 0 
	 //	 && GenJet_pt[1] > 40 
	 
	 // && GenJet_eta[0] *  GenJet_eta[1] < 0 &&
	 // (std::abs(GenJet_eta[0]) < 3 || std::abs(GenJet_eta[1])<3 ) &&
	 // //	 (gen_mindphi_jetmet) > 0.5 &&
	 // pass_mindphi_jetbos &&
	 // gen_dphijj < 1.5 && 
	 // gen_mjj > 200 && 
	 // gen_detajj > 1 
	 // //for k-factors

	 // //	 (  (_zll||_wln) ? (std::abs(GenDressedLepton_eta[0]) < 2.4) : true) 
	 // //	 GenDressedLepton_pt[0] > 20//think
	 
	 // && LHE_HT>70
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


  if ( name == "All" ){
    //    if (  LHE_HT>70 ){
      passcut = true;
      //    }
  }
  

  return passcut;
  
}
