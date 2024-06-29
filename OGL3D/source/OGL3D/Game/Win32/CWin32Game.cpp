#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <Windows.h>

void OGame::run()
{
    onCreate();

    while(m_isRunning)
    {
        MSG msg = {};
        if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                m_isRunning = false;
                continue;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        onUpdateInternal();
    }

    onQuit();
}