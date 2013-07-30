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

#ifndef DEFAULTSHADERS_H
#define DEFAULTSHADERS_H

#include <QString>
#include <QMap>
#include <QGLShaderProgram>

class DefaultShaders
{
public:

    static DefaultShaders* getInstance();
    static void deleteInstance();

    QGLShaderProgram* getShader(QString shaderName);



private:
    DefaultShaders();
    ~DefaultShaders();

    static DefaultShaders *instance;

    QMap<QString, QGLShaderProgram*> shaders;

    QGLShaderProgram* loadShaders(QString vsFilename, QString fsFilename);
};

#endif // DEFAULTSHADERS_H
