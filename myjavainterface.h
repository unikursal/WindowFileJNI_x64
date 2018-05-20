#ifndef MYJAVAINTERFACE_H
#define MYJAVAINTERFACE_H

#include<jni.h>
#include<string>
#include<vector>

#include "myword.h"

class MyJavaInterface
{
private:
    JNIEnv *env;
    JavaVM *jvm;
    jclass cls;
    jmethodID mId, constructor;
public:
    MyJavaInterface();
    ~MyJavaInterface();

    int initializeJVM();
    std::vector<MyWord*> createVertex(std::string path);
};

#endif // MYJAVAINTERFACE_H
