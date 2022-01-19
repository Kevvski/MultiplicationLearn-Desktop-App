#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <random>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QStyle>
#include "settingswindow.h"
#include "hintdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSystemTrayIcon* trayIcon;
    QLabel* trainingInfoLabel;
    QLabel* operationLabel;
    QLabel* successLabel;
    QPushButton* checkButton;
    QPushButton* randomButton;
    QPushButton* hintButton;
    QLineEdit* lineEdit;
    QTimer* timer;
    QTimer* showTimer;
    SettingsWindow settingsWindow;
    HintDialog hintWindow;

    bool calculateSuccess;
    int firstNumber;
    int secondNumber;
    int sum;
    int randomClickedCount;

private:
    void createWidgets();
    void randomize();
    void createConnections();
    void checkAnswer();

private slots:
    void successCalculate();
    void showSettings();
    void showSolution();
};

#endif // MAINWINDOW_H
