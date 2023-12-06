#include "Player.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Graphics.h"
#include "ImmovableSprite.h"
#include "Button.h"
#include "Label.h"
#include <string>
#include <iostream>

using namespace crane;

GameEngine engine;

class StartButton : public Button {
public:
    StartButton(Label* lbl, GameEngine* engine) 
        : Button(400, 300, 150, 70, "Start"), label(lbl), gameEngine(engine) {}

    void perform(Button* source) override {
        std::cout << "Starting game..." << std::endl;
        gameEngine->startGame();
        gameEngine->removeUIComponent(this); // Remove the button when the game starts
    }

private:
    Label* label;
    GameEngine* gameEngine;
};


int main(int argc, char** argv) {
    Player* player = Player::getInstance(50, 525, 50, 50);
    //player->setAdaptToYPosition(false);
    //player->setAdaptFactorToYPosition(1);
    engine.addGameComponent(player); // Add as a game component
    ImmovableSprite* rock = ImmovableSprite::getInstance(50, 50, 50, 50, "images/rock.png");
    engine.addGameComponent(rock);
    graphic.setCustomBackground(constants::gResPath + "images/grassBackground.png");

    Label* lbl = Label::getInstance(270, 100, 100, 70, "0");
    engine.addUIComponent(lbl); // Add as a UI component
    StartButton* startButton = new StartButton(lbl, &engine);
    engine.addUIComponent(startButton); // Add as a UI component

    engine.run();

    return 0;
}
