#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void StacktwoRatio()
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
	TH1F* hzprimebkg = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_TTM_Zprime_M"));
	TH1F* hsum_data = new TH1F("sum_data","sum_data",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_pred = new TH1F("sum_pred","sum_pred",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_bkg = new TH1F("sum_bkg","sum_bkg",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_pred_zprime = new TH1F("sum_pred_zprime","sum_pred",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	//adding histograms
	hsum_data->Add(hfirst,httbar); hsum_data->Add(hzprime);
	hsum_pred->Add(httm,httbar); hsum_pred->Add(hzprimebkg);
	hsum_pred_zprime->Add(httm,httbar); hsum_pred_zprime->Add(hzprime);
	hsum_bkg->Add(httm,httbar);
		// canvas
	TCanvas *c1 = new TCanvas("c1","c1",800,800);
	c1->SetTicks(0,0);
	//upper plot in pad 1
	TPad *pad1 = new TPad("pad1","pad1",0.,0.4,1.,1.0);
	pad1->SetBottomMargin(0);
	pad1->Draw();
	pad1->cd();
	//ratio plot
	TRatioPlot* Ratio = new TRatioPlot(hsum_data,hsum_pred,"divsym");
	// style for sum_data
	hsum_data->SetTitle("");
	hsum_data->SetMarkerStyle(8);
	hsum_data->SetMarkerSize(1.1);
	hsum_data->SetLineColor(1);
	hsum_data->Scale(37.82);
	//hsum_data->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsum_data->GetYaxis()->SetTitle("Events");
	//style for sum_pred
	hsum_pred->SetLineWidth(2);
	hsum_pred->SetFillStyle(3000);
	hsum_pred->SetLineColor(1);
	hsum_pred->SetFillColor(2);
	hsum_pred->Scale(37.82);
	//Ratio Style
	Ratio->SetSeparationMargin(0);
	Ratio->SetH1DrawOpt("pe");
	Ratio->SetH2DrawOpt("histe");
	Ratio->Draw("fhideup same");
	// style of graph
	Ratio->GetLowerRefGraph()->SetMinimum(0.5);
	Ratio->GetLowerRefGraph()->SetMaximum(1.5);
	Ratio->GetLowerRefGraph()->SetLineColor(1);
	Ratio->GetLowerRefXaxis()->SetLabelSize(0);
	Ratio->GetLowYaxis()->SetNdivisions(305); 
	//Ratio->GetLowerRefYaxis()->ChangeLabel(1,-1,0);
	//Number of grid lines
	std::vector<double> lines = {1};
	Ratio->SetGridlines(lines);
	// Style
	Ratio->GetUpperPad()->cd();
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPublicationStatus("Private Work");
	//plotting prediction + signal
	hsum_pred_zprime->SetLineWidth(2);
	hsum_pred_zprime->SetLineStyle(2);
	hsum_pred_zprime->SetLineColor(8);
	hsum_pred_zprime->Scale(37.82);
	hsum_pred_zprime->Draw("same histe");
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
	//hsum_data->Draw("same pe");
	//Legend
	gRStyle->BuildLegend(hsum_pred,"Signal contamination","f","RightUp",5);
	gRStyle->BuildLegend(hsum_pred_zprime,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","l");
	gRStyle->BuildLegend(httbar,"Top quark","f");
	gRStyle->BuildLegend(hsum_bkg,"QCD Prediction","f");
	gRStyle->BuildLegend(hsum_data,"Data","ep");
	//lower plot will be in pad
	c1->cd();
	TPad *pad2 = new TPad("pad2","pad2",0.,0.,1.,0.4);
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.1);
	pad2->Draw();
	pad2->cd();
	//define the ratio plot
	TH1F * hsub = new TH1F("hsub","hsub",hsum_data->GetSize()-2,hsum_data->GetXaxis()->GetXmin(),hsum_data->GetXaxis()->GetXmax());
	hsub->Add(hsum_data);
	hsub->Add(hsum_pred,-1);
	hsub->SetLineColor(1);
	hsub->SetMinimum(-5);
	hsub->SetMaximum(15);
	//hsub->Sumw2();
	hsub->SetTitle("");
	hsub->SetLabelSize(0.05);
	hsub->SetStats(false);
	hsub->SetNdivisions(305,"y"); 
	hsub->SetMarkerStyle(2);
	hsub->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsub->Draw("e1p");
	TLine *l = new TLine(0,0,5000,0);
	l->SetLineColor(1);
	l->SetLineStyle(2);
	l->Draw("same");
	
}
