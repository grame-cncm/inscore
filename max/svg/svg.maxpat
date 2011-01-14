{
	"patcher" : 	{
		"fileversion" : 1,
		"rect" : [ 1235.0, 149.0, 640.0, 480.0 ],
		"bglocked" : 0,
		"defrect" : [ 1235.0, 149.0, 640.0, 480.0 ],
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
		"boxes" : [ 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL/scene/svg set svg",
					"outlettype" : [ "" ],
					"patching_rect" : [ 65.0, 183.0, 177.0, 20.0 ],
					"fontsize" : 12.0,
					"id" : "obj-3",
					"numinlets" : 1,
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s osc",
					"patching_rect" : [ 65.0, 240.0, 39.0, 20.0 ],
					"fontsize" : 12.0,
					"id" : "obj-2",
					"numinlets" : 1,
					"numoutlets" : 0,
					"fontname" : "Arial"
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "\"<svg viewBox=\\\"0 0 20 20\\\" width=\\\"20px\\\" height=\\\"20px\\\" version=\\\"1.1\\\"> <circle cx=\\\"10\\\" cy=\\\"10\\\" r=\\\"8\\\" style=\\\"fill:#cccccc;\\\"/> </svg>\"",
					"linecount" : 2,
					"outlettype" : [ "" ],
					"patching_rect" : [ 65.0, 59.0, 556.0, 32.0 ],
					"fontsize" : 12.0,
					"id" : "obj-1",
					"numinlets" : 2,
					"numoutlets" : 1,
					"fontname" : "Arial"
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-3", 0 ],
					"destination" : [ "obj-2", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-1", 0 ],
					"destination" : [ "obj-3", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
 ]
	}

}
