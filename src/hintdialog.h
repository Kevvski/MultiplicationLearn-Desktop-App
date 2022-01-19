#ifndef HINTDIALOG_H
#define HINTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>

class HintDialog : public QDialog
{
    Q_OBJECT

public:
    HintDialog(QWidget* parent = nullptr);
    ~HintDialog();

    void createWidgets(int firstNumber, int secondNumber);
    void clear();

private:
    QVector<QLabel*> solutionLabels;
    QPushButton* closeButton;

//private:
    //void createWidgets(int firstNumber, int secondNumber);
};

#endif // HINTDIALOG_H
