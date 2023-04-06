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


}