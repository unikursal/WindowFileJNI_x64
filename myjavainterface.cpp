#include "myjavainterface.h"

#include <jni.h>
#include<cstring>
#include<QString>

#include "vertex.h"

MyJavaInterface::MyJavaInterface()
{

}

MyJavaInterface::~MyJavaInterface(){
    jvm->DestroyJavaVM();
}

int MyJavaInterface::initializeJVM(){
    char path[] = "-Djava.class.path=D:\\grapht.jar";
    JavaVMOption options[1];
    JavaVMInitArgs vm_args;
    jint status;

    options[0].optionString = path;

    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

    if(status == JNI_OK){
        this->cls = env->FindClass("Action");

        if(cls != 0){
            this->constructor = env->GetMethodID(cls, "<init>", "()V");

            if(constructor != 0){
                this->mId = env->GetMethodID(cls, "getGraphText", "(Ljava/lang/String;)[B");

                if(mId != 0)
                    return 0;

                return -4;
            }

            return -3;
        }
        return -2;
    }

    return -1;
}

std::vector<Vertex*> MyJavaInterface::createVertex(std::string path_to_file){
    jobject obj = env->NewObject(cls, constructor);

    jbyteArray array;
    jstring path = env->NewStringUTF(path_to_file.data());
    array = (jbyteArray) env->CallObjectMethod(obj, mId, path);

    int size = env->GetArrayLength(array);

    jbyte* bytes = env->GetByteArrayElements(array, 0);
    uint16_t* buf = (uint16_t*)bytes;

    int i = 0, word_length = 0;
    std::vector<Vertex*> v_vertex;

    while(i < size / 2){
        //length of word or code of exception
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

        int* pointer = (int*) &buf[i];

        //size of array reference
        int ref_size = pointer[0];
        std::vector<int> ref(ref_size);

        int j = 1;
        for(; j < ref_size + 1; j++)
            ref[j - 1] = pointer[j];

        //size array number sentences
        int sent_size = pointer[j];
        std::vector<int> sent(sent_size);
        j++;
        for(int k = 0; k < sent_size; k++, j++)
            sent[k] = pointer[j];

        i += (ref_size + 1) * 2 + (sent_size + 1) * 2;

        Vertex* v = new Vertex(str, ref, sent);
        v_vertex.push_back(v);
    }

    env->ReleaseByteArrayElements(array, bytes, 0);
    env->DeleteLocalRef(array);
    env->DeleteLocalRef(obj);

    return v_vertex;
}
