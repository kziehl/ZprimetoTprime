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
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/bkg_estimation/rootfile/number_of_entries_ak8sep_tops_16_3.root","RECREATE");
	
	
	//Load data files
	TChain	*chain = gRLoader->GetQCDFiles();
	std::cout << "Number of Entries in QCD samples: " << chain->GetEntries() << std::endl;


  //variables
  Int_t N_Signal_Topfirst_Tops{0},N_TTM_Zprime{0},N_TTM_AK8_top_candidates_separated{0};
  vector <Float_t> TTM_Zprime_M(100);
  
  
  //Set branches
  chain->SetBranchStatus("*",0);

  chain->SetBranchStatus("TTM_Zprime_M",1);  
  chain->SetBranchAddress("TTM_Zprime_M",&TTM_Zprime_M);
  
  chain->SetBranchStatus("N_TTM_Zprime",1);  
  chain->SetBranchAddress("N_TTM_Zprime",&N_TTM_Zprime);
  
  chain->SetBranchStatus("N_TTM_AK8_top_candidates_separated",1);  
  chain->SetBranchAddress("N_TTM_AK8_top_candidates_separated",&N_TTM_AK8_top_candidates_separated);
  
  chain->SetBranchStatus("N_Signal_Topfirst_Tops",1);
  chain->SetBranchAddress("N_Signal_Topfirst_Tops",&N_Signal_Topfirst_Tops);

  
  
  //creating histograms
  
  TH1F* hnumbertops = new TH1F("hnumbertops","Amount of tops",10,0,10);
  TH1F* hnumberak8 = new TH1F("hnumberak8","Amount of ak8",10,0,10);
  
 
 
 	// sum over entries and fill histogramms
  Long64_t Nentries = chain->GetEntries();
  
  for(Long64_t iEntry=0;iEntry<Nentries;iEntry++)
  {
		chain->GetEntry(iEntry);
		
		for (int i=0;i<N_TTM_Zprime;i++){
			if (i==0 && TTM_Zprime_M.at(i)>0) {
				hnumberak8->Fill(N_TTM_AK8_top_candidates_separated);
				hnumbertops->Fill(N_Signal_Topfirst_Tops);
			}
		}
		
    
    	
     if(iEntry%100000==0)
     {
      std::cout << "Processing Event Number   " << iEntry << std::endl;
     }
   }


	//Write and save
  file->cd();

  hnumbertops->Write("Amount_of_tops");
  hnumberak8->Write("Amount_of_ak8");

  file->Close();
  
  

}
