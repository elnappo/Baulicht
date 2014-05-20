#include "blink.h"

class Blink::Private
{
public:
    // Properties
    QList<int> intervals;
};

Blink::Blink(QObject *parent)
: QObject(parent)
, d(new Private)
{
}

Blink::~Blink()
{
    delete d;
}

void Blink::setIntervals(const QList<int> &intervals)
{
    if (d->intervals != intervals) {
        d->intervals = intervals;
        emit intervalsChanged(intervals);
    }
}

const QList<int> Blink::intervals() const
{
    return d->intervals;
}
