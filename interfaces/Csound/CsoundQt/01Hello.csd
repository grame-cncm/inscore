<CsoundSynthesizer>
<CsOptions>
-odac
</CsOptions>
<CsInstruments>
ksmps = 32
;seems to work just once - why?

;make sure INScore receives OSC messages on this port
giPort  =        7000

  instr Hello
;delete previous contents in /ITL/scene on localhost
Sdelmsg sprintf  "/ITL/scene/%s","*"
        OSCsend  1,"localhost", giPort, Sdelmsg, "s", "del"
;send text
        OSCsend  1,"localhost", giPort, "/ITL/scene/text", "sss", "set", "txt", "Hello Csound!"
;scale (enlarge)
        OSCsend  1,"localhost", giPort, "/ITL/scene/text", "sf", "scale", 5
        turnoff
  endin
</CsInstruments>
<CsScore>
i "Hello" 0 1
</CsScore>
</CsoundSynthesizer>



<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>138</x>
 <y>342</y>
 <width>440</width>
 <height>270</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>255</r>
  <g>170</g>
  <b>0</b>
 </bgcolor>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>25</x>
  <y>4</y>
  <width>383</width>
  <height>39</height>
  <uuid>{2b129b39-93ca-48a3-9a33-9dbabe9818ef}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>01Hello</label>
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
 <bsbObject version="2" type="BSBDisplay">
  <objectName>show_message</objectName>
  <x>25</x>
  <y>46</y>
  <width>383</width>
  <height>71</height>
  <uuid>{61f2f5b5-0237-4515-a60c-c8b9775d8e15}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Please start Inscore first. Then run this file and watch the Inscore panel.</label>
  <alignment>left</alignment>
  <font>Arial</font>
  <fontsize>20</fontsize>
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
  <bordermode>border</bordermode>
  <borderradius>1</borderradius>
  <borderwidth>1</borderwidth>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>25</x>
  <y>124</y>
  <width>383</width>
  <height>82</height>
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
