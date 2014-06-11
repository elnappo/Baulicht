#include "baulichtexecutor.h"

#include <QTextStream>

BaulichtExecutor::BaulichtExecutor(QObject *parent)
: QObject(parent)
{
    initIntervals();
    initAlphabet();
}

BaulichtExecutor::~BaulichtExecutor()
{
}

QString BaulichtExecutor::convertToMorse(const QString &text) const
{
    QString completeCode;
    QTextStream stream;
    stream.setString(&completeCode);

    for(int i=0; i < text.length(); ++i) {
        QChar c = text.at(i).toUpper();

        QString morseCode = m_morseAlphabet.value(c);
        if (morseCode.isEmpty())
            continue;

        bool lastChar = false;

        for(int x=0; x < morseCode.length(); ++x) {
            QChar code = morseCode.at(x);

            switch(code.toLatin1()) {
            case '.':
                stream << '=';
                break;

            case '-':
                stream << "===";
                break;

            case ' ':
                lastChar = true;
                stream << "_______";
                break;

            default:
                break;
            }

            if (lastChar)
                break;

            if (x == morseCode.length()-1)
                ;
            else
                stream << "_";
        }

        if (lastChar)
            lastChar = false;
        else {
            if (text.length() != i+1) {
                if (text.at(i+1) != ' ')
                    stream << "___";
            }
        }
    }

    return completeCode;
}

void BaulichtExecutor::initAlphabet()
{
    if (!m_morseAlphabet.isEmpty())
        return;

    m_morseAlphabet.insert(" ", " ");
    m_morseAlphabet.insert("\"", ".----.");
    m_morseAlphabet.insert("(", "-.--.-");
    m_morseAlphabet.insert(")", "-.--.-");
    m_morseAlphabet.insert(");", "--..--");
    m_morseAlphabet.insert("-", "-....-");
    m_morseAlphabet.insert(".", ".-.-.-");
    m_morseAlphabet.insert("/", "-..-.");
    m_morseAlphabet.insert("0", "-----");
    m_morseAlphabet.insert("1", ".----");
    m_morseAlphabet.insert("2", "..---");
    m_morseAlphabet.insert("3", "...--");
    m_morseAlphabet.insert("4", "....-");
    m_morseAlphabet.insert("5", ".....");
    m_morseAlphabet.insert("6", "-....");
    m_morseAlphabet.insert("7", "--...");
    m_morseAlphabet.insert("8", "---..");
    m_morseAlphabet.insert("9", "----.");
    m_morseAlphabet.insert(",", "---...");
    m_morseAlphabet.insert(";", "-.-.-.");
    m_morseAlphabet.insert("?", "..--..");
    m_morseAlphabet.insert("A", ".-");
    m_morseAlphabet.insert("B", "-...");
    m_morseAlphabet.insert("C", "-.-.");
    m_morseAlphabet.insert("D", "-..");
    m_morseAlphabet.insert("E", ".");
    m_morseAlphabet.insert("F", "..-.");
    m_morseAlphabet.insert("G", "--.");
    m_morseAlphabet.insert("H", "....");
    m_morseAlphabet.insert("I", "..");
    m_morseAlphabet.insert("J", ".---");
    m_morseAlphabet.insert("K", "-.-");
    m_morseAlphabet.insert("L", ".-..");
    m_morseAlphabet.insert("M", "--");
    m_morseAlphabet.insert("N", "-.");
    m_morseAlphabet.insert("O", "---");
    m_morseAlphabet.insert("P", ".--.");
    m_morseAlphabet.insert("Q", "--.-");
    m_morseAlphabet.insert("R", ".-.");
    m_morseAlphabet.insert("S", "...");
    m_morseAlphabet.insert("T", "-");
    m_morseAlphabet.insert("U", "..-");
    m_morseAlphabet.insert("V", "...-");
    m_morseAlphabet.insert("W", ".--");
    m_morseAlphabet.insert("X", "-..-");
    m_morseAlphabet.insert("Y", "-.--");
    m_morseAlphabet.insert("Z", "--..");
    m_morseAlphabet.insert("_", "..--.-");
}

void BaulichtExecutor::initIntervals()
{
    int dit = 500;
    m_intervals.insert('.', dit);
    m_intervals.insert('-', dit*3);
    m_intervals.insert(' ', dit*7);

    m_letterSpacing = dit*3;
}
