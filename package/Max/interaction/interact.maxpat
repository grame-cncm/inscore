{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 40.0, 59.0, 267.0, 222.0 ],
		"bglocked" : 0,
		"defrect" : [ 40.0, 59.0, 267.0, 222.0 ],
		"openrect" : [ 40.0, 59.0, 267.0, 222.0 ],
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
					"maxclass" : "comment",
					"text" : "This patch illustrates how to interact with a score using 'watched events'.\nIt also illustrates the objects graphic 'origin'  settings.",
					"linecount" : 5,
					"presentation_linecount" : 4,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 10.0, 146.0, 238.0, 71.0 ],
					"id" : "obj-16",
					"fontname" : "Arial",
					"frgb" : [ 0.282353, 0.282353, 0.282353, 1.0 ],
					"patching_rect" : [ 542.0, 179.0, 211.0, 87.0 ],
					"presentation" : 1,
					"fontsize" : 14.0,
					"textcolor" : [ 0.282353, 0.282353, 0.282353, 1.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "cycle~ 220",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"patching_rect" : [ 156.0, 85.0, 68.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "del",
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 227.0, 102.0, 23.0, 18.0 ],
					"id" : "obj-42",
					"fontname" : "Arial",
					"patching_rect" : [ 662.0, 64.0, 41.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"presentation_rect" : [ 229.0, 118.0, 20.0, 20.0 ],
					"outlettype" : [ "bang" ],
					"id" : "obj-43",
					"patching_rect" : [ 662.0, 88.0, 20.0, 20.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/[^r]* del",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-41",
					"fontname" : "Arial",
					"patching_rect" : [ 499.0, 133.0, 110.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend yorigin",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-37",
					"fontname" : "Arial",
					"patching_rect" : [ 365.0, 83.0, 93.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend xorigin",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-35",
					"fontname" : "Arial",
					"patching_rect" : [ 269.0, 84.0, 93.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Addr.",
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 141.0, 72.0, 41.0, 20.0 ],
					"id" : "obj-33",
					"fontname" : "Arial",
					"patching_rect" : [ 438.0, 20.0, 54.0, 20.0 ],
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-29",
					"fontname" : "Arial",
					"patching_rect" : [ 360.0, 128.0, 55.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sprintf set /ITL/scene/%s",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-25",
					"fontname" : "Arial",
					"patching_rect" : [ 463.0, 84.0, 142.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numinlets" : 1,
					"items" : [ "*", ",", "rect", ",", "rond" ],
					"numoutlets" : 3,
					"presentation_rect" : [ 188.0, 72.0, 60.0, 20.0 ],
					"outlettype" : [ "int", "", "" ],
					"id" : "obj-23",
					"fontname" : "Arial",
					"types" : [  ],
					"patching_rect" : [ 441.0, 46.0, 60.0, 20.0 ],
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Y Origin",
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 141.0, 41.0, 54.0, 20.0 ],
					"id" : "obj-22",
					"fontname" : "Arial",
					"patching_rect" : [ 366.0, 20.0, 54.0, 20.0 ],
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "X Origin",
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 141.0, 18.0, 54.0, 20.0 ],
					"id" : "obj-21",
					"fontname" : "Arial",
					"patching_rect" : [ 301.0, 20.0, 54.0, 20.0 ],
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s interact",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-20",
					"fontname" : "Arial",
					"patching_rect" : [ 360.0, 157.0, 59.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numinlets" : 1,
					"items" : [ -1.0, ",", 0.0, ",", 1.0 ],
					"numoutlets" : 3,
					"presentation_rect" : [ 202.0, 41.0, 45.0, 20.0 ],
					"outlettype" : [ "int", "", "" ],
					"id" : "obj-17",
					"fontname" : "Arial",
					"types" : [  ],
					"patching_rect" : [ 370.0, 47.0, 45.0, 20.0 ],
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "umenu",
					"numinlets" : 1,
					"items" : [ -1.0, ",", 0.0, ",", 1.0 ],
					"numoutlets" : 3,
					"presentation_rect" : [ 202.0, 19.0, 45.0, 20.0 ],
					"outlettype" : [ "int", "", "" ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"types" : [  ],
					"patching_rect" : [ 304.0, 47.0, 45.0, 20.0 ],
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"presentation_rect" : [ 186.0, 112.0, 16.0, 16.0 ],
					"outlettype" : [ "int" ],
					"id" : "obj-7",
					"patching_rect" : [ 123.0, 128.0, 20.0, 20.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "*~ 0.1",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"id" : "obj-11",
					"fontname" : "Arial",
					"patching_rect" : [ 156.0, 119.0, 42.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"presentation_rect" : [ 142.0, 101.0, 37.0, 37.0 ],
					"id" : "obj-10",
					"patching_rect" : [ 143.0, 161.0, 45.0, 45.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL rootPath",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-19",
					"fontname" : "Arial",
					"patching_rect" : [ 369.0, 393.0, 127.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "int" ],
					"id" : "obj-36",
					"fontname" : "Arial",
					"patching_rect" : [ 369.0, 368.0, 139.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL load interact.interlude",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"patching_rect" : [ 285.0, 334.0, 149.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-4",
					"fontname" : "Arial",
					"patching_rect" : [ 432.0, 318.0, 34.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"patching_rect" : [ 432.0, 343.0, 69.0, 20.0 ],
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
					"id" : "obj-32",
					"fontname" : "Arial",
					"patching_rect" : [ 417.0, 260.0, 91.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "reload",
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 34.0, 120.0, 43.0, 18.0 ],
					"id" : "obj-46",
					"fontname" : "Arial",
					"patching_rect" : [ 279.0, 282.0, 41.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"presentation_rect" : [ 86.0, 117.0, 20.0, 20.0 ],
					"outlettype" : [ "bang" ],
					"id" : "obj-45",
					"patching_rect" : [ 286.0, 256.0, 20.0, 20.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s interact",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-38",
					"fontname" : "Arial",
					"patching_rect" : [ 301.0, 414.0, 59.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "bang", "bang" ],
					"id" : "obj-6",
					"fontname" : "Arial",
					"patching_rect" : [ 325.0, 285.0, 59.5, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-28",
					"fontname" : "Arial",
					"patching_rect" : [ 325.0, 256.0, 60.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-31",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 271.0, 250.0, 251.0, 197.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-40",
					"fontname" : "Arial",
					"patching_rect" : [ 38.0, 260.0, 189.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-58",
					"fontname" : "Arial",
					"patching_rect" : [ 199.0, 301.0, 34.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r interact",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-39",
					"fontname" : "Arial",
					"patching_rect" : [ 39.0, 291.0, 57.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-72",
					"fontname" : "Arial",
					"patching_rect" : [ 39.0, 331.0, 136.0, 20.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-47",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 18.0, 249.0, 239.0, 191.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"presentation_rect" : [ 30.0, 25.0, 87.0, 87.0 ],
					"ignoreclick" : 1,
					"outlettype" : [ "int" ],
					"id" : "obj-5",
					"patching_rect" : [ 20.0, 132.0, 87.0, 87.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /button /zone",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"id" : "obj-2",
					"fontname" : "Arial",
					"patching_rect" : [ 20.0, 79.0, 111.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7100",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-1",
					"fontname" : "Arial",
					"patching_rect" : [ 20.0, 36.0, 99.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [ 508.5, 175.0, 449.0, 175.0, 449.0, 147.0, 369.5, 147.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [ 671.5, 120.0, 508.5, 120.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [ 374.5, 115.0, 369.5, 115.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [ 392.5, 74.5, 374.5, 74.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [ 278.5, 115.5, 369.5, 115.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 1 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 326.5, 75.0, 278.5, 75.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [ 472.5, 115.5, 369.5, 115.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 1 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [ 294.5, 403.0, 310.5, 403.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [ 378.5, 414.0, 348.0, 414.0, 348.0, 411.0, 310.5, 411.0 ]
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
					"source" : [ "obj-3", 1 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"midpoints" : [ 491.5, 363.0, 378.5, 363.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 3 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 375.0, 313.0, 441.5, 313.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [ 295.5, 278.0, 334.5, 278.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 2 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [ 361.5, 320.0, 294.5, 320.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 75.5, 114.5, 132.5, 114.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-10", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
