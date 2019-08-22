#include "utils.h"
#include <QQmlContext>
#include <QQmlEngine>
#include "customimageprovider.h"

CustomImageProvider* CustomImageProviderFromQmlObject(const QObject* qmlObject)
{
    QQmlContext* context = QQmlEngine::contextForObject(qmlObject);
    if (context == nullptr)
    {
        return nullptr;
    }
    QQmlEngine* engine = context->engine();
    if (engine == nullptr)
    {
        return nullptr;
    }
    return dynamic_cast<CustomImageProvider*>(engine->imageProvider(QLatin1String("customprovider")));
}
