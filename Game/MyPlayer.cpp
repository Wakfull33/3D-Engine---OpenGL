#include "MyPlayer.h"

MyPlayer::MyPlayer()
{
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::onCreate()
{
    m_entity = getEntitySystem()->createEntity<OEntity>();
}

void MyPlayer::onUpdate(f32 deltaTime)
{
    m_elapsedSeconds += deltaTime;

    if(m_entity && m_elapsedSeconds > 5.0f)
    {
        m_entity->release();
        m_entity = nullptr;
    }
}