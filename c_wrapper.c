#include "raga.c"
#include <unistd.h>
#include <jni.h>
#include <stdio.h>

/*JNIEXPORT void JNICALL
Java_com_example_swaram_Bridge_addraga(JNIEnv
* env,
jobject thiz
) {
    addraga();
}*/

JNIEXPORT jint JNICALL
Java_com_example_swaram_Bridge_indexof(JNIEnv *env, jobject obj, jdouble x) {
    return indexof(x);
}

JNIEXPORT jobject JNICALL
Java_com_example_swaram_Bridge_upload_1data(JNIEnv *env, jclass clazz, jobject data, jobject x) {
    data = upload_data(data, x);
    raga * upload;
    for(int i = 0; i < datasize; ++i)
    {
        (*env)->SetObjectArrayElement(env, upload, i, &data[i]);
    }
    return upload;
}

JNIEXPORT jint
Java_com_example_swaram_Bridge_indexofchar(JNIEnv *env, jobject clazz, jstring x) {
    indexofchar(x);
}

JNIEXPORT jint JNICALL
Java_com_example_swaram_Bridge_search(JNIEnv *env, jclass clazz, jstring input) {
    search(input);
}

JNIEXPORT void JNICALL
Java_com_example_swaram_Bridge_clearKeyBoardBuffer(JNIEnv * env, jobject clazz) {
    clearKeyBoardBuffer();
}

JNIEXPORT jdoubleArray JNICALL
Java_com_example_swaram_Bridge_getScale(JNIEnv *env, jclass Raga , jobject ragam) {
    jclass raga = (*env)->GetObjectClass(env, ragam);
    jfieldID scale = (*env)->GetFieldID(env, raga, "scale", "[D");
    jdoubleArray swarascale = (*env)->GetDoubleArrayElements(env, scale, JNI_TRUE);
    return swarascale;
}

JNIEXPORT jint JNICALL
Java_com_example_swaram_Bridge_getLength(JNIEnv *env, jclass clazz, jobject ragam) {
    jclass raga = (*env)->GetObjectClass(env, ragam);
    jfieldID length = (*env)->GetFieldID(env, raga, "length", "I");
    return (*env)->GetIntField(env, ragam, length);
}

/*JNIEXPORT void JNICALL
Java_com_example_swaram_Bridge_addraga(JNIEnv *env, jobject thiz, jobject data) {
    addraga(data);
}*/JNIEXPORT void JNICALL
Java_com_example_swaram_Bridge_addraga(JNIEnv *env, jobject thiz, jobject data) {
    // TODO: implement addraga()
}

JNIEXPORT jobjectArray JNICALL
Java_com_example_swaram_Bridge_srutis(JNIEnv *env, jclass clazz) {
    char srutilist[12][2] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    jobjectArray srutis;
    srutis = (jobjectArray)(*env)->NewObjectArray(env, 12, (*env)->FindClass(env,"java/lang/String"), (*env)->NewStringUTF(env,""));
    for(int i=0; i<12; i++) {
        (*env)->SetObjectArrayElement(
                env,srutis,i,(*env)->NewStringUTF(env,srutilist[i]));
    }
    return srutis;
}



JNIEXPORT jdoubleArray JNICALL
Java_com_example_swaram_Bridge_ratios(JNIEnv *env, jclass clazz) {
    double ratios[17] = {1.0, 1.067, 1.125, 1.2, 1.125, 1.2, 1.25, 1.333, 1.406, 1.5, 1.6, 1.6875, 1.8, 1.6875, 1.8, 1.875, 2.0};
    jobjectArray getratios;
    getratios = (*env)->GetDoubleArrayElements(env, ratios, JNI_TRUE);
    return getratios;
}

JNIEXPORT jdoubleArray JNICALL
Java_com_example_swaram_Bridge_srutivals(JNIEnv *env, jclass clazz) {
    double srutis[12] = {220,233.08,246.942,261.6256,277.18,293.6648,311.13,329.6275,349.2282,369.99,391.9954,415.30};
    jobjectArray getsrutis;
    getsrutis = (*env)->GetDoubleArrayElements(env, srutis, JNI_TRUE);
    return getsrutis;
}