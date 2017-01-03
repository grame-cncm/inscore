<CsoundSynthesizer>
<CsOptions>
-odac -m128
</CsOptions>
<CsInstruments>
ksmps = 128

;make sure INScore receives OSC messages on this port
giSendPort =          7000

;refresh rate for view (Hz)
giRefresh  =          10

;who has been the last selected (for RandomShow)
gkLast     init       0

;random seed from internal clock
           seed       0

  opcode StrLineBreak, S, Si
;inserts line breaks after iNum characters in the input string
String, iNum xin
Sres       =          ""
loop:
ilen       strlen     String
 if ilen > iNum then
S1         strsub     String, 0, iNum
Sres       strcat     Sres, S1
Sres       strcat     Sres, "\n"
String     strsub     String, iNum
           igoto      loop
           else
Sres       strcat     Sres, String
 endif
           xout       Sres
  endop

  opcode DirUp, S, S
  ;returns the directory above the current directory
SCurDir    xin
;make sure the input does not end with '/'
ilen       strlen     SCurDir
ipos       strrindex  SCurDir, "/"
 if ipos == ilen-1 then
Sok        strsub     SCurDir, 0, ipos
 else	
Sok        strcpy     SCurDir
 endif
ipos       strrindex  Sok, "/"
SUpDir     strsub     Sok, 0, ipos
           xout       SUpDir
  endop


  instr RunForLive

;delete previous contents in /ITL/scene on localhost
Sdelmsg    sprintf    "/ITL/scene/%s","*"
           OSCsend    1,"localhost", giSendPort, Sdelmsg, "s", "del"

;set root path
Swd        pwd
gSrootPath DirUp      Swd
           OSCsend    1,"localhost", giSendPort, "/ITL", "ss", "rootPath", gSrootPath

;receive GUI input for transformations
gkScale    invalue    "scale"
gkX        invalue    "x"
gkY        invalue    "y"
gkAngle    invalue    "angle"
gkRotateX  invalue    "rotatex"
gkRotateY  invalue    "rotatey"
gkRotateZ  invalue    "rotatez"
gkShearX   invalue    "shearx"
gkShearY   invalue    "sheary"

;live input text
SText      invalue    "intext"
kBreakLines invalue   "breaklines"
kTextLen   strlenk    SText
kNewText   changed    kTextLen
ktimek     timek
  if ktimek > 1 then ;avoid triggering the Text instr at first k-cycle
    if kNewText == 1 then
      if kBreakLines == 1 then
           reinit     linebreak
linebreak:
gSText     StrLineBreak SText, 12
           rireturn
      else
gSText     strcpyk    SText
      endif
           event      "i", "Text", 0, 1
    endif
  endif

;select text, image or score
kText      invalue    "text"
kImage     invalue    "image"
kScore     invalue    "score"

;see if they have changed their status
kTextChng  changed    kText
kImageChng changed    kImage
kScoreChng changed    kScore

;activate or deactivate them via latch button
  if kTextChng == 1 then
    if kText == 1 then
           event      "i", "Text", 0, 1
    else
           event      "i", "TextDel", 0, 1
    endif
  endif
  if kImageChng == 1 then
    if kImage == 1 then
           event      "i", "Image", 0, 1
    else
           event      "i", "ImageDel", 0, 1
    endif
  endif
  if kScoreChng == 1 then
    if kScore == 1 then
           event      "i", "Score", 0, 1
    else
           event      "i", "ScoreDel", 0, 1
    endif
  endif

;send the transformations to the Transform instrument
kMetro     metro      giRefresh
  if kMetro == 1 then
    if kText == 1 then
           event      "i", "Transform", 0, 1, 1
    endif
    if kImage == 1 then
           event      "i", "Transform", 0, 1, 2
    endif
    if kScore == 1 then
           event      "i", "Transform", 0, 1, 3
    endif
  endif

;trigger or stop RandomShow instrument
kRandomShow invalue   "randomshow"
kRandShwChng changed  kRandomShow
  if kRandShwChng == 1 then
    if kRandomShow == 1 then
           event      "i", "RandomShow", 0, p3
    else
           turnoff2   "RandomShow", 0, 0
    endif
  endif

  endin

  instr Text
           OSCsend    1,"localhost", giSendPort, "/ITL/scene/txt", "sss", "set", "txt", gSText
gkLast     =          1
           turnoff
  endin

  instr TextDel
           OSCsend    1,"localhost", giSendPort, "/ITL/scene/txt", "s", "del"
           turnoff
  endin

  instr Image
           OSCsend    1,"localhost", giSendPort, "/ITL/scene/img", "sss", "set", "img", "./rsrc/csconf.jpg"
gkLast     =          2
           turnoff
  endin

  instr ImageDel
           OSCsend    1,"localhost", giSendPort, "/ITL/scene/img", "s", "del"
           turnoff
  endin

  instr Score
           OSCsend    1,"localhost", giSendPort, "/ITL/scene/sco", "sss", "set", "gmnf", "./rsrc/1voice-846_2f.gmn"
gkLast     =          3
           turnoff
  endin

  instr ScoreDel
           OSCsend    1,"localhost", giSendPort, "/ITL/scene/sco", "s", "del"
           turnoff
  endin

  instr Transform
iWhich     =          p4
  if iWhich == 1 then
Starget    =          "/ITL/scene/txt"
  elseif iWhich == 2 then
Starget    =          "/ITL/scene/img"
  elseif iWhich == 3 then
Starget    =          "/ITL/scene/sco"
  endif
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "scale", gkScale
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "x", gkX
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "y", gkY
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "angle", gkAngle
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "rotatex", gkRotateX
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "rotatey", gkRotateY
           OSCsend    1,"localhost", giSendPort, Starget, "sf", "rotatez", gkRotateZ
           OSCsend    1,"localhost", giSendPort, Starget, "sff", "shear", gkShearX, gkShearY
           turnoff
  endin

  instr Reset
           outvalue   "scale", 1
           outvalue   "x", 0
           outvalue   "y", 0
           outvalue   "angle", 0
           outvalue   "rotatex", 0
           outvalue   "rotatey", 0
           outvalue   "rotatez", 0
           outvalue   "shearx", 0
           outvalue   "sheary", 0
           turnoff
  endin

  instr RandomShow

;scale is different according to selected input
  ;text
  if gkLast == 1 then
kScaleMin  =          3
kScaleMax  =          7
  ;image
  elseif gkLast == 2 then
kScaleMin  =          .5
kScaleMax  =          2
  ;score
  else
kScaleMin  =          1
kScaleMax  =          3
  endif

;values independent from input
iXMin      =          -1
iXMax      =          1
iYMin      =          -1
iYMax      =          1
iRotXMin   =          -180
iRotXMax   =          180
iRotYMin   =          -180
iRotYMax   =          180
iRotZMin   =          -180
iRotZMax   =          180
iShXMin    =          -.5
iShXMax    =          .5
iShYMin    =          -.5
iShYMax    =          .5

;get previous state
iPrevScale chnget     "scale"
iPrevX     chnget     "x"
iPrevY     chnget     "y"
iPrevRotX  chnget     "rotatex"
iPrevRotY  chnget     "rotatey"
iPrevRotZ  chnget     "rotatez"
iPrevShX   chnget     "shearx"
iPrevShY   chnget     "sheary"

;calculate random movement
kScale     randomi    kScaleMin, kScaleMax, .1, 2, iPrevScale
kX         randomi    iXMin, iXMax, .2, 2, iPrevX
kY         randomi    iYMin, iYMax, .2, 2, iPrevY
kRotateX   randomi    iRotXMin, iRotXMax, .2, 2, iPrevRotX
kRotateY   randomi    iRotYMin, iRotYMax, .2, 2, iPrevRotY
kRotateZ   randomi    iRotZMin, iRotZMax, .2, 2, iPrevRotZ
kShearX    randomi    iShXMin, iShXMax, .1, 2, iPrevShX
kShearY    randomi    iShYMin, iShYMax, .1, 2, iPrevShY

;output values in refresh rate
kTrig      metro      giRefresh
  if kTrig == 1 then
           outvalue   "scale", kScale
           outvalue   "x", kX
           outvalue   "y", kY
           outvalue   "rotatex", kRotateX
           outvalue   "rotatey", kRotateY
           outvalue   "rotatez", kRotateZ
           outvalue   "shearx", kShearX
           outvalue   "sheary", kShearY
  endif
  endin

</CsInstruments>
<CsScore>
i "RunForLive" 0 99999
</CsScore>
</CsoundSynthesizer>

<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>0</y>
 <width>501</width>
 <height>607</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>255</r>
  <g>170</g>
  <b>0</b>
 </bgcolor>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>23</x>
  <y>4</y>
  <width>433</width>
  <height>39</height>
  <uuid>{2b129b39-93ca-48a3-9a33-9dbabe9818ef}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>05ShowAndTransform</label>
  <alignment>center</alignment>
  <font>Arial</font>
  <fontsize>25</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>155</y>
  <width>80</width>
  <height>25</height>
  <uuid>{f7a775f0-7895-4902-92b3-0ddcaead988e}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>scale</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>186</y>
  <width>80</width>
  <height>25</height>
  <uuid>{3f64ffac-a28e-49f7-a98a-49a7bdd6c937}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>x</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>217</y>
  <width>80</width>
  <height>28</height>
  <uuid>{ec0f69b7-e4a5-4c40-9fa8-7dbdf7e987a3}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>y</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>247</y>
  <width>80</width>
  <height>28</height>
  <uuid>{897e7634-bb2f-4c03-8805-778ebe3fdc4d}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>angle</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>278</y>
  <width>80</width>
  <height>25</height>
  <uuid>{9e23ac50-97c6-4efc-9f15-65251d8897f9}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>rotate x</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>rotatex</objectName>
  <x>378</x>
  <y>278</y>
  <width>79</width>
  <height>26</height>
  <uuid>{08b412a2-9c1d-48ec-a25d-396167834209}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-180</minimum>
  <maximum>180</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>304</y>
  <width>80</width>
  <height>25</height>
  <uuid>{a1afcbcd-d48f-43e8-90d6-24f82240792e}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>rotate y</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>rotatey</objectName>
  <x>378</x>
  <y>304</y>
  <width>79</width>
  <height>26</height>
  <uuid>{0a7ee821-af3c-4106-a9dc-25f3e8fd9f76}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-180</minimum>
  <maximum>180</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>330</y>
  <width>80</width>
  <height>25</height>
  <uuid>{3af119a6-5329-4d7b-85f1-eb6fc7a9e3d2}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>rotate z</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>rotatez</objectName>
  <x>378</x>
  <y>330</y>
  <width>79</width>
  <height>26</height>
  <uuid>{0eea33d9-09a6-4a99-a996-9924beaf27f0}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-180</minimum>
  <maximum>180</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>362</y>
  <width>80</width>
  <height>25</height>
  <uuid>{7354360b-2845-4b1c-9314-3cd5e10df89a}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>shear x</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>shearx</objectName>
  <x>378</x>
  <y>362</y>
  <width>79</width>
  <height>26</height>
  <uuid>{e0e38087-44cd-4c1a-a425-242cea52ce28}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-180</minimum>
  <maximum>180</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>24</x>
  <y>388</y>
  <width>80</width>
  <height>25</height>
  <uuid>{62631204-dce0-4d4e-88cc-4e47545f51c8}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>shear y</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>sheary</objectName>
  <x>378</x>
  <y>388</y>
  <width>79</width>
  <height>26</height>
  <uuid>{7d2248cf-0d08-45a1-979d-e93e947ef0d3}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-180</minimum>
  <maximum>180</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>scale</objectName>
  <x>380</x>
  <y>155</y>
  <width>79</width>
  <height>26</height>
  <uuid>{5421dce4-fe4a-40bd-9e3f-c31993df525d}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>0</minimum>
  <maximum>10</maximum>
  <randomizable group="0">false</randomizable>
  <value>1.66836</value>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>x</objectName>
  <x>378</x>
  <y>186</y>
  <width>79</width>
  <height>26</height>
  <uuid>{4f989918-dd11-48b4-8f34-64e4bff20963}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-10</minimum>
  <maximum>10</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>y</objectName>
  <x>378</x>
  <y>217</y>
  <width>79</width>
  <height>26</height>
  <uuid>{5fa7ebed-7cd2-4355-92a2-090b5339df6d}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-10</minimum>
  <maximum>10</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBSpinBox" version="2">
  <objectName>angle</objectName>
  <x>378</x>
  <y>247</y>
  <width>79</width>
  <height>26</height>
  <uuid>{8bb9ab6d-ad83-43f5-a2bd-134552aa2e76}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <resolution>0.00100000</resolution>
  <minimum>-180</minimum>
  <maximum>180</maximum>
  <randomizable group="0">false</randomizable>
  <value>0</value>
 </bsbObject>
 <bsbObject type="BSBButton" version="2">
  <objectName>button28</objectName>
  <x>307</x>
  <y>123</y>
  <width>150</width>
  <height>26</height>
  <uuid>{41a4804c-7e5e-493e-b389-5c19a5f638a5}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>event</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Reset all parameters</text>
  <image>/</image>
  <eventLine>i "Reset" 0 1</eventLine>
  <latch>false</latch>
  <latched>false</latched>
 </bsbObject>
 <bsbObject type="BSBButton" version="2">
  <objectName>text</objectName>
  <x>172</x>
  <y>87</y>
  <width>63</width>
  <height>30</height>
  <uuid>{e251ae93-0de9-4584-b53d-a5940c798c48}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>value</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Text</text>
  <image>/</image>
  <eventLine>i "ClearImage" 0 1</eventLine>
  <latch>true</latch>
  <latched>false</latched>
 </bsbObject>
 <bsbObject type="BSBButton" version="2">
  <objectName>image</objectName>
  <x>245</x>
  <y>87</y>
  <width>63</width>
  <height>30</height>
  <uuid>{dedd70d6-7b81-4e9a-a20c-f2b5a5d1f95a}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>value</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Image</text>
  <image>/</image>
  <eventLine>i "ClearImage" 0 1</eventLine>
  <latch>true</latch>
  <latched>false</latched>
 </bsbObject>
 <bsbObject type="BSBButton" version="2">
  <objectName>score</objectName>
  <x>316</x>
  <y>87</y>
  <width>63</width>
  <height>30</height>
  <uuid>{a8bba1ba-2e38-475f-b2ec-6bae48e23efd}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>value</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Score</text>
  <image>/</image>
  <eventLine>i "ClearImage" 0 1</eventLine>
  <latch>true</latch>
  <latched>false</latched>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>scale</objectName>
  <x>105</x>
  <y>156</y>
  <width>275</width>
  <height>24</height>
  <uuid>{d5a255d7-799d-43b4-bb87-84653ca0b94a}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>0.10000000</minimum>
  <maximum>2.00000000</maximum>
  <value>1.66836364</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>x</objectName>
  <x>105</x>
  <y>187</y>
  <width>275</width>
  <height>24</height>
  <uuid>{0f487aba-8cf2-4d98-9fc1-f47e91515234}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-1.00000000</minimum>
  <maximum>1.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>y</objectName>
  <x>105</x>
  <y>218</y>
  <width>275</width>
  <height>24</height>
  <uuid>{c7a3ca2e-d854-4d61-93b6-4b56369acfb5}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-1.00000000</minimum>
  <maximum>1.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>angle</objectName>
  <x>105</x>
  <y>248</y>
  <width>275</width>
  <height>24</height>
  <uuid>{76d5c3af-c535-4941-a5ee-4e84e36f6f42}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-180.00000000</minimum>
  <maximum>180.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>rotatex</objectName>
  <x>105</x>
  <y>279</y>
  <width>275</width>
  <height>24</height>
  <uuid>{73561d28-070d-41d2-a8cd-c8bb5793a3c5}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-180.00000000</minimum>
  <maximum>180.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>rotatey</objectName>
  <x>105</x>
  <y>305</y>
  <width>275</width>
  <height>24</height>
  <uuid>{69603777-bf5b-48ec-9091-aedbef348857}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-180.00000000</minimum>
  <maximum>180.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>rotatez</objectName>
  <x>105</x>
  <y>331</y>
  <width>275</width>
  <height>24</height>
  <uuid>{b50a3dc3-6ce5-41c7-b83e-4292a28f165e}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-180.00000000</minimum>
  <maximum>180.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>shearx</objectName>
  <x>105</x>
  <y>363</y>
  <width>275</width>
  <height>24</height>
  <uuid>{aa93b0b9-4ad1-4892-abc8-78fa13b75d4e}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-2.00000000</minimum>
  <maximum>2.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBHSlider" version="2">
  <objectName>sheary</objectName>
  <x>105</x>
  <y>389</y>
  <width>275</width>
  <height>24</height>
  <uuid>{6c9d468a-b4d8-46b3-b4c7-bdd0a83f630c}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-2.00000000</minimum>
  <maximum>2.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBLineEdit" version="2">
  <objectName>intext</objectName>
  <x>22</x>
  <y>49</y>
  <width>436</width>
  <height>31</height>
  <uuid>{80c4dafe-bfa2-40e6-9d42-3d2b7f31ed6a}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Type your text here </label>
  <alignment>left</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>239</r>
   <g>235</g>
   <b>231</b>
  </bgcolor>
  <background>nobackground</background>
 </bsbObject>
 <bsbObject type="BSBCheckBox" version="2">
  <objectName>breaklines</objectName>
  <x>23</x>
  <y>124</y>
  <width>20</width>
  <height>20</height>
  <uuid>{5db8a409-0a09-4eca-bedb-9f2775369563}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>43</x>
  <y>123</y>
  <width>154</width>
  <height>23</height>
  <uuid>{3989aae6-abc1-4875-bffd-7f6301441bfb}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>break lines in text input</label>
  <alignment>left</alignment>
  <font>Arial</font>
  <fontsize>12</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>22</x>
  <y>88</y>
  <width>146</width>
  <height>27</height>
  <uuid>{554cad8b-cdf5-4612-9c9a-6d4f3f4eaa4d}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Select what to show</label>
  <alignment>left</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBButton" version="2">
  <objectName>randomshow</objectName>
  <x>196</x>
  <y>123</y>
  <width>112</width>
  <height>26</height>
  <uuid>{04e5278a-1c60-4e71-a34e-2d7e9c296934}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>value</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Random Show</text>
  <image>/</image>
  <eventLine>i "ClearImage" 0 1</eventLine>
  <latch>true</latch>
  <latched>false</latched>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>23</x>
  <y>423</y>
  <width>435</width>
  <height>140</height>
  <uuid>{4b18f1f9-5fd6-4435-9a45-a425a7d8dba8}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Click on 'Text', 'Image' or 'Score' to see different examples for objects shown by Inscore. (The text input can be altered in real time.)
Move the sliders to transform the view.
Click on 'Random Show' for an example of automatic transformations.</label>
  <alignment>left</alignment>
  <font>Arial</font>
  <fontsize>14</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject type="BSBLabel" version="2">
  <objectName/>
  <x>-15</x>
  <y>570</y>
  <width>516</width>
  <height>37</height>
  <uuid>{acf74984-f17d-4f66-89e8-2b8e871ccc7a}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>PLEASE USE CSOUND 5.18 OR HIGHER!</label>
  <alignment>center</alignment>
  <font>Arial</font>
  <fontsize>25</fontsize>
  <precision>3</precision>
  <color>
   <r>0</r>
   <g>0</g>
   <b>0</b>
  </color>
  <bgcolor mode="nobackground">
   <r>255</r>
   <g>255</g>
   <b>255</b>
  </bgcolor>
  <bordermode>noborder</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
</bsbPanel>
<bsbPresets>
</bsbPresets>
