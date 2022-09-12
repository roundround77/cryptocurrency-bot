#pragma once
#include <string>
#include <vector>
#include <map>


class AdvisorBot
{
public:
AdvisorBot();
void init();

private:

        void printMenu();
std::string getUserInput();
        void processUserInput(std::string input);
        void printHelp(std::vector<std::string> cmdoutput);
        

};
