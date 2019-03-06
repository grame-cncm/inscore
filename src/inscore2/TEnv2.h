
#ifndef __TEnv2__
#define __TEnv2__

#include <map>
#include <memory>
#include <ostream>


namespace inscore2
{

class INode;
typedef std::shared_ptr<INode>	SINode;

class TEnv : public std::map<std::string, SINode>
{

	public:
	typedef std::map<std::string, SINode> TEnvMap;
	
			 TEnv() {}
			 TEnv(const TEnv& e) { *this = e; }
	virtual ~TEnv() {}

	const SINode get (const std::string& name) const {
		TEnvMap::const_iterator i = this->find(name);
		return i == this->end() ? 0 : i->second;
	}

	void put (const std::string& name, SINode val )	{
		(*this)[name] = val;
	}

	TEnv operator + (const TEnv& e) const	{
 		TEnv ne(e);
 		for (auto n: *this) ne.put(n.first, n.second);
 		return ne;
	}

	void operator += (const TEnv& e) {
 		for (auto n: e) this->put(n.first, n.second);
	}
	std::ostream& print (std::ostream& os) const;
};

inline std::ostream& operator<< (std::ostream& os, const TEnv& e) { return e.print(os); }

} // end namespace

#endif

