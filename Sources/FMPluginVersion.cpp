//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMPluginVersion.cpp - Default external function for returning plug-in version
//
//  Version 3.1, Copyright ©2002-2012 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky & HOnza Koudelka
//
////////////////////////////////////////////////////////////////////////////////
//
//  The latest version of 24U Plug-In Template is available for download from:
//
//  http://www.24uSoftware.com/PlugInTemplate 
//
////////////////////////////////////////////////////////////////////////////////
//
//  24U Sample Code - Terms of use
//
//  Under the terms of the 24U Software License Agreement, 24U s.r.o. grants
//  you a non-exclusive royalty-free Developer License (3.2) to use 24U Plug-In
//  Template solely to compile plug-ins for use with FileMaker products.
//
//  Redistribution of 24U Sample Code in the source form, as part of
//  an open-source plug-in project is permitted provided that the following
//  conditions are met:
//
//  * Redistributions of source code must retain the copyright notice, the terms
//    of use, and the "24U Software License Agreement" document.
//
//  * We require that you make it clear in the source wherever modified that the
//    code was descended from 24U Sample Code, but that you've made changes.
//
//  See the "License.txt" and "24U Software License Agreement.pdf" files
//  for detailed terms of use and licensing conditions.
//
////////////////////////////////////////////////////////////////////////

//
//  This source file contains code for the plug-in's Version function. Since
//  it is recommended for every FileMaker Plug-in to have a function to check
//  the plug-in's version, we have written a simple version function for you.
//  When en empty string is passed to this function, it simply returns the
//  version of this plug-in, as defined in the FMTConfig.h header file.
//
//  As a bonus for you, if you pass the string "platform" as a parameter to this
//  function, it will respond with the information about which code is being
//  used, whether it is Mac OS X code, or Windows code. If you pass the string
//  "long" to this function, a long version string consisting of the plug-in's
//  name and version is returned.
//
////////////////////////////////////////////////////////////////////////////////


#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"
#include "LBFMPluginHandler.h"

#define BUFFER_SIZE 256

#pragma mark Sync2API_Version
FMX_PROC(fmx::errcode) Sync2API_Version(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result)
{
    fmx::errcode        err = 0;
    FMX_Unichar         pluginVersion[BUFFER_SIZE];
    fmx::TextAutoPtr    tempText;
    fmx::TextAutoPtr    resultText;
    
    if( dataVect.Size() > 0 )
    {
        //We have at least one parameter. Read it and return correct information.
        
        const fmx::Text& parameter1 = dataVect.AtAsText(0);
        
        if( tempText->Assign(""), *tempText == parameter1 )
        {
            //The parameter is an empty string. Return default, "short", version.

            ReadString( pluginVersion, sizeof(pluginVersion)/sizeof(FMX_Unichar), PLUGIN_VERSION_ID );
            resultText->AssignUnicode(pluginVersion);
        }
        else if( tempText->Assign("long"), *tempText == parameter1 )
        {
            //The parameter is "long". Return longer version.
            
            fmx::TextAutoPtr tempText;
            FMX_Unichar      pluginName[BUFFER_SIZE];
            
            ReadString(pluginName, sizeof(pluginName)/sizeof(FMX_Unichar), 
                       PLUGIN_NAME_ID);
            
            resultText->AssignUnicode(pluginName);
            tempText->Assign(" ");
            resultText->AppendText(*tempText);
            tempText->Assign(PLUGIN_VERSION);
            resultText->AppendText(*tempText);
        }
        else if( tempText->Assign("platform"), *tempText == parameter1 )
        {
            //The parameter is "platform", return. Return platform information.
            
            #if FMX_MAC_TARGET
                resultText->Assign("Mac OS X");
            #else
                resultText->Assign("Windows");
            #endif
        }
        else if( tempText->Assign("short"), *tempText == parameter1 )
        {
            //The parameter is "short". Return short (default) version.

            ReadString( pluginVersion, sizeof(pluginVersion)/sizeof(FMX_Unichar), PLUGIN_VERSION_ID );
            resultText->AssignUnicode(pluginVersion);
        }
        else if( tempText->Assign("autoupdate"), *tempText == parameter1 )
        {
            //The parameter is "autoupdate". Return version in format suitable for autoupdate feature.
            
            char auChars[9];
            sprintf(auChars, "%02d%02d%02d%02d", 
                    PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, 
                    PLUGIN_VERSION_BUILD, PLUGIN_VERSION_DEV);
            resultText->Assign(auChars);
        }else if(tempText->Assign("LBDebug"), *tempText == parameter1 ){
            LBJSONRenderFM *j = getObject();
            j->setLBDebug(true);
        }else if(tempText->Assign("LBDebugOff"), *tempText == parameter1 ){
            LBJSONRenderFM *j = getObject();
            j->setLBDebug(false);
        }else if(tempText->Assign("debug"), *tempText == parameter1 ){
            LBJSONRenderFM *j = getObject();
            j->setDebug(true);
        }else if(tempText->Assign("debugOff"), *tempText == parameter1 ){
            LBJSONRenderFM *j = getObject();
            j->setDebug(false);
        }else if(tempText->Assign("LBDebugAll"), *tempText == parameter1 ){
            LBJSONRenderFM *j = getObject();
            j->setDebug(true);
            j->setLBDebug(true);
        }else if(tempText->Assign("LBDebugAllOff"), *tempText == parameter1 ){
            LBJSONRenderFM *j = getObject();
            j->setDebug(false);
            j->setLBDebug(false);
        }

        err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
    }
    else 
    {
        //The function has no parameter. Return short (default) version in the default locale.
        
        fmx::LocaleAutoPtr locale;

        ReadString( pluginVersion, sizeof(pluginVersion)/sizeof(FMX_Unichar), PLUGIN_VERSION_ID );
        resultText->AssignUnicode(pluginVersion);
        
        err = result.SetAsText( *resultText, *locale );
    }

    return err;
}
