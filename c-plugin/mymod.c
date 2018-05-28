#include <emacs-module.h>
#include <stdlib.h>

/* Declare mandatory GPL symbol.  */

int plugin_is_GPL_compatible;
extern emacs_value el_nil, el_t;

/* New emacs lisp function. All function exposed to Emacs must have this prototype. */
static emacs_value
Fmymod_test (emacs_env *env, int nargs, emacs_value args[], void *data)
{
  return env->make_integer (env, 42);
}

// char *
// copy_lisp_string(emacs_env *env, emacs_value s_val)
// {
//   ptrdiff_t len = 0;
//   env->copy_string_contents(env, s_val, NULL, &len);
//   if (env->non_local_exit_check(env)) return NULL;

//   char *c_str = malloc(len);
//   bool ok = env->copy_string_contents(env, s_val, c_str, &len);
//   if (!ok || env->non_local_exit_check(env)) {
//     free(c_str);
//     return NULL;
//   }

//   return c_str;
// }


// static emacs_value
// Floopy (emacs_env *env, int nargs, emacs_value args[], void *data)
// {

//     char *payload;
//     if (!(payload = copy_lisp_string(env, args[1]))) {
//         payload = "Failed";
//     }
//     // ptrdiff_t len = 0;

//     return env->make_string (env, payload, 10);
// }

/* Bind NAME to FUN.  */
static void
bind_function (emacs_env *env, const char *name, emacs_value Sfun)
{
  /* Set the function cell of the symbol named NAME to SFUN using
     the 'fset' function.  */

  /* Convert the strings to symbols by interning them */
  emacs_value Qfset = env->intern (env, "fset");
  emacs_value Qsym = env->intern (env, name);

  /* Prepare the arguments array */
  emacs_value args[] = { Qsym, Sfun };

  /* Make the call (2 == nb of arguments) */
  env->funcall (env, Qfset, 2, args);
}

/* Provide FEATURE to Emacs.  */
static void
provide (emacs_env *env, const char *feature)
{
  /* call 'provide' with FEATURE converted to a symbol */

  emacs_value Qfeat = env->intern (env, feature);
  emacs_value Qprovide = env->intern (env, "provide");
  emacs_value args[] = { Qfeat };

  env->funcall (env, Qprovide, 1, args);
}

int
emacs_module_init (struct emacs_runtime *ert)
{
  emacs_env *env = ert->get_environment (ert);

  /* create a lambda (returns an emacs_value) */
  emacs_value fun = env->make_function (env,
              0,            /* min. number of arguments */
              0,            /* max. number of arguments */
              Fmymod_test,  /* actual function pointer */
              "doc",        /* docstring */
              NULL          /* user pointer of your choice (data param in Fmymod_test) */
  );

  // emacs_value fun_2 = env->make_function (env,
  //             0,            /* min. number of arguments */
  //             1,            /* max. number of arguments */
  //             Floopy,  /* actual function pointer */
  //             "doc",        /* docstring */
  //             NULL          /* user pointer of your choice (data param in Fmymod_test) */
  // );

  bind_function (env, "mymod-test", fun);
  // bind_function (env, "loopy-test", fun_2);
  provide (env, "mymod");

  
  /* loaded successfully */
  return 0;
}
