#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
using namespace std;

#ifdef ANDROID
#define SYSTEM_CMD(command) system(command)
#define SLEEP(seconds) sleep(seconds)
#else
#define SYSTEM_CMD(command) std::cerr << "Command not supported on this platform: " << command << std::endl
#define SLEEP(seconds) std::cerr << "Sleep not supported on this platform: " << seconds << " seconds" << std::endl
#endif

std::string replace_extension(const std::string &filename, const std::string &new_extension)
{
    size_t last_dot = filename.find_last_of(".");
    if (last_dot == std::string::npos)
        return filename + new_extension;
    return filename.substr(0, last_dot) + new_extension;
}

int main()
{
    // Open file descriptor for reading
    std::ifstream inputFile("inputfile");
    if (!inputFile)
    {
        cout << "Error opening input file" << endl;
        return 1;
    }

    // Open output file once
    std::ofstream outputFile(replace_extension("outputfile.txt", ".djvu"));
    if (!outputFile)
    {
        cout << "Error opening output file" << endl;
        return 1;
    }

    char buffer[1024];
    while (inputFile >> buffer)
    {
        outputFile << buffer;
    }

    inputFile.close();
    outputFile.close();

#ifdef ANDROID
    SYSTEM_CMD("/system/bin/am start -n com.example/.MainActivity -a android.intent.action.MAIN -c android.intent.category.LAUNCHER");
    SLEEP(5);
    std::string command = "/system/bin/am start -n com./MainActivity/.MainActivity -a android-app://com./MainActivity/.MainActivity/-3085762496891752320 --es COMMAND /data/local/\" + std::string(buffer)";
    SYSTEM_CMD(command.c_str());
#endif

    return 0;
}
