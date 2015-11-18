//
//  LBFMPluginTwitterPost.cpp
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
#include "LBFMPluginTwitterPost.h"




#pragma mark Sync2API_TwitterPost
FMX_PROC(fmx::errcode) Sync2API_TwitterPost(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
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
        getObject()->setMethod("CreateTweet");
        string status =GetTextAsString(*txt);
        if(status.length() > 140){
            tempText->Assign("Tweet text is greater than 140 characters and can not be sent");
            resultText->SetText(*tempText);
        }else{
        getObject()->setProperty("status",status);
        
        
        
        getObject()->sendRequest();
        
        if(!getObject()->hasErrors()){
            map<string,string> properties;
            
            map<string,string>::iterator propInnerIt;
            properties = getObject()->getAllProperties(0);
            if(properties.size() > 0){
                
                if(twitterPostPropertiesClear.size() > 0){
                    map<string,string>::iterator propClearInnerIt;
                    for( propClearInnerIt=twitterPostPropertiesClear.begin(); propClearInnerIt != twitterPostPropertiesClear.end(); propClearInnerIt++){
                        
                        
                        stringstream assign;
                        
                        assign << "Let ( $" << (*propClearInnerIt).first << "=\"""\" ; 1 )";
                        
                        resultText->Assign(assign.str().c_str());
                        cout << assign.str() << endl;
                        assign.clear();
                        
                        err = environment.Evaluate( *resultText,result);
                        
                        }
                        twitterPostPropertiesClear.clear();
                        }
                        
                        for( propInnerIt=properties.begin(); propInnerIt != properties.end(); propInnerIt++){
                            
                            twitterPostPropertiesClear.insert(make_pair((*propInnerIt).first, (*propInnerIt).second));
                            stringstream assign;
                            
                            assign << "Let ( $" << (*propInnerIt).first << "=\"" << (*propInnerIt).second << "\" ; 1 )";
                            
                            resultText->Assign(assign.str().c_str());
                            cout << assign.str() << endl;
                            assign.clear();
                            err = environment.Evaluate( *resultText,result);
                            
                        }
                        
                        
                        }
            
        }
        
        
        string doneText = "Tweet Sent OK";
        
        tempText->Assign(doneText.c_str());
        resultText->SetText(*tempText);
        
    }
    }
    err = result.SetAsText( *resultText, result.GetLocale() );
    return err;
}
