#ifndef _Plotter_h_
#define _Plotter_h_


#include "Helpers.h"
#include "CmdLine.h"
#include "TFile.h"
#include "TLegend.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLatex.h"
#include <iostream>

class Plotter{

 private:

  void InitialiseLegend();
  void InitialiseCanvas();
  void InitialiseLatex();
  //  std::vector<HistObject> _histlist;
  std::map<std::string,TFile*> _fileout;

 protected:

  TLegend * _legend;
  TCanvas * _canvas;
  TLatex * _latex;
  std::string  _outdir;

  double lower_bound = NAN;
  double upper_bound = NAN;

  double legx1 = 0.5;
  double legx2 = 0.7;
  double legy1 = 0.7;
  double legy2 = 0.8;

 public:

  Plotter(  );
  Plotter( CmdLine * cmd, Helpers & helper );
  ~Plotter();
  Helpers& _helper;


  void SetLegendXY(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

  void ResetConfig(){

    lower_bound = NAN;
    upper_bound = NAN;
  };

  void SetRangeUser(double low, double high){

    lower_bound = low;
    upper_bound = high;

  };


  template< class T > void SaveToFile( T graph, TString name, std::string outputfilename="output.root", std::string root_dir = "kfactors_shape"){
    std::vector<T> graphs = {graph};
    std::vector<TString> names = {name};
    SaveToFile(graphs, names,  outputfilename, root_dir);
  }

  template< class T > void SaveToFile( std::vector<T>& graphs, std::vector<TString>& names, std::string outputfilename, std::string root_dir = "kfactors_shape" ){
    TDirectory * dir = gDirectory;
    if ( _fileout[outputfilename] == 0 ){
      _fileout[outputfilename] = new TFile ( ("plots/"+_outdir+"/" + outputfilename + ".root").c_str(), "RECREATE");
    }
    if ( _fileout[outputfilename]->GetDirectory(TString(root_dir)) == 0 ){
      _fileout[outputfilename]->mkdir(TString(root_dir));
    }
    _fileout[outputfilename]->cd(TString(root_dir));
    
    int i=0;
    for (auto &graph: graphs ){
      graph->Write( names.at(i));
      i++;
    };
    dir->cd();
    //_fileout->Close();
    //    _fileout->Delete();
  }

  template< class T > void Draw( T hist, TString legend = "", TString savename = "temp", bool logy=false, TString OPT= "" ){
    
    std::vector<T> vechist = {hist};
    std::vector<TString> leghist = {legend};
    Draw( vechist, leghist, savename, false, logy, OPT );


  }
  template< class T > void DrawError( std::vector<T>& hist, std::vector<T>& err, std::vector<TString> legend = {""}, TString savename = "temp", bool ratio = false, bool logy=false){
    
    for ( int j=0;j<hist.size();j++){
      for ( int i=1;i<hist.at(j)->GetXaxis()->GetNbins()+1;i++){
	hist.at(j)->SetBinError( i, std::sqrt(std::pow(hist.at(j)->GetBinError(i),2) + std::pow(err.at(j)->GetBinContent(i),2)) );
	//	hist.at(j)->SetBinError( i, std::sqrt(0 + std::pow(err.at(j)->GetBinContent(i),2)) );
	//hist.at(j)->SetBinError( i, 0 );
      }
    }

    Draw( hist, legend, savename, ratio, logy );
    
  }

  template< class T > void Draw( std::vector<T>& hist, std::vector<TString> legend = {""}, TString savename = "temp", bool ratio = false, bool logy=false, TString OPT= "" ){
    
    TLegend *_legend = new TLegend(legx1, legy1, legx2, legy2);
    _legend->SetFillColor(0);
    _legend->SetBorderSize(0);
    _legend->SetTextSize(0.04);

    TCanvas * c = _canvas;
    c->SetCanvasSize(650, 600);

    TPad* p1 = 0;
    TPad* p2 = 0;

    c->cd();
    if ( ratio ){
      p1 = new TPad("p1"+_helper.counter(),"",0.0,0.351,1.0,1.0,0,0,0);
      p2 = new TPad("p2"+_helper.counter(),"",0.0,0.0,1.0,0.35,0,0,0);
      p1->SetBottomMargin(0);
      p1->SetTopMargin(0.08);
      p2->SetBottomMargin(0.33);
      p2->SetTopMargin(0.03);
      p1->Draw();
      p2->Draw();
      p1->cd();
      p1->SetTicks(1,1);
      p1->SetLogy(logy);
    }
    else{
      gPad->SetTicks(1,1);
      gPad->SetLogy(logy);
    }

    int i = 0;
    for (auto &histo : hist){
      _legend->AddEntry( histo, legend.at(i) , "L");    
      histo->SetLineColor(i+1);
      if(i>3){
	histo->SetLineColor(i+2);
      }
      histo->SetTitle("");
      if ( i == 0 ){
	histo->Draw(OPT);  
	if ( !std::isnan(lower_bound) ) histo->GetYaxis()->SetRangeUser(lower_bound, upper_bound);  
      }
      else
	histo->Draw("same"+OPT);

     histo->GetYaxis()->SetTitleOffset(1.9);
     histo->GetYaxis()->SetTitleFont(43);
     histo->GetYaxis()->SetLabelFont(43);
     histo->GetYaxis()->SetTitleSize(25);
     histo->GetYaxis()->SetLabelSize(25);
     histo->Draw("same"+OPT);

     //      histo->SaveAs( "plots/" + TString(_outdir) + "/linear/" + savename + "_histo.root" );
      i++;
    }


    _legend->Draw();



    //Ratio plot

    if (ratio){
      p2->cd();
      for (unsigned i =1;i<hist.size();i++){
	
	T rat = (T)hist.at(i)->Clone( ("Ratio"+ std::to_string(i)).c_str());
       	rat->Divide(hist.at(0)); 

	

	if ( i == 1 ){
	  rat->Draw();
	}
	else
	  rat->Draw("E1same");

	rat->SetMaximum( 1.4 );
	rat->SetMinimum( 0.6 );
	/* rat->SetMaximum( 2 ); */
	/* rat->SetMinimum( 0 ); */
	rat->GetYaxis()->SetTitleOffset(0.5);
	rat->GetYaxis()->CenterTitle();
	rat->GetXaxis()->SetTitleFont(43);
        rat->GetXaxis()->SetLabelFont(43);
	rat->GetXaxis()->SetTitleOffset(3.5);
	rat->GetXaxis()->SetTitleSize(25);
	rat->GetXaxis()->SetLabelSize(25);
	rat->GetXaxis()->SetNdivisions(505);
	rat->GetYaxis()->SetNdivisions(505);
        rat->GetYaxis()->SetTitleFont(43);
        rat->GetYaxis()->SetLabelFont(43);
        rat->GetYaxis()->SetTitleSize(25);
	rat->GetYaxis()->SetLabelSize(25);
	rat->GetYaxis()->SetTitleOffset(2.0);

	rat->Draw("same");
      }
    }

    if ( !logy ){
      c->SaveAs("plots/" + TString(_outdir) + "/linear/" + savename + ".root");
      c->SaveAs("plots/" + TString(_outdir) + "/linear/" + savename + ".png");
      //c->SaveAs("plots/" + TString(_outdir) + "/linear/" + savename + ".pdf");
    }
    if ( logy ){
      c->SaveAs("plots/" + TString(_outdir) + "/log/" + savename + ".png");
      //      c->SaveAs("plots/" + TString(_outdir) + "/log/" + savename + ".pdf");
    }



    if (p1)    p1->Delete();
    if (p2)    p2->Delete();
    if (_legend) _legend->Delete();
    //    ResetConfig();

  }

  template< class T > T DrawRatio( T hist1, T hist2, TString legend = "", TString savename = "temp"){
    /* std::cout << hist2->GetName() << std::endl; */
    /* std::cout << hist1->GetName() << std::endl; */
    /* std::cout << hist2->GetName() << std::endl; */
    
    T Ratio = (T) hist1->Clone( TString(hist1->GetName()) + TString(hist2->GetName()) );

    //    std::cout << savename << " - " << Ratio->Integral() << " - " << hist2->Integral() << std::endl;

    Ratio->Divide(hist2);
    Ratio->SetMaximum(2.8);
    Ratio->SetMinimum(0.3);


    for (int i = 1;i<Ratio->GetNbinsX()+1;i++){
      if ( Ratio->GetBinContent(i) <= 0 )
	Ratio->SetBinContent(i,1);
    }

    Draw( Ratio, legend, savename, false );
    //Ratio->Delete();
    return Ratio;
    
  }
  
};


#endif
