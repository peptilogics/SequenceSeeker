// https://github.com/Tessil/hat-trie
#include <tsl/htrie_set.h>

#include <string>
#include <memory>
#include <iostream>

namespace sequence_seeker
{
    class SequenceLookup
    {
    public:
        SequenceLookup(const std::string& triePath);
        ~SequenceLookup();

        SequenceLookup(const SequenceLookup&) = delete;
        SequenceLookup& operator=(const SequenceLookup&) = delete;

        void deserialize();
        void processLookupList(const std::string& sequenceFilePath, std::ostream* outStreamPtr);
        void runInteractive();
        inline bool isSequencePresent(const std::string& sequence)
        {
            return this->m_htrie_ptr->find(sequence) != this->m_htrie_ptr->end();
        }

    private:
        std::string m_trie_path;
        std::shared_ptr< tsl::htrie_set< char > > m_htrie_ptr;
    };
}
