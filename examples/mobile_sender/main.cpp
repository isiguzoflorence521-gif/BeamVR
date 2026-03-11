#include "beam_vr.h"
int main() { auto s = BeamVR::Streamer::Create(); s->Connect("127.0.0.1"); return 0; }
