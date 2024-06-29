#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <OGL3D/Graphics/OShaderProgram.h>
#include <OGL3D/Graphics/OUniformBuffer.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Math/OMat4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/Math/OVec2.h>
#include <OGL3D/Entity/OEntitySystem.h>

struct UniformData
{
    OMat4 world;
    OMat4 projection;
};

struct Vertex
{
    OVec3 position;
    OVec2 texCoord;
};

OGame::OGame()
{
    m_graphicsEngine = std::make_unique<OGraphicsEngine>();
    m_display = std::make_unique<OWindow>();
    m_entitySystem = std::make_unique<OEntitySystem>();

    m_display->makeCurrentContext();

    m_graphicsEngine->setViewport(m_display->getInnerSize());
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
    OVec3 positionList[] = 
    {
        //Front Face
        OVec3(-0.5f, -0.5f, -0.5f),
        OVec3(-0.5f, 0.5f, -0.5f),
        OVec3(0.5f, 0.5f, -0.5f),
        OVec3(0.5f, -0.5f, -0.5f),

        //Back Face
        OVec3(0.5f, -0.5f, 0.5f),
        OVec3(0.5f, 0.5f, 0.5f),
        OVec3(-0.5f, 0.5f, 0.5f),
        OVec3(-0.5f, -0.5f, 0.5f)
    };

    OVec2 texCoordsList[] = 
    {
        OVec2(0, 0),
        OVec2(0, 1),
        OVec2(1, 0),
        OVec2(1, 1)
    };

    Vertex verticesList[] = 
    {
        //Front Face
        {positionList[0], texCoordsList[1]},
        {positionList[1], texCoordsList[0]},
        {positionList[2], texCoordsList[2]},
        {positionList[3], texCoordsList[3]},
        
        //Back Face
        {positionList[4], texCoordsList[1]},
        {positionList[5], texCoordsList[0]},
        {positionList[6], texCoordsList[2]},
        {positionList[7], texCoordsList[3]},
        
        //Top Face
        {positionList[1], texCoordsList[1]},
        {positionList[6], texCoordsList[0]},
        {positionList[5], texCoordsList[2]},
        {positionList[2], texCoordsList[3]},
        
        //Bottom Face
        {positionList[7], texCoordsList[1]},
        {positionList[0], texCoordsList[0]},
        {positionList[3], texCoordsList[2]},
        {positionList[4], texCoordsList[3]},
        
        //Right Face
        {positionList[3], texCoordsList[1]},
        {positionList[2], texCoordsList[0]},
        {positionList[5], texCoordsList[2]},
        {positionList[4], texCoordsList[3]},
        
        //Left Face
        {positionList[7], texCoordsList[1]},
        {positionList[6], texCoordsList[0]},
        {positionList[1], texCoordsList[2]},
        {positionList[0], texCoordsList[3]}
    };

    ui32 indicesList[] =
    {
        //Front
        0, 1, 2,
        2, 3, 0,

        //Back
        4, 5, 6,
        6, 7, 4,

        //Top
        8, 9, 10,
        10, 11, 8,

        //Bottom
        12, 13, 14,
        14, 15, 12,

        //Right
        16, 17, 18,
        18, 19, 16,

        //Left
        20, 21, 22,
        22, 23, 20
    };

    // const f32 polygonVertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     1, 0, 0,
    //     -0.5f, 0.5f, 0.0f,
    //     0, 1, 0,
    //     0.5f, -0.5f, 0.0f,
    //     0, 0, 1,
    //     0.5f, 0.5f, 0.0f,
    //     1, 1, 0
    // };

    OVertexAttribute attribsList[] = {
        sizeof(OVec3)/sizeof(f32), //position
        sizeof(OVec2)/sizeof(f32)  //texcoord
    };

    m_polygonVAO = m_graphicsEngine->createVertexArrayObject(
        {
            (void *)verticesList,
            sizeof(Vertex),
            sizeof(verticesList)/sizeof(Vertex),

            attribsList,
            sizeof(attribsList)/sizeof(OVertexAttribute)
        },
        {
            (void *)indicesList,
            sizeof(indicesList)
        }
    );

    m_uniform = m_graphicsEngine->createUniformBuffer({
        sizeof(UniformData)
    });

    m_shader = m_graphicsEngine->createShaderProgram(
        {
            L"Assets/Shaders/BasicShader.vert",
            L"Assets/Shaders/BasicShader.frag"
        }
    );

    m_shader->setUniformBufferSlot("UniformData", 0);

}

void OGame::onUpdateInternal()
{
    // Computing delta time
    auto currentTime = std::chrono::system_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>();

    if(m_previousTime.time_since_epoch().count())
    {
        elapsedSeconds = currentTime - m_previousTime;
    }

    m_previousTime = currentTime;

    auto deltaTime = (f32)elapsedSeconds.count();



    onUpdate(deltaTime);
    m_entitySystem->update(deltaTime);



    m_scale += 0.14f * deltaTime;
    auto currentScale = abs(sin(m_scale));

    OMat4 world, projection, temp;
    temp.setIdentity();
    temp.setScale(OVec3(1.0f, 1.0f, 1.0f));
    world *= temp;

    temp.setIdentity();
    temp.setRotationZ(m_scale);
    world *= temp;

    temp.setIdentity();
    temp.setRotationY(m_scale);
    world *= temp;

    temp.setIdentity();
    temp.setRotationX(m_scale);
    world *= temp;

    temp.setIdentity();
    temp.setTranslation(OVec3(0, 0, 0));
    world *= temp;


    auto displaySize = m_display->getInnerSize();
    projection.setOrthoLH(displaySize.width * 0.004f, displaySize.height * 0.004f, 0.01f, 100.0f);


    UniformData data = { world, projection };
    m_uniform->setData(&data);

    m_graphicsEngine->clear(OVec4(0, 0, 0, 1));

    m_graphicsEngine->setFaceCulling(OCullType::BackFace);
    m_graphicsEngine->setWindingOrder(OWindingOrder::Clockwise);
    m_graphicsEngine->setVertexArrayObject(m_polygonVAO);
    m_graphicsEngine->setUniformBuffer(m_uniform, 0);
    m_graphicsEngine->setShaderProgram(m_shader);
    m_graphicsEngine->drawIndexedTriangles(OTriangleType::TriangleList, 36);

    m_display->present(false);
}

void OGame::onQuit()
{
}

void OGame::quit()
{
    m_isRunning = false;
}

OEntitySystem* OGame::getEntitySystem()
{
    return m_entitySystem.get();
}
