'''
Written by Jireh Agda        Nov 22, 2019

Purpose: Initialize Keyence Microscope
'''

import logging
import os
import subprocess
import sys

_IP = '131.104.63.75'

FORMAT = '%(asctime)-15s [%(levelname)s] %(message)s'
logging.basicConfig(format=FORMAT)
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

def init_keyence():

    multiplier = '1'

    os.chdir("C:/Users/VHX Microscope/source/repos/testingrun/x64/Release")
    cmd = ["Initialize.exe", str(40), str(500), "C:/Windows/Temp/testimage.jpg", _IP, multiplier]
    logger.info(f"{cmd}")
    rc = subprocess.call(cmd)
    logger.info(f"Return Code {rc}")
    if rc != 0:
        logger.error("Initialization failed. Please check log for details and try again. Contact support for assistance.")
        sys.exit(1)

    return rc


if __name__ == '__main__':
    import argparse

    desc = "Keyence Initialization"
    parser = argparse.ArgumentParser(description=desc)

    args = parser.parse_args()

    print(init_keyence())
