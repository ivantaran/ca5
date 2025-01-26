# Class Assignment #5

![cmake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white) ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)

![ca5-screenshot](https://github.com/user-attachments/assets/31ffb27c-57d3-49c7-bb22-4b623ccf35f2)

## Releases

[![Downloads](https://custom-icon-badges.demolab.com/badge/-Downloads-darkgreen?style=for-the-badge&logo=downloads&logoColor=white)](https://github.com/ivantaran/ca5/releases)

## Building

### Linux

```bash
cmake -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Windows

```bash
cmake -B build -DCMAKE_CXX_COMPILER=cl -DCMAKE_C_COMPILER=cl -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Usage

Just open the data file using open file dialog box \
![ca5-opendialog](https://github.com/user-attachments/assets/6ca7ad4f-b197-41c6-afe7-5a190ff061e5) \
or use command line

```bash
./ca5 tests/data.txt
```

![Build status](https://github.com/ivantaran/ca5/actions/workflows/main.yml/badge.svg)
