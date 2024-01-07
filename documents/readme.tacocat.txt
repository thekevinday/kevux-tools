# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.tacocat.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.tacocat.txt +Q -w -rr FLL FLL DNS DNS -W code '"' '"'
#
# To read the "TacocaT Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.tacocat.txt +Q -cn "TacocaT Readme Documentation" | iki_read +Q -w -rr FLL FLL DNS DNS -W code '"' '"'
#

TacocaT Readme Documentation:
  The bold:"tacocat" is a program for sending and receiving files, mainly for testing purposes.

  This program is similar to code:"netcat" or code:"nc" but is not intended to function as a replacement for these tools.

  The primary use for this is to test FLL:"Featureless Linux Library" and bold:"Kevux Tools" network functionality.

  The bold:"tacocat" program has the following arguments\:

  The code:"--interval" (code:"-I") parameter designates a custom poll interval (in milliseconds) to use.
  The code:"--max_buffer" (code:"-M") parameter designates a maximum buffer size to allow (in bytes) when receiving packets.
  The code:"--receive" (code:"-r") parameter is an address or socket file to listen to.
  The code:"--resolve" (code:"-R") parameter designates a DNS:"Domain Name Resolver" mode, such as code:"classic" or code:"kevux".
  The code:"--send" (code:"-s") parameter is an address or socket file to transmit to.
