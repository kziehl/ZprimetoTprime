void test()
{
	//no stat box
	gStyle->SetOptStat(0);
	// load file
	TFile *file = new TFile("/home/kevin/Desktop/file/analysis.root");
	//create histograms
	TH1F* httm = dynamic_cast<TH1F*>(file->Get("QCD_TTM_Zprime_M"));
	TH1F* hfirst = dynamic_cast<TH1F*>(file->Get("QCD_Signal_Topfirst_Zprime_M"));
	TH1F* httbar = dynamic_cast<TH1F*>(file->Get("TTbar_Signal_Topfirst_Zprime_M"));
	TH1F* hzprime = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_Signal_Topfirst_Zprime_M"));
	TH1F* hzprimebkg = dynamic_cast<TH1F*>(file->Get("Zprime_2500_1500_TTM_Zprime_M"));
	TH1F* hsum_data = new TH1F("sum_data","sum_data",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_pred = new TH1F("sum_pred","sum_pred",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_bkg = new TH1F("sum_bkg","sum_bkg",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	TH1F* hsum_pred_zprime = new TH1F("sum_pred_zprime","sum_pred",httm->GetSize()-2,httm->GetXaxis()->GetXmin(),httm->GetXaxis()->GetXmax());
	//adding histograms
	hsum_data->Add(hfirst,httbar); hsum_data->Add(hzprime);
	hsum_pred->Add(httm,httbar); hsum_pred->Add(hzprimebkg);
	hsum_pred_zprime->Add(httm,httbar); hsum_pred_zprime->Add(hzprime);
	hsum_bkg->Add(httm,httbar);
		// canvas
	TCanvas *c1 = new TCanvas("c1","c1",800,800);
	c1->SetTicks(0,0);
	//ratio plot
	TRatioPlot* Ratio = new TRatioPlot(hsum_data,hsum_pred,"divsym");
	// style for sum_data
	hsum_data->SetTitle("");
	hsum_data->SetMarkerStyle(8);
	hsum_data->SetMarkerSize(1.1);
	hsum_data->SetLineColor(1);
	hsum_data->Scale(37.82);
	//hsum_data->GetXaxis()->SetTitle("m_{Z'} in GeV");
	hsum_data->GetYaxis()->SetTitle("Events");
	//style for sum_pred
	hsum_pred->SetLineWidth(2);
	//hsum_pred->SetFillStyle(3000);
	hsum_pred->SetLineColor(1);
	hsum_pred->SetFillColor(2);
	hsum_pred->Scale(37.82);
	//Ratio Style
	Ratio->SetSeparationMargin(0);
	Ratio->SetH1DrawOpt("pe");
	Ratio->SetH2DrawOpt("histe");
	Ratio->Draw("fhideup same");
	
	
}
