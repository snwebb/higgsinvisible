/******************************************************************************
HGC analysis code
Samuel Webb
Imperial College
***************************************************************************/

// Time-stamp: <2019-03-14 13:22:32 (snwebb)>

#include "HiggsInvisible.h"

void HiggsInvisible::MakeAllHistograms( std::vector<std::string> &HistoSets){

  std::cout << "Creating All Histograms" << std::endl;
  
  for (auto& names : HistoSets ){
    LoadHistoTemplates ( names );
  }
  
}

void HiggsInvisible::LoadHistoTemplates( std::string name ){

  if ( name == "test" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] = new TH1D ( (name + "_gen_boson_pt").c_str(), "", 100,0,1000 );  

  }

}


// void HiggsInvisible::CalculateTriggerCellVariables(  ){

//   _event_variables[  "ex_sum_forward"  ] = exsum_forward;

// }



void HiggsInvisible::FillAllHists( std::string name ){

  //  CalculateTriggerCellVariables();
  

  if ( name == "test" ){

    _cloned_hists[ name ] [ "gen_boson_pt" ] -> Fill( gen_boson_pt );

  }

}
