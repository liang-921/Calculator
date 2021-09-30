#ifndef CALCULATOR_H
#define CALCULATOR_H


#include <QDialog>
#include <QString>
#include "ui_calculator.h"

class Calculator :public QDialog,public Ui::Calculator
{
    Q_OBJECT

public:
    Calculator(QWidget *parent=nullptr);
    double AnalyseExpr(QString &calculate);
    double AnalyseTerm(QString &calculate);
    double AnalyseFactor(QString &calculate);

private slots:
    void buttonClicked();
private:
    //Ui::Calculator *ui;
    QString m_calculate="";
    double m_result;

    bool m_FirstInput = true;
    bool m_Error = false;
    bool m_End = false;//结束一次计算
};
#endif // CALCULATOR_H
