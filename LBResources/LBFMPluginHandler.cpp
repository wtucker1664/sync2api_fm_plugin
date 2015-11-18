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
LBJSONRenderFM *jObject;
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

LBJSONRenderFM* getObject(){
    if(jObject == nullptr){
        jObject = new LBJSONRenderFM;
        return jObject;
    }else{
        return jObject;
    }
    
    
}

std::wstring utf8_to_utf16(const std::string& utf8)
{
    std::vector<unsigned long> unicode;
    size_t i = 0;
    while (i < utf8.size())
    {
        unsigned long uni;
        size_t todo;
        bool error = false;
        unsigned char ch = utf8[i++];
        if (ch <= 0x7F)
        {
            uni = ch;
            todo = 0;
        }
        else if (ch <= 0xBF)
        {
            throw std::logic_error("not a UTF-8 string");
        }
        else if (ch <= 0xDF)
        {
            uni = ch&0x1F;
            todo = 1;
        }
        else if (ch <= 0xEF)
        {
            uni = ch&0x0F;
            todo = 2;
        }
        else if (ch <= 0xF7)
        {
            uni = ch&0x07;
            todo = 3;
        }
        else
        {
            throw std::logic_error("not a UTF-8 string");
        }
        for (size_t j = 0; j < todo; ++j)
        {
            if (i == utf8.size())
                throw std::logic_error("not a UTF-8 string");
            unsigned char ch = utf8[i++];
            if (ch < 0x80 || ch > 0xBF)
                throw std::logic_error("not a UTF-8 string");
            uni <<= 6;
            uni += ch & 0x3F;
        }
        if (uni >= 0xD800 && uni <= 0xDFFF)
            throw std::logic_error("not a UTF-8 string");
        if (uni > 0x10FFFF)
            throw std::logic_error("not a UTF-8 string");
        unicode.push_back(uni);
    }
    std::wstring utf16;
    for (size_t i = 0; i < unicode.size(); ++i)
    {
        unsigned long uni = unicode[i];
        if (uni <= 0xFFFF)
        {
            utf16 += (wchar_t)uni;
        }
        else
        {
            uni -= 0x10000;
            utf16 += (wchar_t)((uni >> 10) + 0xD800);
            utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
        }
    }
    return utf16;
}

