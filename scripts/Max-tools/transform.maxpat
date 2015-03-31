{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 277.0, 105.0, 1100.0, 529.0 ],
		"bglocked" : 0,
		"defrect" : [ 277.0, 105.0, 1100.0, 529.0 ],
		"openrect" : [ 277.0, 105.0, 230.0, 222.0 ],
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
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 719.0, 124.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-2"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 429.0, -3.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-64",
					"presentation_rect" : [ 191.0, 5.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "100",
					"numinlets" : 2,
					"patching_rect" : [ 426.0, 22.0, 32.5, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-60",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 361.0, 218.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-55"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 50.",
					"numinlets" : 2,
					"patching_rect" : [ 382.0, 182.0, 34.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"id" : "obj-54",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 50.",
					"numinlets" : 2,
					"patching_rect" : [ 344.0, 183.0, 34.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"id" : "obj-53",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "pack 0. 0.",
					"numinlets" : 2,
					"patching_rect" : [ 344.0, 244.0, 63.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-52",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "shear $1 $2",
					"numinlets" : 2,
					"patching_rect" : [ 344.0, 273.0, 74.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-50",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rotatez $1",
					"numinlets" : 2,
					"patching_rect" : [ 236.0, 192.0, 64.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-48",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "y",
					"numinlets" : 1,
					"patching_rect" : [ 377.0, 36.0, 18.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-35",
					"fontname" : "Arial",
					"presentation_rect" : [ 179.0, 32.0, 21.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"size" : 200.0,
					"patching_rect" : [ 376.0, 60.0, 20.0, 108.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"min" : -100.0,
					"outlettype" : [ "" ],
					"id" : "obj-37",
					"orientation" : 2,
					"floatoutput" : 1,
					"presentation_rect" : [ 178.0, 56.0, 20.0, 86.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "x",
					"numinlets" : 1,
					"patching_rect" : [ 346.0, 36.0, 18.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-45",
					"fontname" : "Arial",
					"presentation_rect" : [ 148.0, 32.0, 23.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"size" : 200.0,
					"patching_rect" : [ 345.0, 60.0, 20.0, 108.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"min" : -100.0,
					"outlettype" : [ "" ],
					"id" : "obj-46",
					"orientation" : 2,
					"floatoutput" : 1,
					"presentation_rect" : [ 147.0, 56.0, 20.0, 86.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"bgcolor" : [ 0.992157, 0.905882, 0.65098, 1.0 ],
					"patching_rect" : [ 331.0, 31.0, 84.0, 146.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"rounded" : 24,
					"id" : "obj-47",
					"presentation_rect" : [ 132.0, 27.0, 84.0, 127.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rotatey $1",
					"numinlets" : 2,
					"patching_rect" : [ 168.0, 193.0, 64.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-28",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rotatex $1",
					"numinlets" : 2,
					"patching_rect" : [ 101.0, 193.0, 64.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-27",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "y",
					"numinlets" : 1,
					"patching_rect" : [ 173.0, 37.0, 18.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-20",
					"fontname" : "Arial",
					"presentation_rect" : [ 58.0, 32.0, 18.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"size" : 360.0,
					"patching_rect" : [ 172.0, 61.0, 20.0, 108.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-22",
					"orientation" : 2,
					"floatoutput" : 1,
					"presentation_rect" : [ 56.0, 56.0, 20.0, 90.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "x",
					"numinlets" : 1,
					"patching_rect" : [ 142.0, 37.0, 18.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-15",
					"fontname" : "Arial",
					"presentation_rect" : [ 27.0, 32.0, 18.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"size" : 360.0,
					"patching_rect" : [ 141.0, 61.0, 20.0, 108.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-16",
					"orientation" : 2,
					"floatoutput" : 1,
					"presentation_rect" : [ 26.0, 56.0, 20.0, 90.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rotatez 0.",
					"numinlets" : 2,
					"patching_rect" : [ 876.0, 195.0, 61.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-10",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rotatey 0.",
					"numinlets" : 2,
					"patching_rect" : [ 855.0, 173.0, 61.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "rotatex 0.",
					"numinlets" : 2,
					"patching_rect" : [ 841.0, 149.0, 61.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-1",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _dest",
					"numinlets" : 1,
					"patching_rect" : [ 344.0, 301.0, 49.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-63",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Shear",
					"numinlets" : 1,
					"patching_rect" : [ 346.0, 4.0, 65.0, 23.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-44",
					"fontname" : "Arial",
					"presentation_rect" : [ 132.0, 1.0, 54.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _dest",
					"numinlets" : 1,
					"patching_rect" : [ 819.0, 242.0, 49.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-42",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "shear 0. 0.",
					"numinlets" : 2,
					"patching_rect" : [ 765.0, 142.0, 67.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-41",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 818.0, 97.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-40",
					"presentation_rect" : [ 197.0, 177.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Remove transform",
					"presentation_linecount" : 2,
					"numinlets" : 1,
					"patching_rect" : [ 781.0, 69.0, 143.0, 23.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-39",
					"fontname" : "Arial",
					"presentation_rect" : [ 136.0, 172.0, 74.0, 39.0 ],
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s transform",
					"numinlets" : 1,
					"patching_rect" : [ 639.0, 267.0, 71.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-38",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "z",
					"numinlets" : 1,
					"patching_rect" : [ 203.0, 37.0, 18.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-36",
					"fontname" : "Arial",
					"presentation_rect" : [ 90.0, 32.0, 21.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _dest",
					"numinlets" : 1,
					"patching_rect" : [ 168.0, 233.0, 49.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-29",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"numinlets" : 1,
					"size" : 360.0,
					"patching_rect" : [ 202.0, 61.0, 20.0, 108.0 ],
					"numoutlets" : 1,
					"presentation" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-26",
					"orientation" : 2,
					"floatoutput" : 1,
					"presentation_rect" : [ 91.0, 56.0, 20.0, 90.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Rotate",
					"numinlets" : 1,
					"patching_rect" : [ 149.0, 4.0, 65.0, 23.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-23",
					"fontname" : "Arial",
					"presentation_rect" : [ 20.0, 1.0, 71.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sprintf /ITL/scene/%s",
					"numinlets" : 1,
					"patching_rect" : [ 639.0, 166.0, 123.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-19",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"patching_rect" : [ 598.0, 48.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-18"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _dest",
					"numinlets" : 0,
					"patching_rect" : [ 586.0, 188.0, 47.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-14",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numinlets" : 1,
					"patching_rect" : [ 530.0, 14.0, 60.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-13",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route text",
					"numinlets" : 1,
					"patching_rect" : [ 639.0, 128.0, 61.0, 20.0 ],
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"numinlets" : 1,
					"patching_rect" : [ 639.0, 196.0, 74.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /address",
					"numinlets" : 1,
					"patching_rect" : [ 639.0, 230.0, 104.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"numinlets" : 1,
					"patching_rect" : [ 36.0, 283.0, 156.0, 23.0 ],
					"numoutlets" : 0,
					"id" : "obj-11",
					"fontname" : "Arial",
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"numinlets" : 1,
					"patching_rect" : [ 234.0, 331.0, 34.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-17",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print ITL",
					"numinlets" : 1,
					"patching_rect" : [ 174.0, 424.0, 55.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-21",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print ITLOut",
					"numinlets" : 1,
					"patching_rect" : [ 34.0, 423.0, 74.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-30",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7002",
					"numinlets" : 1,
					"patching_rect" : [ 174.0, 393.0, 99.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-31",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7001",
					"numinlets" : 1,
					"patching_rect" : [ 34.0, 390.0, 99.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-34",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r transform",
					"numinlets" : 0,
					"patching_rect" : [ 34.0, 312.0, 69.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-61",
					"fontname" : "Arial",
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"numinlets" : 1,
					"patching_rect" : [ 34.0, 352.0, 136.0, 20.0 ],
					"numoutlets" : 0,
					"id" : "obj-32",
					"fontname" : "Arial",
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 21.0, 272.0, 266.0, 192.0 ],
					"numoutlets" : 0,
					"id" : "obj-62"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC dest address ",
					"numinlets" : 1,
					"patching_rect" : [ 631.0, 70.0, 117.0, 20.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"id" : "obj-49",
					"fontname" : "Arial",
					"presentation_rect" : [ 16.0, 165.0, 115.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "textedit",
					"text" : "*",
					"numinlets" : 1,
					"patching_rect" : [ 639.0, 95.0, 98.0, 21.0 ],
					"numoutlets" : 4,
					"presentation" : 1,
					"outlettype" : [ "", "int", "", "" ],
					"id" : "obj-24",
					"fontname" : "Arial",
					"lines" : 1,
					"clickmode" : 1,
					"presentation_rect" : [ 17.0, 191.0, 101.0, 19.0 ],
					"fontsize" : 11.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"bgcolor" : [ 0.992157, 0.905882, 0.65098, 1.0 ],
					"patching_rect" : [ 127.0, 32.0, 117.0, 148.0 ],
					"numoutlets" : 0,
					"presentation" : 1,
					"rounded" : 24,
					"id" : "obj-25",
					"presentation_rect" : [ 13.0, 27.0, 112.0, 127.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [ 728.5, 153.0, 747.5, 153.0, 747.5, 85.0, 648.5, 85.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 3 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-31", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-34", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-61", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 827.5, 133.0, 850.5, 133.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [ 827.5, 144.5, 864.5, 144.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 827.5, 155.5, 885.5, 155.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-28", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-48", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-50", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 0 ],
					"destination" : [ "obj-53", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-54", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-63", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [ 595.5, 219.0, 648.5, 219.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 0 ],
					"destination" : [ "obj-52", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 0 ],
					"destination" : [ "obj-52", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 0 ],
					"destination" : [ "obj-55", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-53", 0 ],
					"destination" : [ "obj-52", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-60", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-60", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
