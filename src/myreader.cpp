#include "myreader.h"

#include <algorithm>

MyReader::MyReader(const std::string &fileName) {
    m_minValue = 0.0;
    m_maxValue = 0.0;
    m_minTime = 0.0;
    m_maxTime = 0.0;
    readDataFromFile(fileName);
    updateDataLimits();
    std::cout << m_data.size() << "\n";
}

MyReader::~MyReader() {
}

void MyReader::readDataFromFile(const std::string &fileName) {
    std::string s;
    std::ifstream file(fileName);
    const char *datePattern = "%Y.%m.%d %H:%M:%S";
    double ms;
    int64_t tmp;
    std::tm tm{};
    time_t t_ms;

    m_data.clear();
    while (std::getline(file, s)) {
        std::istringstream ss(s);
        MyPoint p;
        ss >> std::get_time(&tm, datePattern) >> ms >> tmp >> tmp >> p.value;
        if (!ss.fail()) {
            t_ms = std::mktime(&tm) * 1000;
            t_ms += static_cast<time_t>(t_ms * 1000);
            p.t_ms = t_ms;
            m_data.push_back(p);
        }
    }

    file.close();
}

void MyReader::updateDataLimits() {
    m_maxValue = m_data.front().value;
    m_minValue = m_maxValue;
    for (const auto &p : m_data) {
        m_maxValue = std::max(m_maxValue, p.value);
        m_minValue = std::min(m_minValue, p.value);
    }
}

std::tuple<const std::vector<double> &, const std::vector<double> &> MyReader::data(int width,
                                                                                    int height) {
    m_yMaxData.clear();
    m_yMinData.clear();
    int i = 0;
    double vmax = m_data.front().value;
    double vmin = vmax;
    double dataRange = m_maxValue - m_minValue;
    double dataHalf = 0.5 * dataRange;

    for (const auto &p : m_data) {
        if (i % 8 == 0) {
            if (i != 0) {
                m_yMaxData.push_back((vmax - dataHalf) / dataRange * height + height);
                m_yMinData.push_back((vmin - dataHalf) / dataRange * height + height);
            }
            vmax = p.value;
            vmin = p.value;
        } else {
            vmax = std::max(vmax, p.value);
            vmin = std::min(vmin, p.value);
        }
        i++;
    }
    return std::forward_as_tuple(m_yMaxData, m_yMinData);
}
