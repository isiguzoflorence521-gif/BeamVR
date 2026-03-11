#ifndef BEAM_VR_H
#define BEAM_VR_H
#include <cstdint>

namespace BeamVR {
    enum class Mode { WIFI, USB };
    struct Config { Mode mode; int fps; int bitrate; };
    
    class Streamer {
    public:
        static Streamer* Create(const Config& config);
        virtual bool Connect(const char* ip) = 0;
        virtual void SendFrame(const uint8_t* data, int sz) = 0;
    };
}
#endif
