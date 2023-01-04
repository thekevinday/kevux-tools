# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.remove.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.remove.txt +Q -w -r FLL FLL -WW character "'" "'" code '"' '"'
#
# To read the "Remove Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.remove.txt +Q -cn "Remove Readme Documentation" | iki_read +Q -w -r FLL FLL -WW character "'" "'" code '"' '"'
#

Remove Readme Documentation:
  The bold:"remove" is a program for removing files and directories.

  This program is similar to code:"rm", code:"rmdir", and code:"unlink".
  Compatibility helpers are provided for code:"rm", code:"rmdir", and code:"unlink" programs to closely match functionality.
  Not everything may be supported but these compatibility helpers should help ease the transition.

  The default behavior is to remove all non-directory files and to fail when a directory is attempted to be removed.
  When any of the file type parameters are specified, then the default behavior is completely overwritten.
  Once a single file type parameter is specified, then the removals happen for all specified file type parameters combined.

  The standard code:"FLL-0.6" help options are supported and two of the code:"FLL-0.7" options are brought in (code:"--line_first_no" and code:"--line_last_no").
  The code:"--line_first_no" parameter suppresses printing the first line that is not data related.
  The code:"--line_last_no" parameter suppresses printing the last line that is not data related.

  The bold:"remove" program has the following arguments\:

  The code:"--block" (code:"-b") parameter is a file type parameter that restricts removal to block device files.
  The code:"--character" (code:"-c") parameter is a file type parameter that restricts removal to character device files.
  The code:"--date" (code:"-D") parameter accepts three additional parameters and restricts removal based on the relationship to some date.
  The code:"--different" (code:"-O") parameter restricts removal of files whose owner is not the user of the caller of the program.
  The code:"--directory" (code:"-d") parameter is a file type parameter that restricts removal to directory files.
  The code:"--empty" (code:"-e") parameter to remove empty directories.
  The code:"--empty_fail" (code:"-y") parameter to fail on empty directories.
  The code:"--empty_fail_not" (code:"-Y") parameter to fail on not empty directories.
  The code:"--empty_not" (code:"-E") parameter to fail on not-empty directories.
  The code:"--follow" (code:"-F") parameter alters removal to remove the files pointed to by a symbolic link rather than the link itself.
  The code:"--force" (code:"-f") parameter to never prompt and ignore non-existent files and arguments.
  The code:"--group" (code:"-g") parameter accepts two additional parameters that restrict removal to the given group identifier.
  The code:"--isolate" (code:"-i") parameter accepts one additional parameter that restricts removal to a single file system.
  The code:"--link" (code:"-l") parameter is a file type parameter that restricts removal to a symbolic link file.
  The code:"--mode" (code:"-m") parameter accepts two additional parameters that restrict removal to the given file mode.
  The code:"--prompt" (code:"-p") parameter accepts one additional parameter that designates operating in interactive mode and prompts the user for input.
  The code:"--recurse" (code:"-g") parameter remove directories and their contents recursively.
  The code:"--regular" (code:"-R") parameter is a file type parameter that restricts removal to regular files (commonly referred to as just bold:"file").
  The code:"--same" (code:"-s") parameter restricts removal of files whose owner is the user of the caller of the program.
  The code:"--simulate" (code:"-S") parameter designates that the program operates in simulation mode, never removing anything and instead printing what would have been mode (unless in quiet mode).
  The code:"--socket" (code:"-k") parameter is a file type parameter that restricts removal to socket files.
  The code:"--tree" (code:"-t") parameter designates that the specified directory tree is also deleted (may require --force and --recurse if directory tree is not empty).
  The code:"--user" (code:"-u") parameter accepts two additional parameters that restrict removal to the given group identifier.

  The code:"--date" (code:"-d") parameter's arguments three are (and in this order)\:
    1) Either bold:"create" or bold:"modify" to represent file created date or file modified date.
    2) One of bold:"<", bold:"<=", bold:"==", bold:">=", and bold:">" to represent the relationship between the date in argument 3.
    3) The date (can be in Time format, such as code:"2020:86.4 TT" and code:"2020:86400000000000" (copy the documentation from Featureless Make and/or Controller to describe this)).
