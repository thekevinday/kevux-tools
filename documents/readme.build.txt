# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.build.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.build.txt +Q -w -rr FLL FLL FSS FSS -W code '"' '"'
#
# To read the "Build Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.build.txt +Q -cn "Build Readme Documentation" | iki_read +Q -w -rr FLL FLL FSS FSS -W code '"' '"'
#

Build Readme Documentation:
  This project is intended to be built using the bold:"Featureless Make" program.

  The build system does not normally handle installation.
  The installation process should generally be handled by a distributor or by a system administrator.
  A very basic install process is added for convenience through an file:"install.sh" script.

  The files may also be manually copied as desired if not using the file:"install.sh" script.

  All built file are provided within the file:"build/" directory by default.
  This directory may have the following notable directories\:
    - code:"documents": Holds any documents for installation (often installed somewhere within file:"/usr/share" or file:"/usr/local/share").
    - code:"libraries": Holds any shared or static library files (often install somewhere within either file:"/usr/lib" or file:"/usr/local/lib").
    - code:"programs": Holds any executable files (often installed somewhere within file:"/usr/bin" or file:"/usr/local/bin").
    - code:"settings": Holds any settings files (often installed somewhere within file:"/etc" or file:"/usr/local/etc").

  Build Example, using "make"\:
    code:"fake"

  See: The FLL:"Featureless Linux Library" bold:"Featureless Make" project documents for further details on how to use the bold:"Featureless Make" system.
  See: The FLL:"Featureless Linux Library" bold:"Featureless Make" project specifications for how to configure the write FSS:"Featureless Settings Specification" files.
