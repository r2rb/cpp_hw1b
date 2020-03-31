//
// Created by owner on 3/26/2020.
//

#pragma once
#include <string>
#include <list>
namespace phonetic {
    std::string find(std::string text, std::string word);
    std::list<std::string> split(std::string text,int size);
    bool check(std::string word,std::string test);
    std::string toLower(std::string word);
    bool cycle(std::string word,std::string test);
    std::string & ltrim(std::string & str);
    std::string & rtrim(std::string & str);
    std::string & trim(std::string & str);
    std::string trim_copy(std::string const & str);
    struct MyException : public std::exception {    //used code for exception: https://stackoverflow.com/questions/23742448/c-how-to-pass-parameters-to-custom-exceptions
        std::string x;
        MyException(const std::string &word)
        : x(std::string("Did not find the word '"+word+"' in the text") ){}
        MyException(): x(std::string("")){}
        const char * what () const throw () {
            if (x.empty()) return "Illegal word";
            else return x.c_str();
        }
    };
}



