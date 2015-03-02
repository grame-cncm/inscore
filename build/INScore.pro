TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS = INScoreLib INScoreApp

INScoreApp.depends = INScoreLib
