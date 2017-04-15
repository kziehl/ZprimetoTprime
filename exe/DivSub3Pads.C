#include <iostream>

#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void DivSub3Pads()
{
	//disable error in x
	gStyle->SetErrorX(0);
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
	//subtraction and ratio
	TH1F * hsub = new TH1F("hsub","hsub",hsum_data->GetSize()-2,hsum_data->GetXaxis()->GetXmin(),hsum_data->GetXaxis()->GetXmax());
	TH1F * hratio = new TH1F("hratio","hratio",hsum_data->GetSize()-2,hsum_data->GetXaxis()->GetXmin(),hsum_data->GetXaxis()->GetXmax());
	//adding histograms
	hsum_data->Add(hfirst,httbar); hsum_data->Add(hzprime);
	hsum_pred->Add(httm,httbar); hsum_pred->Add(hzprimebkg);
	hsum_pred_zprime->Add(httm,httbar); hsum_pred_zprime->Add(hzprime);
	hsum_bkg->Add(httm,httbar);
	
		// canvas
	TCanvas *c1 = new TCanvas("c1","c1",800,800);
	c1->SetTicks(0,0);
	
	//pad 1 contains graphic
	TPad *pad1 = new TPad("pad1","pad1",0.,0.5,1.,1.0);
	pad1->SetBottomMargin(0);
	pad1->Draw();
	pad1->cd();
	//style for sum_pred
	hsum_pred->SetTitle("");
	hsum_pred->GetXaxis()->SetRangeUser(500,4000);
	//hsum_pred->GetXaxis()->SetTitle("m_{Z'} in GeV");
	//hsum_pred->GetYaxis()->SetRangeUser(0,3000); //doesnt work
	hsum_pred->GetYaxis()->SetTitle("Events");
	hsum_pred->GetYaxis()->ChangeLabel(1,-1,0);
	hsum_pred->SetLineWidth(2);
	hsum_pred->SetLineColor(1);
	hsum_pred->SetFillColor(2);
	hsum_pred->SetLabelSize(0.05,"y");
	hsum_pred->SetTitleSize(0.06,"y");
	hsum_pred->SetTitleOffset(0.8,"y");
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

	
	
	
	
	
	
	// ratio plot in pad 2
	c1->cd();
	TPad *pad2 = new TPad("pad2","pad2",0.,0.3,1.,0.5);
	pad2->SetBottomMargin(0);
	pad2->SetTopMargin(0);
	pad2->Draw();
	pad2->cd();
	//ratio plot options
	hratio->Divide(hsum_data,hsum_pred);
	hratio->SetMarkerStyle(8);
	hratio->SetTitle("");
	hratio->SetMarkerSize(0.8);
	hratio->SetMinimum(0);
	hratio->SetMaximum(2.0);
	hratio->SetLineColor(1);
	hratio->SetLabelSize(0.12,"y");
	hratio->GetXaxis()->SetRangeUser(500,4000);
	hratio->GetXaxis()->SetLabelSize(0);
	hratio->GetYaxis()->SetNdivisions(-204); 
	hratio->GetYaxis()->ChangeLabel(1,-1,0);
	hratio->GetYaxis()->ChangeLabel(5,-1,0);
	hratio->GetYaxis()->SetTitleSize(0.15);
	hratio->GetYaxis()->SetTitle("#frac{MCData}{Pred.}");
	hratio->GetYaxis()->SetTitleOffset(0.3);
	hratio->GetYaxis()->CenterTitle(true);
	hratio->Draw("pe same");
	//lateral line
	TLine *lratio = new TLine(500,1,4000,1);
	lratio->SetLineColor(1);
	lratio->SetLineStyle(2);
	lratio->Draw("same");
	
	
	
	
	
	// sub plot in pad 3
	c1->cd();
	TPad *pad3 = new TPad("pad3","pad3",0.,0.0,1.,0.3);
	pad3->SetBottomMargin(0.3);
	pad3->SetTopMargin(0);
	pad3->Draw();
	pad3->cd();
	//define the sub plot
	hsub->Add(hsum_data);
	hsub->Add(hsum_pred,-1);
	hsub->SetLineColor(1);
	hsub->SetMinimum(-200);
	hsub->SetMaximum(600);
	//hsub->Sumw2();
	hsub->SetTitle("");
	hsub->SetLabelSize(0.09,"yx");
	//hsub->SetLabelSize(0.0,"x");
	hsub->SetLabelOffset(0.03,"x");
	hsub->SetStats(false);
	hsub->SetNdivisions(-204,"y"); 
	hsub->GetYaxis()->ChangeLabel(1,-1,0);
	hsub->GetYaxis()->ChangeLabel(5,-1,0);
	hsub->GetYaxis()->SetTitleSize(0.1);
	hsub->GetYaxis()->SetTitle("MCData - Pred.");
	hsub->GetYaxis()->SetTitleOffset(0.44);
	hsub->GetYaxis()->CenterTitle(true);
	hsub->GetXaxis()->SetTitleSize(0.1);
	hsub->GetXaxis()->SetTitleOffset(1.25);
	hsub->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsub->SetMarkerStyle(8);
	hsub->SetMarkerSize(0.8);
	//hsub->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsub->GetXaxis()->SetRangeUser(500,4000);
	hsub->Draw("pe");
	TLine *l = new TLine(500,0,4000,0);
	l->SetLineColor(1);
	l->SetLineStyle(2);
	l->Draw("same");
	
	
	
	//Legend	
	pad1->cd();
	gRStyle->BuildLegend(hsum_pred_zprime,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","l","RightUp",6);
	gRStyle->BuildLegend(hsum_data,"MC Data","ep");
	gRStyle->BuildLegend(0,"Prediction:","");
	gRStyle->BuildLegend(hsum_pred,"Signal contamination","f");
	gRStyle->BuildLegend(httbar,"Top quark","f");
	gRStyle->BuildLegend(hsum_bkg,"QCD Prediction","f");


	
}
