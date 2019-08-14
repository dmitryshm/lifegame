#ifndef CUSTOMIMAGEEDITOR_H
#define CUSTOMIMAGEEDITOR_H

#include <QObject>
#include <QQuickImageProvider>
#include <QImage>

class CustomImageEditor : public QQuickImageProvider
{
public:
    CustomImageEditor();
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestSize) override;

    /*
    Q_OBJECT
    Q_PROPERTY(QImage image MEMBER m_image NOTIFY imageChanged)

public:
    explicit CustomImageEditor(QObject *parent = nullptr);
    Q_INVOKABLE void setupImagePixel(int x, int y);
    Q_INVOKABLE void initImage(int playgroundSize);

signals:
    void imageChanged();

public slots:
*/

private:
    QImage m_image;
};

#endif // CUSTOMIMAGEEDITOR_H
