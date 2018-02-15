#ifndef MYJAVAINTERFACE_H
#define MYJAVAINTERFACE_H

#include<jni.h>
#include<string>
#include<vector>

#include "vertex.h"

class MyJavaInterface
{
private:
    JNIEnv *env;
    JavaVM *jvm;
    jclass cls;
    jmethodID mId;
    jobject obj;

public:
    MyJavaInterface();
    ~MyJavaInterface();

    int initializeJVM();
    std::vector<Vertex*> createVertex(std::string path);
};

#endif // MYJAVAINTERFACE_H
