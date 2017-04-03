#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"

void Ratiodiff()
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
	//Define the canvas
	TCanvas *c1 = new TCanvas("c1","canvas",800,800);
	//upper plot in pad 1
	TPad *pad1 = new TPad("pad1","pad1",0.,0.3,1.,1.0);
	pad1->SetBottomMargin(0);
	pad1->Draw();
	pad1->cd();
	//draw stack plot
	hsum_pred->SetTitle("");
	hsum_pred->GetYaxis()->SetTitle("Events");
	hsum_pred->SetFillColor(2);
	hsum_pred->SetLineColor(1);
	hsum_pred->Scale(37.82);
	hsum_pred->SetLineWidth(2);
	hsum_pred->Draw("histe");
	gRStyle->BuildLegend(hsum_pred,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","fe","RightUp",4);
	hsum_bkg->SetFillColor(5);
	hsum_bkg->SetLineColor(1);
	hsum_bkg->Scale(37.82);
	hsum_bkg->SetLineWidth(2);
	hsum_bkg->Draw("histe same");
	gRStyle->BuildLegend(hsum_bkg,"QCD Prediction","fe");	
	httbar->SetFillColor(4);
	httbar->Scale(37.82);
	httbar->SetLineColor(1);
	httbar->SetLineWidth(2);
	httbar->Draw("same histe");
	gRStyle->BuildLegend(httbar,"Top quark","f");
	// draw data
	hsum_data->SetMarkerStyle(8);
	hsum_data->SetMarkerSize(1.1);
	hsum_data->SetLineColor(1);
	hsum_data->Scale(37.82);
	hsum_data->Draw("pe same");
	gRStyle->BuildLegend(hsum_data,"Data","pe");
	//style
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPublicationStatus("Private Work");
	//lower plot will be in pad
	c1->cd();
	TPad *pad2 = new TPad("pad2","pad2",0.,0.05,1.,0.3);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.2);
	pad2->Draw();
	pad2->cd();
	//Define the ratio plot
	TH1F *ratio = (TH1F*)hsum_data->Clone("data");
	ratio->SetLineColor(kBlack);
	ratio->SetMinimum(0.5);
	ratio->SetMaximum(1.5);
	ratio->Sumw2();
	ratio->SetStats(false);
	ratio->Divide(hsum_pred)
	}
