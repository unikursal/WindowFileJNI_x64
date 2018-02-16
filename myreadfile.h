#ifndef MYREADFILE_H
#define MYREADFILE_H

#include<vertex.h>

#include<cstring>
#include<vector>
#include<utility>
#include<list>
#include<QProgressBar>

static std::string PATH_TO_ORIG_FILE = "D:\\ONPU\\Diplom\\ubercorpus.lowercased.lemmatized.word2vec.300d";
static std::string PATH_TO_SMALL_FILE = "D:\\fiction.lowercased.lemmatized.word2vec.300d";

struct MyPair{
    int n;
    std::string word;
};

class MyReadFile
{
private:
    std::vector<double> createVector(std::string);
    std::string header;

    int isWord(std::string, std::list<MyPair>&);
public:
    MyReadFile();
    //ALIGNMENT = 65536
    const int SIZE_PAGE = 2048;
    const int SEGMENT_SIZE = 4096;

    std::string getHeaders(std::string path);
    void findWords(std::vector<Vertex*>&, std::string path, QProgressBar* pBar);
    std::vector<double> findWord(std::string word, std::string path);
};

#endif // MYREADFILE_H
