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

#ifndef __Methods__
#define __Methods__

namespace inscore
{

extern const char* kabsolutexy_GetSetMethod;
extern const char* kaccept_GetSetMethod;
extern const char* kalias_GetSetMethod;
extern const char* kalpha_GetSetMethod;
extern const char* kangle_GetSetMethod;
extern const char* kanimate_GetSetMethod;
extern const char* kanimated_GetMethod;
extern const char* karrows_GetSetMethod;
extern const char* kautoVoicesColoration_GetSetMethod;
extern const char* kblue_GetSetMethod;
extern const char* kbrightness_GetSetMethod;
extern const char* kbrowse_SetMethod;
extern const char* kbrowse_SetMethod;
extern const char* kbrushStyle_GetSetMethod;
extern const char* kcancel_SetMethod;
extern const char* kclippitch_GetSetMethod;
extern const char* kcliptime_GetSetMethod;
extern const char* kclock_SetMethod;
extern const char* kclose_GetSetMethod;
extern const char* kcolor_GetSetMethod;
extern const char* kcolumns_GetSetMethod;
extern const char* kcompatibility_GetSetMethod;
extern const char* kconnect_GetSetMethod;
extern const char* kcount_GetMethod;
extern const char* kdalpha_SetMethod;
extern const char* kdangle_SetMethod;
extern const char* kdate_GetSetMethod;
extern const char* kdblue_SetMethod;
extern const char* kdbrightness_SetMethod;
extern const char* kdcolor_SetMethod;
extern const char* kddate_SetMethod;
extern const char* kdduration_SetMethod;
extern const char* kdebug_GetSetMethod;
extern const char* kdefault_GetSetMethod;
extern const char* kdefaultShow_GetSetMethod;
extern const char* kdel_SetMethod;
extern const char* kdend_SetMethod;
extern const char* kdgreen_SetMethod;
extern const char* kdhsb_SetMethod;
extern const char* kdhue_SetMethod;
extern const char* kdimension_GetMethod;
extern const char* kdisconnect_SetMethod;
extern const char* kdpage_SetMethod;
extern const char* kdrange_SetMethod;
extern const char* kdred_SetMethod;
extern const char* kdrotatex_SetMethod;
extern const char* kdrotatey_SetMethod;
extern const char* kdrotatez_SetMethod;
extern const char* kdsaturation_SetMethod;
extern const char* kdscale_SetMethod;
extern const char* kdstart_SetMethod;
extern const char* kdtempo_SetMethod;
extern const char* kduration_GetSetMethod;
extern const char* kdurClock_SetMethod;
extern const char* kdx_SetMethod;
extern const char* kdxorigin_SetMethod;
extern const char* kdy_SetMethod;
extern const char* kdyorigin_SetMethod;
extern const char* kdz_SetMethod;
extern const char* kedit_SetMethod;
extern const char* keffect_GetSetMethod;
extern const char* kend_GetSetMethod;
extern const char* kerror_SetMethod;
extern const char* kerrport_GetSetMethod;
extern const char* keval_SetMethod;
extern const char* kevent_SetMethod;
extern const char* kexport_SetMethod;
extern const char* kexportAll_SetMethod;
extern const char* kexpression_GetMethod;
extern const char* kfontFamily_GetSetMethod;
extern const char* kfontSize_GetSetMethod;
extern const char* kfontStyle_GetSetMethod;
extern const char* kfontWeight_GetSetMethod;
extern const char* kforeground_SetMethod;
extern const char* kforward_GetSetMethod;
extern const char* kframe_GetMethod;
extern const char* kframeless_GetSetMethod;
extern const char* kfullscreen_GetSetMethod;
extern const char* kget_SetMethod;
extern const char* kgreen_GetSetMethod;
extern const char* kguidoVersion_GetMethod;
extern const char* kheight_GetSetMethod;
extern const char* khello_SetMethod;
extern const char* khsb_SetMethod;
extern const char* khue_GetSetMethod;
extern const char* kin_GetMethod;
extern const char* kkeyboard_GetSetMethod;
extern const char* klevel_GetSetMethod;
extern const char* kload_SetMethod;
extern const char* klock_GetSetMethod;
extern const char* kmap_GetSetMethod;
extern const char* kmapf_SetMethod;
extern const char* kmapplus_SetMethod;
extern const char* kmeasureBars_GetSetMethod;
extern const char* kmls_GetMethod;
extern const char* kmouse_SetMethod;
extern const char* kmusicxmlVersion_GetMethod ;
extern const char* kname_GetSetMethod;
extern const char* knew_SetMethod;
extern const char* korder_GetSetMethod;
extern const char* kosc_GetSetMethod;
extern const char* kout_GetMethod;
extern const char* koutport_GetSetMethod;
extern const char* kpage_GetSetMethod;
extern const char* kpageCount_GetMethod;
extern const char* kpageFormat_GetSetMethod;
extern const char* kpath_GetSetMethod;
extern const char* kpenAlpha_GetSetMethod;
extern const char* kpenColor_GetSetMethod;
extern const char* kpendAlpha_SetMethod;
extern const char* kpenStyle_GetSetMethod;
extern const char* kpenWidth_GetSetMethod;
extern const char* kpitchLines_GetSetMethod;
extern const char* kplay_GetSetMethod;
extern const char* kpop_SetMethod;
extern const char* kport_GetSetMethod;
extern const char* kpush_SetMethod;
extern const char* kquit_SetMethod;
extern const char* kradius_GetSetMethod;
extern const char* krange_GetSetMethod;
extern const char* krate_GetSetMethod;
extern const char* krcount_GetMethod;
extern const char* kread_SetMethod;
extern const char* kred_GetSetMethod;
extern const char* kreject_GetSetMethod;
extern const char* krequire_SetMethod;
extern const char* kreset_SetMethod;
extern const char* kresetBench_SetMethod;
extern const char* krootPath_GetSetMethod;
extern const char* krotatex_GetSetMethod;
extern const char* krotatey_GetSetMethod;
extern const char* krotatez_GetSetMethod;
extern const char* krows_GetSetMethod;
extern const char* krun_SetMethod;
extern const char* ksaturation_GetSetMethod;
extern const char* ksave_SetMethod;
extern const char* kscale_GetSetMethod;
extern const char* kset_SetMethod;
extern const char* kshear_GetSetMethod;
extern const char* kshow_GetSetMethod;
extern const char* ksize_GetSetMethod;
extern const char* kstack_GetMethod;
extern const char* kstart_GetSetMethod;
extern const char* kstartBench_SetMethod;
extern const char* kstatus_GetMethod;
extern const char* kstopBench_SetMethod;
extern const char* ksuccess_SetMethod;
extern const char* ksystemCount_GetMethod;
extern const char* ktempo_GetSetMethod;
extern const char* kticks_GetSetMethod;
extern const char* ktime_GetSetMethod;
extern const char* kvdate_GetSetMethod;
extern const char* kvduration_GetMethod;
extern const char* kversion_GetMethod;
extern const char* kvideoMap_GetSetMethod;
extern const char* kvideoMapf_SetMethod;
extern const char* kvoiceColor_GetSetMethod;
extern const char* kvolume_GetSetMethod;
extern const char* kwatch_GetSetMethod;
extern const char* kwatchplus_SetMethod;
extern const char* kwidth_GetSetMethod;
extern const char* kwindowOpacity_GetSetMethod;
extern const char* kwrap_GetSetMethod;
extern const char* kwrite_SetMethod;
extern const char* kwriteBench_SetMethod;
extern const char* kx_GetSetMethod;
extern const char* kxborder_GetSetMethod;
extern const char* kxorigin_GetSetMethod;
extern const char* ky_GetSetMethod;
extern const char* kyborder_GetSetMethod;
extern const char* kyorigin_GetSetMethod;
extern const char* kz_GetSetMethod;


// gesture follower methods
extern const char* klearn_SetMethod;
extern const char* kfollow_SetMethod;
extern const char* kstop_SetMethod;
extern const char* klikelihoodwindow_GetSetMethod;
extern const char* ktolerance_GetSetMethod;
extern const char* kclear_SetMethod;
extern const char* klikelihoodthreshold_GetSetMethod;

// sensors methods
extern const char* kcalibrate_SetMethod;
extern const char* kmode_GetSetMethod;
extern const char* khasZ_GetMethod;
extern const char* kmax_GetSetMethod;
extern const char* ksmooth_GetSetMethod;


} //namespace

#endif
