#include <iostream>
#include <vector>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void BuildTH2()
{
	//gRStyle->SetGlobalStyle();
	TFile *file = new TFile("/home/kevin/Desktop/file/ak8candidate_top_comparison.root");
	
	TH1F* h1 = dynamic_cast<TH1F*>(file->Get("top_pt"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("AK8pt"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("AK8_highest_pt"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("top_highest_pt"));
	
	//create TH2
	TH2F* h10 = new TH2F("h10","",100,0,5000,100,0,5000);
	TH2F* h11 = new TH2F("h11","",100,0,5000,100,0,5000);
	
	for(int i=1;i<5000;i++)
	{
		h10->Fill(h1->GetBinContent(i),h2->GetBinContent(i));
	}
	
	//set style
  TCanvas * cs = new TCanvas("cs","cs",800,800);
  h10->SetTitleOffset(0.85,"x");
	h10->SetTitleSize(0.05,"x");
	h10->SetLabelSize(0.04,"x");
	h10->SetTitleOffset(0.8,"y");
	h10->SetTitleSize(0.05,"y");
	h10->SetLabelSize(0.04,"y");
  h10->GetXaxis()->SetTitle("Top p_{T} in GeV");
  h10->GetYaxis()->SetTitle("AK8 Jet p_{T} in GeV");
  h10->SetStats(false);
	h10->Draw("colz");
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPublicationStatus("Private Work");
}
