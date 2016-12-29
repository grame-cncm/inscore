<CsoundSynthesizer>
<CsOptions>
-odac -m128 
</CsOptions>
<CsInstruments>
ksmps = 128
           seed       0

;set send port
giSendPort =          7000 ;from Csound to Inscore

;various tables
giSine     ftgen      0, 0, 1024, 10, 1
giRnd      ftgen      0, 0, -300, 21, 3

  opcode TbToITL, 0, kSPjopppj
  ;let inscore show the kft function table with Sname
  ;defaults: kTrig=1, iThick=0.02, iHue=0, iSat=1, iBright=1, iTransp=1
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
           OSCsend    1, "localhost", giSendPort, SPanel, "s", "new"

;delete previous content if necessary
Sdelmsg    sprintfk   "%s/%s", SPanel, "*"
           OSCsend    1,"localhost", giSendPort, Sdelmsg, "s", "del"

;set signal size (= ftable size)
SSignal    sprintfk   "%s/signal/table", SPanel
           OSCsend    1, "localhost", giSendPort, SSignal, "si", "size", kTabLen

;send values to the ring buffer
kndx       =          0
sendToInscore:
kVal       tablekt    kndx, kft
           OSCsend    kndx, "localhost", giSendPort, SSignal, "f", kVal * .99 ;looks nicer if scales to 99%
           loop_le    kndx, 1, kTabLen, sendToInscore

;create signal with table values as y values
Ssig       sprintfk   "%s/signal/sig", SPanel
           OSCsend    1, "localhost", giSendPort, Ssig, "ssfffff", "set", "table", iThick, iHue, iSat, iBright, iTransp

;show signal as graph
Sshow      sprintfk   "%s/show_table", SPanel
           OSCsend    1, "localhost", giSendPort, Sshow, "sss", "set", "graph", "sig"
           OSCsend    1, "localhost", giSendPort, Sshow, "sf", "scale", 2
  endif

  endop
  
  
  instr Sine ;default values
           TbToITL    giSine, "Sine"
           turnoff
  endin

  instr Rand ;different thickness and color
           TbToITL    giRnd, "Rand", 1, .04, -.5
           turnoff
  endin
  
  
</CsInstruments>
<CsScore>
i "Sine" 0 1
i "Rand" 1 1
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>121</x>
 <y>93</y>
 <width>449</width>
 <height>140</height>
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
  <y>10</y>
  <width>387</width>
  <height>38</height>
  <uuid>{2b129b39-93ca-48a3-9a33-9dbabe9818ef}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>06Tables</label>
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
