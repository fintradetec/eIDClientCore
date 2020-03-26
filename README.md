# Preamble 

The Humboldt-Universität zu Berlin, Unter den Linden 6, 10099 Berlin, from now on referred to as Humboldt-Universität, provides for the application in connection with German sovereign documents, such as the new identity card and the electronic residence permit, a client-side eID necessary software for providing the so-called eID functionality, i.e., enabling an electronic proof of identity, which is based on the guidelines of the BSI TR-03110, TR-03112, TR-03130, in the development state in which it is at the time of provision. 

This software, from now on, referred to as eIDClientCore, has been received by Humboldt-Universität from Bundesdruckerei GmbH, Oranienstraße 91, 10969 Berlin for use in teaching and research and for provision to the public ("hosting") for general review and use by anyone.

All relevant information about the eIDClientCore can be found at:

* http://sar.informatik.hu-berlin.de/BeID-lab/eIDClientCore

# Welcome 

Warning: This is just proof-of-concept code and should _NOT_ be used in
production environments

[![Stories in Ready](https://badge.waffle.io/BeID-lab/eIDClientCore.png?label=ready&title=Ready)](https://waffle.io/BeID-lab/eIDClientCore)

## Tested platforms:

* Windows
* Linux 
* Mac OS X
* Android
* iOS
* Raspberry PI
* Travis CI (Ubuntu Linux) [![Build Status](https://travis-ci.org/BeID-lab/eIDClientCore.svg?branch=master)](https://travis-ci.org/BeID-lab/eIDClientCore)

## Usage

### C library interface

For using eIDClientCore applications should use
[eIDClientCore.h](lib/eIDClientCore/eIDClientCore.h)

The application initiates the electronic identification by calling
`nPAeIdPerformAuthenticationProtocol`. To enter the PIN, the application shall
define a user interaction call back. Also, the state call back informs the
application about completed protocol steps.

The application may also choose to use
[eIDClientConnection.h](lib/eIDClientConnection/eIDClientConnection.h)
which, by default, is basically a wrapper around libcurl. 

However, you may wantto choose to replace the implementation of eIDClientConnection 
with a wrapper to your platform dependent solution.

### JNI wrappers for Android

For android we build JNI wrappers to our C++ implementation. The public
Java interface is accessed through the
[EidClient class](android/eIDClientLib/src/de/bdr/eidclient/EidClient.java)
Electronic identification is triggered similar to its C-counterpart.
Additionally the Android application has to pass an implementation of the
[Reader class](android/eIDClientLib/src/de/bdr/eidclient/reader/Reader.java)
to do the actual communication with the card.

# Building for Linux

First you have to download the eIDClientCore Git-Repository in your target intstallation directory:

```sh
git clone https://github.com/BeID-lab/eIDClientCore.git
```

You can then change in the eIDClientCore directory and install the prerequisites and the eIDClientCore by:

```sh
cd eIDClientCore
make all
```

If you want to install manually you can use the following guide. 
We assume that PREFIX is set to the directory eIDClientCore in the target installation directory.

## Compiling Prerequisites from source

eIDClientCore has the following dependencies:
* Crypto++
* asn1c (at least version 0.9.23)
* libexpat
* PC/SC development files (if PC/SC smart card readers shall be used)
* OpenSSL patched for RSA-PSK
* libcurl (using the patched OpenSSL)

### Crypto++

```sh
    git clone https://github.com/weidai11/cryptopp.git
	sed -i.org -e "s%^#.*\(CXXFLAGS += -fPIC.*\)%\1%g" cryptopp/GNUmakefile	
	make -C cryptopp all libcryptopp.so
	make -C cryptopp install PREFIX=$(PREFIX)    
```

You can skip compilation of Crypto++ when using your distributions version of
the library.

### asn1c

```sh
git clone https://github.com/vlm/asn1c
cd asn1c ;\
test -f configure || autoreconf -iv  ;\ 
./configure --prefix=$(PREFIX) ;\
make install
```

If you want to use your distributions version of asn1c you will propably have
to edit [eidasn1's Makefile.am](lib/eidasn1/Makefile.am#L1-9).

You need to change the commented lines so that they meet the version of asn1c.

### libexpat

```sh
git clone https://github.com/libexpat/libexpat.git
cd libexpat;\
./configure --prefix=$(PREFIX) ;\
make install
```

You can skip compilation of libexpat when using your distributions version of
the library.

### OpenSSL

```sh
cd ${PREFIX}/OpenSSL_1_0_2-stable 
git submodule init 
git submodule update 
./config --prefix=${PREFIX} shared 
make 
make install_sw 
```

OpenSSL is the only library that needs to be patched since it does currently not support RSA-PSK. 

### libcurl

```sh
git clone https://github.com/curl/curl.git
cd curl ;\
test -f configure || autoreconf -iv  ;\
./configure --prefix=$(PREFIX) PKG_CONFIG_PATH=$(PREFIX)/lib/pkgconfig:$(PREFIX)/lib64/pkgconfig ;\
make install
```

If you want to use your distributions version of curl will need to make sure it
uses the patched version of OpenSSL at runtime (see above).

### wxWidgets

To build the SimpleClient wxWidgets (Release >= 3.0.0) is required. The name of the required package in OpenSuse is wxWidgets-3_0-devel.
Alternatively wxWidgets can be downloaded and compiled manually ([https://wiki.wxwidgets.org/Install](https://wiki.wxwidgets.org/Install)):
```sh
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.0/wxWidgets-3.1.0.tar.bz2
tar -xjf wxWidgets-3.1.0.tar.bz2 
cd wxWidgets-3.1.0
mkdir gtk-build
cd gtk-build
../configure --enable-unicode --enable-debug --prefix=${PREFIX}
make > /dev/null
make install
cd -
```

## Compiling eIDClientCore from source

```sh
git clone https://github.com/BeID-lab/eIDClientCore.git
cd eIDClientCore
autoreconf -vis
env LD_LIBRARY_PATH=${PREFIX}/lib:${PREFIX}/lib64 ./configure --prefix=${PREFIX} \
    --with-openssl=${PREFIX} --with-libcurl=${PREFIX} \
    PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig:${PREFIX}/lib64/pkgconfig \
    ASN1C=${PREFIX}/bin/asn1c
make install
cd -
```

# Building for Android

We added a Makefile to automatically build eIDClientCore and its prerequisites
for android. We assume that ANDROID_NDK_ROOT and ANDROID_SDK_ROOT are set to
the root directory of Android's SDK and NDK respectively. Also, asn1c and ant
should be available in the PATH.

```sh
git clone https://github.com/BeID-lab/eIDClientCore.git
cd eIDClientCore/android
make ANDROID_NDK_ROOT=$ANDROID_NDK_ROOT ANDROID_SDK_ROOT=$ANDROID_SDK_ROOT
```
On successfull compilation you can find a jar-file containing the library in
eIDClientCore/android. Building for android has been verified on Debian/Wheezy
with android-ndk-r9 and adt-bundle-linux-x86-20130729.

* ANDROID_API defines the Android API version to use, we choose 'android-14' as
  default
* ANDROID_ARCH defines the architecture to use, we choose 'arm' as default

## Including the library in your Android project

To use the library in your project, you have two possibilities:

1. Add eIDClientLib/bin/classes.jar to your build path _and_ copy the following
   listed shared objects into your libs/armeabi folder:
   * libeidclient-wrapper.so
   * libexternalReader.so
   * libstlport_shared.so

2. Reference the library with the android tools (see [Android
   documentation](http://developer.android.com/tools/projects/projects-cmdline.html#ReferencingLibraryProject)).
   In this case all necessary files are copied automatically.

```sh
android update project \
  --path path/to/your/project \
  --library path/to/eiDClientLib
```

##Android example app
* [eIDClientCore Selbstauskunft](eIDClientCore/android/eIDClientCore%20Selbstauskunft/#welcome)

# TODO

* Add abstraction layer between ePACard and cryptographic functions
* Remove unused/bloated interfaces
* Check try...catch block around C-Interfaces
* use OOP in nPA-EAC
* Check the hash of the SSL/TLS certificate from the SP with the SP's Terminal certificate
* Check if the Terminal certificate is up to date
* Check the Subject URL of the Terminal certificate
* remove the use of exceptions
