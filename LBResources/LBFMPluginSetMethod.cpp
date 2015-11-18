//
//  LBFMPluginSetMethod.cpp
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
#include "LBFMPluginSetMethod.h"




#pragma mark Sync2API_SetMethod
FMX_PROC(fmx::errcode) Sync2API_SetMethod(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
    if(dataVect.Size() != 1) {
        resultText->Assign("ERR no Module specified.");
    } else {
        // get url
        fmx::TextAutoPtr method;
        method->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        
        
     
        getObject()->setMethod(GetTextAsString(*method));
        
        
        
        tempText->Assign("Method Set");
        resultText->SetText(*tempText);
        
    }
    err = result.SetAsText( *resultText, result.GetLocale());
    return err;
}
