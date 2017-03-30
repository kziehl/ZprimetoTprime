#include <iostream>
#include <cmath>
#include <cstring>


#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TChain.h"


#include "../include/RUtil.h"
#include "../include/RLoader.h"
#include "../include/RStyle.h"

using namespace std;


int main()
{
	// create root file in which the histograms will be saved
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/bkg_estimation/rootfile/analysis_Zprime_2500_1500.root","RECREATE");
	
	
	//Load data files
	//TChain	*chain = gRLoader->GetTTbarFiles();
	//std::cout << "Number of Entries in chain: " << chain->GetEntries() << std::endl;
	TFile f("/nfs/dust/cms/user/kziehl/processed_MC/ntuples_3_29/Signal_Zprime/Zprime_2500_1500_nominal_Tree.root")
	TTree *chain =(TTree*)f.Get("MVATree");

  
  //variables
  Float_t Weight_XS{0},TTM_Zprime_M{0},TTM_Mistagrate{0},TTM_separated_highest_bottoms_M{0},TTM_AK8_top_candidates_highest_M{0},TTM_highest_Ws_M{0},TTM_no_top_separated_highest_bottoms_M{0},TTM_no_top_Zprime_M{0},Signal_Topfirst_Zprime_M{0},TTM_Tprime_M{0},TTM_no_top_Tprime_M{0},Signal_Topfirst_Tprime_M{0};
  
  
  //Set branches
  chain->SetBranchStatus("*",0);
  /*
  chain->SetBranchStatus("Weight_XS",1);  
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  chain->SetBranchStatus("TTM_Mistagrate",1);  
  chain->SetBranchAddress("TTM_Mistagrate",&TTM_Mistagrate);
  
  chain->SetBranchStatus("TTM_Tprime_M",1);  
  chain->SetBranchAddress("TTM_Tprime_M",&TTM_Tprime_M);
  
  chain->SetBranchStatus("TTM_Zprime_M",1);  
  chain->SetBranchAddress("TTM_Zprime_M",&TTM_Zprime_M);
  
  chain->SetBranchStatus("TTM_separated_highest_bottoms_M",1);  
  chain->SetBranchAddress("TTM_separated_highest_bottoms_M",&TTM_separated_highest_bottoms_M);
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_highest_M",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_highest_M",&TTM_AK8_top_candidates_highest_M);
  
  chain->SetBranchStatus("TTM_highest_Ws_M",1);  
  chain->SetBranchAddress("TTM_highest_Ws_M",&TTM_highest_Ws_M);
  
  chain->SetBranchStatus("TTM_no_top_separated_highest_bottoms_M",1); 
  chain->SetBranchAddress("TTM_no_top_separated_highest_bottoms_M",&TTM_no_top_separated_highest_bottoms_M);
  
  chain->SetBranchStatus("TTM_no_top_Zprime_M",1);  
  chain->SetBranchAddress("TTM_no_top_Zprime_M",&TTM_no_top_Zprime_M);
  
  chain->SetBranchStatus("TTM_no_top_Tprime_M",1);  
  chain->SetBranchAddress("TTM_no_top_Tprime_M",&TTM_no_top_Tprime_M);
  */
  chain->SetBranchStatus("Signal_Topfirst_Zprime_M",1);
  chain->SetBranchAddress("Signal_Topfirst_Zprime_M",&Signal_Topfirst_Zprime_M);
  
  chain->SetBranchStatus("Signal_Topfirst_Tprime_M",1);
  chain->SetBranchAddress("Signal_Topfirst_Tprime_M",&Signal_Topfirst_Tprime_M);  
  
  //creating histograms
  TH1F* hZmass = new TH1F("hZmass","M(Z') Background",50,0,5000);
  TH1F* hZmassnotop = new TH1F("hZmassnotop","M(Z') Background no top",50,0,5000);
  TH1F* hmisstag = new TH1F("hmisstag","misstagrate",100,0,1);
  TH1F* hTmass = new TH1F("hTmass","m_{T'}",50,0,5000);
  TH1F* hTmassnotop = new TH1F("hTmassnotop","m_{T} no top",50,0,5000);
  TH1F* hZmassTopfirst = new TH1F("hZmassTopfirst","M(Z') Background Topfirst",50,0,5000);
  TH1F* hTmassTopfirst = new TH1F("hTmassTopfirst","m(t')",50,0,5000);
  //TH1F* hbotmass = new TH1F("hbotmass","Massdistriubtion of b-Quarks with the highest p_{T}",15,0,150);
	//TH1F* hAK8mass = new TH1F("hAK8mass","Massdistriubtion of AK8 Jets with the highest p_{T}",20,0,200);
	//TH1F* hWmass = new TH1F("hWmass","Massdistriubtion of W-Bosons with the highest p_{T}",15,0,150);
	//TH1F* hbotmassnotop = new TH1F("hbotmassnotop","Massdistriubtion of b-Quarks with the highest p_{T} without top tag",15,0,150);
  
  
  //store sum of squares of weights
  hZmass->Sumw2();
  hZmassTopfirst->Sumw2();
  hZmassnotop->Sumw2();
  hTmass->Sumw2();
  hTmassnotop->Sumw2();
  hTmassTopfirst->Sumw2();
  
 
 	// sum over entries and fill histogramms
  Long64_t Nentries = chain->GetEntries();
  
  for(Long64_t iEntry=0;iEntry<Nentries;iEntry++)
  {
		chain->GetEntry(iEntry);
		//if(TTM_Zprime_M>0) hZmass->Fill(TTM_Zprime_M,Weight_XS*TTM_Mistagrate);
		//if(TTM_no_top_Zprime_M>0) hZmassnotop->Fill(TTM_no_top_Zprime_M,Weight_XS*TTM_Mistagrate);
		if(Signal_Topfirst_Zprime_M>0) hZmassTopfirst->Fill(Signal_Topfirst_Zprime_M,Weight_XS);
		//if(TTM_Mistagrate>0)  hmisstag->Fill(TTM_Mistagrate);
		//if(TTM_Tprime_M>0) hTmass->Fill(TTM_Tprime_M,Weight_XS);
		//if(TTM_no_top_Tprime_M>0) hTmassnotop->Fill(TTM_no_top_Tprime_M,Weight_XS);
		//if(TTM_Mistagrate>0)  hmisstag->Fill(TTM_Mistagrate);
		//if(TTM_Tprime_M>0) hTmass->Fill(TTM_Tprime_M,Weight_XS*TTM_Mistagrate);
		//if(TTM_no_top_Tprime_M>0) hTmassnotop->Fill(TTM_no_top_Tprime_M,Weight_XS*TTM_Mistagrate);
		if(Signal_Topfirst_Tprime_M>0) hTmassTopfirst->Fill(Signal_Topfirst_Tprime_M,Weight_XS);
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
  //hZmass->Write("TTbar_TTM_Zprime_M");
  hZmassTopfirst->Write("Zprime_2500_1500_Signal_Topfirst_Zprime_M");
  //hZmassnotop->Write("TTbar_TTM_no_top_Zprime_M");
  //hTmass->Write("TTbar_TTM_Tprime_M");
  //hTmassnotop->Write("TTbar_TTM_no_top_Tprime_M");
  //hmisstag->Write("TTbar_misstag");
  hTmassTopfirst->Write("Zprime_2500_1500_Signal_Topfirst_Tprime_M");
  file->Close();
  
  

}

