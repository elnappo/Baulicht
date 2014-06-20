#ifndef BAULICHT_H
#define BAULICHT_H

#include <QObject>
#include <QStringList>

class Settings;

/**
 * @brief The Baulicht class
 */
class Baulicht : public QObject
{
    Q_OBJECT
    Q_ENUMS(Mode)
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht")
    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY pausedChanged)
    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)

public:
    explicit Baulicht(QObject *parent = 0);
    ~Baulicht();

    enum Mode
    {
        TextMode  = 0,
        BlinkMode = 1
    };

    void setSettings(Settings *settings);
    Settings* settings() const;

public slots:
    void setMode(int mode);
    int mode() const;

    void setPaused(bool paused);
    bool paused() const;

    QString addText(const QString& text, int repeat);
    void removeText(const QString& path);
    QStringList texts() const;

    void clear();

    void start();
    void stop();

signals:
    void modeChanged(int mode);
    void pausedChanged(bool paused);
    void textAdded(const QString& path);

protected:
    class Private;
    Private* d;
};

#endif // BAULICHT_H
