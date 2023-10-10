all: build

build:
ifeq ($(OS), Linux)
	./mvnw clean compile package
else
	mvnw clean compile package
endif

run: build
	java -Djava.library.path=src/main/java/ru/school21/webcalculator/models -jar target/WebCalculator-0.0.1-SNAPSHOT.jar