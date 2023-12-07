#include "Player.h"
#include "Constants.h"
#include "GameEngine.h"
#include "Graphics.h"
#include "ImmovableSprite.h"
#include "ThrowableRock.h"
#include "Button.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
using namespace crane;

GameEngine engine;

class StartButton : public Button {
public:
    StartButton(GameEngine* engine, std::string upAssetPath, std::string downAssetPath) 
        : Button(400, 300, 150, 70, upAssetPath, downAssetPath), gameEngine(engine) {}

    void perform(Button* source) override {
        std::cout << "Starting game..." << std::endl;
        gameEngine->startGame();
        gameEngine->removeUIComponent(this);
    }

private:
    GameEngine* gameEngine;
};

class ResumeButton : public Button{
public:
    ResumeButton(GameEngine* engine, std::string upAssetPath, std::string downAssetPath)
        : Button(400, 200, 150, 70, upAssetPath, downAssetPath), gameEngine(engine) {}

        void perform(Button* source) override {
            gameEngine->togglePause();
        }

private:
    GameEngine* gameEngine;
};
/*
class QuitButton : public Button {
public:
    QuitButton(GameEngine* engine)
        : Button(400,400,150,70, "Quit"), gameEngine(engine) {}

    void perform(Button* source) override {
        gameEngine->quit();
    }

private:
    GameEngine* gameEngine;
};
*/

//Ifall vi vill lägga till en pauseKnapp. Just nu funkar den inte av att bara bortkommentera, 
//kan va för att jag inte satt en bild på den eller liknande i Button.
/*
class PauseButton : public Button {
public:
    PauseButton(GameEngine* engine) 
        : Button(400, 300, 150, 70, "Pause"), gameEngine(engine) {}

    void perform(Button* source) override {
        std::cout << "Toggling pause..." << std::endl;
        gameEngine->togglePause(); // This method should toggle the pause state in your GameEngine
    }

private:
    GameEngine* gameEngine;
};
*/


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

    void handleCollision(const Component* other)
    {
        const ThrowableRock* rockPtr = dynamic_cast<const ThrowableRock*>(other);
        if (rockPtr != nullptr) {
            engine.removeGameComponent(this);
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

//TODO: Implementera loop som lägger till monster
int main(int argc, char** argv) {
    //graphic.setScreenSize(500, 300);
    graphic.setCustomBackground(constants::gResPath + "images/grassBackground.png");

    StartButton* startButton = new StartButton(&engine, constants::gResPath + "images/start.png", constants::gResPath + "images/stentroll.png");
    engine.addUIComponent(startButton);
    ResumeButton* resumeButton = new ResumeButton(&engine, constants::gResPath + "images/resume.png", constants::gResPath + "images/start.png");
    engine.addPauseMenuComponent(resumeButton);
    //QuitButton* quitButton = new QuitButton(&engine);
   //engine.addUIComponent(quitButton);

    //PauseButton* pauseButton = new PauseButton(&engine);
    //engine.addUIComponent(pauseButton);
    
    Player* player = Player::getInstance(425, 325, 50, 50, "images/tempPlayer.png", &engine);
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

    Monster* monster = Monster::getInstance(150, 325, 42, 42, "images/stentroll.png", player);
    engine.addGameComponent(monster);
    //std::thread monsterThread(addMonsters, std::ref(engine));


    engine.run();
    delete startButton;
    delete resumeButton;
    //monsterThread.join();

    return 0;
}
