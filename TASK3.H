/*
 * TASK3.H
 *
 *  Created on: 13.09.2019
 *      Author: aml
 */

#ifndef TASK3_H_
#define TASK3_H_

#include <string>
#include <vector>

using namespace std;

namespace TASK3{

enum BlockState{CLEAR = 0, USED = 1, HIT = 2};
enum ShipState {INPROGRESS, ALIVE, DESTROYED};
enum ShipType  {FIVE=5, FOUR=4, THREE=3 ,TWO=2};

class Block{
public:
	int x_; // Koordinate of a block starting with value 1; value -1 means block not placed yet
	int y_; // Koordinate of a block starting with value 1; value -1 means block not placed yet
	BlockState state_ = CLEAR;
	Block(){x_=-1; y_=-1;state_=CLEAR;};
	Block(int x, int y, BlockState state){x_=x; y_=y; state_=CLEAR;};

	void print();
};


class Ship{
public:
	Block*         *blocks_;
	int            nmbBlocks_;
	ShipType       shipname_;
	ShipState      state_;

	void print();
};

class World{
public:
	World():World(10,10,1,2,3,4){};
	World(int maxX, int maxY, int nmbFiver, int nmbFourer, int nmbThreer, int nmbTwoer);
	string worldDrawing();

	virtual bool placeShips();

	void print();
	void printBoard();


protected:
	int    maxX_;
	int    maxY_;
	int    nmbShips_;
	Ship*  *ships_;


	virtual Ship* defaultShipFactory(int nmbBlocks);
	virtual bool placeSingleShip(int idxShip);
	BlockState coordAlreadyUsed(int x, int y);
	void removeAllBlockCoordFromShip(Ship *s);

};


} // namespace TASK3

#endif /* TASK3_H_ */
