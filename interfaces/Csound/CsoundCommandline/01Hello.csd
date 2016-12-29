<CsoundSynthesizer>
<CsOptions>
-odac -+rtaudio=null
</CsOptions>
<CsInstruments>

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



