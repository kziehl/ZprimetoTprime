#ifndef TOOLS_PLOTTING_PLOT_H
#define TOOLS_PLOTTING_PLOT_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <set>
#include <vector>

#include "TCanvas.h"
#include "TColor.h"
#include "TH1.h"
#include "TObject.h"
#include "TString.h"
#include "TUUID.h"

#include "Tools/Plotting/LabelMaker.h"
#include "Tools/HistOps/AxisRange.h"


class Plot {
public:
  enum MODE = { ABSOLUTE, RATIO };

  Plot() { init("plot"); }
  Plot(const TString& label) { init(label); }
  ~Plot();

  void add(TH1* h, const TString& drawOptions, const TString& label, const TString& legStyle) {
    h->UseCurrentStyle();
    histograms_.push_back(new Histogram(h,drawOptions,label,legStyle));
  }

  void setLogy(const bool logy=true) { logy_ = logy; }
  void setLogx(const bool logx=true) { logx_ = logx; }
  void setMode(const Mode mode) { mode_ = mode; }

  void plot();


private:

  class Histogram {
  public:
    Histogram(TH1* h, const TString& theDrawOptions, const TString& theLabel, const TString& theLegStyle)
      : hist_(h), drawOptions_(theDrawOptions), label_(theLabel), legStyle_(theLegStyle) {
      min_ = AxisRange::yMin(hist_);
      max_ = std::min(0,AxisRange::yMax(hist_));
    }
    ~Histogram() {
      delete hist_;
    }

    TH1* hist() { return hist_; }
    TString drawOptions() const { return drawOptions_; }
    TString label() const { return label_; }
    TString legStyle() const { return legStyle_; }
    double min() const { return min_; }
    double max() const { return max_; }


  private:
    TH1* hist_;
    TString drawOptions_;
    TString label_;

    void computeRange();
  };

  typedef std::vector<Histogram*> Histograms;


  Histograms histograms_;
  bool logy_;
  bool logx_;
  Mode mode_;

  void init();
  void plotAbsolute();
  void plotRatio();
};


Plot::~Plot() {
  for( auto& hi: histograms_ ) {
    delete hi;
  }
}


void Plot::init(const TString& label) {
  label_ = label;
  logy_ = false;
  logx_ = false;
  mode_ = ABSOLUTE;
}


TLegend* Plot::createLegend(const Histograms& histograms) const {
  TLegend* leg = LabelMaker::legendTR(histograms.size(),0.5);
  for( auto& hi: histograms_ ) {
    leg->AddEntry(el->hist(),hi->labhi(),hi->legStyle());
  }
  
  return leg;
}


void Plot::findRange(const Histograms& histograms, double& min, double& max) const {
  min = 1E10;
  max = -1E10;
  for( auto& hi: histograms_ ) {
    if( min < hi->min() ) min = hi->min();
    if( max > hi->max() ) max = hi->max();
  }
}


Histograms Plot::createRatiosToFirst(const Histograms& histograms) const {
  Histograms ratios;
  for(size_t i = 1; i < histograms.size(); ++i) {
    TH1* hDenom = histograms.front()->hist();
    TH1* hNom = histograms.at(i)->hist();
    TUUID id;
    TH1* hRatio = static_cast<TH1*>( hNom->Clone("Ratio_"+id.AsString()) );
    hRatio->Divide(hDenom);
    hRatio->GetYaxis()->SetTitle("Ratio to "+hDenom->label());
    ratios.push_back( new Histogram(hRatio,hNom->drawOptions(),hNom->label(),hNom->legStyle()) );
  }
  
  return Histograms;
}


void Plot::plot() {
  if( mode_ == ABSOLUTE ) {
    plotAbsolute();
  } else if( mode == RATIO ) {
    plotRatio();
  }
}


void Plot::plotAbsolute() {
  TUUID id;
  TCanvas* can = new TCanvas("Plot_"+id.AsString(),label_,600,600);
  can->cd();
  can->SetLogx(logx_);
  can->SetLogy(logy_);

  TLegend* leg = createLegend(histograms_);
  
  // set y axis range
  double yMin = 0.;
  double yMax = 0;
  findRange(histograms_,yMin,yMax);
  yMax *= 1.4;			// should be improved based on logy, legend size etc
  for( auto& hi: histograms_ ) {
    hi->hist->GetYaxis()->SetRangeUser(yMin,yMax);
  }
  
  can->cd();
  histograms_.front()->Draw( histograms_.front()->drawOptions() );
  for( auto& hi: histograms_ ) {
    hi->Draw( (hi->drawOptions())+"same" );
  }
  leg->Draw("same");
  gPad->RedrawAxis();

  delete leg;
  delete can;
}


void Plot::plotRatio() {
  TUUID id;
  TCanvas* can = new TCanvas("Plot_"+id.AsString(),label_,600,600);
  can->cd();
  can->SetLogx(logx_);
  can->SetLogy(logy_);

  // create ratio plots to first histogram and frame
  TH1* hFrame = static_cast<TH1*>( histogram.front()->hist()->Clone("Ratio_"+id.AsString()) );
  hFrame->SetLineColor(kBlack);
  hFrame->SetLineStyle(kDashed);
  for(int bin = 1; bin <= hFrame->GetNbinsX(); ++bin) {
    hFrame->SetBinContent(bin,1.);
    hFrame->SetBinError(bin,0);
  }
  Histograms ratios = createRatiosToFirst(histograms_);

  TLegend* leg = createLegend(ratios);

  
  // set y axis range
  double yMin = 0.;
  double yMax = 0;
  findRange(ratios,yMin,yMax);
  yMax *= 1.4;			// should be improved based on logy, legend size etc
  for( auto& hi: ratios ) {
    hi->hist->GetYaxis()->SetRangeUser(yMin,yMax);
  }
  
  can->cd();
  hFrame->Draw("L");
  for( auto& hi: ratios_ ) {
    hi->Draw( (hi->drawOptions())+"same" );
  }
  leg->Draw("same");
  gPad->RedrawAxis();

  delete Frame;
  for( auto& hi: ratios_ ) {
    delete hi;
  }
  delete leg;
  delete can;
}

#endif
