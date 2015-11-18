//
//  LBFMPluginTwitterDelete.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 19/06/2015.
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
#include "LBFMPluginTwitterDelete.h"




#pragma mark Sync2API_TwitterDelete
FMX_PROC(fmx::errcode) Sync2API_TwitterDelete(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
    fmx::TextAutoPtr	resultText;
    fmx::TextAutoPtr	tempText;
    
    if(dataVect.Size() != 1) {
        resultText->Assign("ERR no Property specified.");
    } else {
        // get url
        fmx::TextAutoPtr txt;
        txt->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        getObject()->setModule("twitter");
        getObject()->setMethod("DeleteTweet");
        
        getObject()->setProperty("id",GetTextAsString(*txt));
        
        getObject()->sendRequest();
        
        if(!getObject()->hasErrors()){
            map<string,string> properties;
            
            map<string,string>::iterator propInnerIt;
            properties = getObject()->getAllProperties(0);
            if(properties.size() > 0){
                
                if(twitterDeletePropertiesClear.size() > 0){
                    map<string,string>::iterator propClearInnerIt;
                    for( propClearInnerIt=twitterDeletePropertiesClear.begin(); propClearInnerIt != twitterDeletePropertiesClear.end(); propClearInnerIt++){
                        
                        
                        stringstream assign;
                        
                        assign << "Let ( $" << (*propClearInnerIt).first << "=\"""\" ; 1 )";
                        
                        resultText->Assign(assign.str().c_str());
                        cout << assign.str() << endl;
                        assign.clear();
                        
                        err = environment.Evaluate( *resultText,result);
                        
                        }
                        twitterDeletePropertiesClear.clear();
                        }
                        
                        for( propInnerIt=properties.begin(); propInnerIt != properties.end(); propInnerIt++){
                            
                            twitterDeletePropertiesClear.insert(make_pair((*propInnerIt).first, (*propInnerIt).second));
                            stringstream assign;
                            
                            assign << "Let ( $" << (*propInnerIt).first << "=\"" << (*propInnerIt).second << "\" ; 1 )";
                            
                            resultText->Assign(assign.str().c_str());
                            cout << assign.str() << endl;
                            assign.clear();
                            err = environment.Evaluate( *resultText,result);
                            
                        }
                        
                        
                        }
                        
                        }
                        
                        
                        string doneText = "Tweet Deleted OK";
                        
                        tempText->Assign(doneText.c_str());
                        resultText->SetText(*tempText);
                        
                        }
                        err = result.SetAsText( *resultText, result.GetLocale() );
                        return err;
}

