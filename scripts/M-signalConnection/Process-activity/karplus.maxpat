{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 6,
			"architecture" : "x86"
		}
,
		"openrect" : [ 55.0, 251.0, 475.0, 165.0 ],
		"bgcolor" : [ 0.8, 0.8, 0.8, 1.0 ],
		"bglocked" : 0,
		"openinpresentation" : 1,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-48",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 340.0, 24.0, 44.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 341.5, 26.0, 43.0, 20.0 ],
					"text" : "Clock"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-53",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 425.5, 361.0, 117.0, 18.0 ],
					"text" : "/ITL/scene/obj clock"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-51",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 425.5, 307.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 353.0, 46.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-50",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 425.5, 334.5, 58.0, 20.0 ],
					"text" : "metro 50"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-49",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.5, 68.0, 32.5, 18.0 ],
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-46",
					"maxclass" : "newobj",
					"numinlets" : 4,
					"numoutlets" : 4,
					"outlettype" : [ "", "", "", "" ],
					"patching_rect" : [ 48.5, 37.0, 131.0, 20.0 ],
					"text" : "route /stop /bing /clock"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-45",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 48.5, 9.0, 99.0, 20.0 ],
					"text" : "udpreceive 8000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-44",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 206.5, 63.0, 37.0, 18.0 ],
					"text" : "2000"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-43",
					"maxclass" : "number",
					"maximum" : 3000,
					"minimum" : 250,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 206.5, 97.0, 50.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 95.5, 17.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"frgb" : 0.0,
					"id" : "obj-42",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 68.5, 362.0, 44.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 404.0, 26.0, 43.0, 20.0 ],
					"text" : "Audio"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-41",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 264.0, 84.0, 60.0, 20.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-39",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 440.0, 117.0, 32.5, 18.0 ],
					"text" : "45"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-27",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 396.0, 117.0, 32.5, 18.0 ],
					"text" : "0.9"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-26",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 342.0, 117.0, 41.0, 18.0 ],
					"text" : "0.008"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-24",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 300.0, 117.0, 32.5, 18.0 ],
					"text" : "250"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-23",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 264.0, 117.0, 32.5, 18.0 ],
					"text" : "18"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 26.25, 270.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 415.5, 46.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-13",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 26.25, 243.0, 60.0, 20.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-40",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 160.5, 97.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 75.5, 17.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-36",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 160.5, 124.0, 41.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 75.5, 46.0, 41.0, 20.0 ],
					"text" : "metro"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-35",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 20.0, 84.0, 20.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 32.0, 17.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-33",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 20.0, 147.0, 32.5, 18.0 ],
					"text" : "1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-32",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 59.0, 147.0, 32.5, 18.0 ],
					"text" : "0"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-31",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 59.0, 117.0, 63.0, 20.0 ],
					"text" : "delay 200"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-29",
					"maxclass" : "number",
					"maximum" : 512,
					"minimum" : 0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 468.0, 165.0, 50.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 383.0, 85.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-30",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 468.0, 213.0, 64.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 383.0, 116.0, 64.0, 18.0 ],
					"text" : "detune $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-25",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 287.0, 398.5, 35.0, 20.0 ],
					"text" : "s sig"
				}

			}
, 			{
				"box" : 				{
					"fontface" : 1,
					"fontname" : "Arial",
					"fontsize" : 14.0,
					"frgb" : 0.0,
					"id" : "obj-19",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 48.5, 396.0, 160.0, 22.0 ],
					"text" : "OSC communication"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-20",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 111.5, 424.0, 34.0, 20.0 ],
					"text" : "print"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-21",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 164.0, 524.0, 55.0, 20.0 ],
					"text" : "print ITL"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-22",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 60.5, 524.0, 74.0, 20.0 ],
					"text" : "print ITLOut"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-28",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 164.0, 493.0, 99.0, 20.0 ],
					"text" : "udpreceive 7002"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 60.5, 491.0, 99.0, 20.0 ],
					"text" : "udpreceive 7001"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-37",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 60.5, 424.0, 33.0, 20.0 ],
					"text" : "r sig"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 11.595187,
					"id" : "obj-38",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 60.5, 464.0, 136.0, 19.0 ],
					"text" : "udpsend 127.0.0.1 7000"
				}

			}
, 			{
				"box" : 				{
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"id" : "obj-47",
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 48.5, 396.0, 223.0, 159.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-18",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 287.0, 362.0, 68.0, 18.0 ],
					"text" : "/target1 $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-17",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : -1.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 222.0, 362.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 222.0, 270.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-15",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "float" ],
					"patching_rect" : [ 222.0, 319.5, 83.0, 20.0 ],
					"text" : "snapshot~ 20"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-4",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 392.0, 165.0, 50.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 307.0, 85.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 392.0, 213.0, 66.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 307.0, 116.0, 66.0, 18.0 ],
					"text" : "volume $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-12",
					"maxclass" : "flonum",
					"maximum" : 1.0,
					"minimum" : 0.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 296.0, 165.0, 50.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 211.0, 85.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-11",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 296.0, 213.0, 87.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 211.0, 116.0, 87.0, 18.0 ],
					"text" : "attenuation $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-10",
					"maxclass" : "number",
					"maximum" : 512,
					"minimum" : 2,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 210.0, 165.0, 50.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 125.0, 85.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-9",
					"maxclass" : "number",
					"maximum" : 32,
					"minimum" : 1,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "int", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 117.0, 165.0, 50.0, 20.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 32.0, 85.0, 50.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 210.0, 213.0, 71.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 125.0, 116.0, 71.0, 18.0 ],
					"text" : "duration $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 117.0, 213.0, 82.0, 18.0 ],
					"presentation" : 1,
					"presentation_rect" : [ 32.0, 116.0, 82.0, 18.0 ],
					"text" : "polyphony $1"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-7",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 59.0, 213.0, 49.0, 18.0 ],
					"text" : "play $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 59.0, 180.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 68.5, 307.0, 45.0, 45.0 ]
				}

			}
, 			{
				"box" : 				{
					"bitcode" : "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",
					"bitcode_size" : 20120,
					"color" : [ 1.0, 0.0, 0.0, 1.0 ],
					"compile_options" : [ "-double", "-svg" ],
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "signal", "signal" ],
					"patching_rect" : [ 59.0, 263.0, 106.0, 20.0 ],
					"sourcecode" : "declare name \t\t\"karplus32\";\ndeclare version \t\"1.0\";\ndeclare author \t\t\"Grame\";\ndeclare license \t\"BSD\";\ndeclare copyright \t\"(c)GRAME 2006\";\n\n\n//-----------------------------------------------\n// \t\t\t\tkarplus-strong\n//\t\twith 32 resonators in parallel\n//-----------------------------------------------\n\nimport(\"music.lib\"); \n\n\n// Excitator\n//--------\n\nupfront(x) \t= (x-x') > 0.0;\ndecay(n,x)\t= x - (x>0)/n;\nrelease(n)\t= + ~ decay(n);\ntrigger(n) \t= upfront : release(n) : >(0.0) : +(leak);\nleak \t\t= 1.0/65536.0;\n\nsize \t\t= hslider(\"excitation\", 128, 2, 512, 1);\n\n\n\n\n// Resonator\n//-----------------\n\ndur \t\t= hslider(\"duration\", 128, 2, 512, 1);\natt \t\t= hslider(\"attenuation\", 0.1, 0, 1, 0.01);\naverage(x)\t= (x+x')/2;\n\nresonator(d, a) = (+ : delay(4096, d-1.5)) ~ (average : *(1.0-a)) ;\n\n\n// Polyphony\n//-----------------\n\ndetune \t\t= hslider(\"detune\", 32, 0, 512, 1);\npolyphony \t= hslider(\"polyphony\", 1, 0, 32, 1);\n\n\n\noutput \t\t= hslider(\"volume\", 0.5, 0, 1, 0.1);\n\n\nprocess =  vgroup(\"karplus32\",\n\t \t\t   \tvgroup(\"noise generator\", noise * hslider(\"level\", 0.5, 0, 1, 0.1))\n\t\t\t\t : vgroup(\"excitator\", *(button(\"play\"): trigger(size)))\n\t\t\t\t<: vgroup(\"resonator x32\", par(i,32, resonator(dur+i*detune, att) * (polyphony > i)))\n\t\t\t\t:> *(output),*(output)\n\t\t\t);\n",
					"sourcecode_size" : 1249,
					"text" : "faustgen~ karplus",
					"varname" : "faustgen-623f220",
					"version" : "0.87b"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-8", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-11", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-11", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-13", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-3", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-15", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-15", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-16", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-18", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-23", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-27", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-21", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-28", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-30", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-32", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-31", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-32", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-6", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-22", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-35", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-36", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-38", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-37", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-39", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-40", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-23", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-24", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-26", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-27", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-39", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-44", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-41", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-36", 1 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-43", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-43", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-44", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-46", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-45", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-35", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-46", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-49", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-46", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-51", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-46", 2 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-40", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-49", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-53", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-50", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-50", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-51", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-53", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-7", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"dependency_cache" : [ 			{
				"name" : "faustgen~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}
