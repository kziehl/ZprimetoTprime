#include <iostream>
#include <vector>
#include <cmath>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TChain.h"

#include "../include/RUtil.h"
#include "../include/RLoader.h"
#include "../include/RStyle.h"


void Pt_eta_plots()
{
	//load file
	TFile *file = new TFile("/home/kevin/Desktop/file/QCD_false_negativ_bottom_W_tprime.root");
	
	TH2F* hdiv = dynamic_cast<TH2F*>(file->Get("BKG_QCD_false_negativ"));
	
	 //set style
  TCanvas * cs = new TCanvas("cs","cs",800,800);
  divide->SetTitleOffset(1.1,"x");
	divide->SetTitleSize(0.05,"x");
	divide->SetLabelSize(0.05,"x");
	divide->SetTitleOffset(1.3,"y");
	divide->SetTitleSize(0.05,"y");
	divide->SetLabelSize(0.05,"y");
  divide->GetXaxis()->SetTitle("#eta");
  divide->GetYaxis()->SetTitle("p_{T}");
  divide->SetStats(kFALSE);
	divide->Draw("colz");
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPublicationStatus("Private Work");
	
}
