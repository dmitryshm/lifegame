#ifndef CUSTOMIMAGEPROVIDER_H
#define CUSTOMIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QPixmap>

class CustomImageProvider : public QQuickImageProvider
{
public:
    explicit CustomImageProvider();
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestSize) override;
};

#endif // CUSTOMIMAGEPROVIDER_H
