#ifndef READING_HPP
#define READING_HPP

#include <map>

namespace bazhin {
  using dictionary = std::map< std::string, int >;

  dictionary readDictionary(std::istream& file);
  void addWordAtDictionary(std::string& word, dictionary& dict);
}

#endif
