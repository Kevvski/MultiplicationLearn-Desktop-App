#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    SettingsWindow(QWidget* parent = nullptr);
    ~SettingsWindow();

    int getDelay() const;
    const QString& getMessage() const;
    bool getRepeatable() const;

private:
    QLabel* delayLabel;
    QLabel* messageLabel;
    QTextEdit* messageField;
    QCheckBox* repeatCheckBox;
    QSpinBox* delaySpinBox;
    QPushButton* saveButton;

    int delay;
    QString message;
    bool repeat;

private:
    void createWidgets();
    void createConnections();

private slots:
    void saveSettings();
};

#endif // SETTINGSWINDOW_H
