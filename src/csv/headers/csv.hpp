#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifndef CSV_H
#define CSV_H

#define DATA_PATH std::string("./../../data/")

class CSVProcessor {
private:
    std::vector<std::string> headers;
    std::vector<std::vector<float>> data;

public:
    // Method to read CSV file and store data in vectors
    void readCSVFile(const std::string& filename);
    // Getter for headers
    const std::vector<std::string>& getHeaders() const;
    // Getter for data
    const std::vector<std::vector<float>>& getData() const;

};

#endif