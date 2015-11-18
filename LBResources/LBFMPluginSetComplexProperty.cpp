//
//  LBFMPluginSetComplexProperty.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 20/05/2015.
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
#include "LBFMPluginSetComplexProperty.h"




#pragma mark Sync2API_SetComplexProperty
FMX_PROC(fmx::errcode) Sync2API_SetComplexProperty(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    stringstream varNames;
    if(dataVect.Size() == 1) {
        fmx::TextAutoPtr property;
        property->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        getObject()->setComplexProperty(GetTextAsString(*property));
        
        }else if(dataVect.Size() == 2){
            fmx::TextAutoPtr property;
            property->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
            
            fmx::TextAutoPtr value;
            value->SetText( dataVect.AtAsText(1), 0, dataVect.AtAsText(1).GetSize() );
            string recNum = GetTextAsString(*value);
            int numb;
            istringstream ( recNum ) >> numb;
            
            getObject()->setComplexProperty(GetTextAsString(*property), numb);
            
        }
        tempText->Assign(varNames.str().c_str());
        resultText->SetText(*tempText);
        err = result.SetAsText( *resultText, result.GetLocale() );
        
        return err;

}