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
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/bkg_estimation/rootfile/ak8candidate_separated_top_comparison_mistag_all.root","RECREATE");
	
	
	//Load data files
	TChain	*chain = gRLoader->GetQCDFiles();
	std::cout << "Number of Entries in QCD sample: " << chain->GetEntries() << std::endl;


  
  //variables
  Float_t Weight_XS{0},TTM_Mistagrate_high{0};
  Int_t N_Signal_Topfirst_Tops{0},N_TTM_Mistagrate{0},N_TTM_Zprime{0},N_TTM_AK8_top_candidates_separated{0};
  vector <Float_t> Signal_Topfirst_Tops_Pt(1000),TTM_Zprime_M(100),TTM_Mistagrate(100),TTM_AK8_top_candidates_separated_pt(100);
  
  
  //Set branches
  chain->SetBranchStatus("*",0);
  
  chain->SetBranchStatus("Weight_XS",1);  
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  chain->SetBranchStatus("TTM_Mistagrate_high",1);  
  chain->SetBranchAddress("TTM_Mistagrate_high",&TTM_Mistagrate_high);
  
  chain->SetBranchStatus("TTM_Mistagrate",1);  
  chain->SetBranchAddress("TTM_Mistagrate",&(TTM_Mistagrate.front()));
  
  chain->SetBranchStatus("TTM_Zprime_M",1);  
  chain->SetBranchAddress("TTM_Zprime_M",&TTM_Zprime_M);
  
  chain->SetBranchStatus("N_TTM_Zprime",1);  
  chain->SetBranchAddress("N_TTM_Zprime",&N_TTM_Zprime);
  
  chain->SetBranchStatus("N_TTM_AK8_top_candidates_separated",1);  
  chain->SetBranchAddress("N_TTM_AK8_top_candidates_separated",&N_TTM_AK8_top_candidates_separated);
  
  chain->SetBranchStatus("TTM_AK8_top_candidates_separated_pt",1);  
  chain->SetBranchAddress("TTM_AK8_top_candidates_separated_pt",&(TTM_AK8_top_candidates_separated_pt.front()));
  
  chain->SetBranchStatus("N_Signal_Topfirst_Tops",1);
  chain->SetBranchAddress("N_Signal_Topfirst_Tops",&N_Signal_Topfirst_Tops);
  
  chain->SetBranchStatus("N_TTM_Mistagrate",1);
  chain->SetBranchAddress("N_TTM_Mistagrate",&N_TTM_Mistagrate);
  
  chain->SetBranchStatus("Signal_Topfirst_Tops_Pt",1);
  chain->SetBranchAddress("Signal_Topfirst_Tops_Pt",&(Signal_Topfirst_Tops_Pt.front()));


  
  
  //creating histograms
	TH1F* hAK8pt = new TH1F("hAK8pt","Pt of AK8 Jets with the highest p_{T}",100,0,5000);
	TH1F* htoppt = new TH1F("htoppt","pt of top jet",100,0,5000);



    
  //store sum of squares of weight
  hAK8pt->Sumw2();
  htoppt->Sumw2();

  
 
 	// sum over entries and fill histogramms
  Long64_t Nentries = chain->GetEntries();
  
  for(Long64_t iEntry=0;iEntry<Nentries;iEntry++)
  {
		chain->GetEntry(iEntry);
		
		for (int iEv=0;iEv<N_TTM_Zprime;iEv++) {
			if (iEv==0 && TTM_Zprime_M.at(iEv)>0) hAK8pt->Fill(TTM_AK8_top_candidates_separated_pt.at(iEv),Weight_XS*TTM_Mistagrate.at(iEv));
		}
		
		for (Int_t iEvent=0;iEvent<N_Signal_Topfirst_Tops;iEvent++) {
			if (iEvent==0 && Signal_Topfirst_Tops_Pt.at(iEvent)>0) htoppt->Fill(Signal_Topfirst_Tops_Pt.at(iEvent),Weight_XS);
			}

    	
     if(iEntry%100000==0)
     {
      std::cout << "Processing Event Number   " << iEntry << std::endl;
     }
   }


	//Write and save
  file->cd();
	hAK8pt->Write("AK8pt");
  htoppt->Write("top_pt");

  
  file->Close();
  
  

}
