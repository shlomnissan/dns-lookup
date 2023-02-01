# 🌍 dns-lookup

This repository contains a simple CLI tool that makes DNS queries. This tool is written in modern C++ and uses BSD sockets directly to send a request to your local DNS server and parse a response.

## Dependencies
All the dependencies are included in this repository as submodules.
- [gflags](https://github.com/gflags/gflags) - CLI flags processing 
- [GoogleTest](https://github.com/google/googletest) - Unit testing

## Building with CMake
```
$ git clone https://github.com/shlomnissan/dns-lookup
$ cd dns-lookup
$ git submodule update --init # download dependencies
$ mkdir build
$ cd build
$ cmake ..
$ make
```
If the build was successful, the build folder should contain the `dns_lookup` executable. 

## Usage

```
dns_lookup -host github.com -type MX
```
- `-host` The hostname that you wish to look up [**required**]
- `-type` The record type (A, NS, CNAME, MX, TXT, AAAA, and ANY) [optional]
- `-server` The DNS server address [optional]

## Licence
```
    ____       __                             __  
   / __ )___  / /_____ _____ ___  ____ ______/ /__
  / __  / _ \/ __/ __ `/ __ `__ \/ __ `/ ___/ //_/
 / /_/ /  __/ /_/ /_/ / / / / / / /_/ / /  / ,<   
/_____/\___/\__/\__,_/_/ /_/ /_/\__,_/_/  /_/|_|  
                                                  
Copyright (c) 2023 Shlomi Nissan
https://betamark.com

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```
