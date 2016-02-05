CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = a4q3
OBJECTS = main.o textprocess.o echo.o decorator.o dropfirst.o doublewords.o allcaps.o count.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
