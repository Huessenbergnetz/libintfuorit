TEMPLATE = subdirs

SUBDIRS += Intfuorit
SUBDIRS += translations
SUBDIRS += dox
SUBDIRS += imports

imports.depends = Intfuorit
