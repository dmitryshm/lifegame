#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include <QQuickFramebufferObject>
#include "customimageeditor.h"

class MoveMaker : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(int patternSize MEMBER m_patternSize READ getPatternSize)
public:
    MoveMaker(QQuickItem *parent = nullptr);
    QQuickFramebufferObject::Renderer* createRenderer() const;
    int getPatternSize() const;
private:
    int m_patternSize;
};

#endif // MOVEMAKER_H
