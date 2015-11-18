
/*
  Copyright 1998-2006 FileMaker, Inc.  All Rights Reserved.
  
*/



#if !defined(FMPLUGINGLOBALDEFINES_H)  		// Only include once.
	#define FMPLUGINGLOBALDEFINES_H



// The following are compiler specific directives.
#if defined( __GNUC__ )
	#define FMX_MAC_TARGET	1

	// Unloadable modules can not use the new style constant strings that Apple introduced
	// in 10.4. So we have to turn if off in the headers and the project file with 
	#undef __CONSTANT_CFSTRINGS__

#elif defined( _MSC_VER )
	#define FMX_WIN_TARGET	1

#endif // Compiler specific directives


#endif // FMPLUGINGLOBALDEFINES_H
