#include <iostream>
#include <cmath>
#include <vector>

#include "TH1F.h"
#include "TChain.h"
#include "TString.h"
#include "TRatioPlot.h"
#include "TCanvas.h"

#include "../include/RUtil.h"
#include "../include/RStyle.h"

RUtil* gRUtil;

Double_t RUtil::GetYMaxOfList (const std::vector<TH1F*>& histo)
{
  Double_t highest_value {0};
  for (unsigned int i=0; i<histo.size(); i++)
  {
    Double_t curr_highest {0};
    curr_highest = histo[i]->GetMaximum();
    
    if (highest_value < curr_highest) highest_value = curr_highest;
  }
  return highest_value;
}
// what happens if variable is not an array? -> length not defined ->  use function template??
Double_t RUtil::GetMaxValOfVar (TChain* chain, const char* variable, const char* length)
{
    Long64_t nentries = chain->GetEntries();
    std::vector <Float_t> branch(1000); //initial with a length large enough
    Int_t Length_branch(0);
    chain->SetBranchAddress(variable,&(branch.front()));
    chain->SetBranchAddress(length,&Length_branch);
    chain->SetBranchStatus("*",0);
    chain->SetBranchStatus(variable,1);
    chain->SetBranchStatus(length,1);
    Double_t MaxVal{0};
    std::cout << "Determine maximum value of " << variable << std::endl;
    for (Long64_t i=0;i<nentries;i++)
    {
        chain->GetEntry(i);
        for (Int_t j=0;j<Length_branch;j++)
        {
            if (branch.at(j)>MaxVal) MaxVal=branch.at(j);
        }
        if (i%10000==0)
  			{
  				std::cout << "Evaluating entry...." << i << std::endl;
  			}
    }
    return MaxVal;
}

TRatioPlot* RUtil::PrintRatioPlot(TH1F* histo1,TH1F* histo2)
{
	TCanvas *c1 = new TCanvas();
	c1->SetTicks(0,1);
	TRatioPlot* Ratio = new TRatioPlot(histo1,histo2,"divsym");
	// hist style
	histo1->SetTitle("");
	histo1->SetStats(false);
	histo1->SetLineWidth(2);
	histo1->SetLineColor(4);
	histo1->GetXaxis()->SetTitle("m(Z') in GeV");
	histo1->GetYaxis()->SetTitle("Events");
	histo2->SetLineWidth(2);
	histo2->SetLineColor(2);
	//Ratio Style
	Ratio->SetSeparationMargin(0.05);
	Ratio->SetH2DrawOpt("hist");
	Ratio->Draw();
	Ratio->GetLowerRefGraph()->SetMinimum(0.5);
	Ratio->GetLowerRefGraph()->SetMaximum(1.2);
	Ratio->GetLowerRefGraph()->SetLineColor(1);
	Ratio->GetUpperPad()->cd();
	gRStyle->PrintCrossSection();
	gRStyle->PrintCMSPrivateWork();
	return Ratio;
}

