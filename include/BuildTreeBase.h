#ifndef BuildTreeBase_h
#define BuildTreeBase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <math.h>
#include <iostream>
#include <vector>

class BuildTreeBase {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain


  // Declaration of leaf types
   // Declaration of leaf types
   UInt_t          run;
   ULong64_t       event;
   UInt_t          nGenJetAK8;
   Float_t         GenJetAK8_eta[3];   //[nGenJetAK8]
   Float_t         GenJetAK8_mass[3];   //[nGenJetAK8]
   Float_t         GenJetAK8_phi[3];   //[nGenJetAK8]
   Float_t         GenJetAK8_pt[3];   //[nGenJetAK8]
   UInt_t          nGenJet;
   Float_t         GenJet_eta[17];   //[nGenJet]
   Float_t         GenJet_mass[17];   //[nGenJet]
   Float_t         GenJet_phi[17];   //[nGenJet]
   Float_t         GenJet_pt[17];   //[nGenJet]
   UInt_t          nGenPart;
   Float_t         GenPart_eta[86];   //[nGenPart]
   Float_t         GenPart_mass[86];   //[nGenPart]
   Float_t         GenPart_phi[86];   //[nGenPart]
   Float_t         GenPart_pt[86];   //[nGenPart]
   Int_t           GenPart_genPartIdxMother[86];   //[nGenPart]
   Int_t           GenPart_pdgId[86];   //[nGenPart]
   Int_t           GenPart_status[86];   //[nGenPart]
   Int_t           GenPart_statusFlags[86];   //[nGenPart]
   Float_t         Generator_binvar;
   Float_t         Generator_scalePDF;
   Float_t         Generator_weight;
   Float_t         Generator_x1;
   Float_t         Generator_x2;
   Float_t         Generator_xpdf1;
   Float_t         Generator_xpdf2;
   Int_t           Generator_id1;
   Int_t           Generator_id2;
   UInt_t          nGenVisTau;
   Float_t         GenVisTau_eta[3];   //[nGenVisTau]
   Float_t         GenVisTau_mass[3];   //[nGenVisTau]
   Float_t         GenVisTau_phi[3];   //[nGenVisTau]
   Float_t         GenVisTau_pt[3];   //[nGenVisTau]
   Int_t           GenVisTau_charge[3];   //[nGenVisTau]
   Int_t           GenVisTau_genPartIdxMother[3];   //[nGenVisTau]
   Int_t           GenVisTau_status[3];   //[nGenVisTau]
   Float_t         genWeight;
   Float_t         LHEWeight_originalXWGTUP;
   UInt_t          nLHEPdfWeight;
   Float_t         LHEPdfWeight[102];   //[nLHEPdfWeight]
   UInt_t          nLHEScaleWeight;
   Float_t         LHEScaleWeight[9];   //[nLHEScaleWeight]
   Float_t         LHE_HT;
   Float_t         LHE_HTIncoming;
   Float_t         LHE_Vpt;
   UChar_t         LHE_Njets;
   UChar_t         LHE_Nb;
   UChar_t         LHE_Nc;
   UChar_t         LHE_Nuds;
   UChar_t         LHE_Nglu;
   UChar_t         LHE_NpNLO;
   UChar_t         LHE_NpLO;
   UInt_t          nLHEPart;
   Float_t         LHEPart_pt[4];   //[nLHEPart]
   Float_t         LHEPart_eta[4];   //[nLHEPart]
   Float_t         LHEPart_phi[4];   //[nLHEPart]
   Float_t         LHEPart_mass[4];   //[nLHEPart]
   Int_t           LHEPart_pdgId[4];   //[nLHEPart]
   Float_t         GenMET_phi;
   Float_t         GenMET_pt;
   UInt_t          nGenDressedLepton;
   Float_t         GenDressedLepton_eta[4];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_mass[4];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_phi[4];   //[nGenDressedLepton]
   Float_t         GenDressedLepton_pt[4];   //[nGenDressedLepton]
   Int_t           GenDressedLepton_pdgId[4];   //[nGenDressedLepton]
   Int_t           genTtbarId;
   Int_t           GenJetAK8_partonFlavour[3];   //[nGenJetAK8]
   UChar_t         GenJetAK8_hadronFlavour[3];   //[nGenJetAK8]
   Int_t           GenJet_partonFlavour[17];   //[nGenJet]
   UChar_t         GenJet_hadronFlavour[17];   //[nGenJet]
   Float_t         gen_boson_pt;
   Float_t         gen_boson_eta;
   Float_t         gen_mjj;
   Float_t         gen_detajj;
   Float_t         gen_dphijj;
   Float_t         gen_mindphi_jetmet;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nGenJetAK8;   //!
   TBranch        *b_GenJetAK8_eta;   //!
   TBranch        *b_GenJetAK8_mass;   //!
   TBranch        *b_GenJetAK8_phi;   //!
   TBranch        *b_GenJetAK8_pt;   //!
   TBranch        *b_nGenJet;   //!
   TBranch        *b_GenJet_eta;   //!
   TBranch        *b_GenJet_mass;   //!
   TBranch        *b_GenJet_phi;   //!
   TBranch        *b_GenJet_pt;   //!
   TBranch        *b_nGenPart;   //!
   TBranch        *b_GenPart_eta;   //!
   TBranch        *b_GenPart_mass;   //!
   TBranch        *b_GenPart_phi;   //!
   TBranch        *b_GenPart_pt;   //!
   TBranch        *b_GenPart_genPartIdxMother;   //!
   TBranch        *b_GenPart_pdgId;   //!
   TBranch        *b_GenPart_status;   //!
   TBranch        *b_GenPart_statusFlags;   //!
   TBranch        *b_Generator_binvar;   //!
   TBranch        *b_Generator_scalePDF;   //!
   TBranch        *b_Generator_weight;   //!
   TBranch        *b_Generator_x1;   //!
   TBranch        *b_Generator_x2;   //!
   TBranch        *b_Generator_xpdf1;   //!
   TBranch        *b_Generator_xpdf2;   //!
   TBranch        *b_Generator_id1;   //!
   TBranch        *b_Generator_id2;   //!
   TBranch        *b_nGenVisTau;   //!
   TBranch        *b_GenVisTau_eta;   //!
   TBranch        *b_GenVisTau_mass;   //!
   TBranch        *b_GenVisTau_phi;   //!
   TBranch        *b_GenVisTau_pt;   //!
   TBranch        *b_GenVisTau_charge;   //!
   TBranch        *b_GenVisTau_genPartIdxMother;   //!
   TBranch        *b_GenVisTau_status;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_LHEWeight_originalXWGTUP;   //!
   TBranch        *b_nLHEPdfWeight;   //!
   TBranch        *b_LHEPdfWeight;   //!
   TBranch        *b_nLHEScaleWeight;   //!
   TBranch        *b_LHEScaleWeight;   //!
   TBranch        *b_LHE_HT;   //!
   TBranch        *b_LHE_HTIncoming;   //!
   TBranch        *b_LHE_Vpt;   //!
   TBranch        *b_LHE_Njets;   //!
   TBranch        *b_LHE_Nb;   //!
   TBranch        *b_LHE_Nc;   //!
   TBranch        *b_LHE_Nuds;   //!
   TBranch        *b_LHE_Nglu;   //!
   TBranch        *b_LHE_NpNLO;   //!
   TBranch        *b_LHE_NpLO;   //!
   TBranch        *b_nLHEPart;   //!
   TBranch        *b_LHEPart_pt;   //!
   TBranch        *b_LHEPart_eta;   //!
   TBranch        *b_LHEPart_phi;   //!
   TBranch        *b_LHEPart_mass;   //!
   TBranch        *b_LHEPart_pdgId;   //!
   TBranch        *b_GenMET_phi;   //!
   TBranch        *b_GenMET_pt;   //!
   TBranch        *b_nGenDressedLepton;   //!
   TBranch        *b_GenDressedLepton_eta;   //!
   TBranch        *b_GenDressedLepton_mass;   //!
   TBranch        *b_GenDressedLepton_phi;   //!
   TBranch        *b_GenDressedLepton_pt;   //!
   TBranch        *b_GenDressedLepton_pdgId;   //!
   TBranch        *b_genTtbarId;   //!
   TBranch        *b_GenJetAK8_partonFlavour;   //!
   TBranch        *b_GenJetAK8_hadronFlavour;   //!
   TBranch        *b_GenJet_partonFlavour;   //!
   TBranch        *b_GenJet_hadronFlavour;   //!
   TBranch        *b_gen_boson_pt;   //!
   TBranch        *b_gen_boson_eta;   //!
   TBranch        *b_gen_mjj;   //!
   TBranch        *b_gen_detajj;   //!
   TBranch        *b_gen_dphijj;   //!
   TBranch        *b_gen_mindphi_jetmet;   //!

   //   BuildTreeBase(TTree *tree=0);
   BuildTreeBase();
   virtual ~BuildTreeBase();
   //   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    Cut();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     InitRuns(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef BuildTreeBase_cxx
//BuildTreeBase::BuildTreeBase(TTree *tree) : fChain(0)
BuildTreeBase::BuildTreeBase() : fChain(0)
{
}

BuildTreeBase::~BuildTreeBase()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t BuildTreeBase::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t BuildTreeBase::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void BuildTreeBase::Init(TTree *tree)
{

   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nGenJetAK8", &nGenJetAK8, &b_nGenJetAK8);
   fChain->SetBranchAddress("GenJetAK8_eta", GenJetAK8_eta, &b_GenJetAK8_eta);
   fChain->SetBranchAddress("GenJetAK8_mass", GenJetAK8_mass, &b_GenJetAK8_mass);
   fChain->SetBranchAddress("GenJetAK8_phi", GenJetAK8_phi, &b_GenJetAK8_phi);
   fChain->SetBranchAddress("GenJetAK8_pt", GenJetAK8_pt, &b_GenJetAK8_pt);
   fChain->SetBranchAddress("nGenJet", &nGenJet, &b_nGenJet);
   fChain->SetBranchAddress("GenJet_eta", GenJet_eta, &b_GenJet_eta);
   fChain->SetBranchAddress("GenJet_mass", GenJet_mass, &b_GenJet_mass);
   fChain->SetBranchAddress("GenJet_phi", GenJet_phi, &b_GenJet_phi);
   fChain->SetBranchAddress("GenJet_pt", GenJet_pt, &b_GenJet_pt);
   fChain->SetBranchAddress("nGenPart", &nGenPart, &b_nGenPart);
   fChain->SetBranchAddress("GenPart_eta", GenPart_eta, &b_GenPart_eta);
   fChain->SetBranchAddress("GenPart_mass", GenPart_mass, &b_GenPart_mass);
   fChain->SetBranchAddress("GenPart_phi", GenPart_phi, &b_GenPart_phi);
   fChain->SetBranchAddress("GenPart_pt", GenPart_pt, &b_GenPart_pt);
   fChain->SetBranchAddress("GenPart_genPartIdxMother", GenPart_genPartIdxMother, &b_GenPart_genPartIdxMother);
   fChain->SetBranchAddress("GenPart_pdgId", GenPart_pdgId, &b_GenPart_pdgId);
   fChain->SetBranchAddress("GenPart_status", GenPart_status, &b_GenPart_status);
   fChain->SetBranchAddress("GenPart_statusFlags", GenPart_statusFlags, &b_GenPart_statusFlags);
   fChain->SetBranchAddress("Generator_binvar", &Generator_binvar, &b_Generator_binvar);
   fChain->SetBranchAddress("Generator_scalePDF", &Generator_scalePDF, &b_Generator_scalePDF);
   fChain->SetBranchAddress("Generator_weight", &Generator_weight, &b_Generator_weight);
   fChain->SetBranchAddress("Generator_x1", &Generator_x1, &b_Generator_x1);
   fChain->SetBranchAddress("Generator_x2", &Generator_x2, &b_Generator_x2);
   fChain->SetBranchAddress("Generator_xpdf1", &Generator_xpdf1, &b_Generator_xpdf1);
   fChain->SetBranchAddress("Generator_xpdf2", &Generator_xpdf2, &b_Generator_xpdf2);
   fChain->SetBranchAddress("Generator_id1", &Generator_id1, &b_Generator_id1);
   fChain->SetBranchAddress("Generator_id2", &Generator_id2, &b_Generator_id2);
   fChain->SetBranchAddress("nGenVisTau", &nGenVisTau, &b_nGenVisTau);
   fChain->SetBranchAddress("GenVisTau_eta", GenVisTau_eta, &b_GenVisTau_eta);
   fChain->SetBranchAddress("GenVisTau_mass", GenVisTau_mass, &b_GenVisTau_mass);
   fChain->SetBranchAddress("GenVisTau_phi", GenVisTau_phi, &b_GenVisTau_phi);
   fChain->SetBranchAddress("GenVisTau_pt", GenVisTau_pt, &b_GenVisTau_pt);
   fChain->SetBranchAddress("GenVisTau_charge", GenVisTau_charge, &b_GenVisTau_charge);
   fChain->SetBranchAddress("GenVisTau_genPartIdxMother", GenVisTau_genPartIdxMother, &b_GenVisTau_genPartIdxMother);
   fChain->SetBranchAddress("GenVisTau_status", GenVisTau_status, &b_GenVisTau_status);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("LHEWeight_originalXWGTUP", &LHEWeight_originalXWGTUP, &b_LHEWeight_originalXWGTUP);
   fChain->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight, &b_nLHEPdfWeight);
   fChain->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight, &b_LHEPdfWeight);
   fChain->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight, &b_nLHEScaleWeight);
   fChain->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight, &b_LHEScaleWeight);
   fChain->SetBranchAddress("LHE_HT", &LHE_HT, &b_LHE_HT);
   fChain->SetBranchAddress("LHE_HTIncoming", &LHE_HTIncoming, &b_LHE_HTIncoming);
   fChain->SetBranchAddress("LHE_Vpt", &LHE_Vpt, &b_LHE_Vpt);
   fChain->SetBranchAddress("LHE_Njets", &LHE_Njets, &b_LHE_Njets);
   fChain->SetBranchAddress("LHE_Nb", &LHE_Nb, &b_LHE_Nb);
   fChain->SetBranchAddress("LHE_Nc", &LHE_Nc, &b_LHE_Nc);
   fChain->SetBranchAddress("LHE_Nuds", &LHE_Nuds, &b_LHE_Nuds);
   fChain->SetBranchAddress("LHE_Nglu", &LHE_Nglu, &b_LHE_Nglu);
   fChain->SetBranchAddress("LHE_NpNLO", &LHE_NpNLO, &b_LHE_NpNLO);
   fChain->SetBranchAddress("LHE_NpLO", &LHE_NpLO, &b_LHE_NpLO);
   fChain->SetBranchAddress("nLHEPart", &nLHEPart, &b_nLHEPart);
   fChain->SetBranchAddress("LHEPart_pt", LHEPart_pt, &b_LHEPart_pt);
   fChain->SetBranchAddress("LHEPart_eta", LHEPart_eta, &b_LHEPart_eta);
   fChain->SetBranchAddress("LHEPart_phi", LHEPart_phi, &b_LHEPart_phi);
   fChain->SetBranchAddress("LHEPart_mass", LHEPart_mass, &b_LHEPart_mass);
   fChain->SetBranchAddress("LHEPart_pdgId", LHEPart_pdgId, &b_LHEPart_pdgId);
   fChain->SetBranchAddress("GenMET_phi", &GenMET_phi, &b_GenMET_phi);
   fChain->SetBranchAddress("GenMET_pt", &GenMET_pt, &b_GenMET_pt);
   fChain->SetBranchAddress("nGenDressedLepton", &nGenDressedLepton, &b_nGenDressedLepton);
   fChain->SetBranchAddress("GenDressedLepton_eta", GenDressedLepton_eta, &b_GenDressedLepton_eta);
   fChain->SetBranchAddress("GenDressedLepton_mass", GenDressedLepton_mass, &b_GenDressedLepton_mass);
   fChain->SetBranchAddress("GenDressedLepton_phi", GenDressedLepton_phi, &b_GenDressedLepton_phi);
   fChain->SetBranchAddress("GenDressedLepton_pt", GenDressedLepton_pt, &b_GenDressedLepton_pt);
   fChain->SetBranchAddress("GenDressedLepton_pdgId", GenDressedLepton_pdgId, &b_GenDressedLepton_pdgId);
   fChain->SetBranchAddress("genTtbarId", &genTtbarId, &b_genTtbarId);
   fChain->SetBranchAddress("GenJetAK8_partonFlavour", GenJetAK8_partonFlavour, &b_GenJetAK8_partonFlavour);
   fChain->SetBranchAddress("GenJetAK8_hadronFlavour", GenJetAK8_hadronFlavour, &b_GenJetAK8_hadronFlavour);
   fChain->SetBranchAddress("GenJet_partonFlavour", GenJet_partonFlavour, &b_GenJet_partonFlavour);
   fChain->SetBranchAddress("GenJet_hadronFlavour", GenJet_hadronFlavour, &b_GenJet_hadronFlavour);
   fChain->SetBranchAddress("gen_boson_pt", &gen_boson_pt, &b_gen_boson_pt);
   fChain->SetBranchAddress("gen_boson_eta", &gen_boson_eta, &b_gen_boson_eta);
   fChain->SetBranchAddress("gen_mjj", &gen_mjj, &b_gen_mjj);
   fChain->SetBranchAddress("gen_detajj", &gen_detajj, &b_gen_detajj);
   fChain->SetBranchAddress("gen_dphijj", &gen_dphijj, &b_gen_dphijj);
   fChain->SetBranchAddress("gen_mindphi_jetmet", &gen_mindphi_jetmet, &b_gen_mindphi_jetmet);
   Notify();
}

void BuildTreeBase::InitRuns(TTree *tree)
{
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   Notify();
}


Bool_t BuildTreeBase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void BuildTreeBase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
//Int_t BuildTreeBase::Cut(Long64_t entry)
Int_t BuildTreeBase::Cut()
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef BuildTreeBase_cxx
