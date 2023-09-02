#include <iostream>
#include <fstream>
#include "employee.h" // Include the employee struct definition


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <binary_file_name> <num_records> \n";
        return 1; // Exit with an error code
    }

    const char* binaryFileName = argv[1];
    int numRecords = atoi(argv[2]);

    if (numRecords <= 0) {
        std::cerr << "Number of records must be a positive integer. \n";
        return 1; // Exit with an error code
    }

    // Open the binary file for writing in binary mode
    std::ofstream binaryFile(binaryFileName, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error: Unable to open the binary file for writing. \n";
        return 1; // Exit with an error code
    }

    employee emp;

    // Prompt the user to input data for each employee record
    for (int i = 0; i < numRecords; ++i) {
        std::cout << "\nEmployee #" << i + 1 << " details: \n";
        std::cout << "ID: ";
        std::cin >> emp.num;
        std::cout << "Name (up to 10 characters): ";
        std::cin >> emp.name;
        std::cout << "Hours worked: ";
        std::cin >> emp.hours;

        // Write the employee record to the binary file
        binaryFile.write(reinterpret_cast<const char*>(&emp), sizeof(emp));
    }

    // Close the binary file
    binaryFile.close();

    std::cout << "\nBinary file '" << binaryFileName << "' created successfully with " << numRecords << " records. \n";

    return 0; // Exit successfully
}
