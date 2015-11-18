//
//  LBFMPluginGetProperty.cpp
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
#include "LBFMPluginGetProperty.h"




#pragma mark Sync2API_GetProperty
FMX_PROC(fmx::errcode) Sync2API_GetProperty(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    
    if(dataVect.Size() != 2) {
        resultText->Assign("ERR no record or property values.");
    } else {
        
        fmx::TextAutoPtr record;
        record->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        fmx::TextAutoPtr property;
        property->SetText( dataVect.AtAsText(1), 0, dataVect.AtAsText(1).GetSize() );
    
        
        
        string recNum = GetTextAsString(*record);
        int numb;
        istringstream ( recNum ) >> numb;
        string prop = getObject()->getProperty(numb, GetTextAsString(*property));
    
        stringstream assign;
    
        assign << "Let ( $" << GetTextAsString(*property) << "=\"" << prop << "\" ; 1 )";
    
        resultText->Assign(assign.str().c_str(),fmx::Text::kEncoding_UTF8);
    
        err = environment.Evaluate( *resultText,result);
    }
        
    return err;
}