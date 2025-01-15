#include "myreader.h"

#include <algorithm>

MyReader::MyReader(const std::string &fileName) {
    for (int i = 0; i < DataWidth; ++i) {
        m_minValue[i] = 0.0;
        m_maxValue[i] = 0.0;
    }
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
    std::chrono::system_clock::time_point tp;
    std::ifstream file(fileName);
    m_data.clear();
    double ms;
    std::tm tm{};
    int32_t v1;
    const char *datePattern = "%Y.%m.%d %H:%M:%S";
    time_t tms;

    while (std::getline(file, s)) {
        std::istringstream ss(s);
        MyPoint p;
        ss >> std::get_time(&tm, datePattern) >> ms >> p.v[0] >> v1 >> p.v[2];
        if (!ss.fail()) {
            tms = std::mktime(&tm) * 1000;
            tms += static_cast<time_t>(ms * 1000);
            v1 = (v1 & 0x8000) ? -(v1 & 0x7fff) : v1;
            // v1 &= 0x7fff;
            p.v[1] = static_cast<double>(v1);
            m_data.push_back(p);
        }
    }

    file.close();
}

void MyReader::updateDataLimits() {
    for (int i = 0; i < DataWidth; ++i) {
        m_maxValue[i] = m_data.front().v[i];
        m_minValue[i] = m_maxValue[i];
    }
    for (const auto &p : m_data) {
        for (int i = 0; i < DataWidth; ++i) {
            m_maxValue[i] = std::max(m_maxValue[i], p.v[i]);
            m_minValue[i] = std::min(m_minValue[i], p.v[i]);
        }
    }
}

std::tuple<const std::vector<double> &, const std::vector<double> &> MyReader::data(int width,
                                                                                    int height) {
    m_yMaxData.clear();
    m_yMinData.clear();
    int i_val = 1;
    int i = 0;

    double vmax = m_data.front().v[i_val];
    double vmin = vmax;
    double dataRange = m_maxValue[i_val] - m_minValue[i_val];
    double dataHalf = 0.5 * dataRange;

    for (const auto &p : m_data) {
        if (i % 8 == 0) {
            if (i != 0) {
                m_yMaxData.push_back((vmax - dataHalf) / dataRange * height + height);
                m_yMinData.push_back((vmin - dataHalf) / dataRange * height + height);
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
