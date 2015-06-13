#ifndef _SPLITCELL_DATGUI_MEMORYFILEREADER_HPP_
#define _SPLITCELL_DATGUI_MEMORYFILEREADER_HPP_

#ifndef _SPLITCELL_DATGUI_MEMORYFILE_HPP_
#include "MemoryFile.hpp"
#endif

#include <string>

namespace splitcell
{
	namespace datgui
	{
		class MemoryFileReader
		{
			private:
				MemoryFile* m_File;
				bool m_IsSystemBigEndian;
				unsigned int m_DataPosition;

			public:
				MemoryFileReader(MemoryFile* file);
				~MemoryFileReader();

				int readInt();
				unsigned int readUnsignedInt();
				float readFloat();
				short readShort();
				unsigned short readUnsignedShort();
				std::string readString();

				void read(int& i)
				{
					i = readInt();
				}
				void read(unsigned int& i)
				{
					i = readUnsignedInt();
				}
				void read(float& i)
				{
					i = readFloat();
				}
				void read(short& i)
				{
					i = readShort();
				}
				void read(unsigned short& i)
				{
					i = readUnsignedShort();
				}
				void read(std::string& i)
				{
					i = readString();
				}

				unsigned int read(unsigned char* bytes, unsigned int length);

		};
	}
}

#endif