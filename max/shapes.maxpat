{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 21.0, 459.0, 224.0, 157.0 ],
		"bglocked" : 0,
		"defrect" : [ 21.0, 459.0, 224.0, 157.0 ],
		"openrect" : [ 0.0, 0.0, 0.0, 0.0 ],
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
		"metadata" : [  ],
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "receive address",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"patching_rect" : [ 313.0, 276.0, 95.0, 20.0 ],
					"id" : "obj-14",
					"numinlets" : 0,
					"fontname" : "Arial",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /address",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"patching_rect" : [ 188.0, 278.0, 106.0, 20.0 ],
					"id" : "obj-44",
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "sprintf penColor %i %i %i",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"patching_rect" : [ 203.0, 194.0, 145.0, 20.0 ],
					"id" : "obj-10",
					"numinlets" : 3,
					"fontname" : "Arial",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Pen Color",
					"presentation_rect" : [ 95.0, 18.0, 68.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0,
					"patching_rect" : [ 152.0, 33.0, 74.0, 20.0 ],
					"id" : "obj-5",
					"presentation" : 1,
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "swatch",
					"outlettype" : [ "", "float" ],
					"presentation_rect" : [ 95.0, 57.0, 103.0, 68.0 ],
					"patching_rect" : [ 150.0, 58.0, 103.0, 68.0 ],
					"id" : "obj-40",
					"compatibility" : 1,
					"presentation" : 1,
					"numinlets" : 3,
					"numoutlets" : 2
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC Messages ",
					"fontface" : 1,
					"fontsize" : 12.0,
					"patching_rect" : [ 76.0, 230.0, 105.0, 20.0 ],
					"id" : "obj-37",
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend penWidth",
					"outlettype" : [ "" ],
					"fontsize" : 12.0,
					"patching_rect" : [ 225.0, 232.0, 109.0, 20.0 ],
					"id" : "obj-15",
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 1
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "send osc",
					"fontsize" : 12.0,
					"patching_rect" : [ 188.0, 310.0, 59.0, 20.0 ],
					"id" : "obj-42",
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"patching_rect" : [ 66.0, 187.0, 288.0, 75.0 ],
					"id" : "obj-45",
					"bgcolor" : [ 0.992157, 0.905882, 0.65098, 1.0 ],
					"rounded" : 24,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Pen Width",
					"presentation_rect" : [ 20.0, 18.0, 69.0, 20.0 ],
					"fontface" : 1,
					"fontsize" : 12.0,
					"patching_rect" : [ 70.0, 32.0, 71.0, 20.0 ],
					"id" : "obj-56",
					"presentation" : 1,
					"numinlets" : 1,
					"fontname" : "Arial",
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "slider",
					"outlettype" : [ "" ],
					"presentation_rect" : [ 40.0, 42.0, 20.0, 100.0 ],
					"mult" : 0.1,
					"min" : 0.1,
					"patching_rect" : [ 77.0, 57.0, 20.0, 100.0 ],
					"id" : "obj-62",
					"presentation" : 1,
					"numinlets" : 1,
					"floatoutput" : 1,
					"numoutlets" : 1,
					"size" : 100.0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"presentation_rect" : [ 10.0, 11.0, 204.0, 136.0 ],
					"patching_rect" : [ 60.0, 21.0, 206.0, 143.0 ],
					"id" : "obj-22",
					"presentation" : 1,
					"bgcolor" : [ 0.992157, 0.905882, 0.65098, 1.0 ],
					"rounded" : 24,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [ 322.5, 297.0, 295.0, 297.0, 295.0, 273.0, 197.5, 273.0 ]
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
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [ 234.5, 264.0, 197.5, 264.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 86.5, 216.0, 243.0, 216.0, 243.0, 228.0, 234.5, 228.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-40", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 159.5, 186.0, 212.5, 186.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-10", 0 ],
					"destination" : [ "obj-44", 0 ],
					"hidden" : 0,
					"midpoints" : [ 212.5, 219.0, 197.5, 219.0 ]
				}

			}
 ]
	}

}
