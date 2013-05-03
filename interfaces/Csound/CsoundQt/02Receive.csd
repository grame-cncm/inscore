<CsoundSynthesizer>
<CsOptions>
-odac -m128
</CsOptions>
<CsInstruments>

;set send and receive ports
giSendPort =          7000 ;from Csound to Inscore
giRecvPort =          7001 ;from Inscore to Csound
giErrPort  =          7002 ;error messages from Inscore

;initialize
giGetOut   OSCinit    giRecvPort
giGetErr   OSCinit    giErrPort

  instr InitMessage
           outvalue   "show_message", "Please watch the Inscore Panel!"
           turnoff
  endin

  instr ReceiveInscoreOutput
;delete previous contents in /ITL/scene on localhost
Sdelmsg    sprintf    "/ITL/scene/%s","*"
           OSCsend    1,"", giSendPort, Sdelmsg, "s", "del"
;send text
           OSCsend    1,"", giSendPort, "/ITL/scene/text", "sss", "set", "txt", "Drag file 'GetPorts.inscore'\nhere and watch\nCsound's output console!"
;scale (enlarge)
           OSCsend    1,"", giSendPort, "/ITL/scene/text", "sf", "scale", 4
gSmess     =          ""
;get message from inscore when file is dragged
kInPort, kOutPort, kErrPort init 0
kGotIt     OSClisten  giGetOut, "/ITL", "siii", gSmess, kInPort, kOutPort, kErrPort
;call subinstruments to continue
           schedkwhennamed kGotIt, 0, 1, "ShowOutputMessage", 0, p3, kInPort, kOutPort, kErrPort
           schedkwhennamed kGotIt, 0, 1, "ReceiveInscoreErrors", 0, p3, kInPort, kOutPort, kErrPort
;turn off this instrument
  if kGotIt == 1 then
           turnoff
  endif
  endin

  instr ShowOutputMessage
Smess      sprintf    "Message from Inscore:\nIP Address =  %s\nInput Port =  %d\nOutput Port =  %d\nError Port =  %d\n", gSmess, p4, p5, p6
           outvalue   "show_message", Smess
           puts       Smess, 1
           turnoff
  endin

  instr ReceiveInscoreErrors
;delete previous contents in /ITL/scene on localhost
Sdelmsg    sprintf    "/ITL/scene/%s","*"
           OSCsend    1,"", giSendPort, Sdelmsg, "s", "del"
;send new text
           OSCsend    1,"", giSendPort, "/ITL/scene/text", "sss", "set", "txt", "Now drag file\n'GetError.inscore'\nhere and watch\nCsound's output console!"
;scale (enlarge)
           OSCsend    1,"", giSendPort, "/ITL/scene/text", "sf", "scale", 4
gSerror1   =          ""
gSerror2   =          ""
kGotIt     OSClisten  giGetErr, "error:", "s", gSerror1
;call subinstrument to show error message
           schedkwhennamed kGotIt, 0, 1, "ShowErrorMessage", 0, p3
;turn off this instrument
  if kGotIt == 1 then
           turnoff
  endif
  endin
  
  instr ShowErrorMessage
Smess      sprintf    "Error message from Inscore:\n%s\n%s", gSerror1, gSerror2
           outvalue   "show_message", Smess
           puts       Smess, 1
           turnoff
  endin
  
</CsInstruments>
<CsScore>
i "InitMessage" 0 1
i "ReceiveInscoreOutput" 0 99999
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>30</y>
 <width>434</width>
 <height>268</height>
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
  <width>387</width>
  <height>38</height>
  <uuid>{2b129b39-93ca-48a3-9a33-9dbabe9818ef}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>02Receive</label>
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
  <width>386</width>
  <height>150</height>
  <uuid>{61f2f5b5-0237-4515-a60c-c8b9775d8e15}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label/>
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
  <y>213</y>
  <width>387</width>
  <height>53</height>
  <uuid>{bdd09977-80f2-47ed-9d2c-122d6cf1a388}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Note: Receiving the error message will probably not yet work in this version.</label>
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
</bsbPanel>
<bsbPresets>
</bsbPresets>
