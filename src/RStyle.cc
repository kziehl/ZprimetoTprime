#include <iostream>
#include <vector>
#include <cstring>

#include "TPaveText.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TObject.h"
#include "TStyle.h"

#include "../include/RStyle.h"
//TODO:  how to set title of a plot? A: Use TPad

TCanvas* RStyle::fCanvas{0};
TPaveText* RStyle::fPaveText{0};
TLegend* RStyle::fLegend{0};

const char* RStyle::fLeftDown="LeftDown";
const char* RStyle::fLeftUp="LeftUp";
const char* RStyle::fRightDown="RightDown";
const char* RStyle::fRightUp="RightUp";

void RStyle::PrintCrossSection(void)
{
	fPaveText = new TPaveText(0.67,0.87,0.9,0.97,"NB NDC");
	fPaveText->SetFillStyle(3000);
	fPaveText->SetLineColor(0);
	fPaveText->SetTextSize(0.03);
	fPaveText->SetTextFont(42);
	fPaveText->SetTextAlign(31); //right and bottom adjusted
	fPaveText->SetMargin(0);
	fPaveText->AddText("2.69 fb^{-1} (13 TeV)"); //use TLatex
	fPaveText->Draw("same");
}

void RStyle::PrintCMSPrivateWork(void)
{
	fPaveText = new TPaveText(0.7,0.87,0.88,0.97,"NB NDC");
	fPaveText->SetFillStyle(3000);
	fPaveText->SetLineColor(0);
	fPaveText->SetTextSize(0.03);
	fPaveText->SetTextFont(42);
	fPaveText->SetTextAlign(31); //right and bottom adjusted
	fPaveText->SetMargin(0);
	fPaveText->AddText("CMS Private Work");
	fPaveText->Draw("same");
}

void RStyle::PrintCMSPreliminary(void)
{
	fPaveText = new TPaveText(0.175,0.78,0.35,0.88,"NB NDC");
	fPaveText->SetFillStyle(3000);
	fPaveText->SetLineColor(0);
	fPaveText->SetTextSize(0.1);
	fPaveText->SetTextFont(62);
	fPaveText->AddText("CMS");
	fPaveText->Draw("same");
	fPaveText = new TPaveText(0.175,0.70,0.35,0.8,"NB NDC");
	fPaveText->SetFillStyle(3000);
	fPaveText->SetLineColor(0);
	fPaveText->SetTextSize(0.04);
	fPaveText->SetTextFont(42);
	fPaveText->AddText("Preliminary");
	fPaveText->Draw("same");
}

TLegend* RStyle::PrintLegend(TH1F* histo,Int_t nrows,const char* descript,const char* option,const char* corner)
{
	
	TString tdescript = descript;
	Double_t tlengthNDC = tdescript.Length()*0.02; //1 char(here Q) ~ 0.015 NDC
	if(fLegend==0)
	{
		if(strcmp(corner,fLeftDown) == 0) fLegend = new TLegend(0.1,0.1,0.1+tlengthNDC,0.1+0.06*nrows);
		if(strcmp(corner,fLeftUp) == 0) fLegend = new TLegend(0.1,0.9-0.06*nrows,0.1+tlengthNDC,0.9); 
		if(strcmp(corner,fRightDown) == 0) fLegend = new TLegend(0.9-tlengthNDC,0.10,0.9,0.1+0.06*nrows); 
		if(strcmp(corner,fRightUp) == 0) fLegend = new TLegend(0.9-tlengthNDC,0.9-0.06*nrows,0.9,0.9); //height of an entry ~ 0.06
  	fLegend->SetBorderSize(0);
  	fLegend->SetMargin(0.2); 
  	fLegend->SetFillStyle(3000);
  	fLegend->SetTextSize(0.03);
  }
	fLegend->AddEntry(histo,descript,option);
	fLegend->Draw();
	return fLegend;
}

TCanvas* RStyle::PrintCanvasTH1F(TH1F* histo,const char* title,const char* xaxistitle,const char* yaxistitle,const char* option)
{
	fCanvas = new TCanvas("Canvas",title,0,0,800,800);
	//fCanvas->SetTicks(1,1);
  histo->SetTitleOffset(1.1,"x");
  histo->SetTitleSize(0.04,"x");
  histo->SetLabelSize(0.04,"x");
  histo->SetTitleOffset(1.1,"y");
  histo->SetTitleSize(0.04,"y");
  histo->SetLabelOffset(0.01,"y");
  histo->SetLabelSize(0.04,"y");
  histo->GetXaxis()->SetTitle(xaxistitle);
  histo->GetYaxis()->SetTitle(yaxistitle);
  histo->SetStats(kFALSE);
  histo->GetXaxis()->SetTicks("+");
  histo->GetYaxis()->SetTicks("-");
  histo->SetLineColor(1);
  histo->SetLineWidth(2);
  histo->GetYaxis()->SetRangeUser(0,1.1*(histo->GetMaximum()+TMath::Sqrt(histo->GetMaximum())));
  histo->Draw(option);
  return fCanvas;
}
/*
void RStyle::SetGlobalStyle (void);
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
  gStyle->SetFrameBorderSize(10);
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(kBlack);
  gStyle->SetFrameLineStyle(0);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetLineWidth(3);
    
  //  For the Pad
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  //  Margins
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadRightMargin(0.05);

  //  For the histo:
  //gStyle->SetHistLineColor(kBlack);
  //gStyle->SetHistLineStyle(0);
  //gStyle->SetHistLineWidth(2);
  //gStyle->SetMarkerSize(1.2);
  //gStyle->SetEndErrorSize(4);
  //gStyle->SetHatchesLineWidth(1);

  //  For the statistics box:
  gStyle->SetOptStat(0);
  
  //  For the axis
 // gStyle->SetAxisColor(1,"XYZ");
  //gStyle->SetTickLength(0.03,"XYZ");
  //gStyle->SetNdivisions(510,"XYZ");
  //gStyle->SetPadTickX(1);
  //gStyle->SetPadTickY(1);
  //gStyle->SetStripDecimals(kFALSE);
  
  //  For the axis labels and titles
  //gStyle->SetTitleColor(1,"XYZ");
  //gStyle->SetLabelColor(1,"XYZ");
  //gStyle->SetLabelFont(42,"XYZ");
  //gStyle->SetLabelOffset(0.007,"XYZ");
  //gStyle->SetLabelSize(0.04,"XYZ");
  //gStyle->SetTitleFont(42,"XYZ");
  //gStyle->SetTitleSize(0.047,"XYZ");
  //gStyle->SetTitleXOffset(1.5);
  //gStyle->SetTitleYOffset(1.9);

  //  For the legend
  //gStyle->SetLegendBorderSize(0); 
}
*/
