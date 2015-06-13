#ifndef _SPLITCELL_DATGUI_MEMORYFILE_HPP_
#define _SPLITCELL_DATGUI_MEMORYFILE_HPP_

namespace splitcell
{
    namespace datgui
    {
        class MemoryFile
        {
            const char* m_Name;
            unsigned char* m_Data;
            unsigned int m_Length;

            public:
                MemoryFile(const char* name, unsigned char* data, unsigned int length) : m_Name(name), m_Data(data), m_Length(length)
                {

                }

                unsigned char* bytes() { return m_Data; }
                unsigned int size() { return m_Length; }
                const char* name() { return m_Name; }
        };
    }
}

#endif