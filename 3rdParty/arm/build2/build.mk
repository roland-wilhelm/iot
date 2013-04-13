# This makefile is intended for use with GNU make.

TARGET=build2.axf

CC=armcc
AS=armasm
LD=armlink
AR=armar
FE=fromelf

# Select build rules based on Windows or Unix
ifdef WINDIR
DONE=@if exist $(1) echo Build completed.
RM=if exist $(1) del /q $(1)
SHELL=$(WINDIR)\system32\cmd.exe
else
ifdef windir
DONE=@if exist $(1) echo Build completed.
RM=if exist $(1) del /q $(1)
SHELL=$(windir)\system32\cmd.exe
else
DONE=@if [ -f $(1) ]; then echo Build completed.; fi
RM=rm -f $(1)
endif
endif

all: $(TARGET)
	 $(call DONE,$(TARGET))

rebuild: clean all

clean:
	  $(call RM,*.o)
	  $(call RM,$(TARGET))

CFLAGS=-g -O2 --cpu=Cortex-M3 -I../include

build2.axf : main.o exceptions.o retarget.o uart.o pseudo_intrinsics.o scatter.scat
	$(LD) --inline --scatter=scatter.scat --info=unused main.o exceptions.o retarget.o uart.o pseudo_intrinsics.o -o build2.axf

main.o : main.c
	$(CC) -c $(CFLAGS) main.c

exceptions.o : exceptions.c
	$(CC) -c $(CFLAGS) exceptions.c

retarget.o : retarget.c
	$(CC) -c $(CFLAGS) -DSTANDALONE retarget.c

uart.o : uart.c
	$(CC) -c $(CFLAGS) uart.c

pseudo_intrinsics.o : pseudo_intrinsics.c
	$(CC) -c $(CFLAGS) pseudo_intrinsics.c
