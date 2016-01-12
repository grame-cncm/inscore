#include "ExprInfo.h"

#include "ParsedData.h"

namespace itlbundle {

inscore::extvector<std::string> ParsedData::scriptNames() const
{
	inscore::extvector<std::string> vector;
	for(auto it=scripts.begin(); it!=scripts.end(); it++)
		vector.push_back(it->first);
	return vector;
}

inscore::extvector<std::string> ParsedData::ressourceNames() const
{
	inscore::extvector<std::string> vector;
	for(auto it=ressources.begin(); it!=ressources.end(); it++)
		vector.push_back(it->first);
	return vector;
}


//__________________________________________________________
//----------------------------------------------------------
bool RessourceMap::insert(std::string name, SMsgParam param)
{
	auto it = find(name);
	if(it==end()){
		std::list<SMsgParam> l;
		l.push_back(param);
		(*this)[name] = l;
		return true;
	}

	it->second.push_back(param);
	return false;
}

void RessourceMap::insert(std::string name, std::list<SMsgParam> params)
{
	if(!params.size())
		return;

	auto it = find(name);
	if(it==end()){
		(*this)[name] = params;
		return;
	}

	for(auto itParams = params.begin(); itParams!=params.end(); itParams++)
		it->second.push_back(*itParams);

}

void RessourceMap::insert(const RessourceMap &ressources)
{
	for(auto it = ressources.begin(); it!=ressources.end(); it++)
		insert(it->first, it->second);
}


//__________________________________________________________
//----------------------------------------------------------
MsgParam::MsgParam(inscore::SIMessage msg, int paramID)
	:fMsg(msg), fParamID(paramID)
{}

void MsgParam::setValue(std::string value)
{
	fMsg->setparam<std::string>(fParamID, value);
}

std::string MsgParam::getValue() const
{
	std::string r;
	if(fMsg->param(fParamID, r))
		return r;
	return "";
}


//__________________________________________________________
//----------------------------------------------------------
ExprParam::ExprParam(inscore::SIMessage msg, int paramID, std::string initialValue)
	: MsgParam(msg,paramID), fInitialValue(initialValue)
{}

void ExprParam::setValue(std::string value){
	inscore::SIExpression expr;
	if(!fMsg->param(fParamID,expr))
		return;
	inscore::ExprInfo::fileReplace(expr, fInitialValue, value);
	fInitialValue = value;
}

std::string ExprParam::getValue() const
{
	return fInitialValue;
}





} // End namespace
