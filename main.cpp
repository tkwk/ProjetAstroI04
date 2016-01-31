#include <iostream>
#include "ParserAstro.hpp"
#include "Simulator.hpp"

using namespace std;

int main(int argc, char * argv[]) {
    ParserAstro parser(argv);
    if(!parser.check())
        return 0;
    std::string input = "";
    if(parser.isPresent("i"))
        input = parser["i"][0];
    std::string parametres = parser["p"][0];
    std::string output = "output";
    std::string outputMovie = "movie";
    Simulator simulator(input, parametres, output, outputMovie, true);
    Simulator::handleInterruptions();
    simulator.start();
    return 0;
}
