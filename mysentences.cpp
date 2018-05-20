#include "mysentences.h"

MySentences::MySentences(int sn): SENTENCES_NUMBER(sn)
{

}

MySentences::MySentences(const MySentences& inpSentences): SENTENCES_NUMBER(inpSentences.SENTENCES_NUMBER){
    std::vector<int> v = inpSentences.getWords();

    words.insert(words.end(), v.begin(), v.end());
}

MySentences& MySentences::operator =(const MySentences& inpSentences): SENTENCES_NUMBER(inpSentences.SENTENCES_NUMBER){
    std::vector<int> v = inpSentences.getWords();

    words.insert(words.end(), v.begin(), v.end());
}

void MySentences::addWord(int w){
    words.push_back(w);
}

std::vector<int> MySentences::getWords(){
    return words;
}
