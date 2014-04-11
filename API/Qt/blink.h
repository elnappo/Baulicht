#ifndef BAULICHT_H
#define BAULICHT_H

#include <QObject>
#include <QList>

class Blink : public QObject
{
    Q_OBJECT
    Q_ENUMS(Mode)
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht.Blink")

public:
    explicit Blink(QObject *parent = 0);


public slots:
    void setIntervals(const QList<int>& intervals);
    const QList<int> intervals() const;

signals:
};

#endif // BAULICHT_H
