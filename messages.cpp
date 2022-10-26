#include "messages.hpp"
#include <iostream>

std::ostream& bazhin::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

std::ostream& bazhin::printEmpty(std::ostream& out)
{
  return out << "<EMPTY>";
}

std::ostream& bazhin::printInvalidArguments(std::ostream& out)
{
  return out << "<INVALID ARGUMENTS>";
}

std::ostream& bazhin::printAlreadyExists(std::ostream& out)
{
  return out << "<DICTIONARY ALREADY EXISTS>";
}

std::ostream& bazhin::printNotExists(std::ostream& out)
{
  return out << "<DICTIONARY DOES NOT EXIST>";
}

std::ostream& bazhin::printNotEnoughArguments(std::ostream& out)
{
  return out << "<NOT ENOUGH ARGUMENTS>";
}

std::ostream& bazhin::printMissingWord(std::ostream& out)
{
  return out << "< WORD IS MISSING>";
}
