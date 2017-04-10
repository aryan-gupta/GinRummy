
# Copyright (c) 2017 The Gupta Empire - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
#
# Written by Aryan Gupta <me@theguptaempire.net>
# 
# ==============================================================================
# @author 			Aryan Gupta
# @project 			Tic Tac Toe
# @file 			Makefile
# @date				2017-03-12 (YYYY-MM-DD)
# @version			1.0.0
# @brief 		This is the Makefile for The Tic Tac Toe Project
# ==============================================================================
.DEFAULT_GOAL := all
# ==========================  CONST MACROS  ====================================
CC = "g++.exe"
RES = "windres.exe"
OBJDIR = .\obj
BINDIR = .\bin
DATDIR = .\dat
INCDIR = .\inc

DEBUG = -g -DDEBUG=true

# ============================  SDL LIBS  ======================================
GRAPHICS = -w -Wl,-subsystem,windows
# Standard SDL libs
L_SDLC = -I.\SDL\include\SDL2 
L_SDLL = -L.\SDL\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer  -lSDL2_ttf  -lSDL2_image

# ==============================  MACROS  ======================================
CFLAGS = $(DEBUG) -Wall -std=c++17 -c
LFLAGS = $(DEBUG) -Wall
OBJ = $(OBJDIR)\main.o $(OBJDIR)\res.o $(OBJDIR)\Player.o $(OBJDIR)\CardPile.o $(OBJDIR)\Window.o $(OBJDIR)\Resources.o $(OBJDIR)\Human.o

# ============================ RECEPIES ========================================

$(OBJDIR)\main.o: .\main.cpp $(INCDIR)\main.h $(INCDIR)\Player.h $(INCDIR)\CardPile.h $(INCDIR)\Window.h $(INCDIR)\Resources.h
	$(CC) .\main.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)\Player.o: .\Player.cpp $(INCDIR)\Player.h $(INCDIR)\main.h $(INCDIR)\CardPile.h $(INCDIR)\Window.h $(INCDIR)\Resources.h
	$(CC) .\Player.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)\Human.o: .\Human.cpp $(INCDIR)\Human.h $(INCDIR)\main.h $(INCDIR)\CardPile.h $(INCDIR)\Window.h $(INCDIR)\Resources.h
	$(CC) .\Human.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)\CardPile.o: .\CardPile.cpp $(INCDIR)\CardPile.h $(INCDIR)\main.h $(INCDIR)\Window.h $(INCDIR)\Resources.h
	$(CC) .\CardPile.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)\Window.o: .\Window.cpp $(INCDIR)\Window.h $(INCDIR)\main.h $(INCDIR)\Player.h $(INCDIR)\CardPile.h $(INCDIR)\Resources.h
	$(CC) .\Window.cpp -o .\$@ $(CFLAGS) $(L_SDLC)
	
$(OBJDIR)\Resources.o: .\Resources.cpp $(INCDIR)\Resources.h $(INCDIR)\main.h $(INCDIR)\CardPile.h
	$(CC) .\Resources.cpp -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)\%.o: .\%.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)\res.o: .\res.rc .\info.h
	$(RES) .\res.rc  .\$@
	
# Link	
$(BINDIR)\main.exe: $(OBJ)
	$(CC) .\$^ -o .\$@ $(LFLAGS) $(L_SDLL)

# ============================= PHONY RECEPIES =================================
.PHONY: all
all: clean $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(LSDLL) $(LSDLIL) $(LSDLTL) -o $(BINDIR)\final.exe

.PHONY: link
link:
	$(CC) .\$^ $(LFLAGS) $(LSDLL) $(LSDLIL) $(LSDLTL) -o $(BINDIR)\main.exe	
	
.PHONY: clean
clean:
	del $(OBJDIR)\*.o
	del $(BINDIR)\*.exe