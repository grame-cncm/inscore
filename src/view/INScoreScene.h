/*

  INScore viewer
  Copyright (C) 2011  Grame

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

#ifndef __INScoreScene__
#define __INScoreScene__

#include <QGraphicsScene>
#include <string>

#include "smartpointer.h"

class QEvent;
class IScene;

//_______________________________________________________________________
class INScoreScene : public QGraphicsScene
{
	inscore::SMARTP<inscore::IScene> fScene;		// the corresponding scene
	
	public:
				 INScoreScene (const std::string& address, inscore::SMARTP<inscore::IScene> scene);
		virtual ~INScoreScene() {}

	protected:
		std::string	fOscAddress;
		
		const char*	extension ( const char* file ) const;
		std::string	makename ( const char* file ) const;
		std::string	tr ( const std::string& name ) const;

		void	open ( const char* file );
		void	openscene ( const char* file );
		void	openfile ( const char* file );
		void	dropEvent ( QGraphicsSceneDragDropEvent * event );
		void	dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
		void	dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
};



#endif
