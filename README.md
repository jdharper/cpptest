# C++ Unit Test Framework

This unit test frame work, *CppTest*, was inspired by [Cpp Unit Lite] by 
Michael Feathers.

## Similarities with [Cpp Unit Lite]

1. This frame work is implemented in only a couple hundred lines of code.
2. Macros are used to simplify the creation of tests and groups of tests.


## Differences from [Cpp Unit Lite]

1. This frame work relies on C++ exceptions to signal when a test has failed.
2. This frame work has a license!

## Motiviation for another unit test frame work

[CppUnitLite] is a small, lightweight unit test frame work that is easy to port
to new platforms.  I've used it to write unit tests for Linux, Windows, and a 
custom OS in use where I work.  It is small, easy to understand, and easy to
modify.  However, there's one drawback with [Cpp Unit Lite].  There's no 
license.  (At least I've never been able to find one.)  So, I can't give 
[Cpp Unit Lite] to someone else.  If I distribute unit tests I've written with 
[Cpp Unit Lite] to someone else, I have to tell them how to down load the 
frame work.  Admittedly, this is a minor inconvenience.  However, if for some 
reason the author of [Cpp Unit Lite] decides to make it unavailable for download,
It would mean that no one else could run tests I've written for that frame work.

To remedy this, I decided to take an afternoon and bang out a new frame work
similar to [Cpp Unit Lite].  To avoid copyright problems I did not look at the 
source code for [Cpp Unit Lite] during this effort.  Also, I did not try to 
make this frame work compatible.

**Update**  It appears the original [Cpp Unit Lite] code is no longer avaiable 
for download.  However, there is a copy on GitHub.  
<https://github.com/smikes/CppUnitLite>  The copy on GitHub appears to have a
license. 

[Cpp Unit Lite]: http://wiki.c2.com/?CppUnitLite
