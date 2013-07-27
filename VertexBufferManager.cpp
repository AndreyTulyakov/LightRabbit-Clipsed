#include "VertexBufferManager.h"

VertexBufferManager* VertexBufferManager::instance = 0;

VertexBufferManager *VertexBufferManager::getInstance()
{
    if(instance == 0)
    {
        instance = new VertexBufferManager();
    }
    return instance;
}

void VertexBufferManager::deleteInstance()
{
    if(instance != 0){
        delete instance;
        instance = 0;
    }
}



VertexBufferManager::VertexBufferManager()
{
    initializeGLFunctions();

    glGenBuffers(2, vboIds);


    VBSize = 1000;
    VBUsed = 0;

    IBSize = 1000;
    IBUsed = 0;

    void* VBData = calloc (VBSize,1);
    void* IBData = calloc (IBSize,1);

    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, VBSize, VBData, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBSize, IBData, GL_DYNAMIC_DRAW);

    free(VBData);
    free(IBData);
}

VertexBufferManager::~VertexBufferManager()
{
    glDeleteBuffers(2, vboIds);
}
