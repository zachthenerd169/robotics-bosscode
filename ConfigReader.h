#ifndef ConfigReader_h
#define ConfigReader_h

#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#define DEBUG 1
#if DEBUG
# define DEBUG_PRINT(x) std::cout<<x;
#else
# define DEBUG_PRINT(x)
#endif

class ConfigReader
{
public:
  ConfigReader()
  {}

  ConfigReader(std::string file_path)
  {
    std::string key, value, sep;

    std::ifstream file(file_path);
    if(!file.good())
    {
      std::cout << "Error Reading Config File \"" << file_path << "\"" << std::endl;
      exit(1);
    }
    
    std::string line_string;

    while(std::getline(file, line_string))
    {
      std::size_t ifirst = line_string.find_first_not_of(' ');
      if((ifirst != std::string::npos) && (line_string[ifirst] != '#'))
      {
        std::istringstream line_stream(line_string);
        if((line_stream >> key) && (line_stream >> sep) && (sep == "=") && (line_stream >> value))
        {
          DEBUG_PRINT("ConfigReader: key=" << key << " value=" << value << std::endl);
          m_map.emplace(key,value);
        }
        else
        {
          std::cout << "Error Parsing Config File On Line \"" << line_string << "\"" << std::endl;
          exit(1);
        }
      }
    }
  }

  bool has(std::string key)
  {
    return m_map.count(key) > 0;
  }

  std::string get(std::string key)
  {
    if(has(key))
    {
      return m_map[key];
    }
    else
    {
      return std::string("");
    }
  }
private:
  std::map<std::string, std::string> m_map;
};

#endif //ConfigReader_h
