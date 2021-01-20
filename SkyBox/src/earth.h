#ifndef EARTH_H
#define EARTH_H
#include "GLHeaders.h"

class earth
{
public:
    earth(GLFuncName *func);
    ~earth();
    void draw(QOpenGLShaderProgram &program, const QMatrix4x4 &model, const QMatrix4x4 &view, const QMatrix4x4 &project);
private:
    void initBuffer();
    void initShader();
    void initTexture();
    float * earth::generateTexCoor(int bw,int bh);
    float *texCoor;
private:
    GLFuncName *m_func;
    QOpenGLBuffer m_arrayBuf;
    QOpenGLBuffer m_indexBuf;
    QOpenGLShader m_vertexShader;
    QOpenGLShader m_fragmentShader;
    QOpenGLTexture m_texture;
    quint32 m_vao;
    int m_indexCount = 0;
    int vCount=0;
};

#endif // EARTH_H
