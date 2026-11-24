#!/usr/bin/env bash
# BanglaScript Linux/macOS Installer Script
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$(dirname "$SCRIPT_DIR")")"
BIN_DIR="$PROJECT_ROOT/build/bin"

echo "Installing BanglaScript to /usr/local/bin..."

if [ -f "$BIN_DIR/banglascript" ]; then
    sudo cp "$BIN_DIR/banglascript" /usr/local/bin/banglascript
    sudo cp "$BIN_DIR/bs" /usr/local/bin/bs
    sudo chmod +x /usr/local/bin/banglascript /usr/local/bin/bs
    echo "BanglaScript installed successfully!"
    banglascript --version
else
    echo "Binary not found in $BIN_DIR. Run cmake --build build first."
    exit 1
fi
