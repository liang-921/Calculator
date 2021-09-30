#ifndef SCANTOKEN_H
#define SCANTOKEN_H

#include <QChar>
#include <QString>

enum Token_type{
    plus='+',
    minus='-',
    mul='*',
    divi='/',
    lbar='(',
    rbar=')',
    equal='=',
    numbers,
    error,
};

struct Token{
    Token_type type;
    double num;
};

double ChangetoNum(QString &calculate);

Token Get_Token(QString &calculate);

#endif // SCANTOKEN_H
