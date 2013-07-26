#ifndef SHADER_H
#define SHADER_H

#include <QGLShaderProgram>

class Shader
{
    public:
        Shader();
        QGLShaderProgram *getProgram();
        void bind();

    private:
        QString loadFromFile(QString filename);
        QGLShaderProgram program;


};

#endif // SHADER_H
