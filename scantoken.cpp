#include "scantoken.h"
#include <iostream>
#include <QString>

double ChangetoNum(QString &calculate)
{
     QString str;
     while(true){
        if(calculate.isEmpty()){
            break;
        }
        QChar qch=calculate.front();
        if((qch>='0'&&qch<='9')||qch=='.'){
            str.append(qch);
            calculate=calculate.right(calculate.size()-1);
        }else{
            break;
        }
     }
     return str.toDouble();
}

Token Get_Token(QString &calculate)
{
   Token token;
   if(calculate.isEmpty()){
       //std::cerr<<"This Calculation is empty!\n"<<"Please enter a new Calculation again.";
       token.type=error;
       return token;
   }
   char ch=calculate.front().unicode();
   switch (ch) {
       case '+':
       case '-':
       case '*':
       case '/':
       case '(':
       case ')':
       case '=':
            token.type=Token_type(ch);
       break;
       case '0':
       case '1':
       case '2':
       case '3':
       case '4':
       case '5':
       case '6':
       case '7':
       case '8':
       case '9':
            token.type=numbers;
            token.num=ChangetoNum(calculate);
       break;
   }
   return token;
}
