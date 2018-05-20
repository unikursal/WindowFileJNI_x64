#include "myreadfile.h"

#include <QMessageBox>
#include<fstream>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<vector>
#include<sstream>
#include<cstring>
#include<utility>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>

MyReadFile::MyReadFile()
{
    header = "";
}

std::string MyReadFile::getHeaders(std::string path){
    std::ifstream myfile;
    std::string header;

    myfile.open(path, std::ios_base::in);
    if(myfile.is_open() && !myfile.eof()){
        std::getline(myfile, header);
        myfile.close();
    }else{
        QMessageBox box;
        box.setText(QString::fromStdString(path) + " is failed path");
        box.exec();
    }

    return header;
}

void MyReadFile::findWords(std::vector<MyWord*>& vertices, std::string pathFile, QProgressBar* pBar){
    int numberOfBytes = SIZE_PAGE * boost::iostreams::mapped_file_source::alignment(),
            offset = 0, maxSizeWords = vertices.size();

    std::list<MyPair> words;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i]->getWords().size() > 0){
            QString qstr = vertices[i]->getWords().at(0);
            words.push_back({i,qstr.toStdString()});
        }
    }

    struct stat filestatus;
    stat(pathFile.data(), &filestatus);
    long long sizeFile = filestatus.st_size;
    bool readHeader = false;

    std::string buf, tmp_buf;
    bool is_eof = false;

    try{
        while(offset < sizeFile){
            boost::iostreams::mapped_file_source file(pathFile,  numberOfBytes, offset);

            if(file.is_open()){
               boost::iostreams::stream<boost::iostreams::mapped_file_source> is(file);

               while(std::getline(is, buf)){
                 if( !readHeader){
                     this->header = buf;
                     readHeader = true;
                     continue;
                  }

                 if(is_eof){
                    is_eof = false;
                    tmp_buf += buf;
                    buf.swap(tmp_buf);

                    tmp_buf.clear();
                 }

                 if(is.eof()){
                     tmp_buf = buf;
                     is_eof = true;

                     continue;
                 }

                  if( !buf.empty()){
                       std::string tmp = buf.substr(0, buf.find_first_of(' '));

                       int numb_word = isWord(tmp, words);

                       if(numb_word >= 0){

                          std::vector<double> v = createVector(buf);
                          vertices[numb_word]->setWeights(v);

                          //change progress bar
                          int changePB = (((double)(maxSizeWords -  words.size())) / maxSizeWords) * 90 + 10;
                          pBar->setValue(changePB);

                          if(words.size() == 0){
                              std::cout<<"size list  = 0 ";
                              buf.clear();

                              is.close();
                              file.close();

                              return;
                          }
                       }
                   }
                }

                buf.clear();

                is.close();
                file.close();
            }else{
                QMessageBox box;
                box.setText(QString("Error in open file  "));
                box.exec();
                return;
            }

            offset += numberOfBytes;

            if(offset + numberOfBytes >= sizeFile)
                numberOfBytes = sizeFile - offset;
        }
    }catch(std::ios_base::failure& e){
        QMessageBox box;
        box.setText(QString("Error in open file  ") + e.what());
        box.exec();
    }

    //If word not find in vocabulary
    for(MyPair mp: words)
        vertices[mp.n]->setWeights(std::vector<double>(300, 0));
}

std::vector<double> MyReadFile::findWord(std::string word, std::string pathFile){
    int numberOfBytes = SIZE_PAGE * boost::iostreams::mapped_file_source::alignment(),
            offset = 0;

    struct stat filestatus;
    stat(pathFile.data(), &filestatus);
    long long sizeFile = filestatus.st_size;
    bool readHeader = false;

    std::string buf, tmp_buf;
    bool is_eof = false;

    try{
        while(offset < sizeFile){
            boost::iostreams::mapped_file_source file(pathFile,  numberOfBytes, offset);

            if(file.is_open()){
                boost::iostreams::stream<boost::iostreams::mapped_file_source> is(file);

               while(std::getline(is, buf)){

                 if( !readHeader){
                     readHeader = true;
                     continue;
                  }

                 if(is_eof){
                    is_eof = false;
                    tmp_buf += buf;
                    buf.swap(tmp_buf);

                    tmp_buf.clear();
                 }

                 if(is.eof()){
                     tmp_buf = buf;
                     is_eof = true;

                     continue;
                 }

                  if( !buf.empty()){
                       std::string tmp = buf.substr(0, buf.find_first_of(' '));

                       if(tmp.compare(word) == 0){
                          std::vector<double> v = createVector(buf);

                          int count = 0;

                          for(int i = 0; i < 300; i++){
                              if(v[i] == 0.0) count++;
                          }

                          std::cout<<count<<"\n";

                          return v;
                       }
                   }

                   tmp_buf.swap(buf);
                }
                buf.clear();

                is.close();
                file.close();
            }else{
                QMessageBox box;
                box.setText(QString("Error in open file  "));
                box.exec();
                return std::vector<double>();
            }

            offset += numberOfBytes;

            if(offset + numberOfBytes >= sizeFile)
                numberOfBytes = sizeFile - offset;
        }
    }catch(std::ios_base::failure& e){
        QMessageBox box;
        box.setText(QString("Error in open file  ") + e.what());
        box.exec();
        return std::vector<double>();
    }

    return std::vector<double>();
}

std::vector<double> MyReadFile::createVector(std::string str){
    std::string numbers = str.substr(str.find_first_of(' '));

    std::istringstream iss(numbers);
    std::vector<std::string> tmp_vec ((std::istream_iterator<std::string>(iss)),
                                      std::istream_iterator<std::string>());
    //boost::split(tmp_vec, numbers, [](char c){return c == ' ';});


    std::vector<double> results(300);
    double d = 0;
    for(int i = 0; i < tmp_vec.size(); i++){
        d  = std::stod(tmp_vec[i]);

        results[i] = d;
    }

    return results;
}

int MyReadFile::isWord(std::string word, std::list<MyPair>& words){
    std::list<MyPair>::iterator it = words.begin();

    for(it; it != words.end(); it++){
        if(word.compare((*it).word) == 0){
            std::list<MyPair>::iterator prev = it;
            it++;

            words.erase(prev);
            return prev->n;
        }
    }

    return -1;
}
