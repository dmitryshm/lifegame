#include "customimageeditor.h"
#include <QRgb>
#include <QQmlEngine>
#include <QQmlContext>
#include "customimageprovider.h"
#include "utils.h"

CustomImageEditor::CustomImageEditor(QObject *parent) : QObject(parent)
{
}

Q_INVOKABLE void CustomImageEditor::setupImagePixel(int x, int y)
{
    CustomImageProvider* prov = CustomImageProviderFromQmlObject(this);
    if (prov == nullptr)
    {
        return;
    }
    prov->setupPixel(x, y);
    emit imageChanged();
}

void CustomImageEditor::setPatternSize(int val)
{
    CustomImageProvider* prov = CustomImageProviderFromQmlObject(this);
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
