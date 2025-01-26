#ifndef MYREADER_H
#define MYREADER_H

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using myarray_t = std::vector<std::array<int64_t, 3>>;

class MyReader {
public:
    MyReader(const std::string &fileName);
    virtual ~MyReader();
    const myarray_t &plotData(int x, int y, int width, int height);
    size_t dataSize() const;

private:
    struct MyPoint {
        time_t t_ms;
        double value;
    };

    std::vector<MyPoint> m_data;
    myarray_t m_plotData;
    double m_minValue;
    double m_maxValue;
    time_t m_minTime;
    time_t m_maxTime;
    void readDataFromFile(const std::string &fileName);
    void updateDataLimits();
};

#endif /* MYREADER_H */
