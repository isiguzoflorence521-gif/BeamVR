import socket
import cv2
import numpy as np

# Configuration matching the SDK defaults
UDP_IP = "0.0.0.0"  # Listen on all available interfaces
UDP_PORT = 5005     # Must match the port in BeamVR::Config
MAX_PKT = 65507     # Max UDP packet size

def start_receiver():
    # 1. Setup UDP Socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    
    print(f"🚀 BeamVR Test Receiver started on port {UDP_PORT}")
    print("Waiting for mobile stream...")

    try:
        while True:
            # 2. Receive packet
            data, addr = sock.recvfrom(MAX_PKT)
            
            # 3. Basic Debugging: Print packet size
            print(f"Received {len(data)} bytes from {addr}")

            # 4. Optional: Quick Visualization (Requires raw pixels or MJPEG)
            # If sending raw frames, you can attempt to reconstruct them:
            # frame = np.frombuffer(data, dtype=np.uint8).reshape((720, 1280, 3))
            # cv2.imshow('BeamVR Test Stream', frame)
            # if cv2.waitKey(1) & 0xFF == ord('q'): break

    except KeyboardInterrupt:
        print("\nStopping Receiver...")
    finally:
        sock.close()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    start_receiver()
