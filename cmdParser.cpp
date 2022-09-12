#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "cmdParser.h"

//string parser
std::vector<std::string> cmdParser::parse(std::string input, char seperator)
{
   std::vector<std::string> cmdoutput;

signed int start, end;
std::string command;

start = input.find_first_not_of(seperator,0);

do{
end = input.find_first_of(seperator,start);

if(start== input.length() || start==end) break;

if(end>=0) command = input.substr(start,end - start);

else command = input.substr(start, input.length() - start);

cmdoutput.push_back(command);

start = end+1;

} while(end >0);
   return cmdoutput;
}