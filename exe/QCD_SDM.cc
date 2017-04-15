#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>


#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TObjArray.h"
#include "TChain.h"

#include "plotutil.h"

using namespace std;




int main()
{
	//create root file in which we will save histogram
	TFile *file = new TFile("/nfs/dust/cms/user/kziehl/plots/Zprime/BKG_QCD_SDM_Tops_MSD.root","RECREATE");
	
	TChain *chain = BKG_QCD_Loader();
	std::cout << "Numbers of entries: " << chain->GetEntries() << std::endl;
	
	 
	//Signal_Zprime->LoadTree(0);
	//TFile *f = Signal_Zprime->GetFile();
	//TTree *tree = (TTree*)f->Get("MVATree");
	
	vector <Float_t> softDropMassAK8CHS(1000),packedPatJetsAK8PFCHSSoftDrop_Pt(1000),Signal_Topfirst_Tops_MSD(1000);
	Int_t N_packedPatJetsAK8PFCHSSoftDrop(0),N_Signal_Topfirst_Tops(0);
	Float_t Weight_XS(0);
	
	// Set Branches for interesting variables
	chain->SetBranchStatus("*",0);
	

	chain->SetBranchStatus("N_Signal_Topfirst_Tops",1);
	chain->SetBranchAddress("N_Signal_Topfirst_Tops",&N_Signal_Topfirst_Tops);
	chain->SetBranchStatus("Signal_Topfirst_Tops_MSD",1);
	chain->SetBranchAddress("Signal_Topfirst_Tops_MSD",&(Signal_Topfirst_Tops_MSD.front()));
	
	chain->SetBranchStatus("softDropMassAK8CHS",1);
  chain->SetBranchAddress("softDropMassAK8CHS",&(softDropMassAK8CHS.front()));
  chain->SetBranchStatus("N_packedPatJetsAK8PFCHSSoftDrop",1);
  chain->SetBranchAddress("N_packedPatJetsAK8PFCHSSoftDrop",&N_packedPatJetsAK8PFCHSSoftDrop);
  chain->SetBranchStatus("packedPatJetsAK8PFCHSSoftDrop_Pt",1);
  chain->SetBranchAddress("packedPatJetsAK8PFCHSSoftDrop_Pt",&(packedPatJetsAK8PFCHSSoftDrop_Pt.front()));
  chain->SetBranchStatus("Weight_XS",1);
  chain->SetBranchAddress("Weight_XS",&Weight_XS);
  
	// create histogram
  TH1F *hsoftDropMass = new TH1F("hsoftDropMass","",120,100,220);
  TH1F *htopsMSD = new TH1F("htopsMSD","",120,100,220);
  
  //loop over all entries
  Long64_t nentries = chain->GetEntries();
  
  for(Long64_t i=0; i<nentries; i++)
  {
  	chain->GetEntry(i);
  	for (int i=0; i<N_packedPatJetsAK8PFCHSSoftDrop; i++)
  	{	//loose working point
  		if (110 <= softDropMassAK8CHS.at(i) && softDropMassAK8CHS.at(i) <= 210 && packedPatJetsAK8PFCHSSoftDrop_Pt.at(i)>400)
  		{
  			hsoftDropMass->Fill(softDropMassAK8CHS.at(i),Weight_XS);
  		}
  	}
  	for (int i=0; i<N_Signal_Topfirst_Tops;i++)
  	{
  		if (110 <= Signal_Topfirst_Tops_MSD.at(i) && Signal_Topfirst_Tops_MSD.at(i) <= 210)
  		{
  			std::cout << "hello i am in" << std::endl;
  			htopsMSD->Fill(Signal_Topfirst_Tops_MSD.at(i),Weight_XS);
  		}
  	}

  	if (i%10000==0)
  	{
  		std::cout << i << std::endl;
  	}
  }
  	
  	
  	//set style
  	TCanvas * cs = new TCanvas("cs","cs",10,10,1100,800);
  	hsoftDropMass->SetTitleOffset(1.1,"x");
		hsoftDropMass->SetTitleSize(0.04,"x");
		hsoftDropMass->SetLabelSize(0.04,"x");
		hsoftDropMass->SetTitleOffset(1.3,"y");
		hsoftDropMass->SetTitleSize(0.04,"y");
		hsoftDropMass->SetLabelSize(0.04,"y");
  	hsoftDropMass->GetXaxis()->SetTitle("m_{SD}");
  	hsoftDropMass->GetYaxis()->SetTitle("Events");
  	hsoftDropMass->SetStats(kFALSE);
  	int norm=1;
  	hsoftDropMass->Scale(norm/hsoftDropMass->Integral());
  	htopsMSD->Scale(norm/htopsMSD->Integral());
  	hsoftDropMass->Draw("e");
  	htopsMSD->SetFillColor(2);
  	htopsMSD->Draw("same e");
  	
  	//save to disk
  	cs->SaveAs("/nfs/dust/cms/user/kziehl/plots/Zprime/BKG_QCD_SDM_Tops_MSD.pdf");
  	file->cd();
  	hsoftDropMass->Write("BKG_QCD_SDM_Tops_MSD");
  	file->Close();
  	
  	
}
