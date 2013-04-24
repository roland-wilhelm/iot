#!/bin/sh
makeindex=`which makeindex`
pdflatex=`which pdflatex`

$makeindex Beleg.nlo -s nomencl.ist -o Beleg.nls
$pdflatex Beleg.tex
echo "Zweiterlauf"
$makeindex Beleg.nlo -s nomencl.ist -o Beleg.nls
$pdflatex Beleg.tex
#echo Dritterlauf
$makeindex Beleg.nlo -s nomencl.ist -o Beleg.nls
$pdflatex Beleg.tex

/opt/Adobe/Reader9/bin/acroread Beleg.pdf
