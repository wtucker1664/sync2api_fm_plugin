//
//  LBFMPluginHandler.h
//  PlugInTemplate
//
//  Created by Warren Tucker on 21/03/2014.
//
//

#ifndef __PlugInTemplate__LBFMPluginHandler__
#define __PlugInTemplate__LBFMPluginHandler__
#if FMX_WIN_TARGET

#else

#ifdef check
#undef check
#endif

#endif
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cassert>
#include <exception>
#include <sstream>
#include <stdio.h>
#include <string>
#include <istream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <cstdio>
#include <map>
#include "LBJSONRenderFM.h"

#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"

std::string convertLongToString(long input);
std::string GetTextAsString (const fmx::Text& source);
std::string GetCalc(std::string calc, const fmx::ExprEnv& environment, fmx::Data& result);
std::string getDataFromUrl(std::stringstream &url);
std::string getDataForFileMaker(std::string response,const char *vNames);
std::string sendDataToUrl(std::stringstream &postValues);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
std::string createPostString(std::string pNames);
extern std::string consumerKey;
extern std::string consumerSecretKey;
//void ParseJSON(JSONNODE *n,char *data_name,char *ignore);

#endif /* defined(__PlugInTemplate__LBFMPluginHandler__) */
