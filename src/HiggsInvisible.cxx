#include "HiggsInvisible.h"

HiggsInvisible::HiggsInvisible( CmdLine * cmd ){

  _cmd = cmd;
  _origDir = gDirectory ;
  _filein = _cmd->string_val( "--filein" ) ;
  //  _out_directory = _cmd->string_val( "--out_directory" ) ;
  _fileout = _cmd->string_val( "--fileout" ) ;
  _max_events =  _cmd->int_val( "--max_events"  , -1);

  TH1::SetDefaultSumw2();
  _HistoSets.push_back( "Default" );
  _HistoSets.push_back( "Default2ndLep" );
  _HistoSets.push_back( "All" );

  _HistoSets.push_back( "Default-Mjj-200-500" );
  _HistoSets.push_back( "Default-Mjj-500-1000" );
  _HistoSets.push_back( "Default-Mjj-1000-1500" );
  _HistoSets.push_back( "Default-Mjj-1500-5000" );


  if ( _filein.find("WJetsToLNu")!=std::string::npos ) _wln = true;
  if ( _filein.find("ZJetsToNuNu")!=std::string::npos ) _znn = true;
  if ( _filein.find("DYJetsToLL")!=std::string::npos ) _zll = true;

}


HiggsInvisible::~HiggsInvisible() {
  //    _fout->ls();
  // gDirectory = _origDir ;

  // for(auto &it1 : _cloned_hists) {
  //   for(auto &it2 : it1.second) {
  //     if ( it2.second ) it2.second->Delete();
  //   }
  // }

}

void HiggsInvisible::DoNothing(){


}


void HiggsInvisible::SetupFillHistograms(){

  _fout = new TFile( TString(_fileout), "RECREATE" );

  _chain   = new TChain ( "Events" );

  //  std::string remotedir = "root://cms-xrd-global.cern.ch//store/user/sawebb/SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-stc/181025_100629/0000/";

  for ( int i = 0; i < 1; i++ ){
    _chain  ->Add ( TString(_filein) );
  }


  MakeAllHistograms( _HistoSets );





}

void HiggsInvisible::Fill(){

  Init(  _chain );
  Loop( );

}

void HiggsInvisible::Loop( ){

  //Loop over events

  std::cout << "Beginning Event Loop" << std::endl;

  if (fChain == 0) return;

  std::cout << "Getting Number of Entries" << std::endl;

  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("gen_boson_pt",1);
  fChain->SetBranchStatus("gen_boson_eta",1);
  fChain->SetBranchStatus("gen_mjj",1);
  fChain->SetBranchStatus("gen_detajj",1);
  fChain->SetBranchStatus("gen_dphijj",1);
  fChain->SetBranchStatus("gen_mindphi_jetmet",1);
  fChain->SetBranchStatus("LHE_HT",1);

  fChain->SetBranchStatus("GenJet_pt",1);
  fChain->SetBranchStatus("GenJet_eta",1);
  fChain->SetBranchStatus("GenJet_phi",1);
  fChain->SetBranchStatus("GenJet_mass",1);

  fChain->SetBranchStatus("GenDressedLepton_eta",1);
  fChain->SetBranchStatus("GenDressedLepton_pt",1);

  fChain->SetBranchStatus("genWeight",1);
  fChain->SetBranchStatus("nGenJet",1);

  fChain->SetBranchStatus("GenPart_pdgId",1);
  fChain->SetBranchStatus("GenPart_mass",1);
  fChain->SetBranchStatus("GenPart_statusFlags",1);
  fChain->SetBranchStatus("GenPart_genPartIdxMother",1);
  fChain->SetBranchStatus("GenPart_phi",1);
  



  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry % 10000 == 0 ) {
      std::cout << jentry << "/" << nentries  << "\n" ;
    }

    if ( _max_events != -1 ){
      if ( jentry > _max_events ) break;
    }


    CalculateVariables();

    for (auto& names : _HistoSets ){
      if ( CalculateCuts( names ) ){
	FillAllHists( names );
      }
    }



  }


}


bool HiggsInvisible::FileExists( std::string file ){

  struct stat buf;
  if (  stat (  ( file ).c_str(), &buf ) == 0)
    return true;
  else{
    return false;
  }

}

void HiggsInvisible::Save(){

  //  std::system( ("mkdir -p output/" + _out_directory  )   .c_str() );
  //  _fout->cd();

  // for(auto &it1 : _cloned_hists) {
  //   for(auto &it2 : it1.second) {
  //     it2.second->Write();
  //   }
  // }

  //f_hists->Close();
  
  _fout->Write();
  _fout->Close();
    

}


//////////
