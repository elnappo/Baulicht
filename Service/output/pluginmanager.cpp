#include "pluginmanager.h"

class PluginManager::Private
{
public:
    Private()
    {
        // TODO: Initialize the plugins
    }

    // Properties
};

PluginManager::PluginManager(QObject *parent)
: QObject(parent)
, d(new Private)
{
}

PluginManager::~PluginManager()
{
    delete d;
}

Output *PluginManager::newInstance(const QString &name) const
{
    return NULL;
}
