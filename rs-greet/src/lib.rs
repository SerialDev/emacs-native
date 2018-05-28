extern crate libc;
#[macro_use]
extern crate emacs;

use emacs::{Env, CallEnv, Result, Value};

emacs_plugin_is_GPL_compatible!();
emacs_module_init!(init);

// const MODULE: &str = "greeting";
// lazy_static! {
//     static ref MODULE_PREFIX: String = format!("{}/", MODULE);
// }


fn init(env: &Env) -> Result<Value> {
    fn hello(env: &CallEnv) -> Result<Value> {
        let name: String = env.parse_arg(0)?;
        env.message(&format!("Hello twice, {}!", name))
    }

    emacs_export_functions! {
        env, "greeting-", {
            "say-hello" => (hello, 1..1)
        }
    }

    env.provide("greeting")
}

