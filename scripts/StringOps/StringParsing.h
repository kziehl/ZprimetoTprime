#ifndef TOOLS_STRINGOPS_STRING_PARSING_H
#define TOOLS_STRINGOPS_STRING_PARSING_H

#include <string>
#include <vector>

#include "TString.h"


class StringParsing {
public:
  static std::vector<TString> split(const TString& str, const TString& delim);
  static std::vector<std::string> split(const std::string& str, const std::string& delim);
  static bool split(const TString& str, const TString& delim, TString& first, TString& second);
  static bool split(const std::string& str, const std::string& delim, std::string& first, std::string& second);
  static void trim(std::string& str);
};


// ----------------------------------------------------------------------------
std::vector<TString> StringParsing::split(const TString& str, const TString& delim) {
  std::vector<TString> parts;
  TString rest = str;
  TString part1 = "";
  TString part2 = "";
  while( split(rest,delim,part1,part2) ) {
    parts.push_back(part1);
    rest = part2;
  }
  parts.push_back(rest);
 
  return parts;
}
 
 
// ----------------------------------------------------------------------------
std::vector<std::string> StringParsing::split(const std::string& str, const std::string& delim) {
  std::vector<std::string> parts;
  std::vector<TString> partsTmp = split(TString(str.c_str()),TString(delim.c_str()));
  for(auto& part: partsTmp) { 
    parts.push_back(std::string(part.Data()));
  }
  
  return parts;
}


// ----------------------------------------------------------------------------
bool StringParsing::split(const TString& str, const TString& delim, TString& first, TString& second) {
  std::string strt(str.Data());
  std::string delimt(delim.Data());
  std::string firstt(first.Data());
  std::string secondt(second.Data());
  bool result = split(strt,delimt,firstt,secondt);
  first = firstt.c_str();
  second = secondt.c_str();
 
  return result;
}
 
 
// ----------------------------------------------------------------------------
bool StringParsing::split(const std::string& str, const std::string& delim, std::string& first, std::string& second) {
  bool hasDelim = false;
  first = str;
  second = "";
  if( str.find(delim) != std::string::npos ) {
    hasDelim = true;
    size_t end = str.find(delim);
    first = str.substr(0,end);
    second = str.substr(end+delim.size(),str.size());
  }
  trim(first);
  trim(second);
 
  return hasDelim;
}

 
// ----------------------------------------------------------------------------
void StringParsing::trim(std::string& str) {
  while( str.size() && str[0] == ' ' ) str.erase(0,1);
  while( str.size() && str[str.size()-1] == ' ' ) str.erase(str.size()-1,str.size());    
}
 

#endif
