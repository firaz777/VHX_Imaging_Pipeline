'''
Written by Jireh Agda        Nov 19, 2019

Purpose: Keyence Pipeline - Automated Imaging Submission
'''

import datetime
import json
import logging
import os
import pandas as pd
import sys

from argparse import Namespace

from keyence_exec import main as keyence_execute
from keyence_meta_map import get_lims_mapping, create_mapping_file
from keyence_image_sub import assemble_image_sub_package

_CONFIG = 'C:/Users/VHX Microscope/source/repos/testingrun/x64/Release/Python Wrapper/keyence_config.json'

FORMAT = '%(asctime)-15s [%(levelname)s] %(message)s'
logging.basicConfig(format=FORMAT)
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

### PIPELINE FUNC ###

def keyence_pipeline(args):

    if not os.path.isfile(_CONFIG):
        logger.error("Config file not found - Please calibrate first")
        sys.exit(1)

    logger.info("Reading configuration")
    with open(_CONFIG, 'r') as h:
        config = json.load(h)

    plate_id = args.plate
    working_dir = os.path.abspath(args.dir)
    working_dir_tmp = os.path.join(working_dir, f"Data_{plate_id}_{int(datetime.datetime.now().timestamp())}")

    logger.info("Retrieving LIMS data")
    lims_df = get_lims_mapping(plate_id)

    os.makedirs(working_dir_tmp, exist_ok=True)
    os.chdir(working_dir_tmp)

    logger.info("Executing imaging program")
    config['prefix'] = plate_id
    image_map = keyence_execute(**config)

    logger.info("Creating metadata mapping file")
    meta_map = create_mapping_file(working_dir_tmp, lims_df, image_map, plate_id)

    logger.info("Assembling image package")
    img_package = assemble_image_sub_package(working_dir_tmp, working_dir, meta_map, os.path.basename(working_dir_tmp)[5:])

    return img_package


if __name__ == "__main__":
    import argparse

    desc = "Keyence Pipeline - Automated Imaging Submission"
    parser = argparse.ArgumentParser(description=desc)
    parser.add_argument('-d', '--dir', help='Working Dir', required=True)
    parser.add_argument('-p', '--plate', help='Plate ID', required=True)
    args = parser.parse_args()

    logger.info(keyence_pipeline(args))
