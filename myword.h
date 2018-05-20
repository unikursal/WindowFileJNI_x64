#ifndef VERTEX_H
#define VERTEX_H

#include<vector>
#include<string>
#include<QString>
#include<QStringList>

class MyWord
{
private:
    QStringList words;
    std::vector<int> references;
    std::vector<double> weights;
    std::vector<int> numbSentences;
public:
    MyWord();
    MyWord(QString, std::vector<int>, std::vector<int>);
    MyWord(const MyWord&);
    MyWord& operator =(const MyWord&);

    void setWeights(std::vector<double>);
    QStringList getWords() const;
    std::vector<int> getReferences() const;
    std::vector<double> getWeights() const;
    std::vector<int> getNSentences() const;
};

#endif // VERTEX_H
