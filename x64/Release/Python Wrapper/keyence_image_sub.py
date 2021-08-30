'''
Written by Jireh Agda        Nov 18, 2019

Purpose: Assemble image submission package for BOLD dropbox

Usage: Import the function assemble_image_sub_package(folder_path, mapping_file, package_name (optional, without .zip))

The mapping file is expected to be in the format of:
Sample Id\tProcess Id\tImage File
'''

import datetime
import glob
import logging
import os
import pandas as pd
import shutil
import subprocess
import sys

from collections import defaultdict

_NOW = datetime.datetime.now()

_LICENSE_HOLDER = "CBG Photography Group"
_LICENSE = "CreativeCommons - Attribution Non-Commercial Share-Alike"
_LICENSE_YEAR = _NOW.year
_LICENSE_INST = "Centre for Biodiversity Genomics"
_LICENSE_CONTACT = "ccdbcol@uoguelph.ca"
_PHOTOGRAPHER = "CBG Photography Group"

_IMG_PACK = "Keyence_0000"
_SHEET_FILE = "ImageData.xls"
_CFG_FILE = "ZZZ_imageUpload.config"

logger = logging.getLogger("__main__")


### MAIN FUNC ###

def assemble_image_sub_package(folder_path, working_dir, mapping_file, package_name=_IMG_PACK):
    '''
    Assemble image submission package to be placed into dropbox

    :param folder_path: string, folder path with images, mapping file
    :param working_dir: string, working directory where package will be
    :param mapping_file: string, mapping file for metadata -> image name
    :param package_name: string, name of submission package folder
    :return: string, path to created image submission package
    '''

    # Read mapping file
    mapping = read_mapping_file(os.path.join(folder_path, mapping_file))

    # Prepare submission package
    package_path = os.path.join(working_dir, package_name)
    os.makedirs(package_path, exist_ok=True)
    create_config(package_path)

    # Iterate through all images
    img_data = []
    image_list = glob.glob(os.path.join(folder_path, '*.jpg'))
    if not image_list:
        logger.error("No images found")

    # Copy image to submission package and add data
    for image in image_list:
        image = os.path.basename(image)
        row = {
            'Image File': image,
            'Original Specimen': 'yes',
            'View Metadata': 'Microplate',
            'Caption': '',
            'Measurement': '',
            'Measurement Type': '',

            'Sample Id': mapping[image]['sample_id'],
            'Process Id': mapping[image]['process_id'],

            'License Holder': _LICENSE_HOLDER,
            'License': _LICENSE,
            'License Year': _LICENSE_YEAR,
            'License Institution': _LICENSE_INST,
            'License Contact': _LICENSE_CONTACT,
            'Photographer': _PHOTOGRAPHER
        }
        img_data.append(row)

    # Write out spreadsheet file
    sheet_path = os.path.join(folder_path, _SHEET_FILE)
    df = pd.DataFrame(img_data)
    df.to_excel(sheet_path, index=False,
        columns=['Image File', 'Original Specimen', 'View Metadata', 'Caption', 'Measurement',
            'Measurement Type', 'Sample Id', 'Process Id', 'License Holder', 'License',
            'License Year', 'License Institution', 'License Contact', 'Photographer'])    # Enforce order of columns

    # Zip up tmp image directory, delete tmp
    package_zip = os.path.join(package_path, package_name + ".zip")
    os.chdir("C:/Program Files/7-Zip")
    cmd = ["7z.exe", "a", f"{package_zip}", f"{os.path.join(folder_path, '*.jpg')}", f"{os.path.join(folder_path, '*.xls')}", "-mx=0"]
    subprocess.call(cmd)
    os.chdir(working_dir)

    return package_path


### HELPER FUNC ###

def read_mapping_file(mapping_file):
    mapping = defaultdict(lambda: defaultdict(lambda: ''))

    with open(mapping_file, 'r') as h:
        for line in h:
            line = line.rstrip()
            sample_id, process_id, image_file = line.split('\t')
            mapping[image_file] = {
                'sample_id': sample_id,
                'process_id': process_id
            }

    return mapping


def create_config(package_path, desc=f'Keyence auto-plate scanning. Package auto created on {_NOW}'):
    config = f'''\
<?xml version="1.0"?>
<config>
	<submitter>cbgrobotics</submitter>
	<password>cbgrobo!2019</password>
	<files>
		<inputFile filename="{os.path.basename(package_path)}.zip" md5=""/>
		<inputFile filename="info.txt" md5="" optional="Y"/>
	</files>
	<priority>High</priority>
	<keepOriginal>Yes</keepOriginal>
	<instructions>
		<step>
			<action>special</action>
			<actiontype>BatchImgUpload</actiontype>
			<file>{os.path.basename(package_path)}.zip</file>
			<description>{desc}</description>
		</step>
	</instructions>
</config>
'''

    with open(os.path.join(package_path, _CFG_FILE), 'w') as h:
        h.write(config)


#Only for example purposes
if __name__ == "__main__":
    print(assemble_image_sub_package('C:\\Users\\VHX Microscope\\Desktop\\data', 'mapping.txt', 'BIOUG50412_1574790945'))

