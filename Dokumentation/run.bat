"C:\Programme\MiKTeX 2.9\miktex\bin\makeindex" Beleg.nlo -s nomencl.ist -o Beleg.nls
"C:\Programme\MiKTeX 2.9\miktex\bin\pdflatex" Beleg.tex
echo Zweiterlauf
Pause
C:\Programme\MiKTeX 2.9\miktex\bin\makeindex Beleg.nlo -s nomencl.ist -o Beleg.nls
C:\Programme\MiKTeX 2.9\miktex\bin\pdflatex Beleg.tex
#echo Dritterlauf
#/usr/local/texlive/2009/bin/i386-linux/makeindex Beleg.nlo -s nomencl.ist -o Beleg.nls
#/usr/local/texlive/2009/bin/i386-linux/pdflatex Beleg.tex

#/opt/Adobe/Reader9/bin/acroread Beleg.pdf

#"%bm" 