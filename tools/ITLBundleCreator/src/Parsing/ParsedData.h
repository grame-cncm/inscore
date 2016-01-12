#ifndef PARSEDDATA_H
#define PARSEDDATA_H

#include <list>
#include <map>

#include "smartpointer.h"
#include "extvector.h"
#include "IMessage.h"

namespace itlbundle{

typedef std::map<std::string,inscore::SIMessageList> TScripts;
class MsgParam;
typedef libmapping::SMARTP<MsgParam> SMsgParam;


class RessourceMap: public std::map<std::string, std::list<SMsgParam>>{
public:
	bool insert(std::string name, SMsgParam param);
	void insert(std::string name, std::list<SMsgParam> params);
	void insert(std::pair<std::string, std::list<SMsgParam> > ressource){insert(ressource.first, ressource.second);}
	void insert(const RessourceMap& ressources);
};

//_____________________________________________________
class ParsedData{
public:

	TScripts scripts;
	RessourceMap scriptsRessources;
	RessourceMap ressources;

	inscore::extvector<std::string> scriptNames() const;
	inscore::extvector<std::string> ressourceNames() const;

};



//_____________________________________________________
class MsgParam: public libmapping::smartable{
protected:
	inscore::SIMessage fMsg;
	int fParamID;

public:
	MsgParam(inscore::SIMessage msg, int paramID);
	virtual void setValue(std::string value);
	virtual std::string getValue() const;
};

//_____________________________________________________
class ExprParam: public MsgParam{
	std::string fInitialValue;

public:
	ExprParam(inscore::SIMessage msg, int paramID, std::string initialValue);
	virtual void setValue(std::string value);
	virtual std::string getValue() const;
};

} // End namespace

#endif // PARSEDDATA_H
