#ifndef ROOTPRIVATE_RSTYLE_H
#define ROOTPRIVATE_RSTYLE_H

#include "TCanvas.h"
#include "TLegend.h"
#include "TText.h"
#include "TLatex.h"
#include "TObject.h"

class RStyle
{
	private:
		static TCanvas	*fCanvas;
		static TText *fText;
		static TLatex *fLatex;
		static TLegend *fLegend;
		const static char* fLeftDown;
		const static char* fLeftUp;
		const static char* fRightDown;
		const static char* fRightUp;
	public:
		RStyle(){};
		static void PrintCMSPrivateWork (void);
		static void PrintCMSPreliminary (void);
		static void PrintCrossSection (void);
		static void BuildLegend (TH1F* histo,const char* descript="",const char* option="l",const char* corner="RightUp",Int_t nrows=1);
		TCanvas* PrintCanvasTH1F (TH1F* histo,const char* title="",const char* xaxistitle="",const char* yaxistitle="",const char* option="");
		static void SetGlobalStyle (void);
					
							
};

extern RStyle *gRStyle;

#endif
