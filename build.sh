export GENDEV=/opt/toolchains/gen
PATH=$GENDEV/bin:$GENDEV/m68k-elf/bin:$PATH

make -f $GENDEV/skeleton/Makefile
