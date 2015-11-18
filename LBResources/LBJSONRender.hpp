/*
 * LBJSONRender.h
 *
 *  Created on: Jun 18, 2014
 *      Author: Warren Tucker
 *       Email: warren.tucker@linearblue.com; wtucker1664@me.com
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
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include "document.h"		// rapidjson's DOM-style API
#include "prettywriter.h"	// for stringify JSON
#include "filestream.h"	// wrapper of C stream for prettywriter as output
using namespace std;
using namespace rapidjson;
using namespace boost;
#ifndef LBJSONRENDER_H_
#define LBJSONRENDER_H_


namespace LB{
	class LBJSONRender{
		stringstream LBOutput;
		void processLevel1(Document::GenericDocument & doc,const char *name){
			if(doc.HasMember(name)){
				bool intDone = false;

				if(doc[name].IsString()){
					LBOutput << name << ":" << doc[name].GetString() << "\n";
				}

				if(doc[name].IsBool()){
					string boolVal =  doc[name].GetBool()? "true" : "false";
					LBOutput << name << ":" << boolVal << "\n";
				}

				if(doc[name].IsNumber()){
					if(doc[name].IsInt()){
						if(!intDone){
							string Text = boost::lexical_cast<string>(doc[name].GetInt());
							LBOutput << name << ":" << Text << "\n";
							intDone = true;
						}
					}
					if(doc[name].IsDouble()){
						string Text = boost::lexical_cast<string>(doc[name].GetDouble());
						LBOutput << name << ":" << Text << "\n";
					}
					if(doc[name].IsInt64()){
						if(!intDone){
							string Text = boost::lexical_cast<string>(doc[name].GetInt64());
							LBOutput << name << ":" << Text << "\n";
							intDone = true;
						}
					}
				}
				if(doc[name].IsNull()){
					string nullVal = doc[name].IsNull() ? "null" : "?";
					LBOutput << name << ":" << nullVal << "\n";
				}
			}

		}
		void processLevel2(Document::GenericDocument & doc,vector<string> strsig){
			if(doc[strsig[0].c_str()].HasMember(strsig[1].c_str())){
				bool intDone = false;

				if(doc[strsig[0].c_str()][strsig[1].c_str()].IsString()){
					LBOutput << strsig[1].c_str() << ":" << doc[strsig[0].c_str()][strsig[1].c_str()].GetString() << "\n";
				}

				if(doc[strsig[0].c_str()][strsig[1].c_str()].IsBool()){
					string boolVal =  doc[strsig[0].c_str()][strsig[1].c_str()].GetBool()? "true" : "false";
					LBOutput << strsig[1].c_str() << ":" << boolVal << "\n";
				}

				if(doc[strsig[0].c_str()][strsig[1].c_str()].IsNumber()){
					if(doc[strsig[0].c_str()][strsig[1].c_str()].IsInt()){
						if(!intDone){
							string Text = boost::lexical_cast<string>(doc[strsig[0].c_str()][strsig[1].c_str()].GetInt());
							LBOutput << strsig[1].c_str() << ":" << Text << "\n";
							intDone = true;
						}
					}
					if(doc[strsig[0].c_str()][strsig[1].c_str()].IsDouble()){
						string Text = boost::lexical_cast<string>(doc[strsig[0].c_str()][strsig[1].c_str()].GetDouble());
						LBOutput << strsig[1].c_str() << ":" << Text << "\n";
					}
					if(doc[strsig[0].c_str()][strsig[1].c_str()].IsInt64()){
						if(!intDone){
							string Text = boost::lexical_cast<string>(doc[strsig[0].c_str()][strsig[1].c_str()].GetInt64());
							LBOutput << strsig[1].c_str() << ":" << Text << "\n";
							intDone = false;
						}
					}
				}
				if(doc[strsig[0].c_str()][strsig[1].c_str()].IsNull()){
					string nullVal = doc[strsig[0].c_str()][strsig[1].c_str()].IsNull() ? "null" : "?";
					LBOutput << strsig[1].c_str() << ":" << nullVal << "\n";
				}

			}
		}
		void processObject(Document::GenericDocument & doc,const char *fNames){
					vector<string> strsig;
					boost::split(strsig,fNames,boost::is_any_of(","));

					if(strsig.size() > 1){

						for(size_t m = 0; m < strsig.size(); m++){


							vector<string> strsig1;
							boost::split(strsig1,strsig[m],boost::is_any_of(":"));

							if(strsig1.size() == 2){

								this->processLevel2(doc,strsig1);

							}else if(strsig1.size() == 3){
								//jObject.jsonLevel3(strsig1);
							}else if(strsig1.size() == 4){
								//jObject.jsonLevel4(strsig1);
							}else{

								this->processLevel1(doc,strsig[m].c_str());

							}
							strsig1.clear();






						}
						strsig.clear();
					}else{
						this->processLevel1(doc,fNames);
					}


				}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *
 * 		Processing of JSON Root Document Arrays
 *
 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void processArray(Document::GenericDocument & doc,const char *fNames,SizeType i){
			vector<string> strsig;
			boost::split(strsig,fNames,boost::is_any_of(","));

			if(strsig.size() > 1){

				for(size_t m = 0; m < strsig.size(); m++){


					vector<string> strsig1;
					boost::split(strsig1,strsig[m],boost::is_any_of(":"));

					if(strsig1.size() == 2){

						this->processLevel2(doc,strsig1,i);

					}else if(strsig1.size() == 3){
						//jObject.jsonLevel3(strsig1);
					}else if(strsig1.size() == 4){
						//jObject.jsonLevel4(strsig1);
					}else{

						this->processLevel1(doc,strsig[m].c_str(),i);

					}
					strsig1.clear();






				}
				strsig.clear();
			}else{
				this->processLevel1(doc,fNames,i);
			}
		}
		void processLevel1(Document::GenericDocument & doc,const char *name,SizeType i){
					if(doc[i].HasMember(name)){
						bool intDone = false;

						if(doc[i][name].IsString()){
							LBOutput << name << ":" << doc[i][name].GetString() << "\n";
						}

						if(doc[i][name].IsBool()){
							string boolVal =  doc[i][name].GetBool()? "true" : "false";
							LBOutput << name << ":" << boolVal << "\n";
						}

						if(doc[i][name].IsNumber()){
							if(doc[i][name].IsInt()){
								if(!intDone){
									string Text = boost::lexical_cast<string>(doc[i][name].GetInt());
									LBOutput << name << ":" << Text << "\n";
									intDone = true;
								}
							}
							if(doc[i][name].IsDouble()){
								string Text = boost::lexical_cast<string>(doc[i][name].GetDouble());
								LBOutput << name << ":" << Text << "\n";
							}
							if(doc[i][name].IsInt64()){
								if(!intDone){
									string Text = boost::lexical_cast<string>(doc[i][name].GetInt64());
									LBOutput << name << ":" << Text << "\n";
									intDone = true;
								}
							}
						}
						if(doc[i][name].IsNull()){
							string nullVal = doc[i][name].IsNull() ? "null" : "?";
							LBOutput << name << ":" << nullVal << "\n";
						}
					}

				}
		void processLevel2(Document::GenericDocument & doc,vector<string> strsig,SizeType i){
					if(doc[i][strsig[0].c_str()].HasMember(strsig[1].c_str())){

						bool intDone = false;

						if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsString()){
							LBOutput << strsig[0].c_str() << "_" << strsig[1].c_str() << ":" << doc[i][strsig[0].c_str()][strsig[1].c_str()].GetString() << "\n";
						}

						if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsBool()){
							string boolVal =  doc[i][strsig[0].c_str()][strsig[1].c_str()].GetBool()? "true" : "false";
							LBOutput << strsig[0].c_str() << "_" << strsig[1].c_str() << ":" << boolVal << "\n";
						}

						if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsNumber()){

							if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsInt()){
								if(!intDone){
									string Text = boost::lexical_cast<string>(doc[i][strsig[0].c_str()][strsig[1].c_str()].GetInt());
									LBOutput << strsig[1].c_str() << ":" << Text << "\n";
									intDone = true;
								}
							}
							if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsDouble()){
								string Text = boost::lexical_cast<string>(doc[i][strsig[0].c_str()][strsig[1].c_str()].GetDouble());
								LBOutput << strsig[0].c_str() << "_" << strsig[1].c_str() << ":" << Text << "\n";
							}
							if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsInt64()){
								if(!intDone){
									string Text = boost::lexical_cast<string>(doc[i][strsig[0].c_str()][strsig[1].c_str()].GetInt64());
									LBOutput << strsig[0].c_str() << "_" << strsig[1].c_str() << ":" << Text << "\n";
									intDone = false;
								}
							}
						}
						if(doc[i][strsig[0].c_str()][strsig[1].c_str()].IsNull()){
							string nullVal = doc[i][strsig[0].c_str()][strsig[1].c_str()].IsNull() ? "null" : "?";
							LBOutput << strsig[0].c_str() << "_" << strsig[1].c_str() << ":" << nullVal << "\n";
						}

					}
				}
	public:
		void processDocument(Document::GenericDocument & doc,const char *fNames){
			if(doc.IsObject()){	// Document is a JSON value represents the root of DOM. Root can be either an object or array.

				this->processObject(doc,fNames);
			}

			if(doc.IsArray()){
				for (SizeType i = 0; i < doc.Size(); i++){ // rapidjson uses SizeType instead of size_t.
					this->processArray(doc,fNames,i);
                    LBOutput << "\r";
				}
			}
		}



		string getOutput(){
			return LBOutput.str();
		}

	};
}


#endif /* LBJSONRENDER_H_ */
