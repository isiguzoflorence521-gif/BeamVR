# BeamVR SDK API Reference (v2.0.0) 🚀

This document defines the high-level interface for **BeamVR**.

---

## **1. Core C++ Interface**
Header: `sdk/include/beam_vr.h`

```cpp
namespace BeamVR {
    /**
     * @brief Factory method to create a Streamer instance.
     */
    static Streamer* Create(const Config& config);

    /**
     * @brief Establishes UDP connection to the receiver.
     * @param target_ip The IPv4 address of the PC.
     */
    virtual bool StartSession(const std::string& target_ip) = 0;

    /**
     * @brief Encodes and sends a raw frame buffer.
     * @param frame_data Pointer to the pixel buffer (RGBA/YUV).
     * @param size Total size of the buffer in bytes.
     */
    virtual void SendFrame(const uint8_t* frame_data, size_t size) = 0;

    /**
     * @brief Closes the network socket and stops the session.
     */
    virtual void StopSession() = 0;
}
