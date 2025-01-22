#ifndef MYREADER_H
#define MYREADER_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class MyReader {
public:
    MyReader(const std::string &fileName);
    virtual ~MyReader();
    std::tuple<const std::vector<double> &, const std::vector<double> &> data(int width,
                                                                              int height);

private:
    struct MyPoint {
        time_t t_ms;
        double value;
    };

    std::vector<MyPoint> m_data;
    std::vector<double> m_yMaxData;
    std::vector<double> m_yMinData;
    double m_minValue;
    double m_maxValue;
    double m_minTime;
    double m_maxTime;
    void readDataFromFile(const std::string &fileName);
    void updateDataLimits();
};

#endif /* MYREADER_H */
