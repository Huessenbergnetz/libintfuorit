#!/bin/bash

lrelease-qt5 -idbased translations/libintfuorit.ts

for LANG in de
do
lrelease-qt5 -idbased translations/libintfuorit_$LANG.ts
done
