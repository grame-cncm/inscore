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


#ifndef __IWatcher__
#define __IWatcher__

#include "IMessageHandlers.h"
#include "IObject.h"
#include <cassert>

#define ALWAYS_EMIT				"!"
#define ALWAYS_TRUE				"#"
#define CONDITION_SEPARATOR		":"
#define VARIABLE_PREFIX			'$'
#define COMPARATOR_DIFF			"!="
#define COMPARATOR_EQ			"=="
#define COMPARATOR_INF_EQ		"<="
#define COMPARATOR_SUP_EQ		">="
#define COMPARATOR_SUP			">"
#define COMPARATOR_INF			"<"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IWatcher;
typedef class SMARTP<IWatcher>	SIWatcher;

//--------------------------------------------------------------------------
/*!
	\brief the watcherication object of the model
*/
class IWatcher : public IObject
{
	protected:
			
		class ParamChecker: public smartable
		{
			protected:
				ParamChecker() {}
			public:
				virtual ~ParamChecker() {}
				virtual bool check( SIObject o ) const = 0;
				virtual IMessage&  print(IMessage& m) const = 0;
		};
		typedef SMARTP<ParamChecker> SParamChecker;

		struct WatchStruct {
			WatchStruct() : fConditionsState(false), fAlwaysEmit(false) {}
			std::vector< SParamChecker > fConditions;
			bool fConditionsState , fAlwaysEmit;
			IMessage fTemplateMsg;
		};
		
		std::vector< WatchStruct > fWatchedProperties;

	public:
		static const std::string kWatcherType;
		static SIWatcher			create(const std::string& name, IObject* parent)		{ return new IWatcher(name,parent); }

		virtual void		print(std::ostream& out) const;

		virtual int			execute (const IMessage* msg);

	protected:
				 IWatcher(const std::string& name, IObject* parent);
		virtual ~IWatcher();
		
		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief the \c 'add' message handler
		virtual MsgHandler::msgStatus addMsg (const IMessage* msg);
		/// \brief the \c 'remove' message handler
		virtual MsgHandler::msgStatus removeMsg (const IMessage* msg);
		/// \brief the \c 'clear' message handler
		virtual MsgHandler::msgStatus clearMsg (const IMessage* msg);
		
		/// \brief the \c 'get' with no parameter message handler
		virtual IMessageList getSetMsg () const;
		
		/// \brief Builds a message from 'templateMsg', replacing '$param' strings with
		///	the corresponding values of the source object.
		static IMessage* buildEmitedMsg( const IMessage& templateMsg  , SIObject source );
		
		/// \brief Builds a ParamChecker ( of the form 'param' '>=' '3.2' ':' ) list from the
		///			source message first params (parse the params until they don't fit the
		///			ParamChecker's form).
		static int	buildParamCheckerList(const IMessage& source , int startIndex , std::vector< SParamChecker >& outList);
		
		/// \brief	Builds an IMessage from a source IMessage's params.
		///			The params must be of the form: <string>address [<string>optional-msg] [<any-type>optional-params ...]
		///			The parsing of the source IMessage's params starts at 'startIndex'.
		static bool buildTemplateMsg(const IMessage& source, int startIndex , IMessage& outMsg);

		/// \brief Try to build a ParamChecker with the paramName, an operator string and the referenceValue.
		///			The building will fail if the operatorString is not recognized.
		///	\return The new ParamChecker, or 0 if the building failed.
		static SParamChecker buildParamChecker( const std::string& paramName , const std::string& operatorString , IMessage::argPtr referenceValue , IMessage::argPtr optionalReferenceValue );

		template <typename T>
		class ComparisonOperator: public smartable
		{
			protected:
				ComparisonOperator() {}
			public:
				virtual ~ComparisonOperator() {}
				virtual bool compare( const T& a , const T& b ) const = 0;
				virtual IMessage&  print(IMessage& out) const = 0;
		};
		
		template <typename T>
		class InfComparisonOperator: public ComparisonOperator<T>
		{
			protected:
				InfComparisonOperator(): ComparisonOperator<T>() {}
			public:
				static SMARTP<InfComparisonOperator < T > > create() { return new InfComparisonOperator<T>(); }
				virtual ~InfComparisonOperator() {}
				bool compare(const T& a,const T& b) const { return a < b; }
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(COMPARATOR_INF); return out; }
		};
		template <typename T>
		class SupComparisonOperator: public ComparisonOperator<T>
		{
			protected:
				SupComparisonOperator(): ComparisonOperator<T>() {}
			public:
				static SMARTP<SupComparisonOperator < T > > create() { return new SupComparisonOperator<T>(); }
				virtual ~SupComparisonOperator() {}
				bool compare(const T& a,const T& b) const { return a > b; }
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(COMPARATOR_SUP); return out; }
		};
		template <typename T>
		class InfEqComparisonOperator: public ComparisonOperator<T>
		{
			protected:
				InfEqComparisonOperator(): ComparisonOperator<T>() {}
			public:
				static SMARTP<InfEqComparisonOperator < T > > create() { return new InfEqComparisonOperator<T>(); }
				virtual ~InfEqComparisonOperator() {}
				bool compare(const T& a,const T& b) const { return a <= b; }
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(COMPARATOR_INF_EQ); return out; }
		};
		template <typename T>
		class SupEqComparisonOperator: public ComparisonOperator<T>
		{
			protected:
				SupEqComparisonOperator(): ComparisonOperator<T>() {}
			public:
				static SMARTP<SupEqComparisonOperator < T > > create() { return new SupEqComparisonOperator<T>(); }
				virtual ~SupEqComparisonOperator() {}
				bool compare(const T& a,const T& b) const { return a >= b; }
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(COMPARATOR_SUP_EQ); return out; }
		};
		template <typename T>
		class EqComparisonOperator: public ComparisonOperator<T>
		{
			protected:
				EqComparisonOperator(): ComparisonOperator<T>() {}
			public:
				static SMARTP<EqComparisonOperator < T > > create() { return new EqComparisonOperator<T>(); }
				virtual ~EqComparisonOperator() {}
				bool compare(const T& a,const T& b) const { return a == b; }
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(COMPARATOR_EQ); return out; }
		};
		template <typename T>
		class DiffComparisonOperator: public ComparisonOperator<T>
		{
			protected:
				DiffComparisonOperator(): ComparisonOperator<T>() {}
			public:
				static SMARTP<DiffComparisonOperator < T > > create() { return new DiffComparisonOperator<T>(); }
				virtual ~DiffComparisonOperator() {}
				bool compare(const T& a,const T& b) const { return a != b; }
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(COMPARATOR_DIFF); return out; }
		};

		template <typename T>
		class Comparator: public smartable
		{
			protected:
				SMARTP<ComparisonOperator <T> > fOp;
				T fReference;
				
				Comparator( SMARTP<ComparisonOperator <T> > op, const T& reference ) : fOp(op), fReference(reference) {}

			public:
				static SMARTP< Comparator <T> > create( SMARTP<ComparisonOperator <T> > op, const T& reference ) { return new Comparator<T> (op, reference); }
				
				bool result( const T& a ) const		{ return fOp->compare( a , fReference ); }
				
				virtual IMessage&  print(IMessage& out) const	{ fOp->print(out); out << fReference; return out; }
		};
		
		class ParamCheckerAlwaysTrue: public ParamChecker
		{
			protected:
				ParamCheckerAlwaysTrue() {}
			public:
				static SParamChecker create() { return new ParamCheckerAlwaysTrue(); }
				
				virtual ~ParamCheckerAlwaysTrue() {}
				virtual bool check( SIObject o ) const { return true; }
				
				virtual IMessage&  print(IMessage& out) const	{ out << std::string(ALWAYS_TRUE); return out; }
		};
		
		template <typename T>
		class ParamCheckerTemplate: public ParamChecker
		{
			protected:
				std::string fParamName;
				SMARTP< Comparator <T> > fComparator;
			
				ParamCheckerTemplate( const std::string& paramName , SMARTP< Comparator <T> > comparator )
					: fParamName(paramName), fComparator(comparator) {}
			public:
				virtual ~ParamCheckerTemplate() {}
			
				static SParamChecker create( const std::string& paramName , SMARTP< Comparator <T> > comparator ) 
				{ return new ParamCheckerTemplate<T>(paramName , comparator ); }

				// TODO: specialiser ça pour les ParamCheckerTemplate<rational>
				bool check( SIObject o ) const
				{
					assert ( o );

					SGetParamMsgHandler getHandler = o->getMessageHandler( fParamName );
					if ( !getHandler )
						return false;
					IMessage msg;
					getHandler->print(msg);
					if ( !msg.params().size() )
						return false;
					return fComparator->result( msg.params()[0]->value( T() ) );
				}
				
				virtual IMessage&  print(IMessage& out) const	{ out << fParamName; fComparator->print(out); return out; }
		};

		template<typename T> static SParamChecker buildParamCheckerTemplate( const std::string& paramName , const std::string& operatorString , const T& reference )
		{
			SMARTP<ComparisonOperator <T> > op = 0;
			if ( operatorString == COMPARATOR_INF )
				op =  InfComparisonOperator<T>::create();
			else if ( operatorString == COMPARATOR_SUP )
				op =  SupComparisonOperator<T>::create();
			else if ( operatorString == COMPARATOR_INF_EQ )
				op =  InfEqComparisonOperator<T>::create();
			else if ( operatorString == COMPARATOR_SUP_EQ )
				op =  SupEqComparisonOperator<T>::create();
			else if ( operatorString == COMPARATOR_EQ )
				op =  EqComparisonOperator<T>::create();
			else if ( operatorString == COMPARATOR_DIFF )
				op =  DiffComparisonOperator<T>::create();

			if ( !op ) return 0;
			return ParamCheckerTemplate<T>::create( paramName , Comparator<T>::create( op , reference ) );
		}
		
};

/*! @} */

} // end namespoace

#endif
