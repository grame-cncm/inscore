/*

  INScore Project

  Copyright (C) 2012  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#include "Methods.h"

namespace inscore
{

const char* kabsolutexy_GetSetMethod= "absolutexy";		// Get Set
const char* kalias_GetSetMethod		= "alias";			// Get Set
const char* kalpha_GetSetMethod		= "alpha";			// Get Set
const char* kangle_GetSetMethod		= "angle";			// Get Set
const char* kblue_GetSetMethod		= "blue";			// Get Set
const char* kbrightness_GetSetMethod= "brightness";		// Get Set
const char* kclock_SetMethod		= "clock";			// Set
const char* kcolor_GetSetMethod		= "color";			// Get Set
const char* kcolumns_GetSetMethod	= "columns";		// Get Set
const char* kdalpha_SetMethod		= "dalpha";			// Set
const char* kdangle_SetMethod		= "dangle";			// Set
const char* kdate_GetSetMethod		= "date";			// Get Set
const char* kdblue_SetMethod		= "dblue";			// Set
const char* kdbrightness_SetMethod	= "dbrightness";	// Set
const char* kdcolor_SetMethod		= "dcolor";			// Set
const char* kddate_SetMethod		= "ddate";			// Set
const char* kdduration_SetMethod	= "dduration";		// Set
const char* kdebug_GetSetMethod		= "debug";			// Get Set
const char* kdefault_GetSetMethod	= "default";		// Get Set
const char* kdefaultShow_GetSetMethod = "defaultShow";	// Get Set
const char* kdel_SetMethod			= "del";			// Set
const char* kdgreen_SetMethod		= "dgreen";			// Set
const char* kdhsb_SetMethod			= "dhsb";			// Set
const char* kdhue_SetMethod			= "dhue";			// Set
const char* kdimension_GetMethod	= "dimension";		// Get
const char* kdpage_SetMethod		= "dpage";			// Set
const char* kdred_SetMethod			= "dred";			// Set
const char* kdsaturation_SetMethod	= "dsaturation";	// Set
const char* kdscale_SetMethod		= "dscale";			// Set
const char* kdurClock_SetMethod		= "durClock";		// Set
const char* kduration_GetSetMethod	= "duration";		// Get Set
const char* kdx_SetMethod			= "dx";				// Set
const char* kdxorigin_SetMethod		= "dxorigin";		// Set
const char* kdy_SetMethod			= "dy";				// Set
const char* kdyorigin_SetMethod		= "dyorigin";		// Set
const char* kdz_SetMethod			= "dz";				// Set
const char* keffect_GetSetMethod	= "effect";			// Get Set
const char* kerrport_GetSetMethod	= "errport";		// Get Set
const char* kexport_SetMethod		= "export";			// Set
const char* kforward_GetSetMethod	= "forward";		// Get Set
const char* kframeless_GetSetMethod	= "frameless";		// Get Set
const char* kfullscreen_GetSetMethod= "fullscreen";		// Get Set
const char* kget_SetMethod			= "get";			// Set
const char* kgreen_GetSetMethod		= "green";			// Get Set
const char* kheight_GetSetMethod	= "height";			// Get Set
const char* khello_SetMethod		= "hello";			// Set
const char* khsb_SetMethod			= "hsb";			// Set
const char* khue_GetSetMethod		= "hue";			// Get Set
const char* kin_GetMethod			= "in";				// Get
const char* kload_SetMethod			= "load";			// Set
const char* kmap_GetSetMethod		= "map";			// Get Set
const char* kmapplus_SetMethod		= "map+";			// Set
const char* kmapf_SetMethod			= "mapf";			// Set
const char* kmouse_SetMethod		= "mouse";			// Set
const char* kname_GetSetMethod		= "name";			// Get Set
const char* knew_SetMethod			= "new";			// Set
const char* korder_GetSetMethod		= "order";			// Get Set
const char* kosc_GetSetMethod		= "osc";			// Get Set
const char* kout_GetMethod			= "out";			// Get
const char* koutport_GetSetMethod	= "outport";		// Get Set
const char* kpage_GetSetMethod		= "page";			// Get Set
const char* kpageCount_GetMethod	= "pageCount";		// Get
const char* kpageFormat_GetSetMethod= "pageFormat";		// Get Set
const char* kpenAlpha_GetSetMethod	= "penAlpha";		// Get Set
const char* kpenColor_GetSetMethod	= "penColor";		// Get Set
const char* kpenStyle_GetSetMethod	= "penStyle";		// Get Set
const char* kpenWidth_GetSetMethod	= "penWidth";		// Get Set
const char* kpendAlpha_SetMethod	= "pendAlpha";		// Set
const char* kpop_SetMethod			= "pop";			// Set
const char* kport_GetSetMethod		= "port";			// Get Set
const char* kpush_SetMethod			= "push";			// Set
const char* kquit_SetMethod			= "quit";			// Set
const char* krate_GetSetMethod		= "rate";			// Get Set
const char* kred_GetSetMethod		= "red";			// Get Set
const char* krequire_SetMethod		= "require";		// Set
const char* kreset_SetMethod		= "reset";			// Set
const char* kresetBench_SetMethod	= "resetBench";		// Set
const char* krootPath_GetSetMethod	= "rootPath";		// Get Set
const char* krotatex_GetSetMethod	= "rotatex";		// Get Set
const char* krotatey_GetSetMethod	= "rotatey";		// Get Set
const char* krotatez_GetSetMethod	= "rotatez";		// Get Set
const char* krows_GetSetMethod		= "rows";			// Get Set
const char* krun_SetMethod			= "run";			// Set
const char* ksaturation_GetSetMethod= "saturation";		// Get Set
const char* ksave_SetMethod			= "save";			// Set
const char* kscale_GetSetMethod		= "scale";			// Get Set
const char* kset_SetMethod			= "set";			// Set
const char* kshear_GetSetMethod		= "shear";			// Get Set
const char* kshow_GetSetMethod		= "show";			// Get Set
const char* ksignal_GetMethod		= "signal";			// Get
const char* ksize_GetSetMethod		= "size";			// Get Set
const char* kstartBench_SetMethod	= "startBench";		// Set
const char* kstopBench_SetMethod	= "stopBench";		// Set
const char* ktime_GetSetMethod		= "time";			// Get Set
const char* kticks_GetSetMethod		= "ticks";			// Get Set
const char* kversion_GetMethod		= "version";		// Get
const char* kvideoMap_GetSetMethod	= "videoMap";		// Get Set
const char* kvideoMapf_SetMethod	= "videoMapf";		// Set
const char* kwatch_GetSetMethod		= "watch";			// Get Set
const char* kwatchplus_SetMethod	= "watch+";			// Get Set
const char* kwidth_GetSetMethod		= "width";			// Set
const char* kwindowOpacity_GetSetMethod = "windowOpacity";
const char* kwriteBench_SetMethod	= "writeBench";		// Set
const char* kx_GetSetMethod			= "x";				// Get Set
const char* kxborder_GetSetMethod	= "xborder";		// Get Set
const char* kxorigin_GetSetMethod	= "xorigin";		// Get Set
const char* ky_GetSetMethod			= "y";				// Get Set
const char* kyborder_GetSetMethod	= "yborder";		// Get Set
const char* kyorigin_GetSetMethod	= "yorigin";		// Get Set
const char* kz_GetSetMethod			= "z";				// Get Set

} //namespace
