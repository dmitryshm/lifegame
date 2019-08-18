#include "customimageeditor.h"
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
    prov->setupPixel(x, y);
    emit imageChanged();
}

void CustomImageEditor::setPatternSize(int val)
{
    CustomImageProvider* prov = customImageProvider();
    if (prov == nullptr)
    {
        return;
    }
    prov->setSize(val);
    const bool shouldFire = (m_patternSize != val);
    m_patternSize = val;
    if (shouldFire)
    {
        emit imageChanged();
    }
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
