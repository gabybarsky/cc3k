CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k 
MAINOBJ = main.o
FLOOROBJ = board.o chamber.o
CHAROBJ = character.o decorator.o potionDecorator.o
PLAYEROBJ = players/player.o players/shade.o players/goblin.o players/troll.o players/drow.o players/vampire.o 
ENEMYOBJ = enemies/enemy.o enemies/dragon.o enemies/dwarf.o enemies/elf.o enemies/halfling.o enemies/human.o enemies/merchant.o enemies/orc.o
OBJECTS = ${MAINOBJ} ${FLOOROBJ} ${CHAROBJ} ${PLAYEROBJ} ${ENEMYOBJ}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
