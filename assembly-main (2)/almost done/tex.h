#pragma once
#ifndef TEX_H
#define TEX_H
#include <QApplication>
#include <QWidget>
#include <string>

using namespace std;

class tex : public QObject
{
    Q_OBJECT
public:
    tex(QObject *parent = 0);
    float convertHexToTexDec(const char (&hex)[2]);

public slots:
    void convertToTex();

private:
    struct Round {
        int x = 0;
        int y = 0;
        //string name;
        int r = 0;
    };

    struct Line {
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        //string name;
    };

};

#endif // TEX_H
