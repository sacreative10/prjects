// this file is the implementation file for the game state class
// Language: cpp

#include "GameState.h"

//@brief: this is the constructor for the game state class
//@param: state - the state of the game
GameState::GameState(State state)
{
    // this is the constructor for the game state class
    // it takes in the state of the game
    this->state = state;
}

//@brief: this is the destructor for the game state class
GameState::~GameState()
{
    delete this;
    // this is the destructor for the game state class
}

//@brief: this method is used to get the state of the game
//@return: the state of the game
GameState::State GameState::getState()
{
    // this method is used to get the state of the game
    // it returns the state of the game
    return state;
}

//@brief: this method is used to set the state of the game
//@param: state - the state of the game
void GameState::setState(State state)
{
    // this method is used to set the state of the game
    // it takes in the state of the game
    this->state = state;
}