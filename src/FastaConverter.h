#pragma once

namespace sequence_seeker
{
    class FastaConverter
    {
    public:
        FastaConverter();
        FastaConverter(const FastaConverter& fastaConverter) = delete;
        FastaConverter& operator=(const FastaConverter& fastaConverter) = delete;
    };
}
