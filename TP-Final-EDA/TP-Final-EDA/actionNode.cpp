#include "actionNode.h"

actionNode::actionNode() {
}

void actionNode::setData(int col, int row, int floor, string action) {
	sent = false;
	tilePos[0] = col;
	tilePos[1] = row;
	tilePos[2] = floor;
	myAction = action;
}

