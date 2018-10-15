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
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/Zprime/pt_eta/rootfile/BKG_Sum_tagrate_notop.root","RECREATE");
	
	TChain *BKG_TTBar = BKG_QCD_Loader();
	std::cout << BKG_TTBar->GetEntries() << std::endl;
	TChain *chain = BKG_TTbar_Loader();
	std::cout << chain->GetEntries() << std::endl;
	chain->Add(BKG_TTBar);
	std::cout << chain->GetEntries() << std::endl;
	 
	//Signal_Zprime->LoadTree(0);
	//TFile *f = Signal_Zprime->GetFile();
	//TTree *tree = (TTree*)f->Get("MVATree");
	
	//set branches
	vector <Float_t> pt(1000),eta(1000),pt_AK8(1000),eta_AK8(1000);
	Int_t N_tagged_top(0),N_AK8_top_tag_candidates(0);
	Float_t Weight_XS(0);
	
	// Set height of histogram
	Double_t height_pt=GetMaxVal(chain,"tagged_top_anti_pt","N_tagged_top_anti");
	Int_t Nbin=height_pt/100;
	std::cout << "Height of y-range: " << height_pt << std::endl;
	std::cout << "Numbers of Bins in y-axis: " << Nbin << std::endl;
	
	// Set Branches for interesting variables
	chain->SetBranchStatus("*",0);
	chain->SetBranchStatus("tagged_top_anti_pt",1);
  chain->SetBranchAddress("tagged_top_anti_pt",&(pt.front()));
  chain->SetBranchStatus("tagged_top_anti_eta",1);
  chain->SetBranchAddress("tagged_top_anti_eta",&(eta.front()));
  chain->SetBranchStatus("AK8_top_misstagged_candidates_pt",1);
  chain->SetBranchAddress("AK8_top_misstagged_candidates_pt",&(pt_AK8.front()));
  chain->SetBranchStatus("AK8_top_misstagged_candidates_eta",1); 
  chain->SetBranchAddress("AK8_top_misstagged_candidates_eta",&(eta_AK8.front()));
  chain->SetBranchStatus("N_tagged_top_anti",1);
  chain->SetBranchAddress("N_tagged_top_anti",&N_tagged_top);
  chain->SetBranchStatus("N_AK8_top_misstag_candidates",1);
  chain->SetBranchAddress("N_AK8_top_misstag_candidates",&N_AK8_top_tag_candidates);
  chain->SetBranchStatus("Weight_XS",1);
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
  TH1F *hpt = new TH1F("hpt","",Nbin,0,1.1*height_pt);
  TH1F *heta = new TH1F("heta","",50,-3,3);
  TH1F *AK8pt = new TH1F("AK8pt","",Nbin,0,1.1*height_pt);
  TH1F *AK8eta = new TH1F("AK8eta","",50,-3,3);
  TH1F *tageff_pt = new TH1F("tageff_pt","",Nbin,0,1.1*height_pt);
  TH1F *tageff_eta = new TH1F("tageff_eta","",50,-3,3);
  
  
  Long64_t nentries = chain->GetEntries();
  
  for(Long64_t i=0; i<nentries; i++)
  {
  	chain->GetEntry(i);
  	for (int j=0;j<N_tagged_top;j++)
  	{
  		heta->Fill(eta[j],Weight_XS);
  		hpt->Fill(pt[j],Weight_XS);
  	}
  	for (int j=0;j<N_AK8_top_tag_candidates;j++)
  	{
  		AK8pt->Fill(pt_AK8[j],Weight_XS);
  		AK8eta->Fill(eta_AK8[j],Weight_XS);
  	}
  	if (i%10000==0)
  	{
  		std::cout << i << std::endl;
  	}
  }
  	
  	tageff_pt->Divide(hpt,AK8pt,1,1,"B");
  	tageff_eta->Divide(heta,AK8eta,1,1,"B");
  	
  	//set style for pt and eta
  	TCanvas * cpt = new TCanvas("cpt","cpt",10,10,1100,800);
  	tageff_pt->SetTitleOffset(1.1,"x");
		tageff_pt->SetTitleSize(0.04,"x");
		tageff_pt->SetLabelSize(0.04,"x");
		tageff_pt->SetTitleOffset(1.3,"y");
		tageff_pt->SetTitleSize(0.04,"y");
		tageff_pt->SetLabelSize(0.04,"y");
  	tageff_pt->GetXaxis()->SetTitle("p_{T}");
  	tageff_pt->GetYaxis()->SetTitle("t-tagrate");
  	tageff_pt->SetStats(kFALSE);
  	tageff_pt->Draw("e");
  	
  	TCanvas * ceta = new TCanvas("ceta","ceta",10,10,1100,800);
  	tageff_eta->SetTitleOffset(1.1,"x");
		tageff_eta->SetTitleSize(0.04,"x");
		tageff_eta->SetLabelSize(0.04,"x");
		tageff_eta->SetTitleOffset(1.3,"y");
		tageff_eta->SetTitleSize(0.04,"y");
		tageff_eta->SetLabelSize(0.04,"y");
  	tageff_eta->GetXaxis()->SetTitle("#eta");
  	tageff_eta->GetYaxis()->SetTitle("t-tagrate");
  	tageff_eta->SetStats(kFALSE);
  	tageff_eta->Draw("e");
  	
  	//save to disk
  	cpt->SaveAs("/nfs/dust/cms/user/kziehl/plots/Zprime/pt_eta/pdf/BKG_Sum_tagrate_notop_pt.pdf");
  	ceta->SaveAs("/nfs/dust/cms/user/kziehl/plots/Zprime/pt_eta/pdf/BKG_Sum_tagrate_notop_eta.pdf");
  	file->cd();
  	tageff_pt->Write("BKG_Sum_tagrate_notop_pt");
  	tageff_eta->Write("BKG_Sum_tagrate_notop_eta");
  	
  	file->Close();
  	
  	
}
