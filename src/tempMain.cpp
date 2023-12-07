#include "Player.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Graphics.h"
#include "ImmovableSprite.h"
#include "Button.h"
#include "Label.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

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

class Monster : public MovableSprite {
public:
    Monster(int x, int y, int w, int h, std::string assetPath, Player* playerInstance) : MovableSprite(x, y, w, h, assetPath) 
    {
        player = playerInstance;
    }  
    static Monster* getInstance(int x, int y, int w, int h, std::string assetPath, Player* playerInstance)
    {
        return new Monster(x, y, w, h, assetPath, playerInstance);
    }

    void tick() override 
    {
        int playerX = player->getCurrentX();
        int playerY = player->getCurrentY();
        if (rect.x > playerX) {
            rect.x--;
        } 
        if (rect.x < playerX) {
            rect.x++;
        }
        if (rect.y > playerY) {
            rect.y--;
        }
        if (rect.y < playerY) {
            rect.y++;
        }
    }

private:
    Player* player;
};

void addMonsters(GameEngine& engine) {
    while (engine.isGameRunning()) {
        MovableSprite* monster = MovableSprite::getInstance(50, 50, 50, 325, "images/tempMonster.png");
        engine.addGameComponent(monster);

        // Sleep for twenty seconds before adding the next monster
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}


int main(int argc, char** argv) {
    //graphic.setScreenSize(500, 300);
    graphic.setCustomBackground(constants::gResPath + "images/grassBackground.png");

    Label* lbl = Label::getInstance(270, 100, 100, 70, "0");
    engine.addUIComponent(lbl);
    StartButton* startButton = new StartButton(lbl, &engine);
    engine.addUIComponent(startButton); 
    
    Player* player = Player::getInstance(425, 325, 50, 50, "images/tempPlayer.png");
    //player->setAdaptToYPosition(false);
    //player->setAdaptFactorToYPosition(1);
    engine.addGameComponent(player);

    ImmovableSprite* rock = ImmovableSprite::getInstance(50, 50, 50, 50, "images/rock.png");
    ImmovableSprite* rockTwo = ImmovableSprite::getInstance(900, 600, 50, 50, "images/rock.png");
    ImmovableSprite* rockThree = ImmovableSprite::getInstance(120, 230, 50, 50, "images/rock.png");
    ImmovableSprite* rockFour = ImmovableSprite::getInstance(500, 300, 50, 50, "images/rock.png");
    ImmovableSprite* rockFive = ImmovableSprite::getInstance(500, 650, 50, 50, "images/rock.png");
    ImmovableSprite* treeOne = ImmovableSprite::getInstance(50, 500, 150, 200, "images/tree.png");
    ImmovableSprite* treeTwo = ImmovableSprite::getInstance(800, 150, 175, 250, "images/tree.png");

    engine.addGameComponent(rock);
    engine.addGameComponent(rockTwo);
    engine.addGameComponent(rockThree);
    engine.addGameComponent(rockFour);
    engine.addGameComponent(rockFive);
    engine.addGameComponent(treeOne);
    engine.addGameComponent(treeTwo);

    Monster* monster = Monster::getInstance(150, 325, 42, 42, "images/tempMonster.png", player);
    engine.addGameComponent(monster);
    //std::thread monsterThread(addMonsters, std::ref(engine));


    engine.run();


    //monsterThread.join();

    return 0;
}
