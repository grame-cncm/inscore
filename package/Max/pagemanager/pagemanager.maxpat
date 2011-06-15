{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 304.0, 65.0, 219.0, 230.0 ],
		"bglocked" : 0,
		"defrect" : [ 304.0, 65.0, 219.0, 230.0 ],
		"openrect" : [ 304.0, 65.0, 213.0, 224.0 ],
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 565.0, 326.0, 139.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-14",
					"outlettype" : [ "", "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s pagemanager",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 565.0, 390.0, 94.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-13",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL/scene save",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 565.0, 358.0, 143.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-11",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 565.0, 263.0, 20.0, 20.0 ],
					"id" : "obj-10",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "savedialog text",
					"numinlets" : 1,
					"numoutlets" : 3,
					"patching_rect" : [ 565.0, 295.0, 91.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-8",
					"outlettype" : [ "", "", "bang" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "save",
					"presentation_rect" : [ 60.0, 101.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 565.0, 229.0, 36.0, 18.0 ],
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-6",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene load layout.inscore",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 357.0, 481.0, 170.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-5",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "INScore Page Manager",
					"presentation_rect" : [ 19.0, 12.0, 184.0, 25.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 617.0, 23.0, 210.0, 25.0 ],
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-29",
					"fontface" : 1,
					"fontsize" : 16.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "autofit 1",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 225.0, 419.0, 53.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-100",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read INScore.png",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 239.0, 440.0, 105.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-99",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "fpic",
					"presentation_rect" : [ 35.0, 136.0, 76.0, 71.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 239.0, 477.0, 86.0, 79.0 ],
					"pic" : "INScore.png",
					"presentation" : 1,
					"id" : "obj-98",
					"autofit" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL/scene rootPath",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 405.0, 459.0, 163.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-34",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 405.0, 436.0, 139.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-35",
					"outlettype" : [ "", "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 355.0, 390.0, 34.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-51",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 355.0, 411.0, 69.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-53",
					"outlettype" : [ "", "" ],
					"fontsize" : 12.0,
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Initialization",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 358.0, 335.0, 91.0, 23.0 ],
					"fontname" : "Arial",
					"id" : "obj-56",
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "reload",
					"presentation_rect" : [ 150.0, 176.0, 41.0, 18.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 225.0, 358.0, 41.0, 18.0 ],
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-59",
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"presentation_rect" : [ 122.0, 175.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 232.0, 332.0, 20.0, 20.0 ],
					"presentation" : 1,
					"id" : "obj-60",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s pagemanager",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 405.0, 513.0, 94.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-61",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"numinlets" : 1,
					"numoutlets" : 4,
					"patching_rect" : [ 270.0, 361.0, 59.5, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-62",
					"outlettype" : [ "bang", "bang", "bang", "bang" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 270.0, 332.0, 60.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-67",
					"outlettype" : [ "bang" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 221.0, 325.0, 295.0, 216.0 ],
					"id" : "obj-68",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 34.0, 336.0, 158.0, 23.0 ],
					"fontname" : "Arial",
					"id" : "obj-40",
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r pagemanager",
					"numinlets" : 0,
					"numoutlets" : 1,
					"patching_rect" : [ 35.0, 367.0, 92.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-39",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 35.0, 407.0, 136.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-72",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 14.0, 325.0, 196.0, 119.0 ],
					"id" : "obj-47",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "prevPage",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 516.0, 80.0, 62.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-22",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "nextPage",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 451.0, 80.0, 61.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-19",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "or drop files",
					"presentation_rect" : [ 45.0, 74.0, 78.0, 18.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 130.0, 54.0, 66.0, 18.0 ],
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-332",
					"fontface" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "hint",
					"hint" : "Glissez des fichiers guido (.gmn).",
					"presentation_rect" : [ 130.0, 52.0, 68.0, 51.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 192.0, 31.0, 68.0, 51.0 ],
					"presentation" : 1,
					"delay" : 1,
					"id" : "obj-318"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "dropfile",
					"bordercolor" : [ 0.223529, 0.223529, 0.223529, 1.0 ],
					"presentation_rect" : [ 143.0, 55.0, 42.0, 42.0 ],
					"numinlets" : 1,
					"numoutlets" : 2,
					"types" : [  ],
					"patching_rect" : [ 209.0, 38.0, 33.0, 42.0 ],
					"presentation" : 1,
					"id" : "obj-12",
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend addPage",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 39.0, 174.0, 106.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-2",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _pagemgr",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 39.0, 205.0, 74.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-3",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _pagemgr",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 455.0, 181.0, 74.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-26",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset",
					"presentation_rect" : [ 150.0, 152.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 327.0, 79.0, 37.0, 18.0 ],
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-25",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _pagemgr",
					"numinlets" : 0,
					"numoutlets" : 1,
					"patching_rect" : [ 212.0, 181.0, 72.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-24",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s pagemanager",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 212.0, 261.0, 94.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-21",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "setPage $1",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 374.0, 79.0, 71.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-20",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "compile",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 300.0, 188.0, 52.0, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-18",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "js pagemgr.js",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 212.0, 224.0, 81.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-17",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /reset /page /next /prev",
					"numinlets" : 1,
					"numoutlets" : 5,
					"patching_rect" : [ 327.0, 45.0, 251.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-15",
					"outlettype" : [ "", "", "", "", "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7101",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 327.0, 17.0, 99.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-9",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "add image file",
					"presentation_rect" : [ 32.0, 50.0, 95.0, 18.0 ],
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 104.0, 29.0, 85.0, 18.0 ],
					"fontname" : "Arial",
					"presentation" : 1,
					"id" : "obj-75",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 39.0, 137.0, 139.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-81",
					"outlettype" : [ "", "int" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"patching_rect" : [ 104.0, 67.0, 20.0, 20.0 ],
					"id" : "obj-80",
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set",
					"numinlets" : 2,
					"numoutlets" : 1,
					"patching_rect" : [ 40.0, 73.0, 32.5, 18.0 ],
					"fontname" : "Arial",
					"id" : "obj-76",
					"outlettype" : [ "" ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "opendialog",
					"numinlets" : 1,
					"numoutlets" : 2,
					"patching_rect" : [ 39.0, 108.0, 77.0, 20.0 ],
					"fontname" : "Arial",
					"id" : "obj-69",
					"outlettype" : [ "", "bang" ],
					"fontsize" : 12.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-34", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-61", 0 ],
					"hidden" : 0,
					"midpoints" : [ 414.5, 492.5, 414.5, 492.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-61", 0 ],
					"hidden" : 0,
					"midpoints" : [ 366.5, 505.5, 414.5, 505.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 2 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 1 ],
					"destination" : [ "obj-99", 0 ],
					"hidden" : 0,
					"midpoints" : [ 293.0, 412.0, 248.5, 412.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-100", 0 ],
					"hidden" : 0,
					"midpoints" : [ 279.5, 401.5, 234.5, 401.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-100", 0 ],
					"destination" : [ "obj-98", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-99", 0 ],
					"destination" : [ "obj-98", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-53", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-53", 1 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 414.5, 438.5, 414.5, 438.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-62", 0 ],
					"hidden" : 0,
					"midpoints" : [ 241.5, 354.0, 279.5, 354.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 3 ],
					"destination" : [ "obj-51", 0 ],
					"hidden" : 0,
					"midpoints" : [ 320.0, 387.0, 364.5, 387.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-67", 0 ],
					"destination" : [ "obj-62", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-72", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-81", 0 ],
					"hidden" : 0,
					"midpoints" : [ 218.5, 132.5, 48.5, 132.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 2 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 1 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 3 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 0 ],
					"destination" : [ "obj-81", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-75", 0 ],
					"destination" : [ "obj-80", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-76", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-80", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [ 113.5, 97.0, 48.5, 97.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-81", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
