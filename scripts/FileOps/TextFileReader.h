#ifndef TOOLS_FILEOPS_TEXT_FILE_READER_H
#define TOOLS_FILEOPS_TEXT_FILE_READER_H

#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include <TString.h>

#include "Tools/StringOps/StringParsing.h"


class TextFileReader {
  static std::vector<TString> readColumn(const TString& fileName, const TString& delim, const unsigned int col);
};


std::vector<TString> TextFileReader::readColumn(const TString& fileName, const TString& delim, const unsigned int col) {
  std::vector<TString> result;

  // Open file for reading
  std::ifstream file(fileName.Data());
  if( !file.is_open() ) {
    std::cerr << "\n\nERROR opening file '" << fileName << "'\n";
    throw std::exception();
  }

  // Loop over lines and parse
  unsigned int lineNum = 0;
  std::string line = "";
  while( !file.eof() ) {
    ++lineNum;
    std::getline(file,line);
    if( line.size() ) {		// only parse non-empty lines
      const TString tmp(line.c_str());
      std::vector<TString> cols = StringParsing::split(tmp,delim);
      if( col >= cols.size() ) {
	std::cerr << "\n\nERROR reading column " << col << " from file '" << fileName << "':" << std::endl;
	std::cerr << "Too few columns in file" << std::endl;
	throw std::exception();
      }
      result.push_back(cols.at(col));
    } // end: non-empty line
  } // end of loop over lines

  file.close();

  return result;
}

#endif
