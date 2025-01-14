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
    double ms;
    std::tm tm{};
    const char *datePattern = "%Y.%m.%d %H:%M:%S";

    while (std::getline(file, s)) {
        std::istringstream ss(s);
        MyPoint p;
        ss >> std::get_time(&tm, datePattern) >> ms >> p.v[0] >> p.v[1] >> p.v[2];
        if (!ss.fail()) {
            p.tms = std::mktime(&tm) * 1000;
            p.tms += static_cast<time_t>(ms * 1000);
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

std::tuple<const std::vector<double> &, const std::vector<double> &> MyReader::data(int width,
                                                                                    int height) {
    m_yMaxData.clear();
    m_yMinData.clear();
    double vmax = 0.0;
    double vmin = 0.0;
    int i = 0;
    int i_val = 1;
    for (const auto &p : m_data) {
        if (i % 32 == 0) {
            if (i != 0) {
                m_yMaxData.push_back((vmax - 32868) * 0.1 + height / 2);
                m_yMinData.push_back((vmin - 32868) * 0.1 + height / 2);
            }
            vmax = p.v[i_val];
            vmin = p.v[i_val];
        } else {
            vmax = std::max(vmax, p.v[i_val]);
            vmin = std::min(vmin, p.v[i_val]);
        }
        i++;
    }
    return std::forward_as_tuple(m_yMaxData, m_yMinData);
}
