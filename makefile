COMPILER := g++
FLAGS := -std=c++20 
INCLUDE_LIBS_FOLDER := -I/usr/local/include
LIBS := -pthread
TARGET := app
MAINFILE = main.cpp

OBJ := $(patsubst %.cpp, %.o, $(shell find src/ -name '*.cpp'))

all : $(TARGET)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
  LIBS += -lGL -lGLEW -lglfw
endif

ifeq ($(UNAME_S), Darwin)
  LIBS += -framework OpenGL -lGLEW -lglfw
	FLAGS += -arch x86_64
endif

UNAME_P := $(shell uname -p)

%.o : %.cpp
	@mkdir -p build bin
	$(COMPILER) $(FLAGS) ${INCLUDE_LIBS_FOLDER} -c $< -o bin/$(notdir $@)

$(TARGET) : $(OBJ)
	$(COMPILER) $(FLAGS) ${INCLUDE_LIBS_FOLDER} -c ${MAINFILE} -o bin/mainFile.o
	$(COMPILER) ${FLAGS} ${INCLUDE_LIBS_FOLDER} bin/mainFile.o $(shell find bin -name '*.o') -o build/$@.$(UNAME_P) $(LIBS)

clean:
	rm -f bin/*.o
	rm -f build/*
