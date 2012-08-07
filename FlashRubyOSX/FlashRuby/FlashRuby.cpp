#include "FlashRuby.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "ruby.h"
#include "environment.hpp"
#include "vm/on_stack.hpp"
#include "builtin/object.hpp"
#include "builtin/class.hpp"
#include "builtin/string.hpp"
#include "builtin/symbol.hpp"
#include "builtin/array.hpp"
#include "builtin/system.hpp"
#include "builtin/exception.hpp"
#include "builtin/constantscope.hpp"

rubinius::Environment* environment = NULL;

extern "C" {
  int ffi_stat(const char *path, struct stat *buf);
  char* crypt(register const char *key, register const char *setting);

}

void FlashRubyContextEntryPoint(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet)
{
  *extDataToSet = NULL;
  *ctxInitializerToSet = &FlashRubyContextInitializer;
  *ctxFinalizerToSet = NULL;
}

void FlashRubyContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet)
{
  *numFunctionsToTest = 2;
  FRENamedFunction* funcs = (FRENamedFunction*)malloc(*numFunctionsToTest * sizeof(FRENamedFunction));
  
  funcs[0].name = (const uint8_t*)"eval";
  funcs[0].functionData = NULL;
  funcs[0].function = &FlashRuby_eval;
  
  funcs[1].name = (const uint8_t*)"init_vm";
  funcs[1].functionData = NULL;
  funcs[1].function = &FlashRuby_init_vm;
  
  *functionsToSet = funcs;
}

FREObject FlashRuby_eval(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
{
  FREObject arr;
  FRENewObject((const uint8_t*)"Array", 0, NULL, &arr, NULL);
  return arr;
}

/*extern "C" {
  int ffi_stat(const char *path, struct stat *buf);
}*/

FREObject FlashRuby_init_vm(FREContext ctx, void* funcData, uint32_t _argc, FREObject _argv[])
{
  int argc = 1;
  char* argv[] = { "/Users/kibiyama/git/flashruby2/rubinius/bin/rbx" };
  environment = new rubinius::Environment(1, (char**)argv);
  rubinius::State* state = environment->state;
  
  
  int i = 0;
  state->vm()->set_root_stack(reinterpret_cast<uintptr_t>(&i),
                              rubinius::VM::cStackDepthMax);
  
  std::string runtime = environment->system_prefix() + RBX_RUNTIME_PATH;
  
  environment->load_platform_conf(runtime);
  environment->load_vm_options(argc, argv);
  environment->boot_vm();
  environment->load_argv(argc, argv);
  
  state->vm()->initialize_config();
  
  environment->load_tool(); // ?
  
  runtime += "/19";
  G(rubinius)->set_const(state, "RUNTIME_PATH", rubinius::String::create(state,
                                                               runtime.c_str(), runtime.size()));
  
  environment->load_kernel(runtime);
  
  // start_signals();
  environment->run_file(runtime + "/loader.rbc");
  
  state->vm()->thread_state()->clear();
  
  rubinius::Object* loader = G(rubinius)->get_const(state, state->symbol("Loader"));
  if(loader->nil_p()) {
    std::cout << "Unable to find loader!\n";
    exit(127);
  }
  
  rubinius::OnStack<1> os(state, loader);
  
  rubinius::Object* inst = loader->send(state, 0, state->symbol("new"));
  
  rubinius::OnStack<1> os2(state, inst);
  
  inst->send(state, 0, state->symbol("preamble"));
  inst->send(state, 0, state->symbol("system_load_path"));
  inst->send(state, 0, state->symbol("signals"));
  inst->send(state, 0, state->symbol("load_compiler"));
  //inst->send(state, 0, state->symbol("preload"));
  //inst->send(state, 0, state->symbol("detect_alias"));
  //inst->send(state, 0, state->symbol("options"));
  //inst->send(state, 0, state->symbol("load_paths"));
  //inst->send(state, 0, state->symbol("debugger"));
  //inst->send(state, 0, state->symbol("rubygems"));
  //inst->send(state, 0, state->symbol("gemfile"));
  //inst->send(state, 0, state->symbol("requires"));
  //inst->send(state, 0, state->symbol("evals"));
  //inst->send(state, 0, state->symbol("script"));
  

  int (*baz)(const char *, struct stat *) = ffi_stat;
  char* (*baz2)(const char*, const char*) = crypt;
//  void* foo = dlopen(RTLD_SELF, RTLD_NOW | RTLD_GLOBAL);
  //void* bar = dlsym(foo, "ffi_stat");
//  void* bar = dlsym(foo, "FREGetContextNativeData");
  void* bar = dlsym(RTLD_SELF, "ffi_stat");
//  void* bar2 = dlsym(foo, "_ffi_stat");
  const char* err = dlerror();
  
  
  //rubinius::Exception* exception1 = state->thread_state()->current_exception();
//  const char* message1 = exception1->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  rubinius::Object* code_loader = G(rubinius)->get_const(state, "CodeLoader");
  rubinius::Object* code_loader_inst = loader->send(state, NULL, state->symbol("new"));
  bool success = code_loader_inst->send(state, NULL, state->symbol("require"))->true_p();
  rubinius::Exception* exception3 = state->thread_state()->current_exception();
  const char* message3 = exception3->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  rubinius::Object* kernel = G(object)->get_const(state, "Kernel");
  rubinius::Array* require_args = rubinius::Array::create(state, 1);
  require_args->append(state, rubinius::String::create(state, "/Users/kibiyama/git/flashruby2/foobar.rb"));
  bool require = kernel->respond_to_public(state, state->symbol("require"));
  rubinius::Object* result = kernel->send(state, NULL, state->symbol("require"), require_args);
  bool is_true = result->true_p();
  
  
  //environment->load_kernel("/Users/kibiyama/git/flashruby2/rubinius/runtime/19");
  //environment->run_file("/Users/kibiyama/git/flashruby2/rubinius/runtime/19/loader.rbc");
  //environment->run_from_filesystem();
  
  /*rubinius::Object* main = G(main);
  
  rubinius::Array* class_variable_get_args = rubinius::Array::create(state, 1);
  class_variable_get_args->append(state, state->symbol("Kernel"));
  rubinius::Object* kernel = G(constantscope)->send(state, NULL, state->symbol("class_variable_get"), class_variable_get_args);
  bool eval_available = kernel->respond_to(state, state->symbol("eval"), NULL)->true_p();
  
  rubinius::Array* argArray = rubinius::Array::create(state, 1);
  argArray->append(state, rubinius::String::create(state, "/Users/kibiyama/git/flashruby/FlashRubyHost/bin-debug/foobar.rb"));
  bool responds = main->respond_to(state, state->symbol("require"), NULL)->true_p();
  rubinius::Object* resultObject = main->send(state, NULL, state->symbol("require"), argArray);
  const char* result = resultObject->to_s(state)->c_str(state);*/
  return NULL;
}