//
//  LBJSONRenderFM.h
//  pluginTests
//
//  Created by Warren Tucker on 13/05/2015.
//  Copyright (c) 2015 Warren Tucker. All rights reserved.
//

#ifndef LBJSONRenderFM_h
#define LBJSONRenderFM_h

/*
 * LBJSONRenderFM.hpp
 *
 *  Created on: Jun 18, 2014
 *  Modified on: May 11, 2015
 *      Author: Warren Tucker
 *      Email: warren.tucker@linearblue.com
 */
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
        
        void processObject(const Value& doc){
            if(useLBDebug){
                printf("------ \n");
            }
            
            
            
            for (Value::ConstMemberIterator itr = doc.MemberBegin();
                 itr != doc.MemberEnd(); ++itr)
            {
                bool intDone = false;
                if(kTypeNames[itr->value.GetType()] == kTypeNames[3]){
                    if(useLBDebug){
                        printf("Type of member processObject Object %s is %s\n",itr->name.GetString(), kTypeNames[itr->value.GetType()]);
                    }
                    const rapidjson::Value& membersObj = doc[itr->name.GetString()];
                    parentVar = itr->name.GetString();
                    this->processObject(membersObj);
                    parentVar = "";
                }else if(kTypeNames[itr->value.GetType()] == kTypeNames[4]){
                    if(useLBDebug){
                        printf("Type of member processObject Array %s is %s\n",itr->name.GetString(), kTypeNames[itr->value.GetType()]);
                    }
                    string pVar = "";
                    
                    if(parentVar != ""){
                        pVar = parentVar;
                    }
                    stringstream arrayCount;
                    arrayCount << doc[itr->name.GetString()].Size();
                    stringstream arrayCountText;
                    if(pVar != ""){
                        
                        arrayCountText << pVar.c_str() << "_" << itr->name.GetString() << "_count";
                        
                    }else{
                        arrayCountText << itr->name.GetString() << "_count";
                        
                    }
                    record.insert(make_pair(arrayCountText.str(),arrayCount.str()));
                    for (SizeType i = 0; i < doc[itr->name.GetString()].Size(); i++){
                        const rapidjson::Value& membersArray = doc[itr->name.GetString()][i];
                        
                        stringstream multiItems;
                        
                        if(doc[itr->name.GetString()][i].IsArray()){
                            multiItems << itr->name.GetString() << "_" << i;
                            
                            parentVar = multiItems.str();
                            this->processArray(membersArray);
                        }else if(doc[itr->name.GetString()][i].IsObject()){
                            multiItems << itr->name.GetString() << "_" << i;
                            
                            parentVar = multiItems.str();
                            this->processObject(membersArray);
                        }else{
                            if(pVar != ""){
                                multiItems << pVar.c_str() << "_" << itr->name.GetString() << "_" << i;
                            }else{
                                multiItems << itr->name.GetString() << "_" << i;
                                
                            }
                            parentVar = multiItems.str();
                            if(useLBDebug){
                                cout << pVar.c_str() << endl;
                                cout << parentVar.c_str() << endl;
                            }
                            this->processValue(membersArray);
                        }
                        
                        
                    }
                    parentVar = "";
                    
                }else{
                    if(useLBDebug){
                        printf("Type of member processObject Value is %s", kTypeNames[itr->value.GetType()]);
                    }
                    if(itr->value.IsString()){
                        if(useLBDebug){
                            printf(" %s = %s",itr->name.GetString(),itr->value.GetString());
                        }
                        if(parentVar != ""){
                            LBName << parentVar << "_";
                        }
                        LBName << itr->name.GetString();
                        LBValue << itr->value.GetString();
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    if(itr->value.IsNumber()){
                        if(itr->value.IsInt()){
                            if(!intDone){
                                if(useLBDebug){
                                    printf(" %s = %d ",itr->name.GetString(),itr->value.GetInt());
                                }
                                if(parentVar != ""){
                                    LBName << parentVar << "_";
                                }
                                LBName << itr->name.GetString();
                                LBValue << itr->value.GetInt();
                                record.insert(make_pair(LBName.str(),LBValue.str()));
                                LBName.str(std::string());
                                LBValue.str(std::string());
                                intDone = true;
                            }
                            //printf(" %s = %d ",itr->name.GetString(),itr->value.GetInt());
                        }
                        if(itr->value.IsDouble()){
                            if(useLBDebug){
                                printf(" %s = %f ",itr->name.GetString(),itr->value.GetDouble());
                            }
                            if(parentVar != ""){
                                LBName << parentVar << "_";
                            }
                            LBName << itr->name.GetString();
                            LBValue << itr->value.GetDouble();
                            record.insert(make_pair(LBName.str(),LBValue.str()));
                            LBName.str(std::string());
                            LBValue.str(std::string());
                        }
                        if(itr->value.IsInt64()){
                            if(!intDone){
                                if(useLBDebug){
                                    printf(" %s = %lld ",itr->name.GetString(),itr->value.GetInt64());
                                }
                                if(parentVar != ""){
                                    LBName << parentVar << "_";
                                }
                                LBName << itr->name.GetString();
                                LBValue << itr->value.GetInt64();
                                record.insert(make_pair(LBName.str(),LBValue.str()));
                                LBName.str(std::string());
                                LBValue.str(std::string());
                            }
                            
                        }
                    }
                    if(itr->value.IsNull()){
                        if(useLBDebug){
                            printf(" %s = NULL ",itr->name.GetString());
                        }
                        if(parentVar != ""){
                            LBName << parentVar << "_";
                        }
                        LBName << itr->name.GetString();
                        LBValue << "Null";
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    if(itr->value.IsBool()){
                        if(useLBDebug){
                            printf(" %s = %d ",itr->name.GetString(),itr->value.GetBool());
                        }
                        if(parentVar != ""){
                            LBName << parentVar << "_";
                        }
                        LBName << itr->name.GetString();
                        LBValue << itr->value.GetBool();
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    if(useLBDebug){
                        printf("\n");
                    }
                    //
                    
                }
            }
            
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*
         *
         * 		Processing of JSON Root Document Arrays
         *
         */
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void processArray(const Value& doc){
            if(useLBDebug){
                printf("------\n");
            }
            bool intDone = false;
            if(doc.IsArray()){
                
            }else{
            for (Value::ConstMemberIterator itr = doc.MemberBegin();
                 itr != doc.MemberEnd(); ++itr)
            {
                intDone = false;
                if(kTypeNames[itr->value.GetType()] == kTypeNames[3]){
                    if(useLBDebug){
                        printf("Type of processArray Object %s is %s\n",itr->name.GetString(), kTypeNames[itr->value.GetType()]);
                    }
                    const rapidjson::Value& memberObj = itr->value;
                    if(memberObj.IsObject()){
                        if(parentVar != ""){
                            stringstream ss;
                            ss << "_" << itr->name.GetString();
                            parentVar += ss.str();
                        }
                        
                        this->processObject(memberObj);
                    }else if(memberObj.IsArray()){
                        if(parentVar != ""){
                            stringstream ss;
                            ss << "_" << itr->name.GetString();
                            parentVar += ss.str();
                        }
                        
                        this->processArray(memberObj);
                    }else{
                        for (SizeType i = 0; i < itr->value.Size(); i++){
                            intDone = false;
                            const rapidjson::Value& membersObj = itr->value[i];
                            if(membersObj.IsObject()){
                                if(parentVar != ""){
                                    stringstream ss;
                                    ss << "_" << itr->name.GetString();
                                    parentVar += ss.str();
                                }
                                this->processObject(membersObj);
                            }else if(membersObj.IsArray()){
                                if(parentVar != ""){
                                    stringstream ss;
                                    ss << "_" << itr->name.GetString();
                                    parentVar += ss.str();
                                }
                                this->processArray(membersObj);
                            }else{
                                if(useLBDebug){
                                    printf("Type of member processArray Object Value %s is %s",itr->name.GetString(), kTypeNames[itr->value.GetType()]);
                                }
                                if(itr->value.IsString()){
                                    printf(" %s = %s ",itr->name.GetString(),itr->value.GetString());
                                    if(parentVar != ""){
                                        LBName << parentVar << "_";
                                    }
                                    LBName << itr->name.GetString();
                                    LBValue << itr->value.GetString();
                                    record.insert(make_pair(LBName.str(),LBValue.str()));
                                    LBName.str(std::string());
                                    LBValue.str(std::string());
                                }
                                if(itr->value.IsNumber()){
                                    if(itr->value.IsInt()){
                                        if(!intDone){
                                            if(useLBDebug){
                                                printf("int %s = %d ",itr->name.GetString(),itr->value.GetInt());
                                            }
                                            if(parentVar != ""){
                                                LBName << parentVar << "_";
                                            }
                                            LBName << itr->name.GetString();
                                            LBValue << itr->value.GetInt();
                                            record.insert(make_pair(LBName.str(),LBValue.str()));
                                            LBName.str(std::string());
                                            LBValue.str(std::string());
                                            intDone = true;
                                        }
                                        //printf(" %s = %d ",itr->name.GetString(),itr->value.GetInt());
                                    }
                                    if(itr->value.IsDouble()){
                                        if(useLBDebug){
                                            printf(" %s = %f ",itr->name.GetString(),itr->value.GetDouble());
                                        }
                                        if(parentVar != ""){
                                            LBName << parentVar << "_";
                                        }
                                        LBName << itr->name.GetString();
                                        LBValue << itr->value.GetDouble();
                                        record.insert(make_pair(LBName.str(),LBValue.str()));
                                        LBName.str(std::string());
                                        LBValue.str(std::string());
                                    }
                                    if(itr->value.IsInt64()){
                                        if(!intDone){
                                            if(useLBDebug){
                                                printf("int64 %s = %lld ",itr->name.GetString(),itr->value.GetInt64());
                                            }
                                            if(parentVar != ""){
                                                LBName << parentVar << "_";
                                            }
                                            LBName << itr->name.GetString();
                                            LBValue << itr->value.GetInt64();
                                            record.insert(make_pair(LBName.str(),LBValue.str()));
                                            LBName.str(std::string());
                                            LBValue.str(std::string());
                                            
                                        }
                                        
                                    }
                                }
                                if(itr->value.IsNull()){
                                    if(useLBDebug){
                                        printf(" %s = NULL ",itr->name.GetString());
                                    }
                                    if(parentVar != ""){
                                        LBName << parentVar << "_";
                                    }
                                    LBName << itr->name.GetString();
                                    LBValue << "Null";
                                    record.insert(make_pair(LBName.str(),LBValue.str()));
                                    LBName.str(std::string());
                                    LBValue.str(std::string());
                                }
                                if(itr->value.IsBool()){
                                    if(useLBDebug){
                                        printf(" %s = %d ",itr->name.GetString(),itr->value.GetBool());
                                    }
                                    if(parentVar != ""){
                                        LBName << parentVar << "_";
                                    }
                                    LBName << itr->name.GetString();
                                    LBValue << itr->value.GetBool();
                                    record.insert(make_pair(LBName.str(),LBValue.str()));
                                    LBName.str(std::string());
                                    LBValue.str(std::string());
                                }
                                printf("\n");
                            }
                            
                        }
                    }
                    
                }else if(kTypeNames[itr->value.GetType()] == kTypeNames[4]){
                    if(useLBDebug){
                        printf("Type of member processArray Array %s is %s size %d \n",itr->name.GetString(), kTypeNames[itr->value.GetType()],itr->value.Size());
                    }
                    int num = 0;
                    for (Value::ConstValueIterator itr1 = itr->value.Begin(); itr1 != itr->value.End(); ++itr1){
                        bool intDone = false;
                        //printf("Type of member processArray Array Value %s is %s",itr->name[i].GetString(), kTypeNames[itr->value[i].GetType()]);
                        
                        if(itr1->IsString()){
                            if(useLBDebug){
                                printf(" %s_%d = %s ",itr->name.GetString(),num,itr1->GetString());
                            }
                            if(parentVar != ""){
                                LBName << parentVar << "_";
                            }
                            LBName << itr->name.GetString() << num;
                            LBValue << itr1->GetString();
                            record.insert(make_pair(LBName.str(),LBValue.str()));
                            LBName.str(std::string());
                            LBValue.str(std::string());
                        }
                        if(itr1->IsNumber()){
                            if(itr1->IsInt()){
                                if(!intDone){
                                    if(useLBDebug){
                                        printf(" %s_%d = %d ",itr->name.GetString(),num,itr1->GetInt());
                                    }
                                    if(parentVar != ""){
                                        LBName << parentVar << "_";
                                    }
                                    LBName << itr->name.GetString() << num;
                                    LBValue << itr1->GetInt();
                                    record.insert(make_pair(LBName.str(),LBValue.str()));
                                    LBName.str(std::string());
                                    LBValue.str(std::string());
                                    intDone = true;
                                }
                                //printf(" %s_%d = %d ",itr->name.GetString(),num,itr->value.GetInt());
                            }
                            if(itr1->IsDouble()){
                                if(useLBDebug){
                                    printf(" %s_%d = %f ",itr->name.GetString(),num,itr1->GetDouble());
                                }
                                if(parentVar != ""){
                                    LBName << parentVar << "_";
                                }
                                LBName << itr->name.GetString() << num;
                                LBValue << itr1->GetDouble();
                                record.insert(make_pair(LBName.str(),LBValue.str()));
                                LBName.str(std::string());
                                LBValue.str(std::string());
                            }
                            if(itr1->IsInt64()){
                                if(!intDone){
                                    if(useLBDebug){
                                        printf(" %s_%d = %lld ",itr->name.GetString(),num,itr1->GetInt64());
                                    }
                                    if(parentVar != ""){
                                        LBName << parentVar << "_";
                                    }
                                    LBName << itr->name.GetString() << num;
                                    LBValue << itr1->GetInt64();
                                    record.insert(make_pair(LBName.str(),LBValue.str()));
                                    LBName.str(std::string());
                                    LBValue.str(std::string());
                                }
                            }
                            
                        }
                        if(itr1->IsNull()){
                            if(useLBDebug){
                                printf(" %s_%d = NULL ",itr->name.GetString(),num);
                            }
                            if(parentVar != ""){
                                LBName << parentVar << "_";
                            }
                            LBName << itr->name.GetString() << num;
                            LBValue << "Null";
                            record.insert(make_pair(LBName.str(),LBValue.str()));
                            LBName.str(std::string());
                            LBValue.str(std::string());
                        }
                        if(itr1->IsBool()){
                            if(useLBDebug){
                                printf(" %s_%d = %d ",itr->name.GetString(),num,itr1->GetBool());
                            }
                            if(parentVar != ""){
                                LBName << parentVar << "_" << num;
                            }
                            LBName << itr->name.GetString();
                            LBValue << itr1->GetBool();
                            record.insert(make_pair(LBName.str(),LBValue.str()));
                            LBName.str(std::string());
                            LBValue.str(std::string());
                        }
                        if(useLBDebug){
                            printf("\n");
                        }
                        
                        
                        num++;
                        
                        
                        
                        
                        
                    }
                    
                }else{
                    if(useLBDebug){
                        printf("Type of member processArray Value is %s", kTypeNames[itr->value.GetType()]);
                    }
                    if(itr->value.IsString()){
                        printf(" %s = %s ",itr->name.GetString(),itr->value.GetString());
                        if(parentVar != ""){
                            LBName << parentVar << "_";
                        }
                        LBName << itr->name.GetString();
                        LBValue << itr->value.GetString();
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    if(itr->value.IsNumber()){
                        if(itr->value.IsInt()){
                            if(!intDone){
                                if(useLBDebug){
                                    printf("int %s = %d ",itr->name.GetString(),itr->value.GetInt());
                                }
                                if(parentVar != ""){
                                    LBName << parentVar << "_";
                                }
                                LBName << itr->name.GetString();
                                LBValue << itr->value.GetInt();
                                record.insert(make_pair(LBName.str(),LBValue.str()));
                                LBName.str(std::string());
                                LBValue.str(std::string());
                                intDone = true;
                            }
                            //printf(" %s = %d ",itr->name.GetString(),itr->value.GetInt());
                        }
                        if(itr->value.IsDouble()){
                            if(useLBDebug){
                                printf(" %s = %f ",itr->name.GetString(),itr->value.GetDouble());
                            }
                            if(parentVar != ""){
                                LBName << parentVar << "_";
                            }
                            LBName << itr->name.GetString();
                            LBValue << itr->value.GetDouble();
                            record.insert(make_pair(LBName.str(),LBValue.str()));
                            LBName.str(std::string());
                            LBValue.str(std::string());
                        }
                        if(itr->value.IsInt64()){
                            if(!intDone){
                                if(useLBDebug){
                                    printf("int64 %s = %lld ",itr->name.GetString(),itr->value.GetInt64());
                                }
                                if(parentVar != ""){
                                    LBName << parentVar << "_";
                                }
                                LBName << itr->name.GetString();
                                LBValue << itr->value.GetInt64();
                                record.insert(make_pair(LBName.str(),LBValue.str()));
                                LBName.str(std::string());
                                LBValue.str(std::string());
                            }
                        }
                    }
                    if(itr->value.IsNull()){
                        if(useLBDebug){
                            printf(" %s = NULL ",itr->name.GetString());
                        }
                        if(parentVar != ""){
                            LBName << parentVar << "_";
                        }
                        LBName << itr->name.GetString();
                        LBValue << "Null";
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    if(itr->value.IsBool()){
                        if(useLBDebug){
                            printf(" %s = %d ",itr->name.GetString(),itr->value.GetBool());
                        }
                        if(parentVar != ""){
                            LBName << parentVar << "_";
                        }
                        LBName << itr->name.GetString();
                        LBValue << itr->value.GetBool();
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    if(useLBDebug){
                        printf("\n");
                    }
                }
            }
            }
            
        }
        
        void processValue(const Value& doc){
            bool intDone = false;
            if(useLBDebug){
                printf("Type of member processObject Value is %s", kTypeNames[doc.GetType()]);
            }
            if(doc.IsString()){
                if(useLBDebug){
                    printf(" %s = %s",parentVar.c_str(),doc.GetString());
                }
                if(parentVar != ""){
                    LBName << parentVar;
                }else{
                    LBName << doc.GetString();
                }
                
                LBValue << doc.GetString();
                record.insert(make_pair(LBName.str(),LBValue.str()));
                LBName.str(std::string());
                LBValue.str(std::string());
            }
            if(doc.IsNumber()){
                if(doc.IsInt()){
                    if(!intDone){
                        if(useLBDebug){
                            printf(" %s = %d ",parentVar.c_str(),doc.GetInt());
                        }
                        if(parentVar != ""){
                            LBName << parentVar ;
                        }else{
                            LBName << doc.GetString();
                        }
                        LBValue << doc.GetInt();
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                        intDone = true;
                    }
                    //printf(" %s = %d ",itr->name.GetString(),itr->value.GetInt());
                }
                if(doc.IsDouble()){
                    if(useLBDebug){
                        printf(" %s = %f ",parentVar.c_str(),doc.GetDouble());
                    }
                    if(parentVar != ""){
                        LBName << parentVar;
                    }else{
                        LBName << doc.GetString();
                    }
                    LBValue << doc.GetDouble();
                    record.insert(make_pair(LBName.str(),LBValue.str()));
                    LBName.str(std::string());
                    LBValue.str(std::string());
                }
                if(doc.IsInt64()){
                    if(!intDone){
                        if(useLBDebug){
                            printf(" %s = %lld ",parentVar.c_str(),doc.GetInt64());
                        }
                        if(parentVar != ""){
                            LBName << parentVar;
                        }else{
                            LBName << doc.GetString();
                        }
                        LBValue << doc.GetInt64();
                        record.insert(make_pair(LBName.str(),LBValue.str()));
                        LBName.str(std::string());
                        LBValue.str(std::string());
                    }
                    
                }
            }
            if(doc.IsNull()){
                if(useLBDebug){
                    printf(" %s = NULL ",parentVar.c_str());
                }
                if(parentVar != ""){
                    LBName << parentVar;
                }else{
                    LBName << doc.GetString();
                }
                LBValue << "Null";
                record.insert(make_pair(LBName.str(),LBValue.str()));
                LBName.str(std::string());
                LBValue.str(std::string());
            }
            if(doc.IsBool()){
                if(useLBDebug){
                    printf(" %s = %d ",parentVar.c_str(),doc.GetBool());
                }
                if(parentVar != ""){
                    LBName << parentVar;
                }else{
                    LBName << doc.GetString();
                }
                LBValue << doc.GetBool();
                record.insert(make_pair(LBName.str(),LBValue.str()));
                LBName.str(std::string());
                LBValue.str(std::string());
            }
            if(useLBDebug){
                printf("\n");
            }
        }
        
        string sendDataToUrl(stringstream &postValues){
            CURL *curl;
            CURLcode res;
            std::string readBuffer;
            struct curl_slist *headers=NULL;
            headers = curl_slist_append(headers, "Accept: application/json");
            
            curl = curl_easy_init();
            if(curl) {
                string url = this->getRequestUrl();
                if(useLBDebug){
                    cout << "Url to send: " << url.c_str() << endl;
                }
                string postVals = postValues.str();
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postVals.c_str());
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
                
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                
            }else{
                readBuffer = "No Data";
                error.insert(make_pair("code","1007"));
                error.insert(make_pair("message","Error initialising the request"));
                errors.insert(make_pair(errorCount,error));
            }
            if(res == 0){
                return readBuffer;
            }else{
                error.insert(make_pair("code","1008"));
                error.insert(make_pair("message","Error with sending the request"));
                errors.insert(make_pair(errorCount,error));
                errorCount++;
                return "No Data";
            }
        }
        
        string getRequestUrl(){
            if(!useDebug){
                return "https://www.sync2api.com/consumer/";
            }else{
                return "http://sync2api.linearblue.net/website/consumer";
            }
        }
        
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
        {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }
        
        void processDocument(Document::GenericDocument & doc){
            
            parentVar = "";
            
            
            if(doc.IsObject()){	// Document is a JSON value represents the root of DOM. Root can be either an object or array.
                
                this->processObject(doc);
                records.insert(make_pair(0,record));
                record.clear();
            }
            
            if(doc.IsArray()){
                //int rec = 0;
                //for (SizeType i = 0; i < 3; i++){
                for (SizeType i = 0; i < doc.Size(); i++){ // rapidjson uses SizeType instead of size_t.
                    if(useLBDebug){
                        printf("---------------- Start -------------------\n\n");
                    }
					const rapidjson::Value& membersObj = doc[i];
                    assert(membersObj.IsObject());
                    this->processObject(membersObj);
                    records.insert(make_pair(i,record));
                    record.clear();
                    if(useLBDebug){
                        printf("---------------- End -------------------\n\n");
                    }
                }
            }
        }
        
        void addComplexPropertyToRequestList(){
            if(useLBDebug){
                cout << complexProperty.size() << endl;
            }
            stringstream setProperty;
            for(std::vector<int>::size_type i = 0; i != complexProperty.size(); i++) {
                if((i + 1) == complexProperty.size()){
                    this->setProperty(setProperty.str(), complexProperty[i]);
                    setProperty << "=" << complexProperty[i];
                }else{
                    if(i == 0){
                        setProperty << complexProperty[i];
                    }else{
                        setProperty << "[" << complexProperty[i] << "]";
                    }
                    
                }
                
            }
            complexProperty.clear();
            if(useLBDebug){
                cout << setProperty.str() << endl;
            }
        }
        
        bool init = false;
    public:
        
        bool useDebug = false;
        bool useLBDebug = false;
        int errorCount = 0;
        stringstream LBOutput;
        stringstream LBName;
        stringstream LBValue;
        string parentVar;
        string module = "";
        string method = "";
        string cKey = "";
        string scKey = "";
        map<int,map<string,string>> records;
        map<string,string> record = *new map<string,string>() ;
        map<int,map<string,string>> errors;
        map<string,string> error = *new map<string,string>() ;
        map<string,string> postVars = *new map<string,string>() ;
        vector<string> complexProperty;
        
        LBJSONRenderFM(){
            init = true;
            this->setProperty("outputType","json");
        }
        LBJSONRenderFM(const LBJSONRenderFM & jO){
            init = true;
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
        
       LBJSONRenderFM & operator = (const LBJSONRenderFM & jO) const;
        
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
        
        stringstream getRecordVarNames()
        {
            stringstream recordVarNames;
            map<string,string>::iterator it;
            map<string,string> rec = this->getAllProperties(0);
            
            for ( it=rec.begin() ; it != rec.end(); it++ ) {
                    recordVarNames <<  (*it).first << "\n";
            }
            return recordVarNames;
        }
        
        stringstream getRecordVarNames(int recNum)
        {
            stringstream recordVarNames;
            map<string,string>::iterator it;
            map<string,string> rec = this->getAllProperties(recNum);
            
            for ( it=rec.begin() ; it != rec.end(); it++ ) {
                recordVarNames <<  (*it).first << "\n";
            }
            return recordVarNames;
        }
        
        void printRecords()
        {
            map<int,map<string,string>>::iterator it;
            map<string,string>::iterator inner_it;
            
            for ( it=records.begin() ; it != records.end(); it++ ) {
                if(useLBDebug){
                    cout << "\n\nNew record\n" << (*it).first << endl;
                }
                for( inner_it=(*it).second.begin(); inner_it != (*it).second.end(); inner_it++){
                    if(useLBDebug){
                        cout << (*inner_it).first << " => " << (*inner_it).second << endl;
                    }
                }
            }
        }
        
        void printErrors()
        {
            map<int,map<string,string>>::iterator it;
            map<string,string>::iterator inner_it;
            
            for ( it=errors.begin() ; it != errors.end(); it++ ) {
                if(useLBDebug){
                    cout << "\n\nNew record\n" << (*it).first << endl;
                }
                for( inner_it=(*it).second.begin(); inner_it != (*it).second.end(); inner_it++){
                    if(useLBDebug){
                        cout << (*inner_it).first << " => " << (*inner_it).second << endl;
                    }
                }
            }
        }
        
        bool hasErrors(){
            if(errors.size() > 0){
                return true;
            }else{
                return false;
            }
        }
        
        string getErrors()
        {
            map<int,map<string,string>>::iterator it;
            map<string,string>::iterator inner_it;
            stringstream errorOutput;
            if(errors.size() > 0){
                for ( it=errors.begin() ; it != errors.end(); it++ ) {
                
                    for( inner_it=(*it).second.begin(); inner_it != (*it).second.end(); inner_it++){
                        
                            errorOutput << (*inner_it).first << " => " << (*inner_it).second << "\n";
                        
                    }
                errorOutput << "\n\n";
            }
            
                return errorOutput.str();
            }else{
                return "No Errors";
            }
        }
        
        string getRecordCount(){
            stringstream size;
            size << records.size();
            return size.str();
        }
        
        string getProperty(int rec,string prop){
            return records[rec].find(prop)->second;
        }
        
        map<string,string> getAllProperties(int rec){
            return records[rec];
        }
        
        void setLBDebug(bool t){
            useLBDebug = t;
        }
        
        void setModule(string mod){
            module = mod;
        }
        
        void setMethod(string meth){
            method = meth;
        }
        
        void setProperty(string name,string value){
            postVars.insert(make_pair(name,value));
        }
        
        void setLicenceKeys(string cK,string scK){
            cKey = cK;
            scKey = scK;
        }
        
        void setDebug(string debug){
            if(debug == "true" || debug == "yes"){
                useDebug = true;
            }else{
                useDebug = false;
            }
        }
        
        void printRequestVars(){
            stringstream postVals;
            map<string,string>::iterator it;
            for ( it=postVars.begin(); it != postVars.end(); it++ ) {
                if(it == postVars.begin()){
                    postVals << (*it).first << "=" << (*it).second;
                }else{
                    if(it != postVars.end()){
                        postVals << "&" << (*it).first << "=" << (*it).second;
                    }else{
                        postVals << (*it).first << "=" << (*it).second;
                    }
                }
            }
            if(useLBDebug){
                cout << postVals.str() << endl;
            }
        }
        
        void clearRequest(){
            postVars.clear();
            this->setProperty("outputType","json");
            errors.clear();
            errorCount = 0;
        }
        
        void sendRequest(){
            records.clear();
            Document document;
            stringstream postVals;
            if(cKey == ""){
                error.insert(make_pair("code","1001"));
                error.insert(make_pair("message","sKey licence key is missing"));
                errors.insert(make_pair(errorCount,error));
                errorCount++;
            }
            if(scKey == ""){
                error.insert(make_pair("code","1002"));
                error.insert(make_pair("message","scKey licence key is missing"));
                errors.insert(make_pair(errorCount,error));
                error.clear();
                errorCount++;
            }
            if(module == ""){
                error.insert(make_pair("code","1003"));
                error.insert(make_pair("message","Module type is missing"));
                errors.insert(make_pair(errorCount,error));
                error.clear();
                errorCount++;
            }
            if(method == ""){
                error.insert(make_pair("code","1004"));
                error.insert(make_pair("message","Method is missing"));
                errors.insert(make_pair(errorCount,error));
                error.clear();
                errorCount++;
            }
            this->setProperty("cKey",cKey);
            this->setProperty("scKey",scKey);
            this->setProperty("module",module);
            this->setProperty("method",method);
            this->setProperty("appName","FileMaker");
            
            map<string,string>::iterator it;
            
            for ( it=postVars.begin(); it != postVars.end(); it++ ) {
                if(it == postVars.begin()){
                    postVals << (*it).first << "=" << (*it).second;
                }else{
                    if(it != postVars.end()){
                        postVals << "&" << (*it).first << "=" << (*it).second;
                    }else{
                        postVals << (*it).first << "=" << (*it).second;
                    }
                }
            }
            
            if(useLBDebug){
                this->printRequestVars();
            }
            
            string data = this->sendDataToUrl(postVals);
            cout << data << endl;
            const char *json = data.c_str();
            #if 0
            // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
                if (document.Parse<0>(json).HasParseError()){
                
                    error.insert(make_pair("code","1005"));
                    error.insert(make_pair("message","Faild to Parse JSON object"));
                    errors.insert(make_pair(errorCount,error));
                    errorCount++;
                
                }
            #else
            // In-situ parsing, decode strings directly in the source string. Source must be string.
            
                char *buffer;
                buffer = const_cast<char *>(json);
            
                if (document.ParseInsitu<0>(buffer).HasParseError()){
                
                    error.insert(make_pair("code","1006"));
                    error.insert(make_pair("message","Faild to Parse JSON object"));
                    errors.insert(make_pair(errorCount,error));
                    error.clear();
                    errorCount++;
                }
            #endif
            
            if(errorCount ==0){
                this->processDocument(document);
                if(useLBDebug){
                    this->printRecords();
                }
            }else{
                if(useLBDebug){
                    cout << errorCount << endl;
                    this->printErrors();
                }
            }
            
        }
        
        void setComplexProperty(string property){
            
            complexProperty.push_back(property);
            
        }
        
        void setComplexProperty(string property , int isProperty ){
            if(isProperty ==1){
                complexProperty.push_back(property);
                
                this->addComplexPropertyToRequestList();
            }else{
                error.insert(make_pair("code","1007"));
                error.insert(make_pair("message","Faild to set value for complex property"));
                errors.insert(make_pair(errorCount,error));
                error.clear();
                errorCount++;
            }
            
        }
        
        
        
        
        
        
        
        
    };
}


#endif
