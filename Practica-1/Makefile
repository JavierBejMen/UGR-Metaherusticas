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

TARGETS = clean $(BIN)/mainAM1001mej $(BIN)/mainAM1001 $(BIN)/mainAM101 $(BIN)/mainAGECA $(BIN)/mainAGEBLX $(BIN)/mainAGGCA $(BIN)/mainAGGBLX $(BIN)/main1nn $(BIN)/fileFormat $(BIN)/checkTam $(BIN)/mainRelief $(BIN)/mainBL

MAINDEPENDENCES = $(OBJ)/main.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o

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
	
$(OBJ)/mainRelief.o: $(SRC)/mainRelief.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainRelief: $(OBJ)/mainRelief.o $(OBJ)/utils.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Datos.o $(OBJ)/Dato.o
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJ)/mainBL.o: $(SRC)/mainBL.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)	
	
$(BIN)/mainBL: $(OBJ)/mainBL.o $(OBJ)/Algevo.o $(OBJ)/utils.o $(OBJ)/BL.o $(OBJ)/Clasificador.o $(OBJ)/Datos.o $(OBJ)/Dato.o
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJ)/main1nn.o: $(SRC)/main1nn.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/main1nn: $(OBJ)/main1nn.o $(OBJ)/utils.o $(OBJ)/Clasificador.o $(OBJ)/Datos.o $(OBJ)/Dato.o
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJ)/mainAGGBLX.o: $(SRC)/mainAGGBLX.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAGGBLX: $(OBJ)/mainAGGBLX.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAGGCA.o: $(SRC)/mainAGGCA.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAGGCA: $(OBJ)/mainAGGCA.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAGEBLX.o: $(SRC)/mainAGEBLX.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAGEBLX: $(OBJ)/mainAGEBLX.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAGECA.o: $(SRC)/mainAGECA.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAGECA: $(OBJ)/mainAGECA.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAM101.o: $(SRC)/mainAM101.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAM101: $(OBJ)/mainAM101.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAM1001.o: $(SRC)/mainAM1001.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAM1001: $(OBJ)/mainAM1001.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
$(OBJ)/mainAM1001mej.o: $(SRC)/mainAM1001mej.cpp
	$(CC) $(CCFLAGS) -c -o $@ $^ -I$(INCLUDE)
	
$(BIN)/mainAM1001mej: $(OBJ)/mainAM1001mej.o $(OBJ)/Algevo.o $(OBJ)/BL.o $(OBJ)/Relief.o $(OBJ)/Clasificador.o $(OBJ)/Dato.o $(OBJ)/Datos.o $(OBJ)/utils.o
	$(CC) $(CCFLAGS) -o $@ $^
	
# Clean
.PHONY: clean

clean:
	-rm $(BIN)/* $(OBJ)/*.o
