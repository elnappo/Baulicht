#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

/**
 * @brief The Settings class
 */
class Settings : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "de.naptower.Baulicht.Settings")
    Q_PROPERTY(int dit READ dit WRITE setDit NOTIFY ditChanged)
    Q_PROPERTY(int textSpacing READ textSpacing WRITE setTextSpacing NOTIFY textSpacingChanged)
    Q_PROPERTY(int pin READ pin WRITE setPin NOTIFY pinChanged)

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

public slots:
    /**
     * @brief setDit sets the time interval of a dit in milliseconds
     * @param milliseconds
     */
    void setDit(int milliseconds);
    int dit() const;

    /**
     * @brief setTextSpacing sets the time spacing between two texsts in milliseconds
     * @param milliseconds
     */
    void setTextSpacing(int milliseconds);
    int textSpacing() const;

    /**
     * @brief setPin sets the pin number of the GPIO pin used for morse output
     * @param pin
     */
    void setPin(int pin);
    int pin() const;

signals:
    void ditChanged(int dit);
    void textSpacingChanged(int textSpacing);
    void pinChanged(int pin);

protected:
    class Private;
    Private *d;
};

#endif // SETTINGS_H
