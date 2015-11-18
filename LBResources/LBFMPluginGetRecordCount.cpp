//
//  LBFMPluginGetRecordCount.cpp
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
#include "LBFMPluginGetRecordCount.h"




#pragma mark Sync2API_GetRecordCount
FMX_PROC(fmx::errcode) Sync2API_GetRecordCount(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    
    string recNum = getObject()->getRecordCount();
    
    stringstream assign;
    
    assign << "Let ( $recordNumber=\"\" ; 1 )";
    
    resultText->Assign(assign.str().c_str());
    
    err = environment.Evaluate( *resultText,result);
    
    assign.str(std::string());
    
    assign << "Let ( $recordNumber=\"" << recNum << "\" ; 1 )";
    
    resultText->Assign(assign.str().c_str());
    
    err = environment.Evaluate( *resultText,result);
    
    return err;
}
