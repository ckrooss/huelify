#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <HueAPI.hpp>

static QObject *register_hueAPI_singleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    HueAPI *hueapi = new HueAPI();
    return hueapi;
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<HueAPI>("com.hue.HueAPI", 1, 0, "HueAPI", register_hueAPI_singleton);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
