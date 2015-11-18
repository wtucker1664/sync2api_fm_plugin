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


#include "FMPlugin.h"
#include "FMTemplate/FMTemplate.h"
#include "LBJSONRenderFM.h"
using namespace std;
using namespace rapidjson;
using namespace boost;
using namespace LB;

string convertLongToString(long input);
string GetTextAsString (const fmx::Text& source);
string GetCalc(std::string calc, const fmx::ExprEnv& environment, fmx::Data& result);
LBJSONRenderFM* getObject();
std::wstring utf8_to_utf16(const std::string& utf8);


#endif /* defined(__PlugInTemplate__LBFMPluginHandler__) */
