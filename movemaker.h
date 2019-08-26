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
    virtual QQuickFramebufferObject::Renderer* createRenderer() const override;
    int getPatternSize() const;
    Q_INVOKABLE void move();
    bool hasMove() const;
    void moveCompleted();

private:
    int m_patternSize;
    bool m_dirtyMove;
};

#endif // MOVEMAKER_H
