import serial
import time
import sys

PORT = "COM7"        # receiver ESP32
BAUD = 115200
TIMEOUT = 15         # seconds

print(f"opening uart port {PORT}")

ser = serial.Serial(PORT, BAUD, timeout=1)
start = time.time()
result = "fail"

while time.time() - start < TIMEOUT:
    line = ser.readline().decode(errors="ignore").strip()
    if line:
        print(line)
        if "uart toggle test pass" in line.lower():
            result = "pass"
            break
        if "uart toggle test fail" in line.lower():
            result = "fail"
            break

ser.close()

if result == "pass":
    print("UART TEST RESULT: PASS")
    sys.exit(0)
else:
    print("UART TEST RESULT: FAIL")
    sys.exit(1)
