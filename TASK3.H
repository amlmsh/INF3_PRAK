/*
 * TASK3.H
 *
 *  Created on: 13.09.2019
 *      Author: aml
 */

/**
 *
 * \file TASK3.H
 *
 * \brief Contains namespace TASK3. Namespace TASK3 contains the implementation
 * of a the simplified game battle ship.
 *
 */


#ifndef TASK3_H_
#define TASK3_H_



#include <string>

using namespace std;

/**
 *
 * \namespace TASK3
 *
 * \brief Contains the implementation
 * of a the simplified game battle ship.
 *
 */
namespace TASK3{


/**
 *
 * \enum BlockState
 *
 *  Represents the states a Block can have.
 *
 */
enum BlockState  {BLOCK_CLEAR = 0, /**< BLOCK_CLEAR  is the initial state of a block. */
				  BLOCK_USED = 1,  /**< BLOCK_USED   tells that the block is part of a ship and not hit yet. */
				  BLOCK_HIT = 2  /**< BLOCK_HIT    tells that the block is prat of a hip and already hit.*/
};

/**
 *
 * \enum ShipState
 *
 * Represents the states a battle ship (see class Ship) can have.
 *
 */
enum ShipState   {INPROGRESS = 0, /**< INPROGRESS Ship is not finished yet, blocks are still missing.*/
				  ALIVE= 1, /**< ALIVE The ship is complete and nor block of the ship is hit yet. */
				  HIT = 2, /**< HIT At least one block of the ship is hit already*/
				  DESTROYED = 3 /**< DESTROYED All blocks of the ship are hit.*/
};


/**
 *
 * \enum ShipType
 *
 * Represents the types of battle ships used.
 * The number represents the number of blocks a ship consists of.
 *
 */
enum ShipType    {FIVE=5, /**< FIVE A battle ship that is built of five blocks.*/
				  FOUR=4, /**< FOUR A battle ship that is built of four blocks.*/
				  THREE=3, /**< THREE A battle ship that is built of three blocks.*/
				  TWO=2 /**< TWO A battle ship that is built of two blocks.*/
};

/**
 *
 * \enum ShootResult
 *
 * Represents the possible results a shot can have.
 *
 *
 */
enum ShootResult {WATER, /**< WATER The shot has not hit a block. */
	              SHIP_HIT, /**< SHIP_HIT The shot has hit a block. */
	              SHIP_DESTROYED, /**< SHIP_DESTROYED The shot has hit the last non-hit block. Now all blocks a ship are hit, the ship is destroyed.*/
	              ALL_SHIPS_DESTROYED, /**< ALL_SHIPS_DESTROYED With the shot all the ships in the game are destroyed now. */
	              GAME_OVER /**<  GAME_OVER With the shot all ships in the game are destroyed and the game is over.*/
};

/**
 *
 * \class Block
 *
 * \brief Implements a class that is the basic building block
 * of the game world.
 *
 * With a block ships are built. A block
 * can have different states thar are represented through BlockState
 * enum variable.
 *
 */
class Block{
public:
	int x_; // Coordinate of a block starting with value 1; value -1 means block not placed yet
	int y_; // Coordinate of a block starting with value 1; value -1 means block not placed yet
	BlockState state_ = BLOCK_CLEAR;
	Block(){x_=-1; y_=-1;state_=BLOCK_CLEAR;};
	Block(int x, int y, BlockState state){x_=x; y_=y; state_=BLOCK_CLEAR;};

	void print();
};

/**
 *
 * \class Ship
 *
 * \brief Implements the data structure for the battle ships.
 *
 * These ships
 * consists mainly of a number of blocks having different states.
 * The ship itself has a specific state which is determined  by the
 * states of the blocks.
 *
 */
class Ship{
public:
	Block*         *blocks_;
	int            nmbBlocks_;
	ShipType       shipname_;
	ShipState      state_;

	/**
	 *
	 * \brief Prints the state, properties and elements of the ship
	 * on standard output.
	 *
	 */
	void print();
};

/**
 *
 * \class World
 *
 * \brief This class represents the game board.
 *
 * A board has a specific dimension of NxM fields and specifies
 * the numbers of all single ship types (see enum ShipType).
 *
 * The game is played by interaction (method calls) of objects of
 * this class.
 *
 */
class World{
public:
	/**
	 *
	 * \brief Constructor which standard values for board dimension and
	 * number of ships of different types.
	 *
	 */
	World():World(10,10,1,2,3,4){};

	/**
	 *
	 * \brief parameterized constructor
	 *
	 * The board is filled by the constructor. Notice, the board building is
	 * made by a try-and-error strategy. If the number of ships is to large
	 * for the board dimension then the building process runs into a endless-loop.
	 *
	 * \param maxX int Dimension of X (should not be smaller than 10)
	 * \param maxY int Dimension of Y (should not be smaller than 10)
	 * \param nmbFiver int (>0) the number of ships built of five blocks
	 * \param nmbFourer int (>0) the number of ships built of four blocks
	 * \param nmbThreer int (>0) the number of ships built of three blocks
	 * \param nmbTwoer int (>0) the number of ships built of two blocks
	 *
	 */
	World(int maxX, int maxY, int nmbFiver, int nmbFourer, int nmbThreer, int nmbTwoer);

	/**
	 *
	 * \brief Executes a shot on the board.
	 *
	 * The result of the method delivers the success of the shot (see enum ShootResult )
	 *
	 *	\return ShootResult
	 */
	ShootResult shoot(int x, int y);

	/**
	 *
	 * \brief Prints all elements of the board and their current state
	 * on standard output.
	 *
	 */
	void print();

	/**
	 *
	 * \brief Prints the current state of the board on standard output as
	 * pseudo-graphic made of ascii-code.
	 *
	 */
	void printBoard();

private:

	/**
	 *
	 * \brief Places all ships on the board.
	 *
	 * Notice that some constraints are implemented here, like
	 * there shall be a gap of at least one field between all the
	 * ships.
	 *
	 *
	 */
	virtual bool placeShips();


	BlockState coordAlreadyUsed(int x, int y);
	bool checkNeighborhood(int x, int y);
	void removeAllBlockCoordFromShip(Ship *s);
	bool isShipStillAlive(Ship *s);
	bool allShipsDestroyed();

protected:
	int    maxX_;
	int    maxY_;
	int    nmbShips_;
	Ship*  *ships_;


	virtual Ship* defaultShipFactory(int nmbBlocks);
	virtual bool placeSingleShip(int idxShip);

};

/**
 *
 * \brief
 *
 * Runs a demo game of battle ship. The user is asked to
 * provide coordinates for shooting via manual input on the standard input.
 * After each shot the state of the game is printed on the standard output.
 * Untile all ships are destroyed and the game is over.
 */
void demoTask3();


} // namespace TASK3

#endif /* TASK3_H_ */
