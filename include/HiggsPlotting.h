#ifndef _HiggsPlotting_h_
#define _HiggsPlotting_h_
#include "Plotter.h"
#include "Helpers.h"
#include "CmdLine.h"
#include <cstring>
#include <time.h>
#include <TLorentzVector.h>
#include <TMultiGraph.h>
#include <TMatrixD.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFitResult.h>
#include <TRandom3.h>
#include <TVector2.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TEllipse.h>
#include <TProfile.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TKey.h>
#include <TLatex.h>
#include <sys/stat.h>
#include <iomanip>
#include <cmath>
#include <map>

class HiggsPlotting{

 private:

  /***** General *****/
  CmdLine * _cmd ;
  std::string _filein;
  std::string _fileout;

  TDirectory * _origDir ;	
  std::vector<std::string> _HistoSets;

  typedef std::map< TString, TH1D* > histmap;
  typedef std::map< TString, TH2D* > histmap2D;
  typedef std::map< TString, histmap > clonemap;
  typedef std::map< TString, histmap2D > clonemap2D;
  typedef std::map< std::string, double > doublemap;

  clonemap _cloned_hists;
  clonemap2D _cloned_hists2D;

  Helpers _helper;

 public:

  HiggsPlotting(CmdLine * cmd);
  ~HiggsPlotting();

  void DoNothing();

  void LoadAllHistograms();
  void Rebin();
  void CombineHistograms();
  void EvaluateUncertainties();
  void EvaluateUncertainties2D();
  void PlotAllHistograms();

  void MakeTar();


};

#endif
