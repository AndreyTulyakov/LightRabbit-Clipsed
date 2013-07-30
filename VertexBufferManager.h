/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QGLFunctions>


class VertexBufferManager: public QGLFunctions
{
public:

    static VertexBufferManager *getInstance();
    static void deleteInstance();

    void bind(int buffer);
    int addData(int sizeVertexData, void* vertexData, int sizeIndicesData, void* indicesData);


private:
    GLuint vboIds[2];

    VertexBufferManager();
    ~VertexBufferManager();

    static VertexBufferManager *instance;

    int VBSize;
    int VBUsed;

    int IBSize;
    int IBUsed;

};

#endif // VERTEXBUFFER_H
