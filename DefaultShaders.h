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
