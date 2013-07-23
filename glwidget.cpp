/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


GLWidget* GLWidget::instance = 0;

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    qtGreen = QColor::fromRgbF(1,0,0,1);
    qtPurple = QColor(255,255,255);
}

GLWidget* GLWidget::getInstance()
{
    if(instance != 0)
    {
        return instance;
    }
    else
        throw QString("GLWidget not exist");
}


GLWidget::~GLWidget()
{
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}


QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}




void GLWidget::initializeGL()
{
    qglClearColor(qtPurple.dark());

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    

    simpleShader = new Shader();

    vertexAttr1 = simpleShader->getProgram()->attributeLocation("coord2d");
    matrixUniform1 = simpleShader->getProgram()->uniformLocation( "m_transform");

    // Create the vertex buffer.
    vertices.clear();
    vertices << QVector2D(100.25f,100.75f);
    vertices << QVector2D(-100.25f,100.75f);
    vertices << QVector2D(100.25f,100.25f);
    vertices << QVector2D(-100.25f,100.25f);
    RotationMatrix.setToIdentity();
    
    GLushort Static_index[] = {
         0,  1,  2,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
	    };
	indices.clear();
	for(size_t i = 0;i < sizeof(Static_index);i++)
	{
		indices.insert ( i, Static_index[i]);
	}
}



static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        RotationMatrix.rotate ( angle, 0.0f, 0.0f, 0.5f );
        emit xRotationChanged(angle);
        updateGL();
    }
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 0.2 * dy);
    }
    lastPos = event->pos();
}


void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}


void GLWidget::resetRotationMatrix()
{
    RotationMatrix.setToIdentity();
}


void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    QMatrix4x4 finalMatrix = projection;

    simpleShader->bind();

    simpleShader->getProgram()->enableAttributeArray(vertexAttr1);
    simpleShader->getProgram()->setAttributeArray(vertexAttr1, vertices.constData());
    simpleShader->getProgram()->setUniformValue(matrixUniform1, finalMatrix.transposed());

    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, indices.constData());

    simpleShader->getProgram()->disableAttributeArray(vertexAttr1);
    simpleShader->getProgram()->release();
}


void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    projection.ortho(0, width, height, 0, -1000.0f, 1000.0f);

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

