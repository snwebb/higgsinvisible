#include "HiggsPlotting.h"
#include "CmdLine.h"
#include "Plotter.h"

int main( int argc, char ** argv ){

  CmdLine cmd( argc, argv ) ;

  HiggsPlotting * higgs = new HiggsPlotting ( &cmd );

  gErrorIgnoreLevel = 2000;

  higgs->LoadAllHistograms(); //Load histograms into memory

  higgs->Rebin(); //Rebin them where appropriate

  higgs->CombineHistograms(); //Combine the histograms from the sub-samples based on their cross-section weight

  higgs->EvaluateUncertainties(); //Evaluate the uncertainties on the 1D histograms
  higgs->EvaluateUncertainties2D(); //Evaluate the uncertainties on the 2D histograms

  higgs->PlotAllHistograms(); //Plot the histograms
  higgs->MakeTar(); //Make a tarball of the plots

  return 0;

}

void HiggsPlotting::MakeTar(  ){

  std::string  out_directory = _cmd->string_val( "--outdir" );
  std::system( ("cd plots; tar -zcf " + out_directory + ".tar.gz " + out_directory + ";  cd ../plots").c_str() );

}
