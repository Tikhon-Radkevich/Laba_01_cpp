#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include "employee.h"


int main() {
    char binaryFileName[256] = "test_bin";
    int numRecords = 2;

    // Prompt the user for the name of the binary file and the number of records to create
    // std::cout << "Enter the name of the binary file: ";
    // std::cin.getline(binaryFileName, sizeof(binaryFileName));

    // std::cout << "Enter the number of records to create: ";
    // std::cin >> numRecords;

    // Launch the Creator utility as a separate process and wait for it to complete
    char numRecordsStr[16];
    snprintf(numRecordsStr, sizeof(numRecordsStr), "%d", numRecords);

    pid_t creatorPid = fork();

    if (creatorPid == -1) {
        std::cerr << "\nError: Forking Creator process failed. \n";
        return 1;
    } else if (creatorPid == 0) {
        // Child process (Creator)
        execl("./Creator", "./Creator", binaryFileName, numRecordsStr, nullptr);
        std::cerr << "\nError: Failed to execute Creator utility. \n";
        exit(1);
    } else {
        // Parent process (Main)
        int creatorStatus;
        waitpid(creatorPid, &creatorStatus, 0);

        if (WIFEXITED(creatorStatus) && WEXITSTATUS(creatorStatus) == 0) {
            // Creator utility completed successfully
            std::cout << "Contents of the binary file: \n------------------------\n";

            std::ifstream binaryFile(binaryFileName, std::ios::binary);
            if (!binaryFile) {
                std::cerr << "\nError: Unable to open the input binary file for reading.\n";
                return 1;
            }

            employee emp;
            // Read and print employee records from the binary file
            while (binaryFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
                // Print employee details
                std::cout << "Employee ID: " << emp.num << "\n";
                std::cout << "Employee Name: " << emp.name << "\n";
                std::cout << "Hours Worked: " << emp.hours << "\n";
                std::cout << "------------------------\n";
            }
            
            binaryFile.close();

            } else {
                std::cerr << "\nError: Creator utility encountered an issue. \n";
                return 1;
            }
        }

    char reportFileName[256];
    double hourlyWage;

    // Prompt the user for the name of the report file and the hourly wage
    std::cout << "\nEnter the name of the report file: ";
    std::cin.ignore(); // Clear the newline character from the previous input
    std::cin.getline(reportFileName, sizeof(reportFileName));

    std::cout << "Enter the hourly wage: ";
    std::cin >> hourlyWage;

    // Launch the Reporter utility as a separate process and wait for it to complete
    pid_t reporterPid = fork();

    if (reporterPid == -1) {
        std::cerr << "\nError: Forking Reporter process failed. \n";
        return 1;
    } else if (reporterPid == 0) {
        // Child process (Reporter)
        execl("./Reporter", "./Reporter", binaryFileName, reportFileName, numRecordsStr, nullptr);
        std::cerr << "\nError: Failed to execute Reporter utility. \n";
        exit(1);
    } else {
        // Parent process (Main)
        int reporterStatus;
        waitpid(reporterPid, &reporterStatus, 0);

        if (WIFEXITED(reporterStatus) && WEXITSTATUS(reporterStatus) == 0) {
            // Reporter utility completed successfully
            std::cout << "\nGenerated report: \n";
            execl("/bin/cat", "/bin/cat", reportFileName, nullptr);
        } else {
            std::cerr << "\nError: Reporter utility encountered an issue. \n";
            return 1;
        }
    }
    
    std::cout << "\n\n\n";
    return 0;
}
