#include <cassert>
#include <cstdint>
#include <fstream>
#include <type_traits>
#include <tsl/htrie_map.h>

namespace sequence_seeker
{
    class Serializer {
    public:
        Serializer(const char* file_name)
        {
            m_ostream.exceptions(m_ostream.badbit | m_ostream.failbit);
            m_ostream.open(file_name);
        }

        template<class T,
                 typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
        void operator()(const T& value)
        {
            m_ostream.write(reinterpret_cast<const char*>(&value), sizeof(T));
        }

        void operator()(const char* value, std::size_t value_size)
        {
            m_ostream.write(value, value_size);
        }

    private:
        std::ofstream m_ostream;
    };
}
