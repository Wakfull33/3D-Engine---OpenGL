#include "MyGame.h"

MyGame::MyGame()
{

}

MyGame::~MyGame()
{
    
}

void MyGame::onCreate()
{
    OGame::onCreate();
    m_player = getEntitySystem()->createEntity<MyPlayer>();
}

void MyGame::onUpdate(f32 deltaTime)
{
    OGame::onUpdate(deltaTime);
}

void MyGame::onQuit()
{
    OGame::onQuit();
}