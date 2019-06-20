#ifndef _Plotter_h_
#define _Plotter_h_


//#include "Helpers.h"
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
  TFile * _fileout;

 protected:

  TLegend * _legend;
  TCanvas * _canvas;
  TLatex * _latex;
  //  Helpers _helper;
  std::string  _outdir;

  void SetLegendXY(Double_t x1, Double_t y1, Double_t x2, Double_t y2);

 public:

  Plotter();
  Plotter( CmdLine * cmd );
  ~Plotter();


  template< class T > void SaveFile( std::vector<T>& graphs ){
    _fileout = new TFile ( (_outdir+"/graphs.root").c_str(), "RECREATE");
    for (auto &graph: graphs ){
      graph->Write( );
    };
    _fileout->Close();
    _fileout->Delete();
  }

  template< class T > void Draw( T hist, TString legend = "", TString savename = "temp", bool logy=false ){
    
    std::vector<T> vechist = {hist};
    std::vector<TString> leghist = {legend};
    Draw( vechist, leghist, savename, logy );

  }

  template< class T > void Draw( std::vector<T>& hist, std::vector<TString> legend = {""}, TString savename = "temp", bool logy=false ){
    
    _legend->Clear();
    TCanvas * c = _canvas;
    c->SetCanvasSize(800, 600);
    gPad->SetTicks(1,1);
    gPad->SetLogy(logy);
    SetLegendXY( 0.7, 0.5, 0.82, 0.75  );

    int i = 0;
    for (auto &histo : hist){
      _legend->AddEntry( histo, legend.at(i) , "L");    
      histo->SetLineColor(i+1);
      if(i>3){
	histo->SetLineColor(i+2);
      }
      histo->SetTitle("");
      if ( i == 0 )
	histo->Draw();
      else
	histo->Draw("same");
      i++;
    }
    //    _legend->Draw("same");
    
    if ( !logy ){
      c->SaveAs("plots/" + TString(_outdir) + "/linear/" + savename + ".root");
      c->SaveAs("plots/" + TString(_outdir) + "/linear/" + savename + ".png");
    }
    if ( logy ){
      c->SaveAs("plots/" + TString(_outdir) + "/log/" + savename + ".png");
    }

  }

  template< class T > void DrawRatio( T hist1, T hist2, TString legend = "", TString savename = "temp"){
    std::cout << hist2->GetName() << std::endl;
    std::cout << hist1->GetName() << std::endl;
    std::cout << hist2->GetName() << std::endl;
    
    T Ratio = (T) hist1->Clone( TString(hist1->GetName()) + TString(hist2->GetName()) );

    Ratio->Divide(hist2);
    Ratio->SetMaximum(2.8);
    Ratio->SetMinimum(0.3);
    Draw( Ratio, legend, savename );

  }
  
};


#endif
