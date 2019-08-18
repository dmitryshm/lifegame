#include "customimageprovider.h"

CustomImageProvider::CustomImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage CustomImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestSize)
{
    Q_UNUSED(id)
    Q_UNUSED(requestSize)
    if (size != nullptr)
    {
        *size = m_image.size();
    }
    return m_image;
}

void CustomImageProvider::setupPixel(int x, int y)
{
    m_image.setPixelColor(x, y, qRgb(255,255,255));
}

void CustomImageProvider::setSize(int size)
{
    if (size <= 0)
    {
        return;
    }
    m_image = QImage(size, size, QImage::Format_RGB32);
    m_image.fill(qRgb(0, 0, 0));
}
