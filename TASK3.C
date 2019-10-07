/*
 * TASK3.C
 *
 *  Created on: 13.09.2019
 *      Author: aml
 */


#include "TASK3.H"

#include <iostream>

namespace TASK3{

void demoTask3(){
	//TASK3::World w(10,10,1,2,3,4);
	TASK3::World w;
	int x,y;
	TASK3::ShootResult res;

	do{
		w.printBoard();
		cout << "x: "; cin >> x;
		cout << "y: "; cin >> y;
		res = w.shoot(x,y);
		cout << "shoot: (" << x << ", " << y << ") --> " << res << endl;
	}while(res != TASK3::GAME_OVER);
	w.printBoard();

}


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

	placeShips();

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

	if((x<1) || (y<1)) return BLOCK_USED;
	if((x>maxX_) || (y>maxY_)) return BLOCK_USED;

	// check coordinate
	for(int sIdx=0; sIdx<nmbShips_;sIdx++){ // go through the ships
		nmbBlocks = ships_[sIdx]->nmbBlocks_;
		for(int bIdx=0; bIdx < nmbBlocks; bIdx++){
			block = ((ships_[sIdx])->blocks_)[bIdx];
			// check coordinate
			if((block->x_ == x) && (block->y_ == y)){
				return block->state_;
			}
		}
	}
	return BLOCK_CLEAR;
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
		s->blocks_[i]->state_ = BLOCK_CLEAR;
	}
	s->state_ = INPROGRESS;
}

bool World::checkNeighborhood(int x, int y){
	if( ((x + 1) <=maxX_) && ((x - 1) > 0) ){
    	if(coordAlreadyUsed(x-1, y) == BLOCK_USED){ return true;};
    	if(coordAlreadyUsed(x+1, y) == BLOCK_USED){ return true;};
	}

	if( ((y + 1) <=maxY_) && ((y - 1) > 0) ){
    	if(coordAlreadyUsed(x, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x, y+1) == BLOCK_USED) return true;
	}

	if( (((x + 1) <=maxX_) && ((x - 1) > 0)) &&
	    (((y + 1) <=maxY_) && ((y - 1) > 0)) ){
    	if(coordAlreadyUsed(x, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x, y+1) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x+1, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x+1, y+1) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x-1, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x-1, y+1) == BLOCK_USED) return true;

    	if(coordAlreadyUsed(x-1, y) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x+1, y) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x-1, y+1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x+1, y+1) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x-1, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x+1, y-1) == BLOCK_USED) return true;

	}

	if(x == 1){
    	if(coordAlreadyUsed(x+1, y) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x+1, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x+1, y+1) == BLOCK_USED) return true;
	}

	if(y == 1){
    	if(coordAlreadyUsed(x, y+1) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x-1, y+1) == BLOCK_USED) return true;
    	if(coordAlreadyUsed(x+1, y+1) == BLOCK_USED) return true;
	}

	if(x == maxX_){
       	if(coordAlreadyUsed(x-1, y) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x-1, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x-1, y+1) == BLOCK_USED) return true;
	}

	if(y == maxY_){
       	if(coordAlreadyUsed(x, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x-1, y-1) == BLOCK_USED) return true;
       	if(coordAlreadyUsed(x+1, y-1) == BLOCK_USED) return true;
	}
	return false;
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

    // temporary storage for new blocks
    Block tmpBlocks[ship->nmbBlocks_];

	bool shipCompleted = false;
	do{ // get rand start coordinates
		nmbTries++;
		if(nmbTries > maxTries) return false; // give up no place for ship found

		horizontal = ((rand()%2) == 0);

		startCoordX = (rand() % maxX_) + 1;
		startCoordY = (rand() % maxY_) + 1;

		// check if coordinates are free
	    if(coordAlreadyUsed(startCoordX, startCoordY) == BLOCK_USED){
	    	continue;
	    };

	    // check if ship remains on the world
	    if(horizontal){
	    	if((startCoordX + ship->shipname_ - 1)  > maxX_){
	    		continue;
	    	}
	    }else{
	    	if((startCoordY + ship->shipname_ - 1)  > maxY_){
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
	    	if(coordAlreadyUsed(currCoordX, currCoordY) == BLOCK_USED){
	    		break;
	    	}
	    	// check neighborhood
	    	if(checkNeighborhood(currCoordX, currCoordY)){
	    		break;
	    	}

	    	// save current coordinates
	    	tmpBlocks[bIdx].x_ = currCoordX;
	    	tmpBlocks[bIdx].y_ = currCoordY;
	    	tmpBlocks[bIdx].state_ = BLOCK_USED;

    		shipCompleted = true;
	    }

	    for(int i=0; i < ship->nmbBlocks_;i++){
	    	ship->blocks_[i]->x_ = tmpBlocks[i].x_;
	    	ship->blocks_[i]->y_ = tmpBlocks[i].y_;
	    	ship->blocks_[i]->state_ = tmpBlocks[i].state_;
	    }
	}while(!shipCompleted);

	ship->state_ = ALIVE;

	return true;
}


ShootResult World::shoot(int x, int y){
	if(allShipsDestroyed()){
		return GAME_OVER;
	}

	if( (x > maxX_) || (y > maxY_) || (x < 1) || (y < 1)){
		return WATER;
	}

	Ship *s;
	Block *b;
	for(int idxShp = 0; idxShp < nmbShips_; idxShp++){
		s = ships_[idxShp];
		for(int idxBlk = 0; idxBlk < s->nmbBlocks_; idxBlk++){
			b = s->blocks_[idxBlk];
			if( (b->x_ == x) && (b->y_ == y)){
				b->state_ = BLOCK_HIT;
				if(isShipStillAlive(s)){
					return SHIP_HIT;
				}else{
					s->state_ = DESTROYED;

					if(allShipsDestroyed()){
						return GAME_OVER;
					}else{
						return SHIP_DESTROYED;
					}
				}
			}
		}
	}

	return WATER;
}

bool World::isShipStillAlive(Ship *s){
	Block *b;
	for(int idxBlk = 0; idxBlk < s->nmbBlocks_; idxBlk++){
		b = s->blocks_[idxBlk];
		if(b->state_ != BLOCK_HIT){
			return true;
		}
	}
	return false;
}

bool World::allShipsDestroyed(){
	for(int idxShp = 0; idxShp < nmbShips_; idxShp++){
		if( ships_[idxShp]->state_ != DESTROYED){
			return false;
		}
	}
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
	for(int y=1; y <= maxY_; y++){
		for(int x=1; x <= maxX_; x++){
			state = coordAlreadyUsed(x,y);
			if(state == BLOCK_USED){
				cout << "X";
			}else if(state == BLOCK_CLEAR){
				cout << "_";
			}else if(state == BLOCK_HIT){
				cout << "D";
			}else {
				cout << " ";
			}
		}
		cout << endl;
	}
}


}
