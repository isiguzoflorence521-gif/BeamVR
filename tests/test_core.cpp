#include <iostream>
#include <cassert>
#include <vector>
#include "beam_vr.h"

// A simple test runner for the BeamVR Core
int main() {
    std::cout << "[TEST] Initializing BeamVR Core Test..." << std::endl;

    // 1. Define Configuration
    BeamVR::Config testConfig;
    testConfig.mode = BeamVR::StreamMode::WIFI_UDP;
    testConfig.target_fps = 60;
    testConfig.bitrate_kbps = 5000;
    testConfig.enable_ai_upscaling = false;

    // 2. Test Streamer Creation
    BeamVR::Streamer* streamer = BeamVR::Streamer::Create(testConfig);
    assert(streamer != nullptr && "Streamer creation failed!");
    std::cout << "[PASS] Streamer Created Successfully." << std::endl;

    // 3. Test Connection Logic
    // Using a loopback IP for testing purposes
    bool connected = streamer->StartSession("127.0.0.1");
    assert(connected && "Failed to start session on localhost!");
    std::cout << "[PASS] Session Started on 127.0.0.1." << std::endl;

    // 4. Test Frame Transmission
    // Create a dummy 1080p RGB frame (3 bytes per pixel)
    std::vector<uint8_t> dummyFrame(1920 * 1080 * 3, 0xFF); 
    
    try {
        streamer->SendFrame(dummyFrame.data(), dummyFrame.size());
        std::cout << "[PASS] Dummy Frame Sent (Size: " << dummyFrame.size() << " bytes)." << std::endl;
    } catch (...) {
        assert(false && "SendFrame threw an unexpected exception!");
    }

    // 5. Test Shutdown
    streamer->StopSession();
    delete streamer;
    std::cout << "[PASS] Streamer Shutdown and Memory Cleared." << std::endl;

    std::cout << "\n[RESULT] All BeamVR Core tests passed successfully! 🚀" << std::endl;

    return 0;
}
