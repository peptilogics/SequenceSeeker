#include "FastaConverter.h"
#include "gzstream.h"
#include "Serializer.hpp"

#include <algorithm>
#include <istream>
#include <memory>

namespace sequence_seeker
{
    FastaConverter::FastaConverter(const std::string& dbOutfilePath) :
        m_db_outfile_path(dbOutfilePath)
    {
    }

    FastaConverter::~FastaConverter()
    {
    }

    void FastaConverter::addFastaPath(const std::string& path)
    {
        // add the path if it's not already in the list
        if (std::find(this->m_fasta_paths.begin(), this->m_fasta_paths.end(), path) == this->m_fasta_paths.end())
        {
            this->m_fasta_paths.push_back(path);
        }
    }

    void FastaConverter::generateSequenceLookupFile()
    {
        for (std::string path : this->m_fasta_paths)
        {
            std::shared_ptr< igzstream > fPtr;
            if (path.substr(path.find_last_of(".") + 1) == "gz")
            {
                fPtr = std::make_shared< igzstream >();
                fPtr->open(path.c_str());
            }
            else
            {
                std::cout << "skipping non-gz files" << std::endl;
                // fPtr = std::make_shared< std::ifstream >(path, std::fstream::in);
                continue;
            }
            this->m_htrie.max_load_factor(5.0);
            std::string line;
            std::string currentSequence = "";
            std::getline(*fPtr, line); // skip first line because it's just a header
            size_t maxSize = (size_t)this->m_htrie.max_key_size();
            while (std::getline(*fPtr, line))
            {
                if (line.size() > 0 && line.c_str()[0] == '>')
                {
                    if (currentSequence.size() < maxSize)
                    {
                        this->m_htrie.insert(currentSequence);
                    }
                    currentSequence = "";
                    continue;
                }
                currentSequence += line;
            }
            Serializer serial(this->m_db_outfile_path.c_str());
            this->m_htrie.serialize(serial);
            fPtr->close();
        }
        std::cout << "There are " << this->m_htrie.size() << " sequences stored" << std::endl;
    }
}
