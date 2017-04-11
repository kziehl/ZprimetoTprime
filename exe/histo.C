#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void histo()
{
	//gRStyle->SetGlobalStyle();
	TFile *file = new TFile("/home/kevin/Desktop/file/number_of_entries.root");
	
	TH1F* h1 = dynamic_cast<TH1F*>(file->Get("Amount_of_tops"));
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("Amount_of_ak8"));

	
	//h7->Scale(1/h7->Integral());
	//h8->Scale(1/h8->Integral());

	gRStyle->PrintCanvasTH1F(h1,"","Amount of entries","Events","hist");
	h2->SetLineColor(2);
  h2->SetLineWidth(2);
  h2->Draw("same hist");
  gRStyle->BuildLegend(h1,"Top Quark","l","RightUp",2);
	gRStyle->BuildLegend(h2,"AK8 Jet","l");


	
}
