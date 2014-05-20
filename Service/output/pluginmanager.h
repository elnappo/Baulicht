#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "output.h"

#include <QObject>

class PluginManager : public QObject
{
    Q_OBJECT

public:
    explicit PluginManager(QObject *parent = 0);
    ~PluginManager();

    Output* newInstance(const QString& name) const;

protected:
    class Private;
    Private* d;
};

#endif // PLUGINMANAGER_H
