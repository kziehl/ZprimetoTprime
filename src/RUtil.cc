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
void RUtil::PrintRatioPlot(TH1F* histo1,TH1F* histo2,const char* titleyaxis,const char* titlexaxis, const char* titleratioy)
{
	if (histo1->GetSize() != histo2->GetSize()) {
		std::cout << "Failed to add histograms with different number of bins" << std::endl;
		return;
	}
	gStyle->SetOptStat(false);
	gStyle->SetErrorX(false);
	// canvas
	TCanvas *c1 = new TCanvas("c1","c1",800,800);
	c1->SetTicks(0,0);
	
	//pad 1 contains graphic
	TPad *pad1 = new TPad("pad1","pad1",0.,0.4,1.,1.0);
	pad1->SetBottomMargin(0);
	pad1->Draw();
	pad1->cd();
	//style histo1
	histo1->SetLineWidth(2);
	histo1->SetLineColor(2);
	histo1->SetTitle("");
	//x axis histo 1
	histo1->GetXaxis()->SetRangeUser(500,4000);
	//y axis histo 1
	histo1->GetYaxis()->SetTitle(titleyaxis);
	histo1->GetYaxis()->ChangeLabel(1,-1,0); //suppress printing 0
	histo1->SetLabelSize(0.06,"y");
	histo1->SetTitleSize(0.07,"y");
	histo1->SetTitleOffset(0.7,"y");
	//draw
	histo1->Scale(37.82);
	histo1->GetYaxis()->SetRangeUser(0,3000);
	histo1->Draw("histe");
	//histo 2 style
	histo2->SetLineWidth(2);
	histo2->SetLineColor(4);
	histo2->Scale(37.82);
	histo2->Draw("histe same");
	// Style
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPrivateWork("l");
	gRStyle->PrintCMSPublicationStatus("Simulation");

	// ratio plot in pad 2
	c1->cd();
	TPad *pad2 = new TPad("pad2","pad2",0.,0.0,1.,0.4);
	pad2->SetBottomMargin(0.3);
	pad2->SetTopMargin(0);
	pad2->Draw();
	pad2->cd();
	//ratio plot options
	TH1F * hratio = new TH1F("hratio","hratio",histo2->GetSize()-2,histo2->GetXaxis()->GetXmin(),histo2->GetXaxis()->GetXmax());
	hratio->Divide(histo1,histo2);
	hratio->SetMarkerStyle(8);
	hratio->SetTitle("");
	hratio->SetMarkerSize(0.8);
	hratio->SetMinimum(0);
	hratio->SetMaximum(2.0);
	hratio->SetLineColor(1);
	hratio->SetLabelSize(0.09,"yx");
	hratio->GetXaxis()->SetRangeUser(500,4000);
	hratio->GetYaxis()->SetNdivisions(-204); 
	hratio->GetYaxis()->ChangeLabel(1,-1,0);
	hratio->GetYaxis()->ChangeLabel(5,-1,0);
	hratio->GetYaxis()->SetTitleSize(0.1);
	hratio->GetXaxis()->SetTitleSize(0.1);
	hratio->GetYaxis()->SetTitle(titleratioy);
	hratio->GetXaxis()->SetTitle(titlexaxis);
	hratio->GetYaxis()->SetTitleOffset(0.41);
	hratio->GetYaxis()->CenterTitle(true);
	hratio->Draw("pe same");
	//lateral line
	TLine *lratio = new TLine(500,1,4000,1);
	lratio->SetLineColor(1);
	lratio->SetLineStyle(2);
	lratio->Draw("same");
	pad1->cd();
}


TH1F* RUtil::DrawStackPlot(TH1F* histo1, TH1F* histo2,TH1F* histo3)
{
	if (histo1->GetSize() != histo2->GetSize()) {
		std::cout << "Failed to add histograms with different number of bins" << std::endl;
		return 0; //TODO:this will cause an error!
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
	histo2->Add(histo1);
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



