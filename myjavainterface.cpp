#include "myjavainterface.h"

#include <jni.h>
#include<cstring>
#include<iostream>
#include<QTextStream>
#include<QString>

#include "vertex.h"

MyJavaInterface::MyJavaInterface()
{

}

MyJavaInterface::~MyJavaInterface(){
    jvm->DestroyJavaVM();
}

int MyJavaInterface::initializeJVM(){
    char path[] = "-Djava.class.path=D:\\graphtLE.jar\\";
    JavaVMOption options[1];
    JavaVMInitArgs vm_args;
    jint status;
    jmethodID constructor;

    options[0].optionString = path;

    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

    if(status == JNI_OK){
        cls = env->FindClass("Action");

        constructor = env->GetMethodID(cls, "<init>", "()V");

        if(constructor != 0){
            obj = env->NewObject(cls, constructor);

            if(cls != 0){
                mId = env->GetMethodID(cls, "getGraphText", "(Ljava/lang/String;)[B");

                if(mId != 0)
                    return 0;

                return -2;

            }
            return -3;

        }
        return -4;
    }

    return -1;
}

std::vector<Vertex*> MyJavaInterface::createVertex(std::string path_to_file){
    jbyteArray array;
    jstring path = env->NewStringUTF(path_to_file.c_str());
    array = (jbyteArray) env->CallObjectMethod(obj, mId, path);

    int size = env->GetArrayLength(array);

    jbyte* bytes = env->GetByteArrayElements(array, 0);
    uint16_t* buf = (uint16_t*)bytes;

    int i = 0, word_length = 0;
    std::vector<Vertex*> v_vertex;

    while(i < size / 2){
        short length = buf[i];
        i++;

        if(length < 0){
            //error
            break;
        }

        word_length = i + length;

        QString str;
        for(; i < word_length; i++){
            str.append(QChar(buf[i]));
        }

        int* ref_size = (int*) &buf[i];
        std::vector<int> ref(ref_size[0]);

        for(int j = 1; j < ref_size[0] + 1; j++)
            ref[j - 1] = ref_size[j];

        i += (ref_size[0] + 1) * 2;

        Vertex* v = new Vertex(str, ref);
        v_vertex.push_back(v);
    }


    //env->ReleaseStringUTFChars();
    env->ReleaseByteArrayElements(array, bytes, 0);

    return v_vertex;
}
