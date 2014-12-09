{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 0,
			"revision" : 3
		}
,
		"rect" : [ 25.0, 68.0, 593.0, 576.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
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
					"id" : "obj-6",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 272.0, 99.0, 240.0, 34.0 ],
					"presentation_rect" : [ 282.0, 78.0, 0.0, 0.0 ],
					"text" : "The message on the right is accepted by the text box. There is only a line less."
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"linecount" : 5,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 16.0, 57.0, 236.0, 76.0 ],
					"text" : "The message on the left triggers an error :\ntext: Invalid text handle or count\rIt looks like there is a limit of 1000 characters to send quoted strings to text box. "
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-4",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 35.0, 487.0, 37.0, 18.0 ],
					"text" : "open"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"linecount" : 22,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 272.0, 157.0, 244.0, 309.0 ],
					"text" : "\"( [917, 1083[ [873, 1365[ ) ( [0/2, 1/2[ )\n( [1083, 1279[ [873, 1365[ ) ( [1/2, 2/2[ )\n( [1279, 1433[ [873, 1365[ ) ( [2/2, 3/2[ )\n( [1433, 1617[ [873, 1365[ ) ( [3/2, 4/2[ )\n( [1617, 1777[ [873, 1365[ ) ( [4/2, 5/2[ )\n( [1777, 1980[ [873, 1365[ ) ( [5/2, 6/2[ )\n( [388, 622[ [2274, 2821[ ) ( [6/2, 7/2[ )\n( [622, 825[ [2274, 2821[ ) ( [7/2, 8/2[ )\n( [825, 1009[ [2274, 2821[ ) ( [8/2, 9/2[ )\n( [1009, 1218[ [2274, 2821[ ) ( [9/2, 10/2[ )\n( [1218, 1402[ [2274, 2821[ ) ( [10/2, 11/2[ )\n( [1402, 1710[ [2274, 2821[ ) ( [11/2, 12/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1888, 2066[ [2274, 2821[ ) ( [13/2, 14/2[ )\n( [2066, 2244[ [2274, 2821[ ) ( [14/2, 15/2[ )\n\""
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "bang", "int" ],
					"patching_rect" : [ 16.0, 531.0, 46.0, 20.0 ],
					"text" : "text"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-1",
					"linecount" : 23,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 16.0, 157.0, 244.0, 322.0 ],
					"text" : "\"( [917, 1083[ [873, 1365[ ) ( [0/2, 1/2[ )\n( [1083, 1279[ [873, 1365[ ) ( [1/2, 2/2[ )\n( [1279, 1433[ [873, 1365[ ) ( [2/2, 3/2[ )\n( [1433, 1617[ [873, 1365[ ) ( [3/2, 4/2[ )\n( [1617, 1777[ [873, 1365[ ) ( [4/2, 5/2[ )\n( [1777, 1980[ [873, 1365[ ) ( [5/2, 6/2[ )\n( [388, 622[ [2274, 2821[ ) ( [6/2, 7/2[ )\n( [622, 825[ [2274, 2821[ ) ( [7/2, 8/2[ )\n( [825, 1009[ [2274, 2821[ ) ( [8/2, 9/2[ )\n( [1009, 1218[ [2274, 2821[ ) ( [9/2, 10/2[ )\n( [1218, 1402[ [2274, 2821[ ) ( [10/2, 11/2[ )\n( [1402, 1710[ [2274, 2821[ ) ( [11/2, 12/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1710, 1888[ [2274, 2821[ ) ( [12/2, 13/2[ )\n( [1888, 2066[ [2274, 2821[ ) ( [13/2, 14/2[ )\n( [2066, 2244[ [2274, 2821[ ) ( [14/2, 15/2[ )\n\""
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-2", 0 ],
					"disabled" : 0,
					"hidden" : 0,
					"source" : [ "obj-4", 0 ]
				}

			}
 ],
		"dependency_cache" : [  ]
	}

}
