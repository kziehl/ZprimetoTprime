#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void StackRatio()
{
	//no stat box
	gStyle->SetOptStat(0);
	// load file
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis.root");
	//create histograms
	TH1F* httm = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_M"));
	TH1F* hfirst = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Zprime_M"));
	TH1F* httbar = dynamic_cast<TH1F*>(file->Get("TTbar_Signal_Topfirst_Zprime_M"));
	TH1F* hzprime = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_Signal_Topfirst_Zprime_M"));
	TH1F* hsum_data = new TH1F("sum_data","sum_data",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_pred = new TH1F("sum_pred","sum_pred",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_bkg = new TH1F("sum_bkg","sum_bkg",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	//adding histograms
	hsum_data->Add(hfirst,httbar); hsum_data->Add(hzprime);
	hsum_pred->Add(httm,httbar); hsum_pred->Add(hzprime);
	hsum_bkg->Add(httm,httbar);
		// canvas
	TCanvas *c1 = new TCanvas("c1","c1",800,800);
	c1->SetTicks(0,0);
	//ratio plot
	TRatioPlot* Ratio = new TRatioPlot(hsum_pred,hsum_data,"divsym");
	// style for sum_data
	hsum_data->SetMarkerStyle(8);
	hsum_data->SetMarkerSize(1.1);
	hsum_data->SetLineColor(1);
	hsum_data->Scale(37.82);
	//style for sum_pred
	hsum_pred->SetTitle("");
	hsum_pred->SetLineWidth(2);
	hsum_pred->SetLineColor(1);
	hsum_pred->SetFillColor(2);
	hsum_pred->Scale(37.82);
	hsum_pred->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsum_pred->GetYaxis()->SetTitle("Events");
	//Ratio Style
	Ratio->SetSeparationMargin(0);
	Ratio->SetH1DrawOpt("histe");
	Ratio->SetH2DrawOpt("pe");
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
	//plotting bkg
	hsum_bkg->SetLineWidth(2);
	hsum_bkg->SetLineColor(1);
	hsum_bkg->SetFillColor(5);
	hsum_bkg->Scale(37.82);
	hsum_bkg->Draw("same histe");		
	httbar->SetLineWidth(2);
	httbar->SetLineColor(1);
	httbar->SetFillColor(4);
	httbar->Scale(37.82);
	httbar->Draw("same histe");
	//Legend
	gRStyle->BuildLegend(hsum_pred,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","f","RightUp",4);
	gRStyle->BuildLegend(httbar,"Top quark","f");
	gRStyle->BuildLegend(hsum_bkg,"QCD Prediction","f");
	gRStyle->BuildLegend(hsum_data,"Data","ep");


	
}
