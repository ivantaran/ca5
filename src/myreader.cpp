#include "myreader.h"

#include <algorithm>

MyReader::MyReader(const std::string &fileName) {
    for (int i = 0; i < DataWidth; ++i) {
        m_minValue[i] = 0.0;
        m_maxValue[i] = 0.0;
    }
    m_minTime = 0.0;
    m_maxTime = 0.0;
    m_data = readDataFromFile(fileName);
    std::cout << m_data.size() << "\n";
}

MyReader::~MyReader() {
}

std::vector<MyReader::MyPoint> MyReader::readDataFromFile(const std::string &fileName) {
    std::string s;
    std::chrono::system_clock::time_point tp;
    std::ifstream file(fileName);
    std::vector<MyPoint> data;
    const char *datePattern = "%Y.%m.%d %H:%M:%S";
    // double v[DataWidth];

    while (std::getline(file, s)) {
        std::istringstream ss(s);
        MyPoint p;
        ss >> std::get_time(&p.tm, datePattern) >> p.ms >> p.v[0] >> p.v[1] >> p.v[2];
        if (!ss.fail()) {
            // std::cout << std::put_time(&p.tm, "%c\t") << p.v[2] << '\n';
            data.push_back(p);
        }
    }

    file.close();
    return data;
}

std::tuple<double, double> MyReader::dataLimits() {
    auto mm =
        std::minmax_element(m_data.begin(), m_data.end(),
                            [](const MyPoint &a, const MyPoint &b) { return a.v[0] < b.v[0]; });
    double range = mm.second->v[0] - mm.first->v[0];
    std::cout << std::scientific << mm.first->v[0] << '\t' << mm.second->v[0] << '\t' << range
              << '\n';
    return std::make_tuple(mm.first->v[0], mm.second->v[0]);
}

const std::vector<double> &MyReader::data(int width, int height) {
    m_yData.clear();
    for (const auto &p : m_data) {
        m_yData.push_back(p.v[2] + 100);
    }
    return m_yData;
}
