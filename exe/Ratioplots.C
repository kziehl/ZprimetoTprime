#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void Ratioplots()
{
	//gRStyle->SetGlobalStyle();
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis.root");
	//TFile *f = new TFile("/home/kevin/Desktop/file/QCD_false_negativ_bottom_W_tprime.root");
	//TFile *g = new TFile("/home/kevin/Desktop/file/QCD_false_negativ_2.root");
	
	TH1F* h1 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_AK8_top_candidates_highest_pt"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Tops_Pt"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_no_top_Zprime_M"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("QCD_misstag"));
	//TH2F* h5 = dynamic_cast<TH2F*>(f->Get("BKG_QCD_false_negativ"));
	//TH2F* h6 = dynamic_cast<TH2F*>(g->Get("BKG_QCD_false_negativ"));
	TH1F* h7 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Tprime_M"));
	TH1F* h8 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Tprime_M"));
	
	//h7->Scale(1/h7->Integral());
	//h8->Scale(1/h8->Integral());
	
	gRUtil->PrintRatioPlot(h7,h8);
	//gRUtil->PrintRatioPlot(h1,h3);
	//gRUtil->PrintRatioPlot(h3,h2);
	//h1->SetTitle("A simple Ratio");

	//gRStyle->PrintCrossSection();
	//gRStyle->PrintCMSPublicationStatus("Private Work");
	
	//h4->Draw("histe");
		//gRStyle->PrintCMSPublicationStatus("Private Work");
	gRStyle->BuildLegend(h7,"QCD Mistag","l","RightUp",2);
	gRStyle->BuildLegend(h8,"QCD Prediction","l");

	
}
