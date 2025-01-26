#include "myreader.h"

#include <iterator>
// #include <limits>

MyReader::MyReader(const std::string &fileName) {
    m_minValue = 0.0;
    m_maxValue = 0.0;
    m_minTime = 0;
    m_maxTime = 0;
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
    if (!m_data.size()) {
        m_minValue = 0.0;
        m_maxValue = 0.0;
        m_minTime = 0;
        m_maxTime = 0;
        return;
    }
    m_maxValue = m_data.front().value;
    m_maxTime = m_data.front().t_ms;
    m_minTime = m_maxTime;
    for (const auto &p : m_data) {
        m_maxValue = std::max(m_maxValue, p.value);
        m_minValue = std::min(m_minValue, p.value);
        m_maxTime = std::max(m_maxTime, p.t_ms);
        m_minTime = std::min(m_minTime, p.t_ms);
    }
}

const myarray_t &MyReader::plotData(int x, int y, int width, int height) {
    m_plotData.clear();
    if (!m_data.size()) {
        return m_plotData;
    }
    double vmax = m_data.front().value;
    double vmin = vmax;
    double valueRange = m_maxValue - m_minValue;
    double valueHalf = 0.5 * (m_maxValue + m_minValue);
    double timeRange = m_maxTime - m_minTime;
    time_t timeStep = (timeRange > width) ? timeRange / width + 0.5 : 1;
    time_t t = m_minTime + timeStep;
    auto last = &m_data.back();
    for (const auto &point : m_data) {
        vmax = std::max(vmax, point.value);
        vmin = std::min(vmin, point.value);
        if (point.t_ms >= t || &point == last) {
            std::array<int64_t, 3> d = {
                static_cast<int64_t>((point.t_ms - m_minTime) / timeRange * width + x),
                static_cast<int64_t>((valueHalf - vmax) / valueRange * height + height * 0.5 + y),
                static_cast<int64_t>((valueHalf - vmin) / valueRange * height + height * 0.5 + y),
            };
            m_plotData.push_back(d);
            auto np = std::next(&point);
            vmax = np->value; //-std::numeric_limits<double>::max();
            vmin = np->value; //+std::numeric_limits<double>::max();
            t += timeStep;
        }
    }
    return m_plotData;
}

size_t MyReader::dataSize() const {
    return m_data.size();
}
