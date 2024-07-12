// ItsInjectorV1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <libloaderapi.h>
#include <iostream>
#include <thread>
#include <string>
#include <sys/stat.h>
#include <winternl.h>

using namespace std;

void error(const char* error_title, const char* error_message);

void get_process_id(const char* window_title, DWORD& proc_id)
{
    // Find the window handle by its title
    HWND hwnd = FindWindowA(NULL, window_title);
    if (hwnd == NULL) {
        // If window is not found, display an error message
        error("Error", "Window not found");
    }
    // Get the process ID associated with the window handle
    GetWindowThreadProcessId(hwnd, &proc_id);
}

void error(const char* error_title, const char* error_message)
{
    // Display an error message box and exit the program with an error code
    MessageBoxA(NULL, error_message, error_title, MB_ICONERROR);
    exit(-1);
}

bool file_exists(const string& file_name)
{
    struct stat buffer;
    // Check if the file exists using stat function
    return (stat(file_name.c_str(), &buffer) == 0);
}

int main()
{
    cout << "Hello World!\n";

    // Test getting the process ID of a window
    DWORD proc_id = 0;
    const char* window_title = "test.txt: Bloc de notas"; // Change this to the title of an existing window on your system

    get_process_id(window_title, proc_id);
    if (proc_id != 0)
    {
        // If process ID is found, print it
        cout << "Process ID of '" << window_title << "': " << proc_id << endl;
    }
    else
    {
        // If window is not found, print an error message
        cout << "Could not find window with title: " << window_title << endl;
    }

    // Test if a file exists
    string file_name = "test.txt";
    if (file_exists(file_name))
    {
        // If file exists, print a message
        cout << "File '" << file_name << "' exists." << endl;
    }
    else
    {
        // If file does not exist, print an error message
        cout << "File '" << file_name << "' does not exist." << endl;
        error("File Error", "File does not exist");
    }

    return 0;
}