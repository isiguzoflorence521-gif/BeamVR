#include <jni.h>
#include <string>
#include <vector>
#include "beam_vr.h"

// Static instance of the SDK Streamer
static BeamVR::Streamer* g_streamer = nullptr;

extern "C" {

/**
 * JNI Implementation for initializeStream(String ip, int port, int bitrate)
 */
JNIEXPORT jboolean JNICALL
Java_com_beamvr_sdk_NativeBridge_initializeStream(JNIEnv *env, jobject thiz, jstring ip, jint port, jint bitrate) {
    const char *native_ip = env->GetStringUTFChars(ip, nullptr);
    
    BeamVR::Config cfg;
    cfg.mode = BeamVR::StreamMode::WIFI_UDP;
    cfg.target_fps = 90;
    cfg.bitrate_kbps = bitrate;

    g_streamer = BeamVR::Streamer::Create(cfg);
    bool success = g_streamer->StartSession(native_ip);

    env->ReleaseStringUTFChars(ip, native_ip);
    return (jboolean)success;
}

/**
 * JNI Implementation for sendFrameData(byte[] data, int width, int height)
 */
JNIEXPORT void JNICALL
Java_com_beamvr_sdk_NativeBridge_sendFrameData(JNIEnv *env, jobject thiz, jbyteArray data, jint width, jint height) {
    if (g_streamer == nullptr) return;

    // Get the byte array from Kotlin
    jbyte* buffer = env->GetByteArrayElements(data, nullptr);
    jsize len = env->GetArrayLength(data);

    // Pass the buffer to the C++ Core SDK
    g_streamer->SendFrame(reinterpret_cast<uint8_t*>(buffer), static_cast<size_t>(len));

    // Release the buffer without copying back
    env->ReleaseByteArrayElements(data, buffer, JNI_ABORT);
}

/**
 * JNI Implementation for stopStream()
 */
JNIEXPORT void JNICALL
Java_com_beamvr_sdk_NativeBridge_stopStream(JNIEnv *env, jobject thiz) {
    if (g_streamer != nullptr) {
        g_streamer->StopSession();
        delete g_streamer;
        g_streamer = nullptr;
    }
}

} // extern "C"
