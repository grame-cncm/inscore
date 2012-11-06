<CsoundSynthesizer>
<CsOptions>
-odac -+rtaudio=null -m128
</CsOptions>
<CsInstruments>

;make sure INScore receives OSC messages on this port
giPort     =          7000

           turnon     "init"
           #include   "../strays.inc"

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

instr 1
Swd        pwd
gSrootPath DirUp      Swd
Smsg       strget     p4
Swho       StrayGetEl Smsg, 1 
iwho       nstrnum    Swho
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
           turnoff
endin

instr 2 ;for sync, e.g. "/ITL/scene/sync slave* guido"
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Sslave     StrayGetEl Smsg, 1
Smaster    StrayGetEl Smsg, 2
           OSCsend    1, "", giPort, Sdest, "ss", Sslave, Smaster
endin

instr 3 ;for sync, e.g. "/ITL/scene/sync slave* guido hv"
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Sslave     StrayGetEl Smsg, 1
Smaster    StrayGetEl Smsg, 2
Smode      StrayGetEl Smsg, 3
           OSCsend    1, "", giPort, Sdest, "sss", Sslave, Smaster, Smode
endin


instr demotime
ims = p4 ;value for pd metro (ms)
Smsg       sprintf    "/ITL/scene/slave%s","*"
ksend metro 1000/ims
           OSCsend    ksend, "", giPort, Smsg, "s", "clock"
endin

instr shape_dangle
ksend metro 100
           OSCsend    ksend, "", giPort, "/ITL/scene/shape*", "sf", "dangle", .99
endin

instr is_dangle
ksend metro 100
           OSCsend    ksend, "", giPort, "/ITL/scene/[is]*", "sf", "dangle", .99
endin

instr all_dangle_scale
Smsg       sprintf    "/ITL/scene/%s","*"
ksend metro 1000/11
           OSCsend    ksend, "", giPort, Smsg, "sf", "dangle", .99
           OSCsend    ksend, "", giPort, Smsg, "sf", "dscale", .99
endin

instr all_dangle
iamount    =          p4
Smsg       sprintf    "/ITL/scene/%s","*"
ksend metro 1000/10
           OSCsend    ksend, "", giPort, Smsg, "sf", "dangle", iamount
endin

instr init
           OSCsend    1,"", giPort, "/ITL", "ss", "rootPath", gSrootPath
           OSCsend    1, "", giPort, "/ITL", "si", "defaultShow", 0
Sdelmsg    sprintf    "/ITL/scene/%s","*"
           OSCsend    1,"",giPort, Sdelmsg, "s", "del" 
           turnoff
endin

instr color ;e.g. color 255 255 255 255
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
ired       StrayGetNum Smsg, 2 
igreen     StrayGetNum Smsg, 3 
iblue      StrayGetNum Smsg, 4 
ialph      StrayGetNum Smsg, 5 
           OSCsend    1,"",giPort, Sdest, "siiii", "color", ired, igreen, iblue, ialph 
           turnoff
endin

instr width; e.g. width 1.33
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iwidth     StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "width", iwidth 
           turnoff
endin

instr set ;look for any set messages
Smsg       strget     p4
Swhat      StrayGetEl Smsg, 2 
iSetFile   strcmp     Swhat, "file" 
iSetTxt    strcmp     Swhat, "txt"
iSetRect   strcmp     Swhat, "rect"
iSetEllipse strcmp    Swhat, "ellipse"
iSetCurve  strcmp     Swhat, "curve"
iSetPoly   strcmp     Swhat, "polygon"
iSetGmnf   strcmp     Swhat, "gmnf"
iSetImg    strcmp     Swhat, "img"
iSetTxtf   strcmp     Swhat, "txtf"
 if iSetFile == 0 then
iwho       nstrnum    "set_file"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
 elseif iSetTxt == 0 then
iwho       nstrnum    "set_txt"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
 elseif iSetRect == 0 then
iwho       nstrnum    "set_rect"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
 elseif iSetEllipse == 0 then
iwho       nstrnum    "set_ellipse"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
 elseif iSetCurve == 0 then
iwho       nstrnum    "set_curve"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
 elseif iSetPoly == 0 then
iwho       nstrnum    "set_polygon"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall  
 elseif iSetGmnf == 0 then
iwho       nstrnum    "set_gmnf"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall 
 elseif iSetImg == 0 then
iwho       nstrnum    "set_img"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall
 elseif iSetTxtf == 0 then
iwho       nstrnum    "set_txtf"
Scall      sprintf    {{i%d 0 .1 "%s"}}, iwho, Smsg 
           scoreline_i Scall
 endif
           turnoff
endin

instr set_file ; e.g. set file rsrc/title.html
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Sfil       StrayGetEl Smsg, 3 
           OSCsend    1,"",giPort, Sdest, "sss", "set", "file", Sfil 
           turnoff
endin

instr set_txt ; e.g. set txt bla
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Stxt       StrayGetEl Smsg, 3 
           OSCsend    1,"",giPort, Sdest, "sss", "set", "txt", Stxt
           turnoff
endin

instr set_txtf ; e.g. set txtf rsrc/bla.txt
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Sfil       StrayGetEl Smsg, 3 
           OSCsend    1,"",giPort, Sdest, "sss", "set", "txtf", Sfil 
           turnoff
endin

instr set_rect ; e.g. set rect 0.316562 0.325442
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iwidth     StrayGetNum Smsg, 3 
iheight    StrayGetNum Smsg, 4
           OSCsend    1,"",giPort, Sdest, "ssff", "set", "rect", iwidth, iheight
           turnoff
endin

instr set_ellipse ; e.g. set ellipse 0.81554 0.629943
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iwidth     StrayGetNum Smsg, 3 
iheight    StrayGetNum Smsg, 4
           OSCsend    1,"",giPort, Sdest, "ssff", "set", "ellipse", iwidth, iheight
           turnoff
endin

instr set_curve ; e.g. set curve 0.0001 0.0001 0.3 0.0001 0.5 0.3 0.0001 0.3 0.0001 0.0001 0.25 0.0001 0.45 0.3 0.0001 0.3
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
ix1        StrayGetNum Smsg, 3 
iy1        StrayGetNum Smsg, 4
ix2        StrayGetNum Smsg, 5
iy2        StrayGetNum Smsg, 6
ix3        StrayGetNum Smsg, 7 
iy3        StrayGetNum Smsg, 8
ix4        StrayGetNum Smsg, 9 
iy4        StrayGetNum Smsg, 10
ix5        StrayGetNum Smsg, 11
iy5        StrayGetNum Smsg, 12
ix6        StrayGetNum Smsg, 13
iy6        StrayGetNum Smsg, 14
ix7        StrayGetNum Smsg, 15
iy7        StrayGetNum Smsg, 16
ix8        StrayGetNum Smsg, 17
iy8        StrayGetNum Smsg, 18
           OSCsend    1,"",giPort, Sdest, "ssffffffffffffffff", "set", "curve", ix1, iy1, ix2, iy2, ix3, iy3, ix4, iy4, ix5, iy5, ix6, iy6, ix7, iy7, ix8, iy8
           turnoff
endin


instr set_polygon ;e.g. set polygon 0.8 0.9 0.3 1.0001 0.44 -0.1
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
ix1        StrayGetNum Smsg, 3 
iy1        StrayGetNum Smsg, 4
ix2        StrayGetNum Smsg, 5
iy2        StrayGetNum Smsg, 6
ix3        StrayGetNum Smsg, 7 
iy3        StrayGetNum Smsg, 8
           OSCsend    1,"",giPort, Sdest, "ssffffff", "set", "polygon", ix1, iy1, ix2, iy2, ix3, iy3
           turnoff
endin

instr set_gmnf ; e.g. set gmnf rsrc/1voice-846_2f.gmn
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Sfil       StrayGetEl Smsg, 3 
           OSCsend    1,"",giPort, Sdest, "sss", "set", "gmnf", Sfil
           turnoff
endin

instr set_img ; e.g. set img rsrc/car_blue.gif
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Sfil       StrayGetEl Smsg, 3 
           OSCsend    1,"",giPort, Sdest, "sss", "set", "img", Sfil 
           turnoff
endin

instr x ;e.g. x -0.12
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
ix         StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "x", ix 
           turnoff
endin

instr y ;e.g. y -0.66
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iy         StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "y", iy 
           turnoff
endin

instr scale ;e.g. scale 3.3
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iscal      StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "scale", iscal 
           turnoff
endin

instr dscale ;e.g. dscale 0.95
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iscal      StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "dscale", iscal 
           turnoff
endin

instr show ;e.g. show 1
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
ishow      StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "si", "show", ishow 
           turnoff
endin

instr defaultShow ;e.g. defaultShow 1
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
ishow      StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "si", "defaultShow", ishow 
           turnoff
endin

instr dy ;e.g. dy -0.01
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iy         StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "dy", iy 
           turnoff
endin

instr z ;e.g. z 1
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iz         StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "z", iz
           turnoff
endin

instr angle ;e.g. angle 81.3
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iang       StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "angle", iang
           turnoff
endin

instr dangle ;e.g. dangle 0.99
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
iang       StrayGetNum Smsg, 2 
           OSCsend    1,"",giPort, Sdest, "sf", "dangle", iang
           turnoff
endin

instr del ;e.g. del
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
           OSCsend    1,"",giPort, Sdest, "s", "del"
           turnoff
endin

instr date ;e.g. date 2 1
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
inum       StrayGetNum Smsg, 2 
idenum     StrayGetNum Smsg, 3
           OSCsend    1,"",giPort, Sdest, "sii", "date", inum, idenum
           turnoff
endin

instr duration ;e.g. duration 1 4
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
inum       StrayGetNum Smsg, 2 
idenum     StrayGetNum Smsg, 3
           OSCsend    1,"",giPort, Sdest, "sii", "duration", inum, idenum
           turnoff
endin

instr mapf ;e.g. mapf rsrc/syncomment7.map
Smsg       strget     p4
Sdest      StrayGetEl Smsg, 0 
Smap       StrayGetEl Smsg, 2
           OSCsend    1,"",giPort, Sdest, "ss", "mapf", Smap
           turnoff
endin

</CsInstruments>
<CsScore>
i 1 0.000 .01 "/ITL/scene color 255 255 255 255"
i 1 0.001 . "/ITL/scene width 1.33"
i 1 0.002 . "/ITL/scene/title set file rsrc/title.html"
i 1 0.003 . "/ITL/scene/title x -0.12"
i 1 0.004 . "/ITL/scene/title y -0.66"
i 1 0.005 . "/ITL/scene/title scale 3.3"
i 1 0.006 . "/ITL/scene/title show 1"
i 1 1.506 . "/ITL/scene/* dy -0.01"
i 1 1.526 . "/ITL/scene/* dy -0.01"
i 1 1.546 . "/ITL/scene/* dy -0.01"
i 1 1.566 . "/ITL/scene/* dy -0.01"
i 1 1.586 . "/ITL/scene/* dy -0.01"
i 1 1.606 . "/ITL/scene/* dy -0.01"
i 1 1.626 . "/ITL/scene/* dy -0.01"
i 1 1.646 . "/ITL/scene/* dy -0.02"
i 1 1.666 . "/ITL/scene/* dy -0.02"
i 1 1.686 . "/ITL/scene/* dy -0.02"
i 1 1.706 . "/ITL/scene/* dy -0.02"
i 1 1.726 . "/ITL/scene/* dy -0.03"
i 1 1.746 . "/ITL/scene/* dy -0.03"
i 1 1.766 . "/ITL/scene/* dy -0.03"
i 1 1.786 . "/ITL/scene/* dy -0.03"
i 1 1.806 . "/ITL/scene/* dy -0.03"
i 1 1.826 . "/ITL/scene/* z 1"
i "demotime" 1.836 [56.109-1.836] 17.85
i 1 2.336 .01 "/ITL/scene/comment1 set txt supports:"
i 1 2.337 . "/ITL/scene/comment1 x -0.686667"
i 1 2.338 . "/ITL/scene/comment1 y -0.0333334"
i 1 2.339 . "/ITL/scene/comment1 scale 3.79747"
i 1 2.340 . "/ITL/scene/comment1 color 178 42 64 255"
i 1 2.341 . "/ITL/scene/comment1 show 1"
i 1 2.841 . "/ITL/scene/what set txt text"
i 1 2.842 . "/ITL/scene/what scale 4.74"
i 1 2.843 . "/ITL/scene/what show 1"
i 1 2.844 . "/ITL/scene/what z 1."
i 1 3.844 . "/ITL/scene/what set txt shapes"
i 1 4.344 . "/ITL/scene/shapeRect set rect 0.316562 0.325442"
i 1 4.345 . "/ITL/scene/shapeRect x -0.38"
i 1 4.346 . "/ITL/scene/shapeRect y 0.26"
i 1 4.347 . "/ITL/scene/shapeRect scale 1."
i 1 4.348 . "/ITL/scene/shapeRect color 45 153 0 255"
i 1 4.349 . "/ITL/scene/shapeRect show 1"
i 1 4.849 . "/ITL/scene/shapeEllipse set ellipse 0.81554 0.629943"
i 1 4.850 . "/ITL/scene/shapeEllipse color 178 227 255 116"
i 1 4.851 . "/ITL/scene/shapeEllipse show 1"
i 1 5.351 . "/ITL/scene/shapeCurve set curve 0.0001 0.0001 0.3 0.0001 0.5 0.3 0.0001 0.3 0.0001 0.0001 0.25 0.0001 0.45 0.3 0.0001 0.3"
i 1 5.352 . "/ITL/scene/shapeCurve x 0.06"
i 1 5.353 . "/ITL/scene/shapeCurve y 0.1"
i 1 5.354 . "/ITL/scene/shapeCurve z 1.826923"
i 1 5.355 . "/ITL/scene/shapeCurve scale 2.452"
i 1 5.356 . "/ITL/scene/shapeCurve angle 81.290321"
i 1 5.357 . "/ITL/scene/shapeCurve color 246 0 0 116"
i 1 5.358 . "/ITL/scene/shapeCurve show 1"
i 1 5.858 . "/ITL/scene/shapePolygon set polygon 0.8 0.9 0.3 1.0001 0.44 -0.1"
i 1 5.859 . "/ITL/scene/shapePolygon x 0.52"
i 1 5.860 . "/ITL/scene/shapePolygon y -0.04"
i 1 5.861 . "/ITL/scene/shapePolygon color 255 163 59 116"
i 1 5.862 . "/ITL/scene/shapePolygon show 1"
i 1 6.362 . "/ITL/scene/what show 0"
i 1 6.363 . "/ITL/scene/what x -0.3"
i 1 6.364 . "/ITL/scene/what y 0.76"
i 1 6.365 . "/ITL/scene/what z 0.5"
i 1 6.366 . "/ITL/scene/what set txt images"
i 1 6.367 . "/ITL/scene/what show 1"
i 1 6.368 . "/ITL/scene/shape* z 0.5"
i 1 6.868 . "/ITL/scene/img1 set file rsrc/boucou.gif"
i 1 6.869 . "/ITL/scene/img1 x -0.679999"
i 1 6.870 . "/ITL/scene/img1 y 0.379999"
i 1 6.871 . "/ITL/scene/img1 z 0.6"
i 1 6.872 . "/ITL/scene/img1 show 1"
i 1 7.372 . "/ITL/scene/img2 set file rsrc/parm-oeil.jpg"
i 1 7.373 . "/ITL/scene/img2 x 0.36"
i 1 7.374 . "/ITL/scene/img2 y 0.56"
i 1 7.375 . "/ITL/scene/img2 show 1"
i 1 7.875 . "/ITL/scene/what show 0"
i 1 7.895 . "/ITL/scene/shape* dscale 0.95"
i 1 7.915 . "/ITL/scene/shape* dscale 0.95"
i 1 7.935 . "/ITL/scene/shape* dscale 0.95"
i 1 7.955 . "/ITL/scene/shape* dscale 0.95"
i 1 7.975 . "/ITL/scene/shape* dscale 0.95"
i 1 7.995 . "/ITL/scene/shape* dscale 0.95"
i 1 8.015 . "/ITL/scene/shape* dscale 0.95"
i 1 8.035 . "/ITL/scene/shape* dscale 0.95"
i 1 8.055 . "/ITL/scene/shape* dscale 0.95"
i 1 8.075 . "/ITL/scene/shape* dscale 0.95"
i 1 8.095 . "/ITL/scene/shape* dscale 0.95"
i 1 8.115 . "/ITL/scene/imgs* dscale 0.95"
i 1 8.135 . "/ITL/scene/shape* dscale 0.95"
i 1 8.155 . "/ITL/scene/imgs* dscale 0.95"
i 1 8.175 . "/ITL/scene/shape* dscale 0.95"
i 1 8.195 . "/ITL/scene/imgs* dscale 0.95"
i 1 8.215 . "/ITL/scene/shape* dscale 0.95"
i 1 8.235 . "/ITL/scene/imgs* dscale 0.95"
i 1 8.255 . "/ITL/scene/shape* dscale 0.95"
i 1 8.275 . "/ITL/scene/img* dscale 0.95"
i 1 8.295 . "/ITL/scene/img* dscale 0.95"
i 1 8.315 . "/ITL/scene/img* dscale 0.95"
i 1 8.335 . "/ITL/scene/img* dscale 0.95"
i 1 8.355 . "/ITL/scene/img* dscale 0.95"
i 1 8.375 . "/ITL/scene/img* dscale 0.95"
i 1 8.395 . "/ITL/scene/img* dscale 0.95"
i 1 8.415 . "/ITL/scene/img* dscale 0.95"
i 1 8.435 . "/ITL/scene/img* dscale 0.95"
i 1 8.436 . "/ITL/scene/what x 0.94"
i 1 8.437 . "/ITL/scene/what y 0.3"
i 1 8.438 . "/ITL/scene/what set txt scores"
i 1 8.938 . "/ITL/scene/what show 1"
i 1 8.948 . "/ITL/scene/guido set gmnf rsrc/1voice-846_2f.gmn"
i 1 8.958 . "/ITL/scene/guido z 8.5"
i 1 8.968 . "/ITL/scene/guido scale 2.648"
i 1 9.468 . "/ITL/scene/guido show 1"
i 1 9.478 . "/ITL/scene/title del"
i 1 10.478 . "/ITL/scene/what set txt Interaction"
i 1 10.479 . "/ITL/scene/what x 0.95"
i 1 10.480 . "/ITL/scene/what y 0.1"
i 1 10.490 . "/ITL/scene/title del"
i "shape_dangle" 10.491 3
i "is_dangle" 13.581 2
i "all_dangle_scale" 15.981 [19.434 - 15.981]
i 1 19.435 .01 "/ITL/scene/* del"
i 1 19.445 . "/ITL/scene/what set txt Synchronization"
i 1 19.446 . "/ITL/scene/what scale 4.74"
i 1 19.447 . "/ITL/scene/comment set file rsrc/syncomment1.html"
i 1 19.448 . "/ITL/scene/comment y 0.4"
i 1 19.449 . "/ITL/scene/comment scale 2.1"
i 1 19.450 . "/ITL/scene/* show 1"
i 1 22.950 . "/ITL/scene/slave1 set img rsrc/car_blue.gif"
i 1 22.951 . "/ITL/scene/what del"
i 1 22.952 . "/ITL/scene/* show 0"
i 1 22.953 . "/ITL/scene/comment set file rsrc/syncomment2.html"
i 1 22.954 . "/ITL/scene/comment x -0.88"
i 1 22.955 . "/ITL/scene/comment y 0.08"
i 1 22.956 . "/ITL/scene/comment scale 1.406667"
i 1 22.957 . "/ITL/scene/slave2 set img rsrc/car_red.gif"
i 1 22.958 . "/ITL/scene/guido set gmnf rsrc/1voice-846_2f.gmn"
i 1 22.959 . "/ITL/scene/guido y 0.1"
i 1 22.960 . "/ITL/scene/guido scale 2.5"
i 1 22.961 . "/ITL/scene/slave* scale 0.6"
i 1 22.962 . "/ITL/scene/slave* z 2.0"
i 1 22.963 . "/ITL/scene/slave* duration 1 4"
i 1 22.964 . "/ITL/scene/slave1 date 2 1"
i 1 22.965 . "/ITL/scene/slave2 date 4 1"
i 2 22.966 .01 "/ITL/scene/sync slave* guido"
i 1 22.967 .01 "/ITL/scene/* show 1"
i 1 22.968 . "/ITL/scene/comment1 set file rsrc/syncomment3.html"
i 1 22.969 . "/ITL/scene/comment1 x 0.88"
i 1 22.970 . "/ITL/scene/comment1 y -0.2"
i 1 22.971 . "/ITL/scene/comment1 scale 1.406667"
i 1 22.972 . "/ITL/scene/comment1 show 1"
i 1 30.972 . "/ITL/scene/comment2 set file rsrc/syncomment4.html"
i 3 30.973 .01 "/ITL/scene/sync slave* guido hv"
i 1 30.974 .01 "/ITL/scene/comment2 x 0.88"
i 1 30.975 . "/ITL/scene/comment2 y 0.2"
i 1 30.976 . "/ITL/scene/comment2 scale 1.406667"
i 1 30.977 . "/ITL/scene/comment2 show 1"
i 1 38.977 . "/ITL/scene/slave* del"
i 1 38.978 . "/ITL/scene/comment* del"
i 1 38.979 . "/ITL/scene/guido z 0.5"
i 1 38.999 . "/ITL/scene color 250 250 110 255"
i 1 39.019 . "/ITL/scene color 240 240 110 255"
i 1 39.039 . "/ITL/scene color 230 230 110 255"
i 1 39.059 . "/ITL/scene color 220 220 110 255"
i 1 39.079 . "/ITL/scene color 210 210 110 255"
i 1 39.099 . "/ITL/scene color 200 200 110 255"
i 1 39.119 . "/ITL/scene color 190 190 110 255"
i 1 39.139 . "/ITL/scene color 180 180 110 255"
i 1 39.159 . "/ITL/scene color 170 170 110 255"
i 1 39.179 . "/ITL/scene color 160 160 110 255"
i 1 39.199 . "/ITL/scene color 150 150 110 255"
i 1 39.219 . "/ITL/scene color 140 140 110 255"
i 1 39.239 . "/ITL/scene color 130 130 110 255"
i 1 39.259 . "/ITL/scene color 120 120 110 255"
i 1 39.279 . "/ITL/scene color 110 110 110 255"
i 1 39.299 . "/ITL/scene color 90 90 110 255"
i 1 39.319 . "/ITL/scene color 80 80 110 255"
i 1 39.339 . "/ITL/scene color 70 70 110 255"
i 1 39.359 . "/ITL/scene color 60 60 110 255"
i 1 39.379 . "/ITL/scene color 50 50 110 255"
i 1 39.399 . "/ITL/scene color 40 40 110 255"
i 1 39.419 . "/ITL/scene color 30 30 110 255"
i 1 39.439 . "/ITL/scene color 20 20 110 255"
i 1 39.459 . "/ITL/scene color 10 10 110 255"
i 1 39.460 . "/ITL/scene color 0 0 110 255"
i 1 39.461 . "/ITL/scene/slave3 set ellipse 0.15 0.15"
i 1 39.462 . "/ITL/scene/slave3 color 255 255 135 255"
i 1 39.463 . "/ITL/scene/slave3 date 10 1"
i 1 39.464 . "/ITL/scene/slave3 duration 1 4"
i 1 39.465 . "/ITL/scene/slave3 z -0.5"
i 2 39.466 .01 "/ITL/scene/sync slave3 guido"
i 1 39.467 .01 "/ITL/scene/comment set file rsrc/syncomment5.html"
i 1 39.468 . "/ITL/scene/comment color 255 255 135 255"
i 1 39.469 . "/ITL/scene/comment x -0.88"
i 1 39.470 . "/ITL/scene/comment y 0.08"
i 1 39.471 . "/ITL/scene/comment scale 2.1"
i 1 39.472 . "/ITL/scene/* show 1"
i 1 43.472 . "/ITL/scene color 255 255 255 255"
i 1 43.473 . "/ITL/scene/* del"
i 1 43.474 . "/ITL/scene color 255 255 255 255"
i 1 43.475 . "/ITL/scene/comment set file rsrc/syncomment6.txt"
i 1 43.476 . "/ITL/scene/comment mapf rsrc/syncomment6.map"
i 1 43.477 . "/ITL/scene/comment scale 4.2"
i 1 43.478 . "/ITL/scene/comment duration 1 4"
i 1 43.479 . "/ITL/scene/comment z 0.5"
i 1 43.480 . "/ITL/scene/slave set ellipse 0.7 0.7"
i 1 43.481 . "/ITL/scene/slave z 0.4"
i 1 43.482 . "/ITL/scene/slave color 0 221 0 120"
i 1 43.483 . "/ITL/scene/slave date 0 1"
i 1 43.484 . "/ITL/scene/slave duration 1 4"
i 2 43.485 .01 "/ITL/scene/sync slave comment"
i 1 43.486 . "/ITL/scene/* show 1"
i 1 47.486 . "/ITL/scene/img set file rsrc/parm-oeil.jpg"
i 1 47.487 . "/ITL/scene/comment del"
i 1 47.488 . "/ITL/scene/img show 1"
i 1 47.489 . "/ITL/scene/img scale 1.2"
i 1 47.490 . "/ITL/scene/img mapf rsrc/parm-oeil.map"
i 1 47.491 . "/ITL/scene/slavecomment set txtf rsrc/syncomment7.txt"
i 1 47.492 . "/ITL/scene/slavecomment scale 3.1"
i 1 47.493 . "/ITL/scene/slavecomment color 240 0 0 255"
i 1 47.494 . "/ITL/scene/slavecomment mapf rsrc/syncomment7.map"
i 1 47.495 . "/ITL/scene/* date 0 1"
i 1 47.496 . "/ITL/scene/slavecomment show 1"
i 2 47.497 .01 "/ITL/scene/sync slavecomment img"
i 2 47.498 . "/ITL/scene/sync slave slavecomment"
i 1 50.499 .01 "/ITL/scene/comment1 set txtf rsrc/syncomment8.txt"
i 1 50.500 . "/ITL/scene/comment1 scale 2.648"
i 1 50.501 . "/ITL/scene/comment1 x 0.04"
i 1 50.502 . "/ITL/scene/comment1 y 0.54"
i 1 50.503 . "/ITL/scene/comment1 z 0.730769"
i 1 50.504 . "/ITL/scene/comment1 show 1"
i "all_dangle" 51.004 [51.434-51.004] 0.3
i 1 51.435 . "/ITL/scene/slave color 240 0 0 120"
i 1 51.436 . "/ITL/scene/comment color 0 221 0 255"
i "all_dangle" 51.446 [51.866 - 51.446] -0.3
i 1 51.867 .01 "/ITL/scene/slave color 250 200 0 120"
i 1 51.868 . "/ITL/scene/comment color 0 0 240 255"
i "all_dangle" 51.878 [54.098-51.878] 0.3
i 1 56.108 .01 "/ITL/scene/* del"
i 1 56.110 . "/ITL/scene/itl set htmlf rsrc/interlude.html"
i 1 56.111 . "/ITL/scene/itl scale 1.864"
i 1 56.112 . "/ITL/scene/itl show 1"
i 1 56.113 . "/ITL/scene/anr set file rsrc/anr.gif"
i 1 56.114 . "/ITL/scene/anr scale 0.818667"
i 1 56.115 . "/ITL/scene/anr show 1"
i 1 56.116 . "/ITL/scene/anr x 0.44"
i 1 56.117 . "/ITL/scene/anr y 0.46"
i 1 56.118 . "/ITL/scene/grame set file rsrc/grame.png"
i 1 56.119 . "/ITL/scene/grame scale 1.668"
i 1 56.120 . "/ITL/scene/grame show 1"
i 1 56.121 . "/ITL/scene/grame x -0.38"
i 1 56.122 . "/ITL/scene/grame y 0.44"
i 1 56.123 . "/ITL defaultShow 1"

</CsScore>
</CsoundSynthesizer>











<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>72</x>
 <y>179</y>
 <width>400</width>
 <height>200</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>231</r>
  <g>46</g>
  <b>255</b>
 </bgcolor>
 <bsbObject version="2" type="BSBVSlider">
  <objectName>slider1</objectName>
  <x>5</x>
  <y>5</y>
  <width>20</width>
  <height>100</height>
  <uuid>{852b0e8c-48e5-4bea-99df-3bd823a22197}</uuid>
  <visible>true</visible>
  <midichan>0</midichan>
  <midicc>-3</midicc>
  <minimum>0.00000000</minimum>
  <maximum>1.00000000</maximum>
  <value>0.00000000</value>
  <mode>lin</mode>
  <mouseControl act="jump">continuous</mouseControl>
  <resolution>-1.00000000</resolution>
  <randomizable group="0">false</randomizable>
 </bsbObject>
</bsbPanel>
<bsbPresets>
</bsbPresets>
