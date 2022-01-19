#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), calculateSuccess{}, firstNumber{}, secondNumber{}, sum{}, randomClickedCount{}
{
    createWidgets();
    createConnections();
}


MainWindow::~MainWindow()
{
}


void MainWindow::createWidgets()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/images/appico.png"));

    QMenu* menu = new QMenu(this);
    QAction* showAction = new QAction("Pokaż", this);
    QAction* settingsAction = new QAction("Ustawienia", this);
    QAction* closeAction = new QAction("Zamknij", this);

    connect(showAction, &QAction::triggered, this, &QMainWindow::show);
    connect(closeAction, &QAction::triggered, this, &QMainWindow::close);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::showSettings);
    menu->addAction(showAction);
    menu->addAction(settingsAction);
    menu->addAction(closeAction);
    trayIcon->setContextMenu(menu);

    trainingInfoLabel = new QLabel;
    operationLabel = new QLabel;
    successLabel = new QLabel;

    randomize();

    trainingInfoLabel->setText("Oblicz podane wyrażenie:");
    operationLabel->setText(QString::number(firstNumber) + " x " + QString::number(secondNumber) + " = ");

    QFont font = operationLabel->font();
    font.setBold(true);
    font.setPointSize(15);
    operationLabel->setFont(font);

    timer = new QTimer(this);
    showTimer = new QTimer(this);

    checkButton = new QPushButton("Sprawdź");
    randomButton = new QPushButton("Losuj");
    hintButton = new QPushButton;
    hintButton->setIcon(QIcon(":/images/lightico.png"));
    hintButton->setIconSize(QSize(30, 30));
    hintButton->setStyleSheet("QPushButton{ border: 0px; }  QPushButton:hover:!pressed{ background: lightgrey; border-radius: 5px; }");
    hintButton->setToolTip("Rozwiązanie");

    lineEdit = new QLineEdit;
    lineEdit->setFixedSize(QSize(100, 20));

    QHBoxLayout* topLayout = new QHBoxLayout;
    QHBoxLayout* middleLayout = new QHBoxLayout;
    QHBoxLayout* bottomLayout = new QHBoxLayout;
    QVBoxLayout* globalLayout = new QVBoxLayout;

    topLayout->addWidget(trainingInfoLabel, 0, Qt::AlignLeft);
    topLayout->addWidget(hintButton, 0, Qt::AlignRight);

    middleLayout->addWidget(operationLabel, 0, Qt::AlignCenter);
    middleLayout->addWidget(lineEdit, 0, Qt::AlignCenter);

    bottomLayout->addWidget(successLabel, 0, Qt::AlignLeft);
    bottomLayout->addWidget(checkButton, 1, Qt::AlignRight);
    bottomLayout->addWidget(randomButton, 0, Qt::AlignRight);

    globalLayout->addLayout(topLayout);
    globalLayout->addLayout(middleLayout);
    globalLayout->addLayout(bottomLayout);

    QWidget* central = new QWidget;
    central->setLayout(globalLayout);

    setMaximumSize(QSize(400, 100));
    setMinimumSize(QSize(400, 100));
    setCentralWidget(central);
    setWindowTitle("Trenuj Mnożenie!");
    setWindowIcon(QIcon(":/images/appico.png"));
    resize(400, 100);

    trayIcon->show();
}


void MainWindow::randomize()
{
    if(randomClickedCount < 4)
    {
        randomClickedCount++;
        firstNumber = QRandomGenerator::global()->bounded(0, 10);
        secondNumber = QRandomGenerator::global()->bounded(0, 10);
        sum = firstNumber * secondNumber;
        operationLabel->setText(QString::number(firstNumber) + " x " + QString::number(secondNumber) + " = ");

        hintWindow.clear();
        hintWindow.createWidgets(firstNumber, secondNumber);
    }
}


void MainWindow::createConnections()
{
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &MainWindow::successCalculate);
    connect(showTimer, &QTimer::timeout, this, &QMainWindow::show);
    connect(checkButton, &QPushButton::clicked, this, &MainWindow::checkAnswer);
    connect(randomButton, &QPushButton::clicked, this, &MainWindow::randomize);
    connect(hintButton, &QPushButton::clicked, this, &MainWindow::showSolution);
}


void MainWindow::checkAnswer()
{
    bool isLetter{};
    for(auto& character : lineEdit->text())
    {
        if(character.isLetter()) isLetter = true;
    }

    if(!lineEdit->text().isEmpty() && !isLetter)
    {
        int answerValue = lineEdit->text().toInt();
        QFont font = successLabel->font();
        font.setBold(true);
        font.setPointSize(12);
        successLabel->setFont(font);

        timer->start(2000);
        calculateSuccess = answerValue == sum;

        if(calculateSuccess)
        {
            randomClickedCount = 0;
            successLabel->setText("Sukces!");
            successLabel->setStyleSheet("QLabel { color: green; } ");
            if(settingsWindow.getRepeatable()) showTimer->start(settingsWindow.getDelay());
        }
        else
        {
            successLabel->setText("Ups! Źle...");
            successLabel->setStyleSheet("QLabel { color: red; } ");
        }

        lineEdit->clear();
    }
}


void MainWindow::successCalculate()
{
    successLabel->clear();
    randomize();
    if(settingsWindow.getRepeatable() && calculateSuccess)
    {
        hide();
        trayIcon->showMessage("Gratulacje!", settingsWindow.getMessage(), QSystemTrayIcon::Information, 2000);
    }
}


void MainWindow::showSettings()
{
    settingsWindow.show();
}


void MainWindow::showSolution()
{
    if(firstNumber != 0 && firstNumber != 1 && secondNumber != 0 && secondNumber != 1)
        hintWindow.show();
}
