//
//  LBFMPluginSetProperty.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 19/05/2015.
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
#include "LBFMPluginSetProperty.h"




#pragma mark Sync2API_SetProperty
FMX_PROC(fmx::errcode) Sync2API_SetProperty(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
    if(dataVect.Size() != 2) {
        resultText->Assign("ERR no Property specified.");
    } else {
        // get url
        fmx::TextAutoPtr pName;
        pName->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        fmx::TextAutoPtr pValue;
        pValue->SetText( dataVect.AtAsText(1), 0, dataVect.AtAsText(1).GetSize() );
        
        
        getObject()->setProperty(GetTextAsString(*pName),GetTextAsString(*pValue));
        
        
        string doneText = "Property "+GetTextAsString(*pName)+" Set";
        tempText->Assign(doneText.c_str());
        resultText->SetText(*tempText);
        
    }
    err = result.SetAsText( *resultText, result.GetLocale() );
    return err;
}
