#ifndef MOVEMAKER_H
#define MOVEMAKER_H

#include <QQuickFramebufferObject>
#include "customimageeditor.h"

class MoveMaker : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    MoveMaker(QQuickItem *parent = nullptr);
    QQuickFramebufferObject::Renderer* createRenderer() const;
signals:

public slots:

};

#endif // MOVEMAKER_H
