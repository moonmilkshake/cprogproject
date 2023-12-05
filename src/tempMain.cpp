#include "Player.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Graphics.h"
#include "Button.h"
#include <string>
#include <iostream>

using namespace crane;

GameEngine engine;

class StartButton : public Button {
public:
    StartButton(Label* lbl) :Button(100,100,150,70,"Start"),label(lbl) {}
    void perform(Button* source){
        std::cout << "startknapp" << std::endl;
    }
private:
 Label* label;
};

int main(int argc, char** argv) {
    // Initialize the game engine
    Player* player = Player::getInstance(0, 500, 75, 75);
    engine.add(player);

    // Run the game engine
    engine.run();

    return 0;
}
