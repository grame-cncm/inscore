{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 105.0, 52.0, 486.0, 522.0 ],
		"bglocked" : 0,
		"defrect" : [ 105.0, 52.0, 486.0, 522.0 ],
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
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 317.0, 463.0, 42.0, 20.0 ],
					"id" : "obj-111",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 243.0, 463.0, 67.0, 20.0 ],
					"id" : "obj-109",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p pcollect",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 275.0, 435.0, 61.0, 20.0 ],
					"id" : "obj-110",
					"fontname" : "Arial",
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
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 399.0, 133.0, 67.0, 18.0 ],
									"id" : "obj-95",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "temporeset",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 305.0, 133.0, 71.0, 18.0 ],
									"id" : "obj-48",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 305.0, 207.0, 25.0, 25.0 ],
									"id" : "obj-3",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "tempomap.inscore",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 178.0, 131.0, 109.0, 18.0 ],
									"id" : "obj-6",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "collect.inscore",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 83.0, 131.0, 87.0, 18.0 ],
									"id" : "obj-5",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene load",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 83.0, 167.0, 140.0, 20.0 ],
									"id" : "obj-11",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 83.0, 79.0, 48.0, 20.0 ],
									"id" : "obj-4",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 83.0, 209.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 83.0, 32.0, 25.0, 25.0 ],
									"id" : "obj-1",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-95", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [ 408.5, 178.5, 314.5, 178.5 ]
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
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-95", 0 ],
									"hidden" : 0,
									"midpoints" : [ 121.5, 110.5, 408.5, 110.5 ]
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
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 230.0, 146.0, 67.0, 20.0 ],
					"id" : "obj-107",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p ptest",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 230.0, 119.0, 47.0, 20.0 ],
					"id" : "obj-106",
					"fontname" : "Arial",
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
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 178.0, 131.0, 100.0, 18.0 ],
									"id" : "obj-6",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "testturn.inscore",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 83.0, 131.0, 93.0, 18.0 ],
									"id" : "obj-5",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene load",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 83.0, 167.0, 140.0, 20.0 ],
									"id" : "obj-11",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 83.0, 95.0, 48.0, 20.0 ],
									"id" : "obj-4",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 83.0, 209.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 83.0, 32.0, 25.0, 25.0 ],
									"id" : "obj-1",
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
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 570.0, 664.0, 67.0, 20.0 ],
					"id" : "obj-105",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 588.0, 550.0, 20.0, 20.0 ],
					"id" : "obj-104"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p pclocks",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 570.0, 636.0, 61.0, 20.0 ],
					"id" : "obj-103",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1092.0, 666.0, 546.0, 360.0 ],
						"bglocked" : 0,
						"defrect" : [ 1092.0, 666.0, 546.0, 360.0 ],
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
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 355.0, 151.0, 109.0, 18.0 ],
									"id" : "obj-6",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "play.inscore",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 260.0, 151.0, 74.0, 18.0 ],
									"id" : "obj-5",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene load",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 260.0, 187.0, 140.0, 20.0 ],
									"id" : "obj-11",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 260.0, 115.0, 48.0, 20.0 ],
									"id" : "obj-4",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "r _tempo",
									"numinlets" : 0,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 177.0, 51.0, 58.0, 20.0 ],
									"id" : "obj-52",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 103.0, 249.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 102.0, 28.0, 25.0, 25.0 ],
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/pagepos clock",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 65.0, 197.0, 147.0, 18.0 ],
									"id" : "obj-76",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/_* clock",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 103.0, 167.0, 112.0, 18.0 ],
									"id" : "obj-83",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 103.0, 74.0, 20.0, 20.0 ],
									"id" : "obj-84"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tempo 20 1 96",
									"numinlets" : 4,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 103.0, 114.0, 87.0, 20.0 ],
									"id" : "obj-85",
									"fontname" : "Arial"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-85", 0 ],
									"destination" : [ "obj-76", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 155.5, 74.5, 155.5 ]
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
									"source" : [ "obj-84", 0 ],
									"destination" : [ "obj-85", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 97.5, 112.5, 97.5 ]
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
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [ 364.5, 177.5, 269.5, 177.5 ]
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
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-2", 0 ],
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
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-5", 0 ],
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
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 658.0, 576.0, 37.0, 18.0 ],
					"id" : "obj-97",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p tmap",
					"numinlets" : 3,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 588.0, 611.0, 47.0, 20.0 ],
					"id" : "obj-101",
					"fontname" : "Arial",
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1044.0, 492.0, 518.0, 250.0 ],
						"bglocked" : 0,
						"defrect" : [ 1044.0, 492.0, 518.0, 250.0 ],
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
									"text" : "fromsymbol",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 104.0, 100.0, 73.0, 20.0 ],
									"id" : "obj-7",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 103.0, 34.0, 25.0, 25.0 ],
									"id" : "obj-4",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 202.0, 37.0, 25.0, 25.0 ],
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 26.0, 145.0, 20.0, 20.0 ],
									"id" : "obj-87"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 55.0, 147.0, 33.0, 18.0 ],
									"id" : "obj-82",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"patching_rect" : [ 26.0, 117.0, 48.0, 20.0 ],
									"id" : "obj-78",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend insert",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 103.0, 155.0, 87.0, 20.0 ],
									"id" : "obj-54",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "qlist",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 3,
									"outlettype" : [ "", "bang", "bang" ],
									"patching_rect" : [ 103.0, 190.0, 46.0, 20.0 ],
									"id" : "obj-49",
									"fontname" : "Arial",
									"save" : [ "#N", "qlist", ";", "#X", "insert", 0, "_tempo", 4.342835, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 0, 1, ";", ";", "#X", "insert", 2670, "_tempo", 53.665989, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 20554, 425425, ";", ";", "#X", "insert", 1900, "_tempo", 80.839462, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 805193, 1701700, ";", ";", "#X", "insert", 1720, "_tempo", 63.7906, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 447768, 425425, ";", ";", "#X", "insert", 1550, "_tempo", 73.8134, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 17801, 12155, ";", ";", "#X", "insert", 1800, "_tempo", 58.690125, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1717101, 850850, ";", ";", "#X", "insert", 1790, "_tempo", 82.393074, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1044772, 425425, ";", ";", "#X", "insert", 1660, "_tempo", 50.206459, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2574431, 850850, ";", ";", "#X", "insert", 1700, "_tempo", 98.83474, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1438509, 425425, ";", ";", "#X", "insert", 1560, "_tempo", 66.693733, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1711813, 425425, ";", ";", "#X", "insert", 1610, "_tempo", 77.225327, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7608599, 1701700, ";", ";", "#X", "insert", 1640, "_tempo", 80.227211, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 773327, 154700, ";", ";", "#X", "insert", 1510, "_tempo", 80.159378, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 334484, 60775, ";", ";", "#X", "insert", 1720, "_tempo", 66.263985, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1477591, 243100, ";", ";", "#X", "insert", 1680, "_tempo", 87.154762, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 654851, 100100, ";", ";", "#X", "insert", 1620, "_tempo", 59.445435, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3033392, 425425, ";", ";", "#X", "insert", 1690, "_tempo", 91.039284, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12845891, 1701700, ";", ";", "#X", "insert", 1700, "_tempo", 64.647789, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3485813, 425425, ";", ";", "#X", "insert", 1680, "_tempo", 62.137432, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 86549, 10010, ";", ";", "#X", "insert", 4160, "_tempo", 76.517937, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4136536, 425425, ";", ";", "#X", "insert", 1770, "_tempo", 80.840073, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 147113, 14300, ";", ";", "#X", "insert", 2350, "_tempo", 59.708965, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2693349, 243100, ";", ";", "#X", "insert", 1660, "_tempo", 69.100601, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 19556223, 1701700, ";", ";", "#X", "insert", 2650, "_tempo", 68.403679, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 744807, 60775, ";", ";", "#X", "insert", 1610, "_tempo", 71.299202, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 21635463, 1701700, ";", ";", "#X", "insert", 2510, "_tempo", 77.982079, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3272053, 243100, ";", ";", "#X", "insert", 1730, "_tempo", 75.579323, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5965233, 425425, ";", ";", "#X", "insert", 1530, "_tempo", 72.070976, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12340421, 850850, ";", ";", "#X", "insert", 1710, "_tempo", 63.536568, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 19166006, 1276275, ";", ";", "#X", "insert", 1820, "_tempo", 93.700394, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1883899, 121550, ";", ";", "#X", "insert", 1430, "_tempo", 63.29303, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 13662321, 850850, ";", ";", "#X", "insert", 1740, "_tempo", 62.973316, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6022609, 364650, ";", ";", "#X", "insert", 1890, "_tempo", 72.510101, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 28949407, 1701700, ";", ";", "#X", "insert", 1640, "_tempo", 72.230469, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1191703, 68068, ";", ";", "#X", "insert", 3240, "_tempo", 74.567284, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 15725961, 850850, ";", ";", "#X", "insert", 3360, "_tempo", 65.879669, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2373457, 121550, ";", ";", "#X", "insert", 3490, "_tempo", 84.587448, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 34858627, 1701700, ";", ";", "#X", "insert", 1660, "_tempo", 71.899773, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 35854229, 1701700, ";", ";", "#X", "insert", 1570, "_tempo", 88.103706, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 18327307, 850850, ";", ";", "#X", "insert", 1500, "_tempo", 68.433083, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1342559, 60775, ";", ";", "#X", "insert", 1730, "_tempo", 63.979858, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2956237, 130900, ";", ";", "#X", "insert", 2690, "_tempo", 63.809151, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 39651383, 1701700, ";", ";", "#X", "insert", 2330, "_tempo", 78.156746, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5815079, 243100, ";", ";", "#X", "insert", 1550, "_tempo", 75.088547, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2444971, 100100, ";", ";", "#X", "insert", 1870, "_tempo", 79.749214, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 89412, 3575, ";", ";", "#X", "insert", 1450, "_tempo", 72.45623, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 182269, 7150, ";", ";", "#X", "insert", 1760, "_tempo", 72.493095, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 44284213, 1701700, ";", ";", "#X", "insert", 2400, "_tempo", 76.834877, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11379457, 425425, ";", ";", "#X", "insert", 1720, "_tempo", 66.343323, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 46454869, 1701700, ";", ";", "#X", "insert", 1660, "_tempo", 70.202324, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11808934, 425425, ";", ";", "#X", "insert", 2510, "_tempo", 81.155716, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 48485123, 1701700, ";", ";", "#X", "insert", 1510, "_tempo", 72.032784, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 345133, 11900, ";", ";", "#X", "insert", 1720, "_tempo", 77.025581, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12558124, 425425, ";", ";", "#X", "insert", 1680, "_tempo", 71.513023, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51150017, 1701700, ";", ";", "#X", "insert", 1540, "_tempo", 91.128754, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10386177, 340340, ";", ";", "#X", "insert", 1420, "_tempo", 56.813103, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10569681, 340340, ";", ";", "#X", "insert", 1890, "_tempo", 81.914665, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4123827, 130900, ";", ";", "#X", "insert", 1650, "_tempo", 71.031036, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 27284043, 850850, ";", ";", "#X", "insert", 2370, "_tempo", 84.473518, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 13940428, 425425, ";", ";", "#X", "insert", 2250, "_tempo", 77.577713, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11421871, 340340, ";", ";", "#X", "insert", 1680, "_tempo", 61.566067, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 58033453, 1701700, ";", ";", "#X", "insert", 1720, "_tempo", 68.849213, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3457899, 100100, ";", ";", "#X", "insert", 1710, "_tempo", 72.422287, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4586081, 130900, ";", ";", "#X", "insert", 1680, "_tempo", 77.699188, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 274917, 7735, ";", ";", "#X", "insert", 1630, "_tempo", 62.931541, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 61379739, 1701700, ";", ";", "#X", "insert", 1750, "_tempo", 82.929344, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 15540152, 425425, ";", ";", "#X", "insert", 1660, "_tempo", 68.831284, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 31568347, 850850, ";", ";", "#X", "insert", 1600, "_tempo", 62.793468, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 31958781, 850850, ";", ";", "#X", "insert", 1820, "_tempo", 64.782059, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1244767, 32725, ";", ";", "#X", "insert", 1700, "_tempo", 77.224983, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 16377187, 425425, ";", ";", "#X", "insert", 1640, "_tempo", 65.165382, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 33203371, 850850, ";", ";", "#X", "insert", 1690, "_tempo", 73.528633, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 33593803, 850850, ";", ";", "#X", "insert", 3370, "_tempo", 72.454628, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5303427, 130900, ";", ";", "#X", "insert", 1790, "_tempo", 68.342033, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 34932067, 850850, ";", ";", "#X", "insert", 1470, "_tempo", 87.696274, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10082351, 243100, ";", ";", "#X", "insert", 1610, "_tempo", 57.550735, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3578878, 85085, ";", ";", "#X", "insert", 1840, "_tempo", 91.660004, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1643827, 38675, ";", ";", "#X", "insert", 1570, "_tempo", 64.965164, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5642211, 130900, ";", ";", "#X", "insert", 1630, "_tempo", 70.885544, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7409957, 170170, ";", ";", "#X", "insert", 2360, "_tempo", 82.962379, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3011429, 68068, ";", ";", "#X", "insert", 2960, "_tempo", 69.660629, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 77026909, 1701700, ";", ";", "#X", "insert", 1660, "_tempo", 74.940636, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5988217, 130900, ";", ";", "#X", "insert", 1690, "_tempo", 73.540291, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51133, 1105, ";", ";", "#X", "insert", 2490, "_tempo", 63.536713, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1539292, 32725, ";", ";", "#X", "insert", 1690, "_tempo", 84.027908, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 20201133, 425425, ";", ";", "#X", "insert", 1540, "_tempo", 64.601479, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11674579, 243100, ";", ";", "#X", "insert", 1790, "_tempo", 91.128853, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1500763, 30940, ";", ";", "#X", "insert", 1420, "_tempo", 67.230606, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3793613, 77350, ";", ";", "#X", "insert", 1720, "_tempo", 74.832298, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6019957, 121550, ";", ";", "#X", "insert", 1660, "_tempo", 66.183258, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 85160181, 1701700, ";", ";", "#X", "insert", 1600, "_tempo", 84.742172, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 21477752, 425425, ";", ";", "#X", "insert", 1570, "_tempo", 72.517967, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 43427177, 850850, ";", ";", "#X", "insert", 1610, "_tempo", 76.876465, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1992777, 38675, ";", ";", "#X", "insert", 1660, "_tempo", 75.422424, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6814387, 130900, ";", ";", "#X", "insert", 1440, "_tempo", 72.352287, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 89357109, 1701700, ";", ";", "#X", "insert", 3300, "_tempo", 82.255562, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 18210007, 340340, ";", ";", "#X", "insert", 1680, "_tempo", 68.831108, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 18405971, 340340, ";", ";", "#X", "insert", 1600, "_tempo", 80.036217, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 92810721, 1701700, ";", ";", "#X", "insert", 1720, "_tempo", 68.091606, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 23446701, 425425, ";", ";", "#X", "insert", 3280, "_tempo", 69.962486, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 95370381, 1701700, ";", ";", "#X", "insert", 1630, "_tempo", 80.768852, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3434963, 60775, ";", ";", "#X", "insert", 1580, "_tempo", 68.286743, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 48541903, 850850, ";", ";", "#X", "insert", 1670, "_tempo", 83.408356, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 13984627, 243100, ";", ";", "#X", "insert", 1530, "_tempo", 64.577988, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7599787, 130900, ";", ";", "#X", "insert", 1850, "_tempo", 79.140778, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 49822159, 850850, ";", ";", "#X", "insert", 1460, "_tempo", 65.331276, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1931992, 32725, ";", ";", "#X", "insert", 1770, "_tempo", 77.738731, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3895519, 65450, ";", ";", "#X", "insert", 1700, "_tempo", 69.680817, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3931559, 65450, ";", ";", "#X", "insert", 1620, "_tempo", 70.63298, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 103020921, 1701700, ";", ";", "#X", "insert", 1910, "_tempo", 80.977776, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7426963, 121550, ";", ";", "#X", "insert", 1360, "_tempo", 71.102768, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 26189587, 425425, ";", ";", "#X", "insert", 1700, "_tempo", 65.412292, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 96014, 1547, ";", ";", "#X", "insert", 2540, "_tempo", 84.742081, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 8214881, 130900, ";", ";", "#X", "insert", 1570, "_tempo", 74.051018, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4143723, 65450, ";", ";", "#X", "insert", 1540, "_tempo", 85.743324, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 108545379, 1701700, ";", ";", "#X", "insert", 1520, "_tempo", 75.101471, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3909624, 60775, ";", ";", "#X", "insert", 1410, "_tempo", 62.685032, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 55110149, 850850, ";", ";", "#X", "insert", 2000, "_tempo", 87.546494, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 27777306, 425425, ";", ";", "#X", "insert", 2140, "_tempo", 74.53511, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11243761, 170170, ";", ";", "#X", "insert", 1530, "_tempo", 76.200989, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 28311548, 425425, ";", ";", "#X", "insert", 3100, "_tempo", 62.274315, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 28730278, 425425, ";", ";", "#X", "insert", 1810, "_tempo", 91.775139, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 809233, 11900, ";", ";", "#X", "insert", 1500, "_tempo", 82.597527, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3334183, 48620, ";", ";", "#X", "insert", 3400, "_tempo", 60.708351, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 8477687, 121550, ";", ";", "#X", "insert", 3220, "_tempo", 58.779472, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 120073659, 1701700, ";", ";", "#X", "insert", 3200, "_tempo", 73.420036, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 60703663, 850850, ";", ";", "#X", "insert", 1500, "_tempo", 79.975288, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 61094097, 850850, ";", ";", "#X", "insert", 2100, "_tempo", 72.047707, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 30844754, 425425, ";", ";", "#X", "insert", 3210, "_tempo", 76.231781, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11365349, 154700, ";", ";", "#X", "insert", 1770, "_tempo", 74.127037, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 94481663, 1276275, ";", ";", "#X", "insert", 1580, "_tempo", 72.772469, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 95104489, 1276275, ";", ";", "#X", "insert", 1710, "_tempo", 69.036308, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 38306497, 510510, ";", ";", "#X", "insert", 1670, "_tempo", 73.881668, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 64252891, 850850, ";", ";", "#X", "insert", 1640, "_tempo", 81.608566, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 129364899, 1701700, ";", ";", "#X", "insert", 1110, "_tempo", 57.287243, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 32501797, 425425, ";", ";", "#X", "insert", 1150, "_tempo", 79.13562, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 130474307, 1701700, ";", ";", "#X", "insert", 2220, "_tempo", 49.909237, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 18817137, 243100, ";", ";", "#X", "insert", 1320, "_tempo", 34.312748, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12017007, 154700, ";", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 26.0, 34.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-54", 0 ],
									"destination" : [ "obj-49", 0 ],
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
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-7", 0 ],
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
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-78", 0 ],
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
									"source" : [ "obj-78", 1 ],
									"destination" : [ "obj-82", 0 ],
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
									"source" : [ "obj-82", 0 ],
									"destination" : [ "obj-49", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 615.0, 576.0, 37.0, 18.0 ],
					"id" : "obj-102",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 351.0, 485.0, 48.0, 20.0 ],
					"id" : "obj-94",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /collect /play /open /pos",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"patching_rect" : [ 351.0, 402.0, 167.0, 20.0 ],
					"id" : "obj-90",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7101",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 351.0, 372.0, 99.0, 20.0 ],
					"id" : "obj-92",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 175.0, 119.0, 48.0, 20.0 ],
					"id" : "obj-87",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "generate",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 148.0, 187.0, 58.0, 18.0 ],
					"id" : "obj-70",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p clocks",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 216.0, 258.0, 54.0, 20.0 ],
					"id" : "obj-54",
					"fontname" : "Arial",
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
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 103.0, 249.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 102.0, 28.0, 25.0, 25.0 ],
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/pagepos clock",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 65.0, 197.0, 147.0, 18.0 ],
									"id" : "obj-76",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/_* clock",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 103.0, 167.0, 112.0, 18.0 ],
									"id" : "obj-83",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 103.0, 74.0, 20.0, 20.0 ],
									"id" : "obj-84"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tempo 120 1 96",
									"numinlets" : 4,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 103.0, 114.0, 94.0, 20.0 ],
									"id" : "obj-85",
									"fontname" : "Arial"
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
									"source" : [ "obj-85", 0 ],
									"destination" : [ "obj-76", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 155.5, 74.5, 155.5 ]
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
									"source" : [ "obj-84", 0 ],
									"destination" : [ "obj-85", 0 ],
									"hidden" : 0,
									"midpoints" : [ 112.5, 97.5, 112.5, 97.5 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/* del",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 62.0, 630.0, 94.0, 18.0 ],
					"id" : "obj-58",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 463.0, 608.0, 42.0, 20.0 ],
					"id" : "obj-80",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 427.0, 653.0, 74.0, 20.0 ],
					"id" : "obj-79",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "append 0",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 462.0, 576.0, 61.0, 20.0 ],
					"id" : "obj-77",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend timepair",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 462.0, 530.0, 101.0, 20.0 ],
					"id" : "obj-74",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "26902",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 350.0, 685.0, 46.5, 18.0 ],
					"id" : "obj-65",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"patching_rect" : [ 351.0, 597.0, 20.0, 20.0 ],
					"id" : "obj-64"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"presentation_rect" : [ 11.0, 491.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 381.0, 596.0, 20.0, 20.0 ],
					"presentation" : 1,
					"id" : "obj-63"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p openaudio",
					"numinlets" : 3,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "int" ],
					"patching_rect" : [ 321.0, 656.0, 77.0, 20.0 ],
					"id" : "obj-55",
					"fontname" : "Arial",
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
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 35.0, 213.0, 20.0, 20.0 ],
									"id" : "obj-10"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 35.0, 263.0, 25.0, 25.0 ],
									"id" : "obj-9",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "0",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 235.0, 172.0, 32.5, 18.0 ],
									"id" : "obj-8",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "counter",
									"numinlets" : 5,
									"fontsize" : 12.0,
									"numoutlets" : 4,
									"outlettype" : [ "int", "", "", "int" ],
									"patching_rect" : [ 174.0, 209.0, 73.0, 20.0 ],
									"id" : "obj-7",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "metro 10",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 174.0, 172.0, 58.0, 20.0 ],
									"id" : "obj-6",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"patching_rect" : [ 174.0, 25.0, 25.0, 25.0 ],
									"id" : "obj-4",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 257.0, 26.0, 25.0, 25.0 ],
									"id" : "obj-3",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "open",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 257.0, 92.0, 37.0, 18.0 ],
									"id" : "obj-33",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"patching_rect" : [ 70.0, 146.0, 45.0, 45.0 ],
									"id" : "obj-27"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "open",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 82.0, 61.0, 37.0, 18.0 ],
									"id" : "obj-82",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sfplay~",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "bang" ],
									"patching_rect" : [ 82.0, 101.0, 49.0, 20.0 ],
									"id" : "obj-79",
									"fontname" : "Arial",
									"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 174.0, 264.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 82.0, 27.0, 25.0, 25.0 ],
									"id" : "obj-1",
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [ 91.5, 57.0, 44.5, 57.0 ]
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
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-79", 0 ],
									"hidden" : 0,
									"midpoints" : [ 183.5, 89.0, 91.5, 89.0 ]
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
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [ 183.5, 110.5, 244.5, 110.5 ]
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
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [ 183.5, 128.5, 79.5, 128.5 ]
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
									"source" : [ "obj-79", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [ 266.5, 133.0, 79.5, 133.0 ]
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
									"source" : [ "obj-82", 0 ],
									"destination" : [ "obj-79", 0 ],
									"hidden" : 0,
									"midpoints" : [ 91.5, 95.0, 91.5, 95.0 ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open sound file",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"presentation_rect" : [ 3.0, 66.0, 92.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 321.0, 622.0, 92.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-57",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Open an audio file and and switch to \"Tempo map collection\" mode (right arrow). \nClick on 'collect' to start collecting the tempo map and next on the score in sync with the audio, at the corresponding locations. \nWhen finished, click 'collect' again to stop the audio and generate the tempo map. \nYou can test the synchronization using the 'Play' button.\nYou can open the tempo map cue list using the 'Open' button.",
					"linecount" : 8,
					"presentation_linecount" : 6,
					"numinlets" : 1,
					"fontsize" : 12.0,
					"presentation_rect" : [ 14.0, 321.0, 462.0, 89.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 779.0, 470.0, 362.0, 117.0 ],
					"presentation" : 1,
					"id" : "obj-46",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "2) Tempo map",
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 14.0,
					"presentation_rect" : [ 16.0, 293.0, 123.0, 23.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 727.0, 443.0, 185.0, 23.0 ],
					"presentation" : 1,
					"id" : "obj-44",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "1) Page turn",
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 14.0,
					"presentation_rect" : [ 13.0, 193.0, 123.0, 23.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 734.0, 308.0, 185.0, 23.0 ],
					"presentation" : 1,
					"id" : "obj-11",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay 10",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 216.0, 187.0, 56.0, 20.0 ],
					"id" : "obj-43",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 216.0, 214.0, 34.0, 20.0 ],
					"id" : "obj-37",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 171.0, 408.0, 67.0, 20.0 ],
					"id" : "obj-33",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route set",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 107.0, 366.0, 57.0, 20.0 ],
					"id" : "obj-32",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "dump",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 274.0, 260.0, 41.0, 18.0 ],
					"id" : "obj-7",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay 10",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 89.0, 186.0, 56.0, 20.0 ],
					"id" : "obj-10",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 89.0, 212.0, 37.0, 18.0 ],
					"id" : "obj-3",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Notes",
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 14.0,
					"presentation_rect" : [ 13.0, 416.0, 49.0, 23.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 738.0, 586.0, 111.0, 23.0 ],
					"presentation" : 1,
					"id" : "obj-30",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• The score is assumed to have the OSC address '/ITL/scene/score'.\n  You should edit the script manually to use another address.\n• Each time you click in a page, the location replaces the previous one.\n• Click to a non-timed location (e.g. outside a system) may lead to\n  unpredictable results.\n• In test mode, you can click to the score to move the cursor position.",
					"linecount" : 6,
					"presentation_linecount" : 6,
					"numinlets" : 1,
					"fontsize" : 12.0,
					"presentation_rect" : [ 71.0, 419.0, 402.0, 89.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 740.0, 620.0, 388.0, 89.0 ],
					"presentation" : 1,
					"id" : "obj-27",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 441.0, 253.0, 20.0, 20.0 ],
					"id" : "obj-22"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 441.0, 278.0, 37.0, 18.0 ],
					"id" : "obj-18",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "When done, click on open to get the INScore messages, which you can save to a file. The messages involve a hidden object named '_pageturner', and responsible to turn the pages. You should move this object in time by sending clock or date messages. ",
					"linecount" : 5,
					"presentation_linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 12.0,
					"presentation_rect" : [ 13.0, 236.0, 470.0, 48.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 780.0, 373.0, 351.0, 75.0 ],
					"presentation" : 1,
					"id" : "obj-26",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ],
					"patching_rect" : [ 89.0, 149.0, 34.0, 20.0 ],
					"id" : "obj-24",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 132.0, 111.0, 37.0, 18.0 ],
					"id" : "obj-20",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL load layout.inscore",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 548.0, 107.0, 134.0, 18.0 ],
					"id" : "obj-8",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "text",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 3,
					"outlettype" : [ "", "bang", "int" ],
					"patching_rect" : [ 107.0, 331.0, 46.0, 20.0 ],
					"id" : "obj-15",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend store",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 46.0, 109.0, 85.0, 20.0 ],
					"id" : "obj-9",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p openscore",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
					"patching_rect" : [ 549.0, 70.0, 77.0, 20.0 ],
					"id" : "obj-17",
					"fontname" : "Arial",
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
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 20.0, 307.0, 25.0, 25.0 ],
									"id" : "obj-5",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 19.0, 205.5, 20.0, 20.0 ],
									"id" : "obj-4"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 50.0, 53.0, 60.0, 20.0 ],
									"id" : "obj-3",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 159.0, 311.0, 25.0, 25.0 ],
									"id" : "obj-2",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 112.0, 26.0, 25.0, 25.0 ],
									"id" : "obj-1",
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/* del",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 244.0, 236.5, 94.0, 18.0 ],
									"id" : "obj-14",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 244.0, 200.5, 20.0, 20.0 ],
									"id" : "obj-11"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "conformpath native boot",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ],
									"patching_rect" : [ 50.0, 155.5, 139.0, 20.0 ],
									"id" : "obj-81",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 112.0, 91.5, 20.0, 20.0 ],
									"id" : "obj-80"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "set",
									"numinlets" : 2,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 91.5, 32.5, 18.0 ],
									"id" : "obj-76",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene/score set file",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 207.5, 185.0, 20.0 ],
									"id" : "obj-74",
									"fontname" : "Arial"
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "opendialog",
									"numinlets" : 1,
									"fontsize" : 12.0,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ],
									"patching_rect" : [ 50.0, 126.5, 77.0, 20.0 ],
									"id" : "obj-69",
									"fontname" : "Arial"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-1", 0 ],
									"destination" : [ "obj-80", 0 ],
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
									"source" : [ "obj-14", 0 ],
									"destination" : [ "obj-2", 0 ],
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
									"source" : [ "obj-69", 0 ],
									"destination" : [ "obj-81", 0 ],
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
									"source" : [ "obj-76", 0 ],
									"destination" : [ "obj-69", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
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
									"source" : [ "obj-81", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [ 59.5, 186.0, 253.5, 186.0 ]
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
 ]
					}
,
					"saved_object_attributes" : 					{
						"globalpatchername" : "",
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 12.0,
						"fontname" : "Arial"
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "autofit 1",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 17.0, 699.0, 53.0, 18.0 ],
					"id" : "obj-100",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read INScore.png",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 37.0, 723.0, 105.0, 18.0 ],
					"id" : "obj-99",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "fpic",
					"autofit" : 1,
					"numinlets" : 1,
					"presentation_rect" : [ 6.0, 100.0, 100.0, 89.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 34.0, 749.0, 86.0, 79.0 ],
					"pic" : "INScore.png",
					"presentation" : 1,
					"id" : "obj-98"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Click on the score to each location where you want the next page to be displayed.",
					"linecount" : 2,
					"numinlets" : 1,
					"fontsize" : 12.0,
					"presentation_rect" : [ 13.0, 215.0, 450.0, 20.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 780.0, 330.0, 351.0, 34.0 ],
					"presentation" : 1,
					"id" : "obj-91",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Basic principles",
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 18.0,
					"presentation_rect" : [ 101.0, 119.0, 155.0, 27.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 782.0, 221.0, 234.0, 27.0 ],
					"presentation" : 1,
					"id" : "obj-88",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "You should first open a Guido file. Then proceed in:\n1) collecting the page turn\n2) collecting the tempo map",
					"linecount" : 3,
					"presentation_linecount" : 3,
					"numinlets" : 1,
					"fontsize" : 12.0,
					"presentation_rect" : [ 101.0, 146.0, 363.0, 48.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 784.0, 257.0, 354.0, 48.0 ],
					"presentation" : 1,
					"id" : "obj-86",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open score",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"presentation_rect" : [ 13.0, 40.0, 70.0, 18.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 549.0, 36.0, 92.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-75",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 548.0, 155.0, 67.0, 20.0 ],
					"id" : "obj-73",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL rootPath",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 163.0, 632.0, 127.0, 20.0 ],
					"id" : "obj-34",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "int" ],
					"patching_rect" : [ 163.0, 604.0, 139.0, 20.0 ],
					"id" : "obj-35",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 113.0, 554.0, 34.0, 18.0 ],
					"id" : "obj-51",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 113.0, 579.0, 69.0, 20.0 ],
					"id" : "obj-53",
					"fontname" : "Arial",
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Initialization",
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 14.0,
					"numoutlets" : 0,
					"patching_rect" : [ 160.0, 500.0, 91.0, 23.0 ],
					"id" : "obj-56",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Reset",
					"numinlets" : 1,
					"fontsize" : 10.0,
					"presentation_rect" : [ 37.0, 10.0, 41.0, 18.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 27.0, 523.0, 41.0, 18.0 ],
					"presentation" : 1,
					"id" : "obj-59",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"numinlets" : 1,
					"presentation_rect" : [ 13.0, 8.0, 20.0, 20.0 ],
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 34.0, 497.0, 20.0, 20.0 ],
					"presentation" : 1,
					"id" : "obj-60"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 163.0, 662.0, 67.0, 20.0 ],
					"id" : "obj-61",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "bang", "bang" ],
					"patching_rect" : [ 72.0, 526.0, 59.5, 20.0 ],
					"id" : "obj-62",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 72.0, 497.0, 60.0, 20.0 ],
					"id" : "obj-67",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 19.0, 491.0, 293.0, 195.0 ],
					"id" : "obj-68"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "The page turner collects time points with the corresponding page numbers to generate the watch messages to automatically turn the page at the corresponding locations.\nThe tempo collector collects pairs of absolute and music time to generate a tempo map.",
					"linecount" : 5,
					"presentation_linecount" : 5,
					"numinlets" : 1,
					"fontsize" : 12.0,
					"presentation_rect" : [ 101.0, 46.0, 369.0, 75.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 783.0, 130.0, 339.0, 75.0 ],
					"presentation" : 1,
					"id" : "obj-31",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "INScore page turner and tempo collector.",
					"linecount" : 2,
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 20.0,
					"presentation_rect" : [ 82.0, 8.0, 404.0, 29.0 ],
					"numoutlets" : 0,
					"patching_rect" : [ 782.0, 75.0, 333.0, 52.0 ],
					"presentation" : 1,
					"id" : "obj-29",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "compile",
					"numinlets" : 2,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 466.0, 173.0, 52.0, 18.0 ],
					"id" : "obj-16",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r java",
					"numinlets" : 0,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 410.0, 172.0, 40.0, 20.0 ],
					"id" : "obj-6",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "js turns.js",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"patching_rect" : [ 410.0, 209.0, 61.0, 20.0 ],
					"id" : "obj-5",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 0,
					"patching_rect" : [ 47.0, 260.0, 42.0, 20.0 ],
					"id" : "obj-4",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /date /open /reset /test",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ],
					"patching_rect" : [ 46.0, 65.0, 191.0, 20.0 ],
					"id" : "obj-2",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7100",
					"numinlets" : 1,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 46.0, 35.0, 99.0, 20.0 ],
					"id" : "obj-1",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"fontface" : 1,
					"numinlets" : 1,
					"fontsize" : 14.0,
					"numoutlets" : 0,
					"patching_rect" : [ 323.0, 35.0, 158.0, 23.0 ],
					"id" : "obj-40",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _turnedit",
					"numinlets" : 0,
					"fontsize" : 12.0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 324.0, 66.0, 65.0, 20.0 ],
					"id" : "obj-39",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"numinlets" : 1,
					"fontsize" : 11.595187,
					"numoutlets" : 0,
					"patching_rect" : [ 324.0, 92.0, 136.0, 20.0 ],
					"id" : "obj-72",
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"numinlets" : 1,
					"numoutlets" : 0,
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"patching_rect" : [ 303.0, 24.0, 195.0, 103.0 ],
					"id" : "obj-47"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-110", 1 ],
					"destination" : [ "obj-111", 0 ],
					"hidden" : 0,
					"midpoints" : [ 326.5, 459.5, 326.5, 459.5 ]
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
					"source" : [ "obj-94", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-110", 0 ],
					"destination" : [ "obj-109", 0 ],
					"hidden" : 0,
					"midpoints" : [ 284.5, 458.5, 252.5, 458.5 ]
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
					"source" : [ "obj-2", 3 ],
					"destination" : [ "obj-106", 0 ],
					"hidden" : 0,
					"midpoints" : [ 184.5, 101.5, 239.5, 101.5 ]
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
					"source" : [ "obj-90", 1 ],
					"destination" : [ "obj-104", 0 ],
					"hidden" : 0,
					"midpoints" : [ 397.5, 431.5, 597.5, 431.5 ]
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
					"source" : [ "obj-103", 0 ],
					"destination" : [ "obj-105", 0 ],
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
					"source" : [ "obj-104", 0 ],
					"destination" : [ "obj-101", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-90", 2 ],
					"destination" : [ "obj-102", 0 ],
					"hidden" : 0,
					"midpoints" : [ 434.5, 431.0, 455.5, 431.0, 455.5, 431.0, 624.5, 431.0 ]
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
					"source" : [ "obj-97", 0 ],
					"destination" : [ "obj-101", 2 ],
					"hidden" : 0,
					"midpoints" : [ 667.5, 601.0, 625.5, 601.0 ]
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
					"source" : [ "obj-90", 0 ],
					"destination" : [ "obj-94", 0 ],
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
					"source" : [ "obj-92", 0 ],
					"destination" : [ "obj-90", 0 ],
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
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-54", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-87", 0 ],
					"destination" : [ "obj-70", 0 ],
					"hidden" : 0,
					"midpoints" : [ 184.5, 170.5, 157.5, 170.5 ]
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
					"source" : [ "obj-70", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 157.5, 253.0, 56.5, 253.0 ]
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
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [ 141.5, 249.5, 56.5, 249.5 ]
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
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-9", 0 ],
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
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [ 98.5, 103.0, 98.5, 103.0 ]
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
					"source" : [ "obj-62", 2 ],
					"destination" : [ "obj-58", 0 ],
					"hidden" : 0,
					"midpoints" : [ 108.5, 618.5, 71.5, 618.5 ]
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
					"source" : [ "obj-79", 0 ],
					"destination" : [ "obj-77", 0 ],
					"hidden" : 0,
					"midpoints" : [ 436.5, 682.0, 543.5, 682.0, 543.5, 567.0, 471.5, 567.0 ]
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
					"source" : [ "obj-74", 0 ],
					"destination" : [ "obj-77", 0 ],
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
					"source" : [ "obj-64", 0 ],
					"destination" : [ "obj-55", 1 ],
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
					"source" : [ "obj-57", 0 ],
					"destination" : [ "obj-55", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-37", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [ 240.5, 246.5, 283.5, 246.5 ]
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
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 98.5, 280.0, 116.5, 280.0 ]
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
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [ 616.5, 142.0, 557.5, 142.0 ]
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
					"source" : [ "obj-35", 0 ],
					"destination" : [ "obj-34", 0 ],
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
					"midpoints" : [ 172.5, 606.5, 172.5, 606.5 ]
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
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-100", 0 ],
					"hidden" : 0,
					"midpoints" : [ 81.5, 613.5, 26.5, 613.5 ]
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
					"source" : [ "obj-62", 1 ],
					"destination" : [ "obj-99", 0 ],
					"hidden" : 0,
					"midpoints" : [ 95.0, 603.0, 46.5, 603.0 ]
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
					"source" : [ "obj-75", 0 ],
					"destination" : [ "obj-17", 0 ],
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
					"source" : [ "obj-99", 0 ],
					"destination" : [ "obj-98", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [ 557.5, 139.5, 557.5, 139.5 ]
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
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 450.5, 319.0, 116.5, 319.0 ]
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
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [ 116.5, 366.0, 116.5, 366.0 ]
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
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 98.5, 171.5, 98.5, 171.5 ]
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
					"source" : [ "obj-6", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"source" : [ "obj-16", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [ 475.5, 199.5, 419.5, 199.5 ]
				}

			}
 ]
	}

}
