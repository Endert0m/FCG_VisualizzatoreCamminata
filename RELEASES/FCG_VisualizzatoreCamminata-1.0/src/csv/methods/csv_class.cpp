#include "../headers/csv.hpp"

void CSVProcessor::readCSVFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    // Read headers (first line)
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string header;

        while (std::getline(ss, header, ',')) {
            headers.push_back(header);
        }
    }

    data.clear();

    // Read data
    while (std::getline(file, line)) {
        std::vector<float> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stof(value));
            } catch (const std::invalid_argument& e) {
                // Handle non-integer values if needed
                row.push_back(0); // or some other default/error value
            }
        }

        data.push_back(row);
    }

    file.close();
}

// Getter for headers
const std::vector<std::string>& CSVProcessor::getHeaders() const {
    return headers;
}

// Getter for data
const std::vector<std::vector<float>>& CSVProcessor::getData() const {
    return data;
}


