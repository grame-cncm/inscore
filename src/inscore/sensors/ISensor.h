/*

  INScore Project

  Copyright (C) 2016  Grame

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

#ifndef __ISensor__
#define __ISensor__

#include <cmath>
#include <QObject>

#include "ISignal.h"

class QSensor;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

//------------------------------------------------------------------------
class ISensor : public ISignal, public QObject
{
	private:
		QSensor*	fSensor;
		int			fTimerID;
		float		fAlpha;			// the smoothing factor
	
	public:
		static const std::string kSensorType;
		virtual		bool activate(bool val);
	
	protected:
		bool		fIsSignal;

				 ISensor(const std::string& name, IObject * parent);
		virtual ~ISensor();

		void timerEvent(QTimerEvent * );
		virtual void readData () = 0;			///< called by the time task

		/// \brief sets the message handlers.
		virtual void setHandlers ();

		float smooth (float val, float prev)	{ return fAlpha*val + (1-fAlpha)*prev;}
		virtual float getSmooth () const		{ return fAlpha; }
		virtual void  setSmooth (float alpha)	{ fAlpha = std::max(0.f, std::min(alpha, 1.f)); }

		virtual void setSigSize (int size) = 0;		///< set the signal size
	
		SIMessageList getSetMsg() const;

		/// \brief the \c 'run' message handler
		virtual MsgHandler::msgStatus run(const IMessage* msg);
		virtual bool running () const;

		/// \brief object \c 'set' message handler.
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief osc \c 'size' message handler
		virtual MsgHandler::msgStatus sizeMsg (const IMessage* msg);

		void		print (IMessage& out) const;
		bool		setSensor(QSensor* sensor);
		QSensor*	getSensor() const			{ return fSensor; };

		template <typename T> T max (T v1, T v2, T v3, T v4) const {
			return std::max(v1, std::max(v2, std::max(v3, v4)));
		}
};

/*! @} */

} // end namespoace

#endif
