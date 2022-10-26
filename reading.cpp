#include "reading.hpp"
#include <iostream>
#include <algorithm>

namespace {

  void removePunctuationMarks(std::string& str)
  {
    if (!std::isalpha(str.front())) {
      str.erase(str.begin());
    }
    if (!std::isalpha(str.back())) {
      str.erase(str.end() - 1);
    }
  }
}

std::map< std::string, int > bazhin::readDictionary(std::istream& file)
{
  std::map< std::string, int > dictionary;
  std::string str = "";
  while (file >> str) {
    addWordAtDictionary(str, dictionary);
  }
  return dictionary;
}

void bazhin::addWordAtDictionary(std::string& str, bazhin::dictionary& dict)
{
  removePunctuationMarks(str);
  bool isOnlyLetters = true;
  for (char i: str) {
    if (!std::isalpha(i)) {
      isOnlyLetters = false;
      break;
    }
  }
  if (isOnlyLetters) {
    std::transform(str.begin(), str.end(), str.begin(), tolower);
    if (dict.find(str) != dict.end()) {
      ++dict.at(str);
    } else {
      dict.insert(std::make_pair(str, 1));
    }
  }
}
