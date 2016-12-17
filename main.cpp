#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "jsonlistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<JsonListModel>("JsonListModel", 1, 0, "JsonListModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
