#ifndef ROOTPRIVATE_RLOADER_H
#define ROOTPRIVATE_RLOADER_H

#include "TChain.h"

class RLoader
{
	private:
					static TChain *fLoader;
	public:
					RLoader(){};
					static TChain* GetTTbarFiles(void);
					static TChain* GetZprimeFiles(void);
					static TChain* GetQCDFiles(void);
};

extern RLoader* gRLoader;

#endif
