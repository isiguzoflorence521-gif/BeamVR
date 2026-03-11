# BeamVR SDK 🚀

> Low-latency screen mirroring for mobile VR environments.

[![License: MIT](https://img.shields.io)](https://opensource.org)
[![Platform: Android/iOS/Windows](https://img.shields.io)](#)

## 📦 Repository Structure

```text
beam-vr/
├── sdk/                 # Core logic & platform wrappers
│   ├── include/         # Public headers (beam_vr.h)
│   ├── src/             # Implementation (C++)
│   └── platforms/       # Android (JNI) & iOS (Swift)
├── examples/            # Sender & Receiver samples
├── docs/                # API reference
└── tests/               # Unit & integration tests
