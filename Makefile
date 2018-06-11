CC = g++
BIN = efaces
OBJS = $(BUILD)/$(BIN).o $(BUILD)/eigenfaceClassifierBuilder.o $(BUILD)/util.o $(BUILD)/imageProcessing.o
CFLAGS = -std=c++11
INC = -I./include
LIB = `pkg-config --libs opencv --cflags dlib-1`

BUILD = ./src/obj
SRC = ./src

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) $(INC) $(LIB) $(LIBS)

$(BUILD)/%.o: $(SRC)/%.cpp 
	$(CC) -c -o $@ $< $(INC) $(CFLAGS) 

clean: 
	rm $(BUILD)/*.o
	rm $(BIN)