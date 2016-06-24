# README #

VMF Tool is a command-line utility to write and read metadata
information from a video file. It is based on the Intel Video Metadata
Framework SDK, available at
https://software.intel.com/en-us/vmf-sdk/download.

vmftool was written for Linux, but support was later hacked together for
Mac OS X and Windows.

Operation is:

```
#!bash

./vmtool.linux --write <video_path> <data_path>
./vmtool.linux --read <video_path>
```
