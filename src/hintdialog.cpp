#include "hintdialog.h"

HintDialog::HintDialog(QWidget* parent) : QDialog(parent)
{
    setWindowIcon(QIcon(":/images/appico.png"));
    setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    setWindowTitle("Rozwiązanie");
    createWidgets(1, 1);
}


HintDialog::~HintDialog()
{
}


void HintDialog::createWidgets(int firstNumber, int secondNumber)
{
    int sum{ firstNumber };
    for(int i = 1; i < secondNumber; i++)
    {
        QLabel* label = new QLabel;
        QFont font = label->font();
        font.setBold(true);
        font.setPointSize(12);
        label->setFont(font);

        QString text { QString::number(i) + ".  " + QString::number(sum) + " + " + QString::number(firstNumber) };
        sum += firstNumber;
        text += (" = " + QString::number(sum));

        label->setText(text);
        solutionLabels.push_back(label);
    }

    closeButton = new QPushButton("Zamknij");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

    QVBoxLayout* layout = new QVBoxLayout;
    for(int i = 0; i < solutionLabels.size(); i++)
    {
        layout->addWidget(solutionLabels.at(i), 0, Qt::AlignCenter);
    }
    layout->addWidget(closeButton, 0, Qt::AlignCenter);

    setMinimumSize(QSize(50, 50));
    setMaximumSize(QSize(200, 300));

    qDeleteAll(children());
    setLayout(layout);
}


void HintDialog::clear()
{
    solutionLabels.clear();
}
