<CsoundSynthesizer>
<CsOptions>
-odac -m128
</CsOptions>
<CsInstruments>

sr = 44100
ksmps = 32
nchnls = 2
0dbfs = 1
seed 0

giOscPort = 7000 ;inscore's default port for receiving OSC

opcode Scale, i, iiiii
 iVal, iInMin, iInMax, iOutMin, iOutMax xin
 iValOut = (((iOutMax - iOutMin) / (iInMax - iInMin)) * (iVal - iInMin)) + iOutMin
 xout iValOut
endop

instr Init
 OSCsend 1, "localhost", giOscPort, "/ITL/csound", "s", "new"
 OSCsend 1, "localhost", giOscPort, "/ITL/csound/*", "s", "del"
 gkSend metro 15
 indx = 0
 while indx < 10 do
  schedule "OneTone", 0, 1, indx
  indx += 1
 od
 schedule "Reverb", 0, p3
endin

instr OneTone
 ;generate tone and send to reverb
 iOct random 7,10
 iDb random -20,0
 iQ random 100,1000
 p3 = iQ/100
 aStrike butlp mpulse(ampdb(iDb), p3), cpsoct(iOct)
 aTone linen mode(aStrike, cpsoct(iOct), iQ), 0, p3, p3/2
 iPan random 0,1
 aL,aR pan2 aTone, iPan
 chnmix aL, "left"
 chnmix aR, "right"
 ;send OSC messages to Inscore
 S_address sprintf "/ITL/csound/point%d", p4
 iSizeX Scale iDb, -20, 0, .1, .3
 iY_rel Scale iQ, 100, 1000, .1, 2
 OSCsend 1, "localhost", giOscPort, S_address, "ssff", "set", "ellipse", iSizeX, iSizeX*iY_rel^2
 OSCsend 1, "localhost", giOscPort, S_address, "si", "red", Scale(iOct,7,10,0,256)
 OSCsend 1, "localhost", giOscPort, S_address, "si", "blue", Scale(iQ,100,1000,100,0)
 OSCsend 1, "localhost", giOscPort, S_address, "sf", "y", Scale(iOct,7,10,.7,-.7)
 OSCsend 1, "localhost", giOscPort, S_address, "sf", "x", Scale(iPan,0,1,-1,1)
 OSCsend gkSend, "localhost", giOscPort, S_address, "sf", "scale", line:k(1,p3,0)
 ;call a new instance of this ID
 schedule "OneTone", p3, 1, p4
endin

instr Reverb
 aL chnget "left"
 aR chnget "right"
 aLrv, aRrv reverbsc aL, aR, .7, sr/3
 out aL*.8+aLrv*.2, aR*.8+aRrv*.2
 chnclear "left"
 chnclear "right"
endin

schedule("Init",0,9999)

</CsInstruments>
<CsScore>
</CsScore>
</CsoundSynthesizer>

