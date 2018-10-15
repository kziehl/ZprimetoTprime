#include <iostream>

#include "TRatioPlot.h"
#include "TFile.h"
#include "TH1F.h"


#include "../include/RUtil.h"
#include "../include/RStyle.h"

void Stackplot2()
{
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis.root");
	//prediction
	TH1F* histo1 = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_M"));
	//data sampling
	TH1F* h2 = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Zprime_M"));
	TH1F* h3 = dynamic_cast<TH1F*>(file->Get("TTbar_Signal_Topfirst_Zprime_M"));
	TH1F* h4 = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_Signal_Topfirst_Zprime_M"));


}
