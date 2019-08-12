#include "customimageeditor.h"
#include <QtDebug>
#include <QRgb>

CustomImageEditor::CustomImageEditor(QObject *parent) : QObject(parent)
{

}

Q_INVOKABLE void CustomImageEditor::setupImagePixel(int x, int y)
{
    qDebug() << "x = " << x << ", y = " << y;
    m_image.setPixel(x, y, qRgb(255,255,255));
    emit imageChanged();
}

Q_INVOKABLE void CustomImageEditor::initImage(int playgroundSize)
{
    if (playgroundSize <= 0)
    {
        return;
    }
    QImage image(playgroundSize, playgroundSize, QImage::Format_RGB32);
    image.fill(qRgb(0, 0, 0));
    m_image.swap(image);
}
