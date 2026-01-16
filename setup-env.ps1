# ESP-IDF Environment Setup Script
# Run this once per terminal session: . .\setup-env.ps1

# Set ESP-IDF environment variables
$env:IDF_PATH = "C:\Users\99401\esp\v6.0\esp-idf"
$env:IDF_PYTHON_ENV_PATH = "C:\Users\99401\.espressif\python_env\idf6.0_py3.11_env"

# Add all required tools to PATH
$env:PATH = "C:\Users\99401\.espressif\python_env\idf6.0_py3.11_env\Scripts;$env:PATH"
$env:PATH = "C:\Users\99401\.espressif\tools\cmake\4.0.3\bin;$env:PATH"
$env:PATH = "C:\Users\99401\.espressif\tools\ninja\1.12.1;$env:PATH"
$env:PATH = "C:\Users\99401\.espressif\tools\xtensa-esp-elf\esp-15.2.0_20251204\xtensa-esp-elf\bin;$env:PATH"

# Create a function for idf.py
function global:idf.py { 
    & C:\Users\99401\.espressif\python_env\idf6.0_py3.11_env\Scripts\python.exe C:\Users\99401\esp\v6.0\esp-idf\tools\idf.py $args 
}

Write-Host "ESP-IDF v6.0 environment configured!" -ForegroundColor Green
Write-Host "IMPORTANT: Run with dot-source:  . .\setup-env.ps1" -ForegroundColor Yellow
Write-Host "Then you can use: idf.py build" -ForegroundColor Cyan