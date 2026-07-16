@echo off
setlocal

git submodule update --init --recursive

cmake ^
    -S Dunix\vendor\assimp ^
    -B Dunix\vendor\assimp\build ^
    -DASSIMP_BUILD_TESTS=OFF ^
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF

cmake --build Dunix\vendor\assimp\build --config Debug

if errorlevel 1 (
    echo Assimp build failed.
    pause
    exit /b 1
)

echo Assimp built successfully.
pause