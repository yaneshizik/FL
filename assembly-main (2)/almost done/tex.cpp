#include <QApplication>
#include <QWidget>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <utility>
#include "tex.h"

using namespace std;

tex::tex(QObject *parent)
    : QObject(parent)
{}

float tex::convertHexToTexDec(const char (&hex)[2]) {
    int dec = 0;
    for (int i = 0; i < 2; i++) {
        if (int(hex[i]) < 58) {
            //digit
            dec += pow(16, 1 - i)*(int(hex[i]) - 48);
        }
        else {
            //letter
            dec += pow(16, 1 - i)*(int(hex[i]) - 87);
        }
    }

    //convert to tex rgb format: 1 instead of 255
    float ans = dec/255.0;
    ans = int(ans*100 + 0.5)/100.0;
    return ans;
}


void tex::convertToTex() {

    ofstream output("../../../output.txt");
    ifstream input ("../../../text.txt");
    //string name;

    string ifRound_string;
    string x1_string;
    string x2_string;
    string y1_string;
    string y2_string;
    string r_string;

    vector <Line> lines;
    vector <Round> rounds;

    string roundPenColor;
    char roundRed_c[2];
    char roundGreen_c[2];
    char roundBlue_c[2];
    float roundRed;
    float roundGreen;
    float roundBlue;
    string roundBrushColor;
    char roundBrushRed_c[2];
    char roundBrushGreen_c[2];
    char roundBrushBlue_c[2];
    float roundBrushRed;
    float roundBrushGreen;
    float roundBrushBlue;
    string roundWidth_str;
    float roundWidth;
    string arrowPenColor;
    char arrowRed_c[2];
    char arrowGreen_c[2];
    char arrowBlue_c[2];
    float arrowRed;
    float arrowGreen;
    float arrowBlue;
    string arrowWidth_str;
    float arrowWidth;

    if (input.is_open()) {

        getline(input, roundPenColor, '|');
        roundRed_c[0] = roundPenColor[1];
        roundRed_c[1] = roundPenColor[2];
        roundGreen_c[0] = roundPenColor[3];
        roundGreen_c[1] = roundPenColor[4];
        roundBlue_c[0] = roundPenColor[5];
        roundBlue_c[0] = roundPenColor[6];
        //convert to TeX color rgb format
        roundRed = convertHexToTexDec(roundRed_c);
        roundGreen = convertHexToTexDec(roundGreen_c);
        roundBlue = convertHexToTexDec(roundBlue_c);

        getline(input, roundBrushColor, '|');
        roundBrushRed_c[0] = roundBrushColor[1];
        roundBrushRed_c[1] = roundBrushColor[2];
        roundBrushGreen_c[0] = roundBrushColor[3];
        roundBrushGreen_c[1] = roundBrushColor[4];
        roundBrushBlue_c[0] = roundBrushColor[5];
        roundBrushBlue_c[1] = roundBrushColor[6];
        //convert to TeX color rgb format
        roundBrushRed = convertHexToTexDec(roundBrushRed_c);
        roundBrushGreen = convertHexToTexDec(roundBrushGreen_c);
        roundBrushBlue = convertHexToTexDec(roundBrushBlue_c);

        getline(input, roundWidth_str, '|');

        for (int i = 0; i < roundWidth_str.size(); i++) {
                int a = pow(10, roundWidth_str.size() - i - 1);
                roundWidth += a * (int(roundWidth_str[i] - '0'));
        }
        roundWidth = roundWidth;

        getline(input, arrowPenColor, '|');
        arrowRed_c[0] = arrowPenColor[1];
        arrowRed_c[1] = arrowPenColor[2];
        arrowGreen_c[0] = arrowPenColor[3];
        arrowGreen_c[1] = arrowPenColor[4];
        arrowBlue_c[0] = arrowPenColor[5];
        arrowBlue_c[1] = arrowPenColor[6];
        //convert to TeX color rgb format
        arrowRed = convertHexToTexDec(arrowRed_c);
        arrowGreen = convertHexToTexDec(arrowGreen_c);
        arrowBlue = convertHexToTexDec(arrowBlue_c);

        getline(input, arrowWidth_str, '\n');

        for (int i = 0; i < arrowWidth_str.size(); i++) {
                int a = pow(10, arrowWidth_str.size() - i - 1);
                arrowWidth += a * (int(arrowWidth_str[i] - '0'));
        }
        arrowWidth = arrowWidth;

    }


    while (getline(input, ifRound_string, '|')) {

        if (ifRound_string == "0") {
            struct Line line;
            //getline(input, name, '|');
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, x2_string, '|');
            getline(input, y2_string, '\n');

            for (int i = 0; i < x1_string.size(); i++) {
                int a = pow(10, x1_string.size() - i - 1);
                line.x1 += a * (int(x1_string[i] - '0'));
            }

            for (int i = 0; i < y1_string.size(); i++) {
                int a = pow(10, y1_string.size() - i - 1);
                line.y1 += a * (int(y1_string[i] - '0'));
            }
            line.y1=-line.y1;

            for (int i = 0; i < x2_string.size(); i++) {
                int a = pow(10, x2_string.size() - i - 1);
                line.x2 += a * (int(x2_string[i] - '0'));
            }

            for (int i = 0; i < y2_string.size(); i++) {
                int a = pow(10, y2_string.size() - i - 1);
                line.y2 += a * (int(y2_string[i] - '0'));
            }
            line.y2 = -line.y2;
            //l.name = name;

            lines.push_back(line);
        }

        else if (ifRound_string == "1") {
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, r_string, '\n');
            struct Round round;

            for (int i = 0; i < x1_string.size(); i++) {
                int a = pow(10, x1_string.size() - i - 1);
                round.x += a * (int(x1_string[i] - '0'));
            }

            for (int i = 0; i < y1_string.size(); i++) {
                int a = pow(10, y1_string.size() - i - 1);
                round.y += a * (int(y1_string[i] - '0'));
            }

            round.y = -round.y;

            for (int i = 0; i < r_string.size(); i++) {
                int a = pow(10, r_string.size() - i - 1);
                round.r += a * (int(r_string[i] - '0'));
            }

            //cir.name = name;
            //cir.color = y2_string;

            rounds.push_back(round);

        }

    }

    output << "\\documentclass[12pt]{article}" << endl;
    output << "\\usepackage{tikz}" << endl;
    output << "\\begin{document}" << endl;
    output << "\\definecolor{arrowPenColor}{rgb}{" << arrowRed << ", " << arrowGreen << ", " << arrowBlue << "}" << endl;
    output << "\\definecolor{roundPenColor}{rgb}{" << roundRed << ", " << roundGreen << ", " << roundBlue << "}" << endl;
    output << "\\definecolor{roundBrushColor}{rgb}{" << roundBrushRed << ", " << roundBrushGreen << ", " << roundBrushBlue << "}" << endl;
    output << "\\begin{center}\n\t\\begin{tikzpicture}[scale=0.03]" << endl;

    for (auto el : lines) {
        output << "\t\t\\draw [line width = " << arrowWidth << ", arrowPenColor] (" <<
                                                        el.x1 << "," << el.y1 << ") -- (" << el.x2 << "," << el.y2 << ");" << endl;
    }

    for (auto el : rounds) {

        output << "\t\t\\draw[line width = " << roundWidth << ", roundPenColor, fill = roundBrushColor](" << el.x <<
                                                        ", " << el.y << ") circle(" << el.r << ");\n";
    }

    output << "\t\\end{tikzpicture}" << endl << "\\end{center}" << endl;
    output << "\\end{document}" << endl;

}
