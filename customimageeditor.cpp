#include "customimageeditor.h"
#include <QtDebug>
#include <QRgb>
#include <QQmlEngine>
#include <QQmlContext>
#include "customimageprovider.h"

CustomImageEditor::CustomImageEditor(QObject *parent) : QObject(parent)
{
}

Q_INVOKABLE void CustomImageEditor::setupImagePixel(int x, int y)
{
    CustomImageProvider* prov = customImageProvider();
    if (prov == nullptr)
    {
        return;
    }
    qDebug() << "x = " << x << ", y = " << y;
    prov->setupPixel(x, y);
    emit imageChanged();
}

void CustomImageEditor::setPatternSize(int val)
{
    m_patternSize = val;
    CustomImageProvider* prov = customImageProvider();
    if (prov == nullptr)
    {
        return;
    }
    prov->setSize(val);
}

int CustomImageEditor::getPatternSize() const
{
    return m_patternSize;
}

CustomImageProvider* CustomImageEditor::customImageProvider() const
{
    QQmlContext* context = QQmlEngine::contextForObject(this);
    if (context == nullptr)
    {
        return nullptr;
    }
    QQmlEngine* engine = context->engine();
    if (engine == nullptr)
    {
        return nullptr;
    }
    return dynamic_cast<CustomImageProvider*>(engine->imageProvider(QLatin1String("customprovider")));
}
