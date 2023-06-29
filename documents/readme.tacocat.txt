# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.remove.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.tacocate.txt +Q -w -rrr FLL FLL PID PID DNS DNS -WW character "'" "'" code '"' '"'
#
# To read the "Remove Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.tacocate.txt +Q -cn "TacocaT Readme Documentation" | iki_read +Q -w -rrr FLL FLL PID PID DNS DNS -WW character "'" "'" code '"' '"'
#

TacocaT Readme Documentation:
  The bold:"tacocat" is a program for sending and receiving files, mainly for testing purposes.

  This program is similar to code:"netcat" or code:"nc".

  The primary use for this is to test bold:"Featureless Linux Library" and bold:"Kevux Tools" network functionality.

  The bold:"tacocat" program has the following arguments\:

  The code:"--background" (code:"-b") causes this program to run in the background.
  The code:"--from" (code:"-f") parameter is an address or socket file to listen to.
  The code:"--pid" (code:"-p") causes this program to create a PID:"Process Identifier" file.
  The code:"--pid_name" (code:"-N") parameter designates a custom PID:"Process Identifier" file name without the '.pid' extension or the directory path.
  The code:"--pid_path" (code:"-P") parameter designates a custom PID:"Process Identifier" directory path.\
  The code:"--resolve" (code:"-R") parameter designates a DNS:"Domain Name Resolver" mode, such as code:"classic" or code:"kevux".
  The code:"--to" (code:"-t") parameter is an address or socket file to transmit to.
