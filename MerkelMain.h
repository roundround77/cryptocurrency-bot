#pragma once

#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"


class MerkelMain
{
   std::map<std::string, std::string> commands;
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();
private:
    void printMenu();
    void printCommandMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void gotoPreviousTimeframe();
    int getUserOption();
    std::vector<std::string> getUserChoice();
    void processUserOption(int userOption);
    void processUserChoice(std::vector<std::string>& input);
    
    void movingAverage(std::vector<std::string>& UserChoice);
    
    void countProductByType(std::string type, std::string bookType);
    std::string currentTime;
    //created previousTime to calculate previous time
    std::string previousTime;
    int maxWindow;
    int minWindow;
    //OrderBook orderBook{"20200317.csv"};
    OrderBook orderBook{ "20200601.csv" };
    Wallet wallet;

};
