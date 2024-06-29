#pragma once

#include <OGL3D/All.h>
#include "MyPlayer.h"

class MyGame : public OGame
{
public:
    MyGame();
    ~MyGame();

    virtual void onCreate();
    virtual void onUpdate(f32 deltaTime);
    virtual void onQuit();

private:
    f32 m_elapsedSeconds = 0.0f;
    MyPlayer* m_player = nullptr;
};