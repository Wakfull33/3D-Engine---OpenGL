#pragma once
#include <OGL3D/OPrerequisites.h>
#include <memory>
#include <chrono>

class OGraphicsEngine;
class OEntitySystem;
class OWindow;
class OGame
{
public:
    OGame();
    virtual  ~OGame();

    void run();
    void quit();

    OEntitySystem* getEntitySystem();

protected:
    virtual void onCreate();
    virtual void onUpdate(f32 deltaTime){}
    virtual void onQuit();

private:
    void onUpdateInternal();

protected:
    bool m_isRunning = true;
    std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
    std::unique_ptr<OWindow> m_display;
    std::unique_ptr<OEntitySystem> m_entitySystem;

    OVertexArrayObjectPtr m_polygonVAO;
    OUniformBufferPtr m_uniform;
    OShaderProgramPtr m_shader;

    std::chrono::system_clock::time_point m_previousTime;
    f32 m_scale = 0;
};