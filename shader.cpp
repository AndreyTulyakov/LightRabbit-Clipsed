#include "shader.h"

#include <QGLShader>


Shader::Shader()
{
    QGLShader *vshader = new QGLShader(QGLShader::Vertex);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment);

    const char *vSource =
        "#version 120\n"  // OpenGL 2.1
        "attribute vec2 coord2d;                  \n"
        "uniform mat4 m_transform;                \n"
        "void main(void) {                        \n"
        "  vec4 pos =  vec4(coord2d, 0.0, 1.0);   \n"
        "  gl_Position = m_transform * pos;       \n"
        "}\n";

    const char *fSource =
        "#version 120\n"  // OpenGL 2.1
        "void main(void) {        \n"
        "  gl_FragColor[0] = 0.0; \n"
        "  gl_FragColor[1] = 0.0; \n"
        "  gl_FragColor[2] = 1.0; \n"
        "}\n";

    vshader->compileSourceCode(vSource);
    fshader->compileSourceCode(fSource);

    program.addShader(vshader);
    program.addShader(fshader);

    program.link();

}

QGLShaderProgram *Shader::getProgram()
{
    return &program;
}

void Shader::bind()
{
    program.bind();
}

QString Shader::loadFromFile(QString filename)
{
    QString data = "";
    return data;
}
