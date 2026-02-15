
### Ideas/Thoughts/Comments
* I essentially only need to constantly check one pipe for new information the other pipe can be used for sending messages which doesn't need to be checked constantly.
* I can abstract away a lot of the functionality with two separate functions in each language (4 funcs)
* I need to get the TLS up and working will be important for encrypted messages between server and client.
* Converting everything to cpp - scratch that/find a way to allow interaction between go and c because go and cpp are not directly compatiable
* Decided not to abstract anything yet cost/benefit isn't there!
### BUGS (check bug_report for updates)
* issue with if waiter starts up after the constructor then error - Fixed
* having a blocking issue! - Fixed