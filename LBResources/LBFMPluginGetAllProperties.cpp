//
//  LBFMPluginGetAllProperties.cpp
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
#include "LBFMPluginGetAllProperties.h"




#pragma mark Sync2API_GetAllProperties
FMX_PROC(fmx::errcode) Sync2API_GetAllProperties(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    
    map<string,string> properties;
    
    map<string,string>::iterator propInnerIt;
    
    if(dataVect.Size() == 1) {
            fmx::TextAutoPtr record;
            record->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        
            string recNum = GetTextAsString(*record);
            int numb;
            istringstream ( recNum ) >> numb;
            
            properties = getObject()->getAllProperties(numb);
        
       
        
        
        
        
    }
    if(properties.size() > 0){
        
        if(propertiesClear.size() > 0){
            map<string,string>::iterator propClearInnerIt;
            for( propClearInnerIt=propertiesClear.begin(); propClearInnerIt != propertiesClear.end(); propClearInnerIt++){
                
                
                stringstream assign;
                
                assign << "Let ( $" << (*propClearInnerIt).first << "=\"""\" ; 1 )";
                cout << "Unsetting " << assign.str() << endl;
                
                resultText->Assign(assign.str().c_str(),fmx::Text::kEncoding_UTF8);
                
                assign.clear();
                
                err = environment.Evaluate( *resultText,result);
                
                }
                propertiesClear.clear();
        }
        
        for( propInnerIt=properties.begin(); propInnerIt != properties.end(); propInnerIt++){
            
            propertiesClear.insert(make_pair((*propInnerIt).first, (*propInnerIt).second));
            stringstream assign;
            string s = (*propInnerIt).second;
            std::replace( s.begin(), s.end(), '"', '\'');
            assign << "Let ( $" << (*propInnerIt).first << "=\"" << s << "\" ; 1 )";
            cout << "Setting " << assign.str() << endl;
            resultText->Assign(assign.str().c_str(),fmx::Text::kEncoding_UTF8);
            
            assign.clear();
            err = environment.Evaluate( *resultText,result);
            
        }
        
            
    }
    return err;
}