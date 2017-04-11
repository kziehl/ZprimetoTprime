#include <iostream>
#include <vector>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"


void histo()
{
	//gRStyle->SetGlobalStyle();
	TFile *file = new TFile("/home/kevin/Desktop/file/number_of_entries.root");
	
	vector<TH1F*> histo(2);
	histo.at(0) = dynamic_cast<TH1F*>(file->Get("Amount_of_tops"));
	histo.at(1) = dynamic_cast<TH1F*>(file->Get("Amount_of_ak8"));

	
	histo.at(0)->Scale(1/histo.at(0)->Integral());
	histo.at(1)->Scale(1/histo.at(1)->Integral());

	gRStyle->PrintCanvasTH1F(histo,"","Amount of entries","Events","hist");
	gRStyle->BuildLegend(histo.at(0),"Top quark","l","RightUp",2);
	gRStyle->BuildLegend(histo.at(1),"AK8 Jet","l");
	
}
