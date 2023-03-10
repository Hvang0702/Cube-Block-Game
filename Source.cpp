
#include <iostream>
#include "Game.h"

int main(){

    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));
   
    Game game;

    //Game loop
    while (game.running() && !game.getEndGame()) { //!game.getEndGame() quits the game automatically by itself


        //Update
        game.update();

        //Render
        game.render();

        //Draw your game

    }

    //End of applicaiton
    return 0;

}