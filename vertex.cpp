#include "vertex.h"

Vertex::Vertex(){}

Vertex::Vertex(QString str, std::vector<int> inputVec, std::vector<int> nSent)
{
    words = str.split("+");

    references.insert(references.end(), inputVec.begin(), inputVec.end());
    numbSentences.insert(numbSentences.end(), nSent.begin(), nSent.end());
}

Vertex::Vertex(const Vertex& obj){
    words = QStringList(obj.getWords());

    std::vector<int> ref = obj.getReferences();
    std::vector<double> w = obj.getWeights();
    std::vector<int> ns = obj.getNSentences();

    references.insert(references.end(), std::begin(ref), std::end(ref));
    weights.insert(std::end(weights), std::begin(w), std::end(w));
    numbSentences.insert(numbSentences.end(), std::begin(ns), std::end(ns));
}

Vertex& Vertex::operator=(const Vertex& obj){
    words = QStringList(obj.getWords());

    std::vector<int> ref = obj.getReferences();
    std::vector<double> w = obj.getWeights();
    std::vector<int> ns = obj.getNSentences();

    references.insert(references.end(), std::begin(ref), std::end(ref));
    weights.insert(std::end(weights), std::begin(w), std::end(w));
    numbSentences.insert(numbSentences.end(), std::begin(ns), std::end(ns));

    return *this;
}

void Vertex::setWeights(std::vector<double> w){
    weights.insert(weights.end(), w.begin(), w.end());
}

QStringList Vertex::getWords() const{
    return words;
}

std::vector<int> Vertex::getReferences() const{
    return references;
}

std::vector<double> Vertex::getWeights() const{
    return weights;
}

std::vector<int> Vertex::getNSentences() const{
    return numbSentences;
}
