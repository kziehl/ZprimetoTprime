#ifndef ROOTPRIVATE_RLOADER_H
#define ROOTPRIVATE_RLOADER_H

#include "TChain.h"

class RLoader
{
	private:
					TChain *fLoader;
	public:
					RLoader(){};
					TChain* GetTTbarFiles(void);
					TChain* GetZprimeFiles(void);
					TChain* GetQCDFiles(void);
};


#endif
