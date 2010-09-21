======================================================
Interlude project (ANR-08-CORD-010)
------------------------------------------------------
GRAME - Centre national de creation musicale
http://www.grame.fr
research@grame.fr
======================================================
Copyright GRAME (c) 2009-2010

The lisp folder contains sample scripts and libs to address 
the Interlude Score Viewer. Only Lispworks is currently supported.

It makes use of the lisp cl-osc module (osc folder).
See at http://opensoundcontrol.org/implementation/cl-osc and 
http://fo.am/darcs/osc/ for more information and for the latest release.

Using lispworks requires also to have lispworks-udp installed (Lispworks folder). 
See at http://www.cliki.net/lispworks-udp for more information and for the latest release.

The glue between 'cl-osc' and 'lispworks-udp' is provided by 'oscoverudp.lisp', which is 
based on the IRCAM Open Music osc support.

You should evaluate the file 'example.lisp' while Interlude Score Viewer is running.

Credits:
- Chun TIAN (binghe) - NetEase.com, Inc. - for lispworks-udp
- the authors and contributors of cl-osc
- IRCAM OpenMusic - for the glue between 'cl-osc' and 'lispworks-udp'
