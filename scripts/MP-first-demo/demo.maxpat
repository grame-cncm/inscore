{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 25.0, 69.0, 750.0, 597.0 ],
		"bglocked" : 0,
		"defrect" : [ 25.0, 69.0, 750.0, 597.0 ],
		"openrect" : [ 25.0, 69.0, 225.0, 145.0 ],
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
					"text" : "p rootpath",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-22",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 368.0, 503.0, 65.0, 20.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 25.0, 69.0, 312.0, 240.0 ],
						"bglocked" : 0,
						"defrect" : [ 25.0, 69.0, 312.0, 240.0 ],
						"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
						"openinpresentation" : 0,
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene rootPath",
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-3",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"patching_rect" : [ 58.0, 116.0, 163.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 36.0, 151.0, 25.0, 25.0 ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-1",
									"outlettype" : [ "" ],
									"patching_rect" : [ 36.0, 31.0, 25.0, 25.0 ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL rootPath",
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-6",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"patching_rect" : [ 36.0, 76.0, 127.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /reset /play",
					"numinlets" : 1,
					"numoutlets" : 3,
					"id" : "obj-29",
					"fontname" : "Arial",
					"outlettype" : [ "", "", "" ],
					"patching_rect" : [ 372.0, 61.0, 100.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7003",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-26",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 372.0, 26.0, 99.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene fullscreen $1",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-19",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 45.0, 92.0, 138.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s demo",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-20",
					"fontname" : "Arial",
					"patching_rect" : [ 45.0, 129.5, 50.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Full screen",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-17",
					"presentation_rect" : [ 141.0, 13.0, 59.0, 18.0 ],
					"fontname" : "Arial",
					"patching_rect" : [ 40.0, 24.0, 60.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-15",
					"presentation_rect" : [ 161.0, 31.0, 16.0, 16.0 ],
					"outlettype" : [ "int" ],
					"patching_rect" : [ 45.0, 56.0, 18.0, 18.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/slave* clock",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-6",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 33.0, 225.0, 133.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s demo",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-10",
					"fontname" : "Arial",
					"patching_rect" : [ 33.0, 262.5, 50.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "tempo 2",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-1",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 324.0, 181.0, 54.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-18",
					"fontname" : "Arial",
					"outlettype" : [ "", "int" ],
					"patching_rect" : [ 368.0, 478.0, 139.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p time",
					"color" : [ 0.72549, 0.67451, 0.67451, 1.0 ],
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-214",
					"fontname" : "Arial",
					"outlettype" : [ "int" ],
					"patching_rect" : [ 33.0, 186.0, 44.0, 20.0 ],
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 470.0, 194.0, 347.0, 215.0 ],
						"bglocked" : 0,
						"defrect" : [ 470.0, 194.0, 347.0, 215.0 ],
						"openrect" : [ 470.0, 194.0, 347.0, 215.0 ],
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
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"id" : "obj-4",
									"patching_rect" : [ 71.0, 341.0, 25.0, 25.0 ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "number",
									"numinlets" : 1,
									"numoutlets" : 2,
									"id" : "obj-2",
									"fontname" : "Arial",
									"outlettype" : [ "int", "bang" ],
									"patching_rect" : [ 165.0, 245.0, 50.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "comment",
									"text" : "The 'time' bus is used by the demo.osc qlist.",
									"linecount" : 3,
									"presentation_linecount" : 3,
									"textcolor" : [ 0.282353, 0.282353, 0.282353, 1.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"frgb" : [ 0.282353, 0.282353, 0.282353, 1.0 ],
									"id" : "obj-1",
									"presentation_rect" : [ 106.0, 73.0, 113.0, 55.0 ],
									"fontname" : "Arial",
									"patching_rect" : [ 187.0, 16.0, 104.0, 55.0 ],
									"presentation" : 1,
									"fontsize" : 14.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl slice 2",
									"numinlets" : 2,
									"numoutlets" : 2,
									"id" : "obj-67",
									"fontname" : "Arial",
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 108.0, 69.5, 57.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "zl slice 2",
									"numinlets" : 2,
									"numoutlets" : 2,
									"id" : "obj-65",
									"fontname" : "Arial",
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 71.0, 41.5, 57.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route play tempo dest",
									"numinlets" : 1,
									"numoutlets" : 4,
									"id" : "obj-58",
									"fontname" : "Arial",
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 71.0, 122.0, 126.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r demotime",
									"numinlets" : 0,
									"numoutlets" : 1,
									"id" : "obj-57",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"patching_rect" : [ 71.0, 15.5, 71.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend tempo",
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-16",
									"fontname" : "Arial",
									"outlettype" : [ "" ],
									"patching_rect" : [ 144.0, 192.0, 91.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"id" : "obj-12",
									"presentation_rect" : [ 91.0, 11.0, 20.0, 20.0 ],
									"outlettype" : [ "int" ],
									"patching_rect" : [ 72.0, 263.0, 20.0, 20.0 ],
									"presentation" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tempo 60 1 96",
									"numinlets" : 4,
									"numoutlets" : 1,
									"id" : "obj-11",
									"fontname" : "Arial",
									"outlettype" : [ "int" ],
									"patching_rect" : [ 72.0, 297.0, 87.0, 20.0 ],
									"fontsize" : 12.0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-67", 0 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [ 117.5, 109.0, 80.5, 109.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-67", 1 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [ 155.5, 109.0, 80.5, 109.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 1 ],
									"destination" : [ "obj-67", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-65", 0 ],
									"destination" : [ "obj-58", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 1 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [ 116.166664, 234.0, 174.5, 234.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 1 ],
									"destination" : [ "obj-16", 0 ],
									"hidden" : 0,
									"midpoints" : [ 116.166664, 177.0, 153.5, 177.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-58", 0 ],
									"destination" : [ "obj-12", 0 ],
									"hidden" : 0,
									"midpoints" : [ 80.5, 258.0, 81.5, 258.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-57", 0 ],
									"destination" : [ "obj-65", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-16", 0 ],
									"destination" : [ "obj-11", 1 ],
									"hidden" : 0,
									"midpoints" : [ 153.5, 282.0, 104.166664, 282.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-12", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontface" : 0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "This patch is a simple cue list that plays the \"demo.osc\" file.",
					"linecount" : 3,
					"presentation_linecount" : 4,
					"textcolor" : [ 0.282353, 0.282353, 0.282353, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"frgb" : [ 0.282353, 0.282353, 0.282353, 1.0 ],
					"id" : "obj-16",
					"presentation_rect" : [ 91.0, 58.0, 109.0, 71.0 ],
					"fontname" : "Arial",
					"patching_rect" : [ 512.0, 81.0, 183.0, 55.0 ],
					"presentation" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Play",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-14",
					"presentation_rect" : [ 28.0, 18.0, 38.0, 23.0 ],
					"fontname" : "Arial",
					"patching_rect" : [ 259.0, 29.0, 38.0, 23.0 ],
					"fontface" : 1,
					"presentation" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-2",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 229.0, 194.0, 20.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "gswitch2",
					"numinlets" : 2,
					"numoutlets" : 2,
					"id" : "obj-13",
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 229.0, 118.0, 39.0, 32.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-12",
					"presentation_rect" : [ 81.0, 20.0, 20.0, 20.0 ],
					"outlettype" : [ "int" ],
					"patching_rect" : [ 312.0, 31.0, 20.0, 20.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-11",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 249.0, 160.0, 33.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "tempo 0.8",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-9",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 447.0, 233.0, 64.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read demo.osc",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-8",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 411.0, 179.0, 90.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "qlist",
					"numinlets" : 1,
					"numoutlets" : 3,
					"id" : "obj-7",
					"fontname" : "Arial",
					"outlettype" : [ "", "bang", "bang" ],
					"patching_rect" : [ 325.0, 272.0, 46.0, 20.0 ],
					"fontsize" : 12.0,
					"save" : [ "#N", "qlist", ";", "#X", "insert", 1, "demo", "/ITL", "defaultShow", 0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene", "color", 255, 255, 255, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene", "width", 1.33, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/title", "set", "file", "rsrc/title.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/title", "x", 0.0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/title", "y", -0.66, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/title", "scale", 2.8, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/title", "show", 1, ";", ";", "#X", "insert", 1500, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.01, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.02, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.02, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.02, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.02, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.03, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.03, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.03, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.03, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "dy", -0.03, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/*", "z", 1, ";", ";", "#X", "insert", 10, "demotime", "play", 1, "tempo", 140, "dest", "*", ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/comment1", "set", "txt", "supports:", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "x", -0.686667, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "y", -0.033333, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "scale", 3.79747, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "color", 178, 42, 64, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/what", "set", "txt", "text", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "scale", 4.74, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "z", 1.0, ";", ";", "#X", "insert", 1000, "demo", "/ITL/scene/what", "set", "txt", "shapes", ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/shapeRect", "set", "rect", 0.316562, 0.325442, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeRect", "x", -0.38, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeRect", "y", 0.26, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeRect", "scale", 1.0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeRect", "color", 45, 153, 0, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeRect", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/shapeEllipse", "set", "ellipse", 0.81554, 0.629943, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeEllipse", "color", 178, 227, 255, 116, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeEllipse", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/shapeCurve", "set", "curve", 0.0001, 0.0001, 0.3, 0.0001, 0.5, 0.3, 0.0001, 0.3, 0.0001, 0.0001, 0.25, 0.0001, 0.45, 0.3, 0.0001, 0.3, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "x", 0.06, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "y", 0.1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "z", 1.826923, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "scale", 2.452, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "angle", 81.290321, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "color", 246, 0, 0, 116, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapeCurve", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/shapePolygon", "set", "polygon", 0.8, 0.9, 0.3, 1.0001, 0.44, -0.1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapePolygon", "x", 0.52, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapePolygon", "y", -0.04, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapePolygon", "color", 255, 163, 59, 116, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shapePolygon", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/what", "show", 0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "x", -0.3, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "y", 0.76, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "z", 0.5, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "set", "txt", "images", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shape*", "z", 0.5, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/img1", "set", "file", "rsrc/boucou.gif", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img1", "x", -0.679999, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img1", "y", 0.379999, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img1", "z", 0.6, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img1", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/img2", "set", "file", "rsrc/parm-oeil.jpg", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img2", "x", 0.36, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img2", "y", 0.56, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img2", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/what", "show", 0, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/imgs*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/imgs*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/imgs*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/imgs*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/shape*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene/img*", "dscale", 0.95, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "x", 0.94, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "y", 0.3, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "set", "txt", "scores", ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/what", "show", 1, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/guido", "set", "gmnf", "rsrc/1voice-846_2f.gmn", ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/guido", "z", 8.5, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/guido", "scale", 2.648, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/guido", "show", 1, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/title", "del", ";", ";", "#X", "insert", 1000, "demo", "/ITL/scene/what", "set", "txt", "Interaction", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "x", 0.9, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "y", 0.1, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/title", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/shape*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/[is]*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "dscale", 0.99, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/*", "dangle", 0.99, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "del", ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/what", "set", "txt", "Synchronization", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "scale", 4.74, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "set", "file", "rsrc/syncomment1.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "y", 0.4, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "scale", 2.1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "show", 1, ";", ";", "#X", "insert", 3500, "demo", "/ITL/scene/slave1", "set", "img", "rsrc/car_blue.gif", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/what", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "show", 0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "set", "file", "rsrc/syncomment2.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "x", -0.88, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "y", 0.08, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "scale", 1.406667, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave2", "set", "img", "rsrc/car_red.gif", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/guido", "set", "gmnf", "rsrc/1voice-846_2f.gmn", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/guido", "y", 0.1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/guido", "scale", 2.5, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave*", "scale", 0.6, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave*", "z", 2.0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave*", "duration", 1, 4, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave1", "date", 2, 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave2", "date", 4, 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/sync", "slave*", "guido", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "set", "file", "rsrc/syncomment3.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "x", 0.88, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "y", -0.2, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "scale", 1.406667, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "show", 1, ";", ";", "#X", "insert", 8000, "demo", "/ITL/scene/comment2", "set", "file", "rsrc/syncomment4.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/sync", "slave*", "guido", "hv", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment2", "x", 0.88, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment2", "y", 0.2, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment2", "scale", 1.406667, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment2", "show", 1, ";", ";", "#X", "insert", 8000, "demo", "/ITL/scene/slave*", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment*", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/guido", "z", 0.5, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 250, 250, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 240, 240, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 230, 230, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 220, 220, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 210, 210, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 200, 200, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 190, 190, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 180, 180, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 170, 170, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 160, 160, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 150, 150, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 140, 140, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 130, 130, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 120, 120, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 110, 110, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 90, 90, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 80, 80, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 70, 70, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 60, 60, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 50, 50, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 40, 40, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 30, 30, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 20, 20, 110, 255, ";", ";", "#X", "insert", 20, "demo", "/ITL/scene", "color", 10, 10, 110, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene", "color", 0, 0, 110, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave3", "set", "ellipse", 0.15, 0.15, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave3", "color", 255, 255, 135, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave3", "date", 10, 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave3", "duration", 1, 4, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave3", "z", -0.5, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/sync", "slave3", "guido", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "set", "file", "rsrc/syncomment5.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "color", 255, 255, 135, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "x", -0.88, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "y", 0.08, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "scale", 2.1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "show", 1, ";", ";", "#X", "insert", 4000, "demo", "/ITL/scene", "color", 255, 255, 255, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene", "color", 255, 255, 255, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "set", "file", "rsrc/syncomment6.txt", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "mapf", "rsrc/syncomment6.map", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "scale", 4.2, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "duration", 1, 4, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "z", 0.5, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "set", "ellipse", 0.7, 0.7, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "z", 0.4, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "color", 0, 221, 0, 120, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "date", 0, 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "duration", 1, 4, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/sync", "slave", "comment", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "show", 1, ";", ";", "#X", "insert", 4000, "demo", "/ITL/scene/img", "set", "file", "rsrc/parm-oeil.jpg", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "del", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img", "scale", 1.2, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/img", "mapf", "rsrc/parm-oeil.map", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slavecomment", "set", "txtf", "rsrc/syncomment7.txt", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slavecomment", "scale", 3.1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slavecomment", "color", 240, 0, 0, 255, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slavecomment", "mapf", "rsrc/syncomment7.map", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/*", "date", 0, 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slavecomment", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/sync", "slavecomment", "img", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/sync", "slave", "slavecomment", ";", ";", "#X", "insert", 3001, "demo", "/ITL/scene/comment1", "set", "txtf", "rsrc/syncomment8.txt", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "scale", 2.648, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "x", 0.04, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "y", 0.54, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "z", 0.730769, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment1", "show", 1, ";", ";", "#X", "insert", 500, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "color", 240, 0, 0, 120, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "color", 0, 221, 0, 255, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", -0.3, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/slave", "color", 250, 200, 0, 120, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/comment", "color", 0, 0, 240, 255, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 10, "demo", "/ITL/scene/img", "dangle", 0.3, ";", ";", "#X", "insert", 2010, "demo", "/ITL/scene/*", "del", ";", ";", "#X", "insert", 1, "demotime", "play", 0, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/itl", "set", "htmlf", "rsrc/interlude.html", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/itl", "scale", 1.864, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/itl", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/anr", "set", "file", "rsrc/anr.gif", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/anr", "scale", 0.818667, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/anr", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/anr", "x", 0.44, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/anr", "y", 0.46, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/grame", "set", "file", "rsrc/grame.png", ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/grame", "scale", 1.668, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/grame", "show", 1, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/grame", "x", -0.38, ";", ";", "#X", "insert", 1, "demo", "/ITL/scene/grame", "y", 0.44, ";", ";", "#X", "insert", 1, "demo", "/ITL", "defaultShow", 1, ";", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"numinlets" : 2,
					"numoutlets" : 1,
					"id" : "obj-4",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 368.0, 429.0, 34.0, 18.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"numinlets" : 1,
					"numoutlets" : 2,
					"id" : "obj-5",
					"fontname" : "Arial",
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 368.0, 452.0, 69.0, 20.0 ],
					"fontsize" : 12.0,
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Initialisation",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-32",
					"fontname" : "Arial",
					"patching_rect" : [ 419.0, 367.0, 91.0, 23.0 ],
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
					"id" : "obj-46",
					"presentation_rect" : [ 29.0, 106.0, 43.0, 18.0 ],
					"fontname" : "Arial",
					"patching_rect" : [ 281.0, 389.0, 41.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 10.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-45",
					"presentation_rect" : [ 35.0, 83.0, 20.0, 20.0 ],
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 288.0, 363.0, 20.0, 20.0 ],
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s demo",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-38",
					"fontname" : "Arial",
					"patching_rect" : [ 368.0, 527.0, 50.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"numinlets" : 1,
					"numoutlets" : 4,
					"id" : "obj-3",
					"fontname" : "Arial",
					"outlettype" : [ "bang", "bang", "bang", "bang" ],
					"patching_rect" : [ 327.0, 392.0, 59.5, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-28",
					"fontname" : "Arial",
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 327.0, 363.0, 60.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-31",
					"patching_rect" : [ 273.0, 357.0, 250.0, 192.0 ]
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
					"patching_rect" : [ 40.0, 367.0, 189.0, 23.0 ],
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
					"patching_rect" : [ 201.0, 408.0, 34.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print ITL",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-41",
					"fontname" : "Arial",
					"patching_rect" : [ 148.0, 509.0, 55.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print ITLOut",
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-42",
					"fontname" : "Arial",
					"patching_rect" : [ 41.0, 509.0, 74.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7002",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-43",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 148.0, 478.0, 99.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7001",
					"numinlets" : 1,
					"numoutlets" : 1,
					"id" : "obj-44",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 41.0, 476.0, 99.0, 20.0 ],
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r demo",
					"numinlets" : 0,
					"numoutlets" : 1,
					"id" : "obj-39",
					"fontname" : "Arial",
					"outlettype" : [ "" ],
					"patching_rect" : [ 41.0, 398.0, 48.0, 20.0 ],
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
					"patching_rect" : [ 41.0, 438.0, 136.0, 20.0 ],
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0,
					"id" : "obj-47",
					"patching_rect" : [ 25.0, 357.0, 239.0, 191.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 456.5, 264.0, 334.5, 264.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 420.5, 252.0, 334.5, 252.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 1 ],
					"destination" : [ "obj-12", 0 ],
					"hidden" : 0,
					"midpoints" : [ 348.0, 303.0, 309.0, 303.0, 309.0, 27.0, 321.5, 27.0 ]
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
					"source" : [ "obj-5", 1 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [ 427.5, 475.0, 377.5, 475.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [ 297.5, 385.0, 336.5, 385.0 ]
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
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-5", 0 ],
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
					"source" : [ "obj-3", 1 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [ 350.0, 421.0, 405.0, 421.0, 405.0, 228.0, 456.5, 228.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 2 ],
					"destination" : [ "obj-8", 0 ],
					"hidden" : 0,
					"midpoints" : [ 363.5, 417.0, 392.0, 417.0, 392.0, 169.0, 420.5, 169.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 3 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 377.0, 429.0, 377.5, 429.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [ 381.5, 221.5, 297.5, 221.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-29", 1 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 422.0, 90.0, 238.25, 90.0, 238.25, 46.0, 54.5, 46.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-28", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-26", 0 ],
					"destination" : [ "obj-29", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-214", 0 ],
					"destination" : [ "obj-6", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 238.5, 264.0, 334.5, 264.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-13", 1 ],
					"destination" : [ "obj-11", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [ 321.5, 79.0, 238.5, 79.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-13", 1 ],
					"hidden" : 0,
					"midpoints" : [ 321.5, 78.0, 258.5, 78.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-11", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 258.5, 258.0, 334.5, 258.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
