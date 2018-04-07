# Makefile
# Practica 1
# Javier Bejar Mendez

BIN = bin
SRC = src
OBJ = obj
LIB = lib
INCLUDE = include

CC = c++
CCFLAGS = -std=c++11 -Wall -O3

TARGETS = clean $(BIN)/mainDERand $(BIN)/mainDEBest $(BIN)/mainILS $(BIN)/mainES $(BIN)/mainAMmej $(BIN)/mainBL $(BIN)/main $(BIN)/main1nn $(BIN)/mainAGGBLX $(BIN)/mainRelief

MAINDEPENDENCES = $(OBJ)/DE.o $(OBJ)/ILS.o $(OBJ)/ES.o $(OBJ)/main.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o

all: $(TARGETS)

#ejecutables auxiliares
$(BIN)/fileFormat: $(SRC)/fileFormat.cpp
	$(CC) $(CCFLAGS) -o $@ $^
	
$(BIN)/checkTam: $(SRC)/checkTam.cpp
	$(CC) $(CCFLAGS) -o $@ $^

#main
$(BIN)/main: $(MAINDEPENDENCES)
	$(CC) $(CCFLAGS) -o $@ $^ 
		
$(OBJ)/main.o: $(SRC)/main.cpp 
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/Dato.o: $(SRC)/Dato.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/Datos.o: $(SRC)/Datos.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/Clasificador.o: $(SRC)/Clasificador.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/Relief.o: $(SRC)/Relief.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/utils.o: $(SRC)/utils.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/BL.o: $(SRC)/BL.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/Algevo.o: $(SRC)/Algevo.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
		
$(OBJ)/ES.o: $(SRC)/ES.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(OBJ)/ILS.o: $(SRC)/ILS.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(OBJ)/DE.o: $(SRC)/DE.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

#Ejecutables -------------------------------------------------------------------->	
$(OBJ)/main1nn.o: $(SRC)/main1nn.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/main1nn: $(OBJ)/main1nn.o $(OBJ)/utils.o $(OBJ)/Clasificador.o $(OBJ)/Datos.o $(OBJ)/Dato.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAGGBLX.o: $(SRC)/mainAGGBLX.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAGGBLX: $(OBJ)/mainAGGBLX.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(BIN)/mainRelief: $(OBJ)/mainRelief.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainRelief.o: $(SRC)/mainRelief.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(BIN)/mainBL: $(OBJ)/mainBL.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainBL.o: $(SRC)/mainBL.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAMmej: $(OBJ)/mainAMmej.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAMmej.o: $(SRC)/mainAM1001mej.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainES: $(OBJ)/mainES.o $(OBJ)/Algevo.o $(OBJ)/ES.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainES.o: $(SRC)/mainES.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(BIN)/mainILS: $(OBJ)/mainILS.o $(OBJ)/ILS.o $(OBJ)/Algevo.o $(OBJ)/ES.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainILS.o: $(SRC)/mainILS.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(BIN)/mainDERand: $(OBJ)/mainDERand.o $(OBJ)/DE.o $(OBJ)/Algevo.o $(OBJ)/ES.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainDERand.o: $(SRC)/mainDERand.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)

$(BIN)/mainDEBest: $(OBJ)/mainDEBest.o $(OBJ)/DE.o $(OBJ)/Algevo.o $(OBJ)/ES.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainDEBest.o: $(SRC)/mainDEcurrent.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)


	

	
	
# Clean
.PHONY: clean

clean:
	-rm $(BIN)/* $(OBJ)/*.o
