#ifndef TOOLS_STRINGOPS_STRING_CONVERSION_H
#define TOOLS_STRINGOPS_STRING_CONVERSION_H

#include <exception>
#include <iostream>
#include <vector>

#include "TString.h"


class StringConversion {
public:
  static double toDouble(const TString& str);
  static std::vector<double> toDoubles(const std::vector<TString>& strs);

private:
  class Value {
  public:
    Value();
    Value(const TString &value);

    TString value() const { return value_; }
    bool isBoolean() const { return isBoolean_; }
    bool valueBoolean() const { return valueBoolean_; }
    bool isInteger() const { return isInteger_; }
    int valueInteger() const { return isInteger() ? value_.Atoi() : 999999; }
    bool isDouble() const { return isDouble_; }
    double valueDouble() const { return isDouble() ? value_.Atof() : 999999.; }
    
  private:
    TString value_;
    bool isBoolean_;
    bool valueBoolean_;
    bool isInteger_;
    bool isDouble_;
  };
};


double StringConversion::toDouble(const TString& str) {
  Value val(str);
  if( !val.isDouble() ) {
    std::cerr << "\n\nERROR when converting string to double:" << std::endl;
    std::cerr << "'" << str << "' is not a double" << std::endl;
    throw exception();
  }

  return val.valueDouble();  
}


std::vector<double> StringConversion::toDoubles(const std::vector<TString>& strs) {
  std::vector<double> result;
  for(auto& str: strs) {
    result.push_back(toDouble(str));
  }

  return result;
}


StringConversion::Value::Value()
  : value_(""), isBoolean_(false), valueBoolean_(false), isInteger_(false), isDouble_(false) {};


StringConversion::Value::Value(const TString &value)
  : value_(value), isBoolean_(false), valueBoolean_(false), isInteger_(false), isDouble_(false) {
  
  if( value_.IsAlpha() ) {	// first check if this is a boolean
    TString low = value_;
    low.ToLower();
    if( low == "true" || low == "ktrue" ) {
      isBoolean_ = true;
      valueBoolean_ = true;
    } else if( low == "false" || low == "kfalse" ) {
      isBoolean_ = true;
      valueBoolean_ = false;      
    }
  } else if( !isBoolean_ ) {	// if this is not a boolean, parse for number
    if( value_.IsDigit() ) {
      isInteger_ = true;
    } else if( value_.IsFloat() ) {
      isDouble_ = true;
    }
  }
}

#endif
