//
//  LBFMPluginGetRecordVarNames.cpp
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
#include "LBFMPluginGetRecordVarNames.h"




#pragma mark Sync2API_GetRecordVarNames
FMX_PROC(fmx::errcode) Sync2API_GetRecordVarNames(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    stringstream varNames;
    if(dataVect.Size() == 1) {
        fmx::TextAutoPtr record;
        record->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        
        string recNum = GetTextAsString(*record);
        int numb;
        istringstream ( recNum ) >> numb;
        varNames << getObject()->getRecordVarNames(numb).str();
    }else{
        
        varNames << getObject()->getRecordVarNames().str();
    }
        tempText->Assign(varNames.str().c_str());
        resultText->SetText(*tempText);
    err = result.SetAsText( *resultText, result.GetLocale() );
    return err;
}