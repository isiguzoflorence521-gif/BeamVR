#include "beam_vr.h"
#include <iostream>

namespace BeamVR {
    class BeamStreamer : public Streamer {
    public:
        bool Connect(const char* ip) override { 
            std::cout << "BeamVR: Connecting to " << ip << std::endl;
            return true; 
        }
        void SendFrame(const uint8_t* data, int sz) override {
            // Logic for H.264 compression & UDP send
        }
    };

    Streamer* Streamer::Create(const Config& config) {
        return new BeamStreamer();
    }
}
