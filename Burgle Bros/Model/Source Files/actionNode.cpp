#include "../Header Files/actionNode.h"

actionNode::actionNode() {
}

void actionNode::setData(int col, int row, int floor, string action) {
	sent = false;
	tilePos.col = col;
	tilePos.row = row;
	tilePos.floor = floor;
	myAction = action;
}

