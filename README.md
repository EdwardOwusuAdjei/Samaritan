# Samaritan

[![N|Solid](http://68.media.tumblr.com/1c65b200312aeacff084885f3c1731ec/tumblr_o7r8ca7uLG1rzqkdvo4_250.gif)](https://en.wikipedia.org/wiki/Person_of_Interest_(TV_series))

Samaritan is a fast computer vision application developed using QT and C++. Makes use of OpenFace for facial recognition [not included in this public repo]
# Features

  - Detect motion of objects from two video sources simultaneously
  - Captures pictures when there is motion
  - Start recording a video when there is motion
  - Sends a maximum of three computers an alert on the network when there is a breach

To Use:

```sh
$ export LD_PRELOAD=/usr/lib/libv4l/v4l1compat.so
$ ./ComputerVee
```

For developers...  [Instructions for OpenFace will be released soon]

```sh
$ sudo pacman -S gcc qtcreator
```

#### FREE SOFTWARE ROCKS!!
