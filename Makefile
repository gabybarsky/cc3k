CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k 
MAINOBJ = main.o
FLOOROBJ = board.o chamber.o
CHAROBJ = character.o players/player.o players/shade.o players/goblin.o players/troll.o players/drow.o players/vampire.o
OBJECTS = ${MAINOBJ} ${FLOOROBJ} ${CHAROBJ}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
