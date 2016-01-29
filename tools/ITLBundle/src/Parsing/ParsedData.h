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

	void renameRsc(std::string search, std::string replace);
};

//_____________________________________________________
class ParsedData{
public:

	TScripts scripts;
	RessourceMap scriptsRessources;
	RessourceMap ressources;
	std::string mainPath="";

	inscore::extvector<std::string> scriptNames() const;
	inscore::extvector<std::string> ressourceNames() const;

	bool isMainScript(std::string scriptName){return fMainScript==scriptName;}
	void setMainScript(std::string name){fMainScript = name;}

	void applyNameMap(std::map<std::string, std::string> nameMap);
	std::string generateScript(std::string name);

	void simplifyPaths(int charToDelete);

	static size_t findFileInJS(const std::string& js, std::string& filePath, size_t startID = 0);
	static bool isFilePath(std::string string);

protected:
	std::string fMainScript;

};



//_____________________________________________________
class MsgParam: public libmapping::smartable{
protected:
	inscore::SIMessage fMsg;
	int fParamID;

public:
	MsgParam(inscore::SIMessage msg, int paramID);
	virtual void setValue(const std::string &value);
	virtual std::string getValue() const;
};

//_____________________________________________________
class ExprParam: public MsgParam{
	std::string fInitialValue;

public:
	ExprParam(inscore::SIMessage msg, int paramID, std::string initialValue);
	virtual void setValue(const std::string &value);
	virtual std::string getValue() const;
};

//_____________________________________________________
class JsParam: public MsgParam{
	std::string fPath;

public:
	JsParam(inscore::SIMessage msg, std::string path);
	virtual void setValue(const std::string &value);
	virtual std::string getValue() const;
};

} // End namespace

#endif // PARSEDDATA_H
