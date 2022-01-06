#include <cassert>
#include <cstdint>
#include <fstream>
#include <type_traits>
#include <tsl/htrie_map.h>

namespace sequence_seeker
{
    class Deserializer {
    public:
        Deserializer(const char* file_name)
        {
            m_istream.exceptions(m_istream.badbit | m_istream.failbit | m_istream.eofbit);
            m_istream.open(file_name);
        }

        template<class T,
                 typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
        T operator()()
        {
            T value;
            m_istream.read(reinterpret_cast<char*>(&value), sizeof(T));

            return value;
        }

        void operator()(char* value_out, std::size_t value_size)
        {
            m_istream.read(value_out, value_size);
        }

    private:
        std::ifstream m_istream;
    };
}
