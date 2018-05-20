#ifndef MYSENTENCES_H
#define MYSENTENCES_H

#include<vector>

class MySentences
{
public:
    const int SENTENCES_NUMBER;

    MySentences(int);
    MySentences(const MySentences&);
    MySentences& operator =(const MySentences&);
    void addWord(int);
    std::vector<int> getWords();


private:
    std::vector<int> words;
};

#endif // MYSENTENCES_H
