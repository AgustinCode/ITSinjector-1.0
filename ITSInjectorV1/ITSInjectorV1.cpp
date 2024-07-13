// ItsInjectorV1.cpp
#include <windows.h>
#include <libloaderapi.h>
#include <iostream>
#include <thread>
#include <string>
#include <sys/stat.h>
#include <winternl.h>


class Injector {

private:

    DWORD proc_id;
    std::string window_title;
    std::string dll_path;

    void error(const char* error_title, const char* error_message) {
        MessageBoxA(NULL, error_message, error_title, MB_ICONERROR);
        exit(-1);
    }

    bool file_exists(const std::string& file_name) {
        struct stat buffer;
        return (stat(file_name.c_str(), &buffer) == 0);
    }


public:

    Injector(const std::string& window_title, const std::string& dll_path)
        : window_title(window_title), dll_path(dll_path), proc_id(0) {}

    void get_process_id() {
        HWND hwnd = FindWindowA(NULL, window_title.c_str());
        if (hwnd == NULL) {
            error("Error", "Window not found");
        }
        GetWindowThreadProcessId(hwnd, &proc_id);
    }

    bool check_dll_exists() {
        if (!file_exists(dll_path)) {
            error("File Error", "DLL file does not exist");
            return false;
        }
        return true;
    }

    void inject() {
<<<<<<< HEAD
        std::cout << "Injecting DLL: " << dll_path << " into process ID: " << proc_id << std::endl;
        HANDLE h_process = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
        if (!h_process)
        {
            error("OpenProcess", ("Error to open a handle to the process"));
        }

        void* allocated_memory = VirtualAllocEx(h_process, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

        if (!allocated_memory)
        {
            error("VirtualAllocEx", "Failed to allocate memory");
        }

        if (!WriteProcessMemory(h_process, nullptr, dll_path.c_str(), MAX_PATH, nullptr)) 
        {
            error("WriteProcessMemory", "Error writting process memory");
        }

        HANDLE h_thread = CreateRemoteThread(h_process, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), allocated_memory, NULL, nullptr);
        if (!h_thread)
        {
            error("CreateRemoteThread", "Failed to create remote thread");
        }

        CloseHandle(h_process);
        VirtualFreeEx(h_process, allocated_memory, NULL, MEM_RELEASE);
        MessageBoxA(0, "Succesfully injected!", "Success", 0);


=======
        // Aquí implementaremos la lógica de inyección de DLL
        // Por ahora, solo imprimimos información
        std::cout << "Injecting DLL: " << dll_path << " into process ID: " << proc_id << std::endl;
        // TODO: Implementar la inyección real de la DLL
>>>>>>> origin/master
    }

    void run() {
        get_process_id();
        if (proc_id != 0) {
            std::cout << "Process ID of '" << window_title << "': " << proc_id << std::endl;
            if (check_dll_exists()) {
                inject();
            }
        }
        else {
            std::cout << "Could not find window with title: " << window_title << std::endl;
        }
    }
};

int main() {
    std::string window_title = "test: Bloc de notas";
    std::string dll_path = "test.txt";

    Injector injector(window_title, dll_path);
    injector.run();

    return 0;
}