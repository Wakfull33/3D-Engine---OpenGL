#pragma once
#include <memory>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <chrono>

class OWindow;
class OGame
{
public:
    OGame();
    ~OGame();

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onQuit();

    void run();
    void quit();

protected:
    bool m_isRunning = true;
    std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
    std::unique_ptr<OWindow> m_display;

    OVertexArrayObjectPtr m_polygonVAO;
    OUniformBufferPtr m_uniform;
    OShaderProgramPtr m_shader;

    std::chrono::system_clock::time_point m_previousTime;
    f32 m_scale = 0;
};