#ifndef CUSTOMIMAGEEDITOR_H
#define CUSTOMIMAGEEDITOR_H

#include <QObject>
#include <QImage>
#include "customimageprovider.h"

class CustomImageEditor : public QObject
{
public:
    Q_OBJECT
    Q_PROPERTY(int patternSize READ getPatternSize WRITE setPatternSize)

public:
    explicit CustomImageEditor(QObject *parent = nullptr);
    Q_INVOKABLE void setupImagePixel(int x, int y);
    void setPatternSize(int val);
    int getPatternSize() const;

signals:
    void patternSizeChanged();
    void imageChanged();

public slots:

private:
    int m_patternSize;
    CustomImageProvider* customImageProvider() const;
};

#endif // CUSTOMIMAGEEDITOR_H
