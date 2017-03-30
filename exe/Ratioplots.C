#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void Ratioplots()
{
	//gRStyle->SetGlobalStyle();
	TFile *file = new TFile("/home/kevin/Desktop/analysis_QCD.root");
	
	TH1F* h1 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Tprime_M"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Tprime_M"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_no_top_Tprime_M"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("QCD_misstag"));
	//h2->Scale(1/h2->Integral());
	//h3->Scale(1/h3->Integral());
	
	//gRUtil->PrintRatioPlot(h1,h2);
	//gRUtil->PrintRatioPlot(h1,h3);
	gRUtil->PrintRatioPlot(h3,h2);
	//h1->SetTitle("A simple Ratio");

	gRStyle->BuildLegend(h2,"QCD Mistag","l","RightUp",2);
	gRStyle->BuildLegend(h3,"QCD Prediction inverted top tag","l");

	
}
