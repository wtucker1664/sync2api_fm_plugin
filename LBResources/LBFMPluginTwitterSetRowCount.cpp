//
//  LBFMPluginTwitterSetRowCount.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 22/05/2015.
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
#include "LBFMPluginTwitterSetRowCount.h"




#pragma mark Sync2API_TwitterSetRowCount
FMX_PROC(fmx::errcode) Sync2API_TwitterSetRowCount(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
    if(dataVect.Size() == 1) {

        // get url
        fmx::TextAutoPtr qty;
        qty->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );

            getObject()->setModule("twitter");
            getObject()->setMethod("UserTweets");
            getObject()->setProperty("count",GetTextAsString(*qty) );
        
        string doneText = "Twitter Row Count Set as " + GetTextAsString(*qty);
        tempText->Assign(doneText.c_str());
        resultText->SetText(*tempText);
        
    }else{
        getObject()->setModule("twitter");
        getObject()->setMethod("UserTweets");
        getObject()->setProperty("count","1" );
        
        string doneText = "Twitter Row Count Set as 1";
        tempText->Assign(doneText.c_str());
        resultText->SetText(*tempText);
    }
    err = result.SetAsText( *resultText, result.GetLocale());
    return err;
}

