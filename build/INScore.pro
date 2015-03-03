TEMPLATE = subdirs

# For visual studio project generation use : qmake main.pro -tp vc -r

CONFIG += ordered
SUBDIRS = INScoreLib INScoreApp

INScoreApp.depends = INScoreLib
