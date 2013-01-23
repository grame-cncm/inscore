Launch INScoreViewer first
Launch player.pd
In player.pd: 
 - load 07.wav
 - load tempo map 07.metro

Drag and drop DROP-ME.inscore to inscore
Start the pd player

Next you can drag and drop any inscore script while playing.

The sensor and signal folders: 
they contain alternate cursors in the form of graphic signals.
Stop and restart the pd player when switching to graphic signal
(because the object type changes, a new object is created and the current date is lost)
