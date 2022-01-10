#include "SequenceLookup.h"
#include "Deserializer.hpp"

#include <utility>
#include <fstream>
#include <iostream>

namespace sequence_seeker
{
    SequenceLookup::SequenceLookup(const std::string& triePath) :
        m_trie_path(triePath), m_htrie_ptr(nullptr)
    {
    }

    SequenceLookup::~SequenceLookup()
    {
    }

    void SequenceLookup::deserialize()
    {
        sequence_seeker::Deserializer ds(this->m_trie_path.c_str());
        this->m_htrie_ptr = std::make_shared< tsl::htrie_set< char > >(tsl::htrie_set< char >::deserialize(ds, true));
    }

    void SequenceLookup::processLookupList(const std::string& sequenceFilePath, std::ostream* outStreamPtr)
    {
        if (this->m_htrie_ptr == nullptr)
        {
            deserialize();
        }
        std::ifstream inFile;
        inFile.open(sequenceFilePath);
        // std::ofstream outFile;
        // outFile.open(outputFilePath.c_str());
        std::string sequence = "";
        while (std::getline(inFile, sequence))
        {
            uint32_t eval = isSequencePresent(sequence) ? 1 : 0;
            (*outStreamPtr) << eval << std::endl;
        }
        inFile.close();
    }

    void SequenceLookup::runInteractive()
    {

        std::cout << "You are running an interactive sequence lookup session." << std::endl;
        std::cout << "Each time you enter a sequence and press enter the output will be a 1 if the sequence is present or a 0 if the sequence is not present." << std::endl;
        std::cout << "To exit type 'exit' (without quotes)." << std::endl;
        std::string sequence = "";
        while (true)
        {
            std::cout << "Please enter a sequence:" << std::endl;
            getline(std::cin, sequence);
            if (sequence.compare("exit") == 0) { break; }
            uint32_t result = isSequencePresent(sequence) ? 1 : 0;
            std::cout << result << std::endl;
        }
    }
}
