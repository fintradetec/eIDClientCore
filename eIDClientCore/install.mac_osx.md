## Installation on Max OS X, using brew

### Install [Brew](https://brew.sh)

     $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

### Install required libraries and tools for compilation of source code

     $ brew install automake autoconf libtool pkgconfig wget libcryptopp libgcrypt libusb

### Install asn1c (ASN 1 Compiler)
     $ brew install asn1c
     $ brew install cryptopp

### ccid-driver

Download and install reiner sct basis ccid-driver   http://www.reiner-sct.com/support/download/treiber-und-software/cyberjack/rfid-basis-macos.html?grp=kontaktlos

# eIDClientCore
     autoreconf -vis
     ./configure \
       CFLAGS="-I/opt/local/include" \
       LIBS="-Wl,-framework,PCSC -L/opt/local/lib -lgcrypt" \
       PCSC_LIBS="-Wl,-framework,PCSC" \
       PCSC_CFLAGS=-I"/usr/local/include/PCSC -I/Library/Frameworks/jsoncpp.framework/Versions/2.0.0/Headers/json -framework PCSC" \
       CRYPTOPP_CFLAGS="-I/usr/include" \
       CRYPTOPP_LIBS="-L/usr/lib -lcryptopp"
     make

# if gnutls can't find gcrypt:

     $ lib/eIDClientConnection/gnutls-2.10.2/configure CFLAGS="-I/opt/local/include" LIBS="-L/opt/local/lib -lgcrypt"
