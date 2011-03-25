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
					"text" : "js",
					"id" : "obj-54",
					"fontname" : "Arial",
					"patching_rect" : [ 577.0, 313.0, 19.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-82",
					"patching_rect" : [ 747.0, 150.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-78",
					"patching_rect" : [ 854.0, 83.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/* del",
					"id" : "obj-58",
					"fontname" : "Arial",
					"patching_rect" : [ 58.0, 613.0, 94.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"id" : "obj-70",
					"fontname" : "Arial",
					"patching_rect" : [ 336.0, 555.0, 246.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _tempo",
					"id" : "obj-52",
					"fontname" : "Arial",
					"patching_rect" : [ 777.0, 121.0, 58.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "regexp",
					"id" : "obj-49",
					"fontname" : "Arial",
					"patching_rect" : [ 513.0, 506.0, 73.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 5,
					"outlettype" : [ "", "", "", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "print osc",
					"id" : "obj-90",
					"fontname" : "Arial",
					"patching_rect" : [ 292.0, 188.0, 56.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p tmap",
					"id" : "obj-89",
					"fontname" : "Arial",
					"patching_rect" : [ 855.0, 125.0, 47.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 3,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 1022.0, 354.0, 363.0, 347.0 ],
						"bglocked" : 0,
						"defrect" : [ 1022.0, 354.0, 363.0, 347.0 ],
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
									"maxclass" : "inlet",
									"id" : "obj-4",
									"patching_rect" : [ 103.0, 34.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-1",
									"patching_rect" : [ 202.0, 37.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"id" : "obj-87",
									"patching_rect" : [ 26.0, 145.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "stop",
									"id" : "obj-82",
									"fontname" : "Arial",
									"patching_rect" : [ 55.0, 147.0, 33.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"id" : "obj-78",
									"fontname" : "Arial",
									"patching_rect" : [ 26.0, 117.0, 48.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend set",
									"id" : "obj-54",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 155.0, 74.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "qlist",
									"id" : "obj-49",
									"fontname" : "Arial",
									"patching_rect" : [ 103.0, 190.0, 46.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "bang", "bang" ],
									"save" : [ "#N", "qlist", ";", "#X", "insert", 0, "_tempo", 2.469511, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 0, 1, ";", ";", "#X", "insert", 2940, "_tempo", 64.910164, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51479, 1701700, ";", ";", "#X", "insert", 1620, "_tempo", 76.598427, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 199267, 425425, ";", ";", "#X", "insert", 1760, "_tempo", 59.568695, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 35059, 34034, ";", ";", "#X", "insert", 1720, "_tempo", 80.726486, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 354203, 243100, ";", ";", "#X", "insert", 1670, "_tempo", 66.553375, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3435303, 1701700, ";", ";", "#X", "insert", 1580, "_tempo", 75.890366, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 29237, 11900, ";", ";", "#X", "insert", 1760, "_tempo", 49.423492, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5127937, 1701700, ";", ";", "#X", "insert", 1750, "_tempo", 110.386818, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1148239, 340340, ";", ";", "#X", "insert", 1480, "_tempo", 63.463284, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 313617, 77350, ";", ";", "#X", "insert", 1590, "_tempo", 75.716202, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1903761, 425425, ";", ";", "#X", "insert", 1650, "_tempo", 72.934128, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4250431, 850850, ";", ";", "#X", "insert", 1680, "_tempo", 78.847267, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 32761, 5950, ";", ";", "#X", "insert", 1700, "_tempo", 71.527054, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2580012, 425425, ";", ";", "#X", "insert", 1590, "_tempo", 86.544662, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 855879, 130900, ";", ";", "#X", "insert", 1670, "_tempo", 57.560066, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 867943, 121550, ";", ";", "#X", "insert", 1770, "_tempo", 89.408928, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12873583, 1701700, ";", ";", "#X", "insert", 1590, "_tempo", 69.938286, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6940779, 850850, ";", ";", "#X", "insert", 1660, "_tempo", 52.147423, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7352369, 850850, ";", ";", "#X", "insert", 1810, "_tempo", 69.841583, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 768699, 85085, ";", ";", "#X", "insert", 2370, "_tempo", 79.174248, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 8273809, 850850, ";", ";", "#X", "insert", 1760, "_tempo", 81.138184, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 626273, 60775, ";", ";", "#X", "insert", 2280, "_tempo", 53.534676, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4711834, 425425, ";", ";", "#X", "insert", 1840, "_tempo", 67.74456, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 19545769, 1701700, ";", ";", "#X", "insert", 4280, "_tempo", 76.351624, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5400403, 425425, ";", ";", "#X", "insert", 2360, "_tempo", 84.967484, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1759941, 130900, ";", ";", "#X", "insert", 1640, "_tempo", 62.000771, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1835943, 130900, ";", ";", "#X", "insert", 1860, "_tempo", 72.165184, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6171234, 425425, ";", ";", "#X", "insert", 5490, "_tempo", 83.691864, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 808649, 50050, ";", ";", "#X", "insert", 1110, "_tempo", 66.795341, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 42229127, 2552550, ";", ";", "#X", "insert", 2590, "_tempo", 74.3573, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 29379393, 1701700, ";", ";", "#X", "insert", 3260, "_tempo", 75.216255, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 100968, 5525, ";", ";", "#X", "insert", 3290, "_tempo", 65.73867, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 32852749, 1701700, ";", ";", "#X", "insert", 3570, "_tempo", 70.112556, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 17258389, 850850, ";", ";", "#X", "insert", 2570, "_tempo", 76.029167, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 78669, 3740, ";", ";", "#X", "insert", 1580, "_tempo", 91.524704, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 36646139, 1701700, ";", ";", "#X", "insert", 1470, "_tempo", 61.037086, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 37600093, 1701700, ";", ";", "#X", "insert", 1850, "_tempo", 70.584015, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5485819, 243100, ";", ";", "#X", "insert", 2440, "_tempo", 63.276505, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1981094, 85085, ";", ";", "#X", "insert", 2430, "_tempo", 65.394295, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10178029, 425425, ";", ";", "#X", "insert", 1690, "_tempo", 101.072021, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 41495723, 1701700, ";", ";", "#X", "insert", 1450, "_tempo", 72.873009, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 773361, 30940, ";", ";", "#X", "insert", 2110, "_tempo", 70.949898, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1558039, 60775, ";", ";", "#X", "insert", 2160, "_tempo", 65.771271, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4064701, 154700, ";", ";", "#X", "insert", 1640, "_tempo", 73.924034, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 22738259, 850850, ";", ";", "#X", "insert", 1820, "_tempo", 76.254242, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 20409, 748, ";", ";", "#X", "insert", 2300, "_tempo", 65.153351, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 23837013, 850850, ";", ";", "#X", "insert", 1770, "_tempo", 77.007706, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3730131, 130900, ";", ";", "#X", "insert", 3110, "_tempo", 76.825279, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 772151, 26180, ";", ";", "#X", "insert", 1720, "_tempo", 72.384087, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51126739, 1701700, ";", ";", "#X", "insert", 1560, "_tempo", 76.177971, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51927383, 1701700, ";", ";", "#X", "insert", 1640, "_tempo", 68.643791, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2031277, 65450, ";", ";", "#X", "insert", 1680, "_tempo", 86.60392, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2681544, 85085, ";", ";", "#X", "insert", 1520, "_tempo", 74.282257, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 13641062, 425425, ";", ";", "#X", "insert", 3700, "_tempo", 78.253708, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 8073287, 243100, ";", ";", "#X", "insert", 1090, "_tempo", 76.106308, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5192527, 154700, ";", ";", "#X", "insert", 1650, "_tempo", 61.988762, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 58008179, 1701700, ";", ";", "#X", "insert", 1720, "_tempo", 69.623077, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 14691041, 425425, ";", ";", "#X", "insert", 1730, "_tempo", 73.094627, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5961819, 170170, ";", ";", "#X", "insert", 1640, "_tempo", 80.582039, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1099421, 30940, ";", ";", "#X", "insert", 1610, "_tempo", 65.271202, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12277609, 340340, ";", ";", "#X", "insert", 1730, "_tempo", 70.984016, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 62188689, 1701700, ";", ";", "#X", "insert", 1760, "_tempo", 73.57766, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2252661, 60775, ";", ";", "#X", "insert", 1600, "_tempo", 61.88538, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 144591, 3850, ";", ";", "#X", "insert", 1890, "_tempo", 73.189362, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 9248363, 243100, ";", ";", "#X", "insert", 1510, "_tempo", 76.24781, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1008033, 26180, ";", ";", "#X", "insert", 1670, "_tempo", 64.629196, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 145989, 3740, ";", ";", "#X", "insert", 1710, "_tempo", 82.002312, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3953447, 100100, ";", ";", "#X", "insert", 1670, "_tempo", 62.087681, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1002641, 25025, ";", ";", "#X", "insert", 1780, "_tempo", 66.016479, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5304861, 130900, ";", ";", "#X", "insert", 1850, "_tempo", 69.68644, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 315969, 7700, ";", ";", "#X", "insert", 1530, "_tempo", 91.25164, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 70585131, 1701700, ";", ";", "#X", "insert", 1480, "_tempo", 63.89238, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10220387, 243100, ";", ";", "#X", "insert", 2670, "_tempo", 78.641899, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2139773, 50050, ";", ";", "#X", "insert", 2350, "_tempo", 64.049965, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5697127, 130900, ";", ";", "#X", "insert", 1880, "_tempo", 85.854507, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2675587, 60775, ";", ";", "#X", "insert", 1900, "_tempo", 79.107979, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1521461, 34034, ";", ";", "#X", "insert", 1640, "_tempo", 80.084534, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 3849647, 85085, ";", ";", "#X", "insert", 1560, "_tempo", 68.444412, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11125537, 243100, ";", ";", "#X", "insert", 1720, "_tempo", 75.551437, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5622391, 121550, ";", ";", "#X", "insert", 1590, "_tempo", 70.873093, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 79565223, 1701700, ";", ";", "#X", "insert", 2430, "_tempo", 65.856316, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2376069, 50050, ";", ";", "#X", "insert", 1970, "_tempo", 74.289024, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1257019, 26180, ";", ";", "#X", "insert", 1520, "_tempo", 100.105667, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 4125344, 85085, ";", ";", "#X", "insert", 1320, "_tempo", 71.186241, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 20860951, 425425, ";", ";", "#X", "insert", 1620, "_tempo", 68.225212, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 84261483, 1701700, ";", ";", "#X", "insert", 1860, "_tempo", 69.500473, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 85161249, 1701700, ";", ";", "#X", "insert", 1500, "_tempo", 86.020569, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 111559, 2210, ";", ";", "#X", "insert", 1570, "_tempo", 72.162605, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 86858007, 1701700, ";", ";", "#X", "insert", 1970, "_tempo", 87.605759, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 87865983, 1701700, ";", ";", "#X", "insert", 1190, "_tempo", 58.240623, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1611003, 30940, ";", ";", "#X", "insert", 1790, "_tempo", 75.773293, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 490903, 9350, ";", ";", "#X", "insert", 1620, "_tempo", 78.294617, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 45107357, 850850, ";", ";", "#X", "insert", 1930, "_tempo", 80.084282, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 91286137, 1701700, ";", ";", "#X", "insert", 1260, "_tempo", 71.018173, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 23000401, 425425, ";", ";", "#X", "insert", 1590, "_tempo", 85.589996, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 46401123, 850850, ";", ";", "#X", "insert", 1600, "_tempo", 99.727661, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 23443309, 425425, ";", ";", "#X", "insert", 1590, "_tempo", 57.482723, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 47448771, 850850, ";", ";", "#X", "insert", 3100, "_tempo", 65.704323, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 96161029, 1701700, ";", ";", "#X", "insert", 2380, "_tempo", 84.044456, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 6947843, 121550, ";", ";", "#X", "insert", 2650, "_tempo", 64.490913, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 24712241, 425425, ";", ";", "#X", "insert", 1690, "_tempo", 66.187195, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7115839, 121550, ";", ";", "#X", "insert", 3450, "_tempo", 75.48732, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 101240813, 1701700, ";", ";", "#X", "insert", 3310, "_tempo", 74.761475, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 51506223, 850850, ";", ";", "#X", "insert", 3310, "_tempo", 65.370827, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 26191761, 425425, ";", ";", "#X", "insert", 1870, "_tempo", 76.352478, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 68283, 1100, ";", ";", "#X", "insert", 2200, "_tempo", 80.939972, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 9711347, 154700, ";", ";", "#X", "insert", 1610, "_tempo", 71.225403, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 107748793, 1701700, ";", ";", "#X", "insert", 1630, "_tempo", 78.977768, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 27142993, 425425, ";", ";", "#X", "insert", 1560, "_tempo", 68.78717, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 109445549, 1701700, ";", ";", "#X", "insert", 1550, "_tempo", 72.936951, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 11020153, 170170, ";", ";", "#X", "insert", 2530, "_tempo", 88.850166, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 27877482, 425425, ";", ";", "#X", "insert", 1440, "_tempo", 73.479462, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 56208553, 850850, ";", ";", "#X", "insert", 1580, "_tempo", 71.830559, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 56620143, 850850, ";", ";", "#X", "insert", 2210, "_tempo", 70.286613, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 57182929, 850850, ";", ";", "#X", "insert", 2720, "_tempo", 98.205856, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 115721401, 1701700, ";", ";", "#X", "insert", 1370, "_tempo", 91.027687, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5833768, 85085, ";", ";", "#X", "insert", 1610, "_tempo", 75.508194, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 9054961, 130900, ";", ";", "#X", "insert", 1750, "_tempo", 60.063381, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 2281758, 32725, ";", ";", "#X", "insert", 3320, "_tempo", 59.712845, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 10915029, 154700, ";", ";", "#X", "insert", 3170, "_tempo", 73.189735, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 5518521, 77350, ";", ";", "#X", "insert", 1510, "_tempo", 91.296257, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 718771, 10010, ";", ";", "#X", "insert", 2000, "_tempo", 49.056923, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 123485727, 1701700, ";", ";", "#X", "insert", 1910, "_tempo", 86.900131, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 12415009, 170170, ";", ";", "#X", "insert", 1410, "_tempo", 85.738129, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 17859839, 243100, ";", ";", "#X", "insert", 1610, "_tempo", 62.050972, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 8590747, 116025, ";", ";", "#X", "insert", 1750, "_tempo", 80.84304, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 95075674, 1276275, ";", ";", "#X", "insert", 1600, "_tempo", 68.572754, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 95763527, 1276275, ";", ";", "#X", "insert", 1700, "_tempo", 69.988441, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 96383444, 1276275, ";", ";", "#X", "insert", 1660, "_tempo", 93.023277, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 129335029, 1701700, ";", ";", "#X", "insert", 1030, "_tempo", 63.876022, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 1181949, 15470, ";", ";", "#X", "insert", 1050, "_tempo", 63.626373, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 7675879, 100100, ";", ";", "#X", "insert", 3840, "_tempo", 29.941822, ";", ";", "#X", "insert", 0, "_turnedit", "/ITL/scene/_*", "date", 598291, 7700, ";", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-2",
									"patching_rect" : [ 26.0, 34.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"comment" : ""
								}

							}
 ],
						"lines" : [ 							{
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
									"destination" : [ "obj-54", 0 ],
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
									"source" : [ "obj-54", 0 ],
									"destination" : [ "obj-49", 0 ],
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
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "\"\n0 _tempo 2.4695112810358912;\n0 _turnedit /ITL/scene/_* date 0 1;\n2940 _tempo 64.91016608663669;\n0 _turnedit /ITL/scene/_* date 51479 1701700;\n1620 _tempo 76.59842830965823;\n0 _turnedit /ITL/scene/_* date 199267 425425;\n1760 _tempo 59.568693959938855;\n0 _turnedit /ITL/scene/_* date 35059 34034;\n1720 _tempo 80.72648732035834;\n0 _turnedit /ITL/scene/_* date 354203 243100;\n1670 _tempo 66.55337216766858;\n0 _turnedit /ITL/scene/_* date 3435303 1701700;\n1580 _tempo 75.89036631817372;\n0 _turnedit /ITL/scene/_* date 29237 11900;\n1760 _tempo 49.423490794919395;\n0 _turnedit /ITL/scene/_* date 5127937 1701700;\n1750 _tempo 110.38681509269745;\n0 _turnedit /ITL/scene/_* date 1148239 340340;\n1480 _tempo 63.46328477294069;\n0 _turnedit /ITL/scene/_* date 313617 77350;\n1590 _tempo 75.71619824026247;\n0 _turnedit /ITL/scene/_* date 1903761 425425;\n1650 _tempo 72.93412469883063;\n0 _turnedit /ITL/scene/_* date 4250431 850850;\n1680 _tempo 78.84727037668216;\n0 _turnedit /ITL/scene/_* date 32761 5950;\n1700 _tempo 71.52705230396685;\n0 _turnedit /ITL/scene/_* date 2580012 425425;\n1590 _tempo 86.54466350838295;\n0 _turnedit /ITL/scene/_* date 855879 130900;\n1670 _tempo 57.560067051592576;\n0 _turnedit /ITL/scene/_* date 867943 121550;\n1770 _tempo 89.40892625687297;\n0 _turnedit /ITL/scene/_* date 12873583 1701700;\n1590 _tempo 69.93828283693615;\n0 _turnedit /ITL/scene/_* date 6940779 850850;\n1660 _tempo 52.147423587137716;\n0 _turnedit /ITL/scene/_* date 7352369 850850;\n1810 _tempo 69.8415806085203;\n0 _turnedit /ITL/scene/_* date 768699 85085;\n2370 _tempo 79.17424821168136;\n0 _turnedit /ITL/scene/_* date 8273809 850850;\n1760 _tempo 81.13818070474424;\n0 _turnedit /ITL/scene/_* date 626273 60775;\n2280 _tempo 53.53467504362639;\n0 _turnedit /ITL/scene/_* date 4711834 425425;\n1840 _tempo 67.74455890453686;\n0 _turnedit /ITL/scene/_* date 19545769 1701700;\n4280 _tempo 76.35162444733743;\n0 _turnedit /ITL/scene/_* date 5400403 425425;\n2360 _tempo 84.9674858857067;\n0 _turnedit /ITL/scene/_* date 1759941 130900;\n1640 _tempo 62.000769628853185;\n0 _turnedit /ITL/scene/_* date 1835943 130900;\n1860 _tempo 72.16518614782846;\n0 _turnedit /ITL/scene/_* date 6171234 425425;\n5490 _tempo 83.69186722127881;\n0 _turnedit /ITL/scene/_* date 808649 50050;\n1110 _tempo 66.79534410626849;\n0 _turnedit /ITL/scene/_* date 42229127 2552550;\n2590 _tempo 74.35729914257523;\n0 _turnedit /ITL/scene/_* date 29379393 1701700;\n3260 _tempo 75.21625522698265;\n0 _turnedit /ITL/scene/_* date 100968 5525;\n3290 _tempo 65.73867062250685;\n0 _turnedit /ITL/scene/_* date 32852749 1701700;\n3570 _tempo 70.11255624668274;\n0 _turnedit /ITL/scene/_* date 17258389 850850;\n2570 _tempo 76.02916815128265;\n0 _turnedit /ITL/scene/_* date 78669 3740;\n1580 _tempo 91.52470578641048;\n0 _turnedit /ITL/scene/_* date 36646139 1701700;\n1470 _tempo 61.03708691944016;\n0 _turnedit /ITL/scene/_* date 37600093 1701700;\n1850 _tempo 70.58401579134484;\n0 _turnedit /ITL/scene/_* date 5485819 243100;\n2440 _tempo 63.276505629446675;\n0 _turnedit /ITL/scene/_* date 1981094 85085;\n2430 _tempo 65.39429244615444;\n0 _turnedit /ITL/scene/_* date 10178029 425425;\n1690 _tempo 101.07202331137394;\n0 _turnedit /ITL/scene/_* date 41495723 1701700;\n1450 _tempo 72.87300934359781;\n0 _turnedit /ITL/scene/_* date 773361 30940;\n2110 _tempo 70.94989977342921;\n0 _turnedit /ITL/scene/_* date 1558039 60775;\n2160 _tempo 65.77127320312394;\n0 _turnedit /ITL/scene/_* date 4064701 154700;\n1640 _tempo 73.92403330347712;\n0 _turnedit /ITL/scene/_* date 22738259 850850;\n1820 _tempo 76.25424192176126;\n0 _turnedit /ITL/scene/_* date 20409 748;\n2300 _tempo 65.15335113540493;\n0 _turnedit /ITL/scene/_* date 23837013 850850;\n1770 _tempo 77.0077057423379;\n0 _turnedit /ITL/scene/_* date 3730131 130900;\n3110 _tempo 76.82528142172485;\n0 _turnedit /ITL/scene/_* date 772151 26180;\n1720 _tempo 72.38408650173336;\n0 _turnedit /ITL/scene/_* date 51126739 1701700;\n1560 _tempo 76.17796837309011;\n0 _turnedit /ITL/scene/_* date 51927383 1701700;\n1640 _tempo 68.64379318160803;\n0 _turnedit /ITL/scene/_* date 2031277 65450;\n1680 _tempo 86.60392239339635;\n0 _turnedit /ITL/scene/_* date 2681544 85085;\n1520 _tempo 74.28225828225806;\n0 _turnedit /ITL/scene/_* date 13641062 425425;\n3700 _tempo 78.25370528015108;\n0 _turnedit /ITL/scene/_* date 8073287 243100;\n1090 _tempo 76.10631080149723;\n0 _turnedit /ITL/scene/_* date 5192527 154700;\n1650 _tempo 61.98876363035017;\n0 _turnedit /ITL/scene/_* date 58008179 1701700;\n1720 _tempo 69.62308008210745;\n0 _turnedit /ITL/scene/_* date 14691041 425425;\n1730 _tempo 73.09462417066433;\n0 _turnedit /ITL/scene/_* date 5961819 170170;\n1640 _tempo 80.58204126892483;\n0 _turnedit /ITL/scene/_* date 1099421 30940;\n1610 _tempo 65.27119938884675;\n0 _turnedit /ITL/scene/_* date 12277609 340340;\n1730 _tempo 70.98401598401608;\n0 _turnedit /ITL/scene/_* date 62188689 1701700;\n1760 _tempo 73.57765763648128;\n0 _turnedit /ITL/scene/_* date 2252661 60775;\n1600 _tempo 61.88537886016899;\n0 _turnedit /ITL/scene/_* date 144591 3850;\n1890 _tempo 73.18935836271115;\n0 _turnedit /ITL/scene/_* date 9248363 243100;\n1510 _tempo 76.24780995686281;\n0 _turnedit /ITL/scene/_* date 1008033 26180;\n1670 _tempo 64.62919948988096;\n0 _turnedit /ITL/scene/_* date 145989 3740;\n1710 _tempo 82.00230906817767;\n0 _turnedit /ITL/scene/_* date 3953447 100100;\n1670 _tempo 62.08768099052284;\n0 _turnedit /ITL/scene/_* date 1002641 25025;\n1780 _tempo 66.01647636941762;\n0 _turnedit /ITL/scene/_* date 5304861 130900;\n1850 _tempo 69.6864381293447;\n0 _turnedit /ITL/scene/_* date 315969 7700;\n1530 _tempo 91.25164183987602;\n0 _turnedit /ITL/scene/_* date 70585131 1701700;\n1480 _tempo 63.892379926749165;\n0 _turnedit /ITL/scene/_* date 10220387 243100;\n2670 _tempo 78.64189877706815;\n0 _turnedit /ITL/scene/_* date 2139773 50050;\n2350 _tempo 64.04996755434757;\n0 _turnedit /ITL/scene/_* date 5697127 130900;\n1880 _tempo 85.85450462849889;\n0 _turnedit /ITL/scene/_* date 2675587 60775;\n1900 _tempo 79.10797953839497;\n0 _turnedit /ITL/scene/_* date 1521461 34034;\n1640 _tempo 80.08453085376075;\n0 _turnedit /ITL/scene/_* date 3849647 85085;\n1560 _tempo 68.4444146824455;\n0 _turnedit /ITL/scene/_* date 11125537 243100;\n1720 _tempo 75.55144079006412;\n0 _turnedit /ITL/scene/_* date 5622391 121550;\n1590 _tempo 70.87309204956324;\n0 _turnedit /ITL/scene/_* date 79565223 1701700;\n2430 _tempo 65.85631746575305;\n0 _turnedit /ITL/scene/_* date 2376069 50050;\n1970 _tempo 74.28902366982825;\n0 _turnedit /ITL/scene/_* date 1257019 26180;\n1520 _tempo 100.10566973133889;\n0 _turnedit /ITL/scene/_* date 4125344 85085;\n1320 _tempo 71.18624295094884;\n0 _turnedit /ITL/scene/_* date 20860951 425425;\n1620 _tempo 68.2252093257781;\n0 _turnedit /ITL/scene/_* date 84261483 1701700;\n1860 _tempo 69.50047599459253;\n0 _turnedit /ITL/scene/_* date 85161249 1701700;\n1500 _tempo 86.02056617043628;\n0 _turnedit /ITL/scene/_* date 111559 2210;\n1570 _tempo 72.16260598165653;\n0 _turnedit /ITL/scene/_* date 86858007 1701700;\n1970 _tempo 87.60576052716344;\n0 _turnedit /ITL/scene/_* date 87865983 1701700;\n1190 _tempo 58.24062234183853;\n0 _turnedit /ITL/scene/_* date 1611003 30940;\n1790 _tempo 75.77328989093698;\n0 _turnedit /ITL/scene/_* date 490903 9350;\n1620 _tempo 78.29461608187599;\n0 _turnedit /ITL/scene/_* date 45107357 850850;\n1930 _tempo 80.08428546243748;\n0 _turnedit /ITL/scene/_* date 91286137 1701700;\n1260 _tempo 71.01817161750503;\n0 _turnedit /ITL/scene/_* date 23000401 425425;\n1590 _tempo 85.58999823705727;\n0 _turnedit /ITL/scene/_* date 46401123 850850;\n1600 _tempo 99.72766412278112;\n0 _turnedit /ITL/scene/_* date 23443309 425425;\n1590 _tempo 57.48272221137478;\n0 _turnedit /ITL/scene/_* date 47448771 850850;\n3100 _tempo 65.70432039537366;\n0 _turnedit /ITL/scene/_* date 96161029 1701700;\n2380 _tempo 84.04445277253247;\n0 _turnedit /ITL/scene/_* date 6947843 121550;\n2650 _tempo 64.49091458489293;\n0 _turnedit /ITL/scene/_* date 24712241 425425;\n1690 _tempo 66.18719388028829;\n0 _turnedit /ITL/scene/_* date 7115839 121550;\n3450 _tempo 75.48732056995762;\n0 _turnedit /ITL/scene/_* date 101240813 1701700;\n3310 _tempo 74.76147808118677;\n0 _turnedit /ITL/scene/_* date 51506223 850850;\n3310 _tempo 65.37082923368024;\n0 _turnedit /ITL/scene/_* date 26191761 425425;\n1870 _tempo 76.35248174285547;\n0 _turnedit /ITL/scene/_* date 68283 1100;\n2200 _tempo 80.93997343540711;\n0 _turnedit /ITL/scene/_* date 9711347 154700;\n1610 _tempo 71.22540397170359;\n0 _turnedit /ITL/scene/_* date 107748793 1701700;\n1630 _tempo 78.97776431713187;\n0 _turnedit /ITL/scene/_* date 27142993 425425;\n1560 _tempo 68.78716729191045;\n0 _turnedit /ITL/scene/_* date 109445549 1701700;\n1550 _tempo 72.93694912388209;\n0 _turnedit /ITL/scene/_* date 11020153 170170;\n2530 _tempo 88.85016943840672;\n0 _turnedit /ITL/scene/_* date 27877482 425425;\n1440 _tempo 73.47946171475405;\n0 _turnedit /ITL/scene/_* date 56208553 850850;\n1580 _tempo 71.83055964530608;\n0 _turnedit /ITL/scene/_* date 56620143 850850;\n2210 _tempo 70.28661649768883;\n0 _turnedit /ITL/scene/_* date 57182929 850850;\n2720 _tempo 98.20585597313952;\n0 _turnedit /ITL/scene/_* date 115721401 1701700;\n1370 _tempo 91.02768623411441;\n0 _turnedit /ITL/scene/_* date 5833768 85085;\n1610 _tempo 75.50819600567593;\n0 _turnedit /ITL/scene/_* date 9054961 130900;\n1750 _tempo 60.063380984713895;\n0 _turnedit /ITL/scene/_* date 2281758 32725;\n3320 _tempo 59.712846070240936;\n0 _turnedit /ITL/scene/_* date 10915029 154700;\n3170 _tempo 73.1897319665115;\n0 _turnedit /ITL/scene/_* date 5518521 77350;\n1510 _tempo 91.2962566844925;\n0 _turnedit /ITL/scene/_* date 718771 10010;\n2000 _tempo 49.05692398147024;\n0 _turnedit /ITL/scene/_* date 123485727 1701700;\n1910 _tempo 86.90013365858174;\n0 _turnedit /ITL/scene/_* date 12415009 170170;\n1410 _tempo 85.73812741879813;\n0 _turnedit /ITL/scene/_* date 17859839 243100;\n1610 _tempo 62.05097087786206;\n0 _turnedit /ITL/scene/_* date 8590747 116025;\n1750 _tempo 80.84303931362868;\n0 _turnedit /ITL/scene/_* date 95075674 1276275;\n1600 _tempo 68.5727559637603;\n0 _turnedit /ITL/scene/_* date 95763527 1276275;\n1700 _tempo 69.98843820955774;\n0 _turnedit /ITL/scene/_* date 96383444 1276275;\n1660 _tempo 93.02327598158541;\n0 _turnedit /ITL/scene/_* date 129335029 1701700;\n1030 _tempo 63.87602313652609;\n0 _turnedit /ITL/scene/_* date 1181949 15470;\n1050 _tempo 63.62637362637352;\n0 _turnedit /ITL/scene/_* date 7675879 100100;\n3840 _tempo 29.941822882999187;\n0 _turnedit /ITL/scene/_* date 598291 7700;\n\"",
					"linecount" : 534,
					"id" : "obj-76",
					"fontname" : "Arial",
					"patching_rect" : [ 155.0, 209.0, 165.0, 7373.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"id" : "obj-50",
					"fontname" : "Arial",
					"patching_rect" : [ 882.0, 90.0, 37.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "temporeset",
					"id" : "obj-48",
					"fontname" : "Arial",
					"patching_rect" : [ 429.0, 34.0, 71.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "tempomap",
					"id" : "obj-81",
					"fontname" : "Arial",
					"patching_rect" : [ 508.0, 19.0, 67.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"id" : "obj-80",
					"fontname" : "Arial",
					"patching_rect" : [ 392.0, 529.0, 42.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend set",
					"id" : "obj-79",
					"fontname" : "Arial",
					"patching_rect" : [ 427.0, 653.0, 74.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "append 0",
					"id" : "obj-77",
					"fontname" : "Arial",
					"patching_rect" : [ 391.0, 497.0, 61.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend timepair",
					"id" : "obj-74",
					"fontname" : "Arial",
					"patching_rect" : [ 391.0, 451.0, 101.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-71",
					"patching_rect" : [ 351.0, 556.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL load tempomap.inscore",
					"id" : "obj-69",
					"fontname" : "Arial",
					"patching_rect" : [ 320.0, 714.0, 159.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "27745",
					"id" : "obj-65",
					"fontname" : "Arial",
					"patching_rect" : [ 350.0, 685.0, 46.5, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-64",
					"patching_rect" : [ 351.0, 597.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-63",
					"patching_rect" : [ 381.0, 596.0, 20.0, 20.0 ],
					"presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 1,
					"presentation_rect" : [ 11.0, 491.0, 20.0, 20.0 ],
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p openaudio",
					"id" : "obj-55",
					"fontname" : "Arial",
					"patching_rect" : [ 321.0, 656.0, 77.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 3,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "int" ],
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
									"id" : "obj-10",
									"patching_rect" : [ 35.0, 213.0, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-9",
									"patching_rect" : [ 35.0, 263.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "0",
									"id" : "obj-8",
									"fontname" : "Arial",
									"patching_rect" : [ 235.0, 172.0, 32.5, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "counter",
									"id" : "obj-7",
									"fontname" : "Arial",
									"patching_rect" : [ 174.0, 209.0, 73.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 5,
									"numoutlets" : 4,
									"outlettype" : [ "int", "", "", "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "metro 10",
									"id" : "obj-6",
									"fontname" : "Arial",
									"patching_rect" : [ 174.0, 172.0, 58.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-4",
									"patching_rect" : [ 174.0, 25.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-3",
									"patching_rect" : [ 257.0, 26.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "open",
									"id" : "obj-33",
									"fontname" : "Arial",
									"patching_rect" : [ 257.0, 92.0, 37.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "ezdac~",
									"id" : "obj-27",
									"patching_rect" : [ 70.0, 146.0, 45.0, 45.0 ],
									"numinlets" : 2,
									"numoutlets" : 0
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "open",
									"id" : "obj-82",
									"fontname" : "Arial",
									"patching_rect" : [ 82.0, 61.0, 37.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "sfplay~",
									"id" : "obj-79",
									"fontname" : "Arial",
									"patching_rect" : [ 82.0, 101.0, 49.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "bang" ],
									"save" : [ "#N", "sfplay~", "", 1, 120960, 0, "", ";" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-2",
									"patching_rect" : [ 174.0, 264.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-1",
									"patching_rect" : [ 82.0, 27.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
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
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open sound file",
					"id" : "obj-57",
					"fontname" : "Arial",
					"patching_rect" : [ 321.0, 622.0, 92.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"presentation_rect" : [ 3.0, 66.0, 92.0, 18.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Open an audio file and click the play button.\nNext click on the score in sync with the audio, at the corresponding score locations. ",
					"linecount" : 3,
					"presentation_linecount" : 2,
					"id" : "obj-46",
					"fontname" : "Arial",
					"patching_rect" : [ 626.0, 746.0, 351.0, 48.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 14.0, 323.0, 469.0, 34.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "2) Tempo map",
					"id" : "obj-44",
					"fontname" : "Arial",
					"patching_rect" : [ 574.0, 719.0, 185.0, 23.0 ],
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 16.0, 295.0, 123.0, 23.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "1) Page turn",
					"id" : "obj-11",
					"fontname" : "Arial",
					"patching_rect" : [ 581.0, 584.0, 185.0, 23.0 ],
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 193.0, 123.0, 23.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay 10",
					"id" : "obj-43",
					"fontname" : "Arial",
					"patching_rect" : [ 287.0, 79.0, 56.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-42",
					"patching_rect" : [ 287.0, 23.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route 1",
					"id" : "obj-38",
					"fontname" : "Arial",
					"patching_rect" : [ 287.0, 50.0, 48.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"id" : "obj-45",
					"fontname" : "Arial",
					"patching_rect" : [ 460.0, 182.0, 42.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "generate",
					"id" : "obj-41",
					"fontname" : "Arial",
					"patching_rect" : [ 460.0, 142.0, 58.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b",
					"id" : "obj-37",
					"fontname" : "Arial",
					"patching_rect" : [ 287.0, 105.0, 34.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"id" : "obj-33",
					"fontname" : "Arial",
					"patching_rect" : [ 575.0, 257.0, 67.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route set",
					"id" : "obj-32",
					"fontname" : "Arial",
					"patching_rect" : [ 575.0, 226.0, 57.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "dump",
					"id" : "obj-7",
					"fontname" : "Arial",
					"patching_rect" : [ 301.0, 139.0, 41.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p starttest",
					"id" : "obj-36",
					"fontname" : "Arial",
					"patching_rect" : [ 834.0, 245.0, 63.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 25.0, 69.0, 602.0, 366.0 ],
						"bglocked" : 0,
						"defrect" : [ 25.0, 69.0, 602.0, 366.0 ],
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
									"text" : "prepend /ITL/scene load",
									"id" : "obj-11",
									"fontname" : "Arial",
									"patching_rect" : [ 359.0, 237.0, 140.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "setpos.inscore",
									"id" : "obj-10",
									"fontname" : "Arial",
									"patching_rect" : [ 359.0, 146.0, 88.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "setturn.inscore",
									"id" : "obj-9",
									"fontname" : "Arial",
									"patching_rect" : [ 379.0, 121.0, 89.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "255",
									"id" : "obj-8",
									"fontname" : "Arial",
									"patching_rect" : [ 184.0, 135.0, 32.5, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "0",
									"id" : "obj-7",
									"fontname" : "Arial",
									"patching_rect" : [ 220.0, 134.0, 32.5, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/startbutton blue $1",
									"id" : "obj-6",
									"fontname" : "Arial",
									"patching_rect" : [ 184.0, 222.0, 169.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route 1",
									"id" : "obj-5",
									"fontname" : "Arial",
									"patching_rect" : [ 35.0, 62.0, 48.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "t b b b",
									"id" : "obj-4",
									"fontname" : "Arial",
									"patching_rect" : [ 35.0, 95.0, 46.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "bang", "bang", "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-3",
									"patching_rect" : [ 35.0, 294.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-2",
									"patching_rect" : [ 35.0, 16.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/score page 1",
									"id" : "obj-1",
									"fontname" : "Arial",
									"patching_rect" : [ 38.0, 205.0, 139.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/_* date 0 1",
									"id" : "obj-33",
									"fontname" : "Arial",
									"patching_rect" : [ 24.0, 173.0, 128.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/pagepos date 0 1",
									"id" : "obj-32",
									"fontname" : "Arial",
									"patching_rect" : [ 10.0, 142.0, 163.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-6", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-7", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-8", 0 ],
									"destination" : [ "obj-6", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 1 ],
									"destination" : [ "obj-7", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-8", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 2 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 1 ],
									"destination" : [ "obj-33", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-4", 0 ],
									"destination" : [ "obj-32", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-32", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-33", 0 ],
									"destination" : [ "obj-3", 0 ],
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
									"source" : [ "obj-2", 0 ],
									"destination" : [ "obj-5", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-4", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-11", 0 ],
									"destination" : [ "obj-3", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-10", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-9", 0 ],
									"destination" : [ "obj-11", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 0 ],
									"destination" : [ "obj-10", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-5", 1 ],
									"destination" : [ "obj-9", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/pagepos clock",
					"id" : "obj-25",
					"fontname" : "Arial",
					"patching_rect" : [ 685.0, 256.0, 147.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL/scene/_* clock",
					"id" : "obj-14",
					"fontname" : "Arial",
					"patching_rect" : [ 723.0, 223.0, 112.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"id" : "obj-13",
					"fontname" : "Arial",
					"patching_rect" : [ 721.0, 321.0, 67.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "toggle",
					"id" : "obj-19",
					"patching_rect" : [ 723.0, 152.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "tempo 120 1 96",
					"id" : "obj-21",
					"fontname" : "Arial",
					"patching_rect" : [ 723.0, 192.0, 94.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 4,
					"numoutlets" : 1,
					"outlettype" : [ "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "delay 10",
					"id" : "obj-10",
					"fontname" : "Arial",
					"patching_rect" : [ 148.0, 135.0, 56.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open",
					"id" : "obj-3",
					"fontname" : "Arial",
					"patching_rect" : [ 148.0, 161.0, 37.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Note",
					"id" : "obj-30",
					"fontname" : "Arial",
					"patching_rect" : [ 587.0, 779.0, 111.0, 23.0 ],
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 397.0, 45.0, 23.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "• The score is assumed to have the OSC address '/ITL/scene/score'.\n  You should edit the script manually to use another address.\n• Each time you click in a page, the location replaces the previous one.\n• Click to a non-timed location (e.g. outside a system) may lead to\n  unpredictable results.\n• In test mode, you can click to the score to move the cursor position.",
					"linecount" : 6,
					"presentation_linecount" : 6,
					"id" : "obj-27",
					"fontname" : "Arial",
					"patching_rect" : [ 589.0, 813.0, 388.0, 89.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 71.0, 419.0, 402.0, 89.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-22",
					"patching_rect" : [ 606.0, 113.0, 20.0, 20.0 ],
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "clear",
					"id" : "obj-18",
					"fontname" : "Arial",
					"patching_rect" : [ 606.0, 138.0, 37.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "When done, click on open to get the INScore messages, which you can save to a file. The messages involve a hidden object named '_pageturner', and responsible to turn the pages. You should move this object in time by sending clock or date messages. ",
					"linecount" : 5,
					"presentation_linecount" : 3,
					"id" : "obj-26",
					"fontname" : "Arial",
					"patching_rect" : [ 627.0, 649.0, 351.0, 75.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 240.0, 470.0, 48.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b",
					"id" : "obj-24",
					"fontname" : "Arial",
					"patching_rect" : [ 148.0, 109.0, 34.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "reset",
					"id" : "obj-20",
					"fontname" : "Arial",
					"patching_rect" : [ 376.0, 101.0, 37.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "/ITL load pageturn.inscore",
					"id" : "obj-8",
					"fontname" : "Arial",
					"patching_rect" : [ 174.0, 760.0, 149.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p pagenum",
					"id" : "obj-12",
					"fontname" : "Arial",
					"patching_rect" : [ 738.0, 31.0, 71.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patcher" : 					{
						"fileversion" : 1,
						"rect" : [ 177.0, 363.0, 295.0, 273.0 ],
						"bglocked" : 0,
						"defrect" : [ 177.0, 363.0, 295.0, 273.0 ],
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
									"id" : "obj-1",
									"patching_rect" : [ 55.0, 181.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "tosymbol",
									"id" : "obj-26",
									"fontname" : "Arial",
									"patching_rect" : [ 54.0, 110.0, 59.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/pagenum set txt $1",
									"id" : "obj-27",
									"fontname" : "Arial",
									"patching_rect" : [ 54.0, 138.0, 172.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route page",
									"id" : "obj-21",
									"fontname" : "Arial",
									"patching_rect" : [ 54.0, 81.0, 68.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "route /ITL/scene/score",
									"id" : "obj-20",
									"fontname" : "Arial",
									"patching_rect" : [ 54.0, 52.0, 130.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "udpreceive 7001",
									"id" : "obj-19",
									"fontname" : "Arial",
									"patching_rect" : [ 54.0, 24.0, 99.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"source" : [ "obj-27", 0 ],
									"destination" : [ "obj-1", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-26", 0 ],
									"destination" : [ "obj-27", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-21", 0 ],
									"destination" : [ "obj-26", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-20", 0 ],
									"destination" : [ "obj-21", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
, 							{
								"patchline" : 								{
									"source" : [ "obj-19", 0 ],
									"destination" : [ "obj-20", 0 ],
									"hidden" : 0,
									"midpoints" : [  ]
								}

							}
 ]
					}
,
					"saved_object_attributes" : 					{
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "text",
					"id" : "obj-15",
					"fontname" : "Arial",
					"patching_rect" : [ 575.0, 173.0, 46.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "", "bang", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend store",
					"id" : "obj-9",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 152.0, 85.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"id" : "obj-23",
					"fontname" : "Arial",
					"patching_rect" : [ 738.0, 60.0, 67.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "p openscore",
					"id" : "obj-17",
					"fontname" : "Arial",
					"patching_rect" : [ 175.0, 723.0, 77.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "bang", "" ],
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
									"id" : "obj-5",
									"patching_rect" : [ 20.0, 307.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"id" : "obj-4",
									"patching_rect" : [ 19.0, 205.5, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "loadbang",
									"id" : "obj-3",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 53.0, 60.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "outlet",
									"id" : "obj-2",
									"patching_rect" : [ 159.0, 311.0, 25.0, 25.0 ],
									"numinlets" : 1,
									"numoutlets" : 0,
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "inlet",
									"id" : "obj-1",
									"patching_rect" : [ 112.0, 26.0, 25.0, 25.0 ],
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"comment" : ""
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "/ITL/scene/* del",
									"id" : "obj-14",
									"fontname" : "Arial",
									"patching_rect" : [ 244.0, 236.5, 94.0, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"id" : "obj-11",
									"patching_rect" : [ 244.0, 200.5, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "conformpath native boot",
									"id" : "obj-81",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 155.5, 139.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "int" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "button",
									"id" : "obj-80",
									"patching_rect" : [ 112.0, 91.5, 20.0, 20.0 ],
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "message",
									"text" : "set",
									"id" : "obj-76",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 91.5, 32.5, 18.0 ],
									"fontsize" : 12.0,
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "prepend /ITL/scene/score set file",
									"id" : "obj-74",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 207.5, 185.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ]
								}

							}
, 							{
								"box" : 								{
									"maxclass" : "newobj",
									"text" : "opendialog",
									"id" : "obj-69",
									"fontname" : "Arial",
									"patching_rect" : [ 50.0, 126.5, 77.0, 20.0 ],
									"fontsize" : 12.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "bang" ]
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
						"fontname" : "Arial",
						"default_fontname" : "Arial",
						"globalpatchername" : "",
						"default_fontsize" : 12.0,
						"fontface" : 0,
						"fontsize" : 12.0,
						"default_fontface" : 0
					}

				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "autofit 1",
					"id" : "obj-100",
					"fontname" : "Arial",
					"patching_rect" : [ 13.0, 682.0, 53.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "read INScore.png",
					"id" : "obj-99",
					"fontname" : "Arial",
					"patching_rect" : [ 33.0, 706.0, 105.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "fpic",
					"id" : "obj-98",
					"patching_rect" : [ 34.0, 749.0, 86.0, 79.0 ],
					"pic" : "INScore.png",
					"presentation" : 1,
					"numinlets" : 1,
					"autofit" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 6.0, 100.0, 100.0, 89.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Click on the score to each location where you want the next page to be displayed.",
					"linecount" : 2,
					"id" : "obj-91",
					"fontname" : "Arial",
					"patching_rect" : [ 627.0, 606.0, 351.0, 34.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 13.0, 215.0, 450.0, 20.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Basic principles",
					"id" : "obj-88",
					"fontname" : "Arial",
					"patching_rect" : [ 629.0, 497.0, 234.0, 27.0 ],
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 18.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 101.0, 119.0, 155.0, 27.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "You should first open a Guido file. Then proceed in:\n1) collecting the page turn\n2) collecting the tempo map",
					"linecount" : 3,
					"presentation_linecount" : 3,
					"id" : "obj-86",
					"fontname" : "Arial",
					"patching_rect" : [ 631.0, 533.0, 354.0, 48.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 101.0, 146.0, 363.0, 48.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "open score",
					"id" : "obj-75",
					"fontname" : "Arial",
					"patching_rect" : [ 175.0, 689.0, 92.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"presentation_rect" : [ 13.0, 40.0, 70.0, 18.0 ],
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"id" : "obj-73",
					"fontname" : "Arial",
					"patching_rect" : [ 232.0, 836.0, 67.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "prepend /ITL rootPath",
					"id" : "obj-34",
					"fontname" : "Arial",
					"patching_rect" : [ 159.0, 615.0, 127.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "conformpath native boot",
					"id" : "obj-35",
					"fontname" : "Arial",
					"patching_rect" : [ 159.0, 587.0, 139.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "int" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "path",
					"id" : "obj-51",
					"fontname" : "Arial",
					"patching_rect" : [ 109.0, 537.0, 34.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "thispatcher",
					"id" : "obj-53",
					"fontname" : "Arial",
					"patching_rect" : [ 109.0, 562.0, 69.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ],
					"save" : [ "#N", "thispatcher", ";", "#Q", "end", ";" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Initialization",
					"id" : "obj-56",
					"fontname" : "Arial",
					"patching_rect" : [ 156.0, 483.0, 91.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "Reset",
					"id" : "obj-59",
					"fontname" : "Arial",
					"patching_rect" : [ 23.0, 506.0, 41.0, 18.0 ],
					"presentation" : 1,
					"fontsize" : 10.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 37.0, 10.0, 41.0, 18.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "button",
					"id" : "obj-60",
					"patching_rect" : [ 30.0, 480.0, 20.0, 20.0 ],
					"presentation" : 1,
					"numinlets" : 1,
					"numoutlets" : 1,
					"presentation_rect" : [ 13.0, 8.0, 20.0, 20.0 ],
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s _turnedit",
					"id" : "obj-61",
					"fontname" : "Arial",
					"patching_rect" : [ 159.0, 645.0, 67.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "t b b b b",
					"id" : "obj-62",
					"fontname" : "Arial",
					"patching_rect" : [ 68.0, 509.0, 59.5, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "bang", "bang", "bang", "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "loadbang",
					"id" : "obj-67",
					"fontname" : "Arial",
					"patching_rect" : [ 68.0, 480.0, 60.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-68",
					"patching_rect" : [ 15.0, 474.0, 293.0, 195.0 ],
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "The page turner collects time points with the corresponding page numbers to generate the watch messages to automatically turn the page at the corresponding locations.\nThe tempo collector collects pairs of absolute and music time to generate a tempo map.",
					"linecount" : 5,
					"presentation_linecount" : 5,
					"id" : "obj-31",
					"fontname" : "Arial",
					"patching_rect" : [ 630.0, 406.0, 339.0, 75.0 ],
					"presentation" : 1,
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 101.0, 46.0, 369.0, 75.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "INScore page turner and tempo collector.",
					"linecount" : 2,
					"id" : "obj-29",
					"fontname" : "Arial",
					"patching_rect" : [ 629.0, 351.0, 333.0, 52.0 ],
					"presentation" : 1,
					"fontface" : 1,
					"fontsize" : 20.0,
					"numinlets" : 1,
					"numoutlets" : 0,
					"presentation_rect" : [ 82.0, 8.0, 404.0, 29.0 ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "\"/ITL/scene/_pageturner set \\\"txt\\\" \\\"page turner\\\"\n/ITL/scene/_pageturner watch\n/ITL/scene/_pageturner show 0\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 0 1 1175071 130900 \\\"/ITL/scene/score\\\" \\\"page\\\" 1\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 1175071 130900 1275101 75075 \\\"/ITL/scene/score\\\" \\\"page\\\" 2\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 1275101 75075 6314897 243100 \\\"/ITL/scene/score\\\" \\\"page\\\" 3\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 6314897 243100 14880037 425425 \\\"/ITL/scene/score\\\" \\\"page\\\" 4\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 14880037 425425 74835433 1701700 \\\"/ITL/scene/score\\\" \\\"page\\\" 5\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 74835433 1701700 22533482 425425 \\\"/ITL/scene/score\\\" \\\"page\\\" 6\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 22533482 425425 15064063 243100 \\\"/ITL/scene/score\\\" \\\"page\\\" 7\n/ITL/scene/_pageturner watch+ \\\"timeEnter\\\" 15064063 243100 10978523 154700 \\\"/ITL/scene/score\\\" \\\"page\\\" 8\"",
					"linecount" : 19,
					"id" : "obj-28",
					"fontname" : "Arial",
					"patching_rect" : [ 22.0, 237.0, 504.0, 267.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "message",
					"text" : "compile",
					"id" : "obj-16",
					"fontname" : "Arial",
					"patching_rect" : [ 626.0, 40.0, 52.0, 18.0 ],
					"fontsize" : 12.0,
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r java",
					"id" : "obj-6",
					"fontname" : "Arial",
					"patching_rect" : [ 575.0, 40.0, 40.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "js turns.js",
					"id" : "obj-5",
					"fontname" : "Arial",
					"patching_rect" : [ 575.0, 69.0, 61.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "s java",
					"id" : "obj-4",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 190.0, 42.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "route /date /open /reset /start /play /pos",
					"id" : "obj-2",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 66.0, 219.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 7,
					"outlettype" : [ "", "", "", "", "", "", "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpreceive 7100",
					"id" : "obj-1",
					"fontname" : "Arial",
					"patching_rect" : [ 46.0, 35.0, 99.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "comment",
					"text" : "OSC communication",
					"id" : "obj-40",
					"fontname" : "Arial",
					"patching_rect" : [ 34.0, 872.0, 158.0, 23.0 ],
					"fontface" : 1,
					"fontsize" : 14.0,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "r _turnedit",
					"id" : "obj-39",
					"fontname" : "Arial",
					"patching_rect" : [ 35.0, 903.0, 65.0, 20.0 ],
					"fontsize" : 12.0,
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ]
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "newobj",
					"text" : "udpsend 127.0.0.1 7000",
					"id" : "obj-72",
					"fontname" : "Arial",
					"patching_rect" : [ 35.0, 943.0, 136.0, 20.0 ],
					"fontsize" : 11.595187,
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
, 			{
				"box" : 				{
					"maxclass" : "panel",
					"id" : "obj-47",
					"patching_rect" : [ 14.0, 861.0, 196.0, 119.0 ],
					"bgcolor" : [ 0.878431, 0.94902, 0.839216, 1.0 ],
					"numinlets" : 1,
					"numoutlets" : 0
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-82", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-82", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-78", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-78", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-78", 0 ],
					"destination" : [ "obj-89", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-49", 0 ],
					"destination" : [ "obj-70", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-52", 0 ],
					"destination" : [ "obj-21", 1 ],
					"hidden" : 0,
					"midpoints" : [ 786.5, 187.0, 757.5, 187.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-76", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 6 ],
					"destination" : [ "obj-90", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 1 ],
					"destination" : [ "obj-89", 1 ],
					"hidden" : 0,
					"midpoints" : [ 626.5, 119.5, 878.5, 119.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-50", 0 ],
					"destination" : [ "obj-89", 2 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 1 ],
					"destination" : [ "obj-76", 1 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-81", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-16", 0 ],
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
					"midpoints" : [ 584.5, 178.5, 584.5, 178.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-5", 0 ],
					"destination" : [ "obj-28", 1 ],
					"hidden" : 0,
					"midpoints" : [ 584.5, 164.5, 516.5, 164.5 ]
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
					"midpoints" : [ 584.5, 106.0, 615.5, 106.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-48", 0 ],
					"destination" : [ "obj-5", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [ 385.5, 168.5, 469.5, 168.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-41", 0 ],
					"destination" : [ "obj-45", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 1 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [ 172.5, 133.5, 469.5, 133.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-24", 0 ],
					"destination" : [ "obj-10", 0 ],
					"hidden" : 0,
					"midpoints" : [ 157.5, 131.5, 157.5, 131.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-32", 0 ],
					"destination" : [ "obj-33", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-15", 0 ],
					"destination" : [ "obj-32", 0 ],
					"hidden" : 0,
					"midpoints" : [ 584.5, 219.0, 584.5, 219.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-7", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 310.5, 167.0, 584.5, 167.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-18", 0 ],
					"destination" : [ "obj-15", 0 ],
					"hidden" : 0,
					"midpoints" : [ 615.5, 163.0, 584.5, 163.0 ]
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
					"source" : [ "obj-20", 0 ],
					"destination" : [ "obj-28", 1 ],
					"hidden" : 0,
					"midpoints" : [ 385.5, 229.0, 516.5, 229.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-8", 0 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [ 183.5, 792.5, 241.5, 792.5 ]
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
					"midpoints" : [ 91.0, 586.0, 42.5, 586.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 3 ],
					"destination" : [ "obj-51", 0 ],
					"hidden" : 0,
					"midpoints" : [ 118.0, 537.0, 118.5, 537.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-62", 0 ],
					"destination" : [ "obj-100", 0 ],
					"hidden" : 0,
					"midpoints" : [ 77.5, 596.5, 22.5, 596.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-60", 0 ],
					"destination" : [ "obj-62", 0 ],
					"hidden" : 0,
					"midpoints" : [ 39.5, 502.0, 77.5, 502.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-53", 1 ],
					"destination" : [ "obj-35", 0 ],
					"hidden" : 0,
					"midpoints" : [ 168.5, 589.5, 168.5, 589.5 ]
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
					"midpoints" : [ 168.5, 639.5, 168.5, 639.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-17", 1 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-12", 0 ],
					"destination" : [ "obj-23", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
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
					"midpoints" : [ 157.5, 187.0, 275.0, 187.0, 275.0, 162.0, 584.5, 162.0 ]
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
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-21", 0 ],
					"hidden" : 0,
					"midpoints" : [ 732.5, 175.5, 732.5, 175.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-14", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-14", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-25", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-21", 0 ],
					"destination" : [ "obj-25", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-36", 0 ],
					"destination" : [ "obj-13", 0 ],
					"hidden" : 0,
					"midpoints" : [ 843.5, 292.5, 730.5, 292.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-19", 0 ],
					"destination" : [ "obj-36", 0 ],
					"hidden" : 0,
					"midpoints" : [ 732.5, 183.0, 843.5, 183.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-42", 0 ],
					"destination" : [ "obj-38", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 1 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [ 325.5, 92.5, 732.5, 92.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 1 ],
					"destination" : [ "obj-7", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-37", 0 ],
					"destination" : [ "obj-19", 0 ],
					"hidden" : 0,
					"midpoints" : [ 296.5, 130.0, 732.5, 130.0 ]
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
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-41", 0 ],
					"hidden" : 0,
					"midpoints" : [ 296.5, 75.0, 469.5, 75.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-38", 0 ],
					"destination" : [ "obj-43", 0 ],
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
					"source" : [ "obj-2", 1 ],
					"destination" : [ "obj-24", 0 ],
					"hidden" : 0,
					"midpoints" : [ 88.833336, 103.0, 157.5, 103.0 ]
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
					"midpoints" : [ 122.166664, 97.5, 385.5, 97.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 3 ],
					"destination" : [ "obj-42", 0 ],
					"hidden" : 0,
					"midpoints" : [ 155.5, 95.0, 272.75, 95.0, 272.75, 18.0, 296.5, 18.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-55", 0 ],
					"destination" : [ "obj-69", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-69", 0 ],
					"destination" : [ "obj-73", 0 ],
					"hidden" : 0,
					"midpoints" : [ 329.5, 821.0, 241.5, 821.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 4 ],
					"destination" : [ "obj-71", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-71", 0 ],
					"destination" : [ "obj-64", 0 ],
					"hidden" : 0,
					"midpoints" : [  ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-2", 5 ],
					"destination" : [ "obj-74", 0 ],
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
					"midpoints" : [ 388.5, 685.0, 416.5, 685.0, 416.5, 641.0, 436.5, 641.0 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-79", 0 ],
					"destination" : [ "obj-77", 0 ],
					"hidden" : 0,
					"midpoints" : [ 436.5, 682.0, 510.5, 682.0, 510.5, 486.0, 400.5, 486.0 ]
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
					"midpoints" : [ 104.5, 601.5, 67.5, 601.5 ]
				}

			}
, 			{
				"patchline" : 				{
					"source" : [ "obj-58", 0 ],
					"destination" : [ "obj-61", 0 ],
					"hidden" : 0,
					"midpoints" : [ 67.5, 638.0, 168.5, 638.0 ]
				}

			}
 ]
	}

}
