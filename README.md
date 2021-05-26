# lvgl_demo_wayland

Simple Hello world program validated with wayland display driver.

Yocto SDK is used to cross compile source. Makefile will fetch $(CC) from terminal, so it is required to first export Yocto SDK env. 

Run below command to verify

### Command:
echo ${CC}

### Output:
arm-tdx-linux-gnueabi-gcc -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/tdx-xwayland/5.2.0/sysroots/armv7at2hf-neon-tdx-linux-gnueabi

Last issue make command in project directory. After suuceesfull compilation you should see binary wayland_demo in build.binary folder

Copy wayland_demo to target device 

scp build/binary/wayland_demo user@<ip_address_target>:<path_on_target>

ssh <user>@<ip_address_target>

./wayland_demo
