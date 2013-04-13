armcc -g -O2 -I..\include -c --cpu Cortex-M3 main.c -o main.o
armcc -g -O2 -I..\include -c --cpu Cortex-M3 exceptions.c -o exceptions.o
armlink --inline --scatter=scatter.scat --info=unused main.o exceptions.o -o build1.axf
pause
