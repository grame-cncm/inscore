win32 { TEMPLATE = vcsubdirs }
else { TEMPLATE = subdirs }

# For visual studio project generation use : qmake main.pro -tp vc -r

CONFIG += ordered c++11
SUBDIRS = library.pro viewer.pro

#viewer.depends = library
