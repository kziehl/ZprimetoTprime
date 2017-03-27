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
		//prints CMS Private Work above the upper right corner of the frame
		static void PrintCMSPrivateWork (void);
		//prints CMS Preliminary in the top left corner below the frame 
		static void PrintCMSPreliminary (void);
		//prints the current Luminosity above the top left corner of the frame
		static void PrintCrossSection (void);
		//draws a legend in the desired corner.The options are RightUp,RightDown,LeftUp,LeftDown. By the first call of the function the number of rows and the longest entry must be known to initialize the legend. If now description is specified the title of the histogram is used by default.
		static void BuildLegend (TH1F* histo,const char* descript="",const char* option="l",const char* corner="RightUp",Int_t nrows=1);
		//still in progress
		TCanvas* PrintCanvasTH1F (TH1F* histo,const char* title="",const char* xaxistitle="",const char* yaxistitle="",const char* option="");
		//sets default style for Canvas,Pad,Frame,Legend,Axis. Not recommended if using RUtil::PrintRatioPlot.
		static void SetGlobalStyle (void);
					
							
};

extern RStyle *gRStyle;

#endif
