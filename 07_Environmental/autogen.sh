#!/bin/sh

autoreconf --install --force --verbose || {
    echo "Error: autoreconf failed" >&2
    exit 1
}

echo
echo "run ./configure"
