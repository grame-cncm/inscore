{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 94.0, 44.0, 488.0, 380.0 ],
		"bglocked" : 0,
		"defrect" : [ 94.0, 44.0, 488.0, 380.0 ],
		"openrect" : [ 94.0, 44.0, 224.0, 218.0 ],
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
					"text" : "prepend set",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 267.0, 258.0, 74.0, 20.0 ],
					"id" : "obj-1",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "$0",
					"fontname" : "Arial",
					"presentation_rect" : [ 164.0, 121.0, 33.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0,
					"frgb" : [ 0.615686, 0.019608, 0.019608, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 267.0, 285.0, 45.0, 23.0 ],
					"presentation" : 1,
					"id" : "obj-7",
					"textcolor" : [ 0.615686, 0.019608, 0.019608, 1.0 ],
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Current pages count:",
					"presentation_linecount" : 2,
					"fontname" : "Arial",
					"presentation_rect" : [ 115.0, 109.0, 85.0, 29.0 ],
					"fontface" : 1,
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 461.0, 104.0, 115.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-3",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"outlettype" : [ "", "int" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 388.0, 200.0, 139.0, 20.0 ],
					"id" : "obj-14",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s pagemanager",
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 388.0, 264.0, 94.0, 20.0 ],
					"id" : "obj-13",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL/scene save",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 388.0, 232.0, 143.0, 20.0 ],
					"id" : "obj-11",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"numinlets" : 1,
					"patching_rect" : [ 388.0, 137.0, 20.0, 20.0 ],
					"id" : "obj-10",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "savedialog text",
					"outlettype" : [ "", "", "bang" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 388.0, 169.0, 91.0, 20.0 ],
					"id" : "obj-8",
					"numoutlets" : 3
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "save",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"presentation_rect" : [ 60.0, 101.0, 37.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 388.0, 103.0, 36.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-6",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene load layout.inscore",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 357.0, 481.0, 170.0, 18.0 ],
					"id" : "obj-5",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "INScore Page Manager",
					"fontname" : "Arial",
					"presentation_rect" : [ 19.0, 12.0, 184.0, 25.0 ],
					"fontface" : 1,
					"fontsize" : 16.0,
					"numinlets" : 1,
					"patching_rect" : [ 314.0, 22.0, 210.0, 25.0 ],
					"presentation" : 1,
					"id" : "obj-29",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "autofit 1",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 225.0, 419.0, 53.0, 18.0 ],
					"id" : "obj-100",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read INScore.png",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 239.0, 440.0, 105.0, 18.0 ],
					"id" : "obj-99",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "fpic",
					"presentation_rect" : [ 35.0, 136.0, 76.0, 71.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 239.0, 477.0, 86.0, 79.0 ],
					"pic" : "INScore.png",
					"presentation" : 1,
					"id" : "obj-98",
					"numoutlets" : 0,
					"autofit" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL/scene rootPath",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 405.0, 459.0, 163.0, 20.0 ],
					"id" : "obj-34",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"outlettype" : [ "", "int" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 405.0, 436.0, 139.0, 20.0 ],
					"id" : "obj-35",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 355.0, 390.0, 34.0, 18.0 ],
					"id" : "obj-51",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"outlettype" : [ "", "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 355.0, 411.0, 69.0, 20.0 ],
					"id" : "obj-53",
					"numoutlets" : 2,
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Initialization",
					"fontname" : "Arial",
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"patching_rect" : [ 358.0, 335.0, 91.0, 23.0 ],
					"id" : "obj-56",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "reload",
					"fontname" : "Arial",
					"presentation_rect" : [ 153.0, 183.0, 41.0, 18.0 ],
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 225.0, 358.0, 41.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-59",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 125.0, 182.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 232.0, 332.0, 20.0, 20.0 ],
					"presentation" : 1,
					"id" : "obj-60",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s pagemanager",
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 405.0, 513.0, 94.0, 20.0 ],
					"id" : "obj-61",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"outlettype" : [ "bang", "bang", "bang", "bang" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 270.0, 361.0, 59.5, 20.0 ],
					"id" : "obj-62",
					"numoutlets" : 4
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"outlettype" : [ "bang" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 270.0, 332.0, 60.0, 20.0 ],
					"id" : "obj-67",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 221.0, 325.0, 295.0, 216.0 ],
					"id" : "obj-68",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"fontname" : "Arial",
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"patching_rect" : [ 34.0, 336.0, 158.0, 23.0 ],
					"id" : "obj-40",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r pagemanager",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 0,
					"patching_rect" : [ 35.0, 367.0, 92.0, 20.0 ],
					"id" : "obj-39",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"patching_rect" : [ 35.0, 407.0, 136.0, 20.0 ],
					"id" : "obj-72",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"numinlets" : 1,
					"patching_rect" : [ 14.0, 325.0, 196.0, 119.0 ],
					"id" : "obj-47",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "or drop files =>",
					"linecount" : 2,
					"fontname" : "Arial",
					"presentation_rect" : [ 45.0, 74.0, 85.0, 18.0 ],
					"fontface" : 1,
					"fontsize" : 10.0,
					"numinlets" : 1,
					"patching_rect" : [ 130.0, 54.0, 69.0, 29.0 ],
					"presentation" : 1,
					"id" : "obj-332",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "hint",
					"hint" : "Glissez des fichiers guido (.gmn).",
					"presentation_rect" : [ 130.0, 57.0, 68.0, 51.0 ],
					"delay" : 1,
					"numinlets" : 1,
					"patching_rect" : [ 192.0, 31.0, 68.0, 51.0 ],
					"presentation" : 1,
					"id" : "obj-318",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "dropfile",
					"outlettype" : [ "", "" ],
					"bordercolor" : [ 0.223529, 0.223529, 0.223529, 1.0 ],
					"presentation_rect" : [ 143.0, 60.0, 42.0, 42.0 ],
					"types" : [  ],
					"numinlets" : 1,
					"patching_rect" : [ 209.0, 38.0, 33.0, 42.0 ],
					"presentation" : 1,
					"id" : "obj-12",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend addPage",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 39.0, 174.0, 106.0, 20.0 ],
					"id" : "obj-2",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"presentation_rect" : [ 153.0, 159.0, 37.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 158.0, 174.0, 37.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-25",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s pagemanager",
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 158.0, 256.0, 94.0, 20.0 ],
					"id" : "obj-21",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "compile",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 196.0, 189.0, 52.0, 18.0 ],
					"id" : "obj-18",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "js pagemgr.js",
					"outlettype" : [ "", "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 158.0, 219.0, 81.0, 20.0 ],
					"id" : "obj-17",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "add image file",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"presentation_rect" : [ 32.0, 50.0, 95.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 104.0, 29.0, 85.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-75",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"outlettype" : [ "", "int" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 39.0, 137.0, 139.0, 20.0 ],
					"id" : "obj-81",
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"outlettype" : [ "bang" ],
					"numinlets" : 1,
					"patching_rect" : [ 104.0, 67.0, 20.0, 20.0 ],
					"id" : "obj-80",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "set",
					"outlettype" : [ "" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 2,
					"patching_rect" : [ 40.0, 73.0, 32.5, 18.0 ],
					"id" : "obj-76",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "opendialog",
					"outlettype" : [ "", "bang" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"numinlets" : 1,
					"patching_rect" : [ 39.0, 108.0, 77.0, 20.0 ],
					"id" : "obj-69",
					"numoutlets" : 2
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 229.5, 248.0, 276.5, 248.0 ]
				}

			}
, 			{
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [ 48.5, 206.0, 167.5, 206.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-17", 0 ],
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
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
