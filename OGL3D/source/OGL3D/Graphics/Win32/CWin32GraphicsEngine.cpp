#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = "OGL3DDummyWindow";
    wc.lpfnWndProc = DefWindowProc;
    wc.style = CS_OWNDC;

    auto classId = RegisterClassEx(&wc);
    assert(classId);

    auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), "", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
     CW_USEDEFAULT, CW_USEDEFAULT,
     CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

    assert(dummyWindow);

    auto dummyDC = GetDC(dummyWindow);

    PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
    pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDesc.nVersion = 1;
    pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
    pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDesc.cColorBits = 32;
    pixelFormatDesc.cAlphaBits = 8;
    pixelFormatDesc.cDepthBits = 24;
    pixelFormatDesc.cStencilBits = 8;
    pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;

    auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);
    SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);

    auto dummyContext = wglCreateContext(dummyDC);
    assert(dummyContext);

    wglMakeCurrent(dummyDC, dummyContext);

    if(!gladLoadWGL(dummyDC))
        OGL3D_ERROR("OGraphicsEngine - Error - gladLoadWGL failed");

    if(!gladLoadGL())
        OGL3D_ERROR("OGraphicsEngine - Error - gladLoadGL failed");


    wglMakeCurrent(dummyDC, 0);
    wglDeleteContext(dummyContext);
    ReleaseDC(dummyWindow, dummyDC);
    DestroyWindow(dummyWindow);
}

OGraphicsEngine::~OGraphicsEngine()
{

}