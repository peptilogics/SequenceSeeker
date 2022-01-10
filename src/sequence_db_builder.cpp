#include "FastaConverter.h"
#include "Deserializer.hpp"

#include <tsl/htrie_set.h>
#include <cxxopts.hpp>

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    cxxopts::Options options("SequenceDBBuilder", "A tool to build and store a database of sequences");
    options.add_options()
        ("h,help", "Print usage")
        ("f,fasta_files", "Either a single or comma separated list of paths to fasta files on which to build a database file", cxxopts::value< std::vector< std::string > >())
        ("d,db_path", "The path to the database file", cxxopts::value< std::string >())
        ;
    auto cmdOptions = options.parse(argc, argv);
    std::vector< std::string > errorMessages;
    if (cmdOptions.count("db_path") == 0)
    {
        errorMessages.emplace_back("You must provide a path to the db file (db_path)");
    }
    if (cmdOptions.count("fasta_files") == 0)
    {
        errorMessages.emplace_back("You must provide a path to one or more fasta files (comma separated)");
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
    sequence_seeker::FastaConverter fc(cmdOptions["db_path"].as< std::string >());
    for (auto fastaPath : cmdOptions["fasta_files"].as< std::vector< std::string > >())
    {
        fc.addFastaPath(fastaPath);
    }
    fc.generateSequenceLookupFile();

    return 0;
}
