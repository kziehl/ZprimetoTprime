#include <iostream>
#include <cmath>
#include <vector>

#include "TH1F.h"
#include "TChain.h"
#include "TString.h"
#include "TRatioPlot.h"
#include "TCanvas.h"

#include "../include/RUtil.h"
#include "../include/RStyle.h"

RUtil* gRUtil;

Double_t RUtil::GetYMaxOfList (const std::vector<TH1F*>& histo)
{
  Double_t highest_value {0};
  for (unsigned int i=0; i<histo.size(); i++)
  {
    Double_t curr_highest {0};
    curr_highest = histo[i]->GetMaximum();
    
    if (highest_value < curr_highest) highest_value = curr_highest;
  }
  return highest_value;
}
// what happens if variable is not an array? -> length not defined ->  use function template??
Double_t RUtil::GetMaxValOfVar (TChain* chain, const char* variable, const char* length)
{
    Long64_t nentries = chain->GetEntries();
    std::vector <Float_t> branch(1000); //initial with a length large enough
    Int_t Length_branch(0);
    chain->SetBranchAddress(variable,&(branch.front()));
    chain->SetBranchAddress(length,&Length_branch);
    chain->SetBranchStatus("*",0);
    chain->SetBranchStatus(variable,1);
    chain->SetBranchStatus(length,1);
    Double_t MaxVal{0};
    std::cout << "Determine maximum value of " << variable << std::endl;
    for (Long64_t i=0;i<nentries;i++)
    {
        chain->GetEntry(i);
        for (Int_t j=0;j<Length_branch;j++)
        {
            if (branch.at(j)>MaxVal) MaxVal=branch.at(j);
        }
        if (i%10000==0)
  			{
  				std::cout << "Evaluating entry...." << i << std::endl;
  			}
    }
    return MaxVal;
}
//TODO: How to change labels? Maybe shift some of the style settings in the exe file
void RUtil::PrintRatioPlot(TH1F* histo1,TH1F* histo2)
{
	// canvas
	TCanvas *c1 = new TCanvas();
	c1->SetTicks(0,0);
	TRatioPlot* Ratio = new TRatioPlot(histo1,histo2,"divsym");
	// hist style
	histo1->SetTitle("");
	histo1->SetStats(false);
	histo1->SetLineWidth(2);
	histo1->SetLineColor(4); // blue
	histo1->GetXaxis()->SetTitle("p_{T} in GeV");//m_{Z'} in GeV
	histo1->GetYaxis()->SetTitle("Events");
	histo2->SetLineWidth(2);
	histo2->SetLineColor(2); // red
	//histo2->SetMarkerStyle(8);
	//Ratio Style
	Ratio->SetSeparationMargin(0);
	Ratio->SetH2DrawOpt("histe1");
	Ratio->SetH1DrawOpt("histe1");
	Ratio->Draw("fhideup");
	// style of graph
	Ratio->GetLowerRefGraph()->SetMinimum(0.5);
	Ratio->GetLowerRefGraph()->SetMaximum(1.5);
	Ratio->GetLowerRefGraph()->SetLineColor(1);
	Ratio->GetLowYaxis()->SetNdivisions(305); 
	//Ratio->GetLowerRefYaxis()->ChangeLabel(1,-1,0);
	//Number of grid lines
	std::vector<double> lines = {1};
	Ratio->SetGridlines(lines);
	// Style
	Ratio->GetUpperPad()->cd();
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPublicationStatus("Private Work");
}


TH1F* RUtil::DrawStackPlot(TH1F* histo1, TH1F* histo2,TH1F* histo3)
{
	if (histo1->GetSize() != histo2->GetSize()) {
		std::cout << "Failed to add histograms with different number of bins" << std::endl;
	}
	// adding histograms + style
	TH1F* tHisto = new TH1F("tHisto","tHisto",histo1->GetSize()-2,histo1->GetXaxis()->GetXmin(),histo1->GetXaxis()->GetXmax());
	tHisto->Add(histo1,histo2);
	tHisto->Add(histo3);
	TCanvas *c1 = new TCanvas();
	c1->SetTicks(0,0);
	tHisto->GetXaxis()->SetTitle("m_{Z'} in GeV");
	tHisto->GetYaxis()->SetTitle("Events");
	tHisto->SetStats(false);
	tHisto->SetTitle("");
	tHisto->SetFillColor(2);
	tHisto->SetLineColor(1);
	tHisto->SetLineWidth(2);
	tHisto->Scale(37.82); //integrated luminosity 2016
	tHisto->Draw("histe");
	gRStyle->BuildLegend(tHisto,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","fe","RightUp",4);
	//style histo 2
	histo2->SetLineWidth(2);
	histo2->SetFillColor(5);
	histo2->SetLineColor(1);
	histo2->Scale(37.82);
	histo2->Draw("histe same");
	gRStyle->BuildLegend(histo2,"QCD Prediction","f");
	//style histo 1
	histo1->SetLineWidth(2);
	histo1->SetFillColor(4);
	histo1->SetLineColor(1);
	histo1->Scale(37.82);
	histo1->Draw("histe same");
	gRStyle->BuildLegend(histo1,"Top quark","f");
	//style
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPublicationStatus("Private Work");
	
	return tHisto;
}



