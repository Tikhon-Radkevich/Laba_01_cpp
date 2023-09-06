#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include "employee.h"


int main() {
    std::string binaryFileName;
    int numRecords;

    std::cout << "\n\nEnter the name of the binary file: ";
    std::getline(std::cin, binaryFileName);

    std::cout << "Enter the number of records to create: ";
    std::cin >> numRecords;

    std::string numRecordsStr = std::to_string(numRecords);

    // Launch the Creator utility as a separate process and wait for it to complete
    std::string commandLine = "Creator.exe " + binaryFileName + " " + numRecordsStr;
    
    STARTUPINFO si;
    PROCESS_INFORMATION piCreator;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCreator))
    {
        std::cerr << "Error: Failed to execute Creator utility." << std::endl;
        return 1;
    }

    WaitForSingleObject(piCreator.hProcess, INFINITE);
    CloseHandle(piCreator.hThread);
    CloseHandle(piCreator.hProcess);

    std::cout << "\nContents of the binary file: \n------------------------\n";

    std::ifstream binaryFile(binaryFileName, std::ios::binary);
    if (!binaryFile) {
        std::cerr << "Error: Unable to open the input binary file for reading." << std::endl;
        return 1;
    }
    
    // Read and print employee records from the binary file
    employee emp;
    while (binaryFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        // Print employee details
        std::cout << "Employee ID: " << emp.num << "\n";
        std::cout << "Employee Name: " << emp.name << "\n";
        std::cout << "Hours Worked: " << emp.hours << "\n";
        std::cout << "------------------------\n";
    }
    binaryFile.close();

    std::string reportFileName;
    double hourlyWage;

    // Prompt the user for the name of the report file and the hourly wage
    std::cout << "\nEnter the name of the report file: ";
    std::cin.ignore();
    std::getline(std::cin, reportFileName);

    std::cout << "\nEnter the hourly wage: ";
    std::cin >> hourlyWage;
    std::string hourlyWage_str = std::to_string(hourlyWage);

    // Build the command line for launching the Reporter utility
    commandLine = "Reporter.exe " + binaryFileName + " " + reportFileName + " " + hourlyWage_str;

    // Create a process to run the Reporter utility
    PROCESS_INFORMATION piReporter;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, FALSE, 
        0, NULL, NULL, &si, &piReporter)) {
        std::cerr << "\nError: Failed to execute Reporter utility. \n";
        return 1;
    }

    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hThread);
    CloseHandle(piReporter.hProcess);

    std::cout << "\n\n";

    return 0;
}
