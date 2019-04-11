#include "Plotter.h"
#include <TVirtualFitter.h>
#include <TStyle.h>

Plotter::Plotter( CmdLine * cmd ){

  _outdir = cmd->string_val( "--outdir" );
  std::system( ("mkdir -p plots/" + _outdir )   .c_str() );
  std::system( ("mkdir -p plots/" + _outdir + "/linear/")   .c_str() );
  std::system( ("mkdir -p plots/" + _outdir + "/log/")   .c_str() );

  InitialiseLegend();
  InitialiseCanvas();
  InitialiseLatex();

  gStyle->SetOptStat(0);
}

Plotter::~Plotter(){

  delete _canvas;
  delete _legend;
  delete _latex;

}


void Plotter::InitialiseCanvas(){

  _canvas = new TCanvas("c","c",650,600);
  _canvas->SetLeftMargin(0.15);
  _canvas->SetRightMargin(0.15);

}

void Plotter::InitialiseLatex(){

  _latex = new TLatex();
  _latex->SetNDC();
  _latex->SetTextSize(0.03);
  _latex->SetText(0.2,0.9,"CMS Internal");

}

void Plotter::InitialiseLegend(){

  _legend = new TLegend(0.4,0.15,0.7,0.5);
  _legend->SetFillColor(0);
  _legend->SetBorderSize(0);
  _legend->SetTextSize(0.03);

}

void Plotter::SetLegendXY(Double_t x1, Double_t y1, Double_t x2, Double_t y2){

    _legend->SetX1NDC(x1);
    _legend->SetY1NDC(y1);
    _legend->SetX2NDC(x2);
    _legend->SetY2NDC(y2);

}





