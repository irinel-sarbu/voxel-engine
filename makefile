COMPILER := g++
FLAGS := -std=c++20
INCLUDE_LIBS_FOLDER := -I/usr/local/include -L/usr/local/lib
LIBS :=
TARGET := app

OBJ := $(patsubst %.cpp, %.o, $(shell find . -name '*.cpp'))

all : $(TARGET)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
  LIBS += -lGL -lGLEW -lglfw
endif

ifeq ($(UNAME_S), Darwin)
  LIBS += -framework OpenGL -lGLEW -lglfw
endif

UNAME_P := $(shell uname -p)

%.o : %.cpp
	$(COMPILER) $(FLAGS) ${INCLUDE_LIBS_FOLDER} -c $< -o bin/$(notdir $@)

$(TARGET) : $(OBJ)
	$(COMPILER) ${FLAGS} ${INCLUDE_LIBS_FOLDER} $(shell find bin -name '*.o') -o build/$@.$(UNAME_P) $(LIBS)

clean:
	rm bin/*.o
	rm build/*
