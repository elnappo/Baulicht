#include "../baulichtexecutor.h"
#include <QtTest/QtTest>

class TestExecutor : public QObject
{
    Q_OBJECT

private slots:
    void testMorseCodeConversion() {
        BaulichtExecutor e;
        QString code = e.convertToMorse("Morse Code");
        QCOMPARE(code, QString("===_===___===_===_===___=_===_=___=_=_=___=_______===_=_===_=___===_===_===___===_=_=___="));
    }
};

QTEST_MAIN(TestExecutor)

#include "tst_executor.moc"
