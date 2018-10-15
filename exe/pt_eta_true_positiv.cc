#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>

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

#include "plotutil.h"

using namespace std;




int main()
{
	//create root file in which we will save histogram
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/Zprime/pt_eta/rootfile/BKG_TTbar_true_positiv.root","RECREATE");
	
	//TChain *BKG_TTBar = BKG_TTbar_Loader();
	//std::cout << BKG_TTBar->GetEntries() << std::endl;
	TChain *chain = BKG_TTbar_Loader();
	std::cout << chain->GetEntries() << std::endl;
	//chain->Add(BKG_TTBar);
	//std::cout << chain->GetEntries() << std::endl;
	 
	//Signal_Zprime->LoadTree(0);
	//TFile *f = Signal_Zprime->GetFile();
	//TTree *tree = (TTree*)f->Get("MVATree");
	
	vector <Float_t> pt(1000),eta(1000),pt_AK8(1000),eta_AK8(1000);
	Int_t N_tagged_top(0),N_AK8_top_tag_candidates(0);
	Float_t Weight_XS(0);
	
	// Set height of histogram
	Double_t height_pt=GetMaxVal(chain,"tagged_top_pt","N_tagged_top");
	Int_t Nbin=height_pt/40;
	std::cout << "Height of y-range: " << height_pt << std::endl;
	std::cout << "Numbers of Bins in y-axis: " << Nbin << std::endl;
	
	// Set Branches for interesting variables
	chain->SetBranchStatus("*",0);
	chain->SetBranchStatus("tagged_top_pt",1);
  chain->SetBranchAddress("tagged_top_pt",&(pt.front()));
  chain->SetBranchStatus("tagged_top_eta",1);
  chain->SetBranchAddress("tagged_top_eta",&(eta.front()));
  chain->SetBranchStatus("AK8_top_tag_candidates_pt",1);
  chain->SetBranchAddress("AK8_top_tag_candidates_pt",&(pt_AK8.front()));
  chain->SetBranchStatus("AK8_top_tag_candidates_eta",1);
  chain->SetBranchAddress("AK8_top_tag_candidates_eta",&(eta_AK8.front()));
  chain->SetBranchStatus("N_tagged_top",1);
  chain->SetBranchAddress("N_tagged_top",&N_tagged_top);
  chain->SetBranchStatus("N_AK8_top_tag_candidates",1);
  chain->SetBranchAddress("N_AK8_top_tag_candidates",&N_AK8_top_tag_candidates);
  chain->SetBranchStatus("Weight_XS",1);
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  
  TH2F *hpteta = new TH2F("hpteta","eta vs pt",50,-3,3,Nbin,0,1.1*height_pt);  
  TH2F *hAK8 = new TH2F("hAK8","eta vs pt",50,-3,3,Nbin,0,1.1*height_pt);
  TH2F *divide = new TH2F("divide","",50,-3,3,Nbin,0,1.1*height_pt);
  
  
  Long64_t nentries = chain->GetEntries();
  
  for(Long64_t i=0; i<nentries; i++)
  {
  	chain->GetEntry(i);
  	for (int j=0;j<N_tagged_top;j++)
  	{
  		hpteta->Fill(eta[j],pt[j],Weight_XS);
  	}
  	for (int j=0;j<N_AK8_top_tag_candidates;j++)
  	{
  		hAK8->Fill(eta_AK8[j],pt_AK8[j],Weight_XS);
  	}
  	if (i%10000==0)
  	{
  		std::cout << i << std::endl;
  	}
  }
  	divide->Divide(hpteta,hAK8,1,1,"B");
  	
  	//set style
  	TCanvas * cs = new TCanvas("cs","cs",10,10,1100,800);
  	divide->SetTitleOffset(1.1,"x");
		divide->SetTitleSize(0.04,"x");
		divide->SetLabelSize(0.04,"x");
		divide->SetTitleOffset(1.3,"y");
		divide->SetTitleSize(0.04,"y");
		divide->SetLabelSize(0.04,"y");
  	divide->GetXaxis()->SetTitle("#eta");
  	divide->GetYaxis()->SetTitle("p_{T}");
  	divide->SetStats(kFALSE);
  	divide->Draw("colz");
  	
  	//save to disk
  	cs->SaveAs("/nfs/dust/cms/user/kziehl/plots/Zprime/pt_eta/pdf/BKG_TTbar_true_positiv.pdf");
  	file->cd();
  	divide->Write("BKG_TTbar_true_positiv");
  	file->Close();
  	
  	
}
  
  
	
















