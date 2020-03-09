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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#pragma once

#include <string>

#include "HTMLObjectView.h"

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class IScene;

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IScene.
*/
class VSceneView : public HTMLObjectView
{
	public :
		using VObjectView::updateView;

				 VSceneView();
		virtual ~VSceneView();

		virtual TFloatRect referenceRect(VObjectContext item) const;

		void 	updateView( IScene * scene );
		void	foreground() {}
	
};


/*!@} */

} // end namespoace
