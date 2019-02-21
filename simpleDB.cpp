#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string cmd = "";
    while (true) {
        std::cout << "db > ";
        std::getline(std::cin, cmd);
        if (cmd == "exit" || cmd == "quit") {
            std::cout << "bye." << std::endl;
            break;
        } else {
            std::cout << "Unrecognized command : " << cmd << std::endl;
        }
    }
    system("pause");
    return 0;
}