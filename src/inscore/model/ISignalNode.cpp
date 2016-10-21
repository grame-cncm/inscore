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
#include "Updater.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
// signals node
//--------------------------------------------------------------------------
const string ISignalNode::kName				= "signal";
const string ISignalNode::kSignalNodeType	= "signode";

//--------------------------------------------------------------------------
ISignalNode::ISignalNode(IObject * parent) : IVNode(kName, parent), fDebug(false)
{
	fTypeString = kSignalNodeType;

	fGetMsgHandlerMap["debug"]	= TGetParamMsgHandler<bool>::create(fDebug);
	fMsgHandlerMap["debug"]		= TSetMethodMsgHandler<ISignalNode, bool>::create(this,&ISignalNode::debug);
	fMsgHandlerMap[kwatch_GetSetMethod]		= 0L;
	fMsgHandlerMap[kwatchplus_SetMethod]	= 0L;
    fGetMultiMsgHandlerMap[kwatch_GetSetMethod]	= 0L;
    
    fGetMultiMsgHandlerMap[kconnect_GetSetMethod] = TGetParamMultiMethodHandler<ISignalNode, SIMessageList(ISignalNode::*)() const>::create(this, &ISignalNode::getAllConnections);
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
	size_t n = node.find ('/');				// is it a final path ?
	if (n == string::npos)
		return exactfind(node, outlist);	// then find the node

	bool ret = false;
	string name = node.substr(0, n);				// get the node name from the path
	string sub = node.substr (n+1, node.size());	// and the subnode name
	subnodes sigs;
	if (exactfind(name, sigs)) {			// then find the node
		for (unsigned int n=0; n<sigs.size(); n++) {					// for each retrieved node
			ISignal* sig = dynamic_cast<ISignal*>((IObject*)sigs[n]);	// get it as a signal
			if (sig && sig->findSubNode (sub, outlist))			// and ask the node to find the subnode
				ret = true;
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
    
    string signalStr;
    if(!msg->param(0, signalStr)) return MsgHandler::kBadParameters;
    
    // We check if the first parameter is indeed a signal and is on our list
    subnodes signalList;
    if(!find(signalStr, signalList)) return MsgHandler::kBadParameters;

    ISignal* signal = dynamic_cast<ISignal*>((IObject*)signalList[0]);
    if(!signal) return MsgHandler::kBadParameters;
    
    // Then, for each parameter, we separate the first name (the object) and the rest of the string (one or more methods) :
    // "object:method1[range1]:method2[range2]" --> "object" + "method1[range1]:method2[range2]"
    // And for each pair of object-methods, we call connect(signal, objectStr, methods)
    MsgHandler::msgStatus result;
    for(int i = 1; i<n; i++)
    {
		string param;
        if(!msg->param(i, param)) return MsgHandler::kBadParameters;

        string objectStr = param.substr(0,param.find(":"));
		string methods = param.substr(param.find(":")+1);
        result = connect(signal, objectStr, methods);
        if(result != MsgHandler::kProcessed) break;
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
    if(n == 1) return disconnect(signal);
    
    // If we have more parameters, we distinguish each object from its list of methods and call disconnect(signal, objectStr, objectList)
    std::string objectMethodsStr, objectStr;
    MsgHandler::msgStatus result;
    for(int i = 1; i<n; i++)
    {
        if(!msg->param(i, objectMethodsStr)) return MsgHandler::kBadParameters;
        objectStr = objectMethodsStr.substr(0,objectMethodsStr.find(":"));
        subnodes objectList;
        if(!getParent()->find(objectStr, objectList)) return MsgHandler::kBadParameters;
    
        std::string methods;
        if(objectMethodsStr.find(":") != objectMethodsStr.npos)
            methods = objectMethodsStr.substr(objectMethodsStr.find(":")+1);
        else
            methods = "";
        result = disconnect(signal, objectStr, methods);
        if(result != MsgHandler::kProcessed) return result;
    }
    return result;
}


//--------------------------------------------------------------------------
ISignalNode::TCnxPair ISignalNode::string2cnxpair (const std::string& param) const
{
	string range, attribute;
	size_t i = param.find("[");
	if (i != std::string::npos) {
		range = param.substr(i);
		attribute = param.substr(0,i);
	}
	else attribute = param;
	return TCnxPair(attribute, range);
}

//--------------------------------------------------------------------------
ISignalNode::TCnxSet ISignalNode::string2cnxset (const std::string& param) const
{
	TCnxSet outSet;
	// the param expected format is "method1[range1]:method2[range2]..."
    // the method separates 'method' and 'range' in a pair
	size_t beg = 0;
	do {
		size_t i = param.find(":", beg);
		if (i == std::string::npos) {
			outSet.push_back( string2cnxpair(param.substr(beg)) );
			break;
		}
		outSet.push_back( string2cnxpair(param.substr(beg, i)) );
		beg = i+1;
	} while (true);
	return outSet;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::connect(SISignal signal, std::string object, std::string methods)
{
    // We check if the object is indeed in the elements of our parent object
    subnodes objectList;
    if(!getParent()->find(object, objectList)) return MsgHandler::kBadParameters;
    
    SIObject obj = objectList[0];
    string allMethodStr = methods;
    string methodStr;
    string range = "";
    string objectMethod;
    size_t i = allMethodStr.find(":");
	
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
        
        // we test that the method is available for connections
        if(! obj->signalHandler(methodStr)) return MsgHandler::kBadParameters;
        
        ISignalConnection * connection = new ISignalConnection();
        
        objectMethod = object;
        objectMethod += ":";
        objectMethod += methodStr; // "object:method(n)"
        
        connection->setObject(obj);
        connection->setMethod(methodStr);
        connection->setObjectMethod(objectMethod);
        connection->setSignal(signal);
        connection->setRangeString(range);
        
        // We now want to translate the string range into floats, ints, or rationnals.
        if(!range.empty())
        {
            CRegexpT <char> regexp("^\\[.+,.+\\]$"); // range : "[r1,r2]"
            if(regexp.MatchExact(range.c_str()))
            {
                CRegexpT <char> regexp2("^\\[.+ .+,.+ .+\\]$"); // range : "[n1 d1, n2 d2]"
                if(!range.empty() && regexp2.MatchExact(range.c_str()))
                {
                    int n1, d1, n2, d2;
                    int n = sscanf (range.c_str(), "[%i %i,%i %i]", &n1, &d1, &n2, &d2);
                    if (n == 4)
                    {
                        float r1 = (float)(n1)/(float)(d1);
                        float r2 = (float)(n2)/(float)(d2);
                        // We store the information in the object connection
                        connection->setRangeType("float");
                        connection->setFloatRange(r1, r2);
                    }
                    else return MsgHandler::kBadParameters;
                }
                else
                {
                    int i1, i2;
                    float f1, f2;
                    if(sscanf (range.c_str(), "[%i,%i]", &i1, &i2) == 2) // the range is expressed with integers
                    {
                        // We store the information in the object connection
                        connection->setRangeType("int");
                        connection->setIntRange(i1, i2);
                    }
                    else if(sscanf (range.c_str(), "[%f,%f]", &f1, &f2) == 2) // the range is expressed with floats
                    {
                        // We store the information in the object connection
                        connection->setRangeType("float");
                        connection->setFloatRange(f1, f2);
                    }
                    else return MsgHandler::kBadParameters;
                }
            }
            else return MsgHandler::kBadParameters;
        }
        else
            connection->setRangeType("none");
        
        vector<ISignalConnection*>::iterator it = fConnections.begin();
        bool found = false;
        while(it != fConnections.end()  && !found)
        {
            if((*it)->getObjectMethod() == objectMethod)
                found = true;
            else
                it++;
        }
        if(found) // If this method of the object has already been stored, we replace the connection
            fConnections.erase(it);
        
        fConnections.push_back(connection);
    }

    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignalNode::disconnect(SISignal signal, std::string object, std::string methods)
{
    if(object.empty()) // if the object is not specified, we disconnect all connections with the signal
    {
        std::vector<ISignalConnection* >::iterator it = fConnections.begin();
        while(it != fConnections.end())
        {
            if((*it)->contains(signal))		// if we find the signal, we erase the connection object
                it = fConnections.erase(it);
            else it++;
        }
    }
    // if we only specified the signal and the object (without methods), we look for all the connections between the signal and this object
    else if(methods.empty())
    {
        vector<ISignalConnection*>::iterator it = fConnections.begin();
        bool found = false;
        while(it != fConnections.end()  && !found)
        {
            if((*it)->contains(object) && (*it)->contains(signal))
                it = fConnections.erase(it);
            else it++;
        }

    }
    // We separate all the methods of the list to erase them from the map fConnections (after checking that they were indeed connected to the signal) :
    // "method1:method2:method3" --> erase "object:method1", "object:method2", "object:method3"
    else
    {
        std::string allMethodStr = methods;
        std::string methodStr;
        std::string objectMethod;
        size_t i = allMethodStr.find(":");
        while(!allMethodStr.empty())
        {
            methodStr = allMethodStr.substr(0,i);
            methodStr = methodStr.substr(0,methodStr.find("["));
            
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
            
            vector<ISignalConnection*>::iterator it = fConnections.begin();
            bool found = false;
            while(it != fConnections.end()  && !found)
            {
                if((*it)->getObjectMethod() == objectMethod && (*it)->contains(signal))
                    found = true;
                else
                    it++;
            }
            if(found)
                fConnections.erase(it);
            else     // this connections didn't exist
                return MsgHandler::kBadParameters;
        }
    }
    return MsgHandler::kProcessed;
}

std::vector<ISignalConnection* > ISignalNode::getConnectionsOf(const IObject* obj) const
{
    std::vector<ISignalConnection*> connections;
	for (unsigned int i = 0; i < fConnections.size(); i++) {
		if (fConnections[i]->getObject() == obj)
            connections.push_back(fConnections[i]);
    }
    return connections;
}

//--------------------------------------------------------------------------
SIMessageList ISignalNode::getAllConnections() const
{
    SIMessageList list = IMessageList::create();
    const char* address = getOSCAddress().c_str();
    
	for (unsigned int i = 0; i < fConnections.size(); i++)
    {
        SIMessage msg = IMessage::create (address, kconnect_GetSetMethod);
        std::string objectMethodWithRange = fConnections[i]->getObjectMethod();
        objectMethodWithRange.append(fConnections[i]->getRangeString());
        *msg << fConnections[i]->getSignal()->signal(0)->getName() << objectMethodWithRange;
        
        list->list().push_back( msg );
    }
    return list;
}

//--------------------------------------------------------------------------
void ISignalNode::cleanupSignal(const ParallelSignal* signal)
{
	vector<ISignalConnection* >::iterator i = fConnections.begin();
	while (i != fConnections.end()) {
		if ((*i)->getSignal() == signal) {
			i = fConnections.erase( i );
		}
		else i++;
	}
}

//--------------------------------------------------------------------------
void ISignalNode::cleanupTarget(const IObject* obj)
{
	vector<ISignalConnection* >::iterator i = fConnections.begin();
	while (i != fConnections.end()) {
		if ((*i)->getObject() == obj) {
			i = fConnections.erase( i );
		}
		else i++;
	}
}

void ISignalConnection::print (ostream& out) const {
	out << "signal: " << (void*)fSignal << " -> " << fObject << ":" << fMethod << fRangeString ;
}


}
