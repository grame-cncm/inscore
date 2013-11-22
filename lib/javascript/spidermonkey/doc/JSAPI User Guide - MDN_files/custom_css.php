/* 
	cache-developer.mozilla.org.10.1.1-a6affa3d65ae00b80bc195ae6bf82d29 (7,627)
 */

/* --------- CACHE-DEVELOPER.MOZILLA.ORG.10.1.1-A6AFFA3D65AE00B80BC195AE6BF82D29 --------- */
.method{
	margin-left: 10px;
	margin-bottom: 2em;
	margin-top:  1em;
}

.method > .name{
  display: block;
  font-size: 13pt;
  margin-bottom: .2em;
}

.method>.name>.param:after{content: ","; padding-right: .5em; }
.method>.name>.param:last-of-type:after{content: ""; }
.method>.name>.param>.name:after{content: " as "; font-weight: normal; }

.method>.name>.param:not(.required){ font-style:italic; }
.method>.name>.param:not(.required):before{content:"[";}
.method>.name>.param:not(.required):after{content:"]";}

.method>.description{
  display: block;
	font-size: 10pt;
	color: #444;
	font-style: italic;
	margin-bottom: 7px;
}

.method>.name>.returns:before{content: " returns "; font-weight: normal; font-style:italic; }
.method>.name>.returns{ font-weight: bold; }

.method>.params{display: block; color:#555;}
.method>.params>.param{display: block; margin-bottom:5px;}
.method>.params>.param>.name{font-weight:bold; margin-right:.5em; min-width:80px; display:inline-block;}
.method>.params>.param>.description{display:inline-block; width:300px; vertical-align:top;margin-right:30px}

.method>.params>.param>.type{display:inline-block; width:150px; vertical-align:top;font-weight:bold;}
.method>.params>.param>.type:before{content: "Type "; color: #888; font-weight:normal;}
.method>.params>.param>.default{display:inline-block; width:150px; vertical-align:top;font-weight:bold;}
.method>.params>.param>.default:before{content: "Default "; color: #888;font-weight:normal;}

.geckoVersionNote {
  border-left: 5px solid #000088;
  background: #e0e0ff;
  background: -moz-radial-gradient(0px 0px 45deg, circle cover, #e0e0ff 0%, #f8f8ff 80%);
}

.geckoVersionNote p {
  padding-left: 4px;
  border: 0px;
}

.geckoVersionNoteNew {
    background:#ffc;
    display: block;
    position: relative;  
    padding: 3em 3.5em .5em .7em;
    overflow: hidden;
}

.geckoVersionNoteNew p {
        margin: 0 0 1em;
        -webkit-transform: translateX(2.5em) translateY(-2em);
        -moz-transform:    translateX(2.5em) translateY(-2em);
        -ms-transform:     translateX(2.5em) translateY(-2em);
        -o-transform:      translateX(2.5em) translateY(-2em);
        transform:         translateX(2.5em) translateY(-2em);     
}

.geckoVersionHeading {
  background: #000088;
  background: -moz-linear-gradient(left, #000088 50%, #e0e0ff 80%);
  color: #ffffff;
  font: 16px/1.7 Verdana,Tahoma,sans-serif;
  margin-top: 0px;
  margin-left: 0px;
  margin-bottom: 4px;
  height: 42px;
}

.geckoVersionHeadingNew {
    font: 16px/1.7 Verdana,Tahoma,sans-serif;
    background: #369;
    color: #fff;
    padding: .7em;
    margin: 0;
    line-height: 1;
    position: absolute;
    top: 0;
    left: 0;
    width: 1000%;
    -webkit-transform: rotate(90deg) translateX(20px);
    -moz-transform:    rotate(90deg) translateX(20px);
    -ms-transform:     rotate(90deg) translateX(20px);
    -o-transform:      rotate(90deg) translateX(20px);
    transform:         rotate(90deg) translateX(20px);
    -webkit-transform-origin: 1.8em .5em;
    -moz-transform-origin:    1.8em .5em;
    -ms-transform-origin:     1.8em .5em;
    -o-transform-origin:      1.8em .5em;
    transform-origin:         1.8em .5em;
}

.vtab {
	margin: auto;
	width: 100%;
}

.vtab > ul > li {
	background-image: none;
	width:100px;
	height:30px;
	list-style-type:none;
	display:block;
	padding-bottom:3px;
	border: 1px solid #ddd;
	padding-top:8px;
	text-align:left;
	font-size:13px;
	font-weight:bold;
	margin:auto;
	position:relative;
	padding-left:6px;
	border-right:none;
	opacity:.5;
        -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=50)";
        filter: progid:DXImageTransform.Microsoft.Alpha(Opacity=50);
	cursor:pointer;
}

.vtab > ul > li.selected {
	opacity:1;
        -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=100)";
        filter: progid:DXImageTransform.Microsoft.Alpha(Opacity=100);
        border: 1px solid #ddd;
        border-right: none;
        z-index: 10;
        background-color: #f1f6f8 !important;
        position: relative;
	cursor:pointer;
}

.vtab > ul {
	width:100px;
	float:left;
	text-align:left;
	display:block;
	padding:0;
	margin:auto 0;
	position:relative;
	top:30px;
}

.vtab > div {
            background-color: #f1f6f8;
            margin-left: 106px;
            border: 1px solid #ddd;
	    min-height: 300px;
            padding: 12px;
            position: relative;
            z-index: 9;
}

.sidebar-box {
	border-right:1px solid #ecf1f3;
	margin-left:16px;
	padding:12px;
	background:#f1f6f8 url("img/toc-bg.png") 0 0 no-repeat;
	font:12px Verdana,Tahoma,sans-serif;
	margin-bottom: 2.5em;
}

.sidebar-box h2 {
	margin-bottom:.5em;
	font-family:inherit;
	font-size:150%;
	font-weight:bold;
}

.sidebar-box h3 {
	margin-bottom:.5em;
	font-family:inherit;
	font-size:110%;
	font-weight:bold;
}

.sidebar-box h5 {
	margin-bottom:.5em;
	font-family:inherit;
	font-size:90%;
	font-weight:bold;
}

.sidebar-box > ul {
	float:left;
	text-align:left;
	display:block;
	padding:0;
	margin:auto 0;
	position:relative;
}

.sidebar-box ul > li {
	list-style-type:none;
}

.tab-content-box {
	border-right:1px solid #ecf1f3;
	margin-left:16px;
	padding:12px;
	background:#ffffff;
	font:12px Verdana,Tahoma,sans-serif;
}

.tab-content-box h2 {
	margin-bottom:.5em;
	font-family:inherit;
	font-size:150%;
	font-weight:bold;
}

.tab-content-box h3 {
	margin-bottom:.5em;
	font-family:inherit;
	font-size:110%;
	font-weight:bold;
}

.tab-content-box h5 {
	margin-bottom:.5em;
	font-family:inherit;
	font-size:90%;
	font-weight:bold;
}

#menuFiller { display: block; }

.threecolumns {
	-moz-column-count:3;
	column-count:3;
	-webkit-column-count:3;
}

.htab {
	margin: auto;
        display: inline-block;
	width: auto;
}

.htab > ul > li {
	background-image: none;
	width:150px;
	height:30px;
	list-style-type:none;
	display:inline;
	padding-bottom:3px;
	border: 1px solid #ddd;
	padding-top:5px;
	text-align:left;
	font-size:13px;
	font-weight:bold;
	margin:auto;
	position:relative;
	padding-left:6px;
	padding-right:6px;
	border-bottom:none;
	opacity:.5;
        -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=50)";
        filter: progid:DXImageTransform.Microsoft.Alpha(Opacity=50);
	cursor:pointer;
}

.htab > ul > li.selected {
	opacity:1;
  -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=100)";
  filter: progid:DXImageTransform.Microsoft.Alpha(Opacity=100);
  border: 1px solid #ddd;
  border-bottom: none;
  z-index: 10;
  background-color: #f1f6f8 !important;
  position: relative;
	cursor:pointer;
}

.htab > ul {
	width:150px;
	text-align:left;
	display:inline;
	padding:0;
	margin:0 auto;
	position:relative;
	top:1px;
}

.htab > div {
  background-color: #f1f6f8;
  margin-top: 0px;
  border: 1px solid #ddd;
  padding: 12px;
  position: relative;
  z-index: 9;
  word-wrap: break-word;
}

table.compat-table { border: 1px solid #bbb; border-collapse: collapse;}
table.compat-table td { padding: 5px; border: 1px solid #ccc; text-align: left; background: #fff; vertical-align: top; word-wrap: break-word; }
table.compat-table td.header, table.compat-table th { border: 1px solid #bbb; padding: 0 5px; background: #eee; text-align: left; font-weight: bold; }

.archivedContentBlock {
	margin:0px;
	background-color:#ffdddd;
}
