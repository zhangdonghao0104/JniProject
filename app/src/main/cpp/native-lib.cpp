#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "CPPLOG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOG_TAG "CPPLOG"
extern "C" JNIEXPORT jstring JNICALL
Java_com_zdh_jni_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_changeName(JNIEnv *env, jobject thiz) {
    // TODO: implement changeName()

    jclass mainActivityCls = env->FindClass("com/zdh/jni/MainActivity");


    jfieldID nameFid = env->GetFieldID(mainActivityCls, "name", "Ljava/lang/String;");

    jstring value = env->NewStringUTF("修改为test");

    env->SetObjectField(thiz, nameFid, value);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_changeAge(JNIEnv *env, jobject thiz) {
    jclass mainActivityCls = env->GetObjectClass(thiz);
    jfieldID ageFid = env->GetFieldID(mainActivityCls, "age", "I");
    env->SetIntField(thiz, ageFid, 29);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_testArrayAction(JNIEnv *env,
                                              jobject thiz,
                                              jint count,
                                              jstring text_info,
                                              jintArray ints,
                                              jobjectArray strs) {
    // TODO: implement testArrayAction()
    int _count = count;
    LOGD("C++ _count:%d\n", count);
    const char *_text_info = env->GetStringUTFChars(text_info, NULL);
    LOGD("C++ _count:%s\n", _text_info);
    //回收代码
    env->ReleaseStringUTFChars(text_info, _text_info);
    jint *_ints = env->GetIntArrayElements(ints, NULL);
    int intsLen = env->GetArrayLength(ints);
    for (int i = 0; i < intsLen; ++i) {
        env->GetIntArrayElements(ints, NULL);
        //* 取出指针的值 挪动指针，遍历指针就是遍历数组
        LOGI("C++ ints item:%d\n", *(_ints + i));
    }
    //JNI_OK:本次c++的修改 刷新给java层，并且释放c++数组
    env->ReleaseIntArrayElements(ints, _ints, JNI_OK);

    int strLen = env->GetArrayLength(strs);
    for (int i = 0; i < strLen; ++i) {
        jstring strItemS = (jstring) env->GetObjectArrayElement(strs, i);
        const char *strItemC = env->GetStringUTFChars(strItemS, NULL);
        env->ReleaseStringUTFChars(strItemS, strItemC);

        LOGI("C++ 修改前 strItemC:%s\n", strItemC);
        jstring updateValue = env->NewStringUTF("君陌");
        env->SetObjectArrayElement(strs, i, updateValue);
    }
}

//操作student
extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_putObject(JNIEnv *env, jobject thiz, jobject student, jstring str) {

    const char *_str = env->GetStringUTFChars(str, NULL);
    LOGD("C++ _str:%s\n", _str);
    env->ReleaseStringUTFChars(str, _str);
    jclass studentClass = env->FindClass("com/zdh/jni/Student");
    jmethodID toStringMethod = env->GetMethodID(studentClass, "toString", "()Ljava/lang/String;");
    jstring toStringValueS = (jstring) env->CallObjectMethod(student, toStringMethod);
    const char *toStringValueC = env->GetStringUTFChars(toStringValueS, NULL);

    LOGI("C++  toStringValueC:%s\n", toStringValueC);
    env->ReleaseStringUTFChars(toStringValueS, toStringValueC);

    //setName
    jmethodID setNameMethod = env->GetMethodID(studentClass, "setName", "(Ljava/lang/String;)V");
    jstring value1 = env->NewStringUTF("二十三年蝉");
    env->CallVoidMethod(student, setNameMethod, value1);

    //getName
    jmethodID getNameMethod = env->GetMethodID(studentClass, "getName", "()Ljava/lang/String;");
    jstring nameS = (jstring) env->CallObjectMethod(student, getNameMethod);
    const char *nameC = env->GetStringUTFChars(nameS, NULL);
    LOGI("C++  nameC:%s\n", nameC);


    //setAge
    jmethodID setAgeMethod = env->GetMethodID(studentClass, "setAge", "(I)V");
    env->CallVoidMethod(student, setAgeMethod, 26);


    //static showInfo()

    jmethodID showInfoMethod = env->GetStaticMethodID(studentClass, "showInfo",
                                                      "(Ljava/lang/String;)V");
    jstring showInfoValue = env->NewStringUTF("莲生三十二");

    env->CallStaticVoidMethod(studentClass, showInfoMethod, showInfoValue);


    env->DeleteLocalRef(studentClass);


}
extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_insertObject(JNIEnv *env, jobject thiz) {

    jclass studentClass = env->FindClass("com/zdh/jni/Student");
    jobject student = env->AllocObject(studentClass);//C++分配一个对象，不会调用此对象的构造函数

    //setName
    jmethodID setNameMethod = env->GetMethodID(studentClass, "setName", "(Ljava/lang/String;)V");
    jstring value1 = env->NewStringUTF("二十三年蝉");
    env->CallVoidMethod(student, setNameMethod, value1);


    //setAge
    jmethodID setAgeMethod = env->GetMethodID(studentClass, "setAge", "(I)V");
    env->CallVoidMethod(student, setAgeMethod, 20);


    jclass personClass = env->FindClass("com/zdh/jni/Person");
    jobject person = env->AllocObject(personClass);//C++分配一个对象，不会调用此对象的构造函数
    jmethodID setStudentMethod = env->GetMethodID(personClass, "setStudent",
                                                  "(Lcom/zdh/jni/Student;)V");

    env->CallVoidMethod(person, setStudentMethod, student);


    jmethodID putStudentMethod = env->GetStaticMethodID(personClass, "putStudent",
                                                        "(Lcom/zdh/jni/Student;)V");
    env->CallStaticVoidMethod(personClass, putStudentMethod, student);
    // 释放方式一
    env->DeleteLocalRef(personClass);
    env->DeleteLocalRef(student);
    env->DeleteLocalRef(value1);
    env->DeleteLocalRef(personClass);
    env->DeleteLocalRef(person);
}

jclass dogClass = nullptr;
extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_testQuote(JNIEnv *env, jobject thiz) {
    if (!dogClass) {
//        dogClass = env->FindClass("com/zdh/jni/Dog");
        jclass tempClass = env->FindClass("com/zdh/jni/Dog");
        dogClass = (jclass) env->NewGlobalRef((jobject) tempClass);
        env->DeleteLocalRef(tempClass);
    }
    //构造函数永远为<init> sig为（）V  因为构造函数无返回值
    jmethodID dogInit = env->GetMethodID(dogClass, "<init>", "()V");
    jobject dog = env->NewObject(dogClass, dogInit);

    jmethodID dogInit1 = env->GetMethodID(dogClass, "<init>", "(I)V");
    jobject dog1 = env->NewObject(dogClass, dogInit1, 1);

    jmethodID dogInit2 = env->GetMethodID(dogClass, "<init>", "(II)V");
    jobject dog2 = env->NewObject(dogClass, dogInit2, 1, 2);


}
extern "C"
JNIEXPORT void JNICALL
Java_com_zdh_jni_MainActivity_delQuote(JNIEnv *env, jobject thiz) {
    if (dogClass) {
        env->DeleteGlobalRef(dogClass);
        dogClass = nullptr;
    }
}