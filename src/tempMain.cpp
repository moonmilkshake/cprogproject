#include "Constants.h"
#include "GameEngine.h"
#include "Player.h"
#include <string>
#include <iostream>

using namespace crane;

GameEngine engine;

int main(int argc, char** argv) {

    Player* player =  Player::getInstance(10, 700, 75, 75);
    engine.add(player);
    engine.run();


    return 0;
}
