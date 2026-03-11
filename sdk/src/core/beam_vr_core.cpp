#include "beam_vr.h"
namespace BeamVR {
    class CoreStreamer : public Streamer {
        bool Connect(const char* ip) override { return true; }
        void SendFrame(const uint8_t* data, int sz) override {}
    };
    Streamer* Streamer::Create() { return new CoreStreamer(); }
}
