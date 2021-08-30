#!/usr/bin/python
#
# Written by Catherine Wei      Nov 19, 2019
#
# Change Log:
#

import sys
import argparse
import numpy
import logging
import os
import subprocess
import time

_MAX_RETRY = 3
_FATAL_ERROR_CODE = 1000
#_LOG = "C:/Windows/Temp/keyence.log"

logger = logging.getLogger("__main__")

'''
This function takes the x,y coordinate of a point relative to the physical center of microplate as origin, 
apply transformation based a angle of rotation and x,y offset as determined by the 
microscope calibration SOP.  The resulting shifted point can then be used (by SDK) to move the plate into focus.

Please note that the VHX700 desktop application applies a DIFFERENT transformation for user consumption.  Those coordinates 
may NOT map to the resulted ones used by the SDK.

'''
def rotateAndShiftPt (point , offset, angle):

    ptX = point[0] * -1     # flip coordinate
    ptY = point[1] * -1 
    offsetX, offsetY = offset

    shiftedX = int(round (numpy.cos (angle)*ptX - numpy.sin(angle)*ptY + offsetX))
    shiftedY = int(round (numpy.sin (angle)*ptX + numpy.cos(angle)*ptY + offsetY))

    return [str(shiftedX), str(shiftedY)]


def main (**kwargs):

    image_map = []

    try:
        offsetX = kwargs['offset_x']
        offsetY = kwargs['offset_y']
        angle = kwargs['angle']
        moveSpeedScalar = kwargs['speed']
        afWaitTime = kwargs['wait']
        lensMagnification = kwargs['magnify']
        ip = kwargs['ip']
        prefix = kwargs['prefix']
    except KeyError as e:
        logger.error(f"Missing config argument - {e}")
        return image_map

    cwd = os.getcwd()

    data = '''\
index	x (um)	y (um)	Well	Well_leadingZero
1	31500	49500	A1	A01
2	31500	40500	A2	A02
3	31500	31500	A3	A03
4	31500	22500	A4	A04
5	31500	13500	A5	A05
6	31500	4500	A6	A06
7	31500	-4500	A7	A07
8	31500	-13500	A8	A08
9	31500	-22500	A9	A09
10	31500	-31500	A10	A10
11	31500	-40500	A11	A11
12	31500	-49500	A12	A12
13	22500	-49500	B12	B12
14	22500	-40500	B11	B11
15	22500	-31500	B10	B10
16	22500	-22500	B9	B09
17	22500	-13500	B8	B08
18	22500	-4500	B7	B07
19	22500	4500	B6	B06
20	22500	13500	B5	B05
21	22500	22500	B4	B04
22	22500	31500	B3	B03
23	22500	40500	B2	B02
24	22500	49500	B1	B01
25	13500	49500	C1	C01
26	13500	40500	C2	C02
27	13500	31500	C3	C03
28	13500	22500	C4	C04
29	13500	13500	C5	C05
30	13500	4500	C6	C06
31	13500	-4500	C7	C07
32	13500	-13500	C8	C08
33	13500	-22500	C9	C09
34	13500	-31500	C10	C10
35	13500	-40500	C11	C11
36	13500	-49500	C12	C12
37	4500	-49500	D12	D12
38	4500	-40500	D11	D11
39	4500	-31500	D10	D10
40	4500	-22500	D9	D09
41	4500	-13500	D8	D08
42	4500	-4500	D7	D07
43	4500	4500	D6	D06
44	4500	13500	D5	D05
45	4500	22500	D4	D04
46	4500	31500	D3	D03
47	4500	40500	D2	D02
48	4500	49500	D1	D01
49	-4500	49500	E1	E01
50	-4500	40500	E2	E02
51	-4500	31500	E3	E03
52	-4500	22500	E4	E04
53	-4500	13500	E5	E05
54	-4500	4500	E6	E06
55	-4500	-4500	E7	E07
56	-4500	-13500	E8	E08
57	-4500	-22500	E9	E09
58	-4500	-31500	E10	E10
59	-4500	-40500	E11	E11
60	-4500	-49500	E12	E12
61	-13500	-49500	F12	F12
62	-13500	-40500	F11	F11
63	-13500	-31500	F10	F10
64	-13500	-22500	F9	F09
65	-13500	-13500	F8	F08
66	-13500	-4500	F7	F07
67	-13500	4500	F6	F06
68	-13500	13500	F5	F05
69	-13500	22500	F4	F04
70	-13500	31500	F3	F03
71	-13500	40500	F2	F02
72	-13500	49500	F1	F01
73	-22500	49500	G1	G01
74	-22500	40500	G2	G02
75	-22500	31500	G3	G03
76	-22500	22500	G4	G04
77	-22500	13500	G5	G05
78	-22500	4500	G6	G06
79	-22500	-4500	G7	G07
80	-22500	-13500	G8	G08
81	-22500	-22500	G9	G09
82	-22500	-31500	G10	G10
83	-22500	-40500	G11	G11
84	-22500	-49500	G12	G12
86	-31500	-40500	H11	H11
87	-31500	-31500	H10	H10
88	-31500	-22500	H9	H09
89	-31500	-13500	H8	H08
90	-31500	-4500	H7	H07
91	-31500	4500	H6	H06
92	-31500	13500	H5	H05
93	-31500	22500	H4	H04
94	-31500	31500	H3	H03
95	-31500	40500	H2	H02
96	-31500	49500	H1	H01'''.split('\n')

# H12 Removed, is control well
# 85	-31500	-49500	H12	H12

    for i in range (1, len(data)):
        line = data[i].strip("\n")
        cells = line.split("\t")

        # Transform relative (x,y) to SDK coordinates 
        newX, newY = rotateAndShiftPt ((int(cells[1]), int(cells[2])), (offsetX, offsetY), angle)

        # Generate batch commands for moving & taking auto focus image for each well
        imgFile = f"{prefix}_{i}_{cells[4]}.jpg"
        imgPath = os.path.join(cwd, imgFile)

        if os.path.exists(imgPath):
            logging.info(f"{imgPath} already exists. Skipping Well {cells[3]}")
        else:
            for i in range(_MAX_RETRY):
                output = open(os.path.join(cwd, imgFile+".log"), 'a')

                os.chdir("C:/Users/VHX Microscope/source/repos/testingrun/x64/Release")
                cmd = ["Phase2CompleteAutoFocus.exe", newX, newY, str(moveSpeedScalar), str(afWaitTime), lensMagnification, imgPath, ip]
                logger.info(f"{cmd}")
                rc = subprocess.run(cmd, stdout=output)
                output.close()
                logger.info(f"Return Code {rc}")
                if rc == _FATAL_ERROR_CODE:
                    logger.error(f"Fatal Error on Well {cells[3]}")
                    logger.error(f"Aborting program")
                    sys.exit(_FATAL_ERROR_CODE)
                elif os.path.exists(imgPath) and os.stat(imgPath).st_size > 1000:
                    # Read and output log
                    #with open(os.path.join(cwd, imgFile+".log"), 'r') as log:
                    #    print('\n'.join(log.readlines()))

                    # Add result to image map
                    image_map.append({
                        'coordinate': cells[4],
                        'imagefile': imgFile
                    })
                    break    # Break out of retry loop
                else:
                    logger.error(f"Image cannot be taken {imgFile}")
                    if i < _MAX_RETRY - 1:
                        logger.error(f"Retrying (Attempt {i + 1})...")
                        time.sleep(5)
                    else:
                        logger.error(f"Reached Maximum Attempts ({_MAX_RETRY})")

    os.chdir(cwd)

    return image_map
