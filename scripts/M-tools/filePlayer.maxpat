{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 442.0, 565.0, 388.0, 197.0 ],
		"bglocked" : 0,
		"defrect" : [ 442.0, 565.0, 388.0, 197.0 ],
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
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b s",
					"fontname" : "Arial",
					"numoutlets" : 2,
					"patching_rect" : [ 22.0, 46.0, 32.5, 20.0 ],
					"id" : "obj-2",
					"outlettype" : [ "bang", "" ],
					"fontsize" : 11.595187,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "stop",
					"fontname" : "Arial",
					"numoutlets" : 1,
					"patching_rect" : [ 275.0, 86.0, 33.0, 18.0 ],
					"id" : "obj-4",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"numinlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numoutlets" : 1,
					"patching_rect" : [ 275.0, 16.0, 25.0, 25.0 ],
					"id" : "obj-3",
					"outlettype" : [ "" ],
					"numinlets" : 0,
					"comment" : "Bang to stop"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "outlet",
					"numoutlets" : 0,
					"patching_rect" : [ 120.0, 161.0, 25.0, 25.0 ],
					"id" : "obj-1",
					"numinlets" : 1,
					"comment" : "Bang on end"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numoutlets" : 1,
					"patching_rect" : [ 162.0, 15.0, 25.0, 25.0 ],
					"id" : "obj-51",
					"outlettype" : [ "" ],
					"numinlets" : 0,
					"comment" : "Tempo"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "inlet",
					"numoutlets" : 1,
					"patching_rect" : [ 22.0, 17.0, 25.0, 25.0 ],
					"id" : "obj-50",
					"outlettype" : [ "" ],
					"numinlets" : 0,
					"comment" : "Filename"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend tempo",
					"fontname" : "Arial",
					"numoutlets" : 1,
					"patching_rect" : [ 163.0, 83.0, 91.0, 20.0 ],
					"id" : "obj-44",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend read",
					"fontname" : "Arial",
					"numoutlets" : 1,
					"patching_rect" : [ 78.0, 81.0, 82.0, 20.0 ],
					"id" : "obj-45",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"numinlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "qlist",
					"fontname" : "Arial",
					"numoutlets" : 3,
					"patching_rect" : [ 105.0, 128.0, 46.0, 20.0 ],
					"id" : "obj-46",
					"outlettype" : [ "", "bang", "bang" ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"save" : [ "#N", "qlist", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 0, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 50, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 100, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 150, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 180, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 200, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 220, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 250, 0, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 250, 50, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 250, 100, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 250, 150, 0, ";", ";", "#X", "insert", 50, "osc", "/ITL/scene", "color", 250, 180, 0, ";", ";" ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-2", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"midpoints" : [ 31.5, 114.0, 114.5, 114.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 1 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-46", 1 ],
					"destination" : [ "obj-1", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-51", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-45", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"midpoints" : [ 87.5, 112.0, 114.5, 112.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-44", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"midpoints" : [ 172.5, 112.0, 114.5, 112.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-4", 0 ],
					"destination" : [ "obj-46", 0 ],
					"hidden" : 0,
					"midpoints" : [ 284.5, 112.0, 114.5, 112.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-4", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
