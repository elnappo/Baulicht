#ifndef BAULICHT_H
#define BAULICHT_H

#include <QObject>
#include <QStringList>

class Baulicht : public QObject
{
    Q_OBJECT
    Q_ENUMS(Mode)
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht")

public:
    explicit Baulicht(QObject *parent = 0);
    ~Baulicht();

    enum Mode
    {
        Text  = 0,
        Blink = 1
    };

public slots:
    void setMode(int mode);
    int mode() const;

    void setPaused(bool paused);
    bool paused() const;

    QString addText(const QString& text, int interval, int repeat);
    void removeText(const QString& path);
    QStringList texts() const;

    void clear();

signals:
    void modeChanged(int mode);
    void pausedChanged(bool paused);
    void textAdded(const QString& path);

protected:
    class Private;
    Private* d;
};

#endif // BAULICHT_H
