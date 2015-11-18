//
//  LBFMPluginSetModule.cpp
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
#include "LBFMPluginSetModule.h"




#pragma mark Sync2API_SetModule
FMX_PROC(fmx::errcode) Sync2API_SetModule(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
    if(dataVect.Size() != 1) {
        resultText->Assign("ERR no Module specified.");
    } else {
        // get url
        fmx::TextAutoPtr module;
        module->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        
        
        
        getObject()->setModule(GetTextAsString(*module));
        
        
        
        tempText->Assign("Module Set");
        resultText->SetText(*tempText);
        
    }
    err = result.SetAsText( *resultText, result.GetLocale() );
    return err;
}
