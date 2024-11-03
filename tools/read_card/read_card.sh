#!/bin/zsh
# Reads the contents of data.csv from the Adalogger and writes it out to a similar file in this directory

FQBN="adafruit:samd:adafruit_feather_m0"
PORT=$(arduino-cli board list | grep "$FQBN" | awk '{print $1}')

if [ -z "$PORT" ]; then
    echo "Error: No Adalogger detected"
    exit 1
else
    echo "Adalogger detected on port $PORT"
fi

arduino-cli compile --fqbn "$FQBN" read_card.ino
arduino-cli upload -p "$PORT" --fqbn "$FQBN" read_card.ino

python3 save_card.py "$PORT"