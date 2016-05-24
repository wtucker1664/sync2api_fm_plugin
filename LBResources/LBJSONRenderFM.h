//
/*  LBJSONRenderFM.h
 *  pluginTests
 *
 *  Created on: Jun 18, 2014
 *  Modified on: May 11, 2015,May 05 2016,May 24 2016
 *      Author: Warren Tucker
 *      Email: wtucker1664@me.com
 *
 * Copyright (c) 2015 Warren Tucker. All rights reserved.
 */

#ifndef LBJSONRenderFM_h
#define LBJSONRenderFM_h


#include <iostream>
#include <string>
#include <curl/curl.h>
#include <cassert>
#include <exception>
#include <sstream>
#include <stdio.h>
#include <istream>
#include <vector>
#include <map>
#include <cstdio>
#if FMX_MAC_TARGET
#include "document.h"		// rapidjson's DOM-style API
#include "prettywriter.h"	// for stringify JSON
#else
#include "..\rapidjson\document.h"		// rapidjson's DOM-style API
#include "..\rapidjson\prettywriter.h"	// for stringify JSON
#endif


using namespace std;
using namespace rapidjson;
using std::vector;
using std::string;
using std::make_pair;
using std::for_each;
using std::string;
using std::map;
static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

namespace LB{
    class LBJSONRenderFM{
        
    private:
        string multiItemsParent = "";
        string multiItemsTestParent = "";
        vector<string> varString;
        bool multiItemsDone = false;
        int currentLevel = 0;
        bool init = false;
        
        string getVarString();
        void stepBack(SizeType p);
        void processObject(const Value& doc);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*
         *
         * 		Processing of JSON Root Document Arrays
         *
         */
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void processArray(const Value& doc);
        
        void processValue(const Value& doc);
        
        string sendDataToUrl(stringstream &postValues);
        
        string getRequestUrl();
        
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
        {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }
        
        void processDocument(Document & doc);
        
        void addComplexPropertyToRequestList();
        
       
    public:
        
        bool useDebug = false;
        bool useLBDebug = false;
        int errorCount = 0;
        stringstream LBOutput;
        stringstream LBName;
        stringstream LBValue;
        
        
        stringstream outputVars;
        stringstream outputVarsTest;
        
        string module = "";
        string method = "";
        string cKey = "";
        string scKey = "";
        
        map<int,map<string,string>> recordsTest;
        map<string,string> recordTest = *new map<string,string>() ;
        
        map<int,map<string,string>> records;
        map<string,string> record = *new map<string,string>() ;
        map<int,map<string,string>> errors;
        map<string,string> error = *new map<string,string>() ;
        map<string,string> postVars = *new map<string,string>() ;
        vector<string> complexProperty;
        
        LBJSONRenderFM();
        LBJSONRenderFM(const LBJSONRenderFM & jO);
        
        LBJSONRenderFM & operator = (const LBJSONRenderFM & jO){
            if(this != &jO){
                useDebug = jO.useDebug;
                useLBDebug = jO.useLBDebug;
                module = jO.module;
                method = jO.method;
                cKey = jO.cKey;
                scKey = jO.scKey;
                records=jO.records;
                
                errors = jO.errors;
                
                postVars = jO.postVars;
            }
            return *this;
        }
        
        stringstream getRecordVarNames();
        
        stringstream getRecordVarNames(int recNum);
        
        void printRecords();
        
        void printTestRecords();
        
        void printErrors();
        
        bool hasErrors();
        
        string getErrors();
        
        string getRecordCount();
        
        string getProperty(int rec,string prop);
        
        map<string,string> getAllProperties(int rec);
        
        void setLBDebug(bool t);
        
        void setModule(string mod);
        
        void setMethod(string meth);
        
        void setProperty(string name,string value);
        
        void setLicenceKeys(string cK,string scK);
        
        void setDebug(bool t);
        
        void printRequestVars();
        
        void clearRequest();
        
        void sendRequest();
        
        void setComplexProperty(string property);
        
        void setComplexProperty(string property , int isProperty );
        
        
        
        
        
        
        
        
    };
}


#endif
