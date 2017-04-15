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
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/bkg_estimation/rootfile/analysis_QCD_16_3_mistagrate_high.root","RECREATE");
	
	
	Load data files
	TChain	*chain = gRLoader->GetQCDFiles();
	//std::cout << "Number of Entries in chain: " << chain->GetEntries() << std::endl;
	//TFile f("/nfs/dust/cms/user/kziehl/processed_MC/ntuples_3_29/Signal_Zprime/Zprime_2500_1500_nominal_Tree.root");
	//TTree *chain =(TTree*)f.Get("MVATree");

  
  //variables
  //weights
  Float_t Weight_XS{0},TTM_Mistagrate_high{0}
  vector<Float_t> TTM_Mistagrate(100);
  //vector mass
  vector<Float_t> TTM_Zprime_M(1000),TTM_Tprime_M(1000),TTM_separated_highest_per_ak8_bottoms_M(1000),
  TTM_RndmSDM(1000),TTM_AK8_top_candidates_separated_M(1000);
  Float_t TTM_highest_Ws_M{0},TTM_AK8_top_candidates_highest_M{0},Signal_Topfirst_Zprime_M{0},Signal_Topfirst_Tprime_M{0};
  //vector pt
  vector<Float_t> TTM_Zprime_pt(1000),TTM_Tprime_pt(1000),TTM_separated_highest_per_ak8_bottoms_pt(1000),TTM_AK8_top_candidates_separated_pt(1000),Signal_Topfirst_Tops_Pt(1000);
  Float_t TTM_highest_Ws_pt{0},TTM_AK8_top_candidates_highest_pt{0};
  //vector eta
  vector<Float_t> TTM_Zprime_eta(1000),TTM_Tprime_eta(1000),TTM_separated_highest_per_ak8_bottoms_eta(1000),TTM_AK8_top_candidates_separated_eta(1000);
  Float_t TTM_highest_Ws_eta{0},TTM_AK8_top_candidates_highest_eta{0};
  //length
  Int_t N_TTM_Mistagrate{0},N_TTM_Zprime{0},N_TTM_Tprime{0},N_TTM_separated_highest_per_ak8_bottoms{0},N_TTM_RndmSDM{0},N_TTM_AK8_top_candidates_separated{0},N_Signal_Topfirst_Tops{0};

  
  //Set branches
  chain->SetBranchStatus("*",0);
  //weights
  chain->SetBranchStatus("Weight_XS",1);  
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  chain->SetBranchStatus("TTM_Mistagrate_high",1);  
  chain->SetBranchAddress("TTM_Mistagrate_high",&TTM_Mistagrate_high);
  
  chain->SetBranchAddress("TTM_Mistagrate",1);
  chain->SetBranchStatus("TTM_Mistagrate",&(TTM_Mistagrate.front()));
  
  //vector mass
  chain->SetBranchStatus("TTM_Zprime_M",1);  
  chain->SetBranchAddress("TTM_Zprime_M",&(TTM_Zprime_M.front()));
  
  chain->SetBranchStatus("TTM_Tprime_M",1);  
  chain->SetBranchAddress("TTM_Tprime_M",&(TTM_Tprime_M.front()));
  
  chain->SetBranchStatus("TTM_separated_highest_per_ak8_bottoms_M",1);  
  chain->SetBranchAddress("TTM_separated_highest_per_ak8_bottoms_M",&(TTM_separated_highest_per_ak8_bottoms_M.front()));
  
  chain->SetBranchStatus("TTM_RndmSDM",1);  
  chain->SetBranchAddress("TTM_RndmSDM",&(TTM_RndmSDM.front()));
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_separated_M",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_separated_M",&(TTM_AK8_top_candidates_separated_M.front()));
  
	chain->SetBranchStatus("TTM_highest_Ws_M",1);  
  chain->SetBranchAddress("TTM_highest_Ws_M",&TTM_highest_Ws_M); 
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_highest_M",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_highest_M",&TTM_AK8_top_candidates_highest_M);
  
  chain->SetBranchStatus("Signal_Topfirst_Zprime_M",1);  
  chain->SetBranchAddress("Signal_Topfirst_Zprime_M",&Signal_Topfirst_Zprime_M);
  
  chain->SetBranchStatus("Signal_Topfirst_Tprime_M",1);  
  chain->SetBranchAddress("Signal_Topfirst_Tprime_M",&Signal_Topfirst_Tprime_M); 
  
  //vector pt
  chain->SetBranchStatus("TTM_Zprime_pt",1);  
  chain->SetBranchAddress("TTM_Zprime_pt",&(TTM_Zprime_pt.front()));
  
  chain->SetBranchStatus("TTM_Tprime_pt",1);  
  chain->SetBranchAddress("TTM_Tprime_pt",&(TTM_Tprime_pt.front()));
  
  chain->SetBranchStatus("TTM_separated_highest_per_ak8_bottoms_pt",1);  
  chain->SetBranchAddress("TTM_separated_highest_per_ak8_bottoms_pt",&(TTM_separated_highest_per_ak8_bottoms_pt.front()));
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_separated_pt",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_separated_pt",&(TTM_AK8_top_candidates_separated_pt.front()));
  
	chain->SetBranchStatus("Signal_Topfirst_Tops_Pt",1);  
  chain->SetBranchAddress("Signal_Topfirst_Tops_Pt",&(Signal_Topfirst_Tops_Pt.front())); 
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_highest_pt",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_highest_pt",&TTM_AK8_top_candidates_highest_pt);
  
  chain->SetBranchStatus("TTM_highest_Ws_pt",1);  
  chain->SetBranchAddress("TTM_highest_Ws_pt",&TTM_highest_Ws_pt);
  
  //vector eta
  chain->SetBranchStatus("TTM_Zprime_eta",1);  
  chain->SetBranchAddress("TTM_Zprime_eta",&(TTM_Zprime_eta.front()));
  
  chain->SetBranchStatus("TTM_Tprime_eta",1);  
  chain->SetBranchAddress("TTM_Tprime_eta",&(TTM_Tprime_eta.front()));
  
  chain->SetBranchStatus("TTM_separated_highest_per_ak8_bottoms_eta",1);  
  chain->SetBranchAddress("TTM_separated_highest_per_ak8_bottoms_eta",&(TTM_separated_highest_per_ak8_bottoms_eta.front()));
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_separated_eta",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_separated_eta",&(TTM_AK8_top_candidates_separated_eta.front()));
  
	chain->SetBranchStatus("TTM_highest_Ws_eta",1);  
  chain->SetBranchAddress("TTM_highest_Ws_eta",&TTM_highest_Ws_eta); 
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_highest_eta",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_highest_eta",&TTM_AK8_top_candidates_highest_eta);
  //length
  chain->SetBranchStatus("N_TTM_Mistagrate",1);  
  chain->SetBranchAddress("N_TTM_Mistagrate",&N_TTM_Mistagrate); 
  
  chain->SetBranchStatus("N_TTM_Zprime",1);  
  chain->SetBranchAddress("N_TTM_Zprime",&N_TTM_Zprime); 
  	
  chain->SetBranchStatus("N_TTM_Tprime",1);  
  chain->SetBranchAddress("N_TTM_Tprime",&N_TTM_Tprime); 

  chain->SetBranchStatus("N_TTM_separated_highest_per_ak8_bottoms",1);  
  chain->SetBranchAddress("N_TTM_separated_highest_per_ak8_bottoms",&N_TTM_separated_highest_per_ak8_bottoms);
  
  chain->SetBranchStatus("N_TTM_RndmSDM",1);  
  chain->SetBranchAddress("N_TTM_RndmSDM",&N_TTM_RndmSDM);
  
  chain->SetBranchStatus("N_TTM_AK8_top_candidates_separated",1);  
  chain->SetBranchAddress("N_TTM_AK8_top_candidates_separated",&N_TTM_AK8_top_candidates_separated);
  
  chain->SetBranchStatus("N_Signal_Topfirst_Tops",1);  
  chain->SetBranchAddress("N_Signal_Topfirst_Tops",&N_Signal_Topfirst_Tops); 
  
  
  //creating histograms
  
  //weights
  TH1F* hweightxs = new TH1F("weightxs","",100,0,1);
  TH1F* hmis = new TH1F("hmisstag","misstagrate",100,0,1);
  TH1F* hmishigh = new TH1F("hmistag","misstagrate",100,0,1);
  TH1F* hsoftdrop = new TH1F("soft","",50,100,220);
  //mass
  TH1F* hZmass = new TH1F("hZmass","M(Z') Background",50,0,5000);
  TH1F* hTmass = new TH1F("hTmass","m_{T'}",50,0,5000);
  TH1F* hZmassTopfirst = new TH1F("hZmassTopfirst","M(Z') Background Topfirst",50,0,5000);
  TH1F* hTmassTopfirst = new TH1F("hTmassTopfirst","m(t')",50,0,5000);
  TH1F* hbotmass = new TH1F("hbotmass","",15,0,150);
  TH1F* hak8sep = new TH1F("ak8sep","",50,0,5000);
  TH1F* hWmass = new TH1F("hWmass","Massdistriubtion of W-Bosons with the highest p_{T}",15,0,150);
  TH1F* hak8high = new TH1F("ak8highm","",50,0,5000);
	//pt
	TH1F* hZpt = new TH1F("hZpt","",50,0,5000);
  TH1F* hTpt = new TH1F("hTpt","",50,0,5000);
  TH1F* hbotpt = new TH1F("hbotpt","",15,0,150);
  TH1F* hak8seppt = new TH1F("ak8seppt","",50,0,5000);
  TH1F* hWpt = new TH1F("hWpt","Massdistriubtion of W-Bosons with the highest p_{T}",15,0,150);
  TH1F* hak8highpt = new TH1F("ak8highpt","",50,0,5000);
  TH1F* htopspt = new TH1F("topsps","",50,0,5000);
	//eta
	TH1F* hZeta = new TH1F("hZea","",50,0,5000);
  TH1F* hTeta = new TH1F("hTeta","",50,0,5000);
  TH1F* hboteta = new TH1F("hboteta","",15,0,150);
  TH1F* hak8sepeta = new TH1F("ak8sepeta","",50,0,5000);
  TH1F* hWeta = new TH1F("hWeta","Massdistriubtion of W-Bosons with the highest p_{T}",15,0,150);
  TH1F* hak8higheta = new TH1F("ak8higheta","",50,0,5000);
  //length
  TH1F* hNmis = new TH1F("mislength","",10,0,10);
  TH1F* hNzprime = new TH1F("zprimelne","",10,0,10);
  TH1F* hNtprime = new TH1F("tprimeken","",10,0,10);
  TH1F* hNbot = new TH1F("botlen","",10,0,10);
  TH1F* hNsoft = new TH1F("softdrop","",10,0,10);
  TH1F* hak8sep = new TH1F("ak8sepeee","",10,0,10);
  TH1F* htops = new TH1F("amounttops","",10,0,10);
  
  
  //store sum of squares of weight
  hZmass->Sumw2();
  hTmass->Sumw2();
  
  
  // weighting factor for signal
  Double_t Weight = 1000./227926.;
  std::cout << Weight << std::endl;
 
 	// sum over entries and fill histogramms
  Long64_t Nentries = chain->GetEntries();
  
  for(Long64_t iEntry=0;iEntry<Nentries;iEntry++)
  {
		chain->GetEntry(iEntry);
		//weights
		if(Weight_XS>0) hweightxs->Fill(Weight_XS);
		for (int i=0;i<N_TTM_Mistagrate;i++) {
			if(TTM_Mistagrate>0) hmis->Fill(TTM_Mistagrate);
		}
		if(TTM_Mistagrate_high>0) hmishigh->Fill(TTM_Mistagrate_high);
		for (int i=0;i<N_TTM_RndmSDM;i++) {
			if(TTM_RndmSDM>0) hsoftdrop->Fill(TTM_RndmSDM);
		}
		//mass
		for (int i=0;i<N_TTM_Zprime;i++) {
			if(TTM_Zprime_M>0) hZmass->Fill(TTM_Zprime_M,Weight_XS*TTM_Mistagrate_high);
		}
		if(Signal_Topfirst_Zprime_M>0) hZmassTopfirst->Fill(Signal_Topfirst_Zprime_M,Weight_XS);
		for (int i=0;i<N_TTM_Tprime;i++) {
			if(TTM_Tprime_M>0) hTmass->Fill(TTM_Tprime_M,Weight_XS*TTM_Mistagrate_high);
		}
		if(Signal_Topfirst_Tprime_M>0) hTmassTopfirst->Fill(Signal_Topfirst_Tprime_M,Weight_XS);
		for (int i=0;i<N_TTM_separated_highest_per_ak8_bottoms;i++) {
			if(TTM_separated_highest_per_ak8_bottoms_M>0) hbotmass->Fill(TTM_separated_highest_per_ak8_bottoms_M,Weight_XS);
		}
		if(TTM_highest_Ws_M>0) hWmass->Fill(TTM_highest_Ws_M,Weight_XS);
		for (int i=0;i<N_TTM_AK8_top_candidates_separated;i++) {
			if(TTM_AK8_top_candidates_separated_M>0) hak8sep->Fill(TTM_AK8_top_candidates_separated_M,Weight_XS*TTM_Mistagrate_high);
		}
    if(TTM_AK8_top_candidates_highest_M>0) hak8high->Fill(TTM_AK8_top_candidates_highest_M,Weight_XS*TTM_Mistagrate_high);
    
    
    //pt
		for (int i=0;i<N_TTM_Zprime;i++) {
			if(TTM_Zprime_pt>0) hZpt->Fill(TTM_Zprime_pt,Weight_XS*TTM_Mistagrate_high);
		}
		for (int i=0;i<N_TTM_Tprime;i++) {
			if(TTM_Tprime_pt>0) hTpt->Fill(TTM_Tprime_pt,Weight_XS*TTM_Mistagrate_high);
		}
		for (int i=0;i<N_TTM_separated_highest_per_ak8_bottoms;i++) {
			if(TTM_separated_highest_per_ak8_bottoms_pt>0) hbotpt->Fill(TTM_separated_highest_per_ak8_bottoms_pt,Weight_XS);
		}
		if(TTM_highest_Ws_pt>0) hWpt->Fill(TTM_highest_Ws_pt,Weight_XS);
		for (int i=0;i<N_TTM_AK8_top_candidates_separated;i++) {
			if(TTM_AK8_top_candidates_separated_pt>0) hak8seppt->Fill(TTM_AK8_top_candidates_separated_pt,Weight_XS*TTM_Mistagrate_high);
		}
    if(TTM_AK8_top_candidates_highest_pt>0) hak8highpt->Fill(TTM_AK8_top_candidates_highest_pt,Weight_XS*TTM_Mistagrate_high);
    for (int i=0;i<N_Signal_Topfirst_Tops;i++){
    	if (Signal_Topfirst_Tops_Pt>0) htoppt->Fill(Signal_Topfirst_Tops_Pt,Weight_XS);
    }
    
    
    //eta
		for (int i=0;i<N_TTM_Zprime;i++) {
			if(TTM_Zprime_eta>0) hZeta->Fill(TTM_Zprime_eta,Weight_XS*TTM_Mistagrate_high);
		}
		for (int i=0;i<N_TTM_Tprime;i++) {
			if(TTM_Tprime_eta>0) hTeta->Fill(TTM_Tprime_eta,Weight_XS*TTM_Mistagrate_high);
		}
		for (int i=0;i<N_TTM_separated_highest_per_ak8_bottoms;i++) {
			if(TTM_separated_highest_per_ak8_bottoms_eta>0) hboteta->Fill(TTM_separated_highest_per_ak8_bottoms_eta,Weight_XS);
		}
		if(TTM_highest_Ws_eta>0) hWeta->Fill(TTM_highest_Ws_eta,Weight_XS);
		for (int i=0;i<N_TTM_AK8_top_candidates_separated;i++) {
			if(TTM_AK8_top_candidates_separated_eta>0) hak8sepeta->Fill(TTM_AK8_top_candidates_separated_eta,Weight_XS*TTM_Mistagrate_high);
		}
    if(TTM_AK8_top_candidates_highest_eta>0) hak8higheta->Fill(TTM_AK8_top_candidates_highest_eta,Weight_XS*TTM_Mistagrate_high);
    
    //length
    
    if (N_TTM_Mistagrate>0) hNmis->Fill(N_TTM_Mistagrate);
    if (N_TTM_Zprime>0) hNzprime->Fill(N_TTM_Zprime);
    if (N_TTM_Tprime>0) hNtprime->Fill(N_TTM_Tprime);
    if (N_TTM_separated_highest_per_ak8_bottoms>0) hNbot->Fill(N_TTM_separated_highest_per_ak8_bottoms);
    if (N_TTM_AK8_top_candidates_separated>0) hak8sep->Fill(N_TTM_AK8_top_candidates_separated);
    if (N_Signal_Topfirst_Tops>0) htops->Fill(N_Signal_Topfirst_Tops);
    if (N_TTM_RndmSDM>0) hNsoft->Fill(N_TTM_RndmSDM);
    	
     if(iEntry%100000==0)
     {
      std::cout << "Processing Event Number   " << iEntry << std::endl;
     }
   }


	//Write and save
  file->cd();

  //weights
  hweightxs->Write("QCD_weightxs");
  hmis->Write("QCD_mistagrate");
  hmishigh->Write("QCD_mistagrate_high");
  hsoftdrop->Write("QCD_softdropmass");
  //mass
  hZmass->Write("QCD_TTM_Zprime_mistag_high_M");
  hTmass->Write("QCD_TTM_Tprime_mistag_high_M");
  hZmassTopfirst->Write("QCD_Signal_topfirst_zprime_M");
  hTmassTopfirst->Write("QCD_Signal_topfirst_tprime_M");
  hbotmass->Write("QCD_TTM_bottom_M");
  hak8sep->Write("QCD_TTM_AK8_sep_M");
  hWmass->Write("QCD_TTM_Ws_M");
  hak8high->Wrte("QCD_TTM_Ak8_high_M");
	//pt
	hZpt->Write("QCD_TTM_zprime_pt");
  hTpt->Write("QCD_TTM_tprime_pt");
  hbotpt->Write("QCD_TTM_bottom_pt");
  hak8seppt->Write("QCD_TTM_AK8_sep_pt");
  hWpt->Write("QCD_TTM_Ws_pt");
  hak8highpt->Write("QCD_TTM_Ak8_high_pt");
  htopspt->Write("QCD_Signal_topfirst_top_pt");
	//eta
	hZeta->Write("QCD_TTM_zprime_eta");
  hTeta->Write("QCD_TTM_tprime_eta");
  hboteta->Write("QCD_TTM_bottom_eta");
  hak8sepeta->Write("QCD_TTM_AK8_sep_eta");
  hWeta->Write("QCD_TTM_Ws_eta");
  hak8higheta->Write("QCD_TTM_Ak8_high_eta");
  //length
  hNmis->Write("QCD_N_mistag");
  hNzprime->Write("QCD_N_ttm_zprime");
  TH1hNtprime->Write("QCD_N_ttm_tprime");
  hNbot->Write("QCD_N_ttm_bottom");
  hNsoft->Write("QCD_N_softdrop");
  hak8sep->Write("QCD_N_ak8_sep");
  htops->Write("QCD_N_signal_top");
  
  file->Close();
  
  

}

