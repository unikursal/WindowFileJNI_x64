#include "myword.h"

MyWord::MyWord(){}

MyWord::MyWord(QString str, std::vector<int> inputVec, std::vector<int> nSent)
{
    words = str.split("+");

    references.insert(references.end(), inputVec.begin(), inputVec.end());
    numbSentences.insert(numbSentences.end(), nSent.begin(), nSent.end());
}

MyWord::MyWord(const MyWord& obj){
    words = QStringList(obj.getWords());

    std::vector<int> ref = obj.getReferences();
    std::vector<double> w = obj.getWeights();
    std::vector<int> ns = obj.getNSentences();

    references.insert(references.end(), std::begin(ref), std::end(ref));
    weights.insert(std::end(weights), std::begin(w), std::end(w));
    numbSentences.insert(numbSentences.end(), std::begin(ns), std::end(ns));
}

MyWord& MyWord::operator=(const MyWord& obj){
    words = QStringList(obj.getWords());

    std::vector<int> ref = obj.getReferences();
    std::vector<double> w = obj.getWeights();
    std::vector<int> ns = obj.getNSentences();

    references.insert(references.end(), std::begin(ref), std::end(ref));
    weights.insert(std::end(weights), std::begin(w), std::end(w));
    numbSentences.insert(numbSentences.end(), std::begin(ns), std::end(ns));

    return *this;
}

void MyWord::setWeights(std::vector<double> w){
    weights.insert(weights.end(), w.begin(), w.end());
}

QStringList MyWord::getWords() const{
    return words;
}

std::vector<int> MyWord::getReferences() const{
    return references;
}

std::vector<double> MyWord::getWeights() const{
    return weights;
}

std::vector<int> MyWord::getNSentences() const{
    return numbSentences;
}
