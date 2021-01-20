#include "earth.h"
#include <QVector2D>
#include <QVector3D>
#include <QDebug>

#include <QtCore/qmath.h>
struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};
earth::earth(GLFuncName *func)
    : m_func(func)
    , m_indexBuf(QOpenGLBuffer::IndexBuffer)
    , m_vertexShader(QOpenGLShader::Vertex)
    , m_fragmentShader(QOpenGLShader::Fragment)
    , m_texture(QOpenGLTexture::Target2D)
{
    initBuffer();
    initShader();
    initTexture();
}
earth::~earth()
{
    m_arrayBuf.destroy();
    m_indexBuf.destroy();
    m_texture.destroy();
}
void earth::initBuffer()
{
    m_arrayBuf.create();
    m_indexBuf.create();
    float UNIT_SIZE=2.0f;
        QList<float> alVertix;//存放顶点坐标的ArrayList
        float r=1.0f;
        float angleSpan = 10.0f;//将球进行单位切分的角度
        for(float vAngle=90;vAngle>-90;vAngle=vAngle-angleSpan)
        {
            //垂直方向angleSpan度一份
            for(float hAngle=360;hAngle>0;hAngle=hAngle-angleSpan)
            {
                //水平方向angleSpan度一份
                //纵向横向各到一个角度后计算对应的此点在球面上的坐标
                double xozLength=r*UNIT_SIZE*qCos(qDegreesToRadians(vAngle));
                float x1=(float)(xozLength*qCos(qDegreesToRadians(hAngle)));
                float z1=(float)(xozLength*qSin(qDegreesToRadians(hAngle)));
                float y1=(float)(r*UNIT_SIZE*qSin(qDegreesToRadians(vAngle)));
                xozLength=r*UNIT_SIZE*qCos(qDegreesToRadians(vAngle-angleSpan));
                float x2=(float)(xozLength*qCos(qDegreesToRadians(hAngle)));
                float z2=(float)(xozLength*qSin(qDegreesToRadians(hAngle)));
                float y2=(float)(r*UNIT_SIZE*qSin(qDegreesToRadians(vAngle-angleSpan)));
                xozLength=r*UNIT_SIZE*qCos(qDegreesToRadians(vAngle-angleSpan));
                float x3=(float)(xozLength*qCos(qDegreesToRadians(hAngle-angleSpan)));
                float z3=(float)(xozLength*qSin(qDegreesToRadians(hAngle-angleSpan)));
                float y3=(float)(r*UNIT_SIZE*qSin(qDegreesToRadians(vAngle-angleSpan)));
                xozLength=r*UNIT_SIZE*qCos(qDegreesToRadians(vAngle));
                float x4=(float)(xozLength*qCos(qDegreesToRadians(hAngle-angleSpan)));
                float z4=(float)(xozLength*qSin(qDegreesToRadians(hAngle-angleSpan)));
                float y4=(float)(r*UNIT_SIZE*qSin(qDegreesToRadians(vAngle)));
                //构建第一三角形
                alVertix.append(x1);alVertix.append(y1);alVertix.append(z1);
                           alVertix.append(x2);alVertix.append(y2);alVertix.append(z2);
                           alVertix.append(x4);alVertix.append(y4);alVertix.append(z4);
                           //构建第二三角形
                           alVertix.append(x4);alVertix.append(y4);alVertix.append(z4);
                           alVertix.append(x2);alVertix.append(y2);alVertix.append(z2);
                           alVertix.append(x3);alVertix.append(y3);alVertix.append(z3);
        }}
        vCount=alVertix.size()/3;
 texCoor = generateTexCoor((int)(360/angleSpan), (int)(180/angleSpan));


    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    //GLushort *indices =new GLushort[vCount];
GLushort indices[3888];
float vertices[3888*5];
  //  float *vertices=new float[vCount*5];
    for(int i=0;i<vCount;i++)
    {
        vertices[5*i]=alVertix.at(3*i);
        vertices[5*i+1]=alVertix.at(3*i+1);
        vertices[5*i+2]=alVertix.at(3*i+2);
        vertices[5*i+3]=texCoor[2*i];
        vertices[5*i+4]=texCoor[2*i+1];
        indices[i]=i;
    }

    m_indexCount = vCount;
    printf("%dsdgf/n",vCount);
    m_func->glGenVertexArrays(1, &m_vao);
    m_func->glBindVertexArray(m_vao);

    m_indexBuf.bind();
    m_indexBuf.allocate(indices, sizeof indices);

    m_arrayBuf.bind();
    m_arrayBuf.allocate(vertices, sizeof vertices);

    const int positionLocation = 0;
    m_func->glEnableVertexAttribArray(positionLocation);
    m_func->glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof (float)*5, nullptr);

    const int texCoordLocation =  1;
    m_func->glEnableVertexAttribArray(texCoordLocation);
    m_func->glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof (float)*5, (void *)(sizeof (float)*3));

    m_func->glBindVertexArray(0);
}

void earth::initShader()
{
    const auto vShader = u8R"(#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
uniform mat4 mvp;
out vec2 vTexCoord;
void main()
{
    vTexCoord = texCoord;
    gl_Position = mvp * vec4(position, 1.0);
}
)";
    const auto fShader = R"(#version 330 core
uniform sampler2D cubeTexture;
in vec2 vTexCoord;
out vec4 outColor;
void main()
{
    outColor = texture(cubeTexture, vTexCoord);
}
)";
    if (!m_vertexShader.compileSourceCode(vShader)) {
        qWarning() << m_vertexShader.log();
    }
    if (!m_fragmentShader.compileSourceCode(fShader)) {
        qWarning() << m_fragmentShader.log();
    }
}
void earth::initTexture()
{
    QImage img(":/assets/earth.png");
    m_texture.setData(img.mirrored());
    m_texture.setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture.setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture.setWrapMode(QOpenGLTexture::Repeat);
}
void earth::draw(QOpenGLShaderProgram &program, const QMatrix4x4 &model, const QMatrix4x4 &view, const QMatrix4x4 &project)
{
    program.removeAllShaders();
    program.addShader(&m_vertexShader);
    program.addShader(&m_fragmentShader);
    if (!program.link()) {
        qWarning() << program.log();
        return;
    }
    if (!program.bind()) {
        qWarning() << program.log();
        return;
    }
    program.setUniformValue("mvp", project * view * model);

    m_texture.bind();
    program.setUniformValue("cubeTexture", 0);

    m_func->glBindVertexArray(m_vao);

    m_func->glDrawElements(GL_TRIANGLE_STRIP, m_indexCount, GL_UNSIGNED_SHORT, nullptr);
}
float * earth::generateTexCoor(int bw,int bh)
{
    float *result = new float[bw*bh*6*2];
    float sizew=1.0f/bw;//列数
    float sizeh=1.0f/bh;//行数
    int c=0;
    for(int i=0;i<bh;i++)
    {
        for(int j=0;j<bw;j++)
        {
            //每行列一个矩形，由两个三角形构成，共六个点，12个纹理坐标
            float s=j*sizew;
            float t=i*sizeh;

            result[c++]=1-s;
            result[c++]=1-t;

            result[c++]=1-s;
            result[c++]=1-(t+sizeh);

            result[c++]=1-(s+sizew);
            result[c++]=1-t;

            result[c++]=1-(s+sizew);
            result[c++]=1-t;

            result[c++]=1-s;
            result[c++]=1-(t+sizeh);

            result[c++]=1-(s+sizew);
            result[c++]=1-(t+sizeh);
        }
    }
    return result;
}
