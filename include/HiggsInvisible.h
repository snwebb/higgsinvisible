#ifndef _HiggsInvisible_h_
#define _HiggsInvisible_h_
#define XXX std::cout << "I am here: " << __LINE__ << std::endl << std::endl;
#include "BuildTreeBase.h"
#include "Plotter.h"
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

//#include "Helpers.h"

class HiggsInvisible: public BuildTreeBase {

 private:

  /***** General *****/
  CmdLine * _cmd ;
  /* std::string _in_directory; */
  /* std::string _out_directory; */
  std::string _filein;
  std::string _fileout;
  TFile * _fout;

  TDirectory * _origDir ;	
  int _max_events;
  std::vector<std::string> _HistoSets;
  TChain * _chain    ;

  typedef std::map< std::string, TH1D* > histmap;
  typedef std::map< std::string, histmap > clonemap;
  typedef std::map< std::string, double > doublemap;
  //  typedef std::map< std::string, bool > boolmap;

  clonemap _cloned_hists;
  doublemap _event_variables;
  //  boolmap _cuts;

  bool _wln = false;
  bool _znn = false;
  bool _zll = false;

 public:

  HiggsInvisible(CmdLine * cmd);
  ~HiggsInvisible();

  void DoNothing();

  void SetupFillHistograms();

  void LoadHistoTemplates( std::string name );

  void MakeAllHistograms( std::vector<std::string> &HistoSets);

  void Loop();

  void Fill();

  void FillAllHists( std::string name );

  void CalculateVariables( );

  bool CalculateCuts( std::string name );

  bool FileExists( std::string file );

  void Save();



  void LoadAllHistograms();
  void PlotAllHistograms();

};

#endif
