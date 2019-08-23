#include "movemaker.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QImage>
#include "utils.h"
#include "customimageprovider.h"

class MoveMakerRenderer : public QQuickFramebufferObject::Renderer
{
     friend class MoveMaker;

protected:
    MoveMakerRenderer() :
        m_texture(QOpenGLTexture::Target2D),
        m_itemWidth(0),
        m_itemHeight(0),
        m_imageLoc(-1),
        m_vertexLoc(-1),
        m_texCoordLoc(-1)
    {
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
        if ((-1 == m_vertexLoc) || (-1 == m_texCoordLoc) || (-1 == m_imageLoc))
        {
            return;
        }
        const GLfloat vertexData[] = {
            0.0f, 0.0f,
            static_cast<float>(m_itemWidth), 0.0f,
            static_cast<float>(m_itemWidth), static_cast<float>(m_itemHeight),
            0.0f, static_cast<float>(m_itemHeight)
        };
        const GLfloat uvData[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };
        glViewport(0, 0, m_itemWidth, m_itemHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        if (!m_shaderProgram.bind())
        {
            qDebug() << "!m_shaderProgram.bind()";
            return;
        }
        m_texture.bind();
        m_shaderProgram.setUniformValueArray(m_vertexLoc, vertexData, 4, 2);
        m_shaderProgram.setUniformValueArray(m_texCoordLoc, uvData, 4, 2);
        m_shaderProgram.setUniformValue(m_imageLoc, 0);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        m_texture.release();
        m_shaderProgram.release();
        update();
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
        m_shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
             "uniform vec2 vertex;\n"
             "uniform vec2 vertTexCoord;\n"
             "varying vec2 fragTexCoord;\n"
             "void main() {\n"
             "fragTexCoord = vertTexCoord;\n"
             "gl_Position = vec4(vertex, 0.0, 1.0);\n"
             "}\n");
        m_shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
            "uniform sampler2D imagePattern;\n"
            "varying vec2 fragTexCoord;\n"
            "void main() {\n"
            "   gl_FragColor = texture2D(imagePattern, fragTexCoord);\n"
            "}\n");
        if (!m_shaderProgram.link())
        {
            return;
        }
        m_vertexLoc = m_shaderProgram.uniformLocation("vertex");
        m_texCoordLoc = m_shaderProgram.uniformLocation("vertTexCoord");
        m_imageLoc = m_shaderProgram.uniformLocation("imagePattern");
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
    //this->window()
}
