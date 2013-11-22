// CodeTrace.h  by Carmine Emanuele Cella
//

#ifndef CODETRACE
#define CODETRACE

#ifdef TRACE_ON

#include <fstream>
#include <iostream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <cassert>
#include <iomanip>

class CodeTrace {
	CodeTrace () {};
	void operator= (CodeTrace&);
	CodeTrace (const CodeTrace&);	
public:
	template <typename T1> 
		static void print (T1 par1)	{

		serialize () << par1;
		//std::cout << par1;

	}
	template <typename T1> 
		static void printn (T1 par1)	{

		serialize () << par1 << std::endl << std::endl;
		//std::cout << par1 << std::endl << std::endl;

	}	
	template <typename T1> 
		static void trace (T1 par1, std::string name,
		std::string file, int line) {
		std::stringstream a;
		a << file << "[" << line << "] (" << typeid (par1).name () << ") " << name << " = " << par1;

		serialize () << a.str () << std::endl;
		//std::cout << a.str () << std::endl;
	}
	static long getCount () {
		static long count = -1;
		++count;
		
		serialize () << "iteration: " << count;
		//std::cout    << "iteration: " << count;
		return count;
	}	
private:
	static std::ofstream& CodeTrace::serialize () { // Stream creation on use...
		static std::ofstream __TRACEFILE__ ("CodeTrace.log");
		assert (__TRACEFILE__);
	return __TRACEFILE__;
	}
};
	#define PRINT(a) CodeTrace::print (a);
	#define PRINTN(a) CodeTrace::printn (a);
	#define TRACE(a) CodeTrace::trace (a, #a, __FILE__, __LINE__);
	#define ADDCOUNT CodeTrace::getCount ();
#else
	#define PRINT(a) ((void) 0);
	#define PRINTN(a)((void) 0);
	#define TRACE(a) ((void) 0);
	#define ADDCOUNT ((void) 0);
#endif	// TRACE_ON

#endif	// CODETRACE_H


