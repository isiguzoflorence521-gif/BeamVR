package com.beamvr.sdk

import android.view.Surface
import android.util.Log

/**
 * BeamVR Android Native Bridge
 * Connects the Kotlin UI/Camera layer to the C++ Core SDK.
 */
class NativeBridge {

    companion object {
        private const val TAG = "BeamVR_Native"

        // Load the C++ library compiled from sdk/src/core
        init {
            try {
                System.loadLibrary("beamvr_core")
                Log.i(TAG, "BeamVR Core Library Loaded Successfully.")
            } catch (e: UnsatisfiedLinkError) {
                Log.e(TAG, "Failed to load BeamVR library: ${e.message}")
            }
        }
    }

    /**
     * Initializes the streamer with 2026 specs (H.265/Wi-Fi 7).
     * @param ip The target PC receiver IP address.
     * @param port The target port (default 5005).
     */
    external fun initializeStream(ip: String, port: Int, bitrate: Int): Boolean

    /**
     * Pass raw frame data (YUV/RGBA) from Android's MediaProjection or CameraX
     * directly into the C++ encoder.
     */
    external fun sendFrameData(data: ByteArray, width: Int, height: Int)

    /**
     * Stop the session and release native socket resources.
     */
    external fun stopStream()

    /**
     * Callback for the C++ layer to report network latency or errors back to Kotlin.
     */
    fun onNativeError(errorCode: Int, message: String) {
        Log.e(TAG, "Native Error [$errorCode]: $message")
    }
}
