#include "HiggsInvisible.h"
#include "CmdLine.h"

int main( int argc, char ** argv ){

  CmdLine cmd( argc, argv ) ;


  std::string filein   = cmd.string_val( "--filein" ) ;
  std::string treename = cmd.string_val( "--treename", "hgcalTriggerNtuplizer/HGCalTriggerNtuple" ) ;


  HiggsInvisible * higgs = new HiggsInvisible ( &cmd );



  higgs->SetupFillHistograms();


  higgs->Fill();


  higgs->Save();

  delete higgs;

  return 0;



}
