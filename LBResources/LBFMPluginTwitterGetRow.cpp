//
//  LBFMPluginTwitterGetRow.cpp
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
#include "LBFMPluginTwitterGetRow.h"




#pragma mark Sync2API_TwitterGetRow
FMX_PROC(fmx::errcode) Sync2API_TwitterGetRow(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
    if(dataVect.Size() != 2) {
        resultText->Assign("ERR no record or property values.");
    } else {
        
        
        fmx::TextAutoPtr type;
        type->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        fmx::TextAutoPtr record;
        record->SetText( dataVect.AtAsText(1), 0, dataVect.AtAsText(1).GetSize() );
        
        string recNum = GetTextAsString(*record);
        int numb;
        istringstream ( recNum ) >> numb;
        
        if(GetTextAsString(*type) == "Simple"){
            
            string prop = getObject()->getProperty(numb,"text");
            
           
            string assign = "Let ( $text=\"" + prop + "\" ; 1 )";

            cout << assign.c_str() << endl;
            resultText->Assign(assign.c_str(),fmx::Text::kEncoding_UTF8);
            
            err = environment.Evaluate( *resultText,result);
            
        }else if(GetTextAsString(*type) == "Complex"){
            map<string,string> properties;
            
            map<string,string>::iterator propInnerIt;
            
            properties = getObject()->getAllProperties(numb);
            if(properties.size() > 0){
                
                if(twitterRowPropertiesClear.size() > 0){
                    map<string,string>::iterator propClearInnerIt;
                    for( propClearInnerIt=twitterRowPropertiesClear.begin(); propClearInnerIt != twitterRowPropertiesClear.end(); propClearInnerIt++){
                        
                        
                        stringstream assign;
                        
                        assign << "Let ( $" << (*propClearInnerIt).first << "=\"""\" ; 1 )";
                        
                        resultText->Assign(assign.str().c_str());
                        cout << assign.str() << endl;
                        assign.clear();
                       
                        err = environment.Evaluate( *resultText,result);
                        
                    }
                    twitterRowPropertiesClear.clear();
                }
                
                for( propInnerIt=properties.begin(); propInnerIt != properties.end(); propInnerIt++){
                    
                    twitterRowPropertiesClear.insert(make_pair((*propInnerIt).first, (*propInnerIt).second));
                    stringstream assign;
                    
                    assign << "Let ( $" << (*propInnerIt).first << "=\"" << (*propInnerIt).second << "\" ; 1 )";
                    
                    resultText->Assign(assign.str().c_str(),fmx::Text::kEncoding_UTF8);
                    cout << assign.str() << endl;
                    assign.clear();
                    err = environment.Evaluate( *resultText,result);
                    
                }
                
                
            }
        }else{
            string doneText = "No Output type specified";
            
            tempText->Assign(doneText.c_str());
            resultText->SetText(*tempText);
            err = result.SetAsText( *resultText, result.GetLocale() );
        }
            
        
    }
        
        return err;
    }