//////////////////////////////////////////////////////////////////////////////////////
//  
//  myplc.c - File used to extract information from header files to generate
//            info.plist and Localizable.strings
//
//  Version 3.1, Copyright ©2004-2012 by 24U Software. All rights reserved.
//
//  Written by Josef Andrysek
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


#ifndef __PLIST__
    #define __PLIST__   //  Only include definitions intended for plist generation
#endif 

#include "FMTConfig.h"

my_plugin_bundle_id=PLUGIN_BUNDLE_ID
my_plugin_version=PLUGIN_VERSION
my_CFBundleName=CFBUNDLENAME                  
my_copy_statement=COPY_STATEMENT
my_plugin_info=PLUGIN_INFO
my_plugin_name=PLUGIN_NAME
my_plugin_id_string=PLUGIN_ID_STRING


    #ifdef FUNCTION_1_PROTOTYPE
      my_function_1_prototype=FUNCTION_1_PROTOTYPE
	  my_function_1_prototype_str="String101"
        #ifdef FUNCTION_2_PROTOTYPE
		  my_function_2_prototype=FUNCTION_2_PROTOTYPE
		  my_function_2_prototype_str="String102"
            #ifdef FUNCTION_3_PROTOTYPE
			  my_function_3_prototype=FUNCTION_3_PROTOTYPE
			  my_function_3_prototype_str="String103"
                #ifdef FUNCTION_4_PROTOTYPE
				  my_function_4_prototype=FUNCTION_4_PROTOTYPE
				  my_function_4_prototype_str="String104"
                    #ifdef FUNCTION_5_PROTOTYPE
					  my_function_5_prototype=FUNCTION_5_PROTOTYPE
					  my_function_5_prototype_str="String105"
                        #ifdef FUNCTION_6_PROTOTYPE
						  my_function_6_prototype=FUNCTION_6_PROTOTYPE
						  my_function_6_prototype_str="String106"
                            #ifdef FUNCTION_7_PROTOTYPE
							  my_function_7_prototype=FUNCTION_7_PROTOTYPE
							  my_function_7_prototype_str="String107"
								#ifdef FUNCTION_8_PROTOTYPE
								  my_function_8_prototype=FUNCTION_8_PROTOTYPE
								  my_function_8_prototype_str="String108"
                                    #ifdef FUNCTION_9_PROTOTYPE
									  my_function_9_prototype=FUNCTION_9_PROTOTYPE
									  my_function_9_prototype_str="String109"
										#ifdef FUNCTION_10_PROTOTYPE
										  my_function_10_prototype=FUNCTION_10_PROTOTYPE
										  my_function_10_prototype_str="String110"
                                            #ifdef FUNCTION_11_PROTOTYPE
                                              my_function_11_prototype=FUNCTION_11_PROTOTYPE
                                              my_function_11_prototype_str="String111"
                                              #ifdef FUNCTION_12_PROTOTYPE
                                                my_function_12_prototype=FUNCTION_12_PROTOTYPE
                                                my_function_12_prototype_str="String112"
                                                    #ifdef FUNCTION_13_PROTOTYPE
                                                        my_function_13_prototype=FUNCTION_13_PROTOTYPE
                                                        my_function_13_prototype_str="String113"
                                                        #ifdef FUNCTION_14_PROTOTYPE
                                                            my_function_14_prototype=FUNCTION_14_PROTOTYPE
                                                            my_function_14_prototype_str="String114"
                                                            #ifdef FUNCTION_15_PROTOTYPE
                                                                my_function_15_prototype=FUNCTION_15_PROTOTYPE
                                                                my_function_15_prototype_str="String115"
                                                                #ifdef FUNCTION_16_PROTOTYPE
                                                                    my_function_16_prototype=FUNCTION_16_PROTOTYPE
                                                                    my_function_16_prototype_str="String116"
                                                                #endif //FUNCTION_16_PROTOTYPE
                                                            #endif //FUNCTION_15_PROTOTYPE
                                                        #endif //FUNCTION_14_PROTOTYPE
                                                    #endif //FUNCTION_13_PROTOTYPE
                                                #endif //FUNCTION_12_PROTOTYPE
                                            #endif //FUNCTION_11_PROTOTYPE
                                        #endif //FUNCTION_10_PROTOTYPE
                                    #endif //FUNCTION_9_PROTOTYPE
                                #endif //FUNCTION_8_PROTOTYPE
                            #endif //FUNCTION_7_PROTOTYPE
                        #endif //FUNCTION_6_PROTOTYPE
                    #endif //FUNCTION_5_PROTOTYPE
                #endif //FUNCTION_4_PROTOTYPE
            #endif //FUNCTION_3_PROTOTYPE
        #endif //FUNCTION_2_PROTOTYPE
    #endif //FUNCTION_1_PROTOTYPE

