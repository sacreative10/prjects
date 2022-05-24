#pragma once
// this file is the header file for the GameState class
// Language: cpp

// should it be a enum class or a class?
class GameState
{
  public:
    enum State
    {
        PLAYING,
        PAUSED,
        GAME_OVER
    };
    // this is the constructor for the game state class
    // it takes in the state of the game
    GameState(State state);
    // this is the destructor for the game state class
    ~GameState();
    // this method is used to get the state of the game
    // it returns the state of the game
    State getState();
    // this method is used to set the state of the game
    // it takes in the state of the game
    void setState(State state);

  private:
    // this is the state of the game
    State state;
};
