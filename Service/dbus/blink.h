#ifndef BLINK_H
#define BLINK_H

#include <QObject>
#include <QList>

class Blink : public QObject
{
    Q_OBJECT
    Q_ENUMS(Mode)
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht.Blink")

public:
    explicit Blink(QObject *parent = 0);
    ~Blink();

public slots:
    void setIntervals(const QList<int>& intervals);
    const QList<int> intervals() const;

signals:
    void intervalsChanged(const QList<int>& intervals);

protected:
    class Private;
    Private *d;
};

#endif // BLINK_H
