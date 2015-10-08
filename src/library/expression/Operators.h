#ifndef OPERATORPROTOTYPE_H
#define OPERATORPROTOTYPE_H

#include <string>

namespace inscore {



class OperatorPrototype
{
private:
    const std::string fName;
public:
    OperatorPrototype(std::string name);
	inline const std::string getName() const {return fName;}
};


/********************************************
 *             Operator List                *
 ********************************************/


extern const OperatorPrototype opGuidoTail	;
extern const OperatorPrototype opGuidoHead	;
extern const OperatorPrototype opGuidoSeq	;
extern const OperatorPrototype opGuidoPar	;
extern const OperatorPrototype opGuidoParR	;
extern const OperatorPrototype opGuidoDur	;
extern const OperatorPrototype opGuidoTrans	;
extern const OperatorPrototype opGuidoTop	;
extern const OperatorPrototype opGuidoBottom;
extern const OperatorPrototype opGuidoRythm	;
extern const OperatorPrototype opGuidoPitch	;



} //end namespace


// Spécialisation de la fonction de hachage std pour OperatorPrototype, afin d'utiliser les unordered_map<OperatorPrototype, ... >01
namespace std {
template<>
class hash<const inscore::OperatorPrototype*> {
public:
	size_t operator()(const inscore::OperatorPrototype* op) const
	{
		return std::hash<std::string>()(op->getName());
	}
};
}

#endif // OPERATORPROTOTYPE_H
