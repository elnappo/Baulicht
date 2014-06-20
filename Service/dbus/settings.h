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

signals:
    void ditChanged(int dit);
    void textSpacingChanged(int textSpacing);

protected:
    class Private;
    Private *d;
};

#endif // SETTINGS_H
