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
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/bkg_estimation/rootfile/ak8candidate_top_comparison.root","RECREATE");
	
	
	//Load data files
	TChain	*chain = gRLoader->GetQCDFiles();
	std::cout << "Number of Entries in QCD sample: " << chain->GetEntries() << std::endl;


  
  //variables
  Float_t Weight_XS{0},TTM_Zprime_M{0},TTM_Mistagrate{0},TTM_AK8_top_candidates_highest_pt{0},Signal_Topfirst_Zprime_M{0};
  Int_t N_Signal_Topfirst_Tops{0},N_AK8_top_candidates{0};;
  vector <Float_t> Signal_Topfirst_Tops_Pt(1000),AK8_top_candidates_pt(1000);
  
  
  //Set branches
  chain->SetBranchStatus("*",0);
  
  chain->SetBranchStatus("Weight_XS",1);  
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  chain->SetBranchStatus("TTM_Mistagrate",1);  
  chain->SetBranchAddress("TTM_Mistagrate",&TTM_Mistagrate);
  
  chain->SetBranchStatus("TTM_Zprime_M",1);  
  chain->SetBranchAddress("TTM_Zprime_M",&TTM_Zprime_M);
  
  chain->SetBranchStatus("N_Signal_Topfirst_Tops",1);
  chain->SetBranchAddress("N_Signal_Topfirst_Tops",&N_Signal_Topfirst_Tops);
  
  chain->SetBranchStatus("N_AK8_top_candidates",1);
  chain->SetBranchAddress("N_AK8_top_candidates",&N_AK8_top_candidates);
  
  chain->SetBranchStatus("Signal_Topfirst_Tops_Pt",1);
  chain->SetBranchAddress("Signal_Topfirst_Tops_Pt",&(Signal_Topfirst_Tops_Pt.front()));
  
  chain->SetBranchStatus("AK8_top_candidates_pt",1);
  chain->SetBranchAddress("AK8_top_candidates_pt",&(AK8_top_candidates_pt.front()));
  
  
  //creating histograms
	TH1F* hAK8pt = new TH1F("hAK8pt","Pt of AK8 Jets with the highest p_{T}",100,0,5000);
	TH1F* htoppt = new TH1F("htoppt","pt of top jet",100,0,5000);
	TH1F* hAK8pthigh = new TH1F("hAK8pthigh","Pt of AK8 Jets with the highest p_{T}",100,0,5000);
	TH1F* htoppthigh = new TH1F("htoppthigh","pt of top jet",100,0,5000);


    
  //store sum of squares of weight
  hAK8pt->Sumw2();
  htoppt->Sumw2();
  hAK8pthigh->Sumw2();
  htoppthigh->Sumw2();
  
 
 	// sum over entries and fill histogramms
  Long64_t Nentries = chain->GetEntries();
  
  for(Long64_t iEntry=0;iEntry<Nentries;iEntry++)
  {
		chain->GetEntry(iEntry);
		
		if(TTM_Zprime_M>0) {
			for (Int_t iEvent=0;iEvent<N_AK8_top_candidates;iEvent++) {
				hAK8pt->Fill(AK8_top_candidates_pt.at(iEvent),Weight_XS);
			}
		}
		
		for (Int_t iEvent=0;iEvent<N_Signal_Topfirst_Tops;iEvent++) {
			if (Signal_Topfirst_Tops_Pt.at(iEvent)>0) htoppt->Fill(Signal_Topfirst_Tops_Pt.at(iEvent),Weight_XS);
			}
		
	// highest pt
	if(Signal_Topfirst_Tops_Pt.at(0)>0) htoppthigh->Fill(Signal_Topfirst_Tops_Pt.at(0),Weight_XS);
	if(TTM_AK8_top_candidates_highest_pt>0) hAK8pthigh->Fill(TTM_AK8_top_candidates_highest_pt,Weight_XS*TTM_Mistagrate);
    	
     if(iEntry%100000==0)
     {
      std::cout << "Processing Event Number   " << iEntry << std::endl;
     }
   }


	//Write and save
  file->cd();
	hAK8pt->Write("AK8pt");
  htoppt->Write("top_pt");
  hAK8pthigh->Write("AK8_highest_pt");
  htoppthigh->Write("top_highest_pt");
  
  file->Close();
  
  

}
