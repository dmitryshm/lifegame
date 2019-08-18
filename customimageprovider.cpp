#include "customimageprovider.h"

CustomImageProvider::CustomImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
}

QImage CustomImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestSize)
{
    Q_UNUSED(id)
    Q_UNUSED(requestSize)
    *size = QSize(10, 10);
    QImage img(*size, QImage::Format_RGB32);
    img.fill(qRgb(0, 0, 0));
    return img;
}

void CustomImageProvider::setupPixel(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
}

void CustomImageProvider::setSize(int size)
{
    Q_UNUSED(size);
}
