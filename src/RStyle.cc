#include <iostream>
#include <vector>
#include <cstring>

#include "TText.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TObject.h"
#include "TStyle.h"
#include "TLatex.h"

#include "../include/RStyle.h"
#include "../include/RUtil.h"
//TODO:  how to set title of a plot? A: Use TPad //adapt to new canvas size

RStyle* gRStyle;
TCanvas* RStyle::fCanvas{0};
TText* RStyle::fText{0};
TLegend* RStyle::fLegend{0};
TLatex* RStyle::fLatex{0};

const char* RStyle::fLeftDown="LeftDown";
const char* RStyle::fLeftUp="LeftUp";
const char* RStyle::fRightDown="RightDown";
const char* RStyle::fRightUp="RightUp";


void RStyle::PrintCrossSection(void)
{
	fLatex = new TLatex();
	fLatex->SetTextFont(42);
	fLatex->SetTextSize(0.04);
	fLatex->SetTextAlign(31); //left and bottom aligned
	//fLatex->DrawLatexNDC(gStyle->GetPadLeftMargin(),1-gStyle->GetPadTopMargin()+0.02,"2.69 fb^{-1} (13TeV)");
	fLatex->DrawLatexNDC(1-gStyle->GetPadRightMargin(),1-gStyle->GetPadTopMargin()+0.02,"37.82 fb^{-1} (13TeV)");
}


void RStyle::PrintCMSPrivateWork(void)
{
	fText = new TText();
	fText->SetTextFont(42);
	fText->SetTextSize(0.03);
	fText->SetTextAlign(31); //right and bottom aligned
	fText->DrawTextNDC(1-gStyle->GetPadRightMargin(),1-gStyle->GetPadTopMargin()+0.02,"CMS Private Work");
}


void RStyle::PrintCMSPublicationStatus(TString status)
{	 
	TString tStr = "#splitline{#font[42]{#scale[1.5]{#bf{CMS}}}}{#lower[0.2]{#font[42]{replace}}}";
	tStr.ReplaceAll("replace",status);
	fLatex = new TLatex();
	fLatex->SetTextAlign(13); //left and top aligned
	fLatex->DrawLatexNDC(gStyle->GetPadLeftMargin()+0.05,1-gStyle->GetPadTopMargin()-0.02,tStr);
}


void RStyle::BuildLegend(TH1F* histo,const char* descript,const char* option,const char* corner,Int_t nrows)
{
	TString tdescript = descript;
	Double_t tlengthNDC = tdescript.Length()*0.015; //1 char(here Q) ~ 0.015 NDC
	if(fLegend==0)
	{
		if(strcmp(corner,fLeftDown) == 0) fLegend = new TLegend(gStyle->GetPadLeftMargin(),gStyle->GetPadBottomMargin(),gStyle->GetPadLeftMargin()+tlengthNDC,gStyle->GetPadBottomMargin()+0.08*nrows);
		if(strcmp(corner,fLeftUp) == 0) fLegend = new TLegend(gStyle->GetPadLeftMargin(),1-gStyle->GetPadTopMargin()-0.08*nrows,gStyle->GetPadLeftMargin()+tlengthNDC,1-gStyle->GetPadTopMargin()); 
		if(strcmp(corner,fRightDown) == 0) fLegend = new TLegend(1-gStyle->GetPadRightMargin()-tlengthNDC,gStyle->GetPadBottomMargin(),1-gStyle->GetPadRightMargin(),gStyle->GetPadBottomMargin()+0.08*nrows); 
		if(strcmp(corner,fRightUp) == 0) fLegend = new TLegend(1-gStyle->GetPadRightMargin()-tlengthNDC,1-gStyle->GetPadTopMargin()-0.08*nrows,1-gStyle->GetPadRightMargin(),1-gStyle->GetPadTopMargin()); //height of an entry ~ 0.07
		
  	fLegend->SetBorderSize(0);
  	fLegend->SetLineStyle(1);
  	fLegend->SetLineWidth(1);
  	fLegend->SetLineColor(1);
  	fLegend->SetMargin(0.25);  //Distance between Left end of the box and entrytext
  	fLegend->SetFillStyle(0); //hollow
  	fLegend->SetFillColor(0);
  	fLegend->SetTextSize(0.04);
  }
	fLegend->AddEntry(histo,descript,option);
	fLegend->Draw();
}

// match this function with SetGlobalStyle
void RStyle::PrintCanvasTH1F(const std::vector<TH1F*>& histo,const char* title,const char* xaxistitle,const char* yaxistitle,const char* option)
{
	if (histo.size()==0) {
		std::cout << "Fatal error occured. No valid number of histograms." << std::endl;
		return;
	}
	Double_t tMax = gRUtil->GetYMaxOfList(histo);
	fCanvas = new TCanvas("Canvas","",0,0,800,800);
	//fCanvas->SetTicks(1,1);
	histo.at(0)->SetTitle(title);
  histo.at(0)->SetTitleOffset(0.8,"x");
  histo.at(0)->SetTitleSize(0.05,"x");
  histo.at(0)->SetLabelOffset(0.01,"x");
  histo.at(0)->SetLabelSize(0.04,"x");
  histo.at(0)->SetTitleSize(0.05,"y");
  histo.at(0)->SetLabelOffset(0.01,"y");
  histo.at(0)->SetLabelSize(0.04,"y");
  histo.at(0)->SetTitleOffset(1.,"y");
  histo.at(0)->GetXaxis()->SetTitle(xaxistitle);
  histo.at(0)->GetYaxis()->SetTitle(yaxistitle);
  histo.at(0)->SetStats(false);
  histo.at(0)->GetXaxis()->SetTicks("+");
  histo.at(0)->GetYaxis()->SetTicks("-");
  histo.at(0)->SetLineColor(1);
  histo.at(0)->SetLineWidth(2);
  histo.at(0)->GetYaxis()->SetRangeUser(0,1.1*(tMax+TMath::Sqrt(tMax)));
  histo.at(0)->Draw(option);
  //draw all histos in the same pad
  for (Int_t ihisto=1;ihisto<histo.size();ihisto++) {
  	histo.at(ihisto)->SetLineStyle(1);
  	histo.at(ihisto)->SetLineWidth(2);
  	histo.at(ihisto)->SetLineColor(1+ihisto);
  	histo.at(ihisto)->Draw("same hist");
  }
  gRStyle->PrintCrossSection();
  gRStyle->PrintCMSPublicationStatus("Private Work");
}

//TODO:still causes some unexpected behavior
void RStyle::SetGlobalStyle (void)
{
 // Suppress message when canvas has been saved
  //gErrorIgnoreLevel = 1001;

  // Zero horizontal error bars
  //gStyle->SetErrorX(0);

  //  For the canvas
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(800); //Height of canvas
  gStyle->SetCanvasDefW(800); //Width of canvas
  gStyle->SetCanvasDefX(0);   //Position on screen
  gStyle->SetCanvasDefY(0);
  
  //  For the frame
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1); //unenabled if BorderMode is
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1); // 0 white 1 black 2 red 4 blue
  gStyle->SetFrameLineStyle(0);
  gStyle->SetFrameLineWidth(1);
  gStyle->SetLineWidth(1);
    
/*    For the Pad 
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1); */
  
  //  Margins
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadLeftMargin(0.1);
  gStyle->SetPadRightMargin(0.1);

  //  For the histo:
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(2);
  gStyle->SetMarkerSize(1.2);
  gStyle->SetEndErrorSize(4);
  //gStyle->SetHatchesLineWidth(1); // unknown action

  //  For the statistics box:
  gStyle->SetOptStat(0);
  
//    For the axis
	gStyle->SetAxisColor(1,"XYZ");
  gStyle->SetTickLength(0.03,"XYZ");
  gStyle->SetNdivisions(510,"XYZ");
  gStyle->SetPadTickX(0);
  gStyle->SetPadTickY(0);
  gStyle->SetStripDecimals(kFALSE);
  
  //  For the axis labels and titles
  gStyle->SetTitleColor(1,"XYZ");
  gStyle->SetLabelColor(1,"XYZ");
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetLabelOffset(0.005,"XYZ");
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetTitleSize(0.04,"XYZ");
  gStyle->SetTitleXOffset(1);
  gStyle->SetTitleYOffset(5);

  //  For the legend
  gStyle->SetLegendBorderSize(0); 
}

