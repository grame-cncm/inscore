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


#ifndef __IGuidoCode__
#define __IGuidoCode__

#include <string>
#include <map>
#include <set>

#include "IObject.h"
#include "GUIDOEngine.h"
#include "TLocalMapping.h"
#include "IExpressionHandler.h"
#include "GmnEvaluator.h"

struct NodeGR;
typedef const struct NodeGR *  CGRHandler;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class SIExprHandlerbase;
class IGuidoCode;
typedef class libmapping::SMARTP<IGuidoCode>	SIGuidoCode;
//--------------------------------------------------------------------------
/*!
	\brief a textual guido music notation object.
*/
class IGuidoCode : public IObject
{
	protected:
		typedef libmapping::SMARTP<TLocalMapping<libmapping::rational,1> >	SLocalMapping;
		SLocalMapping	fLocalMappings;
		CGRHandler		fGRHandler;
		int				fCurrentPagesCount;		// the current page count, used to fire the 'pageCount' event

	public:
	int fPage;					/// < Guido Page Index. When several pages are displayed: index of the first displayed page. Default 1.
	TFloatSize fPageFormat;		/// < Guido Page Format, in cm. Default: 21 x 29.7
	int fNbOfPageColumns;		/// < Nb of columns of pages. (when the score has multiple pages). Default 2.
	int fNbOfPageRows;			/// < Nb of rows of pages. (when the score has multiple pages) Default 1.

	const	SLocalMapping& localMappings() const	{ return fLocalMappings; }
			SLocalMapping& localMappings()			{ return fLocalMappings; }
	
	protected:
		std::string	fGMN;								/// < Guido Music Notation code.
//		int			fPageCount;							/// < Nb of pages of the score. (set by the view)
		
		std::vector<std::string> fRequestedMappings;	/// < Requested map-name list. 
														/// The 'map' msg just expects a map-name, and then the Guido view
														/// is in charge of building the mappings just from 
														/// the fRequestedMappings list.
		IExprHandler<GmnEvaluator> fExprHandler;


	public:
		static const std::string kGuidoCodeType;
		static SIGuidoCode create(const std::string& name, IObject * parent)	{ return new IGuidoCode(name, parent); }
		virtual void	accept (Updater*u);

		void	print (std::ostream& out) const;

		const std::string&	getGMN() const			{ return fGMN; }
		virtual const std::string getCleanGMN() const {return fGMN; }
		int			getPage() const					{ return fPage; }
		TFloatSize	getPageFormat() const			{ return fPageFormat; }
		int			getNbOfPageColumns() const		{ return fNbOfPageColumns; }
		int			getNbOfPageRows() const			{ return fNbOfPageRows; }
		int			getPageCount() const;
		void		setGRHandler(CGRHandler gr)		{ fGRHandler = gr; }
		libmapping::rational	getPageDate(int pagenum) const;

		const IExprHandlerbase*	getExprHandler() const	{return &fExprHandler;}

		/// \brief requests that the IGuidoCode build a mapping named 'mapName'. The IGuidoCode stores the number of requests.
		virtual void requestMapping(const std::string& mapName);

		/// \brief decreases the number of requests for a mapping named 'mapName'.
		virtual void stopRequestMapping(const std::string& mapName);
		virtual const std::vector<std::string>& requestedMappings() const	{ return fRequestedMappings;  }

		/// \brief gives the systems count as a list of count ordered by page number
		virtual std::vector<int> getSystemsCount() const;

		void	setPageCount(int count);


	protected:
				 IGuidoCode( const std::string& name, IObject * parent );
		virtual ~IGuidoCode() {}

		void setGMN( const std::string& gmn )				{ fGMN = gmn; localMapModified(true); }
		void setPage( int page )							{ fPage = page; localMapModified(true); }
		void setdPage( int dpage );
		void setPageFormat( const TFloatSize& pageFormat )	{ fPageFormat = pageFormat; localMapModified(true); }
		void setNbOfPageColumns(int columns)				{ fNbOfPageColumns = columns; localMapModified(true); }
		void setNbOfPageRows(int rows)						{ fNbOfPageRows = rows; localMapModified(true); }

		/// \brief overrides IObject method to accept score specific events
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);		
		/// \brief the \c 'map' message handler
		MsgHandler::msgStatus mapMsg (const IMessage* msg );
		
		/// \brief Overrides IObject to handle 'get map' msg.
		SIMessageList getMsgs(const IMessage* msg) const;

		MsgHandler::msgStatus exprMsg(const IMessage* msg);
};

/*! @} */

} // end namespoace

#endif
