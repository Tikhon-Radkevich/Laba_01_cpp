#include <iostream>
#include <fstream>
#include "employee.h" // Include the employee struct definition


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "\nUsage: " << argv[0] << " <input_binary_file> <output_report_file> <hourly_wage> \n";
        return 1; // Exit with an error code
    }

    const char* inputBinaryFile = argv[1];
    const char* outputReportFile = argv[2];
    double hourlyWage = std::atof(argv[3]);

    // Open the input binary file for reading in binary mode
    std::ifstream binaryFile(inputBinaryFile, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "\nError: Unable to open the input binary file for reading. \n";
        return 1; // Exit with an error code
    }

    // Open the output report file for writing
    std::ofstream reportFile(outputReportFile);

    if (!reportFile) {
        std::cerr << "\nError: Unable to open the output report file for writing. \n";
        return 1; // Exit with an error code
    }

    employee emp;

    // Write the report header
    reportFile << "Report for file: " << inputBinaryFile << " \n";
    reportFile << "Number, Name, Hours Worked, Salary \n";

    // Read and process employee records from the binary file
    while (binaryFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        // Calculate the salary based on hours worked and hourly wage
        double salary = emp.hours * hourlyWage;

        // Write employee details and salary to the report file
        reportFile << emp.num << ", " << emp.name << ", " << emp.hours << ", " << salary << " \n";
    }

    // Close the input binary file and the output report file
    binaryFile.close();
    reportFile.close();

    std::cout << "Report file '" << outputReportFile << "' created successfully. \n";

    return 0; // Exit successfully
}
