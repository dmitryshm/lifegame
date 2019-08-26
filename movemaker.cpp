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
        //m_texSizeLoc(-1),
        m_isFirstInit(true)
    {
        initializeOpenGLFunctions();
        m_shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
             "attribute vec2 vertex;\n"
             "attribute vec2 vertTexCoord;\n"
             "varying vec2 fragTexCoord;\n"
             "void main() {\n"
             "    fragTexCoord = vertTexCoord;\n"
             "    gl_Position = vec4(vertex, 0.0, 1.0);\n"
             "}\n");
        m_shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
            "uniform sampler2D imagePattern;\n"
            "varying vec2 fragTexCoord;\n"
            "uniform vec2 texSize;\n"
            "void main() {\n"
            "   float tx = 1.0/texSize.x;\n"
            "   float ty = 1.0/texSize.y;\n"
            "   float xm = fragTexCoord.x + 1.0 - tx - step(tx, fragTexCoord.x);\n"
            "   float ym = fragTexCoord.y + 1.0 - ty - step(ty, fragTexCoord.y);\n"
            "   float xp = fragTexCoord.x + tx - step(1.0, fragTexCoord.x + tx);\n"
            "   float yp = fragTexCoord.y + ty - step(1.0, fragTexCoord.y + ty);\n"
            "   vec4 coo = texture2D(imagePattern, fragTexCoord);\n"
            "   vec4 cmm = texture2D(imagePattern, vec2(xm, ym));\n"
            "   vec4 com = texture2D(imagePattern, vec2(fragTexCoord.x, ym));\n"
            "   vec4 cpm = texture2D(imagePattern, vec2(xp, ym));\n"
            "   vec4 cmo = texture2D(imagePattern, vec2(xm, fragTexCoord.y));\n"
            "   vec4 cpo = texture2D(imagePattern, vec2(xp, fragTexCoord.y));\n"
            "   vec4 cmp = texture2D(imagePattern, vec2(xm, yp));\n"
            "   vec4 cop = texture2D(imagePattern, vec2(fragTexCoord.x, yp));\n"
            "   vec4 cpp = texture2D(imagePattern, vec2(xp, yp));\n"
            "   float s = cmm.x + com.x + cpm.x + cmo.x + cpo.x + cmp.x + cop.x + cpp.x;\n"
            "   float c = step(2.0, s) + step(s, 3.0) - 1.0;\n"
            "   gl_FragColor = vec4(c, c, c, 1.0);\n"
            "}\n");
        if (!m_shaderProgram.link())
        {
            return;
        }
        m_vertexLoc = m_shaderProgram.attributeLocation("vertex");
        m_texCoordLoc = m_shaderProgram.attributeLocation("vertTexCoord");
        m_texSizeLoc = m_shaderProgram.uniformLocation("texSize");
        m_imageLoc = m_shaderProgram.uniformLocation("imagePattern");
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
        if ((-1 == m_vertexLoc) || (-1 == m_texCoordLoc) || (-1 == m_texSizeLoc) || (-1 == m_imageLoc))
        {
            return;
        }
        const GLfloat vertexData[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            1.0f, 1.0f,
            -1.0f, 1.0f
        };
        const GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
        const GLfloat uvData[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };
        if (!m_shaderProgram.bind())
        {
            return;
        }
        m_texture.bind();
        m_shaderProgram.enableAttributeArray(m_vertexLoc);
        m_shaderProgram.enableAttributeArray(m_texCoordLoc);
        m_shaderProgram.setAttributeArray(m_vertexLoc, vertexData, 2, 0);
        m_shaderProgram.setAttributeArray(m_texCoordLoc, uvData, 2, 0);
        m_shaderProgram.setUniformValue(m_texSizeLoc, m_itemWidth, m_itemHeight);
        m_shaderProgram.setUniformValue(m_imageLoc, 0);
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
        m_itemWidth = static_cast<GLfloat>(myitem->getPatternSize());
        m_itemHeight = static_cast<GLfloat>(myitem->getPatternSize());
        m_texture.destroy();
        m_texture.create();
        m_texture.setMinificationFilter(QOpenGLTexture::Nearest);
        m_texture.setMagnificationFilter(QOpenGLTexture::Nearest);
        m_texture.setWrapMode(QOpenGLTexture::ClampToEdge);
        QSize sizeRet, sizeReq;
        m_texture.setData(imageProv->requestImage("image", &sizeRet, sizeReq), QOpenGLTexture::MipMapGeneration::DontGenerateMipMaps);
    }

private:
    QOpenGLTexture m_texture;
    QOpenGLShaderProgram m_shaderProgram;
    GLfloat m_itemWidth;
    GLfloat m_itemHeight;
    int m_imageLoc;
    int m_vertexLoc;
    int m_texCoordLoc;
    int m_texSizeLoc;
    bool m_isFirstInit;
};

MoveMaker::MoveMaker(QQuickItem *parent) : QQuickFramebufferObject(parent), m_patternSize(0)
{
}

QQuickFramebufferObject::Renderer* MoveMaker::createRenderer() const
{
    return new MoveMakerRenderer;
}

int MoveMaker::getPatternSize() const
{
    return m_patternSize;
}
