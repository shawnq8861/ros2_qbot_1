#!/usr/local/bin/python3
#
# to run:
# 
#
import sys
from roboclaw_3 import Roboclaw
import time

def main():
    #
    # get the encoder counts
    #
    # address of the RoboClaw as set in Motion Studio
    #
    address = 0x80
    print(address)
    #
    # Creating the RoboClaw object, serial port and baudrate passed
    #
    robo = Roboclaw("/dev/ttymxc2", 38400) 
    #
    # Starting communication with the RoboClaw hardware
    #
    opened = robo.Open()
    if opened:
        #
        # Start motor 1 in the forward direction at half speed
        #
        counts = robo.ReadEncM2(address)
        print("motor 2 counts: ", counts)
        m2_count = counts[1]
        print("motor 2 count: ", m2_count)
    else:
        print("port did not open")

    return

if __name__ == "__main__":
        #
        # run main as standalone applicatiuon
        #
    main()