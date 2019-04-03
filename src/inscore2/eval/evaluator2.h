/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#ifndef __evaluator2__
#define __evaluator2__

#include <exception>

#include "INode.h"

namespace inscore2
{

class TEnv;

class evalException: public std::exception
{
	std::string fWhat;
	public:
			 evalException(const char* reason) : fWhat(reason) {}
	virtual ~evalException() noexcept {}
	virtual const char* what() const noexcept { return fWhat.c_str(); }
};

class evaluator
{
	enum TType { kDefer, kString, kInt, kFloat, kDelay };
	static TType getType (const NList& args);

	typedef std::function<bool(float, float)> 				TCompNumFunction;
	typedef std::function<bool(std::string, std::string)> 	TCompStrFunction;
	typedef std::function<SINode(float)> 					TCreateFunction;

	static void 	error  (const SINode& node, const std::string& what);

	static bool 	isTrue  (const SINode& arg);

	static float 	getFArgValue (const SINode& node, const NList& args, TCreateFunction& f);
	static SINode 	compare (const SINode& arg1, const SINode& arg2, TCompStrFunction f);
	static SINode 	compare (const SINode& arg1, const SINode& arg2, TCompNumFunction f);

	static SINode 	addStrings 	(const NList& args);
	static SINode 	addInt 		(const NList& args);
	static SINode 	addFloat 	(const NList& args);
	static SINode	addDelay 	(const NList& args);

	static SINode 	subInt 		(const NList& args);
	static SINode 	subFloat 	(const NList& args);
	static SINode	subDelay 	(const NList& args);

	static SINode 	divInt 		(const NList& args);
	static SINode 	divFloat 	(const NList& args);
	static SINode 	divDelay 	(const NList& args);

	static SINode 	multInt 	(const NList& args);
	static SINode 	multFloat 	(const NList& args);
	static SINode 	multDelay 	(const NList& args);

	static SINode 	moduloInt 	(const NList& args);

	static SINode 	minStrings	(const NList& args);
	static SINode 	minNum		(const NList& args);
	static SINode 	maxStrings	(const NList& args);
	static SINode 	maxNum		(const NList& args);


	static SINode 	evalAdd 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalSub 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalDiv 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalMult 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalModulo 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalQuest 	(const SINode& node, const NList& args);
	static SINode 	evalNeg 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalEq 		(const SINode& node, const NList& args, TType type);
	static SINode 	evalGreater (const SINode& node, const NList& args, TType type);
	static SINode 	evalGreatereq(const SINode& node, const NList& args, TType type);
	static SINode 	evalLess 	(const SINode& node, const NList& args, TType type);
	static SINode 	evalLesseq	(const SINode& node, const NList& args, TType type);
	static SINode 	evalMin		(const SINode& node, const NList& args, TType type);
	static SINode 	evalMax		(const SINode& node, const NList& args, TType type);
	static SINode 	evalHas		(const SINode& node, const NList& args);

	static SINode 	evalSin		(float value, TCreateFunction create);
	static SINode 	evalCos		(float value, TCreateFunction create);
	static SINode 	evalTan		(float value, TCreateFunction create);
	static SINode 	evalASin	(float value, TCreateFunction create);
	static SINode 	evalACos	(float value, TCreateFunction create);
	static SINode 	evalATan	(float value, TCreateFunction create);
	static SINode 	evalSinh	(float value, TCreateFunction create);
	static SINode 	evalCosh	(float value, TCreateFunction create);
	static SINode 	evalTanh	(float value, TCreateFunction create);
	static SINode 	evalASinh	(float value, TCreateFunction create);
	static SINode 	evalACosh	(float value, TCreateFunction create);
	static SINode 	evalATanh	(float value, TCreateFunction create);

	static SINode 	evalExp		(float value, TCreateFunction create);
	static SINode 	evalLog		(float value, TCreateFunction create);
	static SINode 	evalLog10	(float value, TCreateFunction create);
	static SINode 	evalLog2	(float value, TCreateFunction create);
	static SINode 	evalPow		(const SINode& node, const NList& args, TType type);
	static SINode 	evalSqrt	(float value, TCreateFunction create);
	static SINode 	evalCbrt	(float value, TCreateFunction create);
	static SINode 	evalCeil	(float value, TCreateFunction create);
	static SINode 	evalFloor	(float value, TCreateFunction create);
	static SINode 	evalRound	(float value, TCreateFunction create);
	static SINode 	evalRand();

	static SINode 	evalMath   (const SINode& node, const TEnv&);
	static SINode 	evalSlash  (const SINode& node, const TEnv&);
	static SINode 	evalExpand (const SINode& node, const TEnv&);
	static SINode 	evalExpandVal (const SINode& node, const TEnv&);
	static SINode 	evalVar    (const SINode& node, const TEnv&);
	static SINode 	evalNode   (const SINode& node, const TEnv&);

	static SINode 	eval (const SINode& node, const TEnv&);

	public:
		static SINode 	eval (const SINode& node) throw(evalException);
};

} // end namespace

#endif
