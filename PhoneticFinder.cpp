//
// Created by owner on 3/26/2020.
//

#include "PhoneticFinder.hpp"
#include <iostream>
#include <list>
#include <algorithm>
//#include <stdexcept>


namespace phonetic {
    std::string find(std::string text, std::string word) {
        std::list<std::string> words;
        std::list<std::string> lcText;
        std::string lcWord;
        trim(word);      //trim spaces from searched word
        if (word.empty()) throw MyException();
        for(char c : word)
            if (c == ' ') throw MyException();
        words = split(text, word.length()); //split text to spaces
        if (words.empty()) throw MyException(word);
        for (std::string perfectMatch : words) {
            if (check(word, perfectMatch) == true)
                return perfectMatch;
        }
        lcWord = toLower(word);
        for (std::string orig : words) {    //convert to lower case, and compare
            std::string lc = toLower(orig);
            if (cycle(lcWord, lc)) return orig; //use phonetic rules, try to cycle between chars
        }

        throw MyException(word);

    }
    std::string & trim(std::string & str)   //code for trim functions taken from here: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string/1798170
    {
        return ltrim(rtrim(str));
    }
    std::string & ltrim(std::string & str)
    {
        auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
        str.erase( str.begin() , it2);
        return str;
    }

    std::string & rtrim(std::string & str)
    {
        auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
        str.erase( it1.base() , str.end() );
        return str;
    }

    std::string trim_copy(std::string const & str)
    {
        auto s = str;
        return ltrim(rtrim(s));
    }
    std::list<std::string> split(std::string text, int size) {
        std::list<std::string> res;
        int begin = 0;
        int i;
        while (text.at(begin) == ' ')  //find where first word begins
            ++begin;
        for (i = begin; i < text.length(); ++i) {  //check for spaces
            if (text.at(i) == ' ') {
                if ((i - begin) == (size))  //word of same size, add to check list
                    res.push_back(text.substr(begin, size));
                begin = i + 1;
            }
        }
        if (begin <= i && (i - begin) == (size))   //add last word
            res.push_back(text.substr(begin, i));
        return res;

    }

    bool check(std::string word, std::string test) {
        if (word.compare(test) == 0) return true;
        else return false;
    }

    std::string toLower(std::string word) {
        std::string res;
        for (char c : word) {
            if (c >= 'A' && c <= 'Z')
                res += (c + 'a' - 'A');
            else
                res += c;
        }
        return res;
    }

    bool cycle(std::string word, std::string test) {
        std::string res;
        bool ded = false;   //flag, if a char cannot be fixed, stop checking
        for (int i = 0; i < test.length() && ded == false; ++i) {
            char c = test.at(i);
            if (c != word.at(i)) {
                if (c == 'v' || c == 'w') {
                    if (word.at(i) == 'w')
                        res += 'w';
                    else if (word.at(i) == 'v')
                        res += 'v';
                    else
                        ded = true;
                } else if (c == 'b' || c == 'f' || c == 'p') {
                    if (word.at(i) == 'b')
                        res += 'b';
                    else if (word.at(i) == 'f')
                        res += 'f';
                    else if (word.at(i) == 'p')
                        res += 'p';
                    else
                        ded = true;
                } else if (c == 'g' || c == 'j') {
                    if (word.at(i) == 'g')
                        res += 'g';
                    else if (word.at(i) == 'j')
                        res += 'j';
                    else ded = true;
                } else if (c == 'c' || c == 'k' || c == 'q') {
                    if (word.at(i) == 'c')
                        res += 'c';
                    else if (word.at(i) == 'k')
                        res += 'k';
                    else if (word.at(i) == 'q')
                        res += 'q';
                    else ded = true;
                } else if (c == 's' || c == 'z') {
                    if (word.at(i) == 's')
                        res += 's';
                    else if (word.at(i) == 'z')
                        res += 'z';
                    else ded = true;
                } else if (c == 'd' || c == 't') {
                    if (word.at(i) == 'd')
                        res += 'd';
                    else if (word.at(i) == 't')
                        res += 't';
                    else ded = true;
                } else if (c == 'o' || c == 'u') {
                    if (word.at(i) == 'o')
                        res += 'o';
                    else if (word.at(i) == 'u')
                        res += 'u';
                    else ded = true;
                } else if (c == 'i' || c == 'y') {
                    if (word.at(i) == 'i')
                        res += 'i';
                    else if (word.at(i) == 'y')
                        res += 'y';
                    else ded = true;
                } else ded = true;

            } else res += word.at(i);
        }
        if (!ded)
            return check(word, res);
        else return !ded;
    }
}

