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
    // We must at least have 2 parameters : the signal and at least one pair "object:method"
    if(n < 2) return MsgHandler::kBadParameters;
    
    std::string signalStr, objectsParameterStr, objectStr;
    if(!msg->param(0, signalStr)) return MsgHandler::kBadParameters;
    
    // We check if the first parameter is indeed a signal and is on our list
    subnodes signalList;
    if(!find(signalStr, signalList)) return MsgHandler::kBadParameters;
    IObject* sig = signalList[0];
    ISignal* signal = dynamic_cast<ISignal*>(sig);
    
    if(!signal) return MsgHandler::kBadParameters;
    
    // Then, for each parameter, we separate the first name (the object) and the rest of the string (one or more methods) :
    // "object:method1[range1]:method2[range2]" --> "object" + "method1[range1]:method2[range2]"
    // And for each pair of object-methods, we call connect(signal, objectStr, methods)
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
    
    // We check that the first parameter is a signal, and that it is on the list
    std::string signalStr;
    if(!msg->param(0, signalStr)) return MsgHandler::kBadParameters;
    
    subnodes signalList;
    if(!find(signalStr, signalList)) return MsgHandler::kBadParameters;
    IObject* sig = signalList[0];
    ISignal* signal = dynamic_cast<ISignal*>(sig);
    
    if(!signal) return MsgHandler::kBadParameters;
    
    // If there is only one parameter, we disconnect all connections with the signal
    if(n == 1)
        return disconnect(signal);
    
    // If we have more parameters, we distinguish each object from its list of methods and call disconnect(signal, objectStr, objectList)
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
    
    // We separate all the methods of the list, and also distinguish the method and the range, to add to the maps fConnections and fRanges :
    // "method1[range1]:method2[range2]"    --> insert in fConnections <"object:method1", signal> + <"object:method2", signal >
    //                                      --> insert in fRanges <"object:method1", range1> + <"object:method2", range2 >
    while(!allMethodStr.empty())
    {
        methodStr = allMethodStr.substr(0,i);
        
        if(i!=allMethodStr.npos)
        {
            allMethodStr = allMethodStr.substr(i+1); // rest of the string (after the ":")
            i = allMethodStr.find(":"); // next position of ":"
        }
        else
            allMethodStr = "";
        
        if(methodStr.find("[") != methodStr.npos) // "method(n)[range(n)]"
        {
            range = methodStr.substr(methodStr.find("[")); // "[range(n)]"
            methodStr = methodStr.substr(0, methodStr.find("[")); // "method(n)"
        }
        else
            range = "";
        objectMethod = object;
        objectMethod += ":";
        objectMethod += methodStr; // "object:method(n)"
        std::map<std::string, SParallelSignal >::iterator it = fConnections.find(objectMethod);
        if(it != fConnections.end()) // If this method of the object has already been stored, we replace the corresponding signal and range
        {
            it->second = signal;
            std::map<std::string, std::string>::iterator it2 = fRanges.find(objectMethod); // we actualize the connections map
            if(it2 != fRanges.end()) it2->second = range; // we actualize the ranges map
        }
        else
        {
            fConnections.insert(std::pair<std::string, SParallelSignal >(objectMethod, signal));
            fRanges.insert(std::pair<std::string, std::string>(objectMethod, range));
        }
    }

    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::disconnect(SParallelSignal signal, std::string object, std::string methods)
{
    if(object.empty()) // if the object is not specified, we disconnect all connections with the signal
    {
        std::map<std::string, SParallelSignal >::iterator it = fConnections.begin();
        while(it != fConnections.end())
        {
            if(it->second == signal) // if we find the signal, we erase the pair corresponding to the object:attribute in the Connections and in the Ranges
            {
                std::map<std::string, std::string>::iterator it2 = fRanges.find(it->first);
                if (it2 != fRanges.end())
                    fRanges.erase(it2);
                std::map<std::string, SParallelSignal>::iterator d = it;
                fConnections.erase(d);
                it++;
            }
        }
    }
    // We separate all the methods of the list to erase them from the map fConnections (after checking that they were indeed connected to the signal) :
    // "method1:method2:method3" --> erase "object:method1", "object:method2", "object:method3"
    
    else
    {
        std::string allMethodStr = methods;
        std::string methodStr;
        std::string objectMethod;
        int i = allMethodStr.find(":");
        while(!allMethodStr.empty())
        {
            methodStr = allMethodStr.substr(0,i);
            
            if(i != allMethodStr.npos)
            {
                allMethodStr = allMethodStr.substr(i+1);
                i = allMethodStr.find(":");
            }
            else
                allMethodStr = "";
            
            objectMethod = object;
            objectMethod += ":";
            objectMethod += methodStr;
            
            // we handle the fConnections map
            
            std::map<std::string, SParallelSignal >::iterator it = fConnections.find(objectMethod);
            
            if(it == fConnections.end())            // no such parameter
                return MsgHandler::kBadParameters;
            
            else if(it->second != signal)     // the parameter was not connected to this signal
                return MsgHandler::kBadParameters;
            
            else                                    // this pair exists : we erase it, and the range corresponding
            {
                fConnections.erase(it);
                // we handle the fRanges map
                std::map<std::string, std::string>::iterator it2 = fRanges.find(objectMethod);
                if(it2 != fRanges.end()) fRanges.erase(it2);
            }
        }
    }
    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
std::map<std::string, std::pair<SParallelSignal, std::string> > ISignalNode::getConnectionsOf(std::string objectName)
{
    std::map<std::string, std::pair<SParallelSignal, std::string> > connections;
    std::map<std::string, SParallelSignal >::iterator it;
    for (it = fConnections.begin(); it != fConnections.end(); it++)
    {
        std::string objectsMethod = it->first; // "object:method"
        if(objectsMethod.find(":") != std::string::npos && !objectsMethod.compare(0, objectsMethod.find(":"), objectName)) // "object"
        {
            std::string methods = objectsMethod.substr(objectsMethod.find(":")); // "method"
            std::string range = "";
            std::map<std::string, std::string>::iterator it2 = fRanges.find(it->first); // "object:method"
            if(it2 != fRanges.end()) range = it2->second;
            connections.insert(std::pair<std::string, std::pair<SParallelSignal, std::string> >(methods, std::pair<SParallelSignal, std::string>(it->second, range)));
        }
    }
    return connections;
}

}
