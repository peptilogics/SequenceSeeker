#include "FastaConverter.h"
#include "Deserializer.hpp"

#include <tsl/htrie_set.h>

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    std::cout << "starting" << std::endl;
    /*
    sequence_seeker::FastaConverter fc("data/large_serialized_set.dat");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniparc_active.fasta.gz");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniprot_sprot.fasta.gz");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniprot_sprot_varsplic.fasta.gz");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniprot_trembl.fasta.gz");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniref100.fasta.gz");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniref50.fasta.gz");
    fc.addFastaPath("/nexus/data/DataHub/prod/dc/uniprot/latest/uniref90.fasta.gz");
    fc.generateSequenceLookupFile();
    */
    sequence_seeker::Deserializer ds("data/large_serialized_set.dat");
    auto htrie = tsl::htrie_set< char >::deserialize(ds, true);
    /*
    htrie.max_load_factor(1.0);
    std::cout << htrie.size() << " sequences have been loaded" << std::endl;
    std::string input = "";
    do
    {
        std::cout << "Please enter a sequence" << std::endl;
        std::getline(std::cin, input);
        if (input.compare("exit") == 0) { break; }
        bool isFound = htrie.find(input) != htrie.end();
        std::string statement = (isFound) ? " has " : " has not ";
        std::cout << "Sequence: " << input << statement << "been found." << std::endl;
    } while (true);
    */
    return 0;
}
