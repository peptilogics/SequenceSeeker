#pragma once

#include <string>
#include <vector>

// https://github.com/Tessil/hat-trie
#include <tsl/htrie_set.h>

namespace sequence_seeker
{
    class FastaConverter
    {
    public:
        FastaConverter(const std::string& dbOutfilePath);
        FastaConverter(const FastaConverter& fastaConverter) = delete;
        FastaConverter& operator=(const FastaConverter& fastaConverter) = delete;
        ~FastaConverter();

        void addFastaPath(const std::string& path);
        void generateSequenceLookupFile();

    private:
        std::string m_db_outfile_path;
        std::vector< std::string > m_fasta_paths;
        tsl::htrie_set< char > m_htrie;
    };
}
