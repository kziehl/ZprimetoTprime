#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void Ratioplots()
{
	
	TFile *f = new TFile("/home/kevin/Desktop/file/analysis_mistagrate_all");
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis_QCD_Pt_new_mistagrate_all.root");
	TFile *g = new TFile("/home/kevin/Desktop/file/analysis_mistagrate_fancy.root");

	
	TH1F* h1 = dynamic_cast<TH1F*>(f->Get("QCD_Signal_topfirst_zprime_M"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_mistag_all_M"));
	TH1F* h3 = dynamic_cast<TH1F*>(g->Get("QCD_TTM_Zprime_mistag_all_M"));

	
	gRUtil->PrintRatioPlot(h1,h3,"Events / 100 GeV","m_{Z'} in GeV","#frac{Mistag}{Pred.}");
	//template: 	gRStyle->BuildLegend(tHisto,"m_{Z'}=2.5 TeV, m_{T}=1.5TeV","fe","RightUp",4);
	gRStyle->BuildLegend(h3,"QCD Prediction","l","RightUp",2);
	gRStyle->BuildLegend(h1,"QCD mistag");

	
}
