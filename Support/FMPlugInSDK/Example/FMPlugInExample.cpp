
/*
  Copyright 1998-2006 FileMaker, Inc.  All Rights Reserved.
  
*/



#include "Support/FMPluginGlobalDefines.h"

#if defined(FMX_WIN_TARGET)
	#include "Windows.h"
#endif

#include "FMWrapper/FMXExtern.h"
#include "FMWrapper/FMXTypes.h"
#include "FMWrapper/FMXFixPt.h"
#include "FMWrapper/FMXText.h"
#include "FMWrapper/FMXData.h"
#include "FMWrapper/FMXCalcEngine.h"

#include "Support/FMPluginFunctions.h"
#include "Support/FMPluginPrefs.h"



// ====== "FMPluginExample.h" =================================================================================
// Header-like information for FMPlugInExample.cpp

// General String IDs
	
	// The following strings are usually not localized, but it is your option.
	enum
	{ 
			kXMpl_AddStringID = 102, 
			kXMpl_AppendStringID = 103, 
			kXMpl_EvaluateStringID = 104, 
			kXMpl_StartScriptStringID = 105, 
			kXMpl_UserFormatNumberStringID = 106, 
			kXMpl_FormatNumberStringID = 107, 
			kXMpl_NumToWordsStringID = 108,
			kXMpl_VersionStringID = 109
	};

	// The following strings are usually localized, but it is your option.
	enum { XMpl_PluginNameStringID = 128, kXMpl_PluginDescStringID = 129 }; 


	FMX_ExternCallPtr	gFMX_ExternCallPtr=NULL;



/* ::=- Do_PluginInit =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=:: */
static FMX_Long Do_PluginInit(FMX_Short version) 
{
	// Check the app API version
	if ((version < k70ExtnVersion) || (version > kMaxExtnVersion)) 
	{
		// This version of FileMaker is not supported; let FileMaker disable this 
		// plug-in and report the problem to the user.
		return (kBadExtnVersion);
	}


	// Setup a preference file (Mac OS X) or make changes to preferences settings in the Windows Registry for the plug-in.  
	{
		FMPluginExamplePrefsWidget		prefsLoader;
		if(prefsLoader.Exists() == false)
		{
			prefsLoader.Create();
		}

		if(prefsLoader.Read() == false)
		{
			return (kDoNotEnable);

		}// prefsLoader Read
	}


	// Register plug-in functions
	fmx::QuadCharAutoPtr	pluginID('X', 'M', 'p', 'l');
	fmx::TextAutoPtr		name;
	fmx::TextAutoPtr		prototype;
	fmx::errcode			err;
	fmx::ulong				regFunctionFlags = fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs;

	Do_GetString(kXMpl_AddStringID, name, true);
	Do_GetString(kXMpl_AddStringID, prototype);
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_Add, *name, *prototype, 2, 2, regFunctionFlags, Do_XMpl_Add );
	//	if (err != 0)   // You should warn the user or recover. For the purposes of this example, we ignore the result.

	Do_GetString(kXMpl_AppendStringID, name, true);
	Do_GetString(kXMpl_AppendStringID, prototype);
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_Append, *name, *prototype, 1, -1, regFunctionFlags, Do_XMpl_Append );

	Do_GetString(kXMpl_EvaluateStringID, name, true);
	Do_GetString(kXMpl_EvaluateStringID, prototype);
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_Evaluate, *name, *prototype, 1, 1, regFunctionFlags, Do_XMpl_Evaluate );

	Do_GetString(kXMpl_StartScriptStringID, name, true);
	Do_GetString(kXMpl_StartScriptStringID, prototype);
	regFunctionFlags = fmx::ExprEnv::kDisplayInAllDialogs;
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_StartScript, *name, *prototype, 2, 2, regFunctionFlags, Do_XMpl_StartScript );

	Do_GetString(kXMpl_UserFormatNumberStringID, name, true);
	Do_GetString(kXMpl_UserFormatNumberStringID, prototype);
	regFunctionFlags = fmx::ExprEnv::kDisplayCalcFields |  fmx::ExprEnv::kDisplayAutoEnter | fmx::ExprEnv::kDisplayCustomFunctions | fmx::ExprEnv::kDisplayGeneric;
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_UserFormatNumber, *name, *prototype, 1, 1, regFunctionFlags, Do_XMpl_CommonFormatNumber );

	Do_GetString(kXMpl_FormatNumberStringID, name, true);
	Do_GetString(kXMpl_FormatNumberStringID, prototype);
	regFunctionFlags = fmx::ExprEnv::kDisplayAutoEnter;
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_FormatNumber, *name, *prototype, 2, 2, regFunctionFlags, Do_XMpl_CommonFormatNumber );

	Do_GetString(kXMpl_NumToWordsStringID, name, true);
	Do_GetString(kXMpl_NumToWordsStringID, prototype);
	regFunctionFlags = fmx::ExprEnv::kMayEvaluateOnServer | fmx::ExprEnv::kDisplayInAllDialogs;
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_NumToWords, *name, *prototype, 1, 1, regFunctionFlags, Do_XMpl_NumToWords );

	Do_GetString(kXMpl_VersionStringID, name, true);
	Do_GetString(kXMpl_VersionStringID, prototype);
	err = fmx::ExprEnv::RegisterExternalFunction(*pluginID, kXMpl_Version, *name, *prototype, 0, 0, regFunctionFlags, Do_XMpl_Version );


	// Return kCurrentExtnVersion to enable the plug-in in FileMaker.
	return (kCurrentExtnVersion);
	
} // Do_PluginInit



/* ::=- Do_PluginIdle =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=:: */
static void Do_PluginIdle(FMX_IdleLevel idleLevel) 
{
	// Check idle state
	switch (idleLevel)
	{
		case kFMXT_UserIdle:
		{
			// The plug-in is free to do idle processing at this time.
		}
		break;

		case kFMXT_UserNotIdle:
		case kFMXT_ScriptPaused:
		case kFMXT_ScriptRunning:
		case kFMXT_Unsafe:
		{
			// The plug-in should wait and do nothing at this time.
		}
		break;
	}// switch idleLevel

} // Do_PluginIdle



/* ::=- Do_PluginShutdown =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=:: */
static void Do_PluginShutdown(void) 
{

	// Unregister plug-in functions
	fmx::QuadCharAutoPtr	pluginID('X', 'M', 'p', 'l');
	fmx::errcode			err;

	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_Add );
	// if (err != 0)  // There is likely nothing to do in response. For the purposes of this example, we ignore the result.

	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_Append );
	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_Evaluate );
	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_StartScript );
	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_UserFormatNumber );
	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_FormatNumber );
	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_NumToWords );
	err = fmx::ExprEnv::UnRegisterExternalFunction(*pluginID, kXMpl_Version );

} // Do_PluginShutdown



/* ::=- FMExternCallProc "Main" =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=:: */
void FMX_ENTRYPT FMExternCallProc(FMX_ExternCallPtr pb)
{
	// Setup global defined in FMxExtern.h
	gFMX_ExternCallPtr = pb;

	// Message dispatcher
	switch (gFMX_ExternCallPtr->whichCall) 
	{
		case kFMXT_Init:
		{
			gFMX_ExternCallPtr->result = Do_PluginInit(gFMX_ExternCallPtr->extnVersion);
		}
		break;
			
		case kFMXT_Idle:
		{
			Do_PluginIdle(gFMX_ExternCallPtr->parm1);
		}
		break;
			
		case kFMXT_Shutdown:
		{
			Do_PluginShutdown();
		}
		break;
			
		case kFMXT_DoAppPreferences:
		{
			Do_PluginPrefs();
		}
		break;

		case kFMXT_GetString:
		{
			Do_GetString(gFMX_ExternCallPtr->parm1, gFMX_ExternCallPtr->parm2,
						gFMX_ExternCallPtr->parm3, reinterpret_cast<FMX_Unichar*>(gFMX_ExternCallPtr->result));
		}
		break;

	}// switch whichCall

} // FMExternCallProc
	
