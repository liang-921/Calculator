#include "calculator.h"
#include "scantoken.h"

#include <iostream>
#include <QDateTime>
#include <QRegExp>

Calculator::Calculator(QWidget *parent)
    : QDialog(parent)
    ,m_result{0}
{
    setupUi(this);

    connect(Button_0,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_1,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_2,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_3,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_4,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_5,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_6,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_7,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_8,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_9,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_Plus,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_Minus,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_Mul,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_Div,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_C,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_CE,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_equal,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_Rp,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_time,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_Lp,SIGNAL(clicked()),this,SLOT(buttonClicked()));
    connect(Button_point,SIGNAL(clicked()),this,SLOT(buttonClicked()));
}

double Calculator::AnalyseExpr(QString &calculate)    //expr=
{
    double result;
    result=AnalyseTerm(calculate);

    bool if_Stop=true;
    while(if_Stop){
        Token ex=Get_Token(calculate);

        switch(ex.type){
            case '+':
            calculate=calculate.right(calculate.size()-1);
            result +=AnalyseTerm(calculate);
            break;
            case '-':
            calculate=calculate.right(calculate.size()-1);
            result -=AnalyseTerm(calculate);
            break;
            default:
                 if_Stop=false;
            break;
        }
    }
    return result;
}

double Calculator::AnalyseTerm(QString &calculate)
{
    double result;
    result=AnalyseFactor(calculate);
    double mid;
    bool if_Stop=true;
    while(if_Stop){
        Token ex=Get_Token(calculate);

        switch(ex.type){
            case '*':
            calculate=calculate.right(calculate.size()-1);
            result *=AnalyseFactor(calculate);
            break;
            case '/':
            calculate=calculate.right(calculate.size()-1);
            mid =AnalyseFactor(calculate);
            if(mid == 0.0){
                throw std::runtime_error("error: divided by zero!\n");
            }
            result /=mid;
            break;
            default:
                 if_Stop=false;
            break;
        }
    }
    return result;
}

double Calculator::AnalyseFactor(QString &calculate)
{
    double result=0;
    Token token=Get_Token(calculate);

    switch (token.type) {
        case numbers:
            result=token.num;
        break;
        case lbar:
            calculate=calculate.right(calculate.size()-1);
            result=AnalyseExpr(calculate);
            token=Get_Token(calculate);
            calculate=calculate.right(calculate.size()-1);
            if(token.type!=rbar){
                  throw std::runtime_error("bad syntax: need a )\n");
            }
        break;
        default:
        //???????????? ??????????????????
        throw std::runtime_error("bad syntax: need a number or a )\n");
        break;
    }
    return result;
}


void Calculator::buttonClicked()//?????????????????????
{
    QString input=lineEdit->text();
    QPushButton *tb = qobject_cast<QPushButton *>(sender());//??????????????????????????????pushbutton??????
    QString text = tb->text();//text:??????????????????????????????????????????
   if(text == "CE"){
         text = input.left(input.length()-1); //???????????????
         lineEdit->setText(text);
         if(input.length()==1){
               lineEdit->setText("0");
               m_FirstInput = true;
         }
    }else if(text == "C"){//????????????
         m_FirstInput = true;
         input="0";
         lineEdit->setText(input);
    }else if(text == QString("Time")){
         text=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"); //???????????????????????????
         lineEdit->setText(text);
    }else if(text == "="){
        try {
               m_result=AnalyseExpr(input);
               lineEdit->setText(QString::number(m_result,'.',3));
               m_End = true;
        }catch(std::exception &e){
               lineEdit->setText(e.what());
               m_Error = true;
        }
    }else if(text == "."){
        //???????????????????????????????????????.???
        auto i = input.lastIndexOf('.');
        //??????????????????
        if(i == -1){
            lineEdit->setText(input+=text);
            m_FirstInput = false;
        }
        else {
            //???????????????????????????????????????????????????
            auto res = input.right(input.length()-i-1);
            //????????????res?????????????????????????????????+-??\ rbegin??? r reserve ????????????????????????
            if((res.contains(QRegExp("[( ) + * /]")) || res.contains("-"))&& res.rbegin()->isNumber()){
                  lineEdit->setText(input+=text);
            }

        }
    }else{//+ - * /  0-9
         if(m_FirstInput || m_Error || m_End){
               //?????????????????????
               lineEdit->setText(text);
               m_FirstInput = false;
               m_Error = false;
               m_End = false;
          }else{//?????????????????????????????????????????????????????????
               if(text == "0"){
                   //???????????????????????????????????????????????????
                   if(input != "0"){
                         auto i = input.lastIndexOf(QRegExp("[+-*/(]"));
                          std::cout<<i<<std::endl;
                         if(i != -1){
                                auto res = input.right(input.length() - i -1);
                                if(res != "0"){
                                    lineEdit->setText(input+=text);
                                }
                         }
                         else    lineEdit->setText(input+=text);
                   }
               }
               else
                   lineEdit->setText(input+=text);
          }
    }
}








