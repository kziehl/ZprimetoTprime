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
	
	TH1F* h1 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_M"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Zprime_M"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_no_top_Zprime_M"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("QCD_misstag"));
	h1->Scale(1/h1->Integral());
	h2->Scale(1/h2->Integral());
	
	gRUtil->PrintRatioPlot(h1,h2);
	//gRUtil->PrintRatioPlot(h1,h3);
	//gRUtil->PrintRatioPlot(h3,h2);
	//h1->SetTitle("A simple Ratio");

	gRStyle->BuildLegend(h1,"QCD Prediction","l","RightUp",2);
	gRStyle->BuildLegend(h2,"QCD Mistag","l");

	
}
