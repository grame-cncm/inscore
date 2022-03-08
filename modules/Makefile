
MAKE  ?= make

all:
	git submodule update --init --recursive
	git submodule foreach git checkout dev 
	git submodule foreach git pull origin dev 
	$(MAKE) -C guidolib/build CMAKEOPT="-DMIN=on -DMAKEFRAMEWORK=off" GENERATOR=""
	$(MAKE) -C libmusicxml/build minimal

guido:
	git submodule update --init --recursive
	$(MAKE) -C guidolib/build CMAKEOPT="-DMIN=on -DMAKEFRAMEWORK=off" GENERATOR=""

install:
	$(MAKE) -C guidolib/build install
	$(MAKE) -C libmusicxml/build install
