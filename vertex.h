#ifndef VERTEX_H
#define VERTEX_H

#include<vector>
#include<string>
#include<QString>
#include<QStringList>

class Vertex
{
private:
    QStringList words;
    std::vector<int> references;
    std::vector<double> weights;
    std::vector<int> numbSentences;
public:
    Vertex();
    Vertex(QString, std::vector<int>, std::vector<int>);
    Vertex(const Vertex&);
    Vertex& operator =(const Vertex&);

    void setWeights(std::vector<double>);
    QStringList getWords() const;
    std::vector<int> getReferences() const;
    std::vector<double> getWeights() const;
    std::vector<int> getNSentences() const;
};

#endif // VERTEX_H
