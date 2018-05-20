#include "mywmdmodel.h"

MyWmdModel::MyWmdModel(std::vector<MyWord*>& words)
{
    count = 0;
    maxSentSize = 0;

    int i, j, k;
    for(i = 0; i < words.size(); i++){
        std::vector<int> sentNumb = words[i]->getNSentences();

        for(j = 0; j < sentNumb.size(); j++){
            int ns = sentNumb[j];

            if(ns > count)
                count = ns;

            bool add = false;

            for(k =  0; k < sentences.size(); k++){
                if(sentences[k].SENTENCES_NUMBER == ns){
                    sentences[k].addWord(i);
                    add = true;
                    break;
                }
            }

            if(!add){
                MySentences ms = MySentences(j);
                ms.addWord(i);
                sentences.push_back(ms);

            }
        }
    }

    for(i = 0; i < sentences.size(); i++)
        if(sentences[i].getWords().size() > maxSentSize)
            maxSentSize = sentences[i].getWords().size();
}

double MyWmdModel::getSimilarity(int f_sent, int sec_sent, std::vector<MyWord*>& words){
    int i;
    std::vector<int> words_f_sent, words_sec_sent;
    for(i = 0; i < sentences.size(); i++){
        if(sentences[i].SENTENCES_NUMBER == f_sent)
            words_f_sent = sentences[i].getWords();

        if(sentences[i] == sec_sent)
            words_sec_sent = sentences[i].getWords();
    }
    if(words_f_sent.empty() || words_sec_sent.empty())
        return -1.0;

    int n = words_f_sent.size(), m = words_sec_sent.size();

    double* weights;
    weights = new double[n * m];

    ActionsWithVectors awv;
    int j, w1, w2;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++){
            w1 = words_f_sent[i], w2 = words_sec_sent[j];
            weights[i * n + j] = awv.getSimilarityMeasure(words[i]->getWeights(), words[j]->getWeights());
        }

    delete [] weights;
    return 0.0;
}

int MyWmdModel::getCount(){
    return count;
}
