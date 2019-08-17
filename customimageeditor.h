#ifndef CUSTOMIMAGEEDITOR_H
#define CUSTOMIMAGEEDITOR_H

#include <QObject>
#include <QImage>
#include "customimageprovider.h"

class CustomImageEditor : public QObject
{
public:
    Q_OBJECT
    Q_PROPERTY(QImage image MEMBER m_image NOTIFY imageChanged)

public:
    explicit CustomImageEditor(QObject *parent = nullptr);
    Q_INVOKABLE void setupImagePixel(int x, int y);
    Q_INVOKABLE void initImage(int playgroundSize);

signals:
    void imageChanged();

public slots:

private:
    QImage m_image;
};

#endif // CUSTOMIMAGEEDITOR_H
