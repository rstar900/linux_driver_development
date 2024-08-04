// Inspiration taken from https://discourse.ubuntu.com/t/ubuntu-kernel-is-getting-rusty-in-lunar/

use kernel::prelude::*;

module! {
    type: HelloLDDRust,
    name: "hello_rust",
    author: "Rachit Garg",
    description: "Hello World example for LDD in Rust",
    license: "GPL",
}

struct HelloLDDRust {

}

impl kernel::Module for HelloLDDRust {
    // Called on initialisation of module (after insmod)
    fn init(_module: &'static ThisModule) -> Result<Self> {
        pr_info!("Hello LDD world from Rust 😉\n");
        Ok(HelloLDDRust{})
    }
}

impl Drop for HelloLDDRust {
    // Called on removal of module (rmmod)
    fn drop(&mut self) {
        pr_info!("Good Bye from Rust Kernel Module 🫡\n");
    }
}