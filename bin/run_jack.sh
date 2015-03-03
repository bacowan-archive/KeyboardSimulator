#!/bin/bash
#pulseaudio -kkk
pacmd suspend true
jackd -d alsa -d hw:0 > /dev/null&
sleep 1
pactl load-module module-jack-sink
sleep 1
pactl load-module module-jack-source
#sleep 1
pacmd suspend false
