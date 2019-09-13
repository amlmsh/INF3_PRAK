/*
 * TASK3.C
 *
 *  Created on: 13.09.2019
 *      Author: aml
 */


#include "TASK3.H"

#include <iostream>

namespace TASK3{

World::World(int maxX, int maxY, int nmbFiver, int nmbFourer, int nmbThreer, int nmbTwoer){
	if(maxX < 10){
		maxX_ = 10;
	}else{
		maxX_ = maxX;
	}

	if(maxY < 10){
		maxY_ = 10;
	}else{
		maxY_ = maxY;
	}
	nmbShips_ = nmbFiver + nmbFourer + nmbThreer + nmbTwoer;

	ships_ = new Ship*[nmbShips_];
	int idx = 0;
	//5er
	for(int i=0; i < nmbFiver;i++){
		ships_[idx] = defaultShipFactory(FIVE);
		idx++;
	}

	//4er
	for(int i=0; i < nmbFourer;i++){
		ships_[idx] = defaultShipFactory(FOUR);
		idx++;
	}

	//3er
	for(int i=0; i < nmbThreer;i++){
		ships_[idx] = defaultShipFactory(THREE);
		idx++;
	}

	//2er
	for(int i=0; i < nmbTwoer;i++){
		ships_[idx] = defaultShipFactory(TWO);
		idx++;
	}

	//placeShips();

	return;
}



Ship *World::defaultShipFactory(int nmbBlocks){
	Ship *ship;
	Block *block;

	ship = new Ship();
	ship->state_ = INPROGRESS;
	ship->shipname_= (ShipType) nmbBlocks;
	ship->nmbBlocks_ = nmbBlocks;
	ship->blocks_ = new Block*[nmbBlocks];

	for(int i=0; i<nmbBlocks;i++){
		ship->blocks_[i] = new Block();
	}
	return ship;
}

/**
 *
 *
 *
 */
BlockState World::coordAlreadyUsed(int x, int y){
	int nmbBlocks;
	Block *block;

	if((x<1) || (y<1)) return USED;
	if((x>maxX_) || (y>maxY_)) return USED;

	// check coordinate
	for(int sIdx=0; sIdx<nmbShips_;sIdx++){ // go through the ships
		nmbBlocks = ships_[sIdx]->nmbBlocks_;
		for(int bIdx=0; bIdx < nmbBlocks; bIdx++){
			block = ((ships_[sIdx])->blocks_)[bIdx];
			// check coordinate
			if((block->x_ == x) && (block->y_ == y)){
				return USED;
			}

			if((block->x_ < 1) && (block->y_ < 1)){
				return CLEAR;
			}
		}
	}
	return CLEAR;
}

bool World::placeShips(){
	int sIdx = 0;
	do{
		if(!placeSingleShip(sIdx)){
			if(sIdx > 0){
				sIdx = sIdx - 1;
				removeAllBlockCoordFromShip(ships_[sIdx]);
				continue;
			}else{
				continue;
			}
		}
		sIdx++;
	}while(sIdx < nmbShips_);
	return true;
}

void World::removeAllBlockCoordFromShip(Ship *s){
	for(int i; i < s->nmbBlocks_; i++){
		s->blocks_[i]->x_ = -1;
		s->blocks_[i]->y_ = -1;
		s->blocks_[i]->state_ = CLEAR;
	}
	s->state_ = INPROGRESS;
}

bool World::placeSingleShip(int idxShip){
	int startCoordX;
	int startCoordY;
	int currCoordX;
	int currCoordY;
	int nmbTries = 0;
	int maxTries = 10;

	Ship *ship = ships_[idxShip];
	bool horizontal = ((rand()%2) == 0);

	bool shipCompleted = false;
	do{ // get rand start coordinates
		nmbTries++;
		if(nmbTries > maxTries) return false; // give up no place for ship found

		startCoordX = (rand() % maxX_) + 1;
		startCoordY = (rand() % maxY_) + 1;

		// check if coordinates are free
	    if(coordAlreadyUsed(startCoordX, startCoordY) == USED){
	    	continue;
	    };

	    // check if ship remains on the world
	    if(horizontal){
	    	if(startCoordX + ship->shipname_ > maxX_){
	    		continue;
	    	}
	    }else{
	    	if(startCoordY + ship->shipname_ > maxY_){
	    		continue;
	    	}
	    }

		// fill blocks of the ship with the coordinates and neighbors
	    for(int bIdx=0; bIdx < ship->nmbBlocks_; bIdx++){
    		shipCompleted = false;
	    	if(horizontal){
	    		currCoordX = startCoordX + bIdx;
	    		currCoordY = startCoordY;
	    	}else{
	    		currCoordX = startCoordX;
	    		currCoordY = startCoordY + bIdx;
	    	}
	    	// check coord.
	    	if(coordAlreadyUsed(currCoordX, currCoordY) == USED){
	    		removeAllBlockCoordFromShip(ship);
	    		break;
	    	}

    		ship->blocks_[bIdx]->x_ = currCoordX;
    		ship->blocks_[bIdx]->y_ = currCoordY;
    		ship->blocks_[bIdx]->state_ = USED;

    		shipCompleted = true;
	    }
	}while(!shipCompleted);

	ship->state_ = ALIVE;

	return true;
}

void Block::print(){
	cout << "X: " << x_ << " Y: " << y_ << " state: " << state_<< endl;

}

void Ship::print(){
	cout << "type: " << shipname_ << " sate: " << state_ << " nmbBlocks: " << nmbBlocks_ << endl;
	for(int i=0; i < nmbBlocks_; i++){
		blocks_[i]->print();
	}
}

void World::print(){
	cout << "maxX: " << maxX_ << " maxY: " << maxY_ << " nmbShips " << nmbShips_ << endl;
	for(int i=0; i < nmbShips_; i++){
		ships_[i]->print();
	}
}

void World::printBoard(){
	BlockState state;
	for(int x=1; x <= maxX_; x++){
		for(int y=1; y <= maxY_; y++){
			state = coordAlreadyUsed(x,y);
			if(state == USED){
				cout << "X";
			}else if(state == CLEAR){
				cout << "0";
			}else {
				cout << " ";
			}
		}
		cout << endl;
	}
}


}
