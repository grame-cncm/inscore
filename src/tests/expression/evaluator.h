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


/*!
 * \brief Interface defining an evaluator: it can evaluate specific arguments or an entire expression
 */
class evaluator{
public:

    virtual std::string eval(IExpression* arg)=0;
    virtual std::string eval(std::string arg)=0;
    virtual std::string eval(filepath arg)=0;
    virtual std::string eval(identifier arg)=0;
    virtual std::string eval(oscaddress arg)=0;


    /*!
     * \brief evaluate an entire expression
     * \param expr: the expression to evaluate
     * \param result: if the evaluation succeed, store the evaluated string
     * \return true if the evaluation succeed, false otherwise
     */
    virtual bool evalExpression(IExpression *expr, std::string& result)=0;

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

