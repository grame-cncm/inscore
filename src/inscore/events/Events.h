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

#ifndef __Events__
#define __Events__

namespace inscore
{

extern const char* kMouseMoveEvent;
extern const char* kMouseDownEvent;
extern const char* kMouseUpEvent;
extern const char* kMouseEnterEvent;
extern const char* kMouseLeaveEvent;
extern const char* kMouseDoubleClickEvent;

extern const char* kTouchBeginEvent;
extern const char* kTouchEndEvent;
extern const char* kTouchUpdateEvent;

extern const char* kTimeEnterEvent;
extern const char* kTimeLeaveEvent;
extern const char* kDurEnterEvent;
extern const char* kDurLeaveEvent;
extern const char* kExportEvent;
extern const char* kNewDataEvent;

// gesture specific events
extern const char* kGFEnterEvent;
extern const char* kGFLeaveEvent;
extern const char* kGFActiveEvent;
extern const char* kGFIdleEvent;

// URL specific events
extern const char* kSuccessEvent;
extern const char* kErrorEvent;
extern const char* kCancelEvent;

// scene specific events
extern const char* kEndPaintEvent;
extern const char* kNewElementEvent;

// score specific events
extern const char* kPageCountEvent;

// video specific events
extern const char* kEndEvent;
extern const char* kReadyEvent;

} // end namespoace

#endif

