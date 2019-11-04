#ifndef _Helpers_h_
#define _Helpers_h_

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TRandom3.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TEventList.h>
#include <TEfficiency.h>
#include <TChain.h>
#include <THStack.h>
#include <TLatex.h>
#include <TProfile.h>
#include <TMath.h>
#include <TF1.h>
#include <TLine.h>
#include <TGaxis.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TGraphAsymmErrors.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TFitResult.h>
#include <TROOT.h>
#include <TVector.h>
#include <TVectorD.h>

#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm> 

//#include "HistObject.h"

extern void XXX(int line);



typedef std::map<std::array<int,3>,float> Histogram;
typedef std::tuple<double,double,double> GlobalPoint;

class Helpers{
  
 private:

  int _counter;

 public:
  
  Helpers();
  double normalizedPhi(double phi);
  double deltaPhi(double phi1, double phi2);
  float binning(TH1F* h);
  TH1F* single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, float min, float max);
  void single_plot(TH1F* g, TString file, TString tree_name, TString var, TString cut);
  TH1F* single_plot(std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max);
  TH1F* single_plot(std::vector<TString> files, TString tree_name, TString var, std::vector<TString> cut, int nbin, float min, float max);
  TH1D* single_plot_d(std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max);
  TH1F* single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, double* x);
  TH1F* single_plot(std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, double* x);
  TH2F* single_plot2D(TString file, TString tree_name, TString var, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2);
  TH2F* single_plot2D(TString file, TString tree_name, TString var, TString cut, int nbin1, double* x, int nbin2, float min2, float max2);
  TH2F* single_plot2D(std::vector<TString> files, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2);
  TH2F* single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbinx, double* x, int nbiny, double* y);

  TH3F* single_plot3D(TString file, TString tree_name, TString var1, TString var2,TString var3, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2, int nbin3, float min3, float max3);
  std::vector<TH1F*> sort_histo(std::vector<TH1F*> h);
  TH1F* single_plot(TString hname, std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max);
  void makeBinContentsPositive(TH1* histogram, bool verbosity=false);
  TString counter();
  double Get2dX(TF1 * f, double y);
  double Get2dX(double a, double b, double c, double y);
};

#endif
