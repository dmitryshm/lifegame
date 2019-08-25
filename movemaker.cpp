#include "movemaker.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QImage>
#include "utils.h"
#include "customimageprovider.h"

class MoveMakerRenderer : public QQuickFramebufferObject::Renderer,
                          protected QOpenGLFunctions
{
     friend class MoveMaker;

protected:
    MoveMakerRenderer() :
        m_texture(QOpenGLTexture::Target2D),
        m_itemWidth(0),
        m_itemHeight(0),
        m_imageLoc(-1),
        m_vertexLoc(-1),
        m_texCoordLoc(-1),
        m_isFirstInit(true)
    {
        initializeOpenGLFunctions();
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        m_shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
             "attribute vec2 vertex;\n"
             "attribute vec2 vertTexCoord;\n"
             "varying vec2 fragTexCoord;\n"
             "void main() {\n"
             "fragTexCoord = vertTexCoord;\n"
             "gl_Position = vec4(vertex, 0.0, 1.0);\n"
             "}\n");
        m_shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
            "//uniform sampler2D imagePattern;\n"
            "varying vec2 fragTexCoord;\n"
            "void main() {\n"
            "   gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);//texture2D(imagePattern, fragTexCoord);\n"
            "}\n");
        if (!m_shaderProgram.link())
        {
            return;
        }
        m_vertexLoc = m_shaderProgram.attributeLocation("vertex");
        m_texCoordLoc = m_shaderProgram.attributeLocation("vertTexCoord");
        //m_imageLoc = m_shaderProgram.uniformLocation("imagePattern");
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }

    virtual ~MoveMakerRenderer()
    {
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
    {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::NoAttachment);
        return new QOpenGLFramebufferObject(size, format);
    }

    void render()
    {
        if ((-1 == m_vertexLoc) || (-1 == m_texCoordLoc) /*|| (-1 == m_imageLoc)*/)
        {
            return;
        }
        const GLfloat vertexData[] = {
            0.0f, 0.0f,
            static_cast<float>(m_itemWidth), 0.0f,
            static_cast<float>(m_itemWidth), static_cast<float>(m_itemHeight),
            0.0f, static_cast<float>(m_itemHeight)
        };
        const GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
        const GLfloat uvData[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        if (!m_shaderProgram.bind())
        {
            qDebug() << "!m_shaderProgram.bind()";
            return;
        }
        m_texture.bind();
        m_shaderProgram.enableAttributeArray(m_vertexLoc);
        m_shaderProgram.enableAttributeArray(m_texCoordLoc);
        m_shaderProgram.setAttributeArray(m_vertexLoc, vertexData, 2, 0);
        m_shaderProgram.setAttributeArray(m_texCoordLoc, uvData, 2, 0);
        //m_shaderProgram.setUniformValue(m_imageLoc, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
        m_shaderProgram.disableAttributeArray(m_vertexLoc);
        m_shaderProgram.disableAttributeArray(m_texCoordLoc);
        m_texture.release();
        m_shaderProgram.release();
    }

    void synchronize(QQuickFramebufferObject *item)
    {
        MoveMaker *myitem = dynamic_cast<MoveMaker*>(item);
        if (nullptr == myitem)
        {
            return;
        }
        CustomImageProvider* imageProv = CustomImageProviderFromQmlObject(myitem);
        if (imageProv == nullptr)
        {
            return;
        }
        m_itemWidth = static_cast<GLsizei>(myitem->width());
        m_itemHeight = static_cast<GLsizei>(myitem->height());
        m_texture.destroy();
        m_texture.create();
        m_texture.setMinificationFilter(QOpenGLTexture::Nearest);
        m_texture.setMagnificationFilter(QOpenGLTexture::Nearest);
        m_texture.setWrapMode(QOpenGLTexture::ClampToEdge);
        QSize sizeRet, sizeReq;
        m_texture.setData(imageProv->requestImage("image", &sizeRet, sizeReq), QOpenGLTexture::MipMapGeneration::DontGenerateMipMaps);
    }

    void move()
    {

    }

private:
    QOpenGLTexture m_texture;
    QOpenGLShaderProgram m_shaderProgram;
    GLsizei m_itemWidth;
    GLsizei m_itemHeight;
    int m_imageLoc;
    int m_vertexLoc;
    int m_texCoordLoc;
    bool m_isFirstInit;
};

MoveMaker::MoveMaker(QQuickItem *parent) : QQuickFramebufferObject(parent)
{
}

QQuickFramebufferObject::Renderer* MoveMaker::createRenderer() const
{
    return new MoveMakerRenderer;
}

void MoveMaker::Move()
{
    update();
}
