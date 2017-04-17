#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void Stackplot()
{
	//disable error in x
	gStyle->SetErrorX(0);
	//no stat box
	gStyle->SetOptStat(0);
	// load file
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis_mistagrate_via_all");
	//create histograms
	TH1F* httm = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_mistag_all_M"));
	TH1F* hfirst = dynamic_cast<TH1F*>(file->Get("QCD_Signal_topfirst_zprime_M"));
	TH1F* httbar = dynamic_cast<TH1F*>(file->Get("TTbar_Signal_topfirst_zprime_M"));
	TH1F* hzprime = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_Signal_topfirst_zprime_M"));
	TH1F* hzprimebkg = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_TTM_Zprime_mistag_all_M"));
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

	//style for sum_pred
	hsum_pred->SetTitle("");
	hsum_pred->GetXaxis()->SetRangeUser(500,4000);
	//hsum_pred->GetXaxis()->SetTitle("m_{Z'} in GeV");
	//hsum_pred->GetYaxis()->SetRangeUser(0,3000); //doesnt work
	hsum_pred->GetYaxis()->SetTitle("Events");
	hsum_pred->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsum_pred->GetYaxis()->ChangeLabel(1,-1,0);
	hsum_pred->SetLineWidth(2);
	hsum_pred->SetLineColor(1);
	hsum_pred->SetFillColor(2);
	hsum_pred->SetLabelSize(0.04,"yx");
	hsum_pred->SetTitleSize(0.05,"yx");
	hsum_pred->SetTitleOffset(1,"y");
	hsum_pred->SetTitleOffset(0.87,"x");
	hsum_pred->Scale(37.82);
	hsum_pred->GetYaxis()->SetRangeUser(0,3000);
	hsum_pred->Draw("histe");
	//data plotting
	hsum_data->SetMarkerStyle(8);
	hsum_data->SetMarkerSize(1.1);
	hsum_data->SetLineColor(1);
	hsum_data->Scale(37.82);
	hsum_data->Draw("pe same");
	// Style
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPrivateWork("l");
	gRStyle->PrintCMSPublicationStatus("Simulation");
	//draw other histos
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
	//draw again
	hsum_data->Draw("same pe");
	
	//Legend	
	gRStyle->BuildLegend(hsum_pred_zprime,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","l","RightUp",6);
	gRStyle->BuildLegend(hsum_data,"MC Data","ep");
	gRStyle->BuildLegend(0,"Prediction:","");
	gRStyle->BuildLegend(hsum_pred,"Signal contamination","f");
	gRStyle->BuildLegend(httbar,"Top quark","f");
	gRStyle->BuildLegend(hsum_bkg,"QCD Prediction","f");
	
}
