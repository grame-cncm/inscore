{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 54.0, 613.0, 738.0, 449.0 ],
		"bglocked" : 0,
		"defrect" : [ 54.0, 613.0, 738.0, 449.0 ],
		"openrect" : [ 271.0, 46.0, 218.0, 146.0 ],
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
					"maxclass" : "gswitch2",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-30",
					"patching_rect" : [ 379.0, 261.0, 39.0, 32.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 727.0, 170.0, 0.0, 0.0 ],
					"id" : "obj-24",
					"patching_rect" : [ 727.0, 170.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-22",
					"fontname" : "Arial",
					"patching_rect" : [ 894.0, 171.0, 33.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Tempo map",
					"numoutlets" : 0,
					"presentation_rect" : [ 127.0, 36.0, 87.0, 23.0 ],
					"id" : "obj-20",
					"fontname" : "Arial",
					"patching_rect" : [ 751.0, 57.0, 89.0, 23.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 148.0, 83.0, 45.0, 18.0 ],
					"id" : "obj-17",
					"fontname" : "Arial",
					"patching_rect" : [ 849.0, 171.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _tempo",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-29",
					"fontname" : "Arial",
					"patching_rect" : [ 586.0, 130.0, 58.0, 20.0 ],
					"numinlets" : 0,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-27",
					"patching_rect" : [ 751.0, 113.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend read",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-26",
					"fontname" : "Arial",
					"patching_rect" : [ 751.0, 170.0, 82.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 148.0, 62.0, 45.0, 18.0 ],
					"id" : "obj-23",
					"fontname" : "Arial",
					"patching_rect" : [ 751.0, 86.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "opendialog",
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"id" : "obj-21",
					"fontname" : "Arial",
					"patching_rect" : [ 751.0, 141.0, 69.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "qlist",
					"numoutlets" : 3,
					"outlettype" : [ "", "bang", "bang" ],
					"id" : "obj-11",
					"fontname" : "Arial",
					"patching_rect" : [ 751.0, 205.0, 46.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"save" : [ "#N", "qlist", ";", "#X", "insert", 0, "_tempo", "tempo", 51.019566, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 0, 32, ";", ";", "#X", "insert", 2490, "_tempo", "tempo", 60.227592, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 17, 32, ";", ";", "#X", "insert", 2090, "_tempo", "tempo", 54.717697, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 17, 16, ";", ";", "#X", "insert", 2090, "_tempo", "tempo", 52.645256, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 49, 32, ";", ";", "#X", "insert", 2270, "_tempo", "tempo", 61.174942, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 65, 32, ";", ";", "#X", "insert", 1950, "_tempo", "tempo", 60.28109, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 81, 32, ";", ";", "#X", "insert", 2040, "_tempo", "tempo", 48.105816, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 97, 32, ";", ";", "#X", "insert", 2350, "_tempo", "tempo", 67.934601, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 7, 2, ";", ";", "#X", "insert", 1790, "_tempo", "tempo", 63.19656, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 4, 1, ";", ";", "#X", "insert", 1880, "_tempo", "tempo", 60.440929, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 9, 2, ";", ";", "#X", "insert", 2020, "_tempo", "tempo", 53.341709, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 161, 32, ";", ";", "#X", "insert", 2130, "_tempo", "tempo", 77.184509, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 11, 2, ";", ";", "#X", "insert", 1610, "_tempo", "tempo", 55.915646, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 6, 1, ";", ";", "#X", "insert", 2110, "_tempo", "tempo", 58.277626, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 13, 2, ";", ";", "#X", "insert", 2040, "_tempo", "tempo", 63.131084, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 7, 1, ";", ";", "#X", "insert", 1880, "_tempo", "tempo", 63.027519, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 15, 2, ";", ";", "#X", "insert", 1950, "_tempo", "tempo", 56.073677, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 8, 1, ";", ";", "#X", "insert", 2210, "_tempo", "tempo", 59.153622, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 273, 32, ";", ";", "#X", "insert", 2040, "_tempo", "tempo", 58.937092, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 289, 32, ";", ";", "#X", "insert", 1950, "_tempo", "tempo", 52.604584, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 19, 2, ";", ";", "#X", "insert", 2260, "_tempo", "tempo", 63.237576, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 10, 1, ";", ";", "#X", "insert", 1950, "_tempo", "tempo", 59.692738, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 21, 2, ";", ";", "#X", "insert", 1990, "_tempo", "tempo", 63.227962, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 11, 1, ";", ";", "#X", "insert", 1910, "_tempo", "tempo", 62.061665, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 23, 2, ";", ";", "#X", "insert", 3850, "_tempo", "tempo", 63.011505, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 25, 2, ";", ";", "#X", "insert", 2020, "_tempo", "tempo", 59.427177, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 417, 32, ";", ";", "#X", "insert", 1980, "_tempo", "tempo", 64.011406, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 433, 32, ";", ";", "#X", "insert", 1900, "_tempo", "tempo", 58.59, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 449, 32, ";", ";", "#X", "insert", 2000, "_tempo", "tempo", 67.617882, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 465, 32, ";", ";", "#X", "insert", 1830, "_tempo", "tempo", 61.588818, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 481, 32, ";", ";", "#X", "insert", 1950, "_tempo", "tempo", 53.462257, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 497, 32, ";", ";", "#X", "insert", 2230, "_tempo", "tempo", 52.817753, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 513, 32, ";", ";", "#X", "insert", 2140, "_tempo", "tempo", 56.302444, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 33, 2, ";", ";", "#X", "insert", 2110, "_tempo", "tempo", 54.56929, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 17, 1, ";", ";", "#X", "insert", 2230, "_tempo", "tempo", 65.387138, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 35, 2, ";", ";", "#X", "insert", 1860, "_tempo", "tempo", 55.850506, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 18, 1, ";", ";", "#X", "insert", 2110, "_tempo", "tempo", 62.644981, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 37, 2, ";", ";", "#X", "insert", 1950, "_tempo", "tempo", 50.208023, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 19, 1, ";", ";", "#X", "insert", 2300, "_tempo", "tempo", 81.661438, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 39, 2, ";", ";", "#X", "insert", 1560, "_tempo", "tempo", 60.288979, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 641, 32, ";", ";", "#X", "insert", 3920, "_tempo", "tempo", 56.393253, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 21, 1, ";", ";", "#X", "insert", 2090, "_tempo", "tempo", 63.437523, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 43, 2, ";", ";", "#X", "insert", 1930, "_tempo", "tempo", 61.731709, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 22, 1, ";", ";", "#X", "insert", 1880, "_tempo", "tempo", 60.650444, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 45, 2, ";", ";", "#X", "insert", 2040, "_tempo", "tempo", 64.16153, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 23, 1, ";", ";", "#X", "insert", 1810, "_tempo", "tempo", 57.931026, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 47, 2, ";", ";", "#X", "insert", 2160, "_tempo", "tempo", 54.906979, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 24, 1, ";", ";", "#X", "insert", 2070, "_tempo", "tempo", 57.974049, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 49, 2, ";", ";", "#X", "insert", 4180, "_tempo", "tempo", 60.181492, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 51, 2, ";", ";", "#X", "insert", 2020, "_tempo", "tempo", 56.804157, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 26, 1, ";", ";", "#X", "insert", 2020, "_tempo", "tempo", 68.672218, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 847, 32, ";", ";", "#X", "insert", 1810, "_tempo", "tempo", 57.31197, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 27, 1, ";", ";", "#X", "insert", 2070, "_tempo", "tempo", 56.918282, ";", ";", "#X", "insert", 0, "itl", "/ITL/scene/cursor", "date", 55, 2, ";", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"patching_rect" : [ 481.0, 99.0, 48.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-82",
					"fontname" : "Arial",
					"patching_rect" : [ 337.0, 104.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open sound file",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 16.0, 33.0, 92.0, 18.0 ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"patching_rect" : [ 337.0, 73.0, 92.0, 18.0 ],
					"numinlets" : 2,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "if $f1 >= 0 then $f1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-78",
					"fontname" : "Arial",
					"patching_rect" : [ 63.0, 352.0, 111.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s player",
					"numoutlets" : 0,
					"id" : "obj-75",
					"fontname" : "Arial",
					"patching_rect" : [ 63.0, 443.0, 53.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend seek",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-76",
					"fontname" : "Arial",
					"patching_rect" : [ 63.0, 413.0, 83.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "* 4000.",
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"id" : "obj-74",
					"fontname" : "Arial",
					"patching_rect" : [ 63.0, 381.0, 49.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "/ 1.",
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"id" : "obj-66",
					"fontname" : "Arial",
					"patching_rect" : [ 63.0, 323.0, 32.5, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "unpack 1 2",
					"numoutlets" : 2,
					"outlettype" : [ "int", "int" ],
					"id" : "obj-65",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 288.0, 69.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /date /play",
					"numoutlets" : 3,
					"outlettype" : [ "", "", "" ],
					"id" : "obj-35",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 216.0, 97.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7100",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-64",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 185.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "DSP Status",
					"linecount" : 2,
					"numoutlets" : 0,
					"presentation_rect" : [ 150.0, 120.0, 61.0, 18.0 ],
					"id" : "obj-68",
					"fontname" : "Arial",
					"patching_rect" : [ 681.0, 337.0, 41.0, 29.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 127.0, 119.0, 20.0, 20.0 ],
					"id" : "obj-70",
					"patching_rect" : [ 688.0, 311.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"presentation_rect" : [ 29.0, 121.0, 15.0, 15.0 ],
					"id" : "obj-333",
					"patching_rect" : [ 677.0, 428.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Full screen",
					"numoutlets" : 0,
					"presentation_rect" : [ 48.0, 118.0, 68.0, 20.0 ],
					"id" : "obj-328",
					"fontname" : "Arial",
					"patching_rect" : [ 603.0, 429.0, 69.0, 20.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene fullscreen $1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-67",
					"fontname" : "Arial",
					"patching_rect" : [ 599.0, 455.0, 138.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s itl",
					"numoutlets" : 0,
					"id" : "obj-69",
					"fontname" : "Arial",
					"patching_rect" : [ 599.0, 477.0, 28.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Déplacement dans la partition",
					"numoutlets" : 0,
					"id" : "obj-56",
					"fontname" : "Arial",
					"patching_rect" : [ 27.0, 474.0, 210.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Audio",
					"numoutlets" : 0,
					"id" : "obj-53",
					"fontname" : "Arial",
					"patching_rect" : [ 230.0, 65.0, 55.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Messages clock",
					"numoutlets" : 0,
					"id" : "obj-52",
					"fontname" : "Arial",
					"patching_rect" : [ 551.0, 66.0, 171.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "divers",
					"numoutlets" : 0,
					"id" : "obj-49",
					"fontname" : "Arial",
					"patching_rect" : [ 601.0, 318.0, 59.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Communication avec OSC",
					"numoutlets" : 0,
					"id" : "obj-40",
					"fontname" : "Arial",
					"patching_rect" : [ 264.0, 317.0, 189.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print",
					"numoutlets" : 0,
					"id" : "obj-58",
					"fontname" : "Arial",
					"patching_rect" : [ 502.0, 366.0, 34.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print ITL",
					"numoutlets" : 0,
					"id" : "obj-41",
					"fontname" : "Arial",
					"patching_rect" : [ 442.0, 459.0, 55.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print ITLOut",
					"numoutlets" : 0,
					"id" : "obj-42",
					"fontname" : "Arial",
					"patching_rect" : [ 302.0, 458.0, 74.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7002",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-43",
					"fontname" : "Arial",
					"patching_rect" : [ 442.0, 428.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7001",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-44",
					"fontname" : "Arial",
					"patching_rect" : [ 302.0, 425.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r itl",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-39",
					"fontname" : "Arial",
					"patching_rect" : [ 302.0, 347.0, 26.0, 20.0 ],
					"numinlets" : 0,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"numoutlets" : 0,
					"id" : "obj-72",
					"fontname" : "Arial",
					"patching_rect" : [ 302.0, 387.0, 136.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "ON/OFF",
					"numoutlets" : 0,
					"presentation_rect" : [ 16.0, 67.0, 50.0, 18.0 ],
					"id" : "obj-25",
					"fontname" : "Arial",
					"patching_rect" : [ 460.0, 46.0, 53.0, 18.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "INScore player",
					"numoutlets" : 0,
					"presentation_rect" : [ 14.0, 2.0, 161.0, 27.0 ],
					"id" : "obj-15",
					"fontname" : "Arial",
					"patching_rect" : [ 21.0, 16.0, 236.0, 27.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/cursor date 0 1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-18",
					"fontname" : "Arial",
					"patching_rect" : [ 569.0, 101.0, 150.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/cursor clock",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-16",
					"fontname" : "Arial",
					"patching_rect" : [ 558.0, 196.0, 134.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s itl",
					"numoutlets" : 0,
					"id" : "obj-13",
					"fontname" : "Arial",
					"patching_rect" : [ 558.0, 223.0, 28.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "tempo 60 1 96",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"id" : "obj-1",
					"fontname" : "Arial",
					"patching_rect" : [ 558.0, 170.0, 87.0, 20.0 ],
					"numinlets" : 4,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "meter~",
					"numoutlets" : 1,
					"dbperled" : 6,
					"outlettype" : [ "float" ],
					"presentation_rect" : [ 57.0, 91.0, 80.0, 13.0 ],
					"id" : "obj-7",
					"patching_rect" : [ 241.0, 186.0, 80.0, 13.0 ],
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"presentation_rect" : [ 27.0, 86.0, 20.0, 20.0 ],
					"id" : "obj-14",
					"patching_rect" : [ 463.0, 71.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r player",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-12",
					"fontname" : "Arial",
					"patching_rect" : [ 353.0, 172.0, 51.0, 20.0 ],
					"numinlets" : 0,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-2",
					"fontname" : "Arial",
					"patching_rect" : [ 617.0, 373.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "adc~",
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"patching_rect" : [ 617.0, 398.0, 39.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "ezdac~",
					"numoutlets" : 0,
					"id" : "obj-4",
					"patching_rect" : [ 338.0, 260.0, 33.0, 33.0 ],
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "resume",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-5",
					"fontname" : "Arial",
					"patching_rect" : [ 230.0, 124.0, 52.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "pause",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-6",
					"fontname" : "Arial",
					"patching_rect" : [ 230.0, 97.0, 41.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sfplay~",
					"numoutlets" : 2,
					"outlettype" : [ "signal", "bang" ],
					"id" : "obj-10",
					"fontname" : "Arial",
					"patching_rect" : [ 335.0, 212.0, 49.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0,
					"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-47",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 249.0, 307.0, 335.0, 193.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-48",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 591.0, 307.0, 151.0, 193.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-51",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 539.0, 61.0, 190.0, 187.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-54",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 217.0, 52.0, 221.0, 245.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-55",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 16.0, 281.0, 219.0, 221.0 ],
					"numinlets" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-30", 1 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [ 408.5, 302.0, 440.5, 302.0, 440.5, 61.0, 472.5, 61.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-30", 0 ],
					"hidden" : 0,
					"midpoints" : [ 472.5, 251.5, 388.5, 251.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 1 ],
					"destination" : [ "obj-30", 1 ],
					"hidden" : 0,
					"midpoints" : [ 374.5, 241.0, 408.5, 241.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [ 903.5, 196.5, 760.5, 196.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 1 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [ 519.5, 135.5, 903.5, 135.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [ 736.5, 197.0, 760.5, 197.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [ 490.5, 130.0, 736.5, 130.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [ 858.5, 201.0, 760.5, 201.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-16", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-4", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 344.5, 240.0, 236.0, 240.0, 236.0, 183.0, 250.5, 183.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 362.5, 192.0, 344.5, 192.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [ 472.5, 138.0, 567.5, 138.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 472.5, 207.0, 344.5, 207.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 472.5, 246.0, 347.5, 246.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [ 472.5, 93.0, 490.5, 93.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [ 578.5, 147.0, 551.0, 147.0, 551.0, 219.0, 567.5, 219.0 ]
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
					"source" : [ "obj-333", 0 ],
					"destination" : [ "obj-67", 0 ],
					"hidden" : 0,
					"midpoints" : [ 686.5, 449.0, 608.5, 449.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 1 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [ 94.5, 244.0, 183.5, 244.0, 183.5, 61.0, 472.5, 61.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-65", 0 ],
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
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"midpoints" : [ 239.5, 171.0, 339.0, 171.0, 339.0, 207.0, 344.5, 207.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 1,
					"midpoints" : [ 239.5, 117.0, 339.0, 117.0, 339.0, 207.0, 344.5, 207.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 1 ],
					"destination" : [ "obj-66", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-65", 0 ],
					"destination" : [ "obj-66", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-66", 0 ],
					"destination" : [ "obj-78", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-67", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [ 697.5, 332.0, 662.0, 332.0, 662.0, 344.0, 596.0, 344.0, 596.0, 371.0, 626.5, 371.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-76", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-76", 0 ],
					"destination" : [ "obj-75", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-78", 0 ],
					"destination" : [ "obj-74", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-82", 0 ],
					"hidden" : 0,
					"midpoints" : [ 346.5, 97.0, 346.5, 97.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-82", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [ 490.5, 128.0, 534.5, 128.0, 534.5, 91.0, 578.5, 91.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-27", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-23", 0 ],
					"destination" : [ "obj-27", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-26", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
