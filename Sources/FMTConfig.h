//////////////////////////////////////////////////////////////////////////////////////
//  
//  FMTConfig.h - Definitions used to configure 24U Plug-In Template
//
//  Version 3.1, Copyright �2002-2012 by 24U Software. All rights reserved.
//
//  Written by Tomas Zahradnicky, HOnza Koudelka, and Josef Andrysek
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
//  This header file contains all necessary constant definitions for building
//  your plug-in. Start your plug-in development by carefully configuring this
//  file, and you'll be ready to start coding for your external functions.
//  This header should not be included into your sources. It's only purpose
//  is to configure the template. If you need to define some constatns to be
//  used by both your code and the template, define them in your own header
//  file, such as FMPlugin.h, and include that header file here.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __FMTConfig_h__
#define __FMTConfig_h__

#include "FMPlugin.h"


////////////////////////////////////////////////////////////////////////////////
//
//  Shared constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  The following constants configure your plug-in to behave well under
//  FileMaker applications and to be well recognized on both Mac OS and
//  Windows operating systems. It is recommended to always set all these
//  contants up to contain accurate information about your plug-in.
//



#define PLUGIN_ID_STRING        "10Sync2API"

#define PLUGIN_NAME             "Sync2API"
#define PLUGIN_VERSION          "2.0"

#define PLUGIN_VERSION_MAJOR    1
#define PLUGIN_VERSION_MINOR    0
#define PLUGIN_VERSION_BUILD    0
#define PLUGIN_VERSION_DEV      0


#define PLUGIN_INFO             "This plug-in extends FileMaker applications by adding external functions for connecting to the Sync2API platform"

#define COMPANY_NAME            "Linear Blue"
#define COPY_STATEMENT          "Copyright �2015 by " COMPANY_NAME

#define WANT_IDLE               0           // set to 1 if you want idle-processing
#define WANT_PREFERENCES        0           // set to 1 if you want to handle preferences


////////////////////////////////////////////////////////////////////////////////
//
//  Mac OS X constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  Define Mac OS X specific information for you plug-in below.
//

#define PLUGIN_BUNDLE_ID    "com.linearblue.sync2api"


////////////////////////////////////////////////////////////////////////////////
//
//  Windows constants
//
/////////////////////////////////////////////////////////////////////////////
//
//  Define Windows specific information for you plug-in below.
//

#define FILE_NAME_PC        "Sync2API.fmx"  // A hint for user who accidentally renames your plug-in

#define PLUGIN_INFO_PC      "This plug-in extends FileMaker applications by adding external functions for connecting to the Sync2API platform"

#define COMPANY_URL         "http://www.linearblue.com/"


////////////////////////////////////////////////////////////////////////////////
//
//  Function definitions
//
/////////////////////////////////////////////////////////////////////////////
//
//  Do not modify the following enum, use the defined constants to configure
//  minimum and maximum parameters required for each function
//  (the FUNCTION_X_PARAMS macros)
//

#ifndef __PLIST__
enum {
    kAtLeast_0_Parameters = 0,
    kAtLeast_1_Parameter  = 1,
    kAtLeast_2_Parameters = 2,
    kAtLeast_3_Parameters = 3,
    kAtLeast_4_Parameters = 4,
    kAtLeast_5_Parameters = 5,
    kAtLeast_6_Parameters = 6,
    kAtLeast_7_Parameters = 7,
    kAtLeast_8_Parameters = 8,
    kAtLeast_9_Parameters = 9,
    kAtLeast_10_Parameters = 10,

    kAtWorst_0_Parameters = 0,
    kAtWorst_1_Parameter  = 1,
    kAtWorst_2_Parameters = 2,
    kAtWorst_3_Parameters = 3,
    kAtWorst_4_Parameters = 4,
    kAtWorst_5_Parameters = 5,
    kAtWorst_6_Parameters = 6,
    kAtWorst_7_Parameters = 7,
    kAtWorst_8_Parameters = 8,
    kAtWorst_9_Parameters = 9,
    kAtWorst_10_Parameters = 10,
    kAtWorst_Unlimited_Parameters = -1
};
#endif // __PLIST__

/////////////////////////////////////////////////////////////////////////////
//
//  Define your external functions here. For each of your functions,
//  uncomment the first commented block of defines, and set up the
//  function's name, flags, parameters and prototype.
//

#define FUNCTION_1_C_NAME         Sync2API_Version
#define FUNCTION_1_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_1_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_1_PROTOTYPE      "Sync2API_Version( { versionFormat } )"

#define FUNCTION_2_C_NAME         Sync2API_SetModule
#define FUNCTION_2_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_2_PARAMS         kAtLeast_1_Parameter, kAtWorst_1_Parameter
#define FUNCTION_2_PROTOTYPE      "Sync2API_SetModule( module )"

#define FUNCTION_3_C_NAME         Sync2API_SetMethod
#define FUNCTION_3_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_3_PARAMS         kAtLeast_1_Parameter, kAtWorst_1_Parameter
#define FUNCTION_3_PROTOTYPE      "Sync2API_SetMethod( method )"

#define FUNCTION_4_C_NAME         Sync2API_SendRequest
#define FUNCTION_4_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_4_PARAMS         kAtLeast_0_Parameters, kAtLeast_0_Parameters
#define FUNCTION_4_PROTOTYPE      "Sync2API_SendRequest"

#define FUNCTION_5_C_NAME         Sync2API_GetRecordCount
#define FUNCTION_5_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_5_PARAMS         kAtLeast_0_Parameters, kAtLeast_0_Parameters
#define FUNCTION_5_PROTOTYPE      "Sync2API_GetRecordCount"

#define FUNCTION_6_C_NAME         Sync2API_GetProperty
#define FUNCTION_6_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_6_PARAMS         kAtLeast_2_Parameters, kAtWorst_2_Parameters
#define FUNCTION_6_PROTOTYPE      "Sync2API_GetProperty( recordNumber ; propertyName )"

#define FUNCTION_7_C_NAME         Sync2API_GetAllProperties
#define FUNCTION_7_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_7_PARAMS         kAtLeast_1_Parameter, kAtWorst_1_Parameter
#define FUNCTION_7_PROTOTYPE      "Sync2API_GetAllProperties( recordNumber )"

#define FUNCTION_8_C_NAME         Sync2API_ClearRequest
#define FUNCTION_8_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_8_PARAMS         kAtLeast_0_Parameters, kAtWorst_0_Parameters
#define FUNCTION_8_PROTOTYPE      "Sync2API_ClearRequest"

#define FUNCTION_9_C_NAME         Sync2API_Licence
#define FUNCTION_9_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_9_PARAMS         kAtLeast_2_Parameters, kAtWorst_2_Parameters
#define FUNCTION_9_PROTOTYPE      "Sync2API_Licence( ckey ; sckey )"


#define FUNCTION_10_C_NAME         Sync2API_GetRecordVarNames
#define FUNCTION_10_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_10_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_10_PROTOTYPE      "Sync2API_GetRecordVarNames( { recordNumber } )"

#define FUNCTION_11_C_NAME         Sync2API_SetProperty
#define FUNCTION_11_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_11_PARAMS         kAtLeast_2_Parameters, kAtWorst_2_Parameters
#define FUNCTION_11_PROTOTYPE      "Sync2API_SetProperty( name ; value )"

#define FUNCTION_12_C_NAME         Sync2API_SetComplexProperty
#define FUNCTION_12_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_12_PARAMS         kAtLeast_1_Parameter, kAtWorst_2_Parameters
#define FUNCTION_12_PROTOTYPE      "Sync2API_SetComplexProperty( name ; { isValue } )"
/*
#define FUNCTION_13_C_NAME         Sync2API_TwitterSetRowCount
#define FUNCTION_13_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_13_PARAMS         kAtLeast_0_Parameters, kAtWorst_1_Parameter
#define FUNCTION_13_PROTOTYPE      "Sync2API_TwitterSetRowCount( { qty } ) //Qty = Optional value for the last number of tweets to get (leave blank for default of 1"

#define FUNCTION_14_C_NAME         Sync2API_TwitterGetRow
#define FUNCTION_14_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_14_PARAMS         kAtLeast_2_Parameters, kAtWorst_2_Parameters
#define FUNCTION_14_PROTOTYPE      "Sync2API_TwitterGetRow( type ; row ) //Type = \'Simple\' to get just the text or \'Complex\' to get all data; Row = Pass the row number through as a variable in a loop"

#define FUNCTION_15_C_NAME         Sync2API_TwitterPost
#define FUNCTION_15_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_15_PARAMS         kAtLeast_1_Parameter, kAtWorst_1_Parameter
#define FUNCTION_15_PROTOTYPE      "Sync2API_TwitterPost( text ) // Remember to limit your tweet to xx characters in length"

#define FUNCTION_16_C_NAME         Sync2API_TwitterDelete
#define FUNCTION_16_FLAGS          fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs
#define FUNCTION_16_PARAMS         kAtLeast_1_Parameter, kAtWorst_1_Parameter
#define FUNCTION_16_PROTOTYPE      "Sync2API_TwitterDelete( id_str ) // The id string of the tweet"

*/
////////////////////////////////////////////////////////////////////////////////

#endif // __FMTConfig_h__
