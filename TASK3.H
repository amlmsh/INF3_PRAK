/*
 * TASK3.H
 *
 *  Created on: 13.09.2019
 *      Author: aml
 */

#ifndef TASK3_H_
#define TASK3_H_

#include <string>

using namespace std;

namespace TASK3{

enum BlockState  {BLOCK_CLEAR = 0, BLOCK_USED = 1, BLOCK_HIT = 2};
enum ShipState   {INPROGRESS = 0, ALIVE= 1, HIT = 2, DESTROYED = 3};
enum ShipType    {FIVE=5, FOUR=4, THREE=3 ,TWO=2};
enum ShootResult {WATER, SHIP_HIT, SHIP_DESTROYED, ALL_SHIPS_DESTROYED, GAME_OVER};

class Block{
public:
	int x_; // Koordinate of a block starting with value 1; value -1 means block not placed yet
	int y_; // Koordinate of a block starting with value 1; value -1 means block not placed yet
	BlockState state_ = BLOCK_CLEAR;
	Block(){x_=-1; y_=-1;state_=BLOCK_CLEAR;};
	Block(int x, int y, BlockState state){x_=x; y_=y; state_=BLOCK_CLEAR;};

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

	ShootResult shoot(int x, int y);

	string worldDrawing();
	void print();
	void printBoard();

	virtual bool placeShips();


protected:
	int    maxX_;
	int    maxY_;
	int    nmbShips_;
	Ship*  *ships_;


	virtual Ship* defaultShipFactory(int nmbBlocks);
	virtual bool placeSingleShip(int idxShip);
	BlockState coordAlreadyUsed(int x, int y);
	bool checkNeighborhood(int x, int y);
	void removeAllBlockCoordFromShip(Ship *s);
	bool isShipStillAlive(Ship *s);
	bool allShipsDestroyed();
};

void demoTask3();


} // namespace TASK3

#endif /* TASK3_H_ */
