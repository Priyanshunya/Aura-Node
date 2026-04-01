# ⚡ Aura-Node
> **Bridging the safety gap for India's heterogeneous traffic via infrastructure-independent V2V intelligence.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Hardware](https://img.shields.io/badge/Hardware-ESP32-blue.svg)]()
[![Protocol](https://img.shields.io/badge/Protocol-ESP--NOW-green.svg)]()

### 🏆 Team Vision.exe - National Road Safety Initiative Submission

**[📄 View the Official Pitch Deck here (PDF)](Vision_exe_Aura-Node.pdf)**
**[🎥 Watch the Hardware Prototype Demo here](https://drive.google.com/drive/folders/11mKqqmBnzBV_A0G_Bcpa5rW-wn8XLETZ?usp=drive_link)**

---

## 🚨 The Threat Vectors
Standard road safety tech (like luxury ADAS) is designed for structured, predictable environments—leaving massive blind spots when faced with the dynamic realities of Indian traffic. We face three unique challenges:
1. **Visibility Collapse:** Optical sensors (Cameras/LiDAR) fail in India's dense winter fog, causing high-speed fatal pileups.
2. **Heterogeneous Reality:** Over 70% of Indian traffic comprises two-wheelers. Standard car-based safety systems ignore these vulnerable riders.
3. **Golden Hour Deficit:** 80% of severe fatalities occur when victims are hidden off-road. Reliance on bystanders delays emergency dispatch.

---

## 🛠️ Our Solution: Aura-Node
Aura-Node is a retrofittable, clinical-grade safety module designed for autonomous collision avoidance and emergency intervention. At a **sub-₹1000 Bill of Materials**, it is universally retrofittable—protecting a bicycle just as effectively as a commercial truck.

### Core Features
* **Preventative Fog Mesh (ESP-NOW):** Bypasses optical limits using Non-Line-of-Sight (NLOS) telemetry, broadcasting sudden braking/swerving to local vehicles with ultra-low **2ms latency**.
* **Edge-Kinematic Engine:** A custom low-pass filter running at 100Hz isolates true catastrophic impacts (>4G sustained or 90° roll) from standard 20ms pothole spikes.
* **Store-and-Forward Data Mules:** If a crash happens in a cellular dead-zone, the encrypted SOS payload is passed via the mesh to passing vehicles, which auto-upload to the cloud upon entering a 4G zone.
* **Deterministic Escalation:** Instantly translates raw GPS telemetry into an automated Twilio SMS and Voice escalation to secure the "Golden Hour".

---

## ⚙️ Technical Architecture
**1. Perception Node (Hardware)**
* Dual-Core MCU (ESP32) for parallel sensing and RF transmission.
* 6-Axis IMU (MPU6050) for high-fidelity kinematics.
* NEO-6M GPS for exact localization.

**2. Intelligence (Edge Computing)**
* Vector Math: Calculates continuous absolute magnitude vector (|A|) directly on the edge.

**3. Communication (Cloud & Mesh)**
* V2V Mesh: ESP-NOW peer-to-peer MAC routing.
* Cloud: Firebase NoSQL / Twilio REST API.
