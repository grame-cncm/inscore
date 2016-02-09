/*
  INScore Project

  Copyright (C) 2009,2016  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/

#include <sstream>

#include "GmnEvaluator.h"
#include "IGuidoCode.h"
#include "IGuidoPianoRollFile.h"
#include "libguidoar.h"
#include "QGuidoImporter.h"

using namespace std;

namespace inscore{

#define GUIDOAR_OPERATOR(guidoOperator) [](const std::string& str1, const std::string& str2, bool &success) -> const std::string						\
											{																		\
											std::ostringstream oss;													\
											guido::garErr err = guidoOperator( str1.c_str(), str2.c_str(), oss );	\
											success = err == guido::kNoErr;											\
											if ( success ){															\
												return oss.str();													\
											}return "";																\
											}



GmnEvaluator::GmnEvaluator(const IObject *contextObject): ExprEvaluator("GmnEvaluator",contextObject, gOperators)
{
}


//_____________________________________________________
const OperatorList GmnEvaluator::gmnOperators()
{
	std::unordered_map<std::string, OperatorCb> operatorMap;
	operatorMap.insert({"seq",		GUIDOAR_OPERATOR(guido::guidoGSeq)});
	operatorMap.insert({"par",		GUIDOAR_OPERATOR(guido::guidoGPar)});
	operatorMap.insert({"rpar",		GUIDOAR_OPERATOR(guido::guidoGRPar)});
	operatorMap.insert({"head",		GUIDOAR_OPERATOR(guido::guidoGHead)});
	operatorMap.insert({"evhead",	GUIDOAR_OPERATOR(guido::guidoGEHead)});
	operatorMap.insert({"tail",		GUIDOAR_OPERATOR(guido::guidoGTail)});
	operatorMap.insert({"evtail",	GUIDOAR_OPERATOR(guido::guidoGETail)});
	operatorMap.insert({"duration",	GUIDOAR_OPERATOR(guido::guidoGSetDuration)});
	operatorMap.insert({"transpose",GUIDOAR_OPERATOR(guido::guidoGTranpose)});
	operatorMap.insert({"top",		GUIDOAR_OPERATOR(guido::guidoGTop)});
	operatorMap.insert({"bottom",	GUIDOAR_OPERATOR(guido::guidoGBottom)});
	operatorMap.insert({"rhythm",	[](const std::string& str1, const std::string& str2, bool &success) -> const std::string
						{
							std::ostringstream oss;
							guido::garErr err = guido::guidoApplyRythm( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, oss );
							success = err == guido::kNoErr;
							if ( success )
								return oss.str();
							else
								return "";
						} });
	operatorMap.insert({"pitch",	[] (const std::string& str1, const std::string& str2, bool &success) -> const std::string
						{
							std::ostringstream oss;
							guido::garErr err = guido::guidoApplyPitch( str1.c_str(), str2.c_str(), guido::kApplyForwardLoop, guido::kUseLowest, oss );
							success = err == guido::kNoErr;
							if ( success )
								return oss.str();
							else
								return "";
						} });
	return operatorMap;
}
const OperatorList GmnEvaluator::gOperators = GmnEvaluator::gmnOperators();


//_____________________________________________________
const std::string GmnEvaluator::eval(const IObject *arg)
{
    const IGuidoCode* guido = dynamic_cast<const IGuidoCode*>(arg);
    if(!guido){
		ITLErr << evaluatorName() <<": the object "<<arg->name()<<" is not a guido object"<<ITLEndl;
		return fEvalStatus.fail();
    }

	const IGuidoPianoRollFile* pianoRollFile = dynamic_cast<const IGuidoPianoRollFile*>(arg);
	if(pianoRollFile)
		if(pianoRollFile->isMidiFile()){
			ITLErr << evaluatorName() <<": a guido file was expected but the pianoroll \""<<arg->name()<<"\" is a  midi file."<<ITLEndl;
			return fEvalStatus.fail();
		}


	return guido->getCleanGMN();
}


//_____________________________________________________
const string GmnEvaluator::eval(const string &arg, const IExprArgBase *)
{
	std::string gmn = arg;
	if(isXml(arg)){
		if(!QGuidoImporter::musicxmlSupported()){
			ITLErr<< evaluatorName() << ": MusicXML import is not available"<<ITLEndl;
			return fEvalStatus.fail();
		}

		//Converting MusicXML to GMN
		std::stringstream sstr;
		if(!QGuidoImporter::musicxmlString2Guido ( arg.c_str(), true, sstr)){
			ITLErr<< evaluatorName() << ": Cannot convert MusicXML to GMN."<<ITLEndl;
			return fEvalStatus.fail();
		}

		gmn = sstr.str();
	}


	return gmn;
}

//_____________________________________________________
bool GmnEvaluator::isXml(const string &score) const
{
	auto it = score.begin();
	while(it!=score.end()){
		if(*it=='<')
			return true;
		else if(*it == ' ' || *it ==' ' || *it=='\t' || *it=='\n')
			it++;
		else
			return false;
	}
	return false;
}


} //end namespace
