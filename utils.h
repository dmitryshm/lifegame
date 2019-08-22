#ifndef UTILS_HPP
#define UTILS_HPP
#include <QtGlobal>

class CustomImageProvider;
QT_FORWARD_DECLARE_CLASS(QObject)

CustomImageProvider* CustomImageProviderFromQmlObject(const QObject* qmlObject);

#endif // UTILS_HPP
