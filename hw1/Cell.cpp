#include "Cell.h"
#include <iostream>
#include <string>

Cell::Cell(int row, int column) {
	this->row = row;
	this->column = column;
	visited = false;
	setWalls();
} 

void Cell::setWalls() {
	for (int i = 0; i < 4; i++) walls[i] = 1;
}

void Cell::setVisited(bool b) { visited = b; }
bool Cell::isVisited() { return visited; }

int Cell::getRow() { return row; }
int Cell::getColumn() { return column; }

//Removes the wall between current cell and next cell.
void Cell::removeWalls(Cell &next) {
  int x = column - next.column;
  int y = row - next.row;

  if (x == 1) {
    walls[LEFT] = 0;
    next.walls[RIGHT] = 0;
  } else if (x == -1) {
    walls[RIGHT] = 0;
    next.walls[LEFT] = 0;
  } else if (y == -1) {
    walls[TOP] = 0;
    next.walls[BOTTOM] = 0;
  } else if (y == 1) {
    walls[BOTTOM] = 0;
    next.walls[TOP] = 0;
  }
}

std::string Cell::cellInfo()
{
	return ("x=" + std::to_string(column) + " y=" + std::to_string(row) + " l=" + std::to_string(walls[LEFT]) + " r=" + 
		std::to_string(walls[RIGHT]) + " u=" + std::to_string(walls[TOP]) + " d=" + std::to_string(walls[BOTTOM]) + "\n");
}
