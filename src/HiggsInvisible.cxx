#include "HiggsInvisible.h"

HiggsInvisible::HiggsInvisible( CmdLine * cmd ){

  _cmd = cmd;
  _origDir = gDirectory ;
  _filein = _cmd->string_val( "--filein" ) ;
  //  _out_directory = _cmd->string_val( "--out_directory" ) ;
  _fileout = _cmd->string_val( "--fileout" ) ;
  _max_events =  _cmd->int_val( "--max_events"  , -1);

  TH1::SetDefaultSumw2();
  //  TH1::AddDirectory(kFALSE);
  _HistoSets.push_back( "Default" );

  _HistoSets.push_back( "Default_VTR" );




  _HistoSets.push_back( "Default_BARE" );
  // _HistoSets.push_back( "Default2ndLep" );
  _HistoSets.push_back( "All" );

  _HistoSets.push_back( "MJJ-200-500" );
  _HistoSets.push_back( "MJJ-500-1000" );
  _HistoSets.push_back( "MJJ-1000-1500" );
  _HistoSets.push_back( "MJJ-1500-5000" );

  // _HistoSets.push_back( "MJJ-200-500_VTR" );
  // _HistoSets.push_back( "MJJ-500-1000_VTR" );
  // _HistoSets.push_back( "MJJ-1000-1500_VTR" );
  // _HistoSets.push_back( "MJJ-1500-5000_VTR" );

  _HistoSets.push_back( "MJJ-200-500_BARE" );
  _HistoSets.push_back( "MJJ-500-1000_BARE" );
  _HistoSets.push_back( "MJJ-1000-1500_BARE" );
  _HistoSets.push_back( "MJJ-1500-5000_BARE" );

  // _HistoSets.push_back( "NJET1" );
  // _HistoSets.push_back( "NJET2" );
  // _HistoSets.push_back( "NJET3" ); 
  
  //  _HistoSets.push_back( "1JPt150" );

  _HistoSets.push_back( "non-VBF" );


  _HistoSets.push_back( "ZNN-No_gen_mjj" );
  _HistoSets.push_back( "ZNN-2Jets" );
  _HistoSets.push_back( "ZNN-2JetsEta" );
  _HistoSets.push_back( "ZNN-2JetsEtaDeltaEta" );
  _HistoSets.push_back( "ZNN-2JetsEtaDeltaEtaDeltaPhi" );



  // _HistoSets.push_back( "Default-Mjj-200-500" );
  // _HistoSets.push_back( "Default-Mjj-500-1000" );
  // _HistoSets.push_back( "Default-Mjj-1000-1500" );
  // _HistoSets.push_back( "Default-Mjj-1500-5000" );

  if ( _filein.find("WJetsToLNu")!=std::string::npos ) _wln = true;
  if ( _filein.find("ZJetsToNuNu")!=std::string::npos ) _znn = true;
  if ( _filein.find("DYJetsToLL")!=std::string::npos ) _zll = true;
  if ( _filein.find("DY2JetsToLL")!=std::string::npos ) _zll = true;
  if ( _filein.find("DY1JetsToLL")!=std::string::npos ) _zll = true;

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
  _runchain   = new TChain ( "Runs" );

  //  std::string remotedir = "root://cms-xrd-global.cern.ch//store/user/sawebb/SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-stc/181025_100629/0000/";

  for ( int i = 0; i < 1; i++ ){
    _chain  ->Add ( TString(_filein) );
    _runchain  ->Add ( TString(_filein) );
  }


  MakeAllHistograms( _HistoSets );

  //   _fout->mkdir("All");
   _fout->cd("All");
   _cloned_hists[ "All" ] [ "nRuns" ] = new TH1D ( ("All_nRuns"), ";;Number of Events", 1,0.5,1.5 );  
  


}

void HiggsInvisible::Fill(){


  InitRuns(  _runchain );
  LoopRuns( );

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

  nRuns /= double ( fChain->GetEntries() );

  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("gen_boson_pt",1);
  fChain->SetBranchStatus("gen_boson_eta",1);
  fChain->SetBranchStatus("gen_mjj",1);
  fChain->SetBranchStatus("gen_detajj",1);
  fChain->SetBranchStatus("gen_dphijj",1);
  fChain->SetBranchStatus("gen_mindphi_jetmet",1);
  fChain->SetBranchStatus("LHE_Njets",1);
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
  fChain->SetBranchStatus("GenPart_status",1);
  fChain->SetBranchStatus("GenPart_genPartIdxMother",1);
  fChain->SetBranchStatus("GenPart_phi",1);
  fChain->SetBranchStatus("GenPart_pt",1);
  fChain->SetBranchStatus("GenPart_eta",1);

  fChain->SetBranchStatus("LHEScaleWeight",1);
  fChain->SetBranchStatus("LHEPdfWeight",1);
  fChain->SetBranchStatus("nLHEScaleWeight",1);
  fChain->SetBranchStatus("nLHEPdfWeight",1);



  fChain->SetBranchStatus("event",1);
  // fChain->SetBranchStatus("nLHEScaleWeight",1);
  



  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    ResetVariables();

    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry % 10000 == 0 ) {
      std::cout << jentry << "/" << nentries  << "\n" ;
    }

    if ( _max_events != -1 ){
      if ( jentry == _max_events ) break;
    }


    CalculateVariables();

    for (auto& names : _HistoSets ){
      
      //      std::cout << names << " - " << CalculateCuts(names) << std::endl;

      if ( CalculateCuts( names ) ){
	//	std::cout << event << std::endl;
	FillAllHists( names );
      }
    }



  }


}



void HiggsInvisible::LoopRuns(){

  if (fChain == 0) return;
  nRuns = fChain->GetEntries();

  _cloned_hists[ "All" ] [ "nRuns" ] -> Fill( 1, double(nRuns) );

  std::cout << "nRuns = " << nRuns << std::endl;
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
