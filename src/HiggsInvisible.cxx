#include "HiggsInvisible.h"

HiggsInvisible::HiggsInvisible( CmdLine * cmd ){

  _cmd = cmd;
  _origDir = gDirectory ;
  _filein = _cmd->string_val( "--filein" ) ;
  //  _out_directory = _cmd->string_val( "--out_directory" ) ;
  _fileout = _cmd->string_val( "--fileout" ) ;
  _max_events =  _cmd->int_val( "--max_events"  , -1);



  _HistoSets.push_back( "test" );
}


HiggsInvisible::~HiggsInvisible() {

  gDirectory = _origDir ;

  for(auto &it1 : _cloned_hists) {
    for(auto &it2 : it1.second) {
      it2.second->Delete();
    }
  }

}

void HiggsInvisible::DoNothing(){


}


void HiggsInvisible::SetupFillHistograms(){


  _chain   = new TChain ( "Events" );

  //  std::string remotedir = "root://cms-xrd-global.cern.ch//store/user/sawebb/SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-stc/181025_100629/0000/";

  for ( int i = 0; i < 1; i++ ){
    //    if (FileExists( (_in_directory + "/ntuples/ntuple_" + std::to_string(i) + ".root"   ).c_str()  )  )
    //      _chain  ->Add ( (_in_directory + "/ntuples/ntuple_" + std::to_string(i) + ".root"   ).c_str() );
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


    for (auto& names : _HistoSets ){
      FillAllHists( names );
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
  TFile * f_hists = new TFile( TString(_fileout), "RECREATE" );

  for(auto &it1 : _cloned_hists) {
    for(auto &it2 : it1.second) {
      it2.second->Write();
    }
  }

  f_hists->Close();


}


//////////
