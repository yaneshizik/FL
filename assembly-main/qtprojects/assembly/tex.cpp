#include "tex.h"

void tex() {

    ofstream output("output.txt");
    ifstream input ("table.txt");
    string name;
    //bool ifCircle;
    double x1;
    double x2;
    double y1;
    double y2;
    int str_length;

    string line;

    string ifCircle_string;
    string x1_string;
    string x2_string;
    string y1_string;
    string y2_string;
    //string r_string;


    vector <Line> lines;
    vector <Circle> circles;

    int j = 0;
    while (j < d) {
        if (input.is_open()) {
            x1 = 0;
            x2 = 0;
            y1 = 0;
            y2 = 0;

            getline(input, ifCircle_string, '|');
            getline(input, name, '|');
            getline(input, x1_string, '|');
            getline(input, y1_string, '|');
            getline(input, x2_string, '|');
            getline(input, y2_string, '\n');
            j++;
        }

        if (ifCircle_string == "0") {
            str_length = x1_string.size();

            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                x1 += a * double(int(x1_string[i - 1] - '0'));
            }
            x1 += 0.1 * double(int(x1_string[str_length - 2]) - '0');
            x1 += 0.01 * double(int(x1_string[str_length - 1]) - '0');

            str_length = y1_string.size();
            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                y1 += a * double(int(y1_string[i - 1] - '0'));
            }

            y1 += 0.1 * double(int(y1_string[str_length - 2]) - '0');
            y1 += 0.01  * double(int(y1_string[str_length - 1]) - '0');

            str_length = x2_string.size();
            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                x2 += a * double(int(x2_string[i - 1] - '0'));
            }

            x2 += 0.1 * double(int(x2_string[str_length - 2]) - '0');
            x2 += 0.01 * double(int(x2_string[str_length - 1]) - '0');



            str_length = y2_string.size();
            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                y2 += a * double(int(y2_string[i - 1] - '0'));
            }

            y2 += 0.1 * double(int(y2_string[str_length - 2]) - '0');
            y2 += 0.01 * double(int(y2_string[str_length - 1]) - '0');

            struct Line l;
            l.x1 = x1;
            l.x2 = x2;
            l.y1 = y1;
            l.y2 = y2;
            l.name = name;

            lines.push_back(l);
        } else {

            str_length = x1_string.size();
            //cout << str_length << endl;
            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                x1 += a * double(int(x1_string[i - 1] - '0'));
            }
            x1 += 0.1 * double(int(x1_string[str_length - 2]) - '0');
            x1 += 0.01 * double(int(x1_string[str_length - 1]) - '0');


            str_length = y1_string.size();
            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                y1 += a * double(int(y1_string[i - 1] - '0'));
            }

            y1 += 0.1 * double(int(y1_string[str_length - 2]) - '0');
            y1 += 0.01  * double(int(y1_string[str_length - 1]) - '0');

            str_length = x2_string.size();
            for (int i = 1; i <= (str_length - 3); i++) {
                int a = pow(10, str_length - 3 - i);
                x2 += a * double(int(x2_string[i - 1] - '0'));
            }

            x2 += 0.1 * double(int(x2_string[str_length - 2]) - '0');
            x2 += 0.01 * double(int(x2_string[str_length - 1]) - '0');

            struct Circle cir;
            cir.x = x1;
            cir.r = x2;
            cir.y = y1;
            cir.name = name;
            cir.color = y2_string;

            circles.push_back(cir);

        }

    }

    output << "\\begin{center}\n\t\\begin{tikzpicture}[scale=0.2]" << endl;


    for (auto el : lines) {
        double alpha = atan((el.y2 - el.y1) / (el.x2 - el.x1));
        output << "\t\t\\draw [black] (" << el.x1 << "," << el.y1 << ") -- (" << el.x2 << "," << el.y2 << ");" << endl;
        output << "\t\t\\draw (" << (el.x2 + el.x1)/2 << "," << (el.y2 + el.y1)/2 << ") node [below] {$" << el.name << "$};" << endl;
        output << "\t\t\\fill [black] (" << el.x2 << "," << el.y2 << ") -- (" << el.x2 - c * cos(0.52 + alpha) << "," << el.y2 - c * sin(0.52 + alpha) << ") -- (" << el.x2 - c * cos(alpha - 0.52) << "," << el.y2 - c * sin(alpha - 0.52) << ");" << endl;
    }

    for (auto el : circles) {
        output << "\t\t\\draw[" << el.color <<"](" << el.x << ", " << el.y << ") circle(" << el.r << ");\n";
        output << "\t\t\\draw(" << el.x << ", " << el.y << ") node {$" << el.name << "$};" << endl;
    }

    output << "\t\\end{tikzpicture}" << endl << "\\end{center}" << endl;

}
