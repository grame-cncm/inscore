{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 1,
			"revision" : 10,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 38.0, 386.0, 1047.0, 558.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-34",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 139.401793999999995, 178.0, 81.0, 22.0 ],
					"text" : "loadmess 111"
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-33",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 139.401793999999995, 276.75, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-29",
					"maxclass" : "newobj",
					"numinlets" : 6,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 139.401793999999995, 247.75, 121.0, 22.0 ],
					"text" : "scale 0 127 -127. 18."
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "slider",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 139.401793999999995, 203.75, 120.0, 36.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 139.401793999999995, 304.5, 91.0, 22.0 ],
					"text" : "generalGain $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 369.401793999999995, 104.0, 150.0, 33.0 ],
					"text" : "<= ne pas oublier\nd'allumer ici"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-2",
					"linecount" : 2,
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 914.9375, 104.0, 150.0, 33.0 ],
					"text" : "<= ne pas oublier\nd'allumer ici"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-31",
					"maxclass" : "live.meter~",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "int" ],
					"patching_rect" : [ 129.0, 408.500010192394257, 5.0, 100.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-30",
					"maxclass" : "live.meter~",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "float", "int" ],
					"patching_rect" : [ 28.0, 408.500010192394257, 5.0, 100.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 309.401793999999995, 281.666670978069305, 150.0, 20.0 ],
					"text" : "RESET / EVT 1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-15",
					"linecount" : 5,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 826.000012695789337, 316.000003278255463, 107.0, 89.0 ],
					"text" : ";\rtoMT dStretch 0.8;\rtoMT hStretch 2.;\rtoMT hWin 22;\rtoMT fd13 0.4;\r"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-16",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 819.000012040138245, 281.666670978069305, 150.0, 20.0 ],
					"text" : "EVT 4"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-13",
					"linecount" : 3,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 649.000012695789337, 316.000003278255463, 107.0, 62.0 ],
					"text" : ";\rtoMT dStretch 0.7;\rtoMT hWin 24;\r"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-23",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 642.000012040138245, 281.666670978069305, 150.0, 20.0 ],
					"text" : "EVT 3"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"linecount" : 3,
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 474.000013589859009, 316.000003278255463, 114.0, 62.0 ],
					"text" : ";\rtoMT dStretch 0.75;\rtoMT hWin 22;\r"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 467.000012934207916, 281.666670978069305, 150.0, 20.0 ],
					"text" : "EVT 2"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-22",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 556.9375, 237.75, 150.0, 20.0 ],
					"text" : "EVENEMENTS"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-20",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 315.5, 326.0, 58.0, 22.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-18",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 1,
							"revision" : 10,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "box",
						"rect" : [ 59.0, 104.0, 640.0, 480.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-5",
									"linecount" : 387,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 103.0, 134.333332300186157, 144.0, 5210.0 ],
									"text" : ";\rtoMT d00 300;\rtoMT d01 425;\rtoMT d02 800;\rtoMT d03 925;\rtoMT d04 1300;\rtoMT d05 1800;\rtoMT d06 2050;\rtoMT d07 2300;\rtoMT d08 200;\rtoMT d09 500;\rtoMT d10 600;\rtoMT d11 1000;\rtoMT d12 3000;\rtoMT d13 2500;\rtoMT d14 700;\rtoMT d15 300;\rtoMT fd00 0.8;\rtoMT fd01 0.9;\rtoMT fd02 0.9;\rtoMT fd03 0.9;\rtoMT fd04 0.9;\rtoMT fd05 0.9;\rtoMT fd06 0.9;\rtoMT fd07 0.9;\rtoMT fd08 0.5;\rtoMT fd09 0.5;\rtoMT fd10 0.2;\rtoMT fd11 0.5;\rtoMT fd12 0.9;\rtoMT fd13 0.;\rtoMT fd14 0.9;\rtoMT fd15 0.9;\rtoMT tr00 386;\rtoMT tr01 772;\rtoMT tr02 -386;\rtoMT tr03 180;\rtoMT tr04 386;\rtoMT tr05 -772;\rtoMT tr06 -45;\rtoMT tr07 180;\rtoMT tr08 0;\rtoMT tr09 0;\rtoMT tr10 0;\rtoMT tr11 0;\rtoMT tr12 -500;\rtoMT tr13 50;\rtoMT tr14 -1000;\rtoMT tr15 -1200;\rtoMT xvd00 1;\rtoMT xvd01 1;\rtoMT xvd02 1;\rtoMT xvd03 1;\rtoMT xvd04 1;\rtoMT xvd05 1;\rtoMT xvd06 1;\rtoMT xvd07 1;\rtoMT xvd08 0;\rtoMT xvd09 0;\rtoMT xvd10 0;\rtoMT xvd11 0;\rtoMT xvd12 1;\rtoMT xvd13 1;\rtoMT xvd14 1;\rtoMT xvd15 1;\rtoMT inp00 0;\rtoMT inp01 0;\rtoMT inp02 0;\rtoMT inp03 0;\rtoMT inp04 0;\rtoMT inp05 0;\rtoMT inp06 0;\rtoMT inp07 0;\rtoMT inp08 1;\rtoMT inp09 1;\rtoMT inp10 1;\rtoMT inp11 1;\rtoMT inp12 1;\rtoMT inp13 1;\rtoMT inp14 0.5;\rtoMT inp15 1;\rtoMT out00 0.25;\rtoMT out01 0.3;\rtoMT out02 0.35;\rtoMT out03 0;\rtoMT out04 0.25;\rtoMT out05 0;\rtoMT out06 0.9;\rtoMT out07 0;\rtoMT out08 0;\rtoMT out09 0;\rtoMT out10 0;\rtoMT out11 0;\rtoMT out12 0.4;\rtoMT out13 0.4;\rtoMT out14 0.3;\rtoMT out15 0.3;\rtoMT dStretch 0.8;\rtoMT hStretch 4;\rtoMT hWin 24;\rtoMT smoothDuration 50;\rtoMT r000 1;\rtoMT r016 0;\rtoMT r032 0;\rtoMT r048 0;\rtoMT r064 0;\rtoMT r080 0;\rtoMT r096 0;\rtoMT r112 0;\rtoMT r128 0;\rtoMT r144 0;\rtoMT r160 0;\rtoMT r176 0;\rtoMT r192 0;\rtoMT r208 0;\rtoMT r224 0;\rtoMT r240 0;\rtoMT r001 0;\rtoMT r017 1;\rtoMT r033 0;\rtoMT r049 0;\rtoMT r065 0;\rtoMT r081 0;\rtoMT r097 0;\rtoMT r113 0;\rtoMT r129 0;\rtoMT r145 0;\rtoMT r161 0;\rtoMT r177 0;\rtoMT r193 0;\rtoMT r209 0;\rtoMT r225 0;\rtoMT r241 0;\rtoMT r002 0;\rtoMT r018 0;\rtoMT r034 1;\rtoMT r050 0;\rtoMT r066 0;\rtoMT r082 0;\rtoMT r098 0;\rtoMT r114 0;\rtoMT r130 0;\rtoMT r146 0;\rtoMT r162 0;\rtoMT r178 0;\rtoMT r194 0;\rtoMT r210 0;\rtoMT r226 0;\rtoMT r242 0;\rtoMT r003 0;\rtoMT r019 0;\rtoMT r035 0;\rtoMT r051 1;\rtoMT r067 0;\rtoMT r083 0;\rtoMT r099 0;\rtoMT r115 0;\rtoMT r131 0;\rtoMT r147 0;\rtoMT r163 0;\rtoMT r179 0;\rtoMT r195 0;\rtoMT r211 0;\rtoMT r227 0;\rtoMT r243 0;\rtoMT r004 0;\rtoMT r020 0;\rtoMT r036 0;\rtoMT r052 0;\rtoMT r068 1;\rtoMT r084 0;\rtoMT r100 0;\rtoMT r116 0;\rtoMT r132 0;\rtoMT r148 0;\rtoMT r164 0;\rtoMT r180 0;\rtoMT r196 0;\rtoMT r212 0;\rtoMT r228 0;\rtoMT r244 0;\rtoMT r005 0;\rtoMT r021 0;\rtoMT r037 0;\rtoMT r053 0;\rtoMT r069 0;\rtoMT r085 1;\rtoMT r101 0;\rtoMT r117 0;\rtoMT r133 0;\rtoMT r149 0;\rtoMT r165 0;\rtoMT r181 0;\rtoMT r197 0;\rtoMT r213 0;\rtoMT r229 0;\rtoMT r245 0;\rtoMT r006 0;\rtoMT r022 0;\rtoMT r038 0;\rtoMT r054 0;\rtoMT r070 0;\rtoMT r086 0;\rtoMT r102 1;\rtoMT r118 0;\rtoMT r134 0;\rtoMT r150 0;\rtoMT r166 0;\rtoMT r182 0;\rtoMT r198 0;\rtoMT r214 0;\rtoMT r230 0;\rtoMT r246 0;\rtoMT r007 0;\rtoMT r023 0;\rtoMT r039 0;\rtoMT r055 0;\rtoMT r071 0;\rtoMT r087 0;\rtoMT r103 0;\rtoMT r119 1;\rtoMT r135 0;\rtoMT r151 0;\rtoMT r167 0;\rtoMT r183 0;\rtoMT r199 0;\rtoMT r215 0;\rtoMT r231 0;\rtoMT r247 0;\rtoMT r008 1;\rtoMT r024 0;\rtoMT r040 0;\rtoMT r056 0;\rtoMT r072 1;\rtoMT r088 0;\rtoMT r104 0;\rtoMT r120 0;\rtoMT r136 1;\rtoMT r152 0;\rtoMT r168 0;\rtoMT r184 0;\rtoMT r200 0;\rtoMT r216 0;\rtoMT r232 0;\rtoMT r248 0;\rtoMT r009 0;\rtoMT r025 1;\rtoMT r041 0;\rtoMT r057 0;\rtoMT r073 0;\rtoMT r089 1;\rtoMT r105 0;\rtoMT r121 0;\rtoMT r137 0;\rtoMT r153 1;\rtoMT r169 0;\rtoMT r185 0;\rtoMT r201 0;\rtoMT r217 0;\rtoMT r233 0;\rtoMT r249 0;\rtoMT r010 0;\rtoMT r026 0;\rtoMT r042 1;\rtoMT r058 0;\rtoMT r074 0;\rtoMT r090 0;\rtoMT r106 1;\rtoMT r122 0;\rtoMT r138 0;\rtoMT r154 0;\rtoMT r170 1;\rtoMT r186 0;\rtoMT r202 0;\rtoMT r218 0;\rtoMT r234 0;\rtoMT r250 0;\rtoMT r011 0;\rtoMT r027 0;\rtoMT r043 0;\rtoMT r059 1;\rtoMT r075 0;\rtoMT r091 0;\rtoMT r107 0;\rtoMT r123 1;\rtoMT r139 0;\rtoMT r155 0;\rtoMT r171 0;\rtoMT r187 1;\rtoMT r203 0;\rtoMT r219 0;\rtoMT r235 0;\rtoMT r251 0;\rtoMT r012 0;\rtoMT r028 0;\rtoMT r044 0;\rtoMT r060 0;\rtoMT r076 0;\rtoMT r092 0;\rtoMT r108 0;\rtoMT r124 0;\rtoMT r140 0;\rtoMT r156 0;\rtoMT r172 0;\rtoMT r188 0;\rtoMT r204 0;\rtoMT r220 0;\rtoMT r236 0;\rtoMT r252 0;\rtoMT r013 1;\rtoMT r029 1;\rtoMT r045 1;\rtoMT r061 0;\rtoMT r077 1;\rtoMT r093 0;\rtoMT r109 1;\rtoMT r125 0;\rtoMT r141 0;\rtoMT r157 0;\rtoMT r173 0;\rtoMT r189 0;\rtoMT r205 1;\rtoMT r221 1;\rtoMT r237 1;\rtoMT r253 1;\rtoMT r014 0;\rtoMT r030 0;\rtoMT r046 0;\rtoMT r062 0;\rtoMT r078 0;\rtoMT r094 0;\rtoMT r110 0;\rtoMT r126 0;\rtoMT r142 0;\rtoMT r158 0;\rtoMT r174 0;\rtoMT r190 0;\rtoMT r206 0;\rtoMT r222 0;\rtoMT r238 0;\rtoMT r254 0;\rtoMT r015 0;\rtoMT r031 0;\rtoMT r047 0;\rtoMT r063 0;\rtoMT r079 0;\rtoMT r095 0;\rtoMT r111 0;\rtoMT r127 0;\rtoMT r143 0;\rtoMT r159 0;\rtoMT r175 0;\rtoMT r191 0;\rtoMT r207 0;\rtoMT r223 0;\rtoMT r239 0;\rtoMT r255 0;\rtoMT sp119 1;\rtoMT sp137 1;\rtoMT sp157 1;\rtoMT sp023 1;\rtoMT sp080 1;\rtoMT sp047 1;\rtoMT sp116 1;\rtoMT sp100 1;\rtoMT sp016 1;\rtoMT sp019 0;\rtoMT sp021 0;\rtoMT sp040 0;\rtoMT sp063 0;\rtoMT sp081 0;\rtoMT sp099 0;\rtoMT sp117 0;\rtoMT rotfreq3 0.;\rtoMT rotfreq2 0.8;\rtoMT rotfreq1 -0.4;\rtoMT rotfreq0 0.3;\rtoMT rotphase3 0.;\rtoMT rotphase2 0.;\rtoMT rotphase1 0.;\rtoMT rotphase0 0.;\rtoMT guitarGain -10.2;\rtoMT delharmoGain 0.;\rtoMT renv_trim 0.;\rtoMT renv_freq 13.;\rtoMT renv_short 0.5;\rtoMT generalGain 0.;\r"
								}

							}
, 							{
								"box" : 								{
									"comment" : "",
									"id" : "obj-1",
									"index" : 1,
									"maxclass" : "inlet",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "bang" ],
									"patching_rect" : [ 103.0, 52.0, 30.0, 30.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 315.5, 429.0, 34.0, 22.0 ],
					"saved_object_attributes" : 					{
						"description" : "",
						"digest" : "",
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p init"
				}

			}
, 			{
				"box" : 				{
					"format" : 6,
					"id" : "obj-38",
					"maxclass" : "flonum",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 831.0, 975.0, 50.0, 22.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-19",
					"maxclass" : "newobj",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 47.401794000000002, 194.75, 29.5, 22.0 ],
					"text" : "+~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-59",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 92.401793999999995, 304.5, 45.0, 22.0 ],
					"text" : "r toMT"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 3,
					"outlettype" : [ "signal", "signal", "list" ],
					"patching_rect" : [ 47.401794000000002, 367.0, 124.0, 22.0 ],
					"text" : "FilDeSoi1PanStereo~"
				}

			}
, 			{
				"box" : 				{
					"args" : [ "db2", "dcfilt2" ],
					"bgmode" : 0,
					"border" : 1,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-6",
					"lockeddragscroll" : 0,
					"maxclass" : "bpatcher",
					"name" : "abc.sfplay~.maxpat",
					"numinlets" : 2,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 522.9375, 99.0, 390.0, 51.0 ],
					"varname" : "abc.sfplay~",
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"args" : [ "adc1", "indb1", "dcfilt1" ],
					"bgmode" : 0,
					"border" : 1,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-26",
					"lockeddragscroll" : 0,
					"maxclass" : "bpatcher",
					"name" : "abc.adcinput~.maxpat",
					"numinlets" : 1,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 47.401794000000002, 99.0, 320.0, 51.0 ],
					"varname" : "abc.adcinput~",
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 18.0,
					"id" : "obj-9",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 697.0, 32.5, 120.0, 27.0 ],
					"text" : "Alain Bonardi"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 24.0,
					"id" : "obj-11",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 47.401794000000002, 26.5, 647.598206000000005, 33.0 ],
					"text" : "FIL DE SOI 1 - EVENEMENTS 1 A 4 - RAW PATCH"
				}

			}
, 			{
				"box" : 				{
					"fontsize" : 10.0,
					"id" : "obj-8",
					"maxclass" : "comment",
					"numinlets" : 1,
					"numoutlets" : 0,
					"patching_rect" : [ 339.0, 372.0, 34.0, 18.0 ],
					"text" : "reset"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-4",
					"maxclass" : "button",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 315.5, 369.0, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 51.973222571428565, 436.000010192394257, 45.0, 45.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"order" : 1,
					"source" : [ "obj-12", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"order" : 0,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-30", 0 ],
					"order" : 1,
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-31", 0 ],
					"order" : 0,
					"source" : [ "obj-12", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-29", 0 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"midpoints" : [ 56.901794000000002, 223.875, 56.901794000000002, 223.875 ],
					"source" : [ "obj-19", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"source" : [ "obj-20", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 0 ],
					"source" : [ "obj-26", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-33", 0 ],
					"source" : [ "obj-29", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-5", 0 ],
					"source" : [ "obj-33", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-34", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-18", 0 ],
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"midpoints" : [ 148.901793999999995, 349.75, 56.901794000000002, 349.75 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"midpoints" : [ 101.901793999999995, 349.75, 56.901794000000002, 349.75 ],
					"source" : [ "obj-59", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-19", 1 ],
					"midpoints" : [ 532.4375, 169.0, 67.401793999999995, 169.0 ],
					"source" : [ "obj-6", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-26::obj-2" : [ "live.gain~", "live.gain~", 0 ],
			"obj-6::obj-24" : [ "live.gain~[1]", "live.gain~", 0 ],
			"parameterbanks" : 			{

			}
,
			"parameter_overrides" : 			{
				"obj-6::obj-24" : 				{
					"parameter_longname" : "live.gain~[1]"
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "abc.adcinput~.maxpat",
				"bootpath" : "~/Desktop/FilDeSoi1_envoiGrameMars2021/max",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "abc.sfplay~.maxpat",
				"bootpath" : "~/Desktop/FilDeSoi1_envoiGrameMars2021/max",
				"patcherrelativepath" : ".",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "FilDeSoi1PanStereo~.mxo",
				"type" : "iLaX"
			}
 ],
		"autosave" : 0,
		"styles" : [ 			{
				"name" : "newobjBlue-1",
				"default" : 				{
					"accentcolor" : [ 0.317647, 0.654902, 0.976471, 1.0 ]
				}
,
				"parentstyle" : "",
				"multi" : 0
			}
, 			{
				"name" : "newobjGreen-1",
				"default" : 				{
					"accentcolor" : [ 0.0, 0.533333, 0.168627, 1.0 ]
				}
,
				"parentstyle" : "",
				"multi" : 0
			}
, 			{
				"name" : "newobjYellow-1",
				"default" : 				{
					"fontsize" : [ 12.059008 ],
					"accentcolor" : [ 0.82517, 0.78181, 0.059545, 1.0 ]
				}
,
				"parentstyle" : "",
				"multi" : 0
			}
 ]
	}

}
