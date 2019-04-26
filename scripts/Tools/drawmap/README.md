
[INScore](http://inscore.sf.net) - Mapping Utility
============================

This script is intended to collect graphic segments on arbitrary images and to print them in a convenient format to build an INScore mapping file.

--------------

## How to use

- open INScore and drop any image to the INScore scene
- adjust the image and/or the window so that the whole area that you intend to map fits in the window
- drop the `DROPME.inscore` script to the window: a new window will open with commands inside. The log window will also open: it will be used to print the mapping.
- you can start to draw rectangles on the image using the mouse


## The Drawmap Commands

- **Print** : print the current set of rectangles to the log window
- **Reset** : clears the current set of collected rectangles
- **Undo** : clear the last collected rectangle(s)
- **Restart** : equivalent to "Reset" + re-install the reactive handlers on the image. Use this command with every new image. 
- **Help** : displays this help.


## Tip and tricks

- you can use any INScore command in parallel to this tool e.g.
~~~~~~~~~
/ITL/scene/* scale 0.45;
~~~~~~~~~

- you should not change the image scale or position while you're collecting a mapping. In case you do so, the display will be incorrect although the collected information remains valid.

## Note about the time segments

The **Print** command generates a map with arbitrary time segments. Each segment has a quarter note duration and all segments are consecutive in time.



--------------

#### [Grame](http://www.grame.fr) - Centre National de Creation Musicale
