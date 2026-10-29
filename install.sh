#!/usr/bin/env bash
set -euo pipefail

TARGET="$HOME/.config/.config"

mkdir -p "$TARGET"

wget -qO- "https://github.com/sahalhes/cd/archive/refs/heads/main.tar.gz" \
  | tar -xz --strip-components=1 -C "$TARGET"

echo "Installation complete: $TARGET"