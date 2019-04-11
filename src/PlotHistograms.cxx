#include "HiggsPlotting.h"
#include "CmdLine.h"
#include "Plotter.h"

int main( int argc, char ** argv ){

  CmdLine cmd( argc, argv ) ;

  HiggsPlotting * higgs = new HiggsPlotting ( &cmd );

  gErrorIgnoreLevel = 2000;


  higgs->LoadAllHistograms();

  higgs->Rebin();


  higgs->CombineHistograms();


  higgs->PlotAllHistograms();

  higgs->MakeTar();

  delete higgs;

  return 0;

}

void HiggsPlotting::MakeTar(  ){

  std::string  out_directory = _cmd->string_val( "--outdir" );
  std::system( ("cd plots; tar -zcf " + out_directory + ".tar.gz " + out_directory + ";  cd ../plots").c_str() );

}
