#include "parsetext.h"

ParseText::ParseText()
{
    QString txt;
    QString str;
}

QString ParseText::func(qint32 fnd, int r, QString str) {
    QString txt = str.mid(fnd + 2, 3);
    str.remove(fnd, r + 1);

    if (txt == "RUB" || txt == "rub" || txt == "РУБ" || txt == "руб") str.insert(fnd, QChar(8381));
    else if (txt == "EUR" || txt == "eur" || txt == "ЕВР" || txt == "евр") str.insert(fnd, QChar(8364));
    else if (txt == "COP" || txt == "cop" || txt == "КОП" || txt == "коп") str.insert(fnd, QChar(169));
    else if (txt == "REG" || txt == "reg" || txt == "РЕГ" || txt == "рег") str.insert(fnd, QChar(174));
    else if (txt == "PER" || txt == "per" || txt == "ПРО" || txt == "про") str.insert(fnd, QChar(8240));
    return str;
}
