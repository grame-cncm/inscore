
#ifndef __mathparser__
#define __mathparser__

#include <iostream>
#include <fstream>
#include <sstream>


class mathparser {	
		
	void initScanner();
	void destroyScanner();

	public:
		void*			fScanner;	// the flex scanner
		std::istream*	fStream;    // input stream
		std::string		fText;		// the current text
		int				fInt;		// the current int
		float			fFloat;		// the current float

				 mathparser(std::istream* stream)	: fStream(stream) 	{ initScanner(); }
		virtual ~mathparser()											{ destroyScanner(); }
		
		void parse();
};

#endif
