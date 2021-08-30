'''
Written by Jireh Agda        Nov 19, 2019

Purpose: Create metadata mapping file for the image submission package

Usage: Import the function create_mapping_file(folder_path, lims_map, image_map, plate_id)

The LIMS mapping data is from the LIMS mapping endpoint

The image mapping is expected to be in the format of:
[{ 'coordinate': 'A01', 'imagefile': 'Well_10_A10.jpg' },
 { 'coordinate': 'A02', 'imagefile': 'Well_15_B10.jpg' }, ...]
'''
import sys
import logging
import os
import pandas as pd
import requests

_LIMS_URL = "http://131.104.63.3:8090/lims/mapping?plate={}"
_META_MAP_FILE = "mapping.txt"

logger = logging.getLogger("__main__")


### MAIN FUNC ###

def create_mapping_file(folder_path, lims_map, image_map, plate_id):
    '''
    Create metadata mapping file for submission package assembly

    :param folder_path: string, folder path with image map
    :param lims_map: list of dict, mapping of coordinate -> sampleID, processID
    :param image_map: list of dict, mapping of coordinate -> image name
    :param plate_id: string, plate id
    :return: string, path to created metadata mapping file
    '''

    # Load LIMS, image mapping
    lims_df = pd.DataFrame(lims_map)
    image_df = pd.DataFrame(image_map)

    # Write out metadata mapping file
    meta_df = pd.merge(lims_df, image_df, on='coordinate')
    meta_map_path = os.path.join(folder_path, _META_MAP_FILE)
    meta_df.to_csv(meta_map_path, sep='\t', header=False, index=False,
        columns=['sampleid', 'processid', 'imagefile'])

    return _META_MAP_FILE


def get_lims_mapping(plate_id):
    data = []

    with requests.Session() as s:
        r = s.get(_LIMS_URL.format(plate_id))
        result = r.json()
        data = result['data']
        if not data:
            logger.error("No LIMS mapping found. Contact support for assistance.")
            sys.exit(1)

    return data
