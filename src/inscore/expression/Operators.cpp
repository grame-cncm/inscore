#include "Operators.h"
#include "ExprFactory.h"

namespace inscore {


const OperatorPrototype opGuidoSeq		("seq")			;
const OperatorPrototype opGuidoPar		("par")			;
const OperatorPrototype opGuidoParR		("rpar")		;
const OperatorPrototype opGuidoHead		("head")		;
const OperatorPrototype opGuidoEvHead	("evhead")		;
const OperatorPrototype opGuidoTail		("tail")		;
const OperatorPrototype opGuidoEvTail	("evtail")		;
const OperatorPrototype opGuidoDur		("duration")	;
const OperatorPrototype opGuidoTrans	("transpose")	;
const OperatorPrototype opGuidoTop		("top")			;
const OperatorPrototype opGuidoBottom	("bottom")		;
const OperatorPrototype opGuidoRythm	("rhythm")		;
const OperatorPrototype opGuidoPitch	("pitch")		;


OperatorPrototype::OperatorPrototype(std::string name): fName(name)
{
	ExprFactory::registerOperator(this);
}

} //end namespace

