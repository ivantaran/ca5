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
    const std::vector<double> &data(int width, int height);

private:
    static const int DataWidth = 3;

    struct MyPoint {
        std::tm tm;
        double ms;
        double v[DataWidth];
    };

    std::vector<MyPoint> m_data;
    std::vector<double> m_yData;
    double m_minValue[DataWidth];
    double m_maxValue[DataWidth];
    double m_minTime;
    double m_maxTime;
    std::vector<MyPoint> readDataFromFile(const std::string &fileName);
};

#endif /* MYREADER_H */
