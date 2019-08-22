#include "movemaker.h"
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "utils.h"
#include "customimageprovider.h"

class MoveMakerRenderer : public QQuickFramebufferObject::Renderer
{
     friend class MoveMaker;

protected:
    MoveMakerRenderer(const MoveMaker* mm) :
        m_mm(mm),
        m_hasInit(false),
        m_texture(QOpenGLTexture::TargetRectangle)
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
        if (m_mm == nullptr)
        {
            return;
        }
        if (!m_hasInit)
        {
            static const GLfloat vertexData[] = {
                0.0f, 0.0f,
                static_cast<float>(m_mm->width()), 0.0f,
                static_cast<float>(m_mm->width()), static_cast<float>(m_mm->height()),
                0.0f, static_cast<float>(m_mm->height())
            };
            static const GLfloat uvData[] = {
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f,
                0.0f, 1.0f
            };
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
            const int imageLoc = m_shaderProgram.uniformLocation("imagePattern");
            const int vertexLoc = m_shaderProgram.uniformLocation("vertex");
            const int textCoordLoc = m_shaderProgram.uniformLocation("vertTexCoord");
            if ((-1 == imageLoc) || (-1 == vertexLoc) || (-1 == textCoordLoc))
            {
                return;
            }
            m_shaderProgram.setUniformValueArray(vertexLoc, vertexData, 4, 2);
            m_shaderProgram.setUniformValueArray(textCoordLoc, uvData, 4, 2);
            m_shaderProgram.setUniformValue(imageLoc, 0);
            m_hasInit = true;
        }
        CustomImageProvider* imageProv = CustomImageProviderFromQmlObject(m_mm);
        if (imageProv == nullptr)
        {
            return;
        }
        QSize sizeRet, sizeReq;
        m_texture.setData(imageProv->requestImage("image", &sizeRet, sizeReq), QOpenGLTexture::MipMapGeneration::DontGenerateMipMaps);
        //--
        m_shaderProgram.bind();
        m_texture.bind();
        glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_SHORT, nullptr);
        m_shaderProgram.release();
    }

private:
    const MoveMaker* m_mm;
    bool m_hasInit;
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLTexture m_texture;
    QImage m_patternImage;
};

MoveMaker::MoveMaker(QQuickItem *parent) : QQuickFramebufferObject(parent)
{
}

QQuickFramebufferObject::Renderer* MoveMaker::createRenderer() const
{
    return new MoveMakerRenderer(this);
}
