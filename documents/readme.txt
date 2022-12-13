# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.build.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.txt +Q -w -rrr abbreviation-API API abbreviation-FLL FLL abbreviation-FSS FSS -WW character "'" "'" code '"' '"'
#
# To read the "Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.txt +Q -cn "Readme Documentation" | iki_read +Q -w -rrr abbreviation-API API abbreviation-FLL FLL abbreviation-FSS FSS -WW character "'" "'" code '"' '"'
#

Readme Documentation:
  The bold:"Kevux Tools" (code:"kevux-tools") project provides several tools intended and design for bold:"Kevux" software, such as the bold:"Turtle Kevux Linux Distribution".

  This has been inspired by several reasons\:
    - Annoyance with problematic tools encountered during the build and compilation of a standard bold:"Linux" toolchain from scratch.
      Programs such as the standard bold:"Linux" code:"install" (from bold:"GNU Coreutils") has some seriously simple problems such as being incapable of properly installing files when the file:"/proc" file system is mounted.
      The reason for the failure (be it a bug or otherwise) is unclear but the dependency on code:"/proc" being mounted is ridiculous.

    - Better prepare for future planned functionality such as improved accessibility and interaction.
      This should help make the bold:"Turtle Kevux" distribution more ready in regards to the designers and developers future plans.

    - A need to improve maintainability of basic toolchain dependencies.
      Using a project already maintained by the same person who builds and writes both the abbreviation-FLL:"Featureless Linux Library" and the bold:"Turtle Kevux" distribution makes this even easier.
      Having fewer third-party dependencies to monitor and work with can make development and maintenance a lot easier when those replaced dependencies are simple enough.

    - Provides more exposure to the abbreviation-FLL:"Featureless Linux Library".
      This results in more testing through real-word use.

    - Makes the system more familiar.
      The developer behind both the abbreviation-FLL:"Featureless Linux Library" and this project can work better in a more comfortable environment.

  See: file:"dependencies" for specific dependencies of this project.
  See: file:"readme.build.txt" for notes building (compiling) and installing.
