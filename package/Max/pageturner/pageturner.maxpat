{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 105.0, 52.0, 1035.0, 742.0 ],
		"bglocked" : 0,
		"defrect" : [ 105.0, 52.0, 1035.0, 742.0 ],
		"openrect" : [ 105.0, 52.0, 486.0, 522.0 ],
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
					"text" : "s java",
					"numoutlets" : 0,
					"id" : "obj-111",
					"fontname" : "Arial",
					"patching_rect" : [ 317.0, 463.0, 42.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numoutlets" : 0,
					"id" : "obj-109",
					"fontname" : "Arial",
					"patching_rect" : [ 243.0, 463.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p pcollect",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-110",
					"fontname" : "Arial",
					"patching_rect" : [ 275.0, 435.0, 61.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 755.0, 589.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"defrect" : [ 755.0, 589.0, 640.0, 480.0 ],
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
									"maxclass" : "message",
									"text" : "tempomap",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-95",
									"fontname" : "Arial",
									"patching_rect" : [ 399.0, 133.0, 67.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "temporeset",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-48",
									"fontname" : "Arial",
									"patching_rect" : [ 305.0, 133.0, 71.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-3",
									"patching_rect" : [ 305.0, 207.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "tempomap.inscore",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-6",
									"fontname" : "Arial",
									"patching_rect" : [ 178.0, 131.0, 109.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "collect.inscore",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-5",
									"fontname" : "Arial",
									"patching_rect" : [ 83.0, 131.0, 87.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene load",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"fontname" : "Arial",
									"patching_rect" : [ 83.0, 167.0, 140.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"id" : "obj-4",
									"fontname" : "Arial",
									"patching_rect" : [ 83.0, 79.0, 48.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 83.0, 209.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-1",
									"patching_rect" : [ 83.0, 32.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 122.5, 187.5, 122.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [ 187.5, 157.5, 92.5, 157.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-48", 0 ],
									"hidden" : 0,
									"midpoints" : [ 92.5, 116.5, 314.5, 116.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-95", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 110.5, 408.5, 110.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-48", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-95", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 408.5, 178.5, 314.5, 178.5 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numoutlets" : 0,
					"id" : "obj-107",
					"fontname" : "Arial",
					"patching_rect" : [ 230.0, 146.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ptest",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-106",
					"fontname" : "Arial",
					"patching_rect" : [ 230.0, 119.0, 47.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 454.0, 604.0, 355.0, 272.0 ],
						"bglocked" : 0,
						"defrect" : [ 454.0, 604.0, 355.0, 272.0 ],
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
									"maxclass" : "message",
									"text" : "pageturn.inscore",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-6",
									"fontname" : "Arial",
									"patching_rect" : [ 178.0, 131.0, 100.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "testturn.inscore",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-5",
									"fontname" : "Arial",
									"patching_rect" : [ 83.0, 131.0, 93.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene load",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"fontname" : "Arial",
									"patching_rect" : [ 83.0, 167.0, 140.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"id" : "obj-4",
									"fontname" : "Arial",
									"patching_rect" : [ 83.0, 95.0, 48.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 83.0, 209.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-1",
									"patching_rect" : [ 83.0, 32.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [ 187.5, 157.5, 92.5, 157.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 122.5, 187.5, 122.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numoutlets" : 0,
					"id" : "obj-105",
					"fontname" : "Arial",
					"patching_rect" : [ 570.0, 664.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"id" : "obj-104",
					"patching_rect" : [ 588.0, 550.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p pclocks",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-103",
					"fontname" : "Arial",
					"patching_rect" : [ 570.0, 636.0, 61.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1217.0, 625.0, 546.0, 360.0 ],
						"bglocked" : 0,
						"defrect" : [ 1217.0, 625.0, 546.0, 360.0 ],
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
									"maxclass" : "message",
									"text" : "tempomap.inscore",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-6",
									"fontname" : "Arial",
									"patching_rect" : [ 355.0, 151.0, 109.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "play.inscore",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-5",
									"fontname" : "Arial",
									"patching_rect" : [ 260.0, 151.0, 74.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene load",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-11",
									"fontname" : "Arial",
									"patching_rect" : [ 260.0, 187.0, 140.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"id" : "obj-4",
									"fontname" : "Arial",
									"patching_rect" : [ 260.0, 115.0, 48.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r _tempo",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-52",
									"fontname" : "Arial",
									"patching_rect" : [ 177.0, 51.0, 58.0, 20.0 ],
									"numinlets" : 0,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 103.0, 249.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-1",
									"patching_rect" : [ 102.0, 28.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/pagepos clock",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-76",
									"fontname" : "Arial",
									"patching_rect" : [ 65.0, 197.0, 147.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/_* clock",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-83",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 167.0, 112.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-84",
									"patching_rect" : [ 103.0, 74.0, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tempo 20 1 96",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-85",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 114.0, 87.0, 20.0 ],
									"numinlets" : 4,
									"fontsize" : 12.0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-76", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-83", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-84", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-84", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 104.0, 269.5, 104.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [ 298.5, 142.5, 364.5, 142.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [ 364.5, 177.5, 269.5, 177.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-52", 0 ],
									"destination" : [ "obj-85", 1 ],
									"hidden" : 0,
									"midpoints" : [ 186.5, 92.0, 135.166672, 92.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-84", 0 ],
									"destination" : [ "obj-85", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 97.5, 112.5, 97.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-85", 0 ],
									"destination" : [ "obj-83", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-85", 0 ],
									"destination" : [ "obj-76", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 155.5, 74.5, 155.5 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-97",
					"fontname" : "Arial",
					"patching_rect" : [ 658.0, 576.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p tmap",
					"numoutlets" : 0,
					"id" : "obj-101",
					"fontname" : "Arial",
					"patching_rect" : [ 588.0, 611.0, 47.0, 20.0 ],
					"numinlets" : 3,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1211.0, 266.0, 518.0, 250.0 ],
						"bglocked" : 0,
						"defrect" : [ 1211.0, 266.0, 518.0, 250.0 ],
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
						"visible" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "fromsymbol",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-7",
									"fontname" : "Arial",
									"patching_rect" : [ 104.0, 100.0, 73.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-4",
									"patching_rect" : [ 103.0, 34.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-1",
									"patching_rect" : [ 202.0, 37.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-87",
									"patching_rect" : [ 26.0, 145.0, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-82",
									"fontname" : "Arial",
									"patching_rect" : [ 55.0, 147.0, 33.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"id" : "obj-78",
									"fontname" : "Arial",
									"patching_rect" : [ 26.0, 117.0, 48.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend insert",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-54",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 155.0, 87.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "qlist",
									"numoutlets" : 3,
									"outlettype" : [ "", "bang", "bang" ],
									"id" : "obj-49",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 190.0, 46.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0,
									"save" : [ "#N", "qlist", ";", "#X", "insert", 0, "_tempo", 51.019566, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 0, 32, ";", ";", "#X", "insert", 2490, "_tempo", 60.227592, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 17, 32, ";", ";", "#X", "insert", 2090, "_tempo", 54.717697, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 17, 16, ";", ";", "#X", "insert", 2090, "_tempo", 52.645256, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 49, 32, ";", ";", "#X", "insert", 2270, "_tempo", 61.174942, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 65, 32, ";", ";", "#X", "insert", 1950, "_tempo", 60.28109, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 81, 32, ";", ";", "#X", "insert", 2040, "_tempo", 48.105816, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 97, 32, ";", ";", "#X", "insert", 2350, "_tempo", 67.934601, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7, 2, ";", ";", "#X", "insert", 1790, "_tempo", 63.19656, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4, 1, ";", ";", "#X", "insert", 1880, "_tempo", 60.440929, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 9, 2, ";", ";", "#X", "insert", 2020, "_tempo", 53.341709, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 161, 32, ";", ";", "#X", "insert", 2130, "_tempo", 77.184509, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11, 2, ";", ";", "#X", "insert", 1610, "_tempo", 55.915646, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6, 1, ";", ";", "#X", "insert", 2110, "_tempo", 58.277626, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 13, 2, ";", ";", "#X", "insert", 2040, "_tempo", 63.131084, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7, 1, ";", ";", "#X", "insert", 1880, "_tempo", 63.027519, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 15, 2, ";", ";", "#X", "insert", 1950, "_tempo", 56.073677, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 8, 1, ";", ";", "#X", "insert", 2210, "_tempo", 59.153622, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 273, 32, ";", ";", "#X", "insert", 2040, "_tempo", 58.937092, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 289, 32, ";", ";", "#X", "insert", 1950, "_tempo", 52.604584, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 19, 2, ";", ";", "#X", "insert", 2260, "_tempo", 63.237576, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10, 1, ";", ";", "#X", "insert", 1950, "_tempo", 59.692738, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 21, 2, ";", ";", "#X", "insert", 1990, "_tempo", 63.227962, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11, 1, ";", ";", "#X", "insert", 1910, "_tempo", 62.061665, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 23, 2, ";", ";", "#X", "insert", 3850, "_tempo", 63.011505, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 25, 2, ";", ";", "#X", "insert", 2020, "_tempo", 59.427177, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 417, 32, ";", ";", "#X", "insert", 1980, "_tempo", 64.011406, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 433, 32, ";", ";", "#X", "insert", 1900, "_tempo", 58.589935, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 449, 32, ";", ";", "#X", "insert", 2000, "_tempo", 67.617882, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 465, 32, ";", ";", "#X", "insert", 1830, "_tempo", 61.588818, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 481, 32, ";", ";", "#X", "insert", 1950, "_tempo", 53.462257, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 497, 32, ";", ";", "#X", "insert", 2230, "_tempo", 52.817753, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 513, 32, ";", ";", "#X", "insert", 2140, "_tempo", 56.302444, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 33, 2, ";", ";", "#X", "insert", 2110, "_tempo", 54.56929, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 17, 1, ";", ";", "#X", "insert", 2230, "_tempo", 65.387138, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 35, 2, ";", ";", "#X", "insert", 1860, "_tempo", 55.850506, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 18, 1, ";", ";", "#X", "insert", 2110, "_tempo", 62.644981, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 37, 2, ";", ";", "#X", "insert", 1950, "_tempo", 50.208023, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 19, 1, ";", ";", "#X", "insert", 2300, "_tempo", 81.661438, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 39, 2, ";", ";", "#X", "insert", 1560, "_tempo", 60.288979, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 641, 32, ";", ";", "#X", "insert", 3920, "_tempo", 56.393253, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 21, 1, ";", ";", "#X", "insert", 2090, "_tempo", 63.437523, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 43, 2, ";", ";", "#X", "insert", 1930, "_tempo", 61.731709, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 22, 1, ";", ";", "#X", "insert", 1880, "_tempo", 60.650444, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 45, 2, ";", ";", "#X", "insert", 2040, "_tempo", 64.16153, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 23, 1, ";", ";", "#X", "insert", 1810, "_tempo", 57.931026, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 47, 2, ";", ";", "#X", "insert", 2160, "_tempo", 54.906979, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 24, 1, ";", ";", "#X", "insert", 2070, "_tempo", 57.974049, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 49, 2, ";", ";", "#X", "insert", 4180, "_tempo", 60.181492, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51, 2, ";", ";", "#X", "insert", 2020, "_tempo", 56.804157, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 26, 1, ";", ";", "#X", "insert", 2020, "_tempo", 68.672218, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 847, 32, ";", ";", "#X", "insert", 1810, "_tempo", 57.31197, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 27, 1, ";", ";", "#X", "insert", 2070, "_tempo", 56.918282, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 55, 2, ";", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-2",
									"patching_rect" : [ 26.0, 34.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-82", 0 ],
									"destination" : [ "obj-49", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-87", 0 ],
									"destination" : [ "obj-49", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-78", 1 ],
									"destination" : [ "obj-82", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-78", 0 ],
									"destination" : [ "obj-87", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-78", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-49", 0 ],
									"hidden" : 0,
									"midpoints" : [ 211.5, 185.5, 112.5, 185.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-54", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-54", 0 ],
									"destination" : [ "obj-49", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-102",
					"fontname" : "Arial",
					"patching_rect" : [ 615.0, 576.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-94",
					"fontname" : "Arial",
					"patching_rect" : [ 351.0, 485.0, 48.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /collect /play /open /pos",
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"id" : "obj-90",
					"fontname" : "Arial",
					"patching_rect" : [ 351.0, 402.0, 167.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7101",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-92",
					"fontname" : "Arial",
					"patching_rect" : [ 351.0, 372.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-87",
					"fontname" : "Arial",
					"patching_rect" : [ 175.0, 119.0, 48.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "generate",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-70",
					"fontname" : "Arial",
					"patching_rect" : [ 148.0, 187.0, 58.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p clocks",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-54",
					"fontname" : "Arial",
					"patching_rect" : [ 216.0, 258.0, 54.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 611.0, 698.0, 307.0, 333.0 ],
						"bglocked" : 0,
						"defrect" : [ 611.0, 698.0, 307.0, 333.0 ],
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
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 103.0, 249.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-1",
									"patching_rect" : [ 102.0, 28.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/pagepos clock",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-76",
									"fontname" : "Arial",
									"patching_rect" : [ 65.0, 197.0, 147.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/_* clock",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-83",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 167.0, 112.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-84",
									"patching_rect" : [ 103.0, 74.0, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tempo 120 1 96",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-85",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 114.0, 94.0, 20.0 ],
									"numinlets" : 4,
									"fontsize" : 12.0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-84", 0 ],
									"destination" : [ "obj-85", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 97.5, 112.5, 97.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-85", 0 ],
									"destination" : [ "obj-83", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-85", 0 ],
									"destination" : [ "obj-76", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 155.5, 74.5, 155.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-84", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-83", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-76", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/* del",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-58",
					"fontname" : "Arial",
					"patching_rect" : [ 62.0, 630.0, 94.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"numoutlets" : 0,
					"id" : "obj-80",
					"fontname" : "Arial",
					"patching_rect" : [ 463.0, 608.0, 42.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-79",
					"fontname" : "Arial",
					"patching_rect" : [ 427.0, 653.0, 74.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "append 0",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-77",
					"fontname" : "Arial",
					"patching_rect" : [ 462.0, 576.0, 61.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend timepair",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-74",
					"fontname" : "Arial",
					"patching_rect" : [ 462.0, 530.0, 101.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "12137",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-65",
					"fontname" : "Arial",
					"patching_rect" : [ 350.0, 685.0, 46.5, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"id" : "obj-64",
					"patching_rect" : [ 351.0, 597.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"presentation_rect" : [ 11.0, 491.0, 20.0, 20.0 ],
					"id" : "obj-63",
					"patching_rect" : [ 381.0, 596.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p openaudio",
					"numoutlets" : 2,
					"outlettype" : [ "bang", "int" ],
					"id" : "obj-55",
					"fontname" : "Arial",
					"patching_rect" : [ 321.0, 656.0, 77.0, 20.0 ],
					"numinlets" : 3,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1119.0, 373.0, 378.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 1119.0, 373.0, 378.0, 365.0 ],
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
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-10",
									"patching_rect" : [ 35.0, 213.0, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-9",
									"patching_rect" : [ 35.0, 263.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "0",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-8",
									"fontname" : "Arial",
									"patching_rect" : [ 235.0, 172.0, 32.5, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "counter",
									"numoutlets" : 4,
									"outlettype" : [ "int", "", "", "int" ],
									"id" : "obj-7",
									"fontname" : "Arial",
									"patching_rect" : [ 174.0, 209.0, 73.0, 20.0 ],
									"numinlets" : 5,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "metro 10",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-6",
									"fontname" : "Arial",
									"patching_rect" : [ 174.0, 172.0, 58.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"id" : "obj-4",
									"patching_rect" : [ 174.0, 25.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-3",
									"patching_rect" : [ 257.0, 26.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "open",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-33",
									"fontname" : "Arial",
									"patching_rect" : [ 257.0, 92.0, 37.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"numoutlets" : 0,
									"id" : "obj-27",
									"patching_rect" : [ 70.0, 146.0, 45.0, 45.0 ],
									"numinlets" : 2
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "open",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-82",
									"fontname" : "Arial",
									"patching_rect" : [ 82.0, 61.0, 37.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sfplay~",
									"numoutlets" : 2,
									"outlettype" : [ "signal", "bang" ],
									"id" : "obj-79",
									"fontname" : "Arial",
									"patching_rect" : [ 82.0, 101.0, 49.0, 20.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0,
									"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 174.0, 264.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-1",
									"patching_rect" : [ 82.0, 27.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-82", 0 ],
									"destination" : [ "obj-79", 0 ],
									"hidden" : 0,
									"midpoints" : [ 91.5, 95.0, 91.5, 95.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-82", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [ 266.5, 133.0, 79.5, 133.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-79", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-79", 0 ],
									"destination" : [ "obj-27", 1 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [ 183.5, 128.5, 79.5, 128.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-7", 2 ],
									"hidden" : 0,
									"midpoints" : [ 244.5, 201.5, 210.5, 201.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [ 183.5, 110.5, 244.5, 110.5 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-79", 0 ],
									"hidden" : 0,
									"midpoints" : [ 183.5, 89.0, 91.5, 89.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [ 91.5, 57.0, 44.5, 57.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open sound file",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 3.0, 66.0, 92.0, 18.0 ],
					"id" : "obj-57",
					"fontname" : "Arial",
					"patching_rect" : [ 321.0, 622.0, 92.0, 18.0 ],
					"numinlets" : 2,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Open an audio file and and switch to \"Tempo map collection\" mode (right arrow). \nClick on 'collect' to start collecting the tempo map and next on the score in sync with the audio, at the corresponding locations. \nWhen finished, click 'collect' again to stop the audio and generate the tempo map. \nYou can test the synchronization using the 'Play' button.\nYou can open the tempo map cue list using the 'Open' button.",
					"linecount" : 8,
					"presentation_linecount" : 6,
					"numoutlets" : 0,
					"presentation_rect" : [ 14.0, 321.0, 462.0, 89.0 ],
					"id" : "obj-46",
					"fontname" : "Arial",
					"patching_rect" : [ 779.0, 470.0, 362.0, 117.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "2) Tempo map",
					"numoutlets" : 0,
					"presentation_rect" : [ 16.0, 293.0, 123.0, 23.0 ],
					"id" : "obj-44",
					"fontname" : "Arial",
					"patching_rect" : [ 727.0, 443.0, 185.0, 23.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "1) Page turn",
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 193.0, 123.0, 23.0 ],
					"id" : "obj-11",
					"fontname" : "Arial",
					"patching_rect" : [ 734.0, 308.0, 185.0, 23.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay 10",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-43",
					"fontname" : "Arial",
					"patching_rect" : [ 216.0, 187.0, 56.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b",
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"id" : "obj-37",
					"fontname" : "Arial",
					"patching_rect" : [ 216.0, 214.0, 34.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numoutlets" : 0,
					"id" : "obj-33",
					"fontname" : "Arial",
					"patching_rect" : [ 171.0, 408.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route set",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-32",
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 366.0, 57.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "dump",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-7",
					"fontname" : "Arial",
					"patching_rect" : [ 274.0, 260.0, 41.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay 10",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-10",
					"fontname" : "Arial",
					"patching_rect" : [ 89.0, 186.0, 56.0, 20.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-3",
					"fontname" : "Arial",
					"patching_rect" : [ 89.0, 212.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Notes",
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 416.0, 49.0, 23.0 ],
					"id" : "obj-30",
					"fontname" : "Arial",
					"patching_rect" : [ 738.0, 586.0, 111.0, 23.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• The score is assumed to have the OSC address '/ITL/scene/score'.\n  You should edit the script manually to use another address.\n• Each time you click in a page, the location replaces the previous one.\n• Click to a non-timed location (e.g. outside a system) may lead to\n  unpredictable results.\n• In test mode, you can click to the score to move the cursor position.",
					"linecount" : 6,
					"presentation_linecount" : 6,
					"numoutlets" : 0,
					"presentation_rect" : [ 71.0, 419.0, 402.0, 89.0 ],
					"id" : "obj-27",
					"fontname" : "Arial",
					"patching_rect" : [ 740.0, 620.0, 388.0, 89.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-22",
					"patching_rect" : [ 441.0, 253.0, 20.0, 20.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-18",
					"fontname" : "Arial",
					"patching_rect" : [ 441.0, 278.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "When done, click on open to get the INScore messages, which you can save to a file. The messages involve a hidden object named '_pageturner', and responsible to turn the pages. You should move this object in time by sending clock or date messages. ",
					"linecount" : 5,
					"presentation_linecount" : 3,
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 236.0, 470.0, 48.0 ],
					"id" : "obj-26",
					"fontname" : "Arial",
					"patching_rect" : [ 780.0, 373.0, 351.0, 75.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b",
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"id" : "obj-24",
					"fontname" : "Arial",
					"patching_rect" : [ 89.0, 149.0, 34.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-20",
					"fontname" : "Arial",
					"patching_rect" : [ 132.0, 111.0, 37.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL load layout.inscore",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-8",
					"fontname" : "Arial",
					"patching_rect" : [ 548.0, 107.0, 134.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "text",
					"numoutlets" : 3,
					"outlettype" : [ "", "bang", "int" ],
					"id" : "obj-15",
					"fontname" : "Arial",
					"patching_rect" : [ 107.0, 331.0, 46.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend store",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-9",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 109.0, 85.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p openscore",
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
					"id" : "obj-17",
					"fontname" : "Arial",
					"patching_rect" : [ 549.0, 70.0, 77.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1056.0, 250.0, 378.0, 365.0 ],
						"bglocked" : 0,
						"defrect" : [ 1056.0, 250.0, 378.0, 365.0 ],
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
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-5",
									"patching_rect" : [ 20.0, 307.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-4",
									"patching_rect" : [ 19.0, 205.5, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-3",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 53.0, 60.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numoutlets" : 0,
									"id" : "obj-2",
									"patching_rect" : [ 159.0, 311.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-1",
									"patching_rect" : [ 112.0, 26.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/* del",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-14",
									"fontname" : "Arial",
									"patching_rect" : [ 244.0, 236.5, 94.0, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-11",
									"patching_rect" : [ 244.0, 200.5, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "conformpath native boot",
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"id" : "obj-81",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 155.5, 139.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"id" : "obj-80",
									"patching_rect" : [ 112.0, 91.5, 20.0, 20.0 ],
									"numinlets" : 1
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "set",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-76",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 91.5, 32.5, 18.0 ],
									"numinlets" : 2,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene/score set file",
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"id" : "obj-74",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 207.5, 185.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "opendialog",
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"id" : "obj-69",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 126.5, 77.0, 20.0 ],
									"numinlets" : 1,
									"fontsize" : 12.0
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-81", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-81", 0 ],
									"destination" : [ "obj-74", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-81", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [ 59.5, 186.0, 253.5, 186.0 ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-80", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-76", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-74", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-69", 0 ],
									"destination" : [ "obj-81", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-3", 0 ],
									"destination" : [ "obj-76", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-2", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-14", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-80", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "autofit 1",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-100",
					"fontname" : "Arial",
					"patching_rect" : [ 17.0, 699.0, 53.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read INScore.png",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-99",
					"fontname" : "Arial",
					"patching_rect" : [ 37.0, 723.0, 105.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "fpic",
					"numoutlets" : 0,
					"autofit" : 1,
					"presentation_rect" : [ 6.0, 100.0, 100.0, 89.0 ],
					"id" : "obj-98",
					"patching_rect" : [ 34.0, 749.0, 86.0, 79.0 ],
					"pic" : "INScore.png",
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Click on the score to each location where you want the next page to be displayed.",
					"linecount" : 2,
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 215.0, 450.0, 20.0 ],
					"id" : "obj-91",
					"fontname" : "Arial",
					"patching_rect" : [ 780.0, 330.0, 351.0, 34.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Basic principles",
					"numoutlets" : 0,
					"presentation_rect" : [ 101.0, 119.0, 155.0, 27.0 ],
					"id" : "obj-88",
					"fontname" : "Arial",
					"patching_rect" : [ 782.0, 221.0, 234.0, 27.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 18.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "You should first open a Guido file. Then proceed in:\n1) collecting the page turn\n2) collecting the tempo map",
					"linecount" : 3,
					"presentation_linecount" : 3,
					"numoutlets" : 0,
					"presentation_rect" : [ 101.0, 146.0, 363.0, 48.0 ],
					"id" : "obj-86",
					"fontname" : "Arial",
					"patching_rect" : [ 784.0, 257.0, 354.0, 48.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open score",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"presentation_rect" : [ 13.0, 40.0, 70.0, 18.0 ],
					"id" : "obj-75",
					"fontname" : "Arial",
					"patching_rect" : [ 549.0, 36.0, 92.0, 18.0 ],
					"numinlets" : 2,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numoutlets" : 0,
					"id" : "obj-73",
					"fontname" : "Arial",
					"patching_rect" : [ 548.0, 155.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL rootPath",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-34",
					"fontname" : "Arial",
					"patching_rect" : [ 163.0, 632.0, 127.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numoutlets" : 2,
					"outlettype" : [ "", "int" ],
					"id" : "obj-35",
					"fontname" : "Arial",
					"patching_rect" : [ 163.0, 604.0, 139.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-51",
					"fontname" : "Arial",
					"patching_rect" : [ 113.0, 554.0, 34.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-53",
					"fontname" : "Arial",
					"patching_rect" : [ 113.0, 579.0, 69.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0,
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Initialization",
					"numoutlets" : 0,
					"id" : "obj-56",
					"fontname" : "Arial",
					"patching_rect" : [ 160.0, 500.0, 91.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Reset",
					"numoutlets" : 0,
					"presentation_rect" : [ 37.0, 10.0, 41.0, 18.0 ],
					"id" : "obj-59",
					"fontname" : "Arial",
					"patching_rect" : [ 27.0, 523.0, 41.0, 18.0 ],
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
					"presentation_rect" : [ 13.0, 8.0, 20.0, 20.0 ],
					"id" : "obj-60",
					"patching_rect" : [ 34.0, 497.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"presentation" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numoutlets" : 0,
					"id" : "obj-61",
					"fontname" : "Arial",
					"patching_rect" : [ 163.0, 662.0, 67.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "bang", "bang" ],
					"id" : "obj-62",
					"fontname" : "Arial",
					"patching_rect" : [ 72.0, 526.0, 59.5, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"id" : "obj-67",
					"fontname" : "Arial",
					"patching_rect" : [ 72.0, 497.0, 60.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-68",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 19.0, 491.0, 293.0, 195.0 ],
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "The page turner collects time points with the corresponding page numbers to generate the watch messages to automatically turn the page at the corresponding locations.\nThe tempo collector collects pairs of absolute and music time to generate a tempo map.",
					"linecount" : 5,
					"presentation_linecount" : 5,
					"numoutlets" : 0,
					"presentation_rect" : [ 101.0, 46.0, 369.0, 75.0 ],
					"id" : "obj-31",
					"fontname" : "Arial",
					"patching_rect" : [ 783.0, 130.0, 339.0, 75.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "INScore page turner and tempo collector.",
					"linecount" : 2,
					"numoutlets" : 0,
					"presentation_rect" : [ 82.0, 8.0, 404.0, 29.0 ],
					"id" : "obj-29",
					"fontname" : "Arial",
					"patching_rect" : [ 782.0, 75.0, 333.0, 52.0 ],
					"numinlets" : 1,
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 20.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "compile",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-16",
					"fontname" : "Arial",
					"patching_rect" : [ 466.0, 173.0, 52.0, 18.0 ],
					"numinlets" : 2,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r java",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-6",
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 172.0, 40.0, 20.0 ],
					"numinlets" : 0,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "js turns.js",
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"id" : "obj-5",
					"fontname" : "Arial",
					"patching_rect" : [ 410.0, 209.0, 61.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"numoutlets" : 0,
					"id" : "obj-4",
					"fontname" : "Arial",
					"patching_rect" : [ 47.0, 260.0, 42.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /date /open /reset /test",
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"id" : "obj-2",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 65.0, 191.0, 20.0 ],
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
					"id" : "obj-1",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 35.0, 99.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 12.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"numoutlets" : 0,
					"id" : "obj-40",
					"fontname" : "Arial",
					"patching_rect" : [ 323.0, 35.0, 158.0, 23.0 ],
					"numinlets" : 1,
					"fontface" : 1,
					"fontsize" : 14.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _turnedit",
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"id" : "obj-39",
					"fontname" : "Arial",
					"patching_rect" : [ 324.0, 66.0, 65.0, 20.0 ],
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
					"patching_rect" : [ 324.0, 92.0, 136.0, 20.0 ],
					"numinlets" : 1,
					"fontsize" : 11.595187
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numoutlets" : 0,
					"id" : "obj-47",
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 303.0, 24.0, 195.0, 103.0 ],
					"numinlets" : 1
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [ 475.5, 199.5, 419.5, 199.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 419.5, 317.5, 116.5, 317.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-22", 0 ],
					"hidden" : 0,
					"midpoints" : [ 419.5, 246.0, 450.5, 246.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 98.5, 171.5, 98.5, 171.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"midpoints" : [ 116.5, 396.5, 180.5, 396.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [ 116.5, 366.0, 116.5, 366.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 283.5, 304.0, 116.5, 304.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 450.5, 319.0, 116.5, 319.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-22", 0 ],
					"destination" : [ "obj-18", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [ 557.5, 139.5, 557.5, 139.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 0 ],
					"destination" : [ "obj-8", 0 ],
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
					"source" : [ "obj-9", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-75", 0 ],
					"destination" : [ "obj-17", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-62", 1 ],
					"destination" : [ "obj-99", 0 ],
					"hidden" : 0,
					"midpoints" : [ 95.0, 603.0, 46.5, 603.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 3 ],
					"destination" : [ "obj-51", 0 ],
					"hidden" : 0,
					"midpoints" : [ 122.0, 554.0, 122.5, 554.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-100", 0 ],
					"hidden" : 0,
					"midpoints" : [ 81.5, 613.5, 26.5, 613.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-62", 0 ],
					"hidden" : 0,
					"midpoints" : [ 43.5, 519.0, 81.5, 519.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-53", 1 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 172.5, 606.5, 172.5, 606.5 ]
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
					"source" : [ "obj-39", 0 ],
					"destination" : [ "obj-72", 0 ],
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
					"midpoints" : [ 172.5, 656.5, 172.5, 656.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [ 616.5, 142.0, 557.5, 142.0 ]
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
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 98.5, 280.0, 116.5, 280.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 240.5, 246.5, 283.5, 246.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-43", 0 ],
					"destination" : [ "obj-37", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-57", 0 ],
					"destination" : [ "obj-55", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-63", 0 ],
					"destination" : [ "obj-55", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-55", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 1 ],
					"destination" : [ "obj-65", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-77", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 1 ],
					"destination" : [ "obj-79", 0 ],
					"hidden" : 0,
					"midpoints" : [ 388.5, 681.0, 416.5, 681.0, 416.5, 641.0, 436.5, 641.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-79", 0 ],
					"destination" : [ "obj-77", 0 ],
					"hidden" : 0,
					"midpoints" : [ 436.5, 682.0, 543.5, 682.0, 543.5, 567.0, 471.5, 567.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-77", 0 ],
					"destination" : [ "obj-80", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 2 ],
					"destination" : [ "obj-58", 0 ],
					"hidden" : 0,
					"midpoints" : [ 108.5, 618.5, 71.5, 618.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-58", 0 ],
					"destination" : [ "obj-61", 0 ],
					"hidden" : 0,
					"midpoints" : [ 71.5, 655.0, 172.5, 655.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 1 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [ 98.5, 103.0, 98.5, 103.0 ]
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-9", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 2 ],
					"destination" : [ "obj-20", 0 ],
					"hidden" : 0,
					"midpoints" : [ 141.5, 96.5, 141.5, 96.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 141.5, 249.5, 56.5, 249.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 1 ],
					"destination" : [ "obj-70", 0 ],
					"hidden" : 0,
					"midpoints" : [ 113.5, 171.5, 157.5, 171.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 157.5, 253.0, 56.5, 253.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 3 ],
					"destination" : [ "obj-87", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-87", 0 ],
					"destination" : [ "obj-70", 0 ],
					"hidden" : 0,
					"midpoints" : [ 184.5, 170.5, 157.5, 170.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-87", 0 ],
					"destination" : [ "obj-43", 0 ],
					"hidden" : 0,
					"midpoints" : [ 184.5, 162.5, 225.5, 162.5 ]
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
					"source" : [ "obj-87", 1 ],
					"destination" : [ "obj-54", 0 ],
					"hidden" : 0,
					"midpoints" : [ 213.5, 246.0, 225.5, 246.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-92", 0 ],
					"destination" : [ "obj-90", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-90", 3 ],
					"destination" : [ "obj-74", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-90", 0 ],
					"destination" : [ "obj-94", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-102", 0 ],
					"destination" : [ "obj-101", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-97", 0 ],
					"destination" : [ "obj-101", 2 ],
					"hidden" : 0,
					"midpoints" : [ 667.5, 601.0, 625.5, 601.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 1 ],
					"destination" : [ "obj-101", 1 ],
					"hidden" : 0,
					"midpoints" : [ 461.5, 239.0, 611.5, 239.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-90", 2 ],
					"destination" : [ "obj-102", 0 ],
					"hidden" : 0,
					"midpoints" : [ 434.5, 431.0, 455.5, 431.0, 455.5, 431.0, 624.5, 431.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-54", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"midpoints" : [ 225.5, 389.5, 180.5, 389.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-104", 0 ],
					"destination" : [ "obj-101", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-104", 0 ],
					"destination" : [ "obj-103", 0 ],
					"hidden" : 0,
					"midpoints" : [ 597.5, 607.0, 579.5, 607.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-103", 0 ],
					"destination" : [ "obj-105", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-94", 1 ],
					"destination" : [ "obj-97", 0 ],
					"hidden" : 0,
					"midpoints" : [ 389.5, 510.5, 667.5, 510.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-90", 1 ],
					"destination" : [ "obj-104", 0 ],
					"hidden" : 0,
					"midpoints" : [ 397.5, 431.5, 597.5, 431.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-104", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [ 597.5, 582.0, 360.5, 582.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 3 ],
					"destination" : [ "obj-106", 0 ],
					"hidden" : 0,
					"midpoints" : [ 184.5, 101.5, 239.5, 101.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-106", 0 ],
					"destination" : [ "obj-107", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-110", 0 ],
					"destination" : [ "obj-109", 0 ],
					"hidden" : 0,
					"midpoints" : [ 284.5, 458.5, 252.5, 458.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-90", 0 ],
					"destination" : [ "obj-110", 0 ],
					"hidden" : 0,
					"midpoints" : [ 360.5, 427.0, 284.5, 427.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-94", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-94", 1 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [ 389.5, 510.5, 360.5, 510.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-110", 1 ],
					"destination" : [ "obj-111", 0 ],
					"hidden" : 0,
					"midpoints" : [ 326.5, 459.5, 326.5, 459.5 ]
				}

			}
 ]
	}

}
