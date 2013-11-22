/* 
	icons.css (13,311), 
	general.css (4,176), 
	general.css (358), 
	_icons.css (6,614), 
	button-skin.css (5,282), 
	container.css (5,205), 
	dialog.css (341), 
	thickbox.css (3,591), 
	jquery.autocomplete.css (858), 
	messaging.css (1,405), 
	controls.css (4,595), 
	reports.css (8,891), 
	pagination.css (2,462), 
	2010.css (3,727), 
	files_table.css (1,491), 
	image_gallery_lite.css (291), 
	skin.css (7,346), 
	page_tags.css (3,039), 
	page_alerts.css (1,147), 
	page_content_rating.css (1,749), 
	page_title_editor.css (3,148), 
	jquery.qtip.css (96)
 */

/* --------- ICONS.CSS --------- */
/*
 * MindTouch Deki - enterprise collaboration and integration platform
 *  derived from MediaWiki (www.mediawiki.org)
 * Copyright (C) 2006-2009 MindTouch, Inc.
 * www.mindtouch.com  oss@mindtouch.com
 *
 * For community documentation and downloads visit www.opengarden.org;
 * please review the licensing section.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * http://www.gnu.org/copyleft/gpl.html
 */

/* (general icon styles) ---------------------------------------------------------*/

.attach-16,
#topic a.attach-16 {
	background-repeat: no-repeat;
	background-position: 1px center;
	padding: 2px 0 2px 18px;
	line-height: 18px;
	color: #205352;
	text-decoration: none;
}
.buttonify {
	width: 16px;
	height: 16px;
	line-height: 20px;
	display: block;
	background-repeat: no-repeat;
	background-position: center left;
	cursor: pointer;
}
.nul {
	text-decoration: none;
}
a.iconify,
a:link.iconify,
a:visited.iconify,
a:hover.iconify {
	padding-left: 15px;
	min-height: 12px;
	height: auto;
}
* .iconify a { /*\*/ height: 12px; }

.diconify {
	min-height: 18px;
	line-height: 18px;
	padding: 2px 0 2px 21px;
	background-position: center left;
}

a.iconify-16,
.iconify-16,
.iconifym-16,
a.iconifym-16 {
	line-height: 18px;
	padding: 2px 0 2px 21px;
	height: auto;
}
a.iconify-16,
.iconify-16 {
	background-position: top left;
}
a.iconifym-16,
.iconifym-16 {
	line-height: 18px;
	padding: 2px 0 3px 21px;
	background-position: 1px center;
}
* .iconify-16 a { /*\*/ height: 18px; }

a.iconitext-16 {
	margin: 0 0 0 0;
	min-height: 18px;
	padding: 3px 0 3px 21px;
	background: url(/skins/common/icons/file-unknown.png) no-repeat center left;
	height: auto;
}
.nav,
.iconify,
.iconify-16,
.iconitext-16,
.iconifym-16 {
	background-repeat: no-repeat;
	background-position: 1px center;
}
.redirectedFrom {
	padding-left: 22px;
	background: url('icons/icon-redirect.gif') no-repeat center left;
}
div.redirectedTo span {
	padding-right: 22px;
	background: url('icons/icon-redirect.gif') no-repeat center right;
}
/* (iconifying external links - css3) -------------------------------------------*/
#topic a.external {
    background: url('icons/icon-external.gif') no-repeat center right;
    padding-right: 13px;
}
#topic a.link-https {
    background: url('icons/icon-lock.gif') no-repeat center right;
    padding-right: 16px;
}
#topic a.link-mailto {
    background: url('icons/icon-mail.gif') no-repeat center right;
    padding-right: 18px;
}
#topic a.link-news {
    background: url('icons/icon-news.gif') no-repeat center right;
    padding-right: 18px;
}
#topic a.link-ftp {
    background: url('icons/icon-file.gif') no-repeat center right;
    padding-right: 18px;
}
#topic a.link-irc {
    background: url('icons/icon-discuss.gif') no-repeat center right;
    padding-right: 18px;
}
#articleText a.link-user,
#attachTable a.link-user,
div.modified a.link-user {
    background: url('icons/icon-user-s.gif') no-repeat center left;
    padding-left: 14px;
}
.icon-expand {
	background: url('icons/icon-expand.gif')  no-repeat center left;
}

/***
 * icons
 */
a.iconitext {
	text-decoration: none;
	white-space: nowrap;
}
a.iconitext span.text {
	text-decoration: underline;
	padding-left: 2px;
}
.loggedinicon {
	height: 23px;
	overflow: hidden;
}
.icon-s {
	height: 12px;
	overflow: hidden;
}
span.icon {
	height: 16px;
	overflow: hidden;
}
.icon14 {
	height: 14px;
	overflow: hidden;
}
.icon-s img {
	background-image: url('icons/icons.gif');
	background-repeat: no-repeat;
	width: 12px;
}
span.icon img,
.loggedinicon img,
.icon14 img {
	background-image: url('icons/icons.gif');
	background-repeat: no-repeat;
	width: 16px;
}
.icon14 img {
	width: 14px;
}
.loggedinicon img {
	height: 23px;
}
.icon img.icon-s {
	width: 12px;
	height: 12px;
}
a.dd-header .icon img.icon-s {
	height: 16px;
}
.icon-5 {
	font-size: 5px;
	height: 5px;
	overflow:hidden;
}
.icon-5 img {
	background-image: url('icons/icons.gif');
	background-repeat: no-repeat;
	width: 16px;
}
.icon-5 img.icon {
	height: 5px;
}
.icon-11 img {
	background-image: url('icons/icons.gif');
	background-repeat: no-repeat;
	width: 11px;
	height: 11px;
}
.icon img.user					{ background-position: 0px -288px; }
.icon img.ns-user,
.icon img.ns-usertalk			{ background-position: 0px -2272px; }
.icon img.edit, 
.icon img.pageedit				{ background-position: 0px -561px; }
.icon img.attach-add 			{ background-position: 0px -848px; }
.icon img.pageemail 			{ background-position: 0px -32px; }
.icon img.pageemail-disabled	{ background-position: 0px -48px; }
.icon img.attach-remove 		{ background-position: 0px -832px; }
.icon img.recentchanges 		{ background-position: 0px -864px; }
.icon img.controlpanellink, 
.icon img.controlpanel	 		{ background-position: 0px -912px; }
.icon img.listrss 				{ background-position: 0px -992px; }
.icon img.listusers, 
.icon img.userlist	 			{ background-position: 0px -800px; }
.icon img.listguests 			{ background-position: 0px -1808px; }
.icon img.sectionedit 			{ background: url(/skins/common/icons/edit.png) no-repeat }
.icon img.templatesroot, 
.icon img.templatelist, 
.icon img.ns-template	 		{ background-position: 0px -816px; }
.icon img.allpages,
.icon img.sitemap 				{ background-position: 0px -448px; }
.icon img.popularpages 			{ background-position: 0px -896px; }
.icon img.wantedpages 			{ background-position: 0px -784px; }
.icon img.lonelypages 			{ background-position: 0px -928px; }
.icon img.doubleredirects 		{ background-position: 0px -368px; }
.icon img.innavlink,
.icon img.document	 			{ background-position: 0px -768px; }
.icon img.exnavlink 			{ background-position: 0px -512px; }
.icon img.preferences 			{ background-position: 0px -320px; }
.icon img.watchlist,
.icon img.watchedpages 			{ background-position: 0px -352px; }
.icon img.mycontris, 
.icon img.contributions			{ background-position: 0px -944px; }
.icon img.logout	 			{ background-position: 0px -1008px;}
.icon img.edit		 			{ background-position: 0px -560px; }
.icon img.edit-disabled			{ background-position: 0px -544px; }
.icon img.addSubpage 			{ background-position: 0px -688px; }
.icon img.addSubpage-disabled	{ background-position: 0px -672px; }
.icon img.print		 			{ background-position: 0px -432px; }
.icon img.print-disabled		{ background-position: 0px -416px; }
.icon img.tag,
.icon img.tag-disabled			{ background-position: 0px -64px; }
.icon img.anonlogin				{ background-position: 0px -704px;}
.icon img.watch					{ background-position: 0px -2176px; }
.icon img.watch-disabled 		{ background-position: 0px -2192px; }
.icon img.unwatch	 			{ background-position: 0px -336px; }
.icon img.attach	 			{ background-position: 0px -656px; }
.icon img.attach-disabled		{ background-position: 0px -640px; }
.icon img.move		 			{ background-position: 0px -400px; }
.icon img.dotcontinue			{ background-position: 0px -960px; }
.icon img.delete		 		{ background-position: 0px -592px; }
.icon img.move-disabled			{ background-position: 0px -384px; }
.icon img.delete-disabled		{ background-position: 0px -576px; }
.icon img.home			 		{ background-position: 0px -480px; }
.icon img.contextmenu			{ background-position: 0px -464px; }
.icon14 img.contextmenu			{ background-position: 0px -464px; }
.icon img.specialpages			{ background-position: 0px -464px; }
.icon img.menuarrow				{ background-position: 0px -752px; }
.icon img.menuarrow-disabled	{ background-position: 0px -1279px; }
.icon img.file					{ background-position: 0px -1040px; }
.icon img.file-disabled			{ background-position: 0px -1056px; }
.icon img.alert					{ background-position: 0px -1104px; }
.icon img.lock					{ background-position: 0px -1120px; }
.icon img.referring				{ background-position: 0px -1136px; }
.icon img.referring-disabled	{ background-position: 0px -1248px; }
.icon img.toc					{ background-position: 0px -625px; }
.icon img.toc-disabled			{ background-position: 0px -1264px; }
.icon img.restrict				{ background-position: 0px -1200px; }
.icon img.restrict-disabled		{ background-position: 0px -1440px; }
.icon img.pageproperties, 
.icon img.properties			{ background-position: 0px -2112px; }
.icon img.pageproperties-disabled, 
.icon img.properties-disabled	 { background-position: 0px -2128px; }
.icon img.pagetalk, 
.icon img.ns-talk				{ background-position: 0px -2144px; }
.icon img.pagetalk-disabled		{ background-position: 0px -2160px; }
.icon img.expand				{ background-position: 0px -1216px; }
.icon img.contract				{ background-position: 0px -1232px; }
.icon-s img.contract			{ background-position: 0px -1072px; }
.icon img.menuarrow				{ background-position: 0px -752px; }
.icon img.attachfile			{ background-position: 0px -736px;}
.icon img.attachfile-no			{ background-position: 0px -720px; }
.icon img.usercreate			{ background-position: 0px -1296px; }
.icon img.menudown				{ background-position: 0px -1312px; }
.icon img.menudownsimple		{ background-position: 0px -1520px; }
.icon-5 img.menudown2			{ background-position: 0px -1510px; }
.icon img.attachfiles			{ background-position: 0px -1696px; }
.icon img.attachoriginal		{ background-position: 0px -1040px; }
.icon img.attachedit			{ background-position: 0px -1328px; }
.icon img.attachedit-disabled	{ background-position: 0px -1456px; }
.icon img.attachdel				{ background-position: 0px -1344px; }
.icon img.attachdel-disabled	{ background-position: 0px -1472px; }
.icon img.attachhist 			{ background-position: 0px -1632px; }
.icon img.attachhist-disabled	{ background-position: 0px -1648px; }
.icon img.attachmove			{ background-position: 0px -1408px; }
.icon img.attachmove-disabled	{ background-position: 0px -1488px; }
.icon img.email					{ background-position: 0px -1424px; }
.icon img.gallery	 			{ background-position: 0px -1536px; }
.icon img.loggedina 			{ background-position: 0px -1552px; }
.icon-s img.cancel	 			{ background-position: 0px -1616px; }
.icon img.attachfiles 			{ background-position: 0px -1632px; }
.icon-s img.smallattach 		{ background-position: 0px -1664px; }
.icon img.justifyleft 			{ background-position: 0px -1696px;}
.icon img.justifyfull			{ background-position: 0px -1712px;}
.icon img.justifycenter			{ background-position: 0px -1728px;}
.icon img.justifyright 			{ background-position: 0px -1744px;}
.icon img.folder	 			{ background-position: 0px -1760px;}
.icon img.folder-disabled		{ background-position: 0px -1776px;}
.icon img.invite				{ background-position: 0px -1792px;}
.icon img.remove-disabled		{ background-position: 0px -1824px;}
.icon img.add-disabled			{ background-position: 0px -1840px;}
.icon img.comments				{ background-position: 0px -2080px;}
.icon img.commentedit			{ background-position: 0px -2096px;}
.icon img.commentdelete			{ background-position: 0px -2112px;}
.icon img.about					{ background-position: 0px -16px; }
.icon img.key					{ background-position: 0px -2208px;}
.icon img.deki-desktop-suite	{ background-position: 0px -2224px;}
.icon img.source				{ background-position: 0px -2240px;}
.icon img.source-disabled		{ background-position: 0px -2256px;}

/***
 * New, consistent styles
 */
.icon img.mt-ext-sh,
.icon img.mt-ext-txt 			{ background-position: 0px -1856px; }
.icon img.mt-ext-ppt, 
.icon img.mt-ext-pptm, 
.icon img.mt-ext-potx, 
.icon img.mt-ext-potm, 
.icon img.mt-ext-ppam, 
.icon img.mt-ext-pps, 
.icon img.mt-ext-ppsx,
.icon img.mt-ext-ppsm, 
.icon img.mt-ext-pptx			{ background-position: 0px -1872px; }
.icon img.mt-ext-jpg,
.icon img.mt-ext-jpeg,
.icon img.mt-ext-jpe,
.icon img.mt-ext-gif,
.icon img.mt-ext-png			{ background-position: 0px -1888px; }
.icon img.mt-ext-swf,
.icon img.mt-ext-fla			{ background-position: 0px -1904px; }
.icon img.mt-ext-xls, 
.icon img.mt-ext-csv, 
.icon img.mt-ext-xlsm, 
.icon img.mt-ext-xltx, 
.icon img.mt-ext-xltm, 
.icon img.mt-ext-xlsn, 
.icon img.mt-ext-xlam, 
.icon img.mt-ext-xlsx			{ background-position: 0px -1920px; }
.icon img.mt-ext-zip			{ background-position: 0px -1936px; }
.icon img.mt-ext-pdf,
.icon img.pdf					{ background-position: 0px -1952px; }
.icon img.mt-ext-unknown		{ background-position: 0px -1968px; }
.icon img.mt-ext-tar,
.icon img.mt-ext-rar,
.icon img.mt-ext-gzip			{ background-position: 0px -1984px; }
.icon img.mt-ext-doc,
.icon img.mt-ext-rtf,
.icon img.mt-ext-docm,
.icon img.mt-ext-dotx,
.icon img.mt-ext-dotm,
.icon img.mt-ext-docx			{ background-position: 0px -2000px; }
.icon img.mt-ext-wmv,
.icon img.mt-ext-avi,
.icon img.mt-ext-mpg,
.icon img.mt-ext-mov,
.icon img.mt-ext-mp4,
.icon img.mt-ext-mpeg			{ background-position: 0px -2032px; }
.icon img.mt-ext-html,
.icon img.mt-ext-htm,
.icon img.mt-ext-shtml			{ background-position: 0px -2048px; }
.icon img.mt-ext-mp3			{ background-position: 0px -2064px; }


/* --------- GENERAL.CSS --------- */
strike, 
td.strikeout {
	text-decoration: line-through;
}
img {
	border: none;
}
div.autocomplete {
	position:absolute;
	width:350px;
	background-color:white;
	border:1px solid #888;
	margin:0px;
	padding:0px;
	font-size: 11px;
}
div.autocomplete ul {
	list-style-type:none;
	margin:0px;
	padding:0px;
}
div.autocomplete ul li.selected { background-color: #ffb;}
div.autocomplete ul li {
	list-style-type:none;
	display: block;
	margin:0;
	padding:2px;
	cursor:pointer;
}

/***
 * Edit this to set some styling on the section that will be edited
 */
.editIcon {
	display: inline; visibility: hidden; margin-left: 4px; font-size: 11px; font-weight: normal;
}

#pageTags {
	clear: both;
}
#pageToc {
	display: none;
}
/***
 * Spacing of each tagging line
 */
div.pageTagList div.item {
	padding: 4px 0;
}
div.pageTagList div.relatedpages {
	display: block;
}

div.pageRelated, dt.pageRelated {
	clear: both;
}

/***
 * Navigation styles
 */
#siteNavTree a {
	display: block;
	text-decoration: none;
	padding-right: 5px;
	padding-left: 7px;
	width: 163px;
	font-size: 11px;
	height: 24px;
}
#siteNavTree div.node a {
	overflow: hidden;
	line-height: 24px;
}
#siteNavTree div.node{
	overflow: hidden;
}
#siteNavTree div.selectedChild a {
	font-weight: normal;
	padding-left: 16px;
	padding-right: 3px;
	width: 143px;
}
#siteNavTree div.node a span {
	padding-left: 16px;
}
#siteNavTree div.parentOpen a span {
	background: transparent url(/skins/common/images/nav-parent-open.gif) no-repeat center left;
}
#siteNavTree div.parentClosed a span {
	background: transparent url(/skins/common/images/nav-parent-closed.gif) no-repeat center left;
}
#siteNavTree div.dockedNode a span {
	background: transparent url(/skins/common/images/nav-parent-open.gif) no-repeat center left;
}
#siteNavTree div.homeNode a span {
	background: transparent url(/skins/common/images/nav-home.gif) no-repeat center left;
}
#siteNavTree div.selected a {
	font-weight: bold;
}
#siteNavTree img.nodeImage{
	padding-right: 5px;
}
#siteNavTree div.sibling img.nodeImage{
	padding-left: 4px;
	padding-right: 9px;
}
#siteNavTree div.closedNode{
	height: 0px;
	display: none;
}
#siteNavTree img{
	border: 0;
}

#printfooter, 
.urlexpansion, 
#pageAttachForm, 
#printOptions {
	display: none;
}
table.feedtable {
	width: 100%;
	line-height:1.5em;
	overflow: hidden;
}
table.feedtable th {
	padding: 6px 9px 5px 9px;
	text-align: left;
	border-left: none;
}
table.feedtable tr td {
	padding: 6px 9px 5px 9px;
	text-align: left;
	border-left: none;
}
div.menu {
	position: absolute;
	z-index: 9999;
}
div.pageRevision ins {
	color: #009900;
	background-color: #ccffcc;
	text-decoration: none;
}
div.pageRevision del {
	color: #990000;
	background-color: #ffcccc;
	text-decoration: none;
}
/***
 * Warning message from Live Services
 */
span.warning {
	font-weight: bold;
	color: #f00;
}

/***
 * Expired status message
 */
#deki-license-banner,
div.expired {
	background-color: #fffbc5;
	border-bottom: 1px solid #9d0a0e;
	padding: 5px;
	text-align: center;
	color: #9d0a0e;
	font-weight: bold;
	font-size: 12px;
}
div.expired a {
	color: #9D0A0E;
	text-decoration: none;
	padding: 10px 0;
	display: block;
	font-family: Verdana, Sans-Serif;
}
div.expired span.underline {
	text-decoration: underline;
}

/***
 * Some diff styles 
 * TODO: we need to start classing names consistently
 */ 
div.deki-revision {
	float: left; 
	width: 50%;
}

/*** 
 * WebDAV edit icon (only for IE - jQuery will enable this)
 */
a.deki-webdavdoc {
	display: none;
}
/***
 * New page title view
 */
.deki-new-page-title {
	-moz-border-radius:5px 5px 5px 5px;
	border: 1px solid #D3D3D3; 
	background-color: #fff; 
	padding: 5px;
	margin-bottom: 10px;
}
.deki-new-page-title input {
	width: 98%;
	font-size: 20px;
	padding: 2px;
	font-weight: bold;
}
/***
 * Upon initial installation, all the templates might not populate
 */
div.mt-populating {
	width: 480px;
	margin: 0 auto;
	border: 1px solid #aaa;
	padding: 8px 8px 8px 48px;
	background: #efefef url(/skins/common/icons/icon-32-error.gif) no-repeat 4px 4px;
}
div.mt-populating h2 {
	border: none;
	color: #000;
	font-weight: bold;
	font-size: 18px;
	margin: 0;
	padding: 0;	
}

/* --------- GENERAL.CSS --------- */
/* Styles available to all dekiscript templates */

div.error-dependency {
	padding: 8px 5px 8px 42px;
	background: #FFF9AE url("/skins/common/icons/icon-32-error.gif") no-repeat scroll 4px 4px;
	border: 1px solid #ABA000;
	font-weight: bold;
	font-size: 14px;
	color: #9D0A0E;
}

.error-dekiscript {
	font-weight: bold;
	font-size: 14px;
	color: #9D0A0E;
}


/* --------- _ICONS.CSS --------- */
/*
 * MindTouch Deki - enterprise collaboration and integration platform
 *  derived from MediaWiki (www.mediawiki.org)
 * Copyright (C) 2006-2009 MindTouch, Inc.
 * www.mindtouch.com  oss@mindtouch.com
 *
 * For community documentation and downloads visit www.opengarden.org;
 * please review the licensing section.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * http://www.gnu.org/copyleft/gpl.html
 */

/***
 * MT: royk
 * these are the icons for different files
 */
 	.ext-iconify {
	 	background-repeat: no-repeat;
	 	background-position: 1px center;
	 	line-height: 18px;
	 	padding: 2px 0 2px 18px;
 	}
 	
	a.ext-txt,
	a.ext-sh 			{ background-image: url(/skins/common/icons/file-text.png); }
	a.ext-pptx,
	a.ext-ppt			{ background-image: url(/skins/common/icons/file-ppt.png); }
	a.ext-jpg,
	a.ext-jpeg,
	a.ext-jpe,
	a.ext-gif,
	a.ext-png			{ background-image: url(/skins/common/icons/file-image.png); }
	a.ext-swf,
	a.ext-fla			{ background-image: url(/skins/common/icons/file-flash.png); }
	a.ext-xlsx,
	a.ext-xls			{ background-image: url(/skins/common/icons/file-excel.png); }
	a.ext-zip			{ background-image: url(/skins/common/icons/file-zip.png); }
	a.ext-pdf			{ background-image: url(/skins/common/icons/file-acrobat.png); }
	a.ext-unknown		{ background-image: url(/skins/common/icons/file-unknown.png); }
	a.ext-tar,
	a.ext-rar,
	a.ext-gzip			{ background-image: url(/skins/common/icons/file-archived.png); }
	a.ext-docx,
	a.ext-doc			{ background-image: url(/skins/common/icons/file-doc.png); }
	a.ext-wmv,
	a.ext-avi,
	a.ext-mpg,
	a.ext-mov,
	a.ext-mp4,
	a.ext-mpeg			{ background-image: url(/skins/common/icons/file-movie.png); }
	a.ext-html,
	a.ext-htm,
	a.ext-shtml			{ background-image: url(/skins/common/icons/file-html.png); }
	a.ext-mp3			{ background-image: url(/skins/common/icons/file-music.png); }
	
	.file-aif 	{background: url('/skins/common/images/icons/aif-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-aifc 	{background: url('/skins/common/images/icons/aifc-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-aiff 	{background: url('/skins/common/images/icons/aiff-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-au 	{background: url('/skins/common/images/icons/au-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-bmp 	{background: url('/skins/common/images/icons/bmp-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-def	{background: url('/skins/common/images/icons/default-16.gif') no-repeat center left; width:16px; height: 16px; } 
	.file-doc 	{background: url('/skins/common/images/icons/doc-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-dot 	{background: url('/skins/common/images/icons/dot-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-gif 	{background: url('/skins/common/images/icons/gif-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-jpeg 	{background: url('/skins/common/images/icons/jpeg-16.gif') no-repeat center left; width:16px; height: 16px; } 
	.file-jpg 	{background: url('/skins/common/images/icons/jpg-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-m1v 	{background: url('/skins/common/images/icons/m1v-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-mov 	{background: url('/skins/common/images/icons/mov-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-mp2 	{background: url('/skins/common/images/icons/mp2-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-mp3 	{background: url('/skins/common/images/icons/mp3-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-mpa 	{background: url('/skins/common/images/icons/mpa-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-mpeg 	{background: url('/skins/common/images/icons/mpeg-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-mpg 	{background: url('/skins/common/images/icons/mpg-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-pdf 	{background: url('/skins/common/images/icons/pdf-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-png	{background: url('/skins/common/images/icons/png-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-ppt	{background: url('/skins/common/images/icons/ppt-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-pub	{background: url('/skins/common/images/icons/pub-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-qt	{background: url('/skins/common/images/icons/qt-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-snd	{background: url('/skins/common/images/icons/smd-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-tif 	{background: url('/skins/common/images/icons/tif-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-tiff 	{background: url('/skins/common/images/icons/tiff-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-txt, 
	.file-sh 	{background: url('/skins/common/images/icons/txt-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-vsd 	{background: url('/skins/common/images/icons/vsd-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-wav 	{background: url('/skins/common/images/icons/wav-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-wmv 	{background: url('/skins/common/images/icons/wmv-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-xls 	{background: url('/skins/common/images/icons/xls-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-xlt 	{background: url('/skins/common/images/icons/xlt-16.gif') no-repeat center left; width:16px; height: 16px; }
	.file-zip 	{background: url('/skins/common/images/icons/zip-16.gif') no-repeat center left; width:16px; height: 16px; } 

/* --------- BUTTON-SKIN.CSS --------- */
/*
Copyright (c) 2008, Yahoo! Inc. All rights reserved.
Code licensed under the BSD License:
http://developer.yahoo.net/yui/license.txt
version: 2.6.0
*/
.yui-skin-sam .yui-button  {

    border-width: 1px 0;
    border-style: solid;
    border-color: #808080;
    background: url(../../../../assets/skins/sam/sprite.png) repeat-x 0 0;
    margin: auto .25em;
    
}

.yui-skin-sam .yui-button .first-child {

    border-width: 0 1px;
    border-style: solid;
    border-color: #808080;
    margin: 0 -1px;
    *position: relative;    /* Necessary to get negative margins working in IE */
    *left: -1px;
    
	/* 
		Don't apply rounded corners for IE 6 (Quirks and Standards Mode) and IE 7 Quirks Mode 
		since it causes more problems than its worth.
	*/
	_margin: 0;
	_position: static;    

}

.yui-skin-sam .yui-button button,
.yui-skin-sam .yui-button a {

    padding: 0 10px;
    font-size: 93%;  /* 12px */
    line-height: 2;  /* ~24px */
    *line-height: 1.7; /* For IE */
    min-height: 2em; /* For Gecko */
    *min-height: auto; /* For IE */
    color: #000; 

}

.yui-skin-sam .yui-button a {

    /*
        Necessary to get Buttons of type "link" to be the correct 
        height in IE.
    */
    *line-height: 1.875;
	*padding-bottom: 1px;

}

.yui-skin-sam .yui-split-button button,
.yui-skin-sam .yui-menu-button button {

    padding-right: 20px;
    background-position: right center;
    background-repeat: no-repeat;
    
}

.yui-skin-sam .yui-menu-button button {

    background-image: url(menu-button-arrow.png);

}

.yui-skin-sam .yui-split-button button {

    background-image: url(split-button-arrow.png);

}


/* Focus state */


.yui-skin-sam .yui-button-focus {

    border-color: #7D98B8;
    background-position: 0 -1300px;

}

.yui-skin-sam .yui-button-focus .first-child {

    border-color: #7D98B8;

}

.yui-skin-sam .yui-button-focus button, 
.yui-skin-sam .yui-button-focus a {

    color: #000;

}

.yui-skin-sam .yui-split-button-focus button {

    background-image: url(split-button-arrow-focus.png);

}


/* Hover state */

.yui-skin-sam .yui-button-hover {

    border-color: #7D98B8;
    background-position: 0 -1300px;

}

.yui-skin-sam .yui-button-hover .first-child {

    border-color: #7D98B8;

}

.yui-skin-sam .yui-button-hover button, 
.yui-skin-sam .yui-button-hover a {

    color: #000;

}

.yui-skin-sam .yui-split-button-hover button {

    background-image: url(split-button-arrow-hover.png);

}


/* Active state */

.yui-skin-sam .yui-button-active {
    
    border-color: #7D98B8;
    background-position: 0 -1700px;
    
}

.yui-skin-sam .yui-button-active .first-child {

    border-color: #7D98B8;

}

.yui-skin-sam .yui-button-active button, 
.yui-skin-sam .yui-button-active a {

    color: #000;

}

.yui-skin-sam .yui-split-button-activeoption {

    border-color: #808080;
    background-position: 0 0;

}

.yui-skin-sam .yui-split-button-activeoption .first-child {

    border-color: #808080;

}

.yui-skin-sam .yui-split-button-activeoption button {

    background-image: url(split-button-arrow-active.png);

}


/* Checked state */

.yui-skin-sam .yui-radio-button-checked,
.yui-skin-sam .yui-checkbox-button-checked {
    
    border-color: #304369;
    background-position: 0 -1400px;
    
}

.yui-skin-sam .yui-radio-button-checked .first-child,
.yui-skin-sam .yui-checkbox-button-checked .first-child {

    border-color: #304369;

}

.yui-skin-sam .yui-radio-button-checked button,
.yui-skin-sam .yui-checkbox-button-checked button { 

    color: #fff;

}


/* Disabled state */

.yui-skin-sam .yui-button-disabled {
    
    border-color: #ccc;
    background-position: 0 -1500px;
    
}

.yui-skin-sam .yui-button-disabled .first-child {

    border-color: #ccc;

}

.yui-skin-sam .yui-button-disabled button, 
.yui-skin-sam .yui-button-disabled a {

    color: #A6A6A6;
    cursor: default;

}

.yui-skin-sam .yui-menu-button-disabled button {

    background-image: url(menu-button-arrow-disabled.png);
    
}

.yui-skin-sam .yui-split-button-disabled button {

    background-image: url(split-button-arrow-disabled.png);
    
}

/***  
 * Custom override styles
 */
.yui-skin-sam .yui-button, 
.yui-skin-sam .yui-button .first-child { border: none; } 
.yui-skin-sam .button-group button {
	text-decoration: none;
	padding: 3px 6px;
	font-size: 12px;
	font-family: DroidSans, Arial, sans-serif;
	color: #fff;
	border: 1px solid #444;
	background: -moz-linear-gradient(center top , #aaa, #777) repeat scroll 0 0 transparent;
	background: -webkit-gradient(linear, left top, left bottom,	color-stop(0.00, #aaa), color-stop(1.00, #777));
	background-color: #aaa;
	margin-left: 6px;
}
.yui-skin-sam .yui-dialog .ft span.yui-button-disabled button {	
	background: -moz-linear-gradient(center top , #fff, #fff) repeat scroll 0 0 transparent;
	background: -webkit-gradient(linear, left top, left bottom,	color-stop(0.00, #fff), color-stop(1.00, #fff));
	background-color: #fff;
	border: 1px solid #ccc;
	color: #888;
}
	
.yui-skin-sam .button-group span.default button {
	background: -moz-linear-gradient(center top , #777, #222) repeat scroll 0 0 transparent;
	background: -webkit-gradient(linear, left top, left bottom,	color-stop(0.00, #777), color-stop(1.00, #222));
	background-color: #222;
}

/* --------- CONTAINER.CSS --------- */
/*
Copyright (c) 2008, Yahoo! Inc. All rights reserved.
Code licensed under the BSD License:
http://developer.yahoo.net/yui/license.txt
version: 2.6.0
*/
.yui-overlay,.yui-panel-container{visibility:hidden;position:absolute;z-index:2;}.yui-panel-container form{margin:0;}.mask{z-index:1;display:none;position:absolute;top:0;left:0;right:0;bottom:0;}.mask.block-scrollbars{overflow:auto;}.masked select,.drag select,.hide-select select{_visibility:hidden;}.yui-panel-container select{_visibility:inherit;}.hide-scrollbars,.hide-scrollbars *{overflow:hidden;}.hide-scrollbars select{display:none;}.show-scrollbars{overflow:auto;}.yui-panel-container.show-scrollbars,.yui-tt.show-scrollbars{overflow:visible;}.yui-panel-container.show-scrollbars .underlay,.yui-tt.show-scrollbars .yui-tt-shadow{overflow:auto;}.yui-panel-container.shadow .underlay.yui-force-redraw{padding-bottom:1px;}.yui-effect-fade .underlay{display:none;}.yui-tt-shadow{position:absolute;}.yui-override-padding{padding:0 !important;}.yui-panel-container .container-close{overflow:hidden;text-indent:-10000em;text-decoration:none;}.yui-skin-sam .mask{background-color:#000;opacity:.25;-ms-filter: "progid:DXImageTransform.Microsoft.Alpha(opacity=25)";*filter:alpha(opacity=25);}.yui-skin-sam .yui-panel-container{padding:0 1px;*padding:2px;}.yui-skin-sam .yui-panel{position:relative;left:0;top:0;border-style:solid;border-width:1px 0;border-color:#808080;z-index:1;*border-width:1px;*zoom:1;_zoom:normal;}.yui-skin-sam .yui-panel .hd,.yui-skin-sam .yui-panel .bd,.yui-skin-sam .yui-panel .ft{border-style:solid;border-width:0 1px;border-color:#808080;margin:0 -1px;*margin:0;*border:0;}.yui-skin-sam .yui-panel .hd{border-bottom:solid 1px #ccc;}.yui-skin-sam .yui-panel .bd,.yui-skin-sam .yui-panel .ft{background-color:#F2F2F2;}.yui-skin-sam .yui-panel .hd{padding:0 10px;font-size:93%;line-height:2;*line-height:1.9;font-weight:bold;color:#000;background:url(/skins/common/yui/assets/skins/sam/sprite.png) repeat-x 0 -200px;}.yui-skin-sam .yui-panel .bd{padding:10px;}.yui-skin-sam .yui-panel .ft{border-top:solid 1px #808080;padding:5px 10px;font-size:77%;}.yui-skin-sam .yui-panel-container.focused .yui-panel .hd{}.yui-skin-sam .container-close{position:absolute;top:5px;right:6px;width:25px;height:15px;background:url(/skins/common/yui/assets/skins/sam/sprite.png) no-repeat 0 -300px;cursor:pointer;}.yui-skin-sam .yui-panel-container .underlay{right:-1px;left:-1px;}.yui-skin-sam .yui-panel-container.matte{padding:9px 10px;background-color:#fff;}.yui-skin-sam .yui-panel-container.shadow{_padding:2px 4px 0 2px;}.yui-skin-sam .yui-panel-container.shadow .underlay{position:absolute;top:2px;left:-3px;right:-3px;bottom:-3px;*top:4px;*left:-1px;*right:-1px;*bottom:-1px;_top:0;_left:0;_right:0;_bottom:0;_margin-top:3px;_margin-left:-1px;background-color:#000;opacity:.12;-ms-filter: "progid:DXImageTransform.Microsoft.Alpha(opacity=12)";*filter:alpha(opacity=12);}.yui-skin-sam .yui-dialog .ft{border-top:none;padding:0 10px 10px 10px;font-size:100%;}.yui-skin-sam .yui-dialog .ft .button-group{display:block;text-align:right;}.yui-skin-sam .yui-dialog .ft button.default{font-weight:bold;}.yui-skin-sam .yui-dialog .ft span.default{border-color:#304369;background-position:0 -1400px;}.yui-skin-sam .yui-dialog .ft span.default .first-child{border-color:#304369;}.yui-skin-sam .yui-dialog .ft span.default button{color:#fff;}.yui-skin-sam .yui-dialog .ft span.yui-button-disabled{background-position:0pt -1500px;border-color:#ccc;}.yui-skin-sam .yui-dialog .ft span.yui-button-disabled .first-child{border-color:#ccc;}.yui-skin-sam .yui-dialog .ft span.yui-button-disabled button{color:#a6a6a6;}.yui-skin-sam .yui-simple-dialog .bd .yui-icon{background:url(/skins/common/yui/assets/skins/sam/sprite.png) no-repeat 0 0;width:16px;height:16px;margin-right:10px;float:left;}.yui-skin-sam .yui-simple-dialog .bd span.blckicon{background-position:0 -1100px;}.yui-skin-sam .yui-simple-dialog .bd span.alrticon{background-position:0 -1050px;}.yui-skin-sam .yui-simple-dialog .bd span.hlpicon{background-position:0 -1150px;}.yui-skin-sam .yui-simple-dialog .bd span.infoicon{background-position:0 -1200px;}.yui-skin-sam .yui-simple-dialog .bd span.warnicon{background-position:0 -1900px;}.yui-skin-sam .yui-simple-dialog .bd span.tipicon{background-position:0 -1250px;}.yui-skin-sam .yui-tt .bd{position:relative;top:0;left:0;z-index:1;color:#000;padding:2px 5px;border-color:#D4C237 #A6982B #A6982B #A6982B;border-width:1px;border-style:solid;background-color:#FFEE69;}.yui-skin-sam .yui-tt.show-scrollbars .bd{overflow:auto;}.yui-skin-sam .yui-tt-shadow{top:2px;right:-3px;left:-3px;bottom:-3px;background-color:#000;}.yui-skin-sam .yui-tt-shadow-visible{opacity:.12;-ms-filter: "progid:DXImageTransform.Microsoft.Alpha(opacity=12)";*filter:alpha(opacity=12);}

.yui-skin-sam .yui-panel .hd {
	background-image: none;
	background: -moz-linear-gradient(center top , #F9F9F9, #E3E3E3) repeat scroll 0 0 transparent;
	background: -webkit-gradient(linear, left top, left bottom, color-stop(0.00, #F9F9F9), color-stop(1.00, #E3E3E3));
	background-color: #E3E3E3;
	font-family: DroidSans, "Lucida Sans", Arial, sans-serif;
	font-size: 12px;
}

/* --------- DIALOG.CSS --------- */
@CHARSET "UTF-8";

div.deki-dialog-status
{
    border-top: 2px solid #999;
    padding: 4px 6px 0px 6px;
    margin-top: 10px;
    font-size: 11px;
}

div.deki-dialog-loading
{
	position: absolute;
	left: 1em;
	top: 1em;
	font: 12px Verdana;
}

.yui-skin-sam .yui-panel .bd {
    padding: 0;
    position: relative;
}


/* --------- THICKBOX.CSS --------- */

#TB_window *{padding: 0; margin: 0;}

#TB_window {
	color: #333333;
	font-size: 12px;
	min-width: 250px;
}

#TB_secondLine {
	color:#666666;
	padding: 4px 8px 0px 8px;
}

.TB_navigate {
	float: right;
}
#TB_window a:link {color: #666666;}
#TB_window a:visited {color: #666666;}
#TB_window a:hover {color: #000;}
#TB_window a:active {color: #666666;}
#TB_window a:focus{color: #666666;}

#TB_closeWindowButton {
	font-weight: bold;
	font-size: 11px;
}
#TB_next {
	margin-left: 2px;
}
#TB_prev {
	margin-right: 2px;
}

#TB_overlay {
	position: fixed;
	z-index:100;
	top: 0px;
	left: 0px;
	height:100%;
	width:100%;
}

.TB_overlayMacFFBGHack {background: url(jquery/thickbox/macFFBgHack.png) repeat;}
.TB_overlayBG {
	background-color:#000;
	filter:alpha(opacity=75);
	-moz-opacity: 0.75;
	opacity: 0.75;
}
* html #TB_overlay { /* ie6 hack */
     position: absolute;
     height: expression(document.body.scrollHeight > document.body.offsetHeight ? document.body.scrollHeight : document.body.offsetHeight + 'px');
}

#TB_window {
	position: fixed;
	background: #ffffff;
	z-index: 102;
	color:#000000;
	display:none;
	border: 4px solid #525252;
	text-align:left;
	top:50%;
	left:50%;
}

* html #TB_window { /* ie6 hack */
position: absolute;
margin-top: expression(0 - parseInt(this.offsetHeight / 2) + (TBWindowMargin = document.documentElement && document.documentElement.scrollTop || document.body.scrollTop) + 'px');
}

#TB_window img#TB_Image {
	display:block;
	margin: 10px auto 0 auto;
	text-align: center;
	border-right: 1px solid #ccc;
	border-bottom: 1px solid #ccc;
	border-top: 1px solid #666;
	border-left: 1px solid #666;
}

#TB_caption{
	height:25px;
	padding:7px 30px 10px 14px;
	float:left;
}

#TB_closeWindow{
	height:25px;
	padding:7px 14px 10px 0;
	float:right;
}

#TB_closeAjaxWindow{
	padding:7px 10px 5px 0;
	margin-bottom:1px;
	text-align:right;
	float:right;
}
#TB_closeAjaxWindow span {
	display: block;
	height: 15px;
	width: 25px;
	background: url(/skins/common/icons/close.png) no-repeat;
}
#TB_ajaxWindowTitle{
	float:left;
	padding:7px 0 5px 10px;
	margin-bottom:1px;
	font-family: DroidSansBold, Arial, Sans-Serif; 
	font-weight: bold;
	font-size: 12px;
}
#TB_title{
	background: -moz-linear-gradient(center top , #F9F9F9, #E3E3E3) repeat scroll 0 0 transparent;
	background: -webkit-gradient(linear, left top, left bottom, color-stop(0.00, #F9F9F9), color-stop(1.00, #E3E3E3));
	background-color: #E3E3E3;
	font-size: 12px;
	height:27px;
}

#TB_ajaxContent{
	clear:both;
	padding:2px 15px 15px 15px;
	overflow:auto;
	text-align:left;
	line-height:1.4em;
}

#TB_ajaxContent.TB_modal{
	padding:15px;
}

#TB_ajaxContent p{
	padding:5px 0px 5px 0px;
}

#TB_load{
	position: fixed;
	display:none;
	height:32px;
	width:32px;
	z-index:103;
	top: 50%;
	left: 50%;
	margin: -16px 0 0 -16px; /* -height/2 0 0 -width/2 */
}

* html #TB_load { /* ie6 hack */
position: absolute;
margin-top: expression(0 - parseInt(this.offsetHeight / 2) + (TBWindowMargin = document.documentElement && document.documentElement.scrollTop || document.body.scrollTop) + 'px');
}

#TB_HideSelect{
	z-index:99;
	position:fixed;
	top: 0;
	left: 0;
	background-color:#fff;
	border:none;
	filter:alpha(opacity=0);
	-moz-opacity: 0;
	opacity: 0;
	height:100%;
	width:100%;
}

* html #TB_HideSelect { /* ie6 hack */
     position: absolute;
     height: expression(document.body.scrollHeight > document.body.offsetHeight ? document.body.scrollHeight : document.body.offsetHeight + 'px');
}

#TB_iframeContent{
	clear:both;
	border:none;
	margin-bottom:-1px;
	margin-top:1px;
	_margin-bottom:1px;
}


/* --------- JQUERY.AUTOCOMPLETE.CSS --------- */
.ac_results {
	padding: 0px;
	border: 1px solid black;
	background-color: white;
	overflow: hidden;
	z-index: 99999;
}

.ac_results ul {
	width: 100%;
	list-style-position: outside;
	list-style: none;
	padding: 0;
	margin: 0;
}

.ac_results li {
	margin: 0px;
	padding: 2px 5px;
	cursor: default;
	display: block;
	/* 
	if width will be 100% horizontal scrollbar will apear 
	when scroll mode will be used
	*/
	/*width: 100%;*/
	font: menu;
	font-size: 12px;
	/* 
	it is very important, if line-height not setted or setted 
	in relative units scroll will be broken in firefox
	*/
	line-height: 16px;
	overflow: hidden;
}

.ac_loading {
	background: white url('indicator.gif') right center no-repeat;
}

.ac_odd {
	background-color: #eee;
}

.ac_over {
	background-color: #0A246A;
	color: white;
}

.ac_results .count {
  float: right;
  font-size: 10px;
}




/* --------- MESSAGING.CSS --------- */
.ui-msg {
	padding: 8px;
	font-size: 11px;
	font-family: "Lucida Grande", Verdana, Sans-Serif;
	min-height: 32px;
}
.ui-errormsg {
	border: 4px solid #eee488;
	background-color: #fff799;
}
.ui-successmsg {
	border: 4px solid #c4df9b;
	background-color: #e2f6b2;
}
.ui-msg:hover {
	border: 4px solid #000;
}
.ui-msgtextarea {
	width: 100%;
	height: 200px;
	border: 1px solid #000;
	font-size: 12px;
}
.ui-msg-wrap {
	width: 100%;
	position: fixed;
	top: 0px;
	left: 0px;
	z-index: 999;
}
.ui-msg-opt {
	float: right;
	width: 260px;
}
.ui-msg-opt ul {
	padding: 0;
	margin: 0;
	list-style-type: none;
}
.ui-msg-opt ul li {
	float: right;
	padding: 0;
	margin: 0;
	padding-left: 4px;
	margin-left: 4px;
}
.ui-msg-autoclose {
	clear: both;
	text-align: right;
	padding-top: 6px;
	font-size: 10px;
	font-weight: normal;
}
.ui-msg-header {
	font-weight: bold;
	font-size: 14px;
	color: #ed1c24;
}
.ui-successmsg .ui-msg-header {
	color: #00a650;
}
.ui-msg-opt {
	font-size: 10px;
	font-weight: bold;
}
.ui-msg-opt a {
	display: block;
	font-weight: normal;
	color: #000;
}
.ui-msg-opt a:hover {
	color: #ed1c24;
}
.ui-successmsg .ui-msg-opt a:hover {
	color: #00a650;
}
.ui-msg-opt a.dismiss {
	padding-right: 12px;
	background: url(/skins/common/icons/close.png) no-repeat center right;
}
#MTMessageTimer {
	font-weight: bold;
}

/* --------- CONTROLS.CSS --------- */
/**************************************************************************
 * STYLES FOR THE GUIDE COLLECTION PAGE
 */
.mindtouch-content ul li {
	list-style-type: none;
	padding: 0;
	margin: 0;
}

/* Tab elements in the CKB collection "Guide" page */
.mt-control-nav {
	font-family: "Lucida Sans", Sans-Serif;
	background: url(/skins/common/ckb/images/tab-bg-bottom.png) repeat-x bottom;
	font-size: 12px;	
}
/* IE6 specific */
* html body .mt-control-nav { 
	height: 29px;	
}

* html body .mt-control-pagelist div.subtitle {
	clear: both;
}

* html body .mt-control-list {
	clear: both;
}

/* IE6 does not set background properly, so disable alt styling */
* html body .mt-control-pagelist .mt-control-list-alt {
	border-top: 1px solid #ccc;
	background: #fff;  
}

.mt-control-nav ul {
	overflow: hidden;
	padding: 0;
	margin: 0;
}
.mt-control-nav ul li {
	margin-left: 8px;
	border: 1px solid #adaaad;
	float: left; 
	height: 29px;
}
.mt-control-nav ul li.active {
	background: #fff url(/skins/common/ckb/images/tab-bg.png) repeat-x top;
	border-bottom: 1px solid #fff;
}
.mt-control-nav ul li a,
.mt-control-nav ul li a:visited {
	font-weight: bold;
	display: block;
	padding: 6px 12px;
	text-decoration: none;
	color: #000; 
}
.mt-control-nav ul li a:hover {
	color: #004a80;
	text-decoration: underline; 
}
.mt-control-nav ul li.active a:hover {
	color: #000; 
	text-decoration: none; 
}
.mt-control-nav ul li a span.count {
	font-size: 11px;
	color: #959595; 
	font-weight: normal;	
}
/* subnav: only really used for tutorials */
.mt-control-subnav {
	font-size: 11px;
	overflow: auto;
	padding: 8px 8px 0 14px;
} 
.mt-control-subnav ul,
.mt-control-subnav p {
	margin: 0;
	padding: 0;
	float: left; 
	overflow: hidden;
}
.mt-control-subnav ul li {
	float: left; 
	margin-left: 14px;
}
.mt-control-subnav a,
.mt-control-subnav a:visited {
	text-decoration: none;
	color: #000;
	border-bottom: 1px solid #000;
	display: block;
}
.mt-control-subnav a:hover {
	color: #0072bc; 
	border-bottom: 1px solid #0072bc;	
}

/* Showing a list of pages */
.mt-control-pagelist {
	font-size: 12px;
}
.mt-control-pagelist div.subtitle,
div.mt-control-page-subtitle {
	font-size: 16px;
	margin: 0;
	padding: 0; 
	font-weight: bold;
	border-top: 2px solid #000;
	padding: 6px 0 0 14px;
	margin: 6px 0 0 0;
}
.mt-control-pagelist .mt-control-list {
	overflow: auto;
	padding: 14px 14px 6px 14px; /* last node adds padding-bottom */
}
.mt-control-pagelist .mt-control-list-alt {
	background-color: #eee;
}
.mt-control-pagelist .mt-control-block-category {
	float: left;
	width: 180px;
	text-transform: lowercase;
}
.mt-control-pagelist .mt-control-block-content {
	padding-left: 200px;	
}
/* show a category - used by tutorials for the left visual grouping */
.mt-control-block-category {
	font-size: 11px;
}
.mt-control-block-category a,
.mt-control-block-category a:visited {
	color: #000;	
}
.mt-control-block-category a:hover {
	color: #0072bc;
}
.mt-control-block-category ol {
	margin: 0;
	padding: 0;	
}
.mt-control-block-category ol li {
	list-style-type: none; 
	margin: 0 4px 0 0;
	padding: 0 10px 0 0;
	float: left;
	clear: left;
	background: url(/skins/common/icons/187.png) no-repeat center right;
}
/* individual page styling on a list of pages */
.mt-control-block-content dl {
	margin: 0;
	padding: 0;
}
.mt-control-block-content dt, 
.mt-control-block-content dd {
	margin: 0;
	padding: 0;
}
.mt-control-block-content dt {
	font-size: 14px;
}
.mt-control-block-content dd {
	padding-bottom: 8px;
}
.mt-control-block-content dt .rating {
	font-size: 11px;
	color: #959595;
	font-style: italic;
}
/* "Guide Contents"-specific styles */
dl.mt-control-seealso,
.mt-control-guide-description, 
.mt-control-page-listcontent {
	padding: 6px 14px;
}
.page-seealso {
	float: right;
	width: 380px;
}
.mt-control-page-list {
	padding-right: 400px;
}
/* styling in the situation of no contents within a given section */
.mt-control-nocontent {
	background: url(/skins/common/icons/icon-32-document.gif) no-repeat 6px 6px; 
	padding: 8px 8px 8px 41px;
	width: 420px;
	margin: 8px;
}
.mt-control-nocontent p {
	margin: 0 0 8px 0;
	padding: 0;
}
.mt-control-nocontent p.nocontent-title {
	font-weight: bold;
	font-size: 16px;
}

/**
 * Experience for unlicensed
 */
.mindtouch-content .deki-commercial-text {
	background: url(/skins/common/ckb/images/2010-idf-guide.png) no-repeat top center;
}


/* --------- REPORTS.CSS --------- */
.mt-report form.ui-no-results, 
.mt-report table.ui-no-results {
	display: none;
}
.mt-report h3.reports {
	color: #000;
	margin-bottom: 0;
	padding-bottom: 8px;
}
.mt-report h3.reports span {
	background-color: #cfc;
	padding: 2px;
}
.mt-report h3 div.reset-search {
	padding-left: 8px;
	display: inline;
}
.mt-report h3 div.reset-search a {
	font-size: 11px;
	color: #9d0a0e;
}
.mt-report .no-results {
	margin-top: 8px;	
}
/***
 * No search results
 */
.no-results {
	padding: 8px;
	border: 1px solid #aaa;
	background: #e7e7e7; 
}
.no-results-text {
	background: url(/skins/common/icons/silk/information.png) no-repeat center left; 
	padding-left: 21px;
	font-size: 14px;
}
/**
 * Search control
 */
.mt-search-input {
	padding: 0 4px;
}
.mt-search-input label {
	padding-right: 10px;
	font-weight: bold;
}
.mt-search-input input.query {
	width: 300px;
} 
.mt-search-input input.search {
	margin: 0 8px;
}

/**
 * Chart section
 */
.mt-report-overview .stats {
	float: right;
	width: 290px;
	margin: 20px 0 0 0;
}
.mt-report-overview .ui-state-disabled {
	background: url(/skins/common/ckb/images/charting-disabled.png) no-repeat left top;	
}
.mt-report-overview .ui-state-disabled div {
	font-size: 11px;
	width: 380px;
	text-align: center;
	padding-top: 255px;
	padding-left: 20px;
}
.mt-report-overview dt,
.mt-report-overview dd {
	padding: 3px;
}
.mt-report-overview dt {
	border-top: 1px solid #777;
	font-size: 110%;
	padding: 0;
}
.mt-report-overview dt span.title {
	padding-top: 3px;
}
.mt-report-overview dt.information {
	padding: 0;
	margin: 0;
	padding-top: 8px;
}
.mt-report-overview dt.information div {
	background-color: #e1e1e1; 
	padding: 8px;
	font-size: 11px;
}
.mt-report-overview dd {
	padding-bottom: 8px;
}
.mt-report-overview dd span {
	font-size: 26px;
	line-height: 26px;
}
.mt-report-overview dd span.help, 
.mt-report-overview dd span.help a {
	display: block;
	height: 16px;
	width: 16px;
	clear: right;
}
.mt-report-overview dd span.help {
	margin-top: 8px;
	float: right;
	font-size: 11px;
	background: url(/skins/common/icons/silk/help.png) no-repeat center center;
	display: none; /* disable them all */
}
#topic .mt-report-overview dd span.help a.external {
	background: none;
	padding: 0; 
	margin: 0;
}
.mt-report-overview dd span.help span {
	display: none;
}
.mt-report-overview span.site {
	float: right;
	background-color: #777; 
	color: #fff;
	padding: 6px;
	display: block;
	font-size: 12px;
	line-height: 12px;
	margin: 0px;
}
.mt-report-overview .chart {
	height: 325px;
}

/**
 * Results table
 */
table.mt-report-results {
	width: 100%;
	background-color: #fff;
}
table.mt-report-results tr.row-1 {
	background-color: #efefef;
}
/**
 * Table data types
 */
.mt-report-results td.data-type-numeric {
	text-align: right;	
}
.mt-report-results td.data-type-datetime {
	width: 175px;
	text-align: right;
}

table.mt-report-results span.views,
table.mt-report-results span.edits,
table.mt-report-results span.comments { 
	display: block;	
	min-width: 16px;
	height: 16px;
}
table.mt-report-results span.views span,
table.mt-report-results span.edits span,
table.mt-report-results span.comments span {
	display: none;
}
table.mt-report-results span.views {
	background: url(/skins/common/icons/silk/page_white_find.png) no-repeat center center;
}
table.mt-report-results span.edits {
	background: url(/skins/common/icons/silk/page_white_edit.png) no-repeat center center;
}
table.mt-report-results span.comments {
	background: url(/skins/common/icons/silk/comments.png) no-repeat center center;
}
table.mt-report-results div.details {
	font-weight: bold;	
}
table.mt-report-results span.in {
	font-size: 11px;
	font-weight: normal;
}
table.mt-report-results span.in a {
	color: #4F6B72;
}
table.mt-report-results div.tags {
	font-size: 11px;
}
table.mt-report-results div.tags li {
	padding-right: 8px;
}
table.mt-report-results div.tags a {
	color: #393; 
	text-decoration: none; 
}
table.mt-report-results div.tags a:hover {
	text-decoration: underline;
	color: #000;
}
/**
 * Page detail cell
 */
td.page-detail {}
td.page-detail div.details {
	width: 325px;
	overflow: hidden;
}
td.page-detail div.details a {
	white-space: nowrap;
	overflow: hidden;
	text-overflow: ellipsis;
}
td.page-detail .tags span {
	padding-right: 5px;
	float: left;
}
td.page-detail .tags ul {
	margin: 0;
	padding: 0;
}
td.page-detail .tags li {
	padding-right: 3px;
	list-style: none;
	float: left;
}

/**
 * Rating cell
 */
td.rating span {
	font-weight: bold;
}
span.trending {
	padding-right: 10px;
	background: transparent url() no-repeat center right;
}
span.trending-up {
	background-image: url(/skins/common/ckb/images/icon-trend-up.png);
}
span.trending-down {
	background-image: url(/skins/common/ckb/images/icon-trend-down.png);
}

/**
 * Table summary
 */
tr.summary {
	display: none;	
}

/**
 * Sort header
 */
th.sortable a {
	background: transparent url(/skins/common/icons/sort-none.png) no-repeat center right;
	padding-right: 12px;
}
th.sortable a.sort-asc {
	background-image: url(/skins/common/icons/sort-asc.png);
}
th.sortable a.sort-desc {
	background-image: url(/skins/common/icons/sort-desc.png);
}

/**
 * Paging
 */
.mt-search-paging {
	padding: 10px 0;	
	clear: both;
}
.mt-search-paging .summary {
	float: left;
}
.mt-search-paging .paging {
	text-align: right;
}
.mt-search-paging .paging .ui-state-disabled {
	color: #ccc;
}
.mt-search-paging span.jump {
	padding: 0 5px 0 10px;
}
.mt-search-paging input.jump {
	margin-right: 10px;
	text-align: center;
}


/**
 * Experience for Core
 */
.deki-commercial {
	width: 779px;
	height: 606px;
	color: #000;
}
.mt-report-aging .deki-commercial-text {
	background: url(/skins/common/ckb/images/2010-analytics-quality.png) no-repeat top center;
}
.mt-report-rating .deki-commercial-text { 
	background: url(/skins/common/ckb/images/2010-analytics-aging.png) no-repeat top center;
}
.mt-report-search .deki-commercial-text { 
	background: url(/skins/common/ckb/images/2010-analytics-quality.png) no-repeat top center;
}
div.deki-commercial-text {
	padding: 25px;
	min-height: 600px;
}
div.deki-commercial-message {
	margin: 0 auto;
	width: 450px;
	color: #fff; 
	background-color: #000;
	opacity: 0.6;
	padding: 15px;
	font-size: 11px;
	line-height: 18px;
}
div.deki-commercial-message div,
div.deki-commercial-message p {
	padding: 0 0 8px 0;
	margin: 0;
}
div.deki-commercial-message a.new {
	color: #36c; 
	border-bottom: none;
	text-decoration: underline;
	color: #fff;
}
div.deki-commercial-message div.restart {
	font-style: italic;
	text-align: center;	
}
div.deki-commercial-message strong {
	font-size: 14px;
}
div.deki-commercial-message .learn {
	font-weight: bold;
	font-size: 16px;
	text-align: center;
}

/*** 
 * Search reports
 */
dl.mt-query {
	margin: 0 0 8px 0;
}
dl.mt-query dt {
	font-weight: bold;
}
dl.mt-query dd {
	margin-bottom: 8px;
}
dl.mt-query dd.description {
	margin-bottom: 0px;
	font-size: 11px;
	padding: 0;
	color: #aaa;
}
dl.mt-query ul {
	margin: 0;
	padding: 0;
}
/***
 * Search reporting styles
 */
.mt-report-search div.no-results {
	margin: 0 300px 8px 0;
}
.mt-report-search-terms {
	overflow: auto;
}
.mt-report-search-terms a, 
.mt-report-search-terms a:visited {
	color: #393;
}
.mt-report-search-terms a:hover {
	color: #000;
}
.mt-terms-description {
	font-size: 11px;
	padding: 8px;
	background-color:#E1E1E1;
	float: right;
	width: 275px;
}
.mt-report-search-date-filter form input.term {
	display: none;
}
.mt-report-search-date-filter div.reset-search {
	display: none; 
}
.mt-report-search-to {
	padding: 0 8px;
}
.mt-report-search-cloud {
	padding: 4px 8px;	
}
.mt-report-search-date-filter .mt-search-input {
	font-size: 11px;
	text-align: right;
}
.mt-report-search-date-filter .mt-search-input span.back {
	float: left;
	font-weight: bold;
	font-size: 12px; 
	color: #333;
	display: block;
	margin-top: 2px;
}
.mt-report-search-date-filter .mt-search-input span.back a {
	color: #000;
	background: url(/skins/common/icons/d-angle-l.png) no-repeat center left;
	padding: 2px 0 2px 14px;
}
.mt-report-search-custom {
	font-size: 11px;
	padding: 8px;
	background-color: #cfc;
	margin-right: 300px;
}
.mt-report-search-custom .mt-search-input {
	margin: 0;
	padding: 0;
}
.mt-report-search-custom input.term {
	width: 150px;
}
/**
 * Search terms
 */
.mt-search-terms-cloud { 
	padding-right: 300px;
}
.mt-search-terms-cloud ul.terms {
	list-style: none;
	margin: 0;
	padding: 0;
}
.mt-search-terms-cloud ul.terms li {
	display: inline-block;
	padding: 2px 5px 2px 0;
}
.mt-search-terms-cloud .rate-fire a {
	font-size: 24px;
	font-weight: bold;
}
.mt-search-terms-cloud .rate-high a {
	font-size: 18px;
	font-weight: bold;
}
.mt-search-terms-cloud .rate-med a {
	font-size: 14px;
}
.mt-search-terms-cloud .rate-low a {
	font-size: 11px;
}
.mt-search-terms-cloud li.active a {
	color: #000;
	text-decoration: none;
	font-weight: bold;
}


/* --------- PAGINATION.CSS --------- */

/***
 * Pagination controls
 */
.deki-pagination {
	overflow: auto;
	text-align: left;
	padding: 8px 0 8px 8px;
	font-size: 14px;
	margin: 0 0 4px 0;
}
.deki-pagination div.pagelist {
	font-weight: bold;
	float: left;
}
.deki-pagination div.info {
	float: right;
}
.deki-pagination div.prev,
.deki-pagination div.next {
	float: left; 
}
.deki-pagination div.prev {
	margin: 0; padding: 0;
	margin-right: 4px;
	padding-right: 4px;
}
.deki-pagination div.next {
	margin: 0; padding: 0;
	margin-left: 4px;
	padding-left: 4px;
}
.deki-listing-pagination div.prev {
	border-right: 1px solid #ddd;	
	margin-right: 8px;
	padding-right: 8px;
}
.deki-listing-pagination div.next {
	border-left: 1px solid #ddd;
	margin-left: 8px;
	padding-left: 8px;
}
.deki-pagination div.prev a.first {
	background: url(/skins/common/icons/d-angle-l.png) no-repeat center left;
	padding-left: 14px;
}
.deki-pagination div.prev a.prev {
	background: url(/skins/common/icons/angle-l.png) no-repeat center left;
	padding-left: 14px;
}
.deki-pagination div.next a.next {
	background: url(/skins/common/icons/angle-r.png) no-repeat center right;
	padding-right: 14px;
}
.deki-pagination div.next a.last {
	background: url(/skins/common/icons/d-angle-r.png) no-repeat center right;
	padding-right: 14px;
}
/* reset styles */
.deki-pagination div.prev,
.deki-pagination div.pagelist,
.deki-pagination .pagelist ol,
.deki-pagination div.next,
.deki-pagination li {
	display: inline;
}
.deki-pagination .pagelist ol {
	margin: 0;
	padding: 0;
}
.deki-pagination ol li {
	padding-right: 5px;
}

.deki-pagination span.next, 
.deki-pagination span.last,
.deki-pagination span.first, 
.deki-pagination span.prev {
	display: none;
}

.deki-pagination a.selected {
	text-decoration: none;
	color: #000;
	font-weight: bold;
}
.deki-pagination div.pagelist ol li,
.deki-pagination div.prev a,
.deki-pagination div.next a {
	float: left;
}
.deki-pagination div.prev a,
.deki-pagination div.next a {
	color: #555;
}
.deki-pagination a {
	display: block;
	padding: 0 2px;
}
.deki-pagination a.next,
.deki-pagination a.last {
	padding-right: 14px;
	margin-right: 8px;
}
.deki-pagination a.prev,
.deki-pagination a.first {
	padding-left: 14px;
	margin-left: 8px;
}
.deki-pagination div.prev span,
.deki-pagination div.next span {
	display: none; 
}
.deki-pagination-single {
	display: none;
}

/* --------- 2010.CSS --------- */
.mt2010-header {
	width: 735px;
	height: 140px; 
	margin: 0 auto; 
	background: url(/skins/common/2010/header.png) no-repeat;
	margin-bottom: 20px;
}
.mt2010-title {
	color: #fff;
	font-family: Arial, sans-serif;
	font-size: 12px;
	font-weight: normal;
	line-height: 35px;
	margin-bottom: 0px;
	margin-top: 0px;
	padding-left: 20px;
	padding-top: 10px;
	text-transform: uppercase;
}
.mt2010-tagline {
	color: #fff;
	font-family: Arial, sans-serif;
	font-size: 24px;
	font-weight: normal;
	height: 70px;
	line-height: 33px;
	margin-bottom: 6px;
	margin-top: 0px;
	overflow: hidden;
	padding-left: 20px;
	text-transform: uppercase;
	width: 510px;
}

.mt2010-sidebar {
	width: 250px; 
	float: right; 
	padding: 8px; 
	background-color: #efefef; 
	border: 1px solid #ccc; 
	margin: 0 0 0 20px;
}

.mt2010-sidebar strong.subtitle {
	font-size: 14px;
}
.mt2010-sidebar .launch {
	text-align: center;
}
#topic .mt2010-sidebar .launch a.external {
	background: url(/skins/common/2010/bg.png) repeat-x scroll center top #921B1D;
	color: #fff;
	display: block;
	font-size: 11px;
	font-weight: bold;
	margin-bottom: 8px;
	padding: 5px 0;
	text-align: center;
	text-decoration: none;
}
.mt2010-sidebar .more {
	text-align: center;
	font-size: 11px;
}
.mt2010-lede {
	font-size: 14px; 
	line-height: 21px; 
	font-style: italic; 
	font-family: Arial;
}
.mt2010-learn {
	margin-top: 16px;
	background: #fefeeb; 
	padding: 8px; 
	border: 1px solid #e1e1e1; 
	-webkit-border-radius: 8px; 
	-moz-border-radius: 8px;
}
.mt2010-learn h3 {
	border-top: none; 
	margin-top: 0px;
}
#topic .mt2010-learn a.external {
	background: none; 
}

/* updated styles */
#is-1 {
	width: 735px;
	height:140px;
	margin: 0 auto;
	background: url(header-cloud.png) no-repeat;
}
#is-2 {
	color: white;font-family:
	BitstreamVeraSansRoman, Arial, sans-serif;
	font-size: 12px;
	font-weight: normal;
	line-height: 35px;
	margin-bottom: 0px;
	margin-top: 0px;
	padding-left: 20px;
	padding-top: 10px;
	text-transform: uppercase;
}
#is-3 {
	color: white;
	font-family: BitstreamVeraSansRoman, Arial, sans-serif;
	font-size: 24px;
	font-weight: normal;
	height: 70px;
	line-height: 33px;
	margin-bottom: 6px;
	margin-top: 0px;
	overflow: hidden;
	padding-left: 20px;
	text-transform: uppercase;
	width: 510px;
}
#is-4 {
	width:250px;
	float:right;
	padding:5px 8px;
	background-color:#efefef;
	border:1px solid #ccc;
	margin: 20px 0 0 20px;
	-webkit-border-radius: 5px;
	-moz-border-radius: 5px;
}
#is-4 #is-5 {
	background:url(bkg-left-cta.png) repeat-x scroll center top #921B1D;
	color:#FFFFFF;
	display:block;
	font-size:11px;
	font-weight:bold;
	margin-bottom:8px;
	padding:5px 0;
	text-align:center;
	text-decoration:none;
}
#is-6 {
	margin: -4px 5px 0px 0px;
	display: inline-block;
	float: left;
}
#is-7 {
	background: #fefeeb;
	padding: 3px 8px 8px 8px;
	border: 1px solid #e1e1e1;
	-webkit-border-radius: 8px;
	-moz-border-radius: 8px;
	margin: 15px 0px;
}
#is-8 {
	border-top: none;
	margin-top: 0px;
}
#is-9 {
	background: #fefeeb;
	padding: 3px 8px 8px 10px;
	border: 1px solid #e1e1e1;
	-webkit-border-radius: 8px;
	-moz-border-radius: 8px;
}
#is-10 {
	color: rgb(0, 0, 0);
	line-height: 16px;
	font-size: 16px;
	font-weight: bold; 
}
#is-11 {
	background: #fefeeb;
	padding: 3px 8px 8px 10px;
	border: 1px solid #e1e1e1;
	-webkit-border-radius: 8px;
	-moz-border-radius: 8px;
	margin-top: 8px
}
#is-12 {
	border-top: none;
	margin-top: 0px;
}
#is-13 {
	border-top: none;
	margin-top: 0px;
}
#is-14 {
	margin: -4px 5px 0px 0px;
	display: inline-block;
	float: left;
}

/* --------- FILES_TABLE.CSS --------- */
/* ajax loading info */
#attachFiles a.loading img {
	background: transparent url(/skins/common/icons/anim-wait-circle.gif) no-repeat left center;
	background-position: 0 0;
}
#attachFiles a .icon {
	cursor: pointer;
}

/* file description */
#attachFiles .deki-editable textarea {
	width: 90%;
	height: 80px;
}
#attachFiles .deki-editable {
	background: transparent url(/skins/common/icons/silk/pencil.png) no-repeat right center;
	padding: 2px 20px 2px 2px;
	cursor: pointer;
}
#attachFiles .editing:hover {
	cursor: default;
}
#attachFiles .deki-editable .saving {
	background: transparent url(/skins/common/icons/anim-wait-circle.gif) no-repeat right center;
	padding-right: 20px;
}

#attachFiles .file-moved em {
	font-style: italic;
}

/* actions menu default styles */
#attachFiles .deki-file-menu,
#menuFiller .deki-file-menu {
	display: none; /* hidden by default */
	position: absolute;
	z-index: 1000;
	border: 1px solid #c8c8c8;
	background-color: #fff;
	padding: 0;
	white-space: nowrap;
}
#menuFiller .deki-file-menu .menu-item {
	list-style-type: none;
}
#menuFiller .deki-file-menu a {
	text-decoration: none;
	display: block;
	padding: 5px 8px;
}
#menuFiller .deki-file-menu a:hover {
	background-color: #efefef;
}
#menuFiller .deki-file-menu .label {
	padding-left: 5px;
}

#attachFiles .disabled,
#menuFiller .deki-file-menu .disabled,
#menuFiller .deki-file-menu .disabled a {
	color: #999999;
}
#menuFiller .deki-file-menu .disabled a:hover {
	background-color: #fff;
}


/* --------- IMAGE_GALLERY_LITE.CSS --------- */

#deki-image-gallery-lite td {
	text-align: center;
	padding: 10px;
}

#deki-image-gallery-lite td.empty {
	font-style: italic;	
}

#deki-image-gallery-lite img {
	border: solid 1px #000;
	padding: 5px;
	margin-bottom: 10px;
}

#deki-image-gallery-lite span.description {
	display: block;
}


/* --------- SKIN.CSS --------- */
@CHARSET "UTF-8";

#cke_editarea .cke_button_mindtouchsave .cke_label,
#cke_editarea .cke_button_mindtouchcancel .cke_label,
#cke_editarea .cke_button_extensions .cke_label,
#cke_editarea .cke_button_table .cke_label,
#cke_editarea .cke_button_mindtouchimage .cke_label,
#cke_editarea .cke_button_mindtouchtemplates .cke_label,
#cke_editarea .cke_button_video .cke_label,
#cke_editarea .cke_button_tableoneclick .cke_label
{
	display: inline;
}

#cke_editarea .cke_button_insert .cke_label,
#cke_editarea .cke_button_view .cke_label,
#cke_editarea .cke_button_normal .cke_label
{
	display: inline;
	margin-right: 2px;
	padding-left: 0;
}

#cke_editarea .cke_button_insert .cke_icon,
#cke_editarea .cke_button_view .cke_icon,
#cke_editarea .cke_button_normal .cke_icon
{
	display: none;
}

#cke_editarea .cke_button_mindtouchsave .cke_icon
{
	background-position: 0 -32px;
}

#cke_editarea .cke_button_mindtouchimage .cke_icon
{
	background-position: 0 -576px;
}

#eareaParent .cke_editor .cke_toolbox .cke_toolbar a,
#eareaParent .cke_editor .cke_toolbox .cke_toolbar a:hover
{
	text-decoration: none;
}

.cke_skin_kama .cke_transformations_panel,
.cke_skin_v2 .cke_transformations_panel,
.cke_skin_office2003 .cke_transformations_panel,
.cke_skin_mindtouch .cke_transformations_panel
{
	width: 200px !important;
	height: 150px !important;
}

.cke_editor .cke_source
{
	overflow-y: auto;
}

/* remove toolbar padding in IE */
#eareaParent span.cke_editor
{
	padding-bottom: 0;
}

#eareaParent .cke_top
{
	position: relative;
	display: block;
}

/* clearfix */
.cke_top:after {
	visibility: hidden;
	display: block;
	font-size: 0;
	content: " ";
	clear: both;
	height: 0;
	}
* html .cke_top { zoom: 1; } /* IE6 */
*:first-child+html .cke_top { zoom: 1; } /* IE7 */

#eareaParent .cke_skin_kama .cke_top
{
	-moz-border-radius: 5px 5px 0 0;

	-webkit-border-bottom-left-radius: 0; 
	-webkit-border-bottom-right-radius: 0;
	-webkit-border-top-left-radius: 5px;
	-webkit-border-top-right-radius: 5px;
	
	border-radius: 5px 5px 0 0;
	background-color: #d3d3d3;
	background-image: url(/deki/plugins/page_editor_ckeditor/ckeditor/skins/kama/images/sprites.png);
	background-repeat: repeat-x;
	background-position: 0 -1950px;

	padding: 5px 5px 0 5px;
}

#eareaParent .cke_browser_ie .cke_top
{
	z-index: 1;
}

#eareaParent .cke_browser_ie6 .cke_top
{
	width: 100%; /* to trigger hasLayout */
}

#eareaParent .cke_wrapper
{
	display: block;
}

#eareaParent .cke_skin_kama .cke_wrapper
{
	-moz-border-radius: 0 0 5px 5px;
	
	-webkit-border-bottom-left-radius: 5px; 
	-webkit-border-bottom-right-radius: 5px;
	-webkit-border-top-left-radius: 0;
	-webkit-border-top-right-radius: 0;

	border-radius: 0 0 5px 5px;
	background-color: #d3d3d3;
}

#eareaParent .cke_skin_kama .cke_wrapper,
#eareaParent .cke_skin_kama .cke_browser_ie6 .cke_top,
#eareaParent .cke_skin_kama .cke_browser_iequirks .cke_top
{
	background-image: none;
}

#eareaParent .cke_skin_kama .cke_browser_webkit
{
	white-space: normal; /* @see #7992 */
}

/* DSBar Styles */
.cke_editor_editarea .cke_infobar
{
	position: absolute;
	height: 15px;
	padding: 5px 0;
	overflow: hidden;

	-moz-border-radius: 0 0 0 5px;

	-webkit-border-bottom-left-radius: 5px;
	-webkit-border-bottom-right-radius: 0;
	-webkit-border-top-left-radius: 0;
	-webkit-border-top-right-radius: 0;

	border-radius: 0 0 0 5px;
}

.cke_skin_kama .cke_infobar
{
	background-color: #d3d3d3;
	bottom: -25px;
	right: 5px;
}

.cke_skin_office2003 .cke_infobar,
.cke_skin_mindtouch .cke_infobar
{
	bottom: -28px;
	right: 0;
	background-color: #d6dff7;
	background-position: 0 -973px;
	background-repeat: repeat-x;
}

.cke_skin_office2003 .cke_infobar
{
	background-image: url(/deki/plugins/page_editor_ckeditor/ckeditor/skins/office2003/images/sprites.png);
	_background-image: url(/deki/plugins/page_editor_ckeditor/ckeditor/skins/office2003/images/sprites_ie6.png);
}

.cke_skin_mindtouch .cke_infobar
{
	background-image: url(/deki/plugins/page_editor_ckeditor/ckeditor/skins/mindtouch/images/sprites.png);
	_background-image: url(/deki/plugins/page_editor_ckeditor/ckeditor/skins/mindtouch/images/sprites_ie6.png);
}


.cke_skin_v2 .cke_infobar
{
	background-color: #efefde;
	bottom: -28px;
	right: 0;
}

.cke_editor_editarea .cke_infobar .cke_infopanel_group
{
	float: left;
	background: transparent url(/deki/plugins/page_editor_ckeditor/images/infobar-delim.gif) scroll no-repeat right center;
	padding: 0 1em;
}

.cke_editor_editarea .cke_infobar span
{
	cursor: default;
	filter: alpha(opacity=70); /* IE */
	opacity: 0.70; /* Safari, Opera and Mozilla */
}

.cke_editor_editarea .cke_hc .cke_infobar span
{
	opacity: 1.0;
	filter: alpha(opacity=100);
}

.cke_editor_editarea .cke_autosavepanel
{
	background-color: #ffff66;
	border-bottom: solid 2px #cccc99;
	border-top: solid 1px #ccc;
	color: #222;
	bottom: -52px;
	height: 50px;
	left: 0;
	position: absolute;
	width: 100%;
}

.cke_editor_editarea .cke_autosave_outdated
{
	background-color: #ffd266;
}

.cke_editor_editarea .cke_autosavepanel .cke_infopanel_group span
{
	display: block;
	text-align: center;
	padding: 5px;
	cursor: default;
}

.cke_editor_editarea .cke_autosavepanel .cke_infopanel_group a
{
	margin-right: 1em;
	text-decoration: underline;
	cursor: pointer;
	font-weight: bold;
	font-size: 10pt;
	text-decoration: none;
	color: #333;
}

.cke_editor_editarea .cke_autosavepanel .cke_infopanel_group .delimiter
{
	margin-right: 1em;
	display: inline;
}

.cke_editor_editarea .cke_autosavepanel .cke_infopanel_group a:hover
{
	text-decoration: underline;
	color: #000;
}

/* @see #MT-9987 */
.cke_editor_editarea textarea.infobar_enabled
{
	padding-top: 20px;
}

/* Menu button - active items */
.cke_skin_kama .cke_menuitem a.cke_on
{
	background-color: #D3D3D3;
	display:block;
}

.cke_hc .cke_menuitem a.cke_on
{
	border: 2px solid;
}

.cke_skin_kama .cke_menuitem a.cke_on .cke_icon_wrapper
{
	background-color: #9d9d9d;
	border: solid 4px #9d9d9d;
	filter: alpha(opacity=70); /* IE */
	opacity: 0.70; /* Safari, Opera and Mozilla */
}

.cke_skin_kama .cke_menuitem a.cke_on .cke_label
{
	background-color: #D3D3D3;
}

.cke_skin_office2003 .cke_menuitem a.cke_on
{
	background-color: #8db1ff;
	display: block;
}

.cke_skin_office2003 .cke_menuitem a.cke_on .cke_icon_wrapper
{
	background-color: #9d9d9d;
	border: solid 4px #9d9d9d;
	filter: alpha(opacity=70); /* IE */
	opacity: 0.70; /* Safari, Opera and Mozilla */
}

.cke_skin_office2003 .cke_menuitem a.cke_on .cke_label
{
	background-color: #8db1ff;
}

.cke_skin_v2 .cke_menuitem a.cke_on
{
	background-color: #8f8f73;
	display:block;
}

.cke_skin_v2 .cke_menuitem a.cke_on .cke_icon_wrapper
{
	background-color: #9d9d9d;
	border: solid 4px #9d9d9d;
	filter: alpha(opacity=70); /* IE */
	opacity: 0.70; /* Safari, Opera and Mozilla */
}

.cke_skin_v2 .cke_menuitem a.cke_on .cke_label
{
	background-color: #8f8f73;
	color: white;
}

/* Fix for Source menu item */
.cke_skin_kama .cke_menuitem .cke_button_source .cke_label,
.cke_skin_v2 .cke_menuitem .cke_button_source .cke_label,
.cke_skin_office2003 .cke_menuitem .cke_button_source .cke_label,
.cke_skin_mindtouch .cke_menuitem .cke_button_source .cke_label
{
	display: block;
}

/* Discard changes dialog buttons */
.cke_dialog a.cke_dialog_ui_button_discard span,
.cke_dialog a.cke_dialog_ui_button_continue span
{
	width:90px;
}


/* --------- PAGE_TAGS.CSS --------- */
/* Tag display */
#deki-page-tags {
	overflow: auto;
}

#deki-page-tags ul.tags {
	overflow: auto;
	padding: 0px;
}

#deki-page-tags li {
	max-width: 300px;
	overflow: hidden;
	white-space: nowrap;
	text-overflow: ellipsis;
	list-style-type: none;
	float: left;
	padding-left: 10px;
}

/* Tag editing */
#deki-page-tags .tag-edit {
	border: 1px solid #cdcdcd;
	padding: 10px;
	overflow: hidden;
	width: 550px;
	margin: 0 auto;
	background: #f1f1f1;
	position: relative;
}

#deki-page-tags form {
	margin-bottom: 15px;
}

#deki-page-tags .input-button {
	margin: 0px 6px 0px 6px;
}

#deki-page-tags-add {
	width: 305px;
}

#deki-page-tags-close {
	height: 15px;
	width: 25px;
	position: absolute;
	right: 6px;
	top: 5px;
	background: transparent url(/skins/common/icons/container-close.png) no-repeat center;
}

#deki-page-tags-close span {
	display: none;
}

#deki-page-tags-left,
#deki-page-tags-right {
	width: 260px;
	overflow: hidden;
	float: left;
}

#deki-page-tags .tag-edit li {
	width: 240px;
	overflow: hidden;
	text-overflow: ellipsis;
	float: left;
	margin-bottom: 2px;
}

#deki-page-tags .tag-delete {
	float: left;
	width: 16px;
	height: 16px;
	display: inline-block;
	margin-right: 2px;
	background: transparent url(/skins/common/icons/silk/cross.png) no-repeat center;
}

#deki-page-tags .ac_loading {
	background: #ffffff url(/skins/common/icons/loading.gif) no-repeat right;
}

#deki-page-tags .loading {
	background: transparent url(/skins/common/icons/loading.gif) no-repeat center;
}

#deki-page-tags .tag-type {
	font-size: 90%;
	color: #666;
	padding-left: 5px;
}

#deki-page-tags a.date {
	background: transparent url(/skins/common/icons/silk/calendar_view_month.png) no-repeat left;
	padding-left: 18px;
}

#deki-page-tags a.user {
	background: transparent url(/skins/common/icons/silk/user.png) no-repeat left;
	padding-left: 18px;
}

#deki-page-tags a.define {
	background: transparent url(/skins/common/icons/silk/book_open.png) no-repeat left;
	padding-left: 18px;
}

#deki-page-tags .tag-type {
	display: none;
}

#deki-page-tags .tag-edit .tag-type {
	display: inline;
}

#deki-page-tags .tag-edit a.text,
#deki-page-tags .tag-edit a.date,
#deki-page-tags .tag-edit a.define,
#deki-page-tags .tag-edit a.user {
	padding: 0px 3px 0px 3px;
	background-image: none;
}

#deki-page-tags a.highlight {
	background: #ccc;
}

#deki-page-tags-toggleview .tag-edit {
	margin-top: 0.5em;
	display: block;
	clear: both;
}

/* IE6 float fixes */
* html body #deki-page-tags .tag-type {
	display: none;
}

* html body #deki-page-tags ul.tags li {
	width: 240px;
	text-overflow: hidden;
	overflow: hidden;
	text-align: left;
}

* html body #deki-page-tags div.tag-edit ul {
	display: inline;
}

* html body .ac_results span.count {
	float: none;
	padding-left: 10px;
}

/* IE7 float fix */
*:first-child+html .ac_results span.count {
	float: none;
	padding-left: 10px;
}

/* IE6 auto-margin centering fix */
* html body #deki-page-tags {
	text-align: center;
}

* html body #deki-page-tags .tag-edit {
	text-align: left;
}


/* --------- PAGE_ALERTS.CSS --------- */
/* reset styles */
#deki-page-alerts div,
#deki-page-alerts ul {
	margin: 0;
	padding: 0;
}

#deki-page-alerts {
	float: right;
}
#deki-page-alerts span.status {
	font-weight: bold;
}

#deki-page-alerts div.toggle {
	padding: 6px 6px 6px 8px;
	background-color: #eee;
	border: 1px solid #c8c8c8;
}
#deki-page-alerts div.with-options {
	border-bottom: none;
}
#deki-page-alerts div.toggle a {
	padding: 4px 4px 4px 25px;
	background: url(/skins/common/icons/alert_on.gif) no-repeat center left;
	text-decoration: none;
}
#deki-page-alerts div.toggle a.off {
	background: url(/skins/common/icons/alert_off.gif) no-repeat center left;
}
#deki-page-alerts div.toggle a.loading {
	background: url(/skins/common/icons/anim-wait-circle.gif) no-repeat center left;
}

#deki-page-alerts form {
	display: none; /* hidden by default */
	position: absolute;
	z-index: 9999;
	border: 1px solid #c8c8c8;
	background-color: #fff;
}
#deki-page-alerts form.options li {
	list-style-type: none;
	padding: 5px 5px;
	white-space: nowrap;
}
#deki-page-alerts form.options li.off {
	background-color: #d9d9d9;
}
#deki-page-alerts form.options input {
	margin: 0 5px;
}


/* --------- PAGE_CONTENT_RATING.CSS --------- */
#deki-page-rating-bar {
	float: right;
	padding: 4px 5px 4px 8px;
	margin: 4px;
	color: #000;
	font-size: 11px;
	font-weight: bold;
	border: 1px solid #888;
	border-radius: 5px;
	-webkit-border-radius: 5px;
	-moz-border-radius: 5px;
	background: #fef3cc;
	background: -webkit-gradient(linear, left top, left bottom, from(#fff), to(#fef3cc));
	background: -moz-linear-gradient(top,  #fff,  #fef3cc);
	filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffffff', endColorstr='#fef3cc');
}

#deki-page-rating-bar .description {
	display: none;
}

#deki-page-rating,
#deki-page-rating-bar {
	overflow: hidden;
}

#deki-page-rating-score {
	float: left;
	padding-right: 5px;
}

#deki-page-rating-bar div.deki-page-rating-buttons {
	float: left;
}

#deki-page-rating div.deki-page-rating-buttons {
	overflow: hidden;
}

#deki-page-rating-comment {
 	width: 250px;
}

#deki-page-rating a {
	text-decoration: none;
	margin-left: 3px;
}

.deki-page-rating-buttons a {
	float: left;
	display: inline-block;
	padding: 0px 0px 0px 20px;
	height: 18px;
}

.deki-page-rating-up {
	background: transparent url(/deki/plugins/page_content_rating/icons/icon-thumb-up-18.png) no-repeat left;
	padding: 5px 0px 5px 20px;
}

.deki-page-rating-up-highlight {
	background: transparent url(/deki/plugins/page_content_rating/icons/icon-thumb-up-highlight-18.png) no-repeat left;
	padding: 5px 0px 5px 20px;
}

.deki-page-rating-down {
	background: transparent url(/deki/plugins/page_content_rating/icons/icon-thumb-down-18.png) no-repeat left;
	padding: 5px 0px 5px 20px;
}

.deki-page-rating-down-highlight {
	background: transparent url(/deki/plugins/page_content_rating/icons/icon-thumb-down-highlight-18.png) no-repeat left;
	padding: 5px 0px 5px 20px;
}


/* --------- PAGE_TITLE_EDITOR.CSS --------- */
/* long title fix */
#deki-page-title .state-view,
#deki-page-title .state-hover {
	overflow: hidden;
}

/* editor common */
#deki-page-title.ui-state-hover,
#deki-page-title.ui-state-edit {
	position: relative;
	/* z-index here for ie6 */
	z-index: 999;
}

/* ie6 fix */
* html body #deki-page-title {
	position: relative;
}

#deki-page-title a {
	cursor: pointer;
}

#deki-page-title .state-edit,
#deki-page-title .state-hover {
	display: none;

	position: absolute;
	top: 0;
	left: 0;
	padding: 2px;

	-moz-border-radius: 5px;
	background-color: #ddd;
	/* experimenting */
	-moz-box-shadow: 2px 2px 2px #aaa;
	-webkit-box-shadow: 2px 2px 2px #aaa;
	box-shadow: 2px 2px 2px #aaa;
}
#deki-page-title .state-edit {
	right: 0;
}

#deki-page-title .state-hover .title {
	display: block;
	background-color: #fff;
	-moz-border-radius: 5px 5px 0 0;
	padding: 5px;
}

#deki-page-title .state-hover a.edit,
#deki-page-title .state-edit .submit {
	display: block;
	padding: 5px;
	font-size: 8pt;
	font-weight: normal;
}

/* enable hovering */
#deki-page-title.ui-state-hover .state-hover { display: block; }
#deki-page-title.ui-state-hover .state-view  { visibility: hidden; }

/* enable editing */
#deki-page-title.ui-state-edit {
	font-weight: normal;
}

#deki-page-title.ui-state-edit .state-edit  { display: block; }
#deki-page-title.ui-state-edit .state-hover { display: none; }
#deki-page-title.ui-state-edit .state-view 	{ visibility: hidden; }


/* edit styles */
#deki-page-title .state-edit {
	display: none;
	visibility: visible;
}

#deki-page-title .state-edit .fields {
	background-color: #fff;
	padding: 5px;
}
#deki-page-title .state-edit .edit-title {
	padding: 1px;
	font-size: 100%;
	font-weight: bold;
	width: 95%;
}
#deki-page-title .ui-state-fixed .edit-title {
	width: 99%;
}

#deki-page-title .state-edit a.toggle-link {
	display: inline-block;
	margin-top: 5px;
	margin-left: 5px;
	width: 20px;
	height: 20px;

	background: transparent url(/deki/plugins/page_title_editor/icons/icon-linked.png) no-repeat center center;
	border: solid 1px #ccc;
	vertical-align: top;
}

#deki-page-title .state-edit.ui-state-unlinked a.toggle-link {
	background-image: url(/deki/plugins/page_title_editor/icons/icon-unlinked.png);
}

#deki-page-title .state-edit.ui-state-fixed a.toggle-link {
	display: none;
	background-image: url(/deki/plugins/page_title_editor/icons/icon-fixed.png);
	cursor: default;
}

#deki-page-title .state-edit div.path {
	display: none;
	font-size: 12px;
	padding: 5px 0 2px 21px;
	background: url(/skins/common/icons/silk/world_link.png) no-repeat center left; 
}

#deki-page-title .state-edit div.path input {
	padding: 2px; 
	margin-left: 2px; 
	font-size: 12px;
	width: 200px;
}
#deki-page-title .state-edit.ui-state-unlinked div.path {
	display: block;
}

#deki-page-title .state-edit.ui-state-unlinked div.path span.collapsed-url {
	background: url(/deki/plugins/page_title_editor/icons/icon-shortened.png) no-repeat center right; 
	padding-right: 28px;
}

#deki-page-title.ui-state-with-editor {
	-moz-border-radius: 5px;
	background-color: #fff;
	border: 1px solid  #d3d3d3;
	margin-bottom: 10px;
	padding: 5px;
}

/* --------- JQUERY.QTIP.CSS --------- */
.qtip-dark a,
.qtip-dark a:visited {
   color: #8888ff;
}

.qtip-dark a:hover {
	color: #ccc;
}

