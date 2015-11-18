//
//  FMPluginLicence.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 13/07/2014.
//
//
//////////////////////////////////////////////////////////////////////////////////////
//
//  FMPluginVersion.cpp - Default external function for returning plug-in version
//
//  Version 2.2, Copyright ©2002-2006 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky & HOnza Koudelka
//
////////////////////////////////////////////////////////////////////////////////
//
//  The latest version of 24U FM Template is available for download from:
//
//  http://24uSoftware.com/FMTemplate  or  http://www.NewMillennium.com/
//
////////////////////////////////////////////////////////////////////////////////
//
//  24U Sample Code - Terms of use
//
//  You may incorporate this sample code into your products without
//  restriction, though the code has been provided "AS IS" and the
//  responsibility for its operation is 100% yours.
//
//  You are not however permitted to redistribute the source
//  as "24U Sample Code" after having made changes.
//
//  If you are going to redistribute the source with references to
//  24U Software, we require that you make it clear in the source that
//  the code was descended from 24U Sample Code, but that you've made changes.
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
#include "FMPluginLicence.h"




#pragma mark Sync2API_Licence
FMX_PROC(fmx::errcode) Sync2API_Licence(short funcId, const fmx::ExprEnv& environment, const fmx::DataVect& dataVect, fmx::Data& result) {
#pragma unused(funcId,environment,result)
    fmx::errcode        err = 0;
	fmx::TextAutoPtr	resultText;
	fmx::TextAutoPtr	tempText;
	
	if(dataVect.Size() != 2) {
        resultText->Assign("ERR no Keys specified.");
	} else {
		// get url
        fmx::TextAutoPtr ckey;
		ckey->SetText( dataVect.AtAsText(0), 0, dataVect.AtAsText(0).GetSize() );
        fmx::TextAutoPtr sckey;
		sckey->SetText( dataVect.AtAsText(1), 0, dataVect.AtAsText(1).GetSize() );
        
        
        
        getObject()->setLicenceKeys(GetTextAsString(*ckey),GetTextAsString(*sckey));
 
            
        tempText->Assign("Licence Keys Set");
        resultText->SetText(*tempText);
		
	}
    err = result.SetAsText( *resultText, dataVect.At(0).GetLocale() );
	return err;
}


