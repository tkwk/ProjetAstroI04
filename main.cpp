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
    if(parser.isPresent("o"))
        output = parser["o"][0];
    std::string outputMovie = "";
    if(parser.isPresent("m"))
        outputMovie = parser["m"][0];
    Simulator simulator(input, parametres, output, outputMovie, true);
    Simulator::handleInterruptions();
    simulator.start();
    return 0;
}
