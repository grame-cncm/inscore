/*Strays - UDOs for using strings as arrays in Csound
require the new parser (default in Csound 5.16 or higher)
for examples see StrayExamples.csd
more examples and extended documentation at www.csounds.com/udo
joachim heintz feb 2012*/


/*
OVERVIEW
ilen       StrayLen     Stray [, isep1 [, isep2]]
Sel        StrayGetEl   Stray, ielindx [, isep1 [, isep2]]
inum       StrayGetNum  Stray, ielindx [, isep1 [, isep2]]
ipos       StrayElMem   Stray, Stest [, isep1 [, isep2]]
ipos       StrayNumMem  Stray, inum [, isep1 [, isep2]]
Sres       StraySetEl   Stray, Sin [, ielindx [, isep1 [, isep2 [,isepOut]]]]
Sres       StraySetNum  Stray, inum [, ielindx [, isep1 [, isep2 [,isepOut]]]]
Srev       StrayRev     Stray [,isepA [, isepB [, isepOut]]]
Sub        StraySub     Stray [, istart [, iend [, isepA [, isepB [, isepOut]]]]]
Sres       StrayRmv     Stray, Srem [, isepA [, isepB [, isepOut]]]
Srem       StrayRemDup  Stray [, isep1 [, isep2]]
ift,iftlen StrayNumToFt Stray [, iftno [, isep1 [, isep2]]]
*/

/*
SIMPLE EXAMPLES
ilen       StrayLen     "a b c d e"
 ilen -> 5
Sel        StrayGetEl   "a b c d e", 0
 Sel -> "a"
inum       StrayGetNum  "1 2 3 4 5", 0
 inum -> 1
ipos       StrayElMem   "a b c d e", "c"
 ipos -> 2
ipos       StrayNumMem  "1 2 3 4 5", 3
 ipos -> 2
Sres       StraySetEl   "a b c d e", "go", 0
 Sres -> "go a b c d e"
Sres       StraySetNum  "1 2 3 4 5", 0, 0
 Sres -> "0 1 2 3 4 5"
Srev       StrayRev     "a b c d e"
 Srev -> "e d c b a"
Sub        StraySub     "a b c d e", 1, 3
 Sub -> "b c"
Sout       StrayRmv     "a b c d e", "b d"
 Sout -> "a c e"
Srem       StrayRemDup  "a b a c c d e e"
 Srem -> "a b c d e"
ift,iftlen StrayNumToFt "1 2 3 4 5", 1
 ift -> 1 (same as f 1 0 -5 -2 1 2 3 4 5)
 iftlen -> 5
*/


  opcode StrayLen, i, Sjj
;returns the number of elements in Stray. elements are defined by two seperators as ASCII coded characters: isep1 defaults to 32 (= space), isep2 defaults to 9 (= tab). if just one seperator is used, isep2 equals isep1
Stray, isepA, isepB xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
icount    =         0; number of elements
iwarsep   =         1
indx      =         0
 if ilen == 0 igoto end ;don't go into the loop if String is empty
loop:
Snext     strsub    Stray, indx, indx+1; next sign
isep1p    strcmp    Snext, Sep1; returns 0 if Snext is sep1
isep2p    strcmp    Snext, Sep2; 0 if Snext is sep2
 if isep1p == 0 || isep2p == 0 then; if sep1 or sep2
iwarsep   =         1; tell the log so
 else 				; if not 
  if iwarsep == 1 then	; and has been sep1 or sep2 before
icount    =         icount + 1; increase counter
iwarsep   =         0; and tell you are ot sep1 nor sep2 
  endif 
 endif	
          loop_lt   indx, 1, ilen, loop 
end:      xout      icount
  endop 

  opcode StrayGetEl, S, Sijj
;returns the element at position ielindx in Stray, or an empty string if the element has not been found
Stray, ielindx, isepA, isepB xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
istartsel =         -1; startindex for searched element
iendsel   =         -1; endindex for searched element
iel       =         0; actual number of element while searching
iwarleer  =         1
indx      =         0
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Snext     strsub    Stray, indx, indx+1; next sign
isep1p    strcmp    Snext, Sep1; returns 0 if Snext is sep1
isep2p    strcmp    Snext, Sep2; 0 if Snext is sep2
;;NEXT SIGN IS NOT SEP1 NOR SEP2
if isep1p != 0 && isep2p != 0 then
 if iwarleer == 1 then; first character after a seperator 
  if iel == ielindx then; if searched element index
istartsel =         indx; set it
iwarleer  =         0
  else 			;if not searched element index
iel       =         iel+1; increase it
iwarleer  =         0; log that it's not a seperator 
  endif 
 endif 
;;NEXT SIGN IS SEP1 OR SEP2
else 
 if istartsel > -1 then; if this is first selector after searched element
iendsel   =         indx; set iendsel
          igoto     end ;break
 else	
iwarleer  =         1
 endif 
endif
          loop_lt   indx, 1, ilen, loop 
end:
Sout      strsub    Stray, istartsel, iendsel
          xout      Sout
  endop 

  opcode StrayGetNum, i, Sijj
;returns ielindex in Stray. this element must be a number
Stray, ielindx, isepA, isepB xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
istartsel =         -1; startindex for searched element
iendsel   =         -1; endindex for searched element
iel       =         0; actual number of element while searching
iwarleer  =         1
indx      =         0
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Snext     strsub    Stray, indx, indx+1; next sign
isep1p    strcmp    Snext, Sep1; returns 0 if Snext is sep1
isep2p    strcmp    Snext, Sep2; 0 if Snext is sep2
;;NEXT SIGN IS NOT SEP1 NOR SEP2
if isep1p != 0 && isep2p != 0 then
 if iwarleer == 1 then; first character after a seperator 
  if iel == ielindx then; if searched element index
istartsel =         indx; set it
iwarleer  =         0
  else 			;if not searched element index
iel       =         iel+1; increase it
iwarleer  =         0; log that it's not a seperator 
  endif 
 endif 
;;NEXT SIGN IS SEP1 OR SEP2
else 
 if istartsel > -1 then; if this is first selector after searched element
iendsel   =         indx; set iendsel
          igoto     end ;break
 else	
iwarleer  =         1
 endif 
endif
          loop_lt   indx, 1, ilen, loop 
end: 		
Snum      strsub    Stray, istartsel, iendsel
inum      strtod    Snum
          xout      inum
  endop 

  opcode StrayElMem, i, SSjj
;looks whether Stest is an element of Stray. returns the index of the element if found, and -1 if not.
Stray, Stest, isepA, isepB xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
istartsel =         -1; startindex for searched element
iout      =         -1 ;default output
iel       =         -1; actual number of element while searching
iwarleer  =         1; is this the start of a new element
indx      =         0 ;character index
inewel    =         0 ;new element to find
;;LOOP
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Schar     strsub    Stray, indx, indx+1; this character
isep1p    strcmp    Schar, Sep1; returns 0 if Schar is sep1
isep2p    strcmp    Schar, Sep2; 0 if Schar is sep2
is_sep    =         (isep1p == 0 || isep2p == 0 ? 1 : 0) ;1 if Schar is a seperator
 ;END OF STRING AND NO SEPARATORS BEFORE?
 if indx == ilen && iwarleer == 0 then
Sel       strsub    Stray, istartsel, -1
inewel    =         1
 ;FIRST CHARACTER OF AN ELEMENT?
 elseif is_sep == 0 && iwarleer == 1 then
istartsel =         indx ;if so, set startindex
iwarleer  =         0 ;reset info about previous separator 
iel       =         iel+1 ;increment element count
 ;FIRST SEPERATOR AFTER AN ELEMENT?
 elseif iwarleer == 0 && is_sep == 1 then
Sel       strsub    Stray, istartsel, indx ;get elment
inewel    =         1 ;tell about
iwarleer  =         1 ;reset info about previous separator
 endif
 ;CHECK THE ELEMENT
 if inewel == 1 then ;for each new element
icmp      strcmp    Sel, Stest ;check whether equals Stest
  ;terminate and return the position of the element if successful
  if icmp == 0 then
iout      =         iel
          igoto     end
  endif
 endif
inewel    =         0
          loop_le   indx, 1, ilen, loop 
end:
          xout      iout
  endop 

  opcode StrNumP, i, S
;tests whether String is numerical string (simple, no scientific notation) which can be converted via strtod into a float (1 = yes, 0 = no)
Str       xin	
ip        =         1; start at yes and falsify
ilen      strlen    Str
 if ilen == 0 then
ip        =         0
          igoto     end 
 endif 
ifirst    strchar   Str, 0
 if ifirst == 45 then; a "-" is just allowed as first character
Str       strsub    Str, 1, -1
ilen      =         ilen-1
 endif
indx      =         0
inpnts    =         0; how many points have there been
loop:
iascii    strchar   Str, indx; 48-57
 if iascii < 48 || iascii > 57 then; if not 0-9
  if iascii == 46 && inpnts == 0 then; if not the first point
inpnts    =         1
  else 
ip        =         0
  endif 
 endif	
          loop_lt   indx, 1, ilen, loop 
end:	     xout      ip
  endop 

  opcode StrayNumMem, i, Sijj
;looks whether inum is an element of Stray. returns the index of the element if found, and -1 if not.
Stray, inum, isepA, isepB xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
istartsel =         -1; startindex for searched element
iout      =         -1 ;default output
iel       =         -1; actual number of element while searching
iwarleer  =         1; is this the start of a new element
indx      =         0 ;character index
inewel    =         0 ;new element to find
;;LOOP
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Schar     strsub    Stray, indx, indx+1; this character
isep1p    strcmp    Schar, Sep1; returns 0 if Schar is sep1
isep2p    strcmp    Schar, Sep2; 0 if Schar is sep2
is_sep    =         (isep1p == 0 || isep2p == 0 ? 1 : 0) ;1 if Schar is a seperator
 ;END OF STRING AND NO SEPARATORS BEFORE?
 if indx == ilen && iwarleer == 0 then
Sel       strsub    Stray, istartsel, -1
inewel    =         1
 ;FIRST CHARACTER OF AN ELEMENT?
 elseif is_sep == 0 && iwarleer == 1 then
istartsel =         indx ;if so, set startindex
iwarleer  =         0 ;reset info about previous separator 
iel       =         iel+1 ;increment element count
 ;FIRST SEPERATOR AFTER AN ELEMENT?
 elseif iwarleer == 0 && is_sep == 1 then
Sel       strsub    Stray, istartsel, indx ;get element
inewel    =         1 ;tell about
iwarleer  =         1 ;reset info about previous separator
 endif
 ;CHECK THE ELEMENT
 if inewel == 1 then ;for each new element
inump     StrNumP   Sel ;check whether element is number
  if inump == 1 then
inumber   strtod    Sel ;if so, convert
   if inumber == inum then ;check if equals inum
iout      =         iel
          igoto     end ;if so, terminate
   endif
  endif
 endif
inewel    =         0
          loop_le   indx, 1, ilen, loop 
end:
          xout      iout
  endop 

  opcode StraySetEl, S, SSjjjj
;puts the string Sin at the position ielindx (default=-1: at the end) of Stray, and returns the result as a string. elements in the string are seperated by the two ascii-coded seperators isepA (default=32: space) and isepB (default=9: tab). if just isepA is given, it is also read as isepB. the element is inserted using the seperator isepOut (default=isep1)
Stray, Sin, ielindx, isepA, isepB, isepOut xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
isepOut   =         (isepOut == -1 ? isep1 : isepOut)
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
SepOut    sprintf   "%c", isepOut
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
iel       =         0; actual element position
iwarsep   =         1
indx      =         0
;;APPEND Sin IF ielindx=-1
 if ielindx == -1 then
Sres      sprintf   "%s%s%s", Stray, SepOut, Sin
          igoto     end	
 endif
;;PREPEND Sin IF ielindx=0
 if ielindx == 0 then
Sres      sprintf   "%s%s%s", Sin, SepOut, Stray
          igoto     end	
  endif
loop:
Snext     strsub    Stray, indx, indx+1; next sign
isep1p    strcmp    Snext, Sep1; returns 0 if Snext is sep1
isep2p    strcmp    Snext, Sep2; 0 if Snext is sep2
;;NEXT SIGN IS NOT SEP1 NOR SEP2
if isep1p != 0 && isep2p != 0 then
 if iwarsep == 1 then; first character after a seperator 
  if iel == ielindx then; if searched element index
S1        strsub    Stray, 0, indx; string before Sin
S2        strsub    Stray, indx, -1; string after Sin
Sres      sprintf   "%s%s%s%s", S1, Sin, SepOut, S2
          igoto     end
  else 			;if not searched element index
iel       =         iel+1; increase it
iwarsep   =         0; log that it's not a seperator 
  endif 
 endif 
;;NEXT SIGN IS SEP1 OR SEP2
else 
iwarsep   =         1
endif
          loop_lt   indx, 1, ilen, loop 
;;APPEND Sin IF ielindx is >= number of elements
Sres      sprintf   "%s%s%s", Stray, SepOut, Sin
end:      xout      Sres
  endop 

  opcode FracNum, i, io
;returns the number of digits in the fractional part (0=integer)
inum, ifracs xin
ifac      =         10^ifracs
if int(inum*ifac) == inum*ifac then
          igoto     end
else
ifracs    FracNum   inum, ifracs+1
endif
end:      xout      ifracs
  endop

  opcode StraySetNum, S, Sijjjj
;puts the number inum at the position ielindx (default=-1: at the end) of Stray, and returns the result as a string. elements in the string are seperated by the two ascii-coded seperators isepA (default=32: space) and isepB (default=9: tab). if just isepA is given, it is also read as isepB. the element is inserted using the seperator isepOut (default=isep1)
Stray, inum, ielindx, isepA, isepB, isepOut xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
isepOut   =         (isepOut == -1 ? isep1 : isepOut)
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
SepOut    sprintf   "%c", isepOut
;;INITIALIZE SOME PARAMETERS
ifracs    FracNum   inum
ilen      strlen    Stray
iel       =         0; actual element position
iwarsep   =         1
indx      =         0
;;APPEND inum IF ielindx=-1
 if ielindx == -1 then
Sformat   sprintf   "%%s%%s%%.%df", ifracs
Sres      sprintf   Sformat, Stray, SepOut, inum
          igoto     end	
 endif
;;PREPEND inum IF ielindx=0
 if ielindx == 0 then
Sformat   sprintf   "%%.%df%%s%%s", ifracs
Sres      sprintf   Sformat, inum, SepOut, Stray
          igoto     end	
  endif
loop:
Snext     strsub    Stray, indx, indx+1; next sign
isep1p    strcmp    Snext, Sep1; returns 0 if Snext is sep1
isep2p    strcmp    Snext, Sep2; 0 if Snext is sep2
;;NEXT SIGN IS NOT SEP1 NOR SEP2
if isep1p != 0 && isep2p != 0 then
 if iwarsep == 1 then; first character after a seperator 
  if iel == ielindx then; if searched element index
S1        strsub    Stray, 0, indx; string before Sin
S2        strsub    Stray, indx, -1; string after Sin
Sformat   sprintf   "%%s%%.%df%%s%%s", ifracs
Sres      sprintf   Sformat, S1, inum, SepOut, S2
          igoto     end
  else              ;if not searched element index
iel       =         iel+1; increase it
iwarsep   =         0; log that it's not a seperator 
  endif 
 endif 
;;NEXT SIGN IS SEP1 OR SEP2
else 
iwarsep   =         1
endif
          loop_lt   indx, 1, ilen, loop 
;;APPEND inum IF ielindx IS >= NUMBER OF ELEMENTS
Sformat   sprintf   "%%s%%s%%.%df", ifracs
Sres      sprintf   Sformat, Stray, SepOut, inum
end:		xout      Sres
  endop 

  opcode StrayRev, S, Sjjj
;reverses the elements in Stray and returns the result. elements are defined by two seperators as ASCII coded characters: isep1 defaults to 32 (= space), isep2 defaults to 9 (= tab). if just one seperator is used, isep2 equals isep1. the elements in the resulting string Sres are seperated by isepOut (default=isep1)
Stray, isepA, isepB, isepOut xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
isepOut   =         (isepOut == -1 ? isep1 : isepOut)
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
Sres      =         ""
ilen      strlen    Stray
istartsel =         -1; startindex for searched element
iwarleer  =         1; is this the start of a new element
indx      =         0 ;character index
inewel    =         0 ;new element to find
;;LOOP
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Schar     strsub    Stray, indx, indx+1; this character
isep1p    strcmp    Schar, Sep1; returns 0 if Schar is sep1
isep2p    strcmp    Schar, Sep2; 0 if Schar is sep2
is_sep    =         (isep1p == 0 || isep2p == 0 ? 1 : 0) ;1 if Schar is a seperator
 ;END OF STRING AND NO SEPARATORS BEFORE?
 if indx == ilen && iwarleer == 0 then
Sel       strsub    Stray, istartsel, -1
inewel    =         1
 ;FIRST CHARACTER OF AN ELEMENT?
 elseif is_sep == 0 && iwarleer == 1 then
istartsel =         indx ;if so, set startindex
iwarleer  =         0 ;reset info about previous separator 
 ;FIRST SEPERATOR AFTER AN ELEMENT?
 elseif iwarleer == 0 && is_sep == 1 then
Sel       strsub    Stray, istartsel, indx ;get elment
inewel    =         1 ;tell about
iwarleer  =         1 ;reset info about previous separator
 endif
 ;PREPEND THE ELEMENT TO THE RESULT
 if inewel == 1 then ;for each new element
Selsep    sprintf   "%c%s", isepOut, Sel ;prepend seperator
Sres      strcat    Selsep, Sres ;prepend to result
 endif
inewel    =         0
          loop_le   indx, 1, ilen, loop 
end:
Sout      strsub    Sres, 1; remove starting seperator
          xout      Sout
  endop 

  opcode StraySub, S, Sojjjj
;returns a subset of elements in Stray. elements are defined by two seperators as ASCII coded characters: isep1 defaults to 32 (= space), isep2 defaults to 9 (= tab). if just one seperator is used, isep2 equals isep1.
Stray, istart, iend, isepA, isepB, isepOut xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
isepOut   =         (isepOut == -1 ? isep1 : isepOut)
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;INITIALIZE SOME PARAMETERS
Sres      =         ""
ilen      strlen    Stray
iend      =         (iend == -1 ? ilen : iend) ;for simplifying tests later
istartsel =         -1; startindex for any element
iel       =         -1; actual number of element while searching
iwarleer  =         1; is this the start of a new element
indx      =         0 ;character index
inewel    =         0 ;new element to find
;;LOOP
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Schar     strsub    Stray, indx, indx+1; this character
isep1p    strcmp    Schar, Sep1; returns 0 if Schar is sep1
isep2p    strcmp    Schar, Sep2; 0 if Schar is sep2
is_sep    =         (isep1p == 0 || isep2p == 0 ? 1 : 0) ;1 if Schar is a seperator
 ;END OF STRING AND NO SEPARATORS BEFORE?
 if indx == ilen && iwarleer == 0 then
Sel       strsub    Stray, istartsel, -1
inewel    =         1
 ;FIRST CHARACTER OF AN ELEMENT?
 elseif is_sep == 0 && iwarleer == 1 then
istartsel =         indx ;if so, set startindex
iwarleer  =         0 ;reset info about previous separator 
iel       =         iel+1 ;increment element count
 ;FIRST SEPERATOR AFTER AN ELEMENT?
 elseif iwarleer == 0 && is_sep == 1 then
Sel       strsub    Stray, istartsel, indx ;get elment
inewel    =         1 ;tell about
iwarleer  =         1 ;reset info about previous separator
 endif
 ;APPEND THE ELEMENT TO THE RESULT IF IN RANGE
 if inewel == 1 && iel >= istart && iel < iend then ;for each new element in range
Selsep    sprintf   "%c%s", isepOut, Sel ;prepend seperator
Sres      strcat    Sres, Selsep ;append to result
 endif
inewel    =         0
          loop_le   indx, 1, ilen, loop 
end:
Sout      strsub    Sres, 1; remove starting seperator
          xout      Sout
  endop 

  opcode StrayRmv, S, SSjjj
  ;removes the elements in Scmp from Src, and returns the result
  ;requires StrayLen and StrayMem
Src, Scmp, isepA, isepB, isepOut  xin
isepA      =          (isepA == -1 ? 32 : isepA)
isepOut    =          (isepOut == -1 ? isepA : isepOut)
SepOut     sprintf    "%c", isepOut
Sres       =          ""
ilen       StrayLen   Src, isepA, isepB
indx       =          0
loop:
Sel        StrayGetEl Src, indx, isepA, isepB
ismem      StrayElMem Scmp, Sel, isepA, isepB
 if ismem == -1 then
Sadd       sprintf    "%s%s%s", Sres, SepOut, Sel
Sres       strcpy     Sadd
 endif
           loop_lt    indx, 1, ilen, loop  
Sout       strsub     Sres, 1
           xout       Sout
  endop

  opcode StrayRemDup, S, Sjj
;removes duplicates in Stray and returns the result. elements are defined by two seperators as ASCII coded characters: isep1 defaults to 32 (= space), isep2 defaults to 9 (= tab). if just one seperator is used, isep2 equals isep1.
;requires the UDOs StrayLen and StrayGetEl
Stray, isepA, isepB xin
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
ilen1     StrayLen  Stray, isep1, isep2
Sres      =         ""
if ilen1 == 0 igoto end1 
indx1     =         0
loop1:
Sel       StrayGetEl Stray, indx1, isep1, isep2; get element
ires      =         0
ilen      StrayLen  Sres, isep1, isep2; length of Sres
if ilen == 0 igoto end 
indx      =         0
loop:	;iterate over length of Sres
Snext     StrayGetEl Sres, indx, isep1, isep2
icomp     strcmp    Snext, Sel
 if icomp == 0 then
ires      =         1
          igoto     end 
 endif
          loop_lt   indx, 1, ilen, loop 
end:		
 if ires == 0 then ;if element is not already in Sres, append
Sdran     sprintf   "%s%s", Sep1, Sel
Sres      strcat    Sres, Sdran
 endif

          loop_lt	indx1, 1, ilen1, loop1 
end1:		
Sout      strsub    Sres, 1; remove starting sep1
          xout      Sout
  endop 

  opcode Stray1Expr, i, S
  ;returns a number from a binary math expression (without any parentheses)
StrayEl   xin
isum      strindex  StrayEl, "+"; sum
idif      strindex  StrayEl, "-"; difference
ipro      strindex  StrayEl, "*"; product
irat      strindex  StrayEl, "/"; ratio
ipow      strindex  StrayEl, "^"; power
imod      strindex  StrayEl, "%"; modulo
 if ipow > 0 then
ifirst    strindex  StrayEl, "^"
S1        strsub    StrayEl, 0, ifirst
S2        strsub    StrayEl, ifirst+1
i1        strtod    S1
i2        strtod    S2
ires      =         i1 ^ i2
 elseif imod > 0 then
ifirst    strindex  StrayEl, "%"
S1        strsub    StrayEl, 0, ifirst
S2        strsub    StrayEl, ifirst+1
i1        strtod    S1
i2        strtod    S2
ires      =         i1 % i2
 elseif ipro > 0 then
ifirst    strindex  StrayEl, "*"
S1        strsub    StrayEl, 0, ifirst
S2        strsub    StrayEl, ifirst+1
i1        strtod    S1
i2        strtod    S2
ires      =         i1 * i2
 elseif irat > 0 then
ifirst    strindex  StrayEl, "/"
S1        strsub    StrayEl, 0, ifirst
S2        strsub    StrayEl, ifirst+1
i1        strtod    S1
i2        strtod    S2
ires      =         i1 / i2
 elseif isum > 0 then 
ifirst    strindex  StrayEl, "+"
S1        strsub    StrayEl, 0, ifirst
S2        strsub    StrayEl, ifirst+1
i1        strtod    S1
i2        strtod    S2
ires      =         i1 + i2
 elseif idif > -1 then
ifirst    strrindex StrayEl, "-";(last occurrence: -3-4 is possible, but not 3--4)
S1        strsub    StrayEl, 0, ifirst
S2        strsub    StrayEl, ifirst+1
iS1len    strlen    S1
 if iS1len == 0 then ;just a negative number
inum      strtod    S2
ires      =         -inum
 else	 
ifirst    strtod    S1
isec      strtod    S2
ires      =         ifirst - isec
  endif
 else
ires      strtod    StrayEl
 endif
          xout      ires
  endop 


  opcode StrayExpr, i, S
;parses one numerical expression (just one parenthesis allowed) and returns its result
Sin       xin
ilen      strlen    Sin
;if a parenthesis can be found
iparenth  strindex  Sin, "("
if iparenth > -1 then
  ;if in first half
  if iparenth == 0 then
    ;then first element ends in ")"
iprend    strindex   Sin, ")"
S1        strsub     Sin, 1, iprend
    ;convert this element into a number
i1        Stray1Expr S1
    ;append the rest and convert again
S2        strsub     Sin, iprend+2 
Sep       strsub     Sin, iprend+1, iprend+2
Scoll     sprintf    "%f%s%s", i1, Sep, S2
ires      Stray1Expr Scoll
  ;if the parenthesis in in the second half
  else
    ;isolate first element and the conjunction
S1        strsub     Sin, 0, iparenth-1
Sep       strsub     Sin, iparenth-1, iparenth
    ;convert the second element
S2        strsub     Sin, iparenth+1, ilen-1
i2        Stray1Expr S2
      ;if subtraction and i2 negative, convert to addition
isepminus strcmp     Sep, "-"
      if i2 < 0 && isepminus == 0 then
i2        =          i2 * (-1)
Sep       =          "+"
      endif
    ;convert the whole
Scoll     sprintf    "%s%s%f", S1, Sep, i2
ires      Stray1Expr Scoll
  endif
;if no parenthesis, simply convert
else	
ires      Stray1Expr Sin
endif
          xout       ires
  endop


  opcode StrayNumToFt, ii, Sojj
;puts all numbers in Stray (which must not contain non-numerical elements) in a function table and returns its variable ift (which is produced by iftno, default=0) and the length of the elements written iftlen. (an empty string as input writes a function table of size=1 to avoid an error but returns 0 as length of elements written.) simple binary math expressions like +, -, *, /, ^ and % are allowed, with just one parenthesis in total. 
;elements are defined by two seperators as ASCII coded characters: isep1 defaults to 32 (= space), isep2 defaults to 9 (= tab). if just one seperator is used, isep2 equals isep1.
;requires csound 5.15 or higher, and the UDOs StrayLen, Stray1Expr and StrayExpr
Stray, iftno, isepA, isepB xin
;;DEFINE THE SEPERATORS
isep1     =         (isepA == -1 ? 32 : isepA)
isep2     =         (isepA == -1 && isepB == -1 ? 9 : (isepB == -1 ? isep1 : isepB))
Sep1      sprintf   "%c", isep1
Sep2      sprintf   "%c", isep2
;;CREATE A FUNCTION TABLE
iftlen    StrayLen  Stray, isep1, isep2
 if iftlen == 0 then
          prints    "WARNING! StrayNumToFt got empty string as input. Function table with length=1 created, but iftlen=0 returned.\n"
iftl      =         1
 else
iftl      =         iftlen
 endif
ift       ftgen     iftno, 0, -iftl, -2, 0 
;;INITIALIZE SOME PARAMETERS
ilen      strlen    Stray
istartsel =         -1; startindex for searched element
iel       =         -1; number of element in Stray and ift
iwarleer  =         1; is this the start of a new element
indx      =         0 ;character index
inewel    =         0 ;new element to find
;;LOOP
 if ilen == 0 igoto end ;don't go into the loop if Stray is empty
loop:
Schar     strsub    Stray, indx, indx+1; this character
isep1p    strcmp    Schar, Sep1; returns 0 if Schar is sep1
isep2p    strcmp    Schar, Sep2; 0 if Schar is sep2
is_sep    =         (isep1p == 0 || isep2p == 0 ? 1 : 0) ;1 if Schar is a seperator
 ;END OF STRING AND NO SEPARATORS BEFORE?
 if indx == ilen && iwarleer == 0 then
Sel       strsub    Stray, istartsel, -1
inewel    =         1
 ;FIRST CHARACTER OF AN ELEMENT?
 elseif is_sep == 0 && iwarleer == 1 then
istartsel =         indx ;if so, set startindex
iwarleer  =         0 ;reset info about previous separator 
iel       =         iel+1 ;increment element count
 ;FIRST SEPERATOR AFTER AN ELEMENT?
 elseif iwarleer == 0 && is_sep == 1 then
Sel       strsub    Stray, istartsel, indx ;get element
inewel    =         1 ;tell about
iwarleer  =         1 ;reset info about previous separator
 endif
 ;WRITE THE ELEMENT TO THE TABLE
 if inewel == 1 then
inum      StrayExpr Sel ;convert expression to number
          tabw_i    inum, iel, ift ;write to ift
 endif
inewel    =         0
          loop_le   indx, 1, ilen, loop 
end:
          xout      ift, iftlen
  endop 
  
  opcode TbDmpSmpS, 0, iiSo
;prints the content of a table in a simple way, with an additional string as 'introduction'
ifn, iprec, String, ippr xin; function table, float precision while printing, String, parameters per row (maximum = 32)
ippr      =         (ippr == 0 ? 10 : ippr)
iend      =         ftlen(ifn)
indx      =         0
Sformat   sprintf   "%%.%df, ", iprec
Sdump     sprintf   "%s[", String
loop:
ival      tab_i     indx, ifn
Snew      sprintf   Sformat, ival
Sdump     strcat    Sdump, Snew
imod      =         (indx+1) % ippr
 if imod == 0 && indx != iend-1 then
          puts      Sdump, 1
Sdump     =         ""
 endif
          loop_lt   indx, 1, iend, loop
ilen      strlen    Sdump
Slast     strsub    Sdump, 0, ilen-2
		printf_i	"%s]\n", 1, Slast
  endop
