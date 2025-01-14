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
    std::tuple<double, double> dataLimits();
    std::tuple<const std::vector<double> &, const std::vector<double> &> data(int width,
                                                                              int height);

private:
    static const int DataWidth = 3;

    struct MyPoint {
        time_t tms;
        double v[DataWidth];
    };

    std::vector<MyPoint> m_data;
    std::vector<double> m_yMaxData;
    std::vector<double> m_yMinData;
    double m_minValue[DataWidth];
    double m_maxValue[DataWidth];
    double m_minTime;
    double m_maxTime;
    std::vector<MyPoint> readDataFromFile(const std::string &fileName);
};

#endif /* MYREADER_H */
