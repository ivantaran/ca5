#include "myreader.h"

MyReader::MyReader(const std::string &fileName) {
    auto data = readDataFromFile(fileName);
    std::cout << data.size() << "\n";
}

MyReader::~MyReader() {
}

std::vector<MyReader::MyPoint> MyReader::readDataFromFile(const std::string &fileName) {
    std::string s;
    std::chrono::system_clock::time_point tp;
    std::ifstream file("data.txt");
    std::vector<MyPoint> data;

    while (std::getline(file, s)) {
        std::istringstream ss(s);
        MyPoint p;
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
