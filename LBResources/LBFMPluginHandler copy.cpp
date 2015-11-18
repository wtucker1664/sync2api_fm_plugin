//
//  LBFMPluginHandler.cpp
//  PlugInTemplate
//
//  Created by Warren Tucker on 21/03/2014.
//
//

#include "LBFMPluginHandler.h"
using namespace std;
using namespace rapidjson;
using namespace boost;
using namespace LB;
std::string consumerKey = "";
std::string consumerSecretKey = "";
std::string GetCalc(std::string calc, const fmx::ExprEnv& environment, fmx::Data& result) {
	fmx::TextAutoPtr tempText;
	tempText->Assign(calc.c_str(), fmx::Text::kEncoding_UTF8);
	environment.Evaluate(*tempText, result);
	return GetTextAsString(result.GetAsText());
}

std::string GetTextAsString (const fmx::Text& source) {
	fmx::uint64			len=0;
	fmx::TextAutoPtr	tempText;
	
	// Pull URL as char buffer out of FMX::Data and make into CFStringRef
	tempText->SetText(source);
	len = (tempText->GetSize()*3)+1 ; // The max len of the UTF8 string can three times the size of the string. So make room for it.
	char * param1 = (char*)malloc(sizeof(char)*len); //Allocate the memory you need for the string
	memset(param1, 0, sizeof(char)*len);//You do not have to do this but it will amke sure the string is clean
	tempText->GetBytes(param1, len, 0, len, fmx::Text::kEncoding_UTF8); //I'm getting the Data out as UTF8.
	std::string result = "ERR Unable to get string data";
	if(param1) {
		result.assign(param1);
		free(param1);
		param1 = NULL;
	}
	return result;
}

std::string convertLongToString(long input) {
	std::stringstream buf;
	buf<<input;
	return buf.str();
}



static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string getDataFromUrl(std::stringstream &url){
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    
    curl = curl_easy_init();
    if(curl) {
        url << "&outputType=json";
        std::string urlText = url.str();
        
	    curl_easy_setopt(curl, CURLOPT_URL, urlText.c_str());
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
        
	    res = curl_easy_perform(curl);
	    curl_easy_cleanup(curl);
        
    }else{
        readBuffer = "No Data";
        
    }
    return readBuffer;
}

std::string sendDataToUrl(std::stringstream &postValues){
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    struct curl_slist *headers=NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    
    curl = curl_easy_init();
    if(curl) {
        postValues << "&outputType=json";
        
        std::string postVal = postValues.str();
	    curl_easy_setopt(curl, CURLOPT_URL, SYNC2APIPOST_URL);
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postVal.c_str());
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
        
	    res = curl_easy_perform(curl);
	    curl_easy_cleanup(curl);
        
    }else{
        readBuffer = "No Data";
        
    }
    return readBuffer;
}

std::string getDataForFileMaker(std::string response,const char *vNames){
    const char *json = response.c_str();
    std::string error = "Unable to get data";
    Document document;	// Default template parameter uses UTF8 and MemoryPoolAllocator.
    // In-situ parsing, decode strings directly in the source string. Source must be string.
    
    char *buffer;
    buffer = const_cast<char *>(json);
    
    if (document.ParseInsitu<0>(buffer).HasParseError()){
        
        return response;
    }

    
    LBJSONRender jObject;
    
    jObject.processDocument(document,vNames);
    
    
    return jObject.getOutput();
    
}

std::string createPostString(std::string pNames){
    std::stringstream postValues;
    vector<string> strsig;
    boost::split(strsig,pNames,boost::is_any_of(","));
    
    if(strsig.size() > 1){
        
        for(size_t m = 0; m < strsig.size(); m++){
            vector<string> strsig1;
            boost::split(strsig1,strsig[m],boost::is_any_of(":,::,|,||,[]"));
            
            if(strsig1.size() == 2){
                
                
                postValues << "&" << strsig1[0].c_str() << "=" << strsig1[1].c_str();
                
            }
        }
        
    }
    
    return postValues.str();
}

/*
 
 Code from Jason to set variables back into filemaker.
 
 
 string varName = 	"CompanyID";
 string value = 	"100";
 fmx::TextAutoPtr setVariable;
 setVariable->Assign("Let ( $" + varName + "=\"" + value + "\" ; 1 )";
 environment.Evaluate(*getDate, result);
 
 */

