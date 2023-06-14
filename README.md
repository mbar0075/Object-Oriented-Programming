# Object Oriented Programming Assignment

# Author
**Matthias Bartolo 0436103L**

## Preview:
<p align='center'>
  <img src="https://github.com/mbar0075/Object-Oriented-Programming/assets/103250564/2722ff5c-4272-43fe-b7f3-c5ce3c2d81eb" style="display: block; margin: 0 auto; width: 80%; height: auto;">
  <img src="https://github.com/mbar0075/Object-Oriented-Programming/assets/103250564/aa2a2572-45b7-4b86-af43-63f1b22a685e" style="display: block; margin: 0 auto; width: 40%; height: auto;">
  <img src="https://github.com/mbar0075/Object-Oriented-Programming/assets/103250564/46beaaf1-4917-4781-8488-d4302702210e" style="display: block; margin: 0 auto; width: 40%; height: auto;">
</p>

## Description of Task:
The following section encompasses two distinct tasks: the Village War Game and Minesweeper. Each task presents a unique game concept and objective, providing engaging challenges for players.

### **1. Village War Game (Turn-based Strategy)**
In the Village War Game, players controlled villages that were scattered across a map. Each village had distinct properties, including its location on a 2D coordinate system, health status, and owner. The objective was to strategically manage resources and construct various buildings within the village. Certain buildings generated resources, while others were used for training troops. Different types of troops had unique resource costs and stats.

Players had the option to send armies of troops to attack other villages, aiming to reduce their health and plunder resources upon a successful attack. Once a village's health reached zero, it was destroyed, and the player controlling that village was eliminated from the game. The ultimate goal was to be the last player with a surviving village.

At the beginning of a game session, players were prompted to specify the number of human players participating, along with the option to include AI players controlled by the game itself. Each player and AI participant had a village generated for them, with villages evenly distributed across the map.

```cpp
- class Troops{. . .};
- class Buildings{. . .};
- class ResourceGenerator : public Buildings{. . .};
- class Barracks : public Buildings{. . .};
- class Army{. . .};
> class Village{. . .};
- class Cell{. . .};
- class GameMapManager{. . .};
- class InputValidation{. . .};
```

### **2. Minesweeper**
The Minesweeper game was set on a 16x16 grid of cells, randomly generated with 40 mines scattered throughout. The objective was for a single player to clear the grid without detonating any mines.

During gameplay, the player selected uncleared cells one at a time. If a chosen cell contained a mine, the player lost the game. However, if the selected cell was the last uncleared cell without a mine, the player emerged victorious.

When a cell was chosen and did not contain a mine, but had adjacent mines, it was cleared, revealing the number of neighboring mines. In cases where the chosen cell and its surrounding cells were devoid of any mines, they were all cleared, and the number of adjacent mines for each cell was revealed.

```java
| public class Board{. . .};
| public class Cell{. . .};
| public class InputValidation{. . .};
> public class MainClass{. . .};
```

## Village War Game:


https://github.com/mbar0075/Object-Oriented-Programming/assets/103250564/d7932d4e-dc66-4ba7-ac40-0e7749a191bb


## Minesweeper:


## Deliverables:
The repository includes:<br />
1.**task1:** Directory which contains all the files for Task 1 (Village War Game)<br />
2.**task2:** Directory which contains all the files for Task 2 (Minesweeper)<br />
3.**report.pdf:** Assignment Documentation/Report

## Compiling and Running:
Firstly, to compile the program, in each directory, one needs to run the compile.sh shell script, in the command line.<br />
Secondly, to run the program, in each directory, one needs to run the run.sh shell script, in the command line.

## Other Notes:
The directories .idea and cmake-build-debug in the task1 directory are irrelevant, if the user is not using CLion as an IDe.
