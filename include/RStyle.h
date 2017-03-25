#ifndef ROOTPRIVATE_RSTYLE_H
#define ROOTPRIVATE_RSTYLE_H

#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TObject.h"

class RStyle
{
	private:
		static TCanvas	*fCanvas;
		static TPaveText *fPaveText;
		static TLegend *fLegend;
		const static char* fLeftDown;
		const static char* fLeftUp;
		const static char* fRightDown;
		const static char* fRightUp;
	public:
		RStyle(){};
		//Prints text "CMS Private Work" in the upper right corner on top of the frame
		static void PrintCMSPrivateWork (void);
		//Print CMS(bold) preliminary in the upper left corner
		static void PrintCMSPreliminary (void);
		//print invariant mass and cross section
		static void PrintCrossSection (void);
		//Prints Legend in desired corner, default: no border and white 
		TLegend* PrintLegend (TH1F* histo,Int_t nrows=1,const char* descript="",const char* option="l",const char* corner="RightUp");
		//Print Canvas with not Statistics Box, Default: Linecolor=black 
		TCanvas* PrintCanvasTH1F (TH1F* histo,const char* title="",const char* xaxistitle="",const char* yaxistitle="",const char* option="");
		static void SetGlobalStyle (void);
					
							
};

#endif
