#ifndef CUSTOMIMAGEPROVIDER_H
#define CUSTOMIMAGEPROVIDER_H

#include <QQuickImageProvider>

class CustomImageProvider : public QQuickImageProvider
{
public:
    explicit CustomImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestSize) override;
    void setupPixel(int x, int y);
    void setSize(int size);

private:
    QImage m_image;
};

#endif // CUSTOMIMAGEPROVIDER_H
