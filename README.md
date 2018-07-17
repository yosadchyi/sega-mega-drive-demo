# Very simple demo for Sega Mega Drive using SGDK

This project uses SGDK and shows how to create simple "game" where hero can move left and right and can even JUMP!

## Installation instructions

Edit `build.sh` by value of `GENDEV` environment variable to point to place where you have installed SGDK.

```
export GENDEV=/opt/toolchains/gen
```

Start build process by running `build.sh` once compilation succeed you should see `out.bin` file.
That's ROM image which can be used with various emulators. You can use OpenEMU to download engine for Sega Mega Drive.  

Now use left/right to move and "A" for jumping. Enjoy!
