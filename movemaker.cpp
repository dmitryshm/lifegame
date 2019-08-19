#include "movemaker.h"
#include <QOpenGLFramebufferObject>

class MoveMakerRenderer : public QQuickFramebufferObject::Renderer
{
     friend class MoveMaker;

protected:
    MoveMakerRenderer(const MoveMaker* mm) : m_mm(mm)
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
        Q_UNUSED(m_mm);
        // Called with the FBO bound and the viewport set.
        // Issue OpenGL commands.
    }
private:
    const MoveMaker* m_mm;
};

MoveMaker::MoveMaker(QQuickItem *parent) : QQuickFramebufferObject(parent)
{
}

QQuickFramebufferObject::Renderer* MoveMaker::createRenderer() const
{
    return new MoveMakerRenderer(this);
}
