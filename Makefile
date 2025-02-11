
# Copyright (c) 2017 The Cool Group - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
#
# Written by:
# Harrison Read		<hread2@uncc.edu>
# Pichsapa Kulapruk	<pkulapru@uncc.edu>
# Aryan Gupta		<agupta40@uncc.edu>
# 
# ==============================================================================
# @author 			The Cool Group
# @project 			GinRummy
# @file 			Makefile
# @date				2017-03-12 (YYYY-MM-DD)
# @version			1.0.0
# @brief 			This is the Makefile for The GinRummy Project
# ==============================================================================
.DEFAULT_GOAL := all
# ==========================  CONST MACROS  ====================================
CC = "g++"
RES = "windres"
OBJDIR = ./obj
BINDIR = ./bin
DATDIR = ./dat
INCDIR = ./inc

# ============================  SDL LIBS  ======================================
L_SDLC = -I./SDL/include 
L_SDLL = $(GRAPHICS) -L./SDL/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer  -lSDL2_ttf  -lSDL2_image

# ==============================  MACROS  ======================================
CFLAGS = $(DEBUG) -Wall -std=c++11 -c
LFLAGS = $(DEBUG) -Wall
OBJ = $(OBJDIR)/main.o $(OBJDIR)/Player.o $(OBJDIR)/CardPile.o $(OBJDIR)/Window.o $(OBJDIR)/Resources.o $(OBJDIR)/Human.o $(OBJDIR)/Opponent.o $(OBJDIR)/res.o

# ============================ RECEPIES ========================================

$(OBJDIR)/main.o: ./main.cpp $(INCDIR)/main.h $(INCDIR)/CardPile.h $(INCDIR)/Player.h $(INCDIR)/Human.h $(INCDIR)/Opponent.h $(INCDIR)/Window.h $(INCDIR)/Resources.h
	$(CC) ./main.cpp -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/Player.o: ./Player.cpp $(INCDIR)/Player.h $(INCDIR)/main.h $(INCDIR)/CardPile.h $(INCDIR)/Window.h $(INCDIR)/Resources.h
	$(CC) ./Player.cpp -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/Human.o: ./Human.cpp $(INCDIR)/Human.h $(INCDIR)/main.h $(INCDIR)/CardPile.h $(INCDIR)/Window.h $(INCDIR)/Resources.h
	$(CC) ./Human.cpp -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/Opponent.o: ./Opponent.cpp $(INCDIR)/Opponent.h $(INCDIR)/main.h $(INCDIR)/CardPile.h $(INCDIR)/Window.h $(INCDIR)/Resources.h
	$(CC) ./Opponent.cpp -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/CardPile.o: ./CardPile.cpp $(INCDIR)/CardPile.h $(INCDIR)/main.h $(INCDIR)/Window.h $(INCDIR)/Resources.h
	$(CC) ./CardPile.cpp -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/Window.o: ./Window.cpp $(INCDIR)/Window.h $(INCDIR)/main.h $(INCDIR)/Player.h $(INCDIR)/Human.h $(INCDIR)/Opponent.h $(INCDIR)/CardPile.h $(INCDIR)/Resources.h
	$(CC) ./Window.cpp -o ./$@ $(CFLAGS) $(L_SDLC)
	
$(OBJDIR)/Resources.o: ./Resources.cpp $(INCDIR)/Resources.h $(INCDIR)/main.h $(INCDIR)/CardPile.h $(INCDIR)/Player.h $(INCDIR)/Window.h
	$(CC) ./Resources.cpp -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/%.o: ./%.cpp
	$(CC) ./$^ -o ./$@ $(CFLAGS) $(L_SDLC)

$(OBJDIR)/res.o: ./res.rc ./info.h
	$(RES) ./res.rc  ./$@
	
# Link	
$(BINDIR)/main.exe: DEBUG = -g -DDEBUG
$(BINDIR)/main.exe: $(OBJ)
	$(CC) ./$^ -o ./$@ $(LFLAGS) $(L_SDLL)
	
# Link	
$(BINDIR)/main: $(OBJ)
	$(CC) ./$^ -o ./$@ $(LFLAGS) $(L_SDLLM)

# ============================= PHONY RECEPIES =================================
.PHONY: all
all: clean $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(L_SDLL) -o $(BINDIR)/final.exe

.PHONY: install
install: DEBUG = -O2 -s -DNDEBUG
install: GRAPHICS = -w -Wl,-subsystem,windows
install: all Runner.cpp $(OBJDIR)/res.o
	$(CC) ./Runner.cpp $(OBJDIR)/res.o -static -o Play_GinRummy.exe
	Play_GinRummy.exe
	
.PHONY: clean
clean:
	del .\*.exe
	del .\obj\*.o
	del .\bin\*.exe