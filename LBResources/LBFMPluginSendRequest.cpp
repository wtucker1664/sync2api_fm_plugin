//
//  LBFMPluginSendRequest.cpp
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
#include "LBFMPluginSendRequest.h"




#pragma mark Sync2API_SendRequest
FMX_PROC(fmx::errcode) Sync2API_SendRequest(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
        getObject()->sendRequest();
        if(getObject()->hasErrors()){
            tempText->Assign("Error With Request");
            resultText->SetText(*tempText);
            
            
        }else{
            tempText->Assign("Request Sent");
            resultText->SetText(*tempText);
            
        }
    err = result.SetAsText( *resultText, result.GetLocale() );
    return err;
}
