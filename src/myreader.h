#ifndef MYREADER_H
#define MYREADER_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class MyReader {
public:
    MyReader(const std::string &fileName);
    virtual ~MyReader();

private:
    struct MyPoint {
        std::tm tm;
        double ms;
        double v[3];
    };

    std::vector<MyPoint> readDataFromFile(const std::string &fileName);
};

#endif /* MYREADER_H */
