import Foundation
import ReplayKit
import Network

class BeamStreamer {
    private var connection: NWConnection?
    private let recorder = RPScreenRecorder.shared()
    
    // Config for the "Beaming" session
    private let targetIP: String
    private let targetPort: UInt16 = 5005

    init(ip: String) {
        self.targetIP = ip
    }

    func startBeaming() {
        guard recorder.isAvailable else {
            print("[BeamVR] Screen recording not available.")
            return
        }

        // 1. Setup Network Connection (UDP)
        let endpoint = NWEndpoint.hostPort(host: NWEndpoint.Host(targetIP), port: NWEndpoint.Port(integerLiteral: targetPort))
        connection = NWConnection(to: endpoint, using: .udp)
        connection?.start(queue: .global())

        // 2. Start Capturing Video Frames
        recorder.startCapture(handler: { (sampleBuffer, type, error) in
            if error != nil {
                print("[BeamVR] Error capturing: \(String(describing: error))")
                return
            }

            if type == .video {
                self.processAndSend(buffer: sampleBuffer)
            }
        }) { (error) in
            if let error = error {
                print("[BeamVR] Failed to start: \(error.localizedDescription)")
            } else {
                print("[BeamVR] iOS Streaming Started to \(self.targetIP)")
            }
        }
    }

    private func processAndSend(buffer: CMSampleBuffer) {
        guard let imageBuffer = CMSampleBufferGetImageBuffer(buffer) else { return }
        
        // In a real 2026 build, you'd use VideoToolbox here to compress to H.264/H.265
        // For the SDK base, we convert to data and send
        let data = self.convertBufferToData(imageBuffer)
        
        connection?.send(content: data, completion: .contentProcessed({ error in
            if let error = error {
                print("[BeamVR] Send Error: \(error)")
            }
        }))
    }

    private func convertBufferToData(_ buffer: CVPixelBuffer) -> Data {
        CVPixelBufferLockBaseAddress(buffer, .readOnly)
        let address = CVPixelBufferGetBaseAddress(buffer)
        let size = CVPixelBufferGetDataSize(buffer)
        let data = Data(bytes: address!, count: size)
        CVPixelBufferUnlockBaseAddress(buffer, .readOnly)
        return data
    }

    func stopBeaming() {
        recorder.stopCapture { _ in
            self.connection?.cancel()
            print("[BeamVR] iOS Streaming Stopped.")
        }
    }
}
