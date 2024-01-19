#include <iostream>
#include <fstream>
#include <cstdlib>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>

int main() {
    std::cout << "Enter the path of the PDF file you want to process: ";
    std::string pdfFilePath;
    std::cin >> pdfFilePath;

    std::string outputFilePath = "Output.txt";  

    try {
        auto doc = poppler::document::load_from_file(pdfFilePath);

        if (!doc) {
            std::cerr << "Error opening PDF file." << std::endl;
            return 1;
        }

        std::ofstream outputFile(outputFilePath);
        if (!outputFile.is_open()) {
            std::cerr << "Error opening output file." << std::endl;
            return 1;
        }

        outputFile << "Title: " << doc->title() << "\n";
        outputFile << "Author/Producer: " << doc->author() << "\n";
        outputFile << "Creation Date: " << doc->creation_date().to_string() << "\n";
        outputFile << "Modification Date: " << doc->mod_date().to_string() << "\n\n";

        for (int i = 0; i < doc->pages(); ++i) {
            auto page = doc->create_page(i);
            std::string text = page->text().to_utf8();
            outputFile << "Page " << i + 1 << " Text:\n" << text << "\n\n";
        }

        outputFile.close();

        std::cout << "Extraction complete. Output saved to " << outputFilePath << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}