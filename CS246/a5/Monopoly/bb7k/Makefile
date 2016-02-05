CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = bb7k
OBJECTS = main.o controller.o game.o player.o building.o ownableBuilding.o academic.o residence.o gym.o unownableBuilding.o collectOsap.o dcTimsLine.o goToTims.o gooseNesting.o tuition.o coopFee.o slc.o needlesHall.o view.o textDisplay.o cell.o improvable.o unimprovable.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
