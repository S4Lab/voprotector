# VO Protector

A virtualization-obfuscation (VO) protector based on the [ROSE](http://rosecompiler.org/) compiler infrastructure which compiles given C source code to its VO protected counterpart.

## How to build

First setup the ROSE environment based on [this guide](http://rosecompiler.org/ROSE_HTML_Reference/group__installation.html) or download its prebuilt [Ubuntu VM image](http://www.rosecompiler.org/Ubuntu-ROSE-Demo-V3.tar.gz) (about 4.4 GB compressed file; 20.2 GB if fully uncompressed). If you are in the Sharif university network, the ROSE VM image has been cached in the local FTP repo at `ftp://ftp.sharif.ir/OS/Linux/Ubuntu-ROSE-Demo-V3.tar.gz` address.
Assuming that `$BOOST_ROOT` points to the BOOST installation folder and `$ROSE_SRC`, `$ROSE_BLD`, and `$ROSE_INST` point to the ROSE source, build, and installation folders respectively, you can build voprotector as follows:

```
cp voprotector/src/* $ROSE_SRC/tools/
cd $ROSE_SRC
./build
cd $ROSE_BLD
$ROSE_SRC/configure --prefix=$ROSE_INST --enable-languages=c --with-boost=$BOOST_ROOT
cd $ROSE_BLD/tools
make
```

## How to VO-protect a C file

Assuming that `~/voprotector/test/input0.c` file contains the input C source code, the following command puts its VO-protected counterpart in the `~/voprotector/test/input0.voprotected.c` file:

```
./voprotector -rose:C_only -c ~/voprotector/test/input0.c -rose:o ~/voprotector/test/input0.voprotected.c 2>&1 | less
```

## Sample files

There are a few sample input C source codes and their VO-protected counterparts in the `test` folder.
The VO interpretor itself is placed in the `voprotector/test/vo-interpreter.c` file.
Each VO-protected binary can be built using make command after switching to the `test` folder. For example `make input0.voprotected.out` command compiles the input0.voprotected.c and links it to the VO interpretor.
To enable debug messages, uncomment the `ENABLE_VO_DEBUG_MESSAGES` define line at the beginning of `voprotector/test/vo-interpreter.c` file.

