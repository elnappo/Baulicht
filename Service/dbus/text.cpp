#include "text.h"

#include <QDateTime>

class Text::Private
{
public:
    Private()
    : repeat(0)
    , creationDate(QDateTime::currentDateTime())
    {
    }

    // Properties
    QString text;
    int repeat;

    QDateTime creationDate;
};

Text::Text(QObject *parent)
: QObject(parent)
, d(new Private)
{
}

Text::~Text()
{
    delete d;
}

QString Text::creationTimestamp() const
{
    return d->creationDate.toString();
}

void Text::setText(const QString &text)
{
    if (d->text != text) {
        d->text = text;
        emit textChanged(text);
    }
}

QString Text::text() const
{
    return d->text;
}

void Text::setRepeat(int repeat)
{
    if (d->repeat != repeat) {
        d->repeat = repeat;
        emit repeatChanged(repeat);
    }
}

int Text::repeat() const
{
    return d->repeat;
}
