#include "myplot.h"

#include <QApplication>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

struct mypoint {
    std::tm tm;
    double ms;
    double v[3];
};

std::vector<mypoint> readdata() {
    std::string s;
    std::chrono::system_clock::time_point tp;
    std::ifstream file("data.txt");
    std::vector<mypoint> data;

    while (std::getline(file, s)) {
        std::istringstream ss(s);
        mypoint p;
        ss >> std::get_time(&p.tm, "%Y.%m.%d %H:%M:%S") >> //
            p.ms >> p.v[0] >> p.v[1] >> p.v[2];

        if (ss.fail()) {
            // std::cerr << "ERR" << "\n";
        } else {
            // std::cout << std::put_time(&p.tm, "%c\t") << p.v[2] << '\n';
            data.push_back(p);
        }
        if (file.eof()) {
            break;
        }
    }
    // std::cout << s << "\n";
    file.close();
    return data;
}

int main(int argc, char *argv[]) {
    auto data = readdata();
    std::cout << data.size() << "\n";
    for (const auto &p : data) {
        // std::cout << std::put_time(&p.tm, "%c\t") << p.v[2] << '\n';
    }
    QApplication app(argc, argv);
    MyPlot window;
    window.show();
    return app.exec();
}
