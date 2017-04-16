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
	TFile *f = new TFile("/home/kevin/Desktop/file/QCD_false_negativ_bottom_W_tprime.root");
	TFile *g = new TFile("/home/kevin/Desktop/file/QCD_false_negativ_2.root");
	
	TH1F* h1 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_AK8_top_candidates_highest_pt"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Tops_Pt"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_no_top_Zprime_M"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("QCD_misstag"));
	TH2F* h5 = dynamic_cast<TH2F*>(f->Get("BKG_QCD_false_negativ"));
	TH2F* h6 = dynamic_cast<TH2F*>(g->Get("BKG_QCD_false_negativ"));
	TH1F* h7 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Tprime_M"));
	TH1F* h8 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Tprime_M"));
	
	gRUtil->PrintRatioPlot(h1,h2);
	//template: 	gRStyle->BuildLegend(tHisto,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","fe","RightUp",4);
	gRStyle->BuildLegend(h1,"teso","l","RightUp",2);
	gRStyle->BuildLegend(h2,"jkjk");

	
}
