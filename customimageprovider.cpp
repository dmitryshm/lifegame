#include "customimageprovider.h"

CustomImageProvider::CustomImageProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

 QPixmap CustomImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestSize)
 {
 }
