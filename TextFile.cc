

#include "TextFile.h"

#include <iostream>
#include <fstream>

const char TextFile::COMMENT = '#';


TextFile::TextFile(const std::string& filename)
{
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open())
  {
    std::cerr << "TextFile: can't open " << filename << std::endl;
    return;
  }

  while ( getline(file, line) )
  {
    if (line[0] == COMMENT || line.size() == 0)
      continue;

    _lines.push_back(line);
  }

  file.close();
}
