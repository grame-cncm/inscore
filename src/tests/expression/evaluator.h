#ifndef EVALUATOR
#define EVALUATOR

#include <string>

namespace inscore{

//Custom acceptable type as arguments


struct specializedString{
        std::string string;
        specializedString(std::string s=""){string = s;}
        operator std::string() const {return string;}
};
#define STRING_TYPE(typeName) struct typeName: specializedString{ typeName(std::string s=""):specializedString(s){} };

STRING_TYPE(filepath)
STRING_TYPE(identifier)
STRING_TYPE(oscaddress)


class IExpression;

class evaluator{
public:
    virtual std::string eval(IExpression* arg)=0;
    virtual std::string eval(std::string arg)=0;
    virtual std::string eval(filepath arg)=0;
    virtual std::string eval(identifier arg)=0;
    virtual std::string eval(oscaddress arg)=0;

};

/*!
 * \brief Interface for evaluable class (visitable by an evaluator in the visitor design pattern logic)
 */
class evaluable{
public:
    virtual std::string accept(evaluator* e)=0;
};

}
#endif // EVALUATOR

