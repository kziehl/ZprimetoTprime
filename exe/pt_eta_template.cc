#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "THStack.h"
#include "TText.h"
#include "TH2F.h"
#include "TObjArray.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TCollection.h"

#include "plotutil.h"


void SetBranchAddress (TTree *tree,std::vector < std::vector <Float_t> >& pt,std::vector < std::vector <Float_t> >& eta,std::vector <Int_t>& length);
void Init_Histo (std::vector <TH2F*>& hpteta , std::vector <TH2F*>& hAK8pteta, std::vector <TH2F*>& hdivide);
void Loop_Entries (TTree *tree,std::vector <TH2F*>& hpteta , std::vector <TH2F*>& hAK8pteta, std::vector <TH2F*>& hdivide,std::vector <Int_t>& length,std::vector < std::vector <Float_t> >& pt,std::vector < std::vector <Float_t> >& eta);




int main()
{
// Here u have to select your desired Files and perhaps add some additional Matrices for each Chain.
  
//initial TChain via qcd and ttbar, Zprime
//TChain *BKG_TTbar = BKG_TTbar_Loader();
//TChain *BKG_QCD = BKG_QCD_Loader();
TChain *Signal_Zprime = Signal_Zprime_Loader();

Signal_Zprime->LoadTree(0);
TFile *f = Signal_Zprime->GetFile();
TTree *tree = (TTree*)f->Get("MVATree");

// vector with pt and eta. This is a matrix. Each row contains a vector for the respective region and the sum of those.
std::vector < std::vector <Float_t> > pt(6,std::vector <Float_t>(10000)),eta(6,std::vector <Float_t>(10000));

//length of arrays
std::vector <Int_t> length_array_region(6,0);

//create histogram 
std::vector <TH2F*> hpteta(4,0);
std::vector <TH2F*> hAK8pteta(2,0);
std::vector <TH2F*> hdivide(4,0);

//********************************************************************************************
//Call functions and fill in the user defined quantities

SetBranchAddress(tree,pt,eta,length_array_region);
Init_Histo(hpteta,hAK8pteta,hdivide);
Loop_Entries(tree,hpteta,hAK8pteta,hdivide,length_array_region,pt,eta);




return 0;



}

/* 
 Assign the branches in Tree with default vectors. Also hand over a Container which contain the length of the corresponding variable. This is for all four regions: is_top_tagged(0),is_top_misstagged(1),no_top_tagged(2),no_top_misstagged(3). The number stands for the position in the vector. 4 is AK8_top_tag_candidtes and 5 is AK8_top_misstagged_candidates. This is only for one of TTBar,Zprime,QCD. You have to call it multiple times.
 */
void SetBranchAddress(TTree* tree,std::vector < std::vector <Float_t> >& pt,std::vector < std::vector <Float_t> >& eta,std::vector <Int_t>& length)
{
  //It is physically a top and the tagger recognized it
  tree->SetBranchAddress("tagged_top_pt",&((pt.at(0)).front()));
  tree->SetBranchAddress("tagged_top_eta",&((eta.at(0)).front()));
  tree->SetBranchAddress("N_tagged_top",&length.at(0));
  //It is physically a top but it was misstagged 
  tree->SetBranchAddress("misstagged_top_anti_pt",&((pt.at(1)).front()));
  tree->SetBranchAddress("misstagged_top_anti_eta",&((eta.at(1)).front()));
  tree->SetBranchAddress("N_misstagged_top_anti",&length.at(1));
  //It is no top but i was tagged as some
  tree->SetBranchAddress("misstagged_top_pt",&((pt.at(2)).front()));
  tree->SetBranchAddress("misstagged_top_eta",&((eta.at(2)).front()));
  tree->SetBranchAddress("N_misstagged_top",&length.at(2));
  //It is no top and the tagger recognized it
  tree->SetBranchAddress("tagged_top_anti_pt",&((pt.at(3)).front()));
  tree->SetBranchAddress("tagged_top_anti_eta",&((eta.at(3)).front()));
  tree->SetBranchAddress("N_tagged_top_anti",&length.at(3));
  // Sum of all physical tops
  tree->SetBranchAddress("AK8_top_tag_candidates_pt",&((pt.at(4)).front())); 
  tree->SetBranchAddress("AK8_top_tag_candidates_eta",&((eta.at(4)).front()));
  tree->SetBranchAddress("N_AK8_top_tag_candidates",&length.at(4));
  // Sum of non-physical tops
  tree->SetBranchAddress("AK8_top_misstagged_candidates_pt",&((pt.at(5)).front())); 
  tree->SetBranchAddress("AK8_top_misstagged_candidates_eta",&((eta.at(5)).front()));
  tree->SetBranchAddress("N_AK8_top_misstag_candidates",&length.at(5));
}

/* Initialize a Vector with the frame of the histograms. */
void Init_Histo (std::vector <TH2F*>& hpteta , std::vector <TH2F*>& hAK8pteta, std::vector <TH2F*>& hdivide)
{
  for (int i=0;i<hpteta.size();i++)
  {
    char number[10];
    std::sprintf(number,"%d",i+1);
    TString ending(number);
    TH2F* temp1 = new TH2F("hpteta_"+ending,"eta vs pt",50,-3,3,50,0,2000);
    TH2F* temp2 = new TH2F("hdivide_"+ending,"eta vs pt",50,-3,3,50,0,2000);
    hpteta.push_back(temp1);
    hdivide.push_back(temp2);
  }
  for (int it=0;it<hAK8pteta.size();it++)
  {
    char number[10];
    std::sprintf(number,"%d",it+1);
    TString ending(number);
    TH2F* temp = new TH2F("hAK8_"+ending,"eta vs pt",50,-3,3,50,0,2000);
    hAK8pteta.push_back(temp);
  }
}

/* iterate over all entries of the Tree and fill the respective histograms. Create Canvas and filles the histograms in subpathes */
void Loop_Entries (TTree *tree,std::vector <TH2F*>& hpteta , std::vector <TH2F*>& hAK8pteta, std::vector <TH2F*>& hdivide,std::vector <Int_t>& length,std::vector < std::vector <Float_t> >& pt,std::vector < std::vector <Float_t> >& eta)
{
  Long64_t nentries = tree->GetEntries();
  for (Long64_t i=0;i<nentries;i++)
  {
    tree->GetEntry(i);
    for (int it=0; it<length.size(); it++)
    {
      for (int z=0;z<length.at(it);z++)
      {
        if(pt[it][z]>0)
        {
          if (it<4) hpteta.at(it)->Fill(eta[it][z],pt[it][z]);
          if (it>=4) hAK8pteta.at(it)->Fill(eta[it][z],pt[it][z]);
        }
      }
    }
 

  if(i%10000==0)
    {
      std::cout << i << std::endl;
    }

    }
  
  hdivide.at(0)->Divide(hpteta.at(0),hAK8pteta.at(0),1,1,"B");
  hdivide.at(1)->Divide(hpteta.at(1),hAK8pteta.at(0),1,1,"B");
  hdivide.at(2)->Divide(hpteta.at(2),hAK8pteta.at(1),1,1,"B");
  hdivide.at(3)->Divide(hpteta.at(3),hAK8pteta.at(1),1,1,"B");
 
  TCanvas *cs = new TCanvas("cs","cs",10,10,1200,1000);
  cs->Divide(2,2);
  for (int i=0;i<hdivide.size();i++)
    {
      cs->cd(i);
      hdivide.at(i)->SetStats(kFALSE);
      hdivide.at(i)->GetXaxis()->SetTitle("#eta");
      hdivide.at(i)->GetYaxis()->SetTitle("p_{T}");
      hdivide.at(i)->SetTitleOffset(1.5,"y");
      hdivide.at(i)->Draw("colz");
    }
    
  cs->SaveAs("/afs/desy.de/user/k/kziehl/plots/Zprime/pt_eta/Zprime_2500_1500_all_pt_eta.pdf");  
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
