#pragma once

#include <string>
#include <vector>
#include <memory>

// https://github.com/Tessil/hat-trie
#include <tsl/htrie_set.h>

namespace sequence_seeker
{
    class FastaConverter
    {
    public:
        FastaConverter(const std::string& dbOutfilePath);
        ~FastaConverter();
        FastaConverter(const FastaConverter& fastaConverter) = delete;
        FastaConverter& operator=(const FastaConverter& fastaConverter) = delete;

        void addFastaPath(const std::string& path);
        void generateSequenceLookupFile();

    private:
        std::string m_db_outfile_path;
        std::vector< std::string > m_fasta_paths;
        std::shared_ptr< tsl::htrie_set< char > > m_htrie_ptr;
    };
}
