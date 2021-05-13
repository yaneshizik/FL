#ifndef TEX_H
#define TEX_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include <QMainWindow>

using namespace std;

#define d 8
#define c 1
class ConvertToTex: public QMainWindow
{

private slots:
    void tex();

public:

struct Circle {
    double x;
    double y;
    string name;
    double r;
    string color;
};

struct Line {
    double x1;
    double y1;
    double x2;
    double y2;
    string name;
};

};
#endif // TEX_H
