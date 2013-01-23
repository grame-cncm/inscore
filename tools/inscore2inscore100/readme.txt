---------------------
  inscore2inscore100 
---------------------

inscore2inscore100 is a tool designed to convert inscore files to the new file format.
It supports files format from version 0.90 and less than 1.00
Files designed for a version less than 0.90 can be converted using inscore2inscore90

This new file format is introduced with INScore version 1.00
The changes are the following:
  - variables accept any number of values
  - all the OSC addresses support optional extension in the url form introduced
    for the 'watch' message (i.e. any.host.or.ip:portnum/the/osc/address)
  - 'watch' messages (watch, watch+, require) syntax changes : 
     they accept any number of messages as argument, enclosed in parenthesis 
     and separated by a comma)
  - string don't need to be quoted unless they include any other character than 
    letters, numbers and 
