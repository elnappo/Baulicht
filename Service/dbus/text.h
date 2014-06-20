#ifndef TEXT_H
#define TEXT_H

#include <QObject>
#include <QList>

/**
 * @brief The Text class
 */
class Text : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht.Text")

public:
    explicit Text(QObject *parent = 0);
    ~Text();

public slots:
    void setText(const QString& text);
    QString text() const;

    void setRepeat(int repeat);
    int repeat() const;

signals:
    void textChanged(const QString& text);
    void repeatChanged(int repeat);

protected:
    class Private;
    Private *d;
};

#endif // TEXT_H
