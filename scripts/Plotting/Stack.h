#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <exception>
#include <vector>

#include "TH1.h"
#include "TString.h"


class Stack {
public:
  Stack() {}
  Stack(const TString& name) : name_(name) {}
  ~Stack();

  Stack* clone(const TString& name) const;

  TH1* getSumHist(const TString& name) const {
    return static_cast<TH1*>( hists_.back()->Clone(name) );
  }
  double getYMax() const {
    return hists_.back()->GetBinContent( hists_.back()->GetMaximumBin() );
  }

  void add(const TH1* h);
  void scale(const double s);
  void setXRange(const double xmin, const double xmax);
  void setYRange(const double ymin, const double ymax);
  void setTitle(const TString& title);
  void draw(TString opt);


private:
  TString name_;
  std::vector<TH1*> hists_;
};


Stack::~Stack() {
  for(auto& h: hists_) {
    delete h;
  }
}


Stack* Stack::clone(const TString& name) const {
  Stack* copy = new Stack(name);
  for(auto& h: hists_) {
    TString tmp = name;
    tmp += copy->hists_.size();
    copy->hists_.push_back( static_cast<TH1*>( h->Clone(tmp) ) );
  }

  return copy;
}


void Stack::setXRange(const double xmin, const double xmax) {
  const double bmin = hists_.front()->GetXaxis()->FindBin(xmin);
  const double bmax = hists_.front()->GetXaxis()->FindBin(xmax);
  for(auto& h: hists_) {
    h->GetXaxis()->SetRange(bmin,bmax);
  }
}


void Stack::setYRange(const double ymin, const double ymax) {
  for(auto& h: hists_) {
    h->GetYaxis()->SetRangeUser(ymin,ymax);
  }
}


void Stack::add(const TH1* h) {
  if( hists_.size() > 0 ) {
    if( hists_.back()->GetNbinsX() != h->GetNbinsX() ) {
      std::cerr << "\n\nERROR in Stack: inconsistent binning" << std::endl;
      throw std::exception();
    }
  }

  TString name = name_;
  name += hists_.size();
  TH1* tmp = static_cast<TH1*>( h->Clone(name) );
  if( hists_.size() > 0 ) {
    tmp->Add( hists_.back() );
  }
  hists_.push_back( tmp );
}


void Stack::draw(TString opt) {
  opt.ToLower();
  const bool optContainsSame =  opt.Contains("same");
  for(std::vector<TH1*>::reverse_iterator rit = hists_.rbegin();
      rit != hists_.rend(); ++rit) {
    if( !optContainsSame && rit == hists_.rbegin() ) {
      (*rit)->Draw(opt);
      opt += "same";
    }
    (*rit)->Draw(opt);
  }
}


void Stack::scale(const double s) {
  for(auto& h: hists_) {
    h->Scale(s);
  }
}


void Stack::setTitle(const TString& title) {
  for(auto& h: hists_) {
    h->SetTitle( title );
  }
}

#endif
