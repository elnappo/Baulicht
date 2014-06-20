#include "dbus/baulicht.h"
#include "dbus/settings.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    const QString& serviceName = "de.naptower.Baulicht";

    // Try to register our service on the session bus
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService(serviceName)) {
        qDebug() << "Failed to register service" << serviceName << ":" << connection.lastError().message();
        return 1;
    }

    // Initialize the settings
    Settings settings;

    // Create the main service object
    Baulicht service;
    service.setSettings(&settings);

    // Register the settings object
    if (!connection.registerObject("/settings", &settings, QDBusConnection::ExportAllSlots)) {
        qDebug() << "Failed to register settings object at /settings:" << connection.lastError().message();
        return 1;
    }

    // Register the root object
    if (!connection.registerObject("/", &service, QDBusConnection::ExportAllSlots)) {
        qDebug() << "Failed to register object at /:" << connection.lastError().message();
        return 1;
    }

    return app.exec();
}

