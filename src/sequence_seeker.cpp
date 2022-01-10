#include "FastaConverter.h"
#include "Deserializer.hpp"

#include <tsl/htrie_set.h>
#include "SequenceLookup.h"

#include <cxxopts.hpp>

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    cxxopts::Options options("SequenceSeeker", "A sequence storage and lookup tool");
    options.add_options()
        ("h,help", "Print usage")
        ("d,db_path", "The path to the database file [REQUIRED]", cxxopts::value< std::string >())
        ("r,results_path", "The output path of the sequence match results. If a path is not provided than the output is printed to standard out.", cxxopts::value< std::string >())
        ("s,sequence_path", "The path to the file containing sequences to match", cxxopts::value< std::string >())
        ("i,interactive", "Run the session as interactive", cxxopts::value< bool >())
        ;
    auto cmdOptions = options.parse(argc, argv);
    std::vector< std::string > errorMessages;
    if (cmdOptions.count("db_path") == 0)
    {
        errorMessages.emplace_back("You must provide a path to the db file (db_path)");
    }
    if (!cmdOptions["interactive"].as< bool >() && cmdOptions.count("sequence_path") == 0)
    {
        errorMessages.emplace_back("You must either specify a sequence_path or indicate an interactive_session");
    }

    if (cmdOptions.count("help") || errorMessages.size() > 0)
    {
        for (auto errorMessage : errorMessages)
        {
            std::cout << errorMessage << std::endl;
        }
        std::cout << options.help() << std::endl;
        return 0;
    }
    sequence_seeker::SequenceLookup sequenceLookup(cmdOptions["db_path"].as< std::string >());
    sequenceLookup.deserialize();
    if (cmdOptions["interactive"].as< bool >())
    {
        sequenceLookup.runInteractive();
    }
    else
    {

        std::ostream* outStream;
        if (cmdOptions.count("results_path") > 0)
        {
            outStream = new std::ofstream();
            ((std::ofstream*)outStream)->open(cmdOptions["results_path"].as< std::string >().c_str());
        }
        else
        {
            outStream = &std::cout;
        }
        sequenceLookup.processLookupList(cmdOptions["sequence_path"].as< std::string >(), outStream);
        if (cmdOptions.count("results_path") > 0)
        {
            ((std::ofstream*)outStream)->close();
            delete outStream;
        }
    }
    return 0;
}
