#ifndef BAULICHT_H
#define BAULICHT_H

#include <QObject>
#include <QList>

class Text : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht.Text")

public:
    explicit Text(QObject *parent = 0);

public slots:
    void setText(const QString& text);
    QString text() const;

    void setInterval(int interval);
    int interval() const;

    void setRepeat(int repeat);
    int repeat() const;

signals:
};

#endif // BAULICHT_H
