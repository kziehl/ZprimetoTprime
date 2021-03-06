#include "TChain.h"

#include "../include/RLoader.h"

RLoader* gRLoader;
TChain* RLoader::fLoader{0};

TChain* RLoader::GetTTbarFiles(void)
{
	fLoader = new TChain("MVATree","Chain with TTBar files");
	fLoader->Add("/nfs/dust/cms/user/kziehl/processed_MC/ntuples_4_16/BKG_TTbar/MC*.root");
	return fLoader;
}

TChain* RLoader::GetZprimeFiles(void)
{
	fLoader = new TChain("MVATree","Chain with Zprime files");
	fLoader->Add("/nfs/dust/cms/user/kziehl/processed_MC/ntuples_4_16/Signal_Zprime/Zprime*.root");
	return fLoader;
}

TChain* RLoader::GetQCDFiles(void)
{
	fLoader = new TChain("MVATree","Chain with QCD files");
	fLoader->Add("/nfs/dust/cms/user/kziehl/processed_MC/ntuples_4_16/BKG_QCD/MC_QCD_Pt_*.root");
	return fLoader;
}


 

  
  
