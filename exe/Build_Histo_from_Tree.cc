#include <iostream>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "THStack.h"
#include "TText.h"
#include "TH2F.h"
#include "TObjArray.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TCollection.h"

#include "../include/RUtil.h"
#include "../include/RLoader.h"
#include "../include/RStyle.h"

using namespace std;


int main()
{
	// Root file in which the histograms will be saved
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/Zprime/BKG_Estimation/rootfiles/ZprimeM_Different_Cases.root","RECREATE");
	//Load data files
	//TChain *TTbar = RLoader::GetTTbarFiles();
	//std::cout << "Number of Entries in TTbar: " << TTbar->GetEntries() << std::endl;
	TChain	*QCD = RLoader::GetQCDFiles();
	std::cout << "Number of Entries in QCD: " << QCD->GetEntries() << std::endl;
	//TChain	*Zprime = RLoader::GetZprimeFiles(); 
	//std::cout << "Number of Entries in Zprime: " << Zprime->GetEntries() << std::endl;
	//TChain *TotalBKG = RLoader::GetTTbarFiles();
	//std::cout << TotalBKG->GetEntries() << std::endl;
	//TotalBKG->Add(QCD);
  //std::cout << "Nummber of Entries in the whole Background: " << TotalBKG->GetEntries() << std::endl;
  
  
  //variables
  Float_t Weight_XS{0},TTM_Zprime_M{0},TTM_Mistagrate{0},TTM_separated_highest_bottoms_M{0},TTM_AK8_top_candidates_highest_M{0},TTM_highest_Ws_M{0},TTM_no_top_separated_highest_bottoms_M{0},TTM_no_top_Zprime_M{0},Signal_Topfirst_Zprime_M{0};
  
  
  //Set branches
  QCD->SetBranchStatus("*",0);
  
  QCD->SetBranchStatus("Weight_XS",1);  
  QCD->SetBranchAddress("Weight_XS",&Weight_XS);
  
  QCD->SetBranchStatus("TTM_Mistagrate",1);  
  QCD->SetBranchAddress("TTM_Mistagrate",&TTM_Mistagrate);
  
  QCD->SetBranchStatus("TTM_Zprime_M",1);  
  QCD->SetBranchAddress("TTM_Zprime_M",&TTM_Zprime_M);
  
  QCD->SetBranchStatus("TTM_separated_highest_bottoms_M",1);  
  QCD->SetBranchAddress("TTM_separated_highest_bottoms_M",&TTM_separated_highest_bottoms_M);
  
  QCD->SetBranchStatus("TTM_AK8_top_candidates_highest_M",1);  
  QCD->SetBranchAddress("TTM_AK8_top_candidates_highest_M",&TTM_AK8_top_candidates_highest_M);
  
  QCD->SetBranchStatus("TTM_highest_Ws_M",1);  
  QCD->SetBranchAddress("TTM_highest_Ws_M",&TTM_highest_Ws_M);
  
  QCD->SetBranchStatus("TTM_no_top_separated_highest_bottoms_M",1);  
  QCD->SetBranchAddress("TTM_no_top_separated_highest_bottoms_M",&TTM_no_top_separated_highest_bottoms_M);
  
  QCD->SetBranchStatus("TTM_no_top_Zprime_M",1);  
  QCD->SetBranchAddress("TTM_no_top_Zprime_M",&TTM_no_top_Zprime_M);
  
  QCD->SetBranchStatus("Signal_Topfirst_Zprime_M",1);
  QCD->SetBranchAddress("Signal_Topfirst_Zprime_M",&Signal_Topfirst_Zprime_M);
  
  
  //creating histograms
  TH1F* hZmass = new TH1F("hZmass","M(Z') Background",30,0,5000);
  TH1F* hZmassTopfirst = new TH1F("hZmassTopfirst","M(Z') Background Topfirst",30,0,5000);
  TH1F* hZmassnotop = new TH1F("hZmassnotop","M(Z') Background no top",30,0,5000);
  TH1F* hmisstag = new TH1F("hmisstag","misstagrate",100,0,1);
  //TH1F* hbotmass = new TH1F("hbotmass","Massdistriubtion of b-Quarks with the highest p_{T}",15,0,150);
	//TH1F* hAK8mass = new TH1F("hAK8mass","Massdistriubtion of AK8 Jets with the highest p_{T}",20,0,200);
	//TH1F* hWmass = new TH1F("hWmass","Massdistriubtion of W-Bosons with the highest p_{T}",15,0,150);
	//TH1F* hbotmassnotop = new TH1F("hbotmassnotop","Massdistriubtion of b-Quarks with the highest p_{T} without top tag",15,0,150);
  
 
 	// sum over entries and fill histogramms
  Long64_t Nentries = QCD->GetEntries();
  
  for(Long64_t iEntry=0;iEntry<Nentries;iEntry++)
  {
		QCD->GetEntry(iEntry);
		if(TTM_Zprime_M>0) hZmass->Fill(TTM_Zprime_M,Weight_XS*TTM_Mistagrate);
		if(TTM_no_top_Zprime_M>0) hZmassnotop->Fill(TTM_no_top_Zprime_M,Weight_XS*TTM_Mistagrate);
		if(Signal_Topfirst_Zprime_M>0) hZmassTopfirst->Fill(Signal_Topfirst_Zprime_M,Weight_XS);
		if(TTM_Mistagrate>0)  hmisstag->Fill(TTM_Mistagrate);
		//if(TTM_separated_highest_bottoms_M>0) hbotmass->Fill(iEntry,Weight_XS);
		//if(TTM_AK8_top_candidates_highest_M>0) hAK8mass->Fill(iEntry,Weight_XS);
		//if(TTM_highest_Ws_M>0) hWmass->Fill(iEntry,Weight_XS);
		//if(TTM_separated_highest_bottoms_no_top_M>0) hbotmassnotop->Fill(iEntry,Weight_XS);
    
     if(iEntry%100000==0)
     {
      std::cout << "Processing Event Number   " << iEntry << std::endl;
     }
   }


	//Write and save
  file->cd();
  hZmass->Write("TTM_Zprime_M");
  hZmassTopfirst->Write("TTM_Zprime_M");
  hZmassnotop->Write("TTM_Zprime_no_top_M");
  hmisstag->Write("misstag");
  file->Close();
  
  

}

