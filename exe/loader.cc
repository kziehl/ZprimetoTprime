// Links different source files together

#include "TROOT.h"

void loader()
{
    gROOT->ProcessLine(".x plotutil.cc+");
    gROOT->ProcessLine(".x cplott.cc+");
    
}