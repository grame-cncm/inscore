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
const char* kaccept_GetSetMethod	= "accept";			// Get Set
const char* kalias_GetSetMethod		= "alias";			// Get Set
const char* kallnotesoff_SetMethod	= "allNotesOff";	// Set
const char* kalpha_GetSetMethod		= "alpha";			// Get Set
const char* kanimate_GetSetMethod	= "animate";		// Get Set
const char* kanimated_GetMethod		= "animated";		// Get
const char* kangle_GetSetMethod		= "angle";			// Get Set
const char* karrows_GetSetMethod	= "arrows";			// Get Set
const char* kautoScale_SetMethod	= "autoscale";		// Set
const char* kautoVoicesColoration_GetSetMethod = "autoVoicesColoration"; // Get Set
const char* kblue_GetSetMethod		= "blue";			// Get Set
const char* kbrightness_GetSetMethod= "brightness";		// Get Set
const char* kbrowse_SetMethod		= "browse";			// Set
const char* kcancel_SetMethod		= "cancel";			// Set
const char* kclass_GetSetMethod		= "class";			// Get Set
const char* kclients_GeMethod		= "clients";		// Get
const char* kcliptime_GetSetMethod	= "clipTime";		// Get Set
const char* kclippitch_GetSetMethod	= "clipPitch";		// Get Set
const char* kclock_SetMethod		= "clock";			// Set
const char* kclose_GetSetMethod		= "close";			// Get Set
const char* kcolor_GetSetMethod		= "color";			// Get Set
const char* kcolumns_GetSetMethod	= "columns";		// Get Set
const char* kcompatibility_GetSetMethod	= "compatibility";	// Get Set
const char* kcompute_GetSetMethod	= "compute";		// Get Set
const char* kcount_GetMethod		= "count";			// Get
const char* kconnect_GetSetMethod	= "connect";		// Get Set
const char* kdalpha_SetMethod		= "dalpha";			// Set
const char* kdangle_SetMethod		= "dangle";			// Set
const char* kdate_GetSetMethod		= "date";			// Get Set
const char* kdatef_GetMethod		= "date%f";			// Get Set
const char* kdatea_GetMethod		= "date%a";			// Get Set
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
const char* kdisconnect_SetMethod   = "disconnect";		// Set
const char* kdpage_SetMethod		= "dpage";			// Set
const char* kdred_SetMethod			= "dred";			// Set
const char* kdrange_SetMethod		= "drange";			// Set

const char* kdrotatex_SetMethod		= "drotatex";		// Set
const char* kdrotatey_SetMethod		= "drotatey";		// Set
const char* kdrotatez_SetMethod		= "drotatez";		// Set
const char* kdshear_SetMethod		= "dshear";			// Set

const char* kdsaturation_SetMethod	= "dsaturation";	// Set
const char* kdscale_SetMethod		= "dscale";			// Set
const char* kdstart_SetMethod		= "dstart";			// Set
const char* kdtempo_SetMethod		= "dtempo";			// Set
const char* kdurClock_SetMethod		= "durClock";		// Set
const char* kduration_GetSetMethod	= "duration";		// Get Set
const char* kdvolume_SetMethod		= "dvolume";		// Set
const char* kdx_SetMethod			= "dx";				// Set
const char* kdxorigin_SetMethod		= "dxorigin";		// Set
const char* kdy_SetMethod			= "dy";				// Set
const char* kdyorigin_SetMethod		= "dyorigin";		// Set
const char* kdz_SetMethod			= "dz";				// Set
const char* kedit_SetMethod			= "edit";			// Set
const char* keffect_GetSetMethod	= "effect";			// Get Set
const char* kend_GetSetMethod		= "end";			// Get Set
const char* kerror_SetMethod		= "error";			// Set
const char* kerrorAddress_GetSetMethod	= "errorAddress";	// Get Set
const char* kerrport_GetSetMethod	= "errport";		// Get Set
const char* kexpression_GetMethod	= "expr";			// Get
const char* keval_SetMethod			= "eval";			// Set
const char* kevent_SetMethod		= "event";			// Set
const char* kexport_SetMethod		= "export";			// Set
const char* kexportAll_SetMethod	= "exportAll";		// Set
const char* kfontSize_GetSetMethod	= "fontSize";		// Get Set
const char* kfontFamily_GetSetMethod= "fontFamily";		// Get Set
const char* kfontStyle_GetSetMethod	= "fontStyle";		// Get Set
const char* kfontWeight_GetSetMethod= "fontWeight";		// Get Set
const char* kforeground_SetMethod	= "foreground";		// Set
const char* kforward_GetSetMethod	= "forward";		// Get Set
const char* kframeless_GetSetMethod	= "frameless";		// Get Set
const char* kframe_GetMethod		= "frame";			// Get
const char* kfullscreen_GetSetMethod= "fullscreen";		// Get Set
const char* kget_SetMethod			= "get";			// Set
const char* kgreen_GetSetMethod		= "green";			// Get Set
const char* kheight_GetSetMethod	= "height";			// Get Set
const char* khello_SetMethod		= "hello";			// Set
const char* khsb_SetMethod			= "hsb";			// Set
const char* khue_GetSetMethod		= "hue";			// Get Set
const char* kin_GetMethod			= "in";				// Get
const char* kIP_GetMethod			= "IP";				// Get
const char* kkeyboard_GetSetMethod	= "keyboard";		// Get Set
const char* kkeyon_SetMethod		= "keyOn";			// Get Set
const char* kkeyoff_SetMethod		= "keyOff";			// Set
const char* klevel_GetSetMethod		= "level";			// Get Set
const char* kload_SetMethod			= "load";			// Set
const char* klock_GetSetMethod		= "lock";			// Get Set
const char* kmap_GetSetMethod		= "map";			// Get Set
const char* kmapplus_SetMethod		= "map+";			// Set
const char* kmapf_SetMethod			= "mapf";			// Set
const char* kmeasureBars_GetSetMethod = "measureBars";	// Get Set
const char* kmls_GetMethod			= "mls";			// Get
const char* kmouse_SetMethod		= "mouse";			// Set
const char* kname_GetSetMethod		= "name";			// Get Set
const char* knew_SetMethod			= "new";			// Set
const char* kopengl_GetSetMethod	= "opengl";			// Get Set
const char* korder_GetSetMethod		= "order";			// Get Set
const char* kosc_GetSetMethod		= "osc";			// Get Set
const char* kout_GetMethod			= "out";			// Get
const char* koutport_GetSetMethod	= "outport";		// Get Set
const char* kpage_GetSetMethod		= "page";			// Get Set
const char* kpageCount_GetMethod	= "pageCount";		// Get
const char* kpitchLines_GetSetMethod= "pitchLines";		// Get Set
const char* kpath_GetSetMethod		= "path";			// Get Set
const char* ksystemCount_GetMethod	= "systemCount";	// Get
const char* kpageFormat_GetSetMethod= "pageFormat";		// Get Set
const char* kpenAlpha_GetSetMethod	= "penAlpha";		// Get Set
const char* kpenColor_GetSetMethod	= "penColor";		// Get Set
const char* kpenStyle_GetSetMethod	= "penStyle";		// Get Set
const char* kpenWidth_GetSetMethod	= "penWidth";		// Get Set
const char* kbrushStyle_GetSetMethod= "brushStyle";		// Get Set
const char* kpaths_GetMethod		= "paths";			// Get
const char* kparse_GetSetMethod		= "parse";			// Get Set
const char* kpendAlpha_GetSetMethod	= "pendAlpha";		// Set
const char* kpendAlpha_SetMethod	= "pendAlpha";		// Set
const char* kpop_SetMethod			= "pop";			// Set
const char* kplay_GetSetMethod		= "play";			// Get Set
const char* kport_GetSetMethod		= "port";			// Get Set
const char* kpreprocess_SetMethod	= "preprocess";		// Set
const char* kpush_SetMethod			= "push";			// Set
const char* kquit_SetMethod			= "quit";			// Set
const char* kradius_GetSetMethod	= "radius";			// Get Set
const char* krange_GetSetMethod		= "range";			// Get Set
const char* krate_GetSetMethod		= "rate";			// Get Set
const char* krcount_GetMethod		= "rcount";			// Get
const char* kred_GetSetMethod		= "red";			// Get Set
const char* kread_SetMethod			= "read";			// Set
const char* kreject_GetSetMethod	= "reject";			// Get Set
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
//const char* ksignal_GetMethod		= "signal";			// Get
const char* ksize_GetSetMethod		= "size";			// Get Set
const char* kstack_GetMethod		= "stack";			// Get
const char* kstart_GetSetMethod		= "start";			// Get Set
const char* kstatus_GetMethod		= "status";			// Get
const char* kstartBench_SetMethod	= "startBench";		// Set
const char* kstopBench_SetMethod	= "stopBench";		// Set
const char* ksuccess_SetMethod      = "success";		// Set
const char* ktempo_GetSetMethod		= "tempo";			// Get Set
const char* ktext_GetMethod			= "text";			// Get
const char* ktime_GetSetMethod		= "time";			// Get Set
const char* kticks_GetSetMethod		= "ticks";			// Get Set
const char* kui_GetMethod			= "ui";				// Get
const char* kversion_GetMethod		= "version";		// Get

const char* kguidoVersion_GetMethod = "guido-version";	// Get
const char* kmusicxmlVersion_GetMethod = "musicxml-version";	// Get

const char* kvideoMap_GetSetMethod	= "videoMap";		// Get Set
const char* kvideoMapf_SetMethod	= "videoMapf";		// Set
const char* kvoiceColor_GetSetMethod = "voiceColor";	// Get Set
const char* kvdate_GetSetMethod		= "vdate";			// Get Set
const char* kvduration_GetMethod	= "vduration";		// Get
const char* kvolume_GetSetMethod	= "volume";			// Get Set
const char* kwasm_GetMethod			= "wasm";			// Get
const char* kwatch_GetSetMethod		= "watch";			// Get Set
const char* kwatchplus_SetMethod	= "watch+";			// Get Set
const char* kwidth_GetSetMethod		= "width";			// Set
const char* kwindowOpacity_GetSetMethod = "windowOpacity";
const char* kwrap_GetSetMethod		= "wrap";			// Get Set
const char* kwriteBench_SetMethod	= "writeBench";		// Set
const char* kwrite_SetMethod		= "write";		// Set
const char* kx_GetSetMethod			= "x";				// Get Set
const char* kxborder_GetSetMethod	= "xborder";		// Get Set
const char* kxorigin_GetSetMethod	= "xorigin";		// Get Set
const char* ky_GetSetMethod			= "y";				// Get Set
const char* kyborder_GetSetMethod	= "yborder";		// Get Set
const char* kyorigin_GetSetMethod	= "yorigin";		// Get Set
const char* kz_GetSetMethod			= "z";				// Get Set

const char* ksceneHeight_GetMethod   = "sheight";		// Get Set
const char* ksceneWidth_GetMethod    = "swidth";		// Get Set

// gesture follower methods
const char* klearn_SetMethod				= "learn";					// Set
const char* kfollow_SetMethod				= "follow";					// Set
const char* kstop_SetMethod					= "stop";					// Set
const char* klikelihoodwindow_GetSetMethod	= "likelihoodwindow";		// Get Set
const char* klikelihoodthreshold_GetSetMethod= "likelihoodthreshold";	// Get Set

const char* ktolerance_GetSetMethod			= "tolerance";				// Get Set
const char* kclear_SetMethod				= "clear";					// Set

// sensors methods
const char* kcalibrate_SetMethod		= "calibrate";				// Set
const char* khasZ_GetMethod				= "hasZ";					// Get
const char* kmax_GetSetMethod			= "max";					// Get Set
const char* kmode_GetSetMethod			= "mode";					// Get Set
const char* ksmooth_GetSetMethod		= "smooth";					// Get Set

// refresh method
// introduced for the javascript implementation
const char* krefresh_SetMethod		= "refresh";					// Set

// ssl methods
const char* kcert_GetSetMethod			= "cert";				// Get Set
const char* kcacert_GetSetMethod		= "cacert";				// Get Set
const char* kkey_GetSetMethod			= "key";				// Get Set

// MIDI methods
const char* kinit_SetMethod				= "init";				// Set
const char* kverbose_GetSetMethod		= "verbose";			// Get Set

} //namespace
