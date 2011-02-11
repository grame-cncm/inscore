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

#include "mapbuilder.h"
#include "TLocalMapping.h"


struct NodeGR;
typedef const struct NodeGR *  CGRHandler;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class VGuidoItemView;
class Updater;
class IGuidoCode;
typedef class SMARTP<IGuidoCode>	SIGuidoCode;
//--------------------------------------------------------------------------
/*!
	\brief a textual guido music notation object.
*/
class IGuidoCode : public IObject
{
	protected:
		typedef SMARTP<TLocalMapping<RelativeTimeSegment> >	SLocalMapping;
		SLocalMapping	fLocalMappings;
		CGRHandler		fGRHandler;
		VGuidoItemView * fView;

	public:
	int fPage;					/// < Guido Page Index. When several pages are displayed: index of the first displayed page. Default 1.
	TFloatSize fPageFormat;		/// < Guido Page Format, in cm. Default: 21 x 29.7
	int fPageCount;			/// < Nb of pages of the score. (set by the view)
	int fNbOfPageColumns;		/// < Nb of columns of pages. (when the score has multiple pages). Default 2.
	int fNbOfPageRows;			/// < Nb of rows of pages. (when the score has multiple pages) Default 1.

	const	SLocalMapping& localMappings() const	{ return fLocalMappings; }
			SLocalMapping& localMappings()			{ return fLocalMappings; }
	
	protected:
		std::string	fGMN;			/// < Guido Music Notation.
		
		std::vector<std::string> fRequestedMappings;	/// < Requested map-name list. 
														/// The 'map' msg just expects a map-name, and then the Guido view
														/// is in charge of building the mappings just from 
														/// the fRequestedMappings list.

	public:
		static const std::string kGuidoCodeType;
		static SIGuidoCode create(const std::string& name, IObject * parent)	{ return new IGuidoCode(name, parent); }
		virtual void	accept (Updater*u);

		void	print (std::ostream& out) const;

		const std::string&	getGMN() const		{ return fGMN; }
		int			getPage() const				{ return fPage; }
		TFloatSize	getPageFormat() const		{ return fPageFormat; }
		int			getNbOfPageColumns() const	{ return fNbOfPageColumns; }
		int			getNbOfPageRows() const		{ return fNbOfPageRows; }
		int			getPageCount() const		{ return fPageCount; }
		rational	getPageDate(int pagenum) const;
		void		setPagesCount(int pageCount)			{ fPageCount = pageCount; }
		void		setGRHandler(CGRHandler gr)				{ fGRHandler = gr; }

		/// \brief requests that the IGuidoCode build a mapping named 'mapName'. The IGuidoCode stores the number of requests.
		virtual void requestMapping(const std::string& mapName);

		/// \brief decreases the number of requests for a mapping named 'mapName'.
		virtual void stopRequestMapping(const std::string& mapName);

		virtual const std::vector<std::string>& requestedMappings() const	{ return fRequestedMappings;  }
		
		VGuidoItemView *	getView () const				{ return fView; }
		void				setView (VGuidoItemView * view) { fView = view; }
		VGraphicsItemView*	graphicView() const				{ return (VGraphicsItemView*)fView; }

	protected:
				 IGuidoCode( const std::string& name, IObject * parent );
		virtual ~IGuidoCode() {}

		void setGMN( const std::string& gmn )				{ fGMN = gmn; localMapModified(true); }
		void setPage( int page )							{ fPage = page; localMapModified(true); }
		void setPageFormat( const TFloatSize& pageFormat )	{ fPageFormat = pageFormat; localMapModified(true); }
		void setNbOfPageColumns(int columns)				{ fNbOfPageColumns = columns; localMapModified(true); }
		void setNbOfPageRows(int rows)						{ fNbOfPageRows = rows; localMapModified(true); }

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);		
		/// \brief the \c 'map' message handler
		MsgHandler::msgStatus mapMsg (const IMessage* msg );
		
		/// \brief Overrides IObject to handle 'get map' msg.
		IMessageList getMsgs(const IMessage* msg) const;
};

/*! @} */

} // end namespoace

#endif
