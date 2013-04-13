# This makefile is intended for use with GNU make.

TARGET=build1.axf

CC=armcc
AS=armasm
LD=armlink
AR=armar
FE=fromelf

# Select build rules based on Windows or Unix
ifdef WINDIR
DONE=@if exist $(1) echo Build completed.
RM=if exist $(1) del /q $(1)
SHELL=$(WINDIR)\\system32\\cmd.exe
else
ifdef windir
DONE=@if exist $(1) echo Build completed.
RM=if exist $(1) del /q $(1)
SHELL=$(windir)\\system32\\cmd.exe
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

build1.axf : main.o exceptions.o scatter.scat
	$(LD) --inline --scatter=scatter.scat --info=unused main.o exceptions.o -o build1.axf

main.o : main.c
	$(CC) -c $(CFLAGS) main.c

exceptions.o : exceptions.c
	$(CC) -c $(CFLAGS) exceptions.c
