/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>


#include "ISignalNode.h"
#include "IMessage.h"
#include "ISignal.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
// signals node
//--------------------------------------------------------------------------
const string ISignalNode::kName			= "signal";

//--------------------------------------------------------------------------
ISignalNode::ISignalNode(IObject * parent) : IVNode(kName, parent), fDebug(false)
{
	fGetMsgHandlerMap["debug"]	= TGetParamMsgHandler<bool>::create(fDebug);
	fMsgHandlerMap["debug"]		= TSetMethodMsgHandler<ISignalNode, bool>::create(this,&ISignalNode::debug);
	fMsgHandlerMap[kwatch_GetSetMethod]		= 0L;
	fMsgHandlerMap[kwatchplus_SetMethod]	= 0L;
    
    fMsgHandlerMap[kconnect_GetSetMethod]	= TMethodMsgHandler<ISignalNode>::create(this, &ISignalNode::connectMsg);
	fMsgHandlerMap[kdisconnect_SetMethod]   = TMethodMsgHandler<ISignalNode>::create(this, &ISignalNode::disconnectMsg);
}

//--------------------------------------------------------------------------
void ISignalNode::accept (Updater* u)
{
	u->updateTo (SISignalNode(this));
}

//--------------------------------------------------------------------------
void ISignalNode::print (ostream& out) const
{
	out << "  signal node :" << endl; // << elements();	
}

//--------------------------------------------------------------------------
bool ISignalNode::find (std::string node, subnodes& outlist)
{
	size_t n = node.find ('/');
	if (n == string::npos)
		return exactfind(node, outlist);

	bool ret = false;
	string name = node.substr(0, n);
	int index = atoi (node.substr (n+1, node.size()).c_str());
	subnodes sigs;
	if (exactfind(name, sigs)) {
		for (unsigned int n=0; n<sigs.size(); n++) {
			ISignal* sig = dynamic_cast<ISignal*>((IObject*)sigs[n]);
			if (sig  && (index < sig->dimension())) {
				SISignal s = ISignal::create(node, this);
				*s << sig->signal(index);
				outlist.push_back(s);
				ret = true;
			}
		}
	}
	return ret;
}

//--------------------------------------------------------------------------
//SISignal ISignalNode::find (std::string node) const
//{
//	SIObject o = exactfind(node);
//	return dynamic_cast<ISignal*>((IObject*)o);
//}

//--------------------------------------------------------------------------
bool ISignalNode::debug(int state)
{
	if (state < 0) return false;
	fDebug = state ? true : false;
	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::connectMsg (const IMessage* msg)
{
	int n = msg->size();
    if(n < 2) return MsgHandler::kBadParameters;
    
    std::string signalStr, objectsParameterStr, objectStr;
    if(!msg->param(0, signalStr)) return MsgHandler::kBadParameters;
    
    subnodes signalList;
    if(!find(signalStr, signalList)) return MsgHandler::kBadParameters;
    IObject* sig = signalList[0];
    ISignal* signal = dynamic_cast<ISignal*>(sig);
    
    if(!signal) return MsgHandler::kBadParameters;
    
    MsgHandler::msgStatus result;
    for(int i = 1; i<n; i++)
    {
        if(!msg->param(i, objectsParameterStr)) return MsgHandler::kBadParameters;
        objectStr = objectsParameterStr.substr(0,objectsParameterStr.find(":"));
        subnodes objectList;
        if(!getParent()->find(objectStr, objectList)) return MsgHandler::kBadParameters;
        std::string methods = objectsParameterStr.substr(objectsParameterStr.find(":")+1);
        result = connect(signal, objectStr, methods);
        if(result != MsgHandler::kProcessed) return result;
    }
    return result;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::disconnectMsg (const IMessage* msg)
{
	int n = msg->size();
    if(!n) return MsgHandler::kBadParameters;
    
    std::string signalStr;
    if(!msg->param(0, signalStr)) return MsgHandler::kBadParameters;
    
    subnodes signalList;
    if(!find(signalStr, signalList)) return MsgHandler::kBadParameters;
    IObject* sig = signalList[0];
    ISignal* signal = dynamic_cast<ISignal*>(sig);
    
    if(!signal) return MsgHandler::kBadParameters;
    
    if(n == 1)
        return disconnect(signal);
    
    std::string objectMethodsStr, objectStr;
    MsgHandler::msgStatus result;
    for(int i = 1; i<n; i++)
    {
        if(!msg->param(i, objectMethodsStr)) return MsgHandler::kBadParameters;
        objectStr = objectMethodsStr.substr(0,objectMethodsStr.find(":"));
        subnodes objectList;
        if(!getParent()->find(objectStr, objectList)) return MsgHandler::kBadParameters;
    
        std::string methods = objectMethodsStr.substr(objectMethodsStr.find(":")+1);
        result = disconnect(signal, objectStr, methods);
        if(result != MsgHandler::kProcessed) return result;
    }
    return result;
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::connect(SParallelSignal signal, std::string object, std::string methods)
{
    std::string allMethodStr = methods;
    std::string methodStr;
    std::string range = "";
    std::string objectMethod;
    int i = allMethodStr.find(":");
    while(i != allMethodStr.npos)
    {
        methodStr = allMethodStr.substr(0,i);
        if(methodStr.find("[") != methodStr.npos)
        {
            range = methodStr.substr(methodStr.find("["));
            methodStr = methodStr.substr(0, methodStr.find("["));
        }
        else
            range = "";
        objectMethod = object;
        objectMethod += ":";
        objectMethod += methodStr;
        std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator it = fConnections.find(objectMethod);
        if(it != fConnections.end()) // If this attribute of the object has already been stored, we replace the corresponding signal
        {
            it->second.first = signal;
            it->second.second = range;
        }
        else
            fConnections.insert(std::pair<std::string, std::pair<SParallelSignal, std::string> >(objectMethod, std::pair<SParallelSignal, std::string>(signal, range)));
        allMethodStr = allMethodStr.substr(i+1);
        i = allMethodStr.find(":");
    }
    
    if(allMethodStr.find("[") != allMethodStr.npos)
    {
        range = allMethodStr.substr(allMethodStr.find("["));
        allMethodStr = allMethodStr.substr(0, allMethodStr.find("["));
    }
    else
        range = "";
    
    objectMethod = object;
    objectMethod += ":";
    objectMethod += allMethodStr;
    
    std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator it = fConnections.find(objectMethod);
    if(it != fConnections.end()) // If this attribute of the object has already been stored, we replace the corresponding signal
    {
        it->second.first = signal;
        it->second.second = range;
    }
    else
        fConnections.insert(std::pair<std::string, std::pair<SParallelSignal, std::string> >(objectMethod, std::pair<SParallelSignal, std::string>(signal,range)));
    
    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::disconnect(SParallelSignal signal, std::string object, std::string methods)
{
    if(object.empty()) // if the method is not specified, we disconnect all connections with the signal
    {
        std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator it = fConnections.begin();
        while(it != fConnections.end())
        {
            std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator d = it;
            if(it->second.first == signal){
                fConnections.erase(d);
                it++;
            }
        }
    }
    else
    {
        std::string allMethodStr = methods;
        std::string methodStr;
        std::string objectMethod;
        int i = allMethodStr.find(":");
        while(i != allMethodStr.npos)
        {
            methodStr = allMethodStr.substr(0,i);
            objectMethod = object;
            objectMethod += ":";
            objectMethod += methodStr;
            std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator it = fConnections.find(objectMethod);
            if(it == fConnections.end())
                return MsgHandler::kBadParameters;
            else
                fConnections.erase(it);
            
            allMethodStr = allMethodStr.substr(i+1);
            i = allMethodStr.find(":");
        }
        objectMethod = object;
        objectMethod += ":";
        objectMethod += allMethodStr;
        std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator it = fConnections.find(objectMethod);
        if(it == fConnections.end())
            return MsgHandler::kBadParameters;
        else
            fConnections.erase(it);
    }
    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
std::map<std::string, std::pair<SParallelSignal, std::string> > ISignalNode::getConnectionsOf(std::string objectName)
{
    std::map<std::string, std::pair<SParallelSignal, std::string> > connections;
    std::map<std::string, std::pair<SParallelSignal, std::string> >::iterator it;
    for (it = fConnections.begin(); it != fConnections.end(); it++)
    {
        std::string objectsMethod = it->first; // object:method[range]
        if(objectsMethod.find(":") != std::string::npos && !objectsMethod.compare(0, objectsMethod.find(":"), objectName)) // object
        {
            std::string methods = objectsMethod.substr(objectsMethod.find(":")); // method[range]
            connections.insert(std::pair<std::string, std::pair<SParallelSignal, std::string> >(methods, it->second));
        }
    }
    return connections;
}

}
