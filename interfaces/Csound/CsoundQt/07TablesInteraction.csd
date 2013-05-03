<CsoundSynthesizer>
<CsOptions>
-odac -m128 
</CsOptions>
<CsInstruments>
ksmps = 128
           seed       0

;set send port
giSendPort =          7000 ;from Csound to Inscore


  opcode TbToITL, 0, kSPjopppj
  ;let inscore show the kft function table with Sname
kft, Sname, kTrig, iThick, iHue, iSat, iBright, iTransp, iSendPort  xin

;standard OSC port for sending messages from Csound to Inscore is 7000
iSendPort  =          iSendPort == -1 ? 7000 : iSendPort

;standard thickness is 0.02
iThick     =          iThick == -1 ? 0.02 : iThick

;perform only if kTrig is positive
  if kTrig > 0 then
kTabLen    tableng    kft

;create panel for this table
SPanel     sprintfk   "/ITL/Table_%s", Sname
           OSCsend    1, "", giSendPort, SPanel, "s", "new"

;delete previous content if necessary
Sdelmsg    sprintfk   "%s/%s", SPanel, "*"
           OSCsend    1,"", giSendPort, Sdelmsg, "s", "del"

;set signal size (= ftable size)
SSignal    sprintfk   "%s/signal/table", SPanel
           OSCsend    1, "", giSendPort, SSignal, "si", "size", kTabLen

;send values to the ring buffer
kndx       =          0
sendToInscore:
kVal       tablekt    kndx, kft
           OSCsend    kndx, "", giSendPort, SSignal, "f", kVal * .99 ;looks nicer if scales to 99%
           loop_le    kndx, 1, kTabLen, sendToInscore

;create signal with table values as y values
Ssig       sprintfk   "%s/signal/sig", SPanel
           OSCsend    1, "", giSendPort, Ssig, "ssfffff", "set", "table", iThick, iHue, iSat, iBright, iTransp

;show signal as graph
Sshow      sprintfk   "%s/show_table", SPanel
           OSCsend    1, "", giSendPort, Sshow, "sss", "set", "graph", "sig"
           OSCsend    1, "", giSendPort, Sshow, "sf", "scale", 2
  endif

  endop
  
  
  instr Curve 
  
;get the form of the curve from the widget
kCurve     invalue    "curve"

;recalculate the table whenever a new value is received,
;and start an instrument which shows the new form
kNew       changed    kCurve
 if kNew == 1 then
           reinit     curve
 endif
curve:
iCurve     =          i(kCurve)
giTable    ftgen      0, 0, 257, 16, 1, 256, iCurve, -1
           event_i    "i", "Show", 0, 1
  endin

  instr Show
           TbToITL    giTable, "Curve"
           turnoff
  endin
  
</CsInstruments>
<CsScore>
i "Curve" 0 99999
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>273</x>
 <y>265</y>
 <width>413</width>
 <height>138</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>255</r>
  <g>170</g>
  <b>0</b>
 </bgcolor>
 <bsbObject version="2" type="BSBHSlider">
  <objectName>curve</objectName>
  <x>26</x>
  <y>50</y>
  <width>319</width>
  <height>31</height>
  <uuid>{852b0e8c-48e5-4bea-99df-3bd823a22197}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>-10.00000000</minimum>
  <maximum>10.00000000</maximum>
  <value>-2.53918495</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>25</x>
  <y>4</y>
  <width>387</width>
  <height>38</height>
  <uuid>{2b129b39-93ca-48a3-9a33-9dbabe9818ef}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>07TablesInteraction</label>
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
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>26</x>
  <y>85</y>
  <width>387</width>
  <height>53</height>
  <uuid>{bdd09977-80f2-47ed-9d2c-122d6cf1a388}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Start Csound and watch the /ITL/Table_Curve panel</label>
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
 <bsbObject version="2" type="BSBDisplay">
  <objectName>curve</objectName>
  <x>353</x>
  <y>50</y>
  <width>59</width>
  <height>32</height>
  <uuid>{66a4e189-4201-4dd1-97a8-141fd244a638}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>-2.539</label>
  <alignment>right</alignment>
  <font>Arial</font>
  <fontsize>16</fontsize>
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
<MacGUI>
ioView background {65535, 43690, 0}
ioSlider {26, 50} {319, 31} -10.000000 10.000000 -2.539185 curve
ioText {25, 4} {387, 38} label 0.000000 0.00100 "" center "Arial" 25 {0, 0, 0} {52736, 52736, 52736} nobackground noborder 07TablesInteraction
ioText {26, 85} {387, 53} label 0.000000 0.00100 "" left "Arial" 14 {0, 0, 0} {52736, 52736, 52736} nobackground noborder Start Csound and watch the /ITL/Table_Curve panel
ioText {353, 50} {59, 32} display -2.539000 0.00100 "curve" right "Arial" 16 {0, 0, 0} {52736, 52736, 52736} nobackground noborder -2.539
</MacGUI>
