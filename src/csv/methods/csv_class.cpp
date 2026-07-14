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

/*
void CSVProcessor::writeCSVFile(const std::string& filename, std::vector<std::vector<double>> data){
   char c = '0';
   std::ifstream file (filename);
   while (file.is_open())
   {
      file.close();
      file.open(filename+c++);
   }
   
   std::ofstream ofile(filename);

}*/
namespace fs = std::filesystem;

void CSVProcessor::writeCSVFile(const std::string& filename, std::vector<std::vector<double>> data) {
    fs::path filePath(filename);
    std::string stem = filePath.stem().string();      // Il nome del file senza estensione (es: "dati")
    std::string extension = filePath.extension().string(); // L'estensione (es: ".csv")
    
    std::string finalFilename = filename;
    int counter = 0;
    // 1. LOGICA DI CONTROLLO NOME (Evitare sovrascrittura)
    // Se il file esiste già, cerchiamo un nome disponibile: nome0.ext, nome1.ext...
    if (fs::exists(filePath)) {
        while (fs::exists(stem + std::to_string(counter) + extension)) {
            counter++;
        }
        finalFilename = stem + std::to_string(counter) + extension;
    }
    // 2. APERTURA DEL FILE
    std::ofstream ofile(finalFilename);
    if (!ofile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + finalFilename);
    }
    // 3. SCRITTURA DELL'HEADER (Requisito: "Collezione #")
    if (!data.empty()) {
        size_t numCols = data[0].size();
        for (size_t i = 1; i <= numCols; ++i) {
            ofile << "Collezione " << i;
            if (i < numCols) {
                ofile << ",";
            }
        }
        ofile << "\n";
    }
    // 4. SCRITTURA DEI DATI
    for (const auto& row : data) {
        for (size_t j = 0; j < row.size(); ++j) {
            ofile << row[j];
            if (j < row.size() - 1) {
                ofile << ",";
            }
        }
        ofile << "\n";
    }
    ofile.close();
    std::cout << "File salvato con successo come: " << finalFilename << std::endl;
}