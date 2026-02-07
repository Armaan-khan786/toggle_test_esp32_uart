@echo off
setlocal

REM Always run from repo root
cd /d %~dp0

set fqbn=esp32:esp32:esp32

echo compiling sender
arduino-cli compile --fqbn %fqbn% sender || exit /b 1

echo compiling receiver
arduino-cli compile --fqbn %fqbn% receiver || exit /b 1

echo flashing sender on com6
arduino-cli upload -p com6 --fqbn %fqbn% sender || exit /b 1

echo flashing receiver on com7
arduino-cli upload -p com7 --fqbn %fqbn% receiver || exit /b 1

echo waiting for boards to boot
timeout /t 5 >nul

echo reading uart logs from receiver
python tools\uart_read.py com7 || exit /b 1

echo uart toggle test passed
exit /b 0
