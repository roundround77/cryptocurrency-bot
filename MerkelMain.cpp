#include <iostream>
#include <vector>
#include<map>
#include <cstdio>
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{
   //created a map to carry commans and there descriptions
    commands.insert(std::pair<std::string, std::string>("help", "The available commands are help, prod, min, max, avg, predict, time and step"));
    commands.insert(std::pair<std::string, std::string>("prod", "list available products"));
    commands.insert(std::pair<std::string, std::string>("min", " find minimum bid or ask for product in current time step"));
    commands.insert(std::pair<std::string, std::string>("max", "find maximum bid or ask for product in current time step"));
    commands.insert(std::pair<std::string, std::string>("avg", "avg product ask/bid timesteps"));
    commands.insert(std::pair<std::string, std::string>("predict", "predict max or min ask or bid for the sent product for the next time"));
    commands.insert(std::pair<std::string, std::string>("time", "state current time in dataset, i.e. which timeframe are we looking at"));
    commands.insert(std::pair<std::string, std::string>("step", "move to next time step"));
    //For the predict command, these are the variables to carray max and min for moving average.
    int maxWindow = 0;
    int minWindow = 0;
}

void MerkelMain::init()
{
    //map with key as command and value as description
    int input;
    std::string menuInitiate;
    std::vector<std::string> inputParameters;
    currentTime = orderBook.getEarliestTime();
    previousTime = orderBook.getPreviousTime(currentTime);
    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        //commented printMenu method and created a method to take take user choice
        //called getUserChoice to take his input as a string in a string array
        //and finally i created a method to process that choice with the commands he wants below
        //printCommandMenu();
        //input = getUserOption();
        inputParameters = getUserChoice();
        processUserChoice(inputParameters);
    }
}

void MerkelMain::printCommandMenu()
{
    // 1 print help
    std::cout << "1: Help " << std::endl;
    // 2 print help for command
    std::cout << "2: help cmd " << std::endl;
    // 3 list all products
    std::cout << "3: prod " << std::endl;
    // 4 get minimum bid/ask 
    std::cout << "4: min" << std::endl;
    // 5 get maximum bid/ask
    std::cout << "5: max " << std::endl;
    // 6 get average bid/ask for a product   
    std::cout << "6: avg " << std::endl;
    //predict value of product
    std::cout << "7: predict " << std::endl;
    //state current time in dataset
    std::cout << "8: time " << std::endl;
    //step to next time step
    std::cout << "9: step " << std::endl;
    //count number of products
    std::cout << "10: count " << std::endl;
}
void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "The current time now is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;



    }
    // std::cout << "OrderBook contains :  " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }  
    // }    
    // std::cout << "OrderBook asks:  " << asks << " bids:" << bids << std::endl;

}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }

    }

    currentTime = orderBook.getNextTime(currentTime);
}

//function to get the previous timeframe
void MerkelMain::gotoPreviousTimeframe()
{

    currentTime = orderBook.getPreviousTime(currentTime);
}



int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e)
    {
        // 
    }
    std::cout << "You chose the option: " << userOption << std::endl;
    return userOption;
}

// This will get user input and validate it then parse it using tokenise

std::vector<std::string> MerkelMain::getUserChoice()
{
    std::string input;
    bool isEmpty = true;
    //This function will check if input is not empty
    while (isEmpty)
    {
        std::cout << "user>";
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout<<"advisorbot>" << "Cannot enter empty values" << std::endl;
        }
        else
            isEmpty = false;
    }

    //I have used the pre-declared method tokenise to parse the input command
    std::vector<std::string> inputParameters = CSVReader::tokenise(input, ' ');
    return inputParameters;


}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
}


//TASK 2 
//This is a simple function to count number of products by type.
void MerkelMain::countProductByType(std::string type, std::string bookType)
{
    std::vector<OrderBookEntry> entriesAsk;
    //iterate over all products and compare if they are bid or ask
    for (std::string const& p : orderBook.getKnownProducts())
    {
        //if the booking type is ask then get the orders books of type ask otherwise get of type bid
       if(bookType == "ask")
            entriesAsk = orderBook.getOrders(OrderBookType::ask,type, currentTime);
       else if (bookType == "bid")
           entriesAsk = orderBook.getOrders(OrderBookType::bid, type, currentTime);
    }
    //we check if fetched book sizes is not empty
    //then we return the size of entries vector ff
            if (entriesAsk.size() != 0)
                std::cout << "advisorbot>" << "The number of " <<bookType <<" " << type << " is " << entriesAsk.size()
                << std::endl;
            //otherwise return no books found
            else
                std::cout << "advisorbot>" << "No products found" << std::endl;
        
}

//moving average function to use it in predicting 


//this method will calculate the moving average (look it up if you dont know it)
//it will take all the prices in a double vector, and checks if it wants to predict the min or max like previously
void MerkelMain::movingAverage(std::vector<std::string>& UserChoice)
{
    //create bool to check if element exists
    bool isProductExist = false;
    // initializing sum of product provided
    double sum = 0;
    //vector to carry prices
    std::vector<double> prices = orderBook.getKnownPrices();
    double max = 0;
    double min = 0;
    for (std::string const& p : orderBook.getKnownProducts())
    {
        if (p == UserChoice[1])
        {
            isProductExist = true;
        }
    }

        //converting num of steps to int
        //double numOfSteps = stod(UserChoice[3]);
     
    if (UserChoice[1] == "min")
    {
        

        //iterate overall products 
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (UserChoice[2] == p)
            {
                //checking if it's ask or bid
                if (UserChoice[3] == "ask")
                {
                    
                    std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask, UserChoice[2], currentTime);
                    min = OrderBook::getLowPrice(entriesAsk);
                }
                else if (UserChoice[3] == "bid")
                {
                    std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid, UserChoice[2], currentTime);
                    min = OrderBook::getLowPrice(entriesBid);
                }
            }
        }
    }

    if (UserChoice[1] == "max")
    {
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (UserChoice[2] == p)
            {
                if (UserChoice[3] == "ask")
                {
                    std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask, UserChoice[2], currentTime);
                    max = OrderBook::getHighPrice(entriesAsk);
                }
                else if (UserChoice[3] == "bid")
                {
                    std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid, UserChoice[2], currentTime);
                    max = OrderBook::getHighPrice(entriesBid);
                }
            }
        }
    }


    double runningTotal = 0;
    double windowSize, predicion;
    //int steps = stoi(UserChoice[3]);
    //windowSize wasn't provided so i assumed it's 10
    if (UserChoice[1] == "max")
    {
        windowSize = max;
       
    }
    else
        windowSize = min;
   
    //method to predict average using moving average based on windowsize and they are not provided
    for (int i = 0; i < 10; i++)
    {
        runningTotal += prices[i];   // add
        if (i >= windowSize)
            runningTotal -= prices[i - windowSize];   // subtract
        if (i >= (windowSize - 1))  // output moving average
        {
            /*std::cout << runningTotal << std::endl;
            std::cout << windowSize << std::endl;*/
            predicion = (runningTotal / (double)windowSize) *100;
        }
    }
    std::cout << "The average " << UserChoice[2] << " " << UserChoice[3] << " price over the last 10 timesteps was " << predicion << std::endl;
}
//this is the method where the logic will set in 
//This takes a vector of strings from above in a vector called UserChoice
//and treat the elements as the command parameters
void MerkelMain::processUserChoice(std::vector<std::string> &UserChoice)
{
    if (UserChoice.empty())
    {
    std::cout << "Cannot enter empty command" << std::endl;
    }
    //if the user only entered help then userChoice size is 1 so we print desc. of help method, other wise 
    if(UserChoice[0] == "./a.")
    {
        printCommandMenu();
        //int  input = getUserOption();
        //processUserOption(input);
    }
    else if (UserChoice.size() == 1 && UserChoice[0] == "help")
    {
        std::cout<<"advisorbot>" << commands["help"] << std::endl;
    }
    //otherwise then we need to print desc. of other command
    else if (UserChoice.size() == 2 && UserChoice[0] == "help")
    {
        std::cout << "advisorbot>" << commands[UserChoice[1]] << std::endl;
    }
   

    else if (UserChoice[0] == "prod")
    {
        //iterate over all products and display them
        for (std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "advisorbot>" << p << std::endl;
        }
    }
    //min command
    else if (UserChoice[0] == "min" && UserChoice.size() == 3)
    {
        //create bool to check if element exists
            bool isProductExist = false;
            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == UserChoice[1])
                {
                    isProductExist = true;
                }
            }
        
            //check first if product exists
            if (isProductExist)
            {
                //iterate overall products 
                for (std::string const& p : orderBook.getKnownProducts())
                {
                    //if p(iterator over all product names) matches with entered userChoice then proceed
                    if (UserChoice[1] == p)
                    {
                        //checking if it's ask or bid
                        if (UserChoice[2] == "ask")
                        {
                            //getting the order with our parameters bid/ask, product type and time
                            std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask, UserChoice[1], currentTime);
                            //using the predefined method getLowPrice gets lowest price in a vector of OBE
                            double min = OrderBook::getLowPrice(entriesAsk);
                            std::cout << "advisorbot>" << "The min " << UserChoice[2] << " for " << p << " is " << min << std::endl;
                        }
                        //otherwise if operation type is bid then repeat the same steps but change enum to bid
                        else if (UserChoice[2] == "bid")
                        {
                            //changing enum in OrderBookType to bid
                            std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid, UserChoice[1], currentTime);
                            double min = OrderBook::getLowPrice(entriesBid);
                            std::cout << "advisorbot>" << "The min " << UserChoice[2] << " for " << p << " is " << min << std::endl;
                        }
                    }
                }
            }
            else
            {
                std::cout << "product doesn't exist" << std::endl;
            }
       
    }
    //max command
    else if (UserChoice[0] == "max" && UserChoice.size() == 3)
    {
        //create bool to check if element exists
        bool isProductExist = false;
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (p == UserChoice[1])
            {
                isProductExist = true;
            }
        }

        //check first if product exists
        if (isProductExist)
        {
        //iterate over all of our products
            for (std::string const& p : orderBook.getKnownProducts())
            {
                //if the product name (UserChoice[1]) matches the product then fetch the max bid/ask
                if (UserChoice[1] == p)
                {
                    if (UserChoice[2] == "ask")
                    {
                        //Getting the orders with our specefied parameters
                        std::vector<OrderBookEntry> entriesAsk = orderBook.getOrders(OrderBookType::ask, UserChoice[1], currentTime);
                        //using predefined method getHighPrice and storing it in max
                        double max = OrderBook::getHighPrice(entriesAsk);
                        std::cout << "advisorbot>" << "The max " << UserChoice[2] << " for " << p << " is " << max << std::endl;
                    }
                    else if (UserChoice[2] == "bid")
                    {
                        //repeating the above steps but changing the enum type to bid
                        std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::bid, UserChoice[1], currentTime);
                        double max = OrderBook::getHighPrice(entriesBid);
                        std::cout << "advisorbot>" << "The max " << UserChoice[2] << " for " << p << " is " << max << std::endl;
                    }
                }
            }
        }
        else
        {
            std::cout << "product doesn't exist" << std::endl;
        }
    }
    //average command
    else if (UserChoice[0] == "avg" && UserChoice.size() == 4)
    {
        //create bool to check if element exists
            bool isProductExist = false;
            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == UserChoice[1])
                {
                    isProductExist = true;
                }
            }
        
            //converting num of steps to int
            double numOfSteps = stod(UserChoice[3]);
            // initializing sum of product provided
            double sum = 0;
        if (isProductExist)
        {
            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == UserChoice[1])
                {
                    if (UserChoice[2] == "ask")
                    {
                        //here we get time using previous timestep in getOrders method
                        std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::ask, UserChoice[1], previousTime);
                        //created avg double to get the returned value from getAvgPrice
                        double avg = OrderBook::getAvgPrice(entriesBid, numOfSteps, OrderBookType::ask);
                        std::cout << "advisorbot>" << "The average  " << UserChoice[1] << " " << UserChoice[2] << " price over the last  " << numOfSteps << " timesteps was " << avg << std::endl;
                    }
                    else if (UserChoice[2] == "bid")
                    {
                        std::vector<OrderBookEntry> entriesBid = orderBook.getOrders(OrderBookType::ask, UserChoice[1], previousTime);
                        double avg = OrderBook::getAvgPrice(entriesBid, numOfSteps, OrderBookType::bid);
                        std::cout << "advisorbot>" << "The average  " << UserChoice[1] << " " << UserChoice[2] << " price over the last  " << numOfSteps << " timesteps was " << avg << std::endl;
                    }
                }
            }
        }
        else
        {
            std::cout << "product doesn't exist" << std::endl;
        }
        
       
    }
    //check above explanation for this method
    else if (UserChoice[0] == "predict")
    {
        MerkelMain::movingAverage(UserChoice);
    }
    else if (UserChoice[0] == "time")
    {
        std::cout << "advisorbot>" << currentTime <<std::endl;
    }
    else if (UserChoice[0] == "step")
    {
        std::cout << "advisorbot>";
            gotoNextTimeframe();
    }
    else if (UserChoice[0] == "count")
    {
        countProductByType(UserChoice[1], UserChoice[2]);
    }
    else
    {
    std::cout << "advisorbot>" << "invalid parameters" << std::endl;
    }

}
