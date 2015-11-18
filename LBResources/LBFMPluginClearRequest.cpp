//
//  LBFMPluginClearRequest.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 18/05/2015.
//
//




#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"
#include <string>

#include <iostream>
#include <sstream>
#include <exception>
#include <sys/types.h>

#if FMX_WIN_TARGET
#include <wininet.h>
#include <process.h>
#define GRAPH "∂"
#else

#include <Carbon/Carbon.h>
#define GRAPH "¶"
#endif
#include "LBFMPluginClearRequest.h"




#pragma mark Sync2API_ClearRequest
FMX_PROC(fmx::errcode) Sync2API_ClearRequest(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    
    
    getObject()->clearRequest();
    
    
    return err;
}