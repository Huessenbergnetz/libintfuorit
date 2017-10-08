#!/bin/bash

lrelease-qt5 -idbased translations/libintfuorit.ts

for LANG in de en_GB en_US sv
do
lrelease-qt5 -idbased translations/libintfuorit_$LANG.ts
done
