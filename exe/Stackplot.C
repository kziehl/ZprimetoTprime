#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void Stackplot()
{
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis.root");
	//prediction
	TH1F* histo1 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_M"));
	//data sampling
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Zprime_M"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("TTbar_Signal_Topfirst_Zprime_M"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_Signal_Topfirst_Zprime_M"));
		

	//data sampling
	TH1F * data = new TH1F("data","data",histo1->GetSize()-2,histo1->GetXaxis()->GetXmin(),histo1->GetXaxis()->GetXmax());
	data->Add(h2,h3);
	data->Add(h4);
	data->SetMarkerStyle(8);
	data->SetMarkerSize(1.1);
	data->SetLineColor(1);
	data->Scale(37.82);
	gStyle->SetErrorX(0);
	// bkg
	TH1F* sim = gRUtil->DrawStackPlot(h3,histo1,h4);
	data->Draw("pe same");
	
	//ratio pl

	gRStyle->BuildLegend(data,"Data","pe");

	
}
