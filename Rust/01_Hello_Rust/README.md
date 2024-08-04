# Hello Rust 🦀

This is just a simple Hello World Linux kernel Module written in Rust 🦀<br>

Inspiration taken from https://discourse.ubuntu.com/t/ubuntu-kernel-is-getting-rusty-in-lunar/<br> 

The following part in installation was different as compared to the original post (I am using Ubuntu 24.04 for this)

```
sudo apt install rustc rust-src rustfmt \
bindgen llvm clang gcc make \   
linux-lib-rust-`uname -r` \
linux-headers-`uname -r`
```

Also the rust_flags in Makefile were adjusted accordingly (The library folder (RUST_LIB_SRC) might vary in your case)
 ```
 rust_flags = CROSS_COMPILE=x86_64-linux-gnu- HOSTRUSTC=rustc RUSTC=rustc BINDGEN=bindgen RUSTFMT=rustfmt RUST_LIB_SRC=/usr/src/rustc-1.75.0/library
 ```