# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.tacocat-packet.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.tacocat-packet.txt +Q -w -r FLL FLL -W code '"' '"'
#
# To read the "TacocaT Packet Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.tacocat-packet.txt +Q -cn "TacocaT Packet Readme Documentation" | iki_read +Q -w -r FLL FLL -W code '"' '"'
#

TacocaT Packet Readme Documentation:
  This describes the numerous bold:"tacocat" related network packets.

  The bold:"packet" is designed around italic:"push" logic in that the sender shall push to the receiver to initiate the connection and transfer the file.
  The receiver therefore cannot ask which part to work on.
  However, the receiver can immediately issue a code:"next" bold:"packet" with the code:"part" at any given valid position within the range of the total bold:"packets".
  To prevent abuse, the sender should have a maximum number of code:"next" and code:"resend" packets before aborting and must ensure that potential circular logic for the code:"next" bold:"packets" does not become a problem.

  The following are the standard bold:"packet" headers and their purposes\:
  - code:"status": This describes the status code of the bold:"packet" using FLL:"Featureless Linux Library" status codes (as strings rather than digits), such as code:"F_okay".
  - code:"type": This describes the type of the bold:"packet", which is one of: code:"abort", code:"done", code:"file", code:"next", or code:"resend".
  - code:"length": This describes the complete length of the code:"Payload" code:"Content" within the bold:"packet".
  - code:"part": This describes the part within the sequence of total bold:"packets", starting at 0 rather than 1.
  - code:"total": This describes the total number of sequence of packets needed to transmit an entire file.
  - code:"name": This describes the name of the file being transmitted.
  - code:"salt": This is a random sequence of printable characters used to make the bold:"packet" more unique should it be encrypted.

  The code:"abort" bold:"packet" type is the bold:"packet" used for informing the other end to immediately abort the connection.
  This uses the following headers: code:"status", code:"type", and code:"salt".
  The sender should wait for a code:"done" bold:"packet" but may immediately abort rather than wait.
  This is should not have a code:"Payload" section.

  The code:"done" bold:"packet" type is the bold:"packet" used for informing the connection on the other end that this end of the connection is done with a particular transmission or action.
  This uses the following headers: code:"status", code:"type", and code:"salt".
  When the used in response to a code:"file" bold:"packet", this bold:"packet" represents that the file transfer is completely received.
  The sender does not send a done bold:"packet" when transmitting a code:"file" bold:"packet".
  This is should not have a code:"Payload" section.

  The code:"file" bold:"packet" type is the bold:"packet" used for transmitting files from the sender to the receiver.
  This uses the following headers: code:"status", code:"type", code:"length", code:"part", code:"total", code:"name", and code:"salt".
  This is expected to have a code:"Payload" section defined, except when the code:"Payload" is of 0 length (an empty file).

  The code:"next" bold:"packet" type is the bold:"packet" used for confirming that a bold:"packet" part has been received on the receiving end and the sender should send the next bold:"packet".
  This uses the following headers: code:"status", code:"type", code:"part", code:"name", and code:"salt".
  The sender should increment to the immediate next code:"part" by incrementing that part by one so long as that next part is within a valid range.
  This is not sent for the last bold:"packet" by the receiver.
  Should a receiver transmit a code:"next" packet once the total is reached, then the sender should inform the receiver of this error by responding with a code:"done" packet containing the code:"part" header set to the last valid part number (which is total minus one).
  The code:"part" should represent the current part already read and now confirmed.
  This is should not have a code:"Payload" section.

  The code:"resend" bold:"packet" type is the bold:"packet" used for asking for an already sent bold:"packet".
  This uses the following headers: code:"status", code:"type", code:"part", code:"name", and code:"salt".
  The code:"part" should represent the part to be resent.
  This is should not have a code:"Payload" section.
