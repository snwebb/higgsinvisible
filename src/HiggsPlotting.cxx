#include "HiggsPlotting.h"

HiggsPlotting::HiggsPlotting( CmdLine * cmd ){

  _cmd = cmd;
  _origDir = gDirectory ;
  TH1::SetDefaultSumw2();

}


HiggsPlotting::~HiggsPlotting() {

  gDirectory = _origDir ;

  for(auto &it1 : _cloned_hists) {
    for(auto &it2 : it1.second) {
      it2.second->Delete();
    }
  }

}

void HiggsPlotting::LoadAllHistograms(){


    //map of short name and filename

  std::map<TString,TString> filenames;

  filenames[ "ZLL-NLO-orig" ]     = "MC_DYJetsToLL_M-50-amcatnloFXFX.root";
  filenames[ "ZLL-NLO-ext" ] = "MC_DYJetsToLL_M-50-amcatnloFXFX-ext.root";
  filenames[ "ZLL-LO-70-100" ] = "MC_DYJetsToLL_M-50_HT-70to100.root";
  filenames[ "ZLL-LO-100-200" ] = "MC_DYJetsToLL_M-50_HT-100to200.root";
  filenames[ "ZLL-LO-100-200-ext" ] = "MC_DYJetsToLL_M-50_HT-100to200-ext.root";
  filenames[ "ZLL-LO-200-400" ] = "MC_DYJetsToLL_M-50_HT-200to400.root";
  filenames[ "ZLL-LO-200-400-ext" ] = "MC_DYJetsToLL_M-50_HT-200to400-ext.root";
  filenames[ "ZLL-LO-400-600" ] = "MC_DYJetsToLL_M-50_HT-400to600.root";
  filenames[ "ZLL-LO-400-600-ext" ] = "MC_DYJetsToLL_M-50_HT-400to600-ext.root";
  filenames[ "ZLL-LO-600-800" ] = "MC_DYJetsToLL_M-50_HT-600to800.root";
  filenames[ "ZLL-LO-800-1200" ] = "MC_DYJetsToLL_M-50_HT-800to1200.root";
  filenames[ "ZLL-LO-1200-2500" ] = "MC_DYJetsToLL_M-50_HT-1200to2500.root";
  filenames[ "ZLL-LO-2500-Inf" ] = "MC_DYJetsToLL_M-50_HT-2500toInf.root";

  filenames[ "WLN-NLO-0J" ] = "MC_WJetsToLNu_0J_TuneCP5-amcatnloFXFX.root";
  filenames[ "WLN-NLO-2J" ] = "MC_WJetsToLNu_2J_TuneCP5-amcatnloFXFX.root";
  filenames[ "WLN-LO-70-100" ] = "MC_WJetsToLNu_HT-70To100_TuneCP5.root";
  filenames[ "WLN-LO-100-200" ] = "MC_WJetsToLNu_HT-100To200_TuneCP5.root";
  filenames[ "WLN-LO-200-400" ] = "MC_WJetsToLNu_HT-200To400_TuneCP5.root";
  filenames[ "WLN-LO-400-600" ] = "MC_WJetsToLNu_HT-400To600_TuneCP5.root";
  filenames[ "WLN-LO-600-800" ] = "MC_WJetsToLNu_HT-600To800_TuneCP5.root";
  filenames[ "WLN-LO-800-1200" ] = "MC_WJetsToLNu_HT-800To1200_TuneCP5.root";
  filenames[ "WLN-LO-1200-2500" ] = "MC_WJetsToLNu_HT-1200To2500_TuneCP5.root";
  filenames[ "WLN-LO-2500-Inf" ] = "MC_WJetsToLNu_HT-2500ToInf_TuneCP5.root";
  
  filenames[ "ZNN-LO-100-200" ] = "MC_ZJetsToNuNu_HT-100To200.root";
  filenames[ "ZNN-LO-200-400" ] = "MC_ZJetsToNuNu_HT-200To400.root";
  filenames[ "ZNN-LO-400-600" ] = "MC_ZJetsToNuNu_HT-400To600-new-pmx.root";
  filenames[ "ZNN-LO-600-800" ] = "MC_ZJetsToNuNu_HT-600To800-new-pmx.root";
  filenames[ "ZNN-LO-800-1200" ] = "MC_ZJetsToNuNu_HT-800To1200.root";
  filenames[ "ZNN-LO-1200-2500" ] = "MC_ZJetsToNuNu_HT-1200To2500-new-pmx.root";
  filenames[ "ZNN-LO-2500ToInf" ] = "MC_ZJetsToNuNu_HT-2500ToInf.root";


  std::vector<std::string> plots = {"gen_boson_pt", "gen_boson_eta", "gen_mjj", "gen_detajj", "gen_dphijj", "gen_mindphi_jetmet", "LHE_HT", "gen_events", "gen_weight"};
  std::vector<std::string> histoSets = { "Default", "All", "Default-Mjj-200-500" };

  //then load into clonemap with short name and list of hists

  TH1D * loadHist = 0;
  TFile * loadFile = 0;

  TString filepath = "/vols/cms/snwebb/InvisibleOutput/Merged/";

  for (auto const& filename : filenames){

    loadFile = new TFile ( filepath + filename.second, "READ" );

    for ( auto histoset : histoSets ){
      for ( auto plotname : plots ){
	loadHist = 0;
	loadHist = (TH1D*) loadFile->Get( (histoset + "/" + histoset + "_" + plotname).c_str() );
	if ( loadHist != 0 ){ 
	  _cloned_hists[ filename.first ][ histoset + "_" + plotname ]  = (TH1D*) loadHist->Clone( ( filename.first + "_" + histoset + "_" + plotname   )  ) ;
	}
	
      }
      
    }
    
  }


}

void HiggsPlotting::Rebin(){

  std::map<TString,int> RebinValues;

  RebinValues[ "Default_gen_boson_pt" ] = 5;
  RebinValues[ "Default_gen_boson_eta" ] = 1;
  RebinValues[ "Default_gen_mjj" ] = 20;
  RebinValues[ "Default_gen_boson_detajj" ] = 1;
  RebinValues[ "Default_gen_boson_dphijj" ] = 1;
  RebinValues[ "Default_gen_mindphi_jetmet" ] = 1;
  RebinValues[ "Default_LHE_HT" ] = 20;
  RebinValues[ "All_LHE_HT" ] = 5;

  double bins[10] = {120,170,220,270,320,370,470,650,800,1000};
  for(auto &histsets : _cloned_hists) {
    for(auto &plot : histsets.second) {

      //      _cloned_hists[ histsets.first ][ plot.first ] = plot.second->Rebin( RebinValues[ plot.first ]  ) ;
      if ( RebinValues.count(plot.first)>0 ){

	if ( plot.first != "Default_gen_boson_pt" ){
	  plot.second->Rebin( RebinValues[ plot.first ]  ) ;
	}
	else{
	  plot.second =  (TH1D*) plot.second->Rebin( 9, plot.first + "_rebinnned" , bins ) ;
	}


      }

    }
  }

  


}

void HiggsPlotting::CombineHistograms(){

  
  //Add ZLL LO samples
  std::map<TString, double> _xs;
  std::map<TString, double> _sum;

  _xs[ "ZLL-LO-70-100" ] = 1.47E+02 * 1.9;
  _xs[ "ZLL-LO-100-200"] = 1.62E+02;
  _xs[ "ZLL-LO-100-200-ext"] = 1.61E+02;
  _xs[ "ZLL-LO-200-400"] = 4.84E+01;
  _xs[ "ZLL-LO-200-400-ext"] = 4.85E+01;
  _xs[ "ZLL-LO-400-600"] = 7.06E+00;
  _xs[ "ZLL-LO-400-600-ext"] = 7.03E+00;
  _xs[ "ZLL-LO-600-800"] = 1.75E+00 * 2;
  _xs[ "ZLL-LO-800-1200"] = 7.96E-01 * 2;
  _xs[ "ZLL-LO-1200-2500"] = 1.93E-01 * 2;
  _xs[ "ZLL-LO-2500-Inf"] = 3.47E-03 * 2;

  _xs[ "ZLL-NLO-orig"] = 6.47E+03;
  _xs[ "ZLL-NLO-ext"] = 6.52E+03;


  _xs[ "WLN-LO-70-100" ] = 1.47E+01;
  _xs[ "WLN-LO-100-200"] = 1.39E+03;
  _xs[ "WLN-LO-200-400"] = 4.03E+02;
  _xs[ "WLN-LO-400-600"] = 5.82E+01;
  _xs[ "WLN-LO-600-800"] = 1.29E+01;
  _xs[ "WLN-LO-800-1200"] = 5.49E+00;
  _xs[ "WLN-LO-1200-2500"] = 1.09E+00;
  _xs[ "WLN-LO-2500-Inf"] = 8.19E-03;


  _xs[ "WLN-NLO-0J"] = 55470 ;
  _xs[ "WLN-NLO-2J"] = 1940 ;

  for (auto & histset : _cloned_hists ){
    _sum[ histset.first ] = ((histset.second)[ "All_gen_events" ])->GetBinContent( 2 );
    std::cout << histset.first << " - " << ((histset.second)[ "All_gen_events" ])->GetBinContent( 2 ) << std::endl;
  }
  

  for (auto const& histset : _cloned_hists["ZLL-LO-70-100"]){
    
    _cloned_hists["ZLL-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-LO_" + histset.first );   
    _cloned_hists["ZLL-LO"][ histset.first ] ->Reset();

    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-70-100"     ][histset.first], 1E3* _xs["ZLL-LO-70-100"     ] / _sum["ZLL-LO-70-100"     ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200"    ][histset.first], 1E3* _xs["ZLL-LO-100-200"    ] / _sum["ZLL-LO-100-200"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-100-200-ext"][histset.first], 1E3* _xs["ZLL-LO-100-200-ext"] / _sum["ZLL-LO-100-200-ext"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400"    ][histset.first], 1E3* _xs["ZLL-LO-200-400"    ] / _sum["ZLL-LO-200-400"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-200-400-ext"][histset.first], 1E3* _xs["ZLL-LO-200-400-ext"] / _sum["ZLL-LO-200-400-ext"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600"    ][histset.first], 1E3* _xs["ZLL-LO-400-600"    ] / _sum["ZLL-LO-400-600"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-400-600-ext"][histset.first], 1E3* _xs["ZLL-LO-400-600-ext"] / _sum["ZLL-LO-400-600-ext"]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-600-800"    ][histset.first], 1E3* _xs["ZLL-LO-600-800"    ] / _sum["ZLL-LO-600-800"    ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-800-1200"   ][histset.first], 1E3* _xs["ZLL-LO-800-1200"   ] / _sum["ZLL-LO-800-1200"   ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-1200-2500"  ][histset.first], 1E3* _xs["ZLL-LO-1200-2500"  ] / _sum["ZLL-LO-1200-2500"  ]);
    _cloned_hists["ZLL-LO"][ histset.first ]->Add( _cloned_hists["ZLL-LO-2500-Inf"   ][histset.first], 1E3* _xs["ZLL-LO-2500-Inf"   ] / _sum["ZLL-LO-2500-Inf"   ]);

  }
  

  for (auto const& histset : _cloned_hists["ZLL-NLO-orig"]){
    
    _cloned_hists["ZLL-NLO"][ histset.first ] = (TH1D*) histset.second->Clone( "ZLL-NLO-orig_" + histset.first  );   
    _cloned_hists["ZLL-NLO"][ histset.first ]->Reset();

    // _cloned_hists["ZLL-NLO"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-orig"][histset.first]  ,  1000 * _xs["ZLL-NLO-orig"     ] / _sum["ZLL-NLO-orig"     ] );
    // _cloned_hists["ZLL-NLO"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-ext" ][histset.first]  ,  1000 * _xs["ZLL-NLO-ext"      ] / _sum["ZLL-NLO-ext"      ] );

    _cloned_hists["ZLL-NLO"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-orig"][histset.first]  ,  1  );
    _cloned_hists["ZLL-NLO"][ histset.first ]->Add( _cloned_hists["ZLL-NLO-ext" ][histset.first]  ,  1  );
    
  }



  for (auto const& histset : _cloned_hists["WLN-LO-70-100"]){ // 
    
    _cloned_hists["WLN-LO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-LO_" + histset.first );   
    _cloned_hists["WLN-LO"][ histset.first ] ->Reset();

    //    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-70-100"     ][histset.first],  1E3 * _xs["WLN-LO-70-100"     ] / _sum["WLN-LO-70-100"     ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-100-200"    ][histset.first],  1E3 * _xs["WLN-LO-100-200"    ] / _sum["WLN-LO-100-200"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-200-400"    ][histset.first],  1E3 * _xs["WLN-LO-200-400"    ] / _sum["WLN-LO-200-400"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-400-600"    ][histset.first],  1E3 * _xs["WLN-LO-400-600"    ] / _sum["WLN-LO-400-600"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-600-800"    ][histset.first],  1E3 * _xs["WLN-LO-600-800"    ] / _sum["WLN-LO-600-800"    ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-800-1200"   ][histset.first],  1E3 * _xs["WLN-LO-800-1200"   ] / _sum["WLN-LO-800-1200"   ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-1200-2500"  ][histset.first],  1E3 * _xs["WLN-LO-1200-2500"  ] / _sum["WLN-LO-1200-2500"  ]);
    _cloned_hists["WLN-LO"][ histset.first ]->Add( _cloned_hists["WLN-LO-2500-Inf"   ][histset.first],  1E3 * _xs["WLN-LO-2500-Inf"   ] / _sum["WLN-LO-2500-Inf"   ]);

  }
  

  for (auto const& histset : _cloned_hists["WLN-NLO-0J"]){
    
    _cloned_hists["WLN-NLO"][ histset.first ] = (TH1D*) histset.second->Clone( "WLN-NLO-0J_" + histset.first  );   
    _cloned_hists["WLN-NLO"][ histset.first ]->Reset();

    // _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-0J" ][histset.first]  , 1E3 * _xs["WLN-NLO-0J"     ] / _sum["WLN-NLO-0J"     ] );
    // _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-2J" ][histset.first]  , 1E3 * _xs["WLN-NLO-2J"      ] / _sum["WLN-NLO-2J"      ] );


    _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-0J"][histset.first]   ,  1  );
    _cloned_hists["WLN-NLO"][ histset.first ]->Add( _cloned_hists["WLN-NLO-2J" ][histset.first]  ,  1  );
    
  }
  

  
}


void HiggsPlotting::PlotAllHistograms(){

  Plotter plotter(_cmd);

  for (auto const& histset : _cloned_hists["ZLL-LO"]){

    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first );
    plotter.Draw( histset.second , "", "ZLL-LO-" + histset.first, true );

  }

  // plotter.Draw( _cloned_hists["ZLL-LO-70-100"]["All_gen_events"] , "", "70-100" );
  // plotter.Draw( _cloned_hists["ZLL-LO-100-200"]["All_gen_events"] , "", "100-200" );
  // plotter.Draw( _cloned_hists["ZLL-LO-100-200-ext"]["All_gen_events"] , "", "100-200-ext" );
  // plotter.Draw( _cloned_hists["ZLL-LO-200-400"]["All_gen_events"] , "", "200-400" );
  // plotter.Draw( _cloned_hists["ZLL-LO-200-400-ext"]["All_gen_events"] , "", "200-400-ext" );
  // plotter.Draw( _cloned_hists["ZLL-LO-400-600"]["All_gen_events"] , "", "400-600" );
  // plotter.Draw( _cloned_hists["ZLL-LO-400-600-ext"]["All_gen_events"] , "", "400-600-ext" );
  // plotter.Draw( _cloned_hists["ZLL-LO-600-800"]["All_gen_events"] , "", "600-800" );
  // plotter.Draw( _cloned_hists["ZLL-LO-800-1200"]["All_gen_events"] , "", "800-1200" );
  // plotter.Draw( _cloned_hists["ZLL-LO-1200-2500"]["All_gen_events"] , "", "1200-2500" );
  // plotter.Draw( _cloned_hists["ZLL-LO-2500-Inf"]["All_gen_events"] , "", "2500-Inf" );

  for (auto const& histset : _cloned_hists["ZLL-NLO"]){
    plotter.Draw( histset.second , "", "ZLL-NLO-" + histset.first );
  }

  for (auto const& histset : _cloned_hists["ZLL-NLO"]){
    plotter.DrawRatio( histset.second , _cloned_hists["ZLL-LO"][ histset.first ], "", "Ratio-ZLL-" + histset.first );
  }
  
  for (auto const& histset : _cloned_hists["WLN-LO"]){
    plotter.Draw( histset.second , "", "WLN-LO-" + histset.first );
    plotter.Draw( histset.second , "", "WLN-LO-" + histset.first, true );
  }
  for (auto const& histset : _cloned_hists["WLN-NLO"]){
    plotter.Draw( histset.second , "", "WLN-NLO-" + histset.first );
  }
  for (auto const& histset : _cloned_hists["WLN-NLO"]){
    plotter.DrawRatio( histset.second , _cloned_hists["WLN-LO"][ histset.first ], "", "Ratio-WLN-" + histset.first );
  }


  std::vector< TH1D*> z = {_cloned_hists["ZLL-NLO"]["Default_gen_boson_pt"], _cloned_hists["ZLL-LO"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> w = {_cloned_hists["WLN-NLO"]["Default_gen_boson_pt"], _cloned_hists["WLN-LO"]["Default_gen_boson_pt"]};

  std::vector< TH1D*> lo = {_cloned_hists["ZLL-LO"]["Default_gen_boson_pt"], _cloned_hists["WLN-LO"]["Default_gen_boson_pt"]};
  std::vector< TH1D*> nlo = {_cloned_hists["ZLL-NLO"]["Default_gen_boson_pt"], _cloned_hists["WLN-NLO"]["Default_gen_boson_pt"]};

  
  std::vector< TString > zleg = {"NLO", "LO"};
  std::vector< TString > loleg = {"z", "w"};

  plotter.Draw( z , zleg, "z-pt" , true);
  plotter.Draw( w , zleg, "w-pt" , true);

  plotter.Draw( z , zleg, "z-pt"  );
  plotter.Draw( w , zleg, "w-pt" );

  // plotter.Draw( lo , loleg, "lo-pt" , true);
  // plotter.Draw( lo , loleg, "lo-pt" );

  // plotter.Draw( nlo , loleg, "nlo-pt" , true);
  // plotter.Draw( nlo , loleg, "nlo-pt" );


}
