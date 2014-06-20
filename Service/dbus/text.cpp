#include "text.h"

class Text::Private
{
public:
    Private()
    : repeat(0)
    {
    }

    // Properties
    QString text;
    int repeat;
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
