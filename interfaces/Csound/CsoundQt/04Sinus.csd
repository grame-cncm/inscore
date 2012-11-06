<CsoundSynthesizer>
<CsOptions>
-odac -m128 
</CsOptions>
<CsInstruments>
ksmps = 128

;set send port
giSendPort =          7000 ;from Csound to Inscore

;a sine wave table
giSine     ftgen      0, 0, 1024, 10, 1

  instr RunIsFun
;initialise
           event_i    "i", "SetInit", 0, 1
           
;receive GUI input
gkFreq     invalue    "freq"
gkAmp      invalue    "amp"
kStart     invalue    "start"
ky         invalue    "y"
kt         invalue    "t"
kh         invalue    "h"
ks         invalue    "s"
kb         invalue    "b"
ka         invalue    "a"

;start / stop sinus according to gui input
kStartStop changed    kStart
  if kStartStop == 1 then
    if kStart == 1 then
           event      "i", "Sinus", 0, p3
           else
           turnoff2   "Sinus", 0, 0
    endif
  endif

;signal control change
kSigCC     changed    ky, kt, kh, ks, kb, ka
kTrig      init       0
  if kSigCC == 1 then
kTrig      =          kTrig + 1
    if ky == 1 then
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "ssfffff", "set", "y", 0.02, 0.001, 0.999, 0.999, 0.999
    elseif kt == 1 then
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "sfsffff", "set", 0.001, "t", 0.001, 0.999, 0.999, 0.999
    elseif kh == 1 then
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "sffsfff", "set", 0.001, 0.1, "h", 0.999, 0.999, 0.999
    elseif ks == 1 then
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "sfffsff", "set", 0.001, 0.1, 0.001, "s", 0.999, 0.999
    elseif kb == 1 then
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "sffffsf", "set", 0.001, 0.1, 0.001, 0.999, "b", 0.999
    elseif ka == 1 then
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "sfffffs", "set", 0.001, 0.1, 0.001, 0.999, 0.999, "a"
           else       ;reset
           OSCsend    kTrig, "", giSendPort, "/ITL/scene/signal/sig", "sffffff", "set", 0.001, 0.02, 0.001, 0.999, 0.999, 0.999
    endif
  endif
  endin

  instr SetInit
;load sinus.inscore file
SrootPath  pwd
           OSCsend    1,"", giSendPort, "/ITL", "ss", "rootPath", SrootPath
           OSCsend    1,"", giSendPort, "/ITL", "ss", "load", "sinus.inscore"
           turnoff2   "Sinus", 0, 0
           turnoff     
  endin

  instr Sinus
kSend      metro      20
kSin       oscili     gkAmp, gkFreq, giSine, -1
           OSCsend    kSend, "", giSendPort, "/ITL/scene/signal/[ythsba]", "f", kSin
  endin

</CsInstruments>
<CsScore>
i "RunIsFun" 0 99999
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>0</y>
 <width>412</width>
 <height>357</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="background">
  <r>255</r>
  <g>170</g>
  <b>0</b>
 </bgcolor>
 <bsbObject version="2" type="BSBVSlider">
  <objectName>freq</objectName>
  <x>160</x>
  <y>76</y>
  <width>20</width>
  <height>100</height>
  <uuid>{852b0e8c-48e5-4bea-99df-3bd823a22197}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>0.10000000</minimum>
  <maximum>1.00000000</maximum>
  <value>0.10000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBButton">
  <objectName>start</objectName>
  <x>26</x>
  <y>86</y>
  <width>100</width>
  <height>30</height>
  <uuid>{d7cf5685-5c4b-41cb-aacb-8b770b264553}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>value</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Start / Stop</text>
  <image>/</image>
  <eventLine>i1 0 10</eventLine>
  <latch>true</latch>
  <latched>false</latched>
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
  <label>04Sinus</label>
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
 <bsbObject version="2" type="BSBButton">
  <objectName/>
  <x>26</x>
  <y>127</y>
  <width>100</width>
  <height>30</height>
  <uuid>{df991322-6661-4a22-b60e-3d2d4e262ac4}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <type>event</type>
  <pressedValue>1.00000000</pressedValue>
  <stringvalue/>
  <text>Reload</text>
  <image>/</image>
  <eventLine>i "SetInit" 0 1</eventLine>
  <latch>false</latch>
  <latched>false</latched>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>146</x>
  <y>49</y>
  <width>45</width>
  <height>25</height>
  <uuid>{a8a3f320-f55a-4591-9d24-d49e7219ba01}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Freq</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBVSlider">
  <objectName>amp</objectName>
  <x>207</x>
  <y>76</y>
  <width>20</width>
  <height>100</height>
  <uuid>{7d97be35-a6b3-473d-bba5-3c889bf5a7f5}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <minimum>0.01000000</minimum>
  <maximum>1.00000000</maximum>
  <value>0.01000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>196</x>
  <y>49</y>
  <width>45</width>
  <height>25</height>
  <uuid>{cbb95c39-60d4-4a3d-a3b7-fccbf775aa47}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Amp</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBSpinBox">
  <objectName>freq</objectName>
  <x>144</x>
  <y>176</y>
  <width>49</width>
  <height>26</height>
  <uuid>{91a6a136-228d-40de-9205-4faa7d04ee01}</uuid>
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
  <resolution>0.01000000</resolution>
  <minimum>0.1</minimum>
  <maximum>10</maximum>
  <randomizable group="0">false</randomizable>
  <value>0.307</value>
 </bsbObject>
 <bsbObject version="2" type="BSBSpinBox">
  <objectName>amp</objectName>
  <x>192</x>
  <y>176</y>
  <width>49</width>
  <height>26</height>
  <uuid>{8897ea32-cdd3-4ed3-b250-db4687edc87a}</uuid>
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
  <resolution>0.01000000</resolution>
  <minimum>0.01</minimum>
  <maximum>1</maximum>
  <randomizable group="0">false</randomizable>
  <value>0.3664</value>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>293</x>
  <y>50</y>
  <width>110</width>
  <height>25</height>
  <uuid>{34d6b9fa-83c9-4b23-910e-b7b44479e40f}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>Signal Control</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>292</x>
  <y>77</y>
  <width>17</width>
  <height>25</height>
  <uuid>{8e280243-0d9c-4aff-9a45-44a3048c5804}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>y</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBCheckBox">
  <objectName>y</objectName>
  <x>291</x>
  <y>102</y>
  <width>20</width>
  <height>20</height>
  <uuid>{0ce1056d-6d96-4c3c-8160-338169c843df}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>312</x>
  <y>77</y>
  <width>17</width>
  <height>25</height>
  <uuid>{5d72731c-6877-4e70-acc1-c7a0c4f99f4b}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>t</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBCheckBox">
  <objectName>t</objectName>
  <x>311</x>
  <y>102</y>
  <width>20</width>
  <height>20</height>
  <uuid>{346ec645-ab19-4293-823a-e36b605ae3d4}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>332</x>
  <y>77</y>
  <width>17</width>
  <height>25</height>
  <uuid>{b39770d2-53b5-43f1-afa6-5b4e1fe367a9}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>h</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>352</x>
  <y>77</y>
  <width>17</width>
  <height>25</height>
  <uuid>{bebd2f28-7386-4ba9-bc26-f0e18e08893b}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>s</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>372</x>
  <y>77</y>
  <width>17</width>
  <height>25</height>
  <uuid>{bf90a0ca-d069-4e46-95e4-8b18775e1d17}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>b</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>392</x>
  <y>77</y>
  <width>17</width>
  <height>25</height>
  <uuid>{2035ccee-f074-40cd-8aa6-f778bd8d07c7}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <label>a</label>
  <alignment>center</alignment>
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
 <bsbObject version="2" type="BSBCheckBox">
  <objectName>h</objectName>
  <x>331</x>
  <y>102</y>
  <width>20</width>
  <height>20</height>
  <uuid>{a5632542-b272-4d24-ad87-ef4bcaab6f3c}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBCheckBox">
  <objectName>s</objectName>
  <x>351</x>
  <y>102</y>
  <width>20</width>
  <height>20</height>
  <uuid>{e9ed36d6-24b5-427c-9ceb-62e9d8ccba30}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBCheckBox">
  <objectName>b</objectName>
  <x>371</x>
  <y>102</y>
  <width>20</width>
  <height>20</height>
  <uuid>{3b6f260e-8bd4-4286-8bd4-338fa693e83e}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
 </bsbObject>
 <bsbObject version="2" type="BSBCheckBox">
  <objectName>a</objectName>
  <x>391</x>
  <y>102</y>
  <width>20</width>
  <height>20</height>
  <uuid>{5288c7b2-ad03-4ed4-a057-67bbb1712507}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>0</midicc>
  <selected>false</selected>
  <label/>
  <pressedValue>1</pressedValue>
  <randomizable group="0">false</randomizable>
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
  <label>Note: At present you can just see the effect of one checkbox.</label>
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
 <bsbObject version="2" type="BSBLabel">
  <objectName/>
  <x>27</x>
  <y>275</y>
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
