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
#ifndef PARSEDDATA_H
#define PARSEDDATA_H

#include <list>
#include <map>

#include "smartpointer.h"
#include "extvector.h"
#include "IMessage.h"

namespace ibundle{

typedef std::map<std::string,inscore::SIMessageList> TScripts;
typedef std::map<std::string, std::string> TStringMap;
class RessourceRef;
typedef libmapping::SMARTP<RessourceRef> SRessourceRef;

/*!
 * \brief The RessourceMap class handle the list of ressources needed by inscore scripts.
 * Each ressource is stored through a single entry in the map (using its file path as key),
 * along with a list of all the script messages that are refering to the ressource.
 * These references are stored as MsgParam so ressource can be renamed and still keep the scripts correct.
 */
class RessourceMap: public std::map<std::string, std::list<SRessourceRef>>{
public:
	std::list<SRessourceRef> &insert(std::string name, bool &newList);
	bool insert(std::string name);
	bool insert(std::string name, SRessourceRef param);
	bool insert(std::string name, std::list<SRessourceRef> params);
	void insert(std::pair<std::string, std::list<SRessourceRef> > ressource){insert(ressource.first, ressource.second);}
	void insert(const RessourceMap& ressources);

	/*!
	 * \brief Search a ressource and modify the scripts by changing its name.
	 *  However its key is not modified: thus if this ressource should be renamed again,
	 *  its initial name should be used to find it.
	 * \param search The name of the ressource to rename
	 * \param replace The new name of the ressource
	 * \return True if the ressource was found, false otherwise
	 */
	bool renameRsc(std::string search, std::string replace);
};


//_____________________________________________________
/*!
 * \brief The ParsedData class is the core container class of scripts parsing,
 *  ressources detection and files manipulation while preparing IBundle.
 *  Through these operations a single ParsedData object is used to store:
 *		- the scripts list (scripts are stored as a list of inscore messages),
 *		- the main script name
 *		- the ressources list (all the reference to ressources are stored in the RessourceMap so it can be modified later)
 *		- the files map (which associate to each file (script or ressource) its name in the archive)
 *
 *  The ParsedData object is also in charge of simplifying the filepaths it store (removing the shared rootpath).
 *  Finally the ParsedData class provides some static fonction used while compressing or uncompressing ibundle.
 */
class ParsedData{

public:
	/*!
	 * \brief Add a script to the scripts list and insert an entry for this script in the files map.
	 * \param name The path to the script file.
	 * \param msgs The msgs contained in the script.
	 */
	void addScript(std::string name, inscore::SIMessageList msgs);
	/*!
	 * \brief Add a message refering to a script (usally a load message) to the message list.
	 * \param script The script's file path. At some point, this script must be added to the script list
	 *  using the addScript method,  so it will be correctly included in the scripts list and in the files map.
	 * \param msg The message refering to the script.
	 */
	void addScriptMsg(std::string script, SRessourceRef msg);
	/*!
	 * \brief Add a message refering to a ressource to the message list and insert an entry for this ressource in the ressources list and in the files map.
	 * \param ressource The ressource's file path.
	 * \param msg The message refering to the ressource
	 */
	void addRessourceMsg(std::string ressource, SRessourceRef msg);
	/*!
	 * \brief addRessource Add a ressource in the ressources list and insert an entry for this ressources in the files map.
	 * \param name The ressource's file path.
	 */
	void addRessource(std::string name);

	/*!
	 * \brief Test if a script already exist in the scripts list. (Have been added using the addScript method).
	 * \param name The path to the script
	 */
	bool containsScript(std::string name) const ;

	/*!
	 * \brief Return the list of the names (path) of all the scripts stored in the scripts list.
	 */
	inscore::extvector<std::string> scriptNames() const;
	/*!
	 * \brief Return the list of the names (path) of all the ressources stored in the ressources list.
	 */
	inscore::extvector<std::string> ressourceNames() const;


	/*!
	 * \brief mainScript The main script attribute is used to store, during the packaging process, which script should be the main.
	 * The main script must be stored in the scripts list as any other script.
	 * A ParsedData object won't use the value of its mainScript attribute, it will only simplify it when calling the simplifyPaths() method.
	 */
	std::string mainScript;
	bool isMainScript(std::string scriptName) const {return mainScript==scriptName;}

	/*!
	 * \brief Apply a map in order to rename scripts and ressources. The messages of the scripts will be changed accordingly however none of the maps keys will be changed.
	 * \param nameMap The keys of the map must be the file path and can be aquired through filesMap(), the value must be the new paths.
	 */
	void applyFileMap(TStringMap fileMap);
	/*!
	 * \brief Return the current files map where the keys are the real paths to each file and the values are their mapped value (set with the applyNameMap() method).
	 */
	const TStringMap& filesMap() const {return fFilesMap;}

	/*!
	 * \brief Generate a definition of a script from its message list modifyied according to the files map.
	 * \param The file path of the script to generate.
	 * \return The text version of the script.
	 */
	std::string generateScript(std::string name) const;

	/*!
	 * \brief Extract the shared rootPath and simplify all the filepaths (map keys) accordingly.
	 *  The main root path is stored and can be aquired by calling mainPath().
	 */
	void simplifyPaths();
	/*!
	 * \brief Return the root path simplifyed when simplifyPath() was executed.
	 */
	const std::string& mainPath()   const {return fMainPath;}

	/*!
	 * \brief A small tools that split a string on the '/' character and return a list of string
	 */
	static std::vector<std::string> splitPath(std::string path);
	/*!
	 * \brief Find a filepath in a javascript section. Note that file paths should be alone and double quoted.
	 * \param js The javascript section to read.
	 * \param filePath The filepath found (without the double quote).
	 * \param startID The position where findFileInJS() should start to read the javascript section.
	 * \return The position where the filepath has been found (after the double quote) or std::string::npos if none was found.
	 */
	static size_t findFileInJS(const std::string& js, std::string& filePath, size_t startID = 0);
	/*!
	 * \brief Test if the given string is a valid path.
	 * To be a valid path string should follow the following RegExp:
	 *    ^/?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+$
	 */
	static bool isFilePath(std::string string);

protected:
	TScripts fScripts;
	RessourceMap fScriptsRessources;
	RessourceMap fRessources;
	TStringMap fFilesMap;

	void simplifyPaths(int charToDelete);

	std::string fMainPath="";
};



//_____________________________________________________
/*!
 * \brief The RessourceRef class stores all the informations needed to modify a parameter of a message in order to rename the ressources that it reffers to.
 */
class RessourceRef: public libmapping::smartable{
protected:
	inscore::SIMessage fMsg;
	RessourceRef(inscore::SIMessage msg): fMsg(msg) {}

public:
	/*!
	 * \brief Change the value of the ressource.
	 * \param value The new value.
	 */
	virtual void setValue(const std::string &value) = 0;
	/*!
	 * \brief Return the current value of the ressource
	 */
	virtual std::string getValue() const = 0;
};

//_____________________________________________________
/*!
 * \brief The MsgParam class subclass RessourceRef to handle ressources stored as string parameters.
 */
class MsgParam: public RessourceRef{
protected:
	int fParamID;

public:
	/*!
	 * \param msg The message refering to the ressource
	 * \param paramID The index of the string parameter that refers to the ressource
	 */
	MsgParam(inscore::SIMessage msg, int paramID);
	virtual void setValue(const std::string &value);
	virtual std::string getValue() const;
};

//_____________________________________________________
/*!
 * \brief The ExprParam class sublclass MsgParam to handle ressources stored in an IExpression.
 */
class ExprParam: public MsgParam{
	std::string fInitialValue;

public:
	/*!
	 * \param msg The message refering to the ressource
	 * \param paramID The index of the IExpression parameter that refers to the ressource
	 * \param initialPath The initial path to the ressource (it will be use to search/replace when calling setValue).
	 */
	ExprParam(inscore::SIMessage msg, int paramID, std::string initialPath);
	virtual void setValue(const std::string &value);
	virtual std::string getValue() const;
};

//_____________________________________________________
/*!
 * \brief The JsParam class subclass RessourceRef to handle ressources stored in a javascript section.
 * The ressource filepath is detected and modified using ParsedData::findFileInJS(js, filePath)
 */
class JsParam: public RessourceRef{
	std::string fPath;

public:
	/*!
	 * \param The javascript message (the first parameter must be the javascript section).
	 * \param initialPath The initial path to the ressource (it will be use to search/replace when calling setValue).
	 */
	JsParam(inscore::SIMessage msg, std::string initialPath);
	virtual void setValue(const std::string &value);
	virtual std::string getValue() const;
};

} // End namespace

#endif // PARSEDDATA_H
