#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog (parent)
{
    createWidgets();
    repeat = false;
    delay = delaySpinBox->value() * 60000;
    message = "Świetnie! Kolejne liczenie za nami. Widzimy się za " + QString::number(delay / 60000) + " minut.";
}


SettingsWindow::~SettingsWindow()
{
}


void SettingsWindow::createWidgets()
{
    delayLabel = new QLabel("Czas powtarzania(minuty):");
    messageLabel = new QLabel("Wiadomość:");
    messageField = new QTextEdit;
    repeatCheckBox = new QCheckBox;
    delaySpinBox = new QSpinBox;
    saveButton = new QPushButton("Zapisz");

    messageField->setFixedSize(QSize(200, 100));
    delaySpinBox->setValue(5);
    delaySpinBox->setMinimum(1);
    delaySpinBox->setMaximum(20);
    repeatCheckBox->setText("Powtarzaj o podany czas");

    connect(saveButton, &QPushButton::clicked, this, &SettingsWindow::saveSettings);

    QHBoxLayout* topLayout = new QHBoxLayout;
    QHBoxLayout* middleLayout = new QHBoxLayout;
    QHBoxLayout* bottomLayout = new QHBoxLayout;
    QVBoxLayout* globalLayout = new QVBoxLayout;

    topLayout->addWidget(delayLabel);
    topLayout->addWidget(delaySpinBox);

    middleLayout->addWidget(messageLabel);
    middleLayout->addWidget(messageField);

    bottomLayout->addWidget(repeatCheckBox);
    bottomLayout->addWidget(saveButton);

    globalLayout->addLayout(topLayout);
    globalLayout->addLayout(middleLayout);
    globalLayout->addLayout(bottomLayout);

    setLayout(globalLayout);
    setWindowIcon(QIcon(":/images/appico.png"));
    setWindowTitle("Ustawienia");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    setModal(true);
}


int SettingsWindow::getDelay() const
{
    return delay;
}


const QString& SettingsWindow::getMessage() const
{
    return message;
}


bool SettingsWindow::getRepeatable() const
{
    return repeat;
}


void SettingsWindow::saveSettings()
{
    hide();
    delay = delaySpinBox->value() * 60000;
    if(!messageField->toPlainText().isEmpty()) message = messageField->toPlainText();
    else message = "Świetnie! Kolejne liczenie za nami. Widzimy się za " + QString::number(delay / 60000) + " minut.";

    if(repeatCheckBox->isChecked()) repeat = true;
    else repeat = false;

    QMessageBox::information(this, "Zapisywanie...", "Zapisano pomyślnie ;)", QMessageBox::Ok);
}
