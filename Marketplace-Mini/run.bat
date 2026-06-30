@echo off
title Marketplace Mini - Build & Run
echo =========================================
echo Mengkompilasi program Marketplace Mini...
echo =========================================
g++ *.cpp -o MarketplaceMini.exe

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Kompilasi gagal! Silakan cek pesan error di atas.
    pause
    exit /b %errorlevel%
)

echo [SUKSES] Kompilasi berhasil! Memulai program...
echo.
MarketplaceMini.exe

echo.
pause
