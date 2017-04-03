#include <iostream>
#include <vector>
#include <cmath>

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
	// create root file in which the rootfile will be saved
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/pt_eta/rootfile/QCD_false_negativ_bottom_W_tprime.root","RECREATE");
	
	//Load data files
	TChain	*chain = gRLoader->GetQCDFiles();
	std::cout << "Number of Entries in chain: " << chain->GetEntries() << std::endl;
	
	//set branches
	vector <Float_t> pt(1000),eta(1000),pt_AK8(1000),eta_AK8(1000);
	Int_t N_tagged_top(0),N_AK8_top_tag_candidates(0),N_Ws(0),N_Bottoms(0);
	Float_t Weight_XS(0),Signal_Topfirst_Tprime_M(0);
	
	
	// Set Branches
	chain->SetBranchStatus("*",0);
	
	chain->SetBranchStatus("misstagged_top_pt",1);
  chain->SetBranchAddress("misstagged_top_pt",&(pt.front()));
  
  chain->SetBranchStatus("misstagged_top_eta",1);
  chain->SetBranchAddress("misstagged_top_eta",&(eta.front()));
  
  chain->SetBranchStatus("AK8_top_misstagged_candidates_pt",1);
  chain->SetBranchAddress("AK8_top_misstagged_candidates_pt",&(pt_AK8.front())); 
  
  chain->SetBranchStatus("AK8_top_misstagged_candidates_eta",1);
  chain->SetBranchAddress("AK8_top_misstagged_candidates_eta",&(eta_AK8.front()));
  
  chain->SetBranchStatus("N_misstagged_top",1);
  chain->SetBranchAddress("N_misstagged_top",&N_tagged_top);
  
  chain->SetBranchStatus("N_AK8_top_misstag_candidates",1);
  chain->SetBranchAddress("N_AK8_top_misstag_candidates",&N_AK8_top_tag_candidates);
  
  chain->SetBranchStatus("N_Ws",1);
  chain->SetBranchAddress("N_Ws",&N_Ws);
  
  chain->SetBranchStatus("N_Bottoms",1);
  chain->SetBranchAddress("N_Bottoms",&N_Bottoms);
  
  chain->SetBranchStatus("Signal_Topfirst_Tprime_M",1);
  chain->SetBranchAddress("Signal_Topfirst_Tprime_M",&Signal_Topfirst_Tprime_M);
  
  chain->SetBranchStatus("Weight_XS",1);
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  
  //creating histograms
  TH2F *hpteta = new TH2F("hpteta","eta vs pt",50,-3,3,100,0,4000);
  TH2F *hAK8 = new TH2F("hAK8","eta vs pt",50,-3,3,100,0,4000);
  TH2F *divide = new TH2F("divide","",50,-3,3,100,0,4000);
  
  
  Long64_t nentries = chain->GetEntries();
  
  for(Long64_t i=0; i<nentries; i++)
  {
  	chain->GetEntry(i);
  	if (N_Ws>0 && N_Bottoms>0 && Signal_Topfirst_Tprime_M>500)
  	{
			for (int j=0;j<N_tagged_top;j++)
			{
				hpteta->Fill(eta[j],pt[j],Weight_XS);
			}
			for (int j=0;j<N_AK8_top_tag_candidates;j++)
			{
				hAK8->Fill(eta_AK8[j],pt_AK8[j],Weight_XS);
			}
		}
		
  	if (i%100000==0)
  	{
  		std::cout << i << std::endl;
  	}
  }
  
  	divide->Divide(hpteta,hAK8,1,1,"B");
  	

  	
  	//save to disk
  	file->cd();
  	divide->Write("BKG_QCD_false_negativ");
  	file->Close();
  	
  	
}
  
  
	
















