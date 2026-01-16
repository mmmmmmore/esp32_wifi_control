# ESP-IDF Build Script for ESP32-S3
# This script sets up the ESP-IDF v6.0 environment and builds the project

# Navigate to project directory
Push-Location C:\Users\99401\Projects\ESP32\smart_vehicle\esp32_wifi_control

# Set ESP-IDF environment variables
$env:IDF_PATH = "C:\Users\99401\esp\v6.0\esp-idf"
$env:IDF_PYTHON_ENV_PATH = "C:\Users\99401\.espressif\python_env\idf6.0_py3.11_env"

# Add all required tools to PATH
$env:PATH = "C:\Users\99401\.espressif\python_env\idf6.0_py3.11_env\Scripts;$env:PATH"
$env:PATH = "C:\Users\99401\.espressif\tools\cmake\4.0.3\bin;$env:PATH"
$env:PATH = "C:\Users\99401\.espressif\tools\ninja\1.12.1;$env:PATH"
$env:PATH = "C:\Users\99401\.espressif\tools\xtensa-esp-elf\esp-15.2.0_20251204\xtensa-esp-elf\bin;$env:PATH"

Write-Host "ESP-IDF v6.0 environment configured for ESP32-S3" -ForegroundColor Green
Write-Host "Project directory: $(Get-Location)" -ForegroundColor Cyan

# Build the project
C:\Users\99401\.espressif\python_env\idf6.0_py3.11_env\Scripts\python.exe C:\Users\99401\esp\v6.0\esp-idf\tools\idf.py build

Pop-Location
