#ifndef BAULICHTEXECUTOR_H
#define BAULICHTEXECUTOR_H

#include <QObject>
#include <QHash>

class BaulichtExecutor : public QObject
{
    Q_OBJECT

public:
    explicit BaulichtExecutor(QObject *parent = 0);
    ~BaulichtExecutor();

    QString convertToMorse(const QString& text) const;

protected:
    void initAlphabet();
    void initIntervals();

protected:
    QHash<QString, QString> m_morseAlphabet;
    QHash<QChar, int> m_intervals;
    int m_letterSpacing;
};

#endif // BAULICHTEXECUTOR_H
