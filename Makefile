CXX=g++
OS=$(shell uname)
FLAGS=-Wall -Wextra -std=c++17

FILE_MODEL=model
PATH_LIB=src/main/java/ru/school21/webcalculator/models/

all: build

build: build_lib
ifeq ($(OS), Linux)
	./mvnw clean compile package
else
	mvnw clean compile package
endif

build_lib:
ifeq ($(OS), Linux)
	$(CXX) $(FLAGS) -g -shared -fpic  -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" $(PATH_LIB)$(FILE_MODEL).cpp -o $(PATH_LIB)lib$(FILE_MODEL).so
else
	$(CXX) -c $(FLAGS) -I"${JAVA_HOME}\include" -I"${JAVA_HOME}\include\win32" $(PATH_LIB)$(FILE_MODEL).cpp -o $(PATH_LIB)$(FILE_MODEL).o
	$(CXX) -shared -o $(PATH_LIB)$(FILE_MODEL).dll $(PATH_LIB)$(FILE_MODEL).o -Wl,--add-stdcall-alias -static
endif


run: build
	java -Djava.library.path=$(PATH_LIB) -jar target/WebCalculator-0.0.1-SNAPSHOT.jar