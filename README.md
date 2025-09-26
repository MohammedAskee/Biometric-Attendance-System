## 🔐 Fingerprint-Based Attendance System
A secure and user-friendly biometric attendance system built using Arduino. This system uses fingerprint recognition, keypad input, and a passcode-protected interface to mark attendance, enroll users, and manage user data — all without the need for a computer interface.

### 🚀 Project Overview
Traditional attendance systems are prone to errors, buddy punching, and inefficiencies. This project introduces a reliable, biometric-based alternative that ensures only authorized users can register attendance.

Built with affordability and simplicity in mind, this embedded system enables:
* Secure attendance logging
* Administrator-only enrollment and deletion of users
* LCD display for real-time feedback
* Keypad-based password authentication

### 💡 Key Features

* 🧬 *Biometric Authentication*
Scan fingerprints to mark attendance securely — no cards, no manual entry.
* 🛡️ *Admin Controls with Passcode*
Critical actions like user enrollment, deletion, and override are protected by a 4-digit password.
* 🖥️ *User Feedback on LCD*
Clear instructions, welcome messages, and status updates displayed on a 16x2 LCD screen.
* 🔢 *Keypad Interface*
4x4 matrix keypad for entering passcodes and user IDs without needing a serial monitor.
* ♻️ *Override Functionality*
Replace existing users with new fingerprints, using the override mode.
* 📟 *Marquee Welcome Screen*
Animated intro message using a marquee-style scroll on the LCD.

### 🛠️ Technologies & Components Used

🔧 Hardware:
* Arduino (Uno or Mega)
* Fingerprint Sensor Module (e.g., R305)
* 16x2 LCD Display
* 4x4 Matrix Keypad
* Breadboard and Jumper Wires

📚 Libraries:
* LiquidCrystal – LCD control
* Adafruit_Fingerprint – Fingerprint sensor interface
* Keypad – Keypad input handling
* SoftwareSerial – Serial communication

### 📋 Functional Workflow

* Startup: Displays animated welcome message.
* Attendance Mode: System waits for fingerprint scan.
* Match Found: Prompts for 4-digit passcode.
  * If correct, attendance is marked.
  * If incorrect, access is denied.
* Admin Actions (via keypad):
  * Press 'E' → Enroll new user
  * Press 'D' → Delete user by ID
  * Press 'O' → Override user (Delete + Re-enroll)
 
🌐 Use Cases

* Schools and university attendance tracking
* Secure check-ins at offices or labs
* Makerspaces and DIY security systems
* Home automation requiring biometric input
