#ifndef ROOTPRIVATE_RUTIL_H
#define ROOTPRIVATE_RUTIL_H

#include <vector>
#include <iostream>

#include "TH1.h"
#include "TH1F.h"
#include "TChain.h"
#include "TRatioPlot.h"


class RUtil
{
	private:
	public:
		RUtil(){};
		/* Return highest bin value of a set of histograms. Important for drawing options. */
		static Double_t GetYMaxOfList (const std::vector<TH1F*>& histo);
		/*return the max value of a variable stored in an array with a certain length. Todo: Loop over all events is not practical */
		static Double_t GetMaxValOfVar (TChain* chain, const char* variable, const char* length);
		/* create a ratio plot with h1/h2. The ratio is evaluated with the option "divsym". histo1 will be drawn in blue and histo2 in red. */
	 	static void PrintRatioPlot (TH1F* histo1,TH1F* histo2,const char* titleyaxis="",const char* titlexaxis="", const char* titleratioy="");
	 	static TH1F* DrawStackPlot(TH1F* histo1, TH1F* histo2,TH1F* histo3=0);
	 	
			
					
};

extern RUtil *gRUtil;

#endif
