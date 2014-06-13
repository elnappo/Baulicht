#include "dbus/baulicht.h"
#include "baulichtexecutor.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    const QString& serviceName = "de.naptower.Baulicht";

    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService(serviceName)) {
        qDebug() << "Failed to register service" << serviceName << ":" << connection.lastError().message();
        return 1;
    }

    Baulicht service;
    if (!connection.registerObject("/", &service, QDBusConnection::ExportAllSlots)) {
        qDebug() << "Failed to register object at /:" << connection.lastError().message();
        return 1;
    }

    BaulichtExecutor executor;
    QString code = executor.convertToMorse("Morse Code");

    return app.exec();
}

