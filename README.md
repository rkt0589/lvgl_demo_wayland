# lvgl_demo_wayland

Simple Hello world program validated with wayland display driver and tested with Toradex module Apalis iMX6Q running Embedded Linux.

Yocto SDK is used to cross compile source. Makefile will fetch $(CC) from terminal, so it is required to first export Yocto SDK env. 


### Command:
```
. /opt/tdx-xwayland/5.2.0/environment-setup-armv7at2hf-neon-tdx-linux-gnueabi 

echo ${CC}
```

### Output:
```
arm-tdx-linux-gnueabi-gcc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/tdx-xwayland/5.2.0/sysroots/armv7at2hf-neon-tdx-linux-gnueabi
```

Run make. After successfull compilation you should see binary wayland_demo in build/binary folder

```
make
```

Copy binary to target device 

### on Host
```
scp build/binary/wayland_demo <user>@<ip_address_target>:<path_on_target>

ssh <user>@<ip_address_target>
```

### On Target

```
./wayland_demo
```

