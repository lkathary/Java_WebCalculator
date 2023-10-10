#   java -cp . -Djava.library.path="C:/Users/Alex/calc_java/APJ2_SmartCalc_v3.0_Desktop_Java-1/src/calculator/src/main/java/com/example/calculator/models" -jar calculator.jar
#	g++ -c -I"C:\Users\Alex\.jdks\openjdk-19.0.1\include" -I"C:\Users\Alex\.jdks\openjdk-19.0.1\include\win32" model.cpp -o model.o
#	g++ -shared -o model.dll model.o -Wl,--add-stdcall-alias
#	g++ -g -shared -fpic -I"/usr/lib/jvm/java-11-openjdk-amd64/include" -I"/usr/lib/jvm/java-11-openjdk-amd64/include/linux" $(FILE_MODEL).cpp -o lib$(FILE_MODEL).so
#	'dylib' ext for MAC OS

.PHONY: header jni
CXX=g++
CAR=ar
CRANLIB=ranlib

FLAGS=-Wall -Wextra -std=c++17
# FLAGS=-Wall -Werror -Wextra -std=c++17

OS=$(shell uname)

FILE_MODEL=model

all: jni

header:
	javac -h . Model.java
	javac -h . CreditCalc.java

jni:

ifeq ($(OS), Linux)
#	!!! Attention !!!
#	$JAVA_HOME have to be set
#	For example:
#	export JAVA_HOME=`type -p java|xargs readlink -f|xargs dirname|xargs dirname`
#	Check:
#	echo $JAVA_HOME
	$(CXX) $(FLAGS) -g -shared -fpic  -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" $(FILE_MODEL).cpp -o lib$(FILE_MODEL).so
else
	$(CXX) -c $(FLAGS) -I"${JAVA_HOME}\include" -I"${JAVA_HOME}\include\win32" $(FILE_MODEL).cpp -o $(FILE_MODEL).o
	$(CXX) -shared -o $(FILE_MODEL).dll $(FILE_MODEL).o -Wl,--add-stdcall-alias -static
endif

clean:
	rm -rf  *.o *.a *.out *.class

rebuild:
	make clean
	make all
	rm -rf  *.o *.a

# Frequent typos/synonyms
claen:	clean
clear:	clean
claer:	clean
