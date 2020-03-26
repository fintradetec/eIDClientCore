SHELL=/bin/bash

PREFIX ?= $(shell pwd)

ASN1C ?= "$(PREFIX)/bin/asn1c"

#INSECURE = "true"

#BASIERT auf: https://github.com/BeID-lab/eIDClientCore/blob/master/README.md

ALL_DEPS = cryptopp asn1c libexpat openssl libcurl
MY_DEPS = cryptopp asn1c libexpat openssl libcurl

all:	$(MY_DEPS) eIDClient

mydeps: $(MY_DEPS)

delete_all: 
	rm -rf *[^Makefile]*

clean_cryptopp: 
	make -C cryptopp*/ clean

clean_asn1c:
	make -C asn1c*/ clean

clean_libexpat:
	make -C expat*/ clean

clean_openssl:
	make -C OpenSSL*/ clean

clean_libcurl:
	make -C curl*/ clean

clean_eIDClient:
	make -C eIDClientCore/ clean

clean: clean_cryptopp clean_asn1c clean_libexpat clean_openssl clean_libcurl clean_eIDClient

cryptopp:
        git clone https://github.com/weidai11/cryptopp.git
        sed -i.org -e "s%^#.*\(CXXFLAGS += -fPIC.*\)%\1%g" cryptopp/GNUmakefile
        make -C cryptopp all libcryptopp.so
        make -C cryptopp install PREFIX=$(PREFIX)
asn1c:
	git clone https://github.com/vlm/asn1c
	cd asn1c ;\
	test -f configure || autoreconf -iv  ;\ 
	./configure --prefix=$(PREFIX) ;\
	make install

libexpat:
        git clone https://github.com/libexpat/libexpat.git
	cd libexpat;\
	./configure --prefix=$(PREFIX) ;\
	make install
	
openssl:
        git clone https://github.com/openssl/openssl.git ;\
        cd openssl ;\
	git submodule init ;\
	git submodule update ;\
	./config shared ;\
	make -j8 ;\
	make install_sw ;\
	openssl ciphers -v 'PSK';\
	if test $$? -ne 0 ; then \
		echo "No RSA-PSK cipher suites found. OpenSSL build some somehow failed!" ;\
		exit 1 ;\
	fi

libcurl:
	git clone https://github.com/curl/curl.git
	cd curl ;\
	test -f configure || autoreconf -iv  ;\
	./configure --prefix=$(PREFIX) PKG_CONFIG_PATH=$(PREFIX)/lib/pkgconfig:$(PREFIX)/lib64/pkgconfig ;\
	make install

eIDClient:
	cd eIDClientCore ;\
	autoreconf -vis ;\
	env LD_LIBRARY_PATH=$(PREFIX)/lib:$(PREFIX)/lib64 ./configure --prefix=$(PREFIX) \
    	--with-openssl=$(PREFIX) --with-libcurl=$(PREFIX) \
    	PKG_CONFIG_PATH=$(PREFIX)/lib/pkgconfig:$(PREFIX)/lib64/pkgconfig\
    	ASN1C="$(ASN1C)" CRYPTOPP_CFLAGS="-I$(PREFIX)/include" CRYPTOPP_LIBS="-L$(PREFIX)/lib -lcryptopp"
	[[ -v INSECURE ]] || \
		sed -i.org -e "s%^\(CPPFLAGS = .*\)%\1 -DSKIP_PEER_VERIFICATION -DSKIP_HOSTNAME_VERIFICATION%g"\
			eIDClientCore/lib/eIDClientConnection/Makefile ;\
	make -C eIDClientCore install
