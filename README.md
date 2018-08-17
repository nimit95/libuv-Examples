# Libuv Examples 

The aim of this repo is to contain examples for most of the Libuv APIs.

This repo contains libuv example programs. These includes 
* uv_idle
* uv_fs_*


## Overview

libuv is a multi-platform support library with a focus on asynchronous I/O. It
was primarily developed for use by [Node.js][], but it's also
used by [Luvit](http://luvit.io/), [Julia](http://julialang.org/),
[pyuv](https://github.com/saghul/pyuv), and [others](https://github.com/libuv/libuv/wiki/Projects-that-use-libuv).

## Getting Started

### Libuv
To install libuv following steps need to be followed 


To build with autotools:

```bash
$ git clone https://github.com/libuv/libuv && cd libuv
$ sh autogen.sh
$ ./configure
$ make
$ make check
$ make install
```

### Libuv Examples 

```bash
$ git clone https://github.com/nimit95/libuv-Examples && cd libuv-Examples
```
To execute a program :

```bash
$ make <program-name>.c
$ ./<program-name>
```
To make all program at once

```bash
$ make all
```

## Contribution
All the issues and pull requests are welcomed. 