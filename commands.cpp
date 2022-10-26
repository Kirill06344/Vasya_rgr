#include "commands.hpp"
#include <iostream>
#include "messages.hpp"

bazhin::Commands::Commands(std::istream& in, std::ostream& out, bazhin::dictionaries& dicts):
  in_(in),
  out_(out),
  dicts_(dicts)
{}

bazhin::dictionary bazhin::Commands::createCommonDictionary()
{
  dictionary tmp;
  for (auto& dict: dicts_) {
    for (auto& i: dict.second) {
      auto find = tmp.find(i.first);
      if (tmp.empty() || find == tmp.end()) {
        tmp.emplace(i.first, i.second);
      } else {
        find->second += i.second;
      }
    }
  }
  return tmp;
}

void bazhin::Commands::createDictionary()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_);
    in_.clear();
    return;
  }
  auto it = dicts_.find(name);
  if (it != dicts_.end()) {
    bazhin::printAlreadyExists(out_);
  } else {
    dictionary dict;
    dicts_.insert(std::make_pair(name, dict));
  }
}

void bazhin::Commands::deleteDictionary()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_);
    in_.clear();
    return;
  }
  auto it = dicts_.find(name);
  if (it == dicts_.end()) {
    bazhin::printNotExists(out_) << "\n";
  } else {
    dicts_.erase(it);
  }
}

void bazhin::Commands::printDictionary()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }
  auto it = dicts_.find(name);
  if (it == dicts_.end()) {
    bazhin::printNotExists(out_) << "\n";
  } else {
    auto& words = it->second;
    if (words.empty()) {
      bazhin::printEmpty(out_) << "\n";
      return;
    }
    for (auto& item: words) {
      out_ << item.first << " " << item.second << "\n";
    }
  }
}

void bazhin::Commands::searchWordInDictionary()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  if (in_.peek() == '\n') {
    bazhin::printNotEnoughArguments(out_) << "\n";
    return;
  }

  std::string word;
  in_ >> word;

  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  auto it = dicts_.find(name);
  if (it == dicts_.end()) {
    bazhin::printNotExists(out_) << "\n";
  } else {
    auto& words = it->second;
    if (words.empty()) {
      bazhin::printEmpty(out_) << "\n";
      return;
    }
    auto needWord = words.find(word);
    if (needWord == words.end()) {
      bazhin::printMissingWord(out_) << "\n";
    } else {
      out_ << needWord->first << " " << needWord->second << "\n";
    }
  }
}

void bazhin::Commands::deleteWordInDictionary()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  if (in_.peek() == '\n') {
    bazhin::printNotEnoughArguments(out_) << "\n";
    return;
  }

  std::string word;
  in_ >> word;

  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  auto it = dicts_.find(name);
  if (it == dicts_.end()) {
    bazhin::printNotExists(out_) << "\n";
  } else {
    auto& words = it->second;
    if (words.empty()) {
      bazhin::printEmpty(out_) << "\n";
      return;
    }
    auto needWord = words.find(word);
    if (needWord != words.end()) {
      words.erase(needWord);
    }
  }
}

void bazhin::Commands::deleteWordInAllDictionaries()
{
  std::string word = "";
  in_ >> word;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }
  for (auto& dict: dicts_) {
    dict.second.erase(word);
  }
}

void bazhin::Commands::printAllWords()
{
  dictionary tmp = createCommonDictionary();
  if (tmp.empty()) {
    bazhin::printEmpty(out_) << "\n";
  }

  for (auto& it: tmp) {
    out_ << it.first << " " << it.second << "\n";
  }
}

void bazhin::Commands::addWordsFromText()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }
  auto it = dicts_.find(name);
  std::string word = "";
  if (it != dicts_.end()) {
    while (in_.peek() != '\n') {
      in_ >> word;
      bazhin::addWordAtDictionary(word, it->second);
    }
  } else {
    bazhin::printNotExists(out_) << "\n";
  }

}

void bazhin::Commands::printPeriodOfWord()
{
  std::string word;
  in_ >> word;

  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  int counter = 0;
  for (auto& dict: dicts_) {
    auto it = dict.second.find(word);
    if (it != dict.second.end()) {
      counter += it->second;
    }
  }

  out_ << "Period of word " << word << " is : " << counter << "\n";
}

void bazhin::Commands::insertWord()
{
  std::string name = "";
  in_ >> name;
  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  if (in_.peek() == '\n') {
    bazhin::printNotEnoughArguments(out_) << "\n";
    return;
  }

  std::string word;
  in_ >> word;

  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  if (in_.peek() == '\n') {
    bazhin::printNotEnoughArguments(out_) << "\n";
    return;
  }

  int period;
  in_ >> period;

  if (!in_ && !in_.eof()) {
    bazhin::printInvalidArguments(out_) << "\n";
    in_.clear();
    return;
  }

  auto dict = dicts_.find(name);
  if (dict == dicts_.end()) {
    bazhin::printNotExists(out_) << "\n";
  } else {
    auto find = dict->second.find(word);
    if (find == dict->second.end()) {
      dict->second.emplace(word, period);
    } else {
      find->second += period;
    }
  }
}

void bazhin::Commands::printMainWords()
{
  dictionary tmp = createCommonDictionary();
  dictionary top;
  for (auto& i: tmp) {
    if (top.size() < 3) {
      top.emplace(i.first, i.second);
    } else {
      std::string minKey = top.begin()->first;
      int minValue = top.begin()->second;
      for (auto& el: top) {
        if (el.second < minValue) {
          minKey = el.first;
          minValue = el.second;
        }
      }
      if (minValue < i.second) {
        top.erase(minKey);
        top.emplace(i.first, i.second);
      }
    }
  }

  if (top.empty()) {
    bazhin::printEmpty(out_) << "\n";
  } else {
    for (auto& el: top) {
      out_ << el.first << " " << el.second << "\n";
    }
  }
}
