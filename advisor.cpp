#include "advisor.h"
#include "cmdParser.h"
#include <iostream>
#include <vector>

AdvisorBot::AdvisorBot(){

}

void AdvisorBot::init(){
    std::string input;
 
    
    while(true){
        printMenu();
        input = getUserInput();
        processUserInput(input);
    }
}

void AdvisorBot::printMenu(){
 
    std::cout << "===========================================================" <<std::endl;
    std::cout << "Please enter a command or 'help' for a list of commands available." << std::endl;
    
}

void AdvisorBot::printHelp(std::vector<std::string> cmdoutput)
{
    //std::cout << cmdoutput[1] << std::endl;
    if (cmdoutput.size() == 1) {
        std::cout << "\nThe available commands are help, help <cmd>, prod, min, max, avg, predict, time and step. " << std::endl;
    }

    else if (cmdoutput[1] == "prod") 
    {
        std::cout << "\nPurpose: list available products. " << std::endl;
        std::cout << "Command: prod " << std::endl;
        std::cout << "eg: prod " << std::endl;
    }

    else if (cmdoutput[1] == "min")
    {
        std::cout << "\nPurpose: To find minimum bid or ask for product in current time step. " << std::endl;
        std::cout << "Command: min product bid/ask " << std::endl;
        std::cout << "eg: min ETH/BTC ask " << std::endl;
    }

    else if (cmdoutput[1] == "max")
    {
        std::cout << "\nPurpose: To find maximum bid or ask for product in current time step. " << std::endl;
        std::cout << "Command: max product bid/ask " << std::endl;
        std::cout << "eg: max ETH/BTC ask " << std::endl;
    }
    else if (cmdoutput[1] == "avg")
    {
        std::cout << "\nPurpose: To compute average ask or bid for the sent product over the sent number. " << std::endl;
        std::cout << "Command: avg product ask/bid timesteps " << std::endl;
        std::cout << "eg: avg ETH/BTC ask 10 " << std::endl;
    }
    else if (cmdoutput[1] == "predict")
    {
        std::cout << "\nPurpose: To  predict max or min ask or bid for the sent product for the next timestep. " << std::endl;
        std::cout << "Command: min product bid/ask " << std::endl;
        std::cout << "eg: predict max ETH/BTC bid " << std::endl;
    }
    else if (cmdoutput[1] == "time")
    {
        std::cout << "\nPurpose: To state current time in dataset, i.e. which timeframe are we looking at. " << std::endl;
        std::cout << "Command: time " << std::endl;
        std::cout << "eg: time " << std::endl;
    }
    else if (cmdoutput[1] == "step")
    {
        std::cout << "\nPurpose: To move to the next time step. " << std::endl;
        std::cout << "Command: step" << std::endl;
        std::cout << "eg: step " << std::endl;
    }
    else 
    {
        std::cout << "\nInvalid command. Please enter a valid command. " << std::endl;

    }
}

std::string AdvisorBot::getUserInput(){
    std::string input;
    std::cout << "Your command:" <<std::endl;
    return input;
}

void AdvisorBot::processUserInput(std::string input){

std::vector<std::string> cmdoutput = cmdParser::parse(input, ' ');

    if (cmdoutput[0] == "help") {

        printHelp(cmdoutput);
    }
    
    else if (cmdoutput[0] == "prod") {
        std::cout << "prod function" << std::endl;
    }

    else if (cmdoutput[0] == "min") {
        std::cout << "min function" << std::endl;
    }

    else if (cmdoutput[0] == "max") {
        std::cout << "max function " << std::endl;
    }

    else if (cmdoutput[0] == "avg") {
        std::cout << "avg function " << std::endl;
    }

    else if (cmdoutput[0] == "predict") {
        std::cout << "predict function " << std::endl;
    }

    else if (cmdoutput[0] == "time") {
        std::cout << "time function " << std::endl;
    }

    else if (cmdoutput[0] == "step") {
        std::cout << "step function " << std::endl;
    }

    else 
    {
        std::cout << "Invalid input. Please enter avail input " << std::endl;
    }

};

