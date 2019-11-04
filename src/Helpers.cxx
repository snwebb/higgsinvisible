#include "Helpers.h"

void XXX (int line) {std::cout << "I am here: " << line << std::endl << std::endl;}

Helpers::Helpers(){
  
  TH1::SetDefaultSumw2();
  
  _counter = 0;

}

double Helpers::normalizedPhi(double phi){

  double o2pi = 1./(2.*M_PI);
  if (std::fabs(phi) <= M_PI) return phi;
  double n = std::round(phi*o2pi);
  return phi - n*(2.*M_PI);

}



double Helpers::deltaPhi(double phi1, double phi2){

  return normalizedPhi( phi1 - phi2 );

}


float Helpers::binning(TH1F* h){

  float max=h->GetBinLowEdge(h->GetNbinsX()+1);
  float min=h->GetBinLowEdge(1);
  float bin=(max-min)/h->GetNbinsX();
  return bin;
}


// TEventList* Helpers::getEventList(TString file, TString tree_name, TString var, TString cut, int nbin, float min, float max){

//   TChain * tree = new TChain(tree_name);
//   tree->Add(file);
 
//   tree->Draw(var+Form(">>g(%i, %f, %f)", nbin, min, max),cut,"goff");

//   TEventList* g =  (TEventList*) ( (TEventList*)gDirectory->Get("g"))->Clone( var + counter() );

//   return g;

// }

TH1F* Helpers::single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  // TH1F* g=new TH1F("g","g",nbin,min,max);
  // g->Sumw2();
  //g->SetBinErrorOption(TH1::kPoisson);
 
  tree->Draw(var+Form(">>g(%i, %f, %f)", nbin, min, max),cut,"goff");

  TH1F* g =  (TH1F*) ( (TH1F*)gDirectory->Get("g"))->Clone( var + counter() );

  //  delete tree;
  return g;

}


void Helpers::single_plot(TH1F* g, TString file, TString tree_name, TString var, TString cut){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);
  tree->Draw(var+">>"+g->GetName(),cut,"goff");

  delete tree;
  return;

}






TH1F* Helpers::single_plot(std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++)
    tree->Add(files[i]);

  TH1F* g=new TH1F("g","g",nbin,min,max);
  g=new TH1F("g","g",nbin,min,max);

  //g->Sumw2();
  g->SetBinErrorOption(TH1::kPoisson);

  tree->Draw(var+">>g",cut,"goff");
  delete tree;

//cout<<"tree deleted"<<endl;
  return g;

}




TH1F* Helpers::single_plot(std::vector<TString> files, TString tree_name, TString var, std::vector<TString> cut, int nbin, float min, float max){


  TH1F* g=new TH1F("g","g",nbin,min,max);
  //g->Sumw2();
  g->SetBinErrorOption(TH1::kPoisson);

  for(unsigned int i=0; i<files.size(); i++){
    g->Add(single_plot(files[i],tree_name,var,cut[i],nbin,min,max));
  }

  return g;

}



TH1D* Helpers::single_plot_d(std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++)
    tree->Add(files[i]);

  TH1D* g=new TH1D("g","g",nbin,min,max);
  //g->Sumw2();
  g->SetBinErrorOption(TH1::kPoisson);

  tree->Draw(var+">>g",cut,"goff");

  return g;

}




TH1F* Helpers::single_plot(TString file, TString tree_name, TString var, TString cut, int nbin, double* x){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH1F* g=new TH1F("g","g",nbin,x);
  //g->Sumw2();
  g->SetBinErrorOption(TH1::kPoisson);

  tree->Draw(var+">>g",cut,"goff");
  delete tree;



  return g;

}





TH1F* Helpers::single_plot(std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, double* x){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0;i<files.size();i++)
    tree->Add(files[i]);

  TH1F* g=new TH1F("g","g",nbin,x);
  //g->Sumw2();
  g->SetBinErrorOption(TH1::kPoisson);

  tree->Draw(var+">>g",cut,"goff");


  return g;

}





//TH2F* Helpers::single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2){
TH2F* Helpers::single_plot2D(TString file, TString tree_name, TString var, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  tree->Draw(var+Form(">>h(%i,%f,%f,%i,%f,%f)",nbin1,min1,max1,nbin2,min2,max2),cut,"goff");
  TH2F* g=(TH2F*) ((TH2F*)gDirectory->Get("h"))->Clone( tree_name + counter() );
  gDirectory->Get("h")->Delete();
  return g;
}





TH2F* Helpers::single_plot2D(TString file, TString tree_name, TString var, TString cut, int nbin1, double * x, int nbin2, float min2, float max2){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH2F *h = new TH2F("h","",nbin1, x, nbin2, min2, max2);
  //  tree->Draw(var+Form(">>h(%i,%d,%i,%f,%f)",nbin1,min1,max1,nbin2,min2,max2),cut,"goff");
  tree->Draw(var+">>h",cut,"goff");
  TH2F* g=(TH2F*) ((TH2F*)gDirectory->Get("h"))->Clone( tree_name + counter() );
  h->Delete();
  return g;
}






TH2F* Helpers::single_plot2D(std::vector<TString> files, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++){
    tree->Add(files[i]);
  }

  tree->Draw(var2+":"+var1+Form(">>h(%i,%f,%f,%i,%f,%f)",nbin1,min1,max1,nbin2,min2,max2),cut,"goff");
  TH2F* g=(TH2F*) ((TH2F*)gDirectory->Get("h"))->Clone( files.at(0) + counter() );
  return g;
}



TH2F* Helpers::single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbinx, double* x, int nbiny, double* y){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  TH2F* g=new TH2F("g","g",nbinx,x,nbiny,y);
  g->Sumw2();

  tree->Draw(var2+":"+var1+">>g",cut,"goff");

  return g;

}





TH3F* Helpers::single_plot3D(TString file, TString tree_name, TString var1, TString var2,TString var3, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2, int nbin3, float min3, float max3){

  TChain * tree = new TChain(tree_name);
  tree->Add(file);

  tree->Draw(var3+":"+var2+":"+var1+Form(">>h(%i,%f,%f,%i,%f,%f,%i,%f,%f)",nbin1,min1,max1,nbin2,min2,max2,nbin3,min3,max3),cut,"goff");
  TH3F* g=(TH3F*) ((TH3F*)gDirectory->Get("h"))->Clone();
  return g;
}





std::vector<TH1F*> Helpers::sort_histo(std::vector<TH1F*> h){
  
  float max=0;
  unsigned int imax=0;
  for(unsigned int i=0;i<h.size();i++){
    float m=h[i]->GetMaximum();
    if(m>max){
      max=m;
      imax=i;
    }
  }
  std::vector<TH1F*> new_h;
  new_h.push_back(h[imax]);
  for(unsigned int i=0;i<h.size();i++){
    if(i!=imax)
      new_h.push_back(h[i]);
  }

  return new_h;
}







TH1F* Helpers::single_plot(TString hname, std::vector<TString> files, TString tree_name, TString var, TString cut, int nbin, float min, float max){

  TChain * tree = new TChain(tree_name);
  for(unsigned int i=0; i<files.size(); i++)
    tree->Add(files[i]);

  TH1F* g=new TH1F(hname,hname,nbin,min,max);

  //g->Sumw2();
  g->SetBinErrorOption(TH1::kPoisson);

  tree->Draw(var+">>"+hname,cut,"goff");
  return g;

}






void Helpers::makeBinContentsPositive(TH1* histogram, bool verbosity)
{
  if ( verbosity ) {
    std::cout << "<makeBinContentsPositive>:" << std::endl;
    std::cout << " integral(" << histogram->GetName() << ") = " << histogram->Integral() << std::endl;
  }
  double integral_original = histogram->Integral();
  if ( integral_original < 0. ) integral_original = 0.;
  /*if ( verbosity ) {
    std::cout << " integral_original = " << integral_original << std::endl;
    }*/
  int numBins = histogram->GetNbinsX();
  for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
    double binContent_original = histogram->GetBinContent(iBin);
    double binError2_original = pow(histogram->GetBinError(iBin),2);
    if ( binContent_original < 0. ) {
      double binContent_modified = 0.;
      double binError2_modified = binError2_original + pow(binContent_original - binContent_modified,2);
      assert(binError2_modified >= 0.);
      if ( verbosity ) {
	std::cout << "bin #" << iBin << " (x =  " << histogram->GetBinCenter(iBin) << "): binContent = " << binContent_original << " +/- " << TMath::Sqrt(binError2_original)
          << " --> setting it to binContent = " << binContent_modified << " +/- " << TMath::Sqrt(binError2_modified) << std::endl;
      }
      histogram->SetBinContent(iBin, binContent_modified);
      histogram->SetBinError(iBin, TMath::Sqrt(binError2_modified));
    }
  }
  double integral_modified = histogram->Integral();
  if ( integral_modified < 0. ) integral_modified = 0.;
  /*if ( verbosity ) {
    std::cout << " integral_modified = " << integral_modified << std::endl;
    }*/
  if ( integral_modified > 0. ) {
    double sf = integral_original/integral_modified;
    /*if ( verbosity ) {
      std::cout << "--> scaling histogram by factor = " << sf << std::endl;
      }*/
    histogram->Scale(sf);
  } else {
    for ( int iBin = 0; iBin <= (numBins + 1); ++iBin ) {
      histogram->SetBinContent(iBin, 0.);
    }
  }
  /*if ( verbosity ) {
    std::cout << " integral(" << histogram->GetName() << ") = " << histogram->Integral() << std::endl;
    }*/
}

TString Helpers::counter(){

  _counter ++;
  return TString( std::to_string(_counter).c_str() );

}


double Helpers::Get2dX(TF1 * f, double y){

  double  a = f->GetParameter(2);
  double  b = f->GetParameter(1);
  double  c = f->GetParameter(0);

  double x = ( -b + std::sqrt( b*b - 4*a*(c-y) ) ) / (2 * a);

  return x;

}

double Helpers::Get2dX(double a, double b, double c, double y){

  double x = ( -b + std::sqrt( b*b - 4*a*(c-y) ) ) / (2 * a);
  return x;

}
