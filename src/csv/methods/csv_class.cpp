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


namespace fs = std::filesystem;

void CSVProcessor::writeCSVFile(const std::string& filename, std::vector<std::vector<double>> data) {
    fs::path filePath(DATA_PATH+filename);

    if (filePath.has_parent_path()) {
        // create_directories crea tutte le cartelle mancanti nella gerarchia.
        // Se le cartelle esistono già, non fa nulla (non dà errore).
        fs::create_directories(filePath.parent_path());
    }


    std::string stem = filePath.stem().string();      // Il nome del file senza estensione (es: "dati")
    std::string extension = filePath.extension().string(); // L'estensione (es: ".csv")
    fs::path parent = filePath.parent_path();              // es: "../../data/ke/"

    
    fs::path finalPath = filePath; // Default è il nome originale
    int counter = 0;
    // Se il file esiste già, cerchiamo il primo numero disponibile: file0.csv, file1.csv...
    if (fs::exists(filePath)) {
        while (true) {
            // Costruiamo il nuovo percorso usando l'operatore / di filesystem 
            // che gestisce correttamente i separatori (/ o \) in base al sistema operativo
            fs::path candidate = parent / (stem + std::to_string(counter) + extension);
            
            if (!fs::exists(candidate)) {
                finalPath = candidate;
                break;
            }
            counter++;
        }
    }
    // 3. APERTURA DEL FILE
    std::ofstream ofile(finalPath);
    if (!ofile.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + finalPath.string());
    }
    // 4. SCRITTURA DELL'HEADER (Requisito: "Collezione #")
    if (!data.empty()) {
        size_t numCols = data[0].size();
        for (size_t i = 1; i <= numCols; ++i) {
            ofile << "Collezione " << i;
            if (i < numCols) ofile << ",";
        }
        ofile << "\n";
    }
    // 5. SCRITTURA DEI DATI
    for (const auto& row : data) {
        for (size_t j = 0; j < row.size(); ++j) {
            ofile << row[j];
            if (j < row.size() - 1) ofile << ",";
        }
        ofile << "\n";
    }
    ofile.close();
    std::cout << "File salvato con successo in: " << finalPath.string() << std::endl;
}