armcc -g -O2 -I..\include -c --cpu Cortex-M3 main.c -o main.o
armcc -g -O2 -I..\include -c --cpu Cortex-M3 exceptions.c -o exceptions.o
armcc -g -O2 -I..\include -c --cpu Cortex-M3 -DSTANDALONE retarget.c -o retarget.o
armcc -g -O2 -I..\include -c --cpu Cortex-M3 uart.c -o uart.o
armcc -g -O2 -I..\include -c --cpu Cortex-M3 pseudo_intrinsics.c -o pseudo_intrinsics.o
armlink --inline --scatter=scatter.scat --info=unused main.o exceptions.o retarget.o uart.o pseudo_intrinsics.o -o build2.axf
pause
