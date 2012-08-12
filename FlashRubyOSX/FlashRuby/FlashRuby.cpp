#include "FlashRuby.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "ruby.h"
#include "environment.hpp"
#include "vm.hpp"
#include "on_stack.hpp"
#include "call_frame.hpp"
#include "builtin/object.hpp"
#include "builtin/class.hpp"
#include "builtin/string.hpp"
#include "builtin/symbol.hpp"
#include "builtin/array.hpp"
#include "builtin/system.hpp"
#include "builtin/exception.hpp"
#include "builtin/thread.hpp"
#include "builtin/nativemethod.hpp"
#include "builtin/constantscope.hpp"
#include "builtin/compiledmethod.hpp"

using namespace rubinius;

Environment* environment = NULL;
State* state = NULL;

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
  uint32_t length = 0;
  const uint8_t* fl_str = NULL;
  FREGetObjectAsUTF8(argv[0], &length, &fl_str);
  
  
  
  
  
  InterpreterCallFrame* frame = ALLOCA_CALLFRAME(0);
  frame->prepare(0);
  frame->previous = NULL;
  frame->dispatch_data = NULL;
  frame->flags = 0;
  
  CompiledMethod* cm = CompiledMethod::create(state);
  cm->metadata(state, state->symbol("__script__"));
  cm->name(state, state->symbol("__script__"));
  frame->cm = cm;
  
  StackVariables* scope = ALLOCA_STACKVARIABLES(0);
  scope->initialize(G(main), cNil, G(object), 0);
  scope->on_heap_ = VariableScope::synthesize(state, cm, G(object), cNil, G(main), cNil, state->new_object<Tuple>(G(tuple)));
  frame->scope = scope;
  
  Arguments* arguments = new Arguments(state->symbol("script"), G(main), cNil, 0, 0);
  frame->arguments = arguments;
  
  state->set_call_frame(frame);
  
  
  
  
  String* str = String::create(state, (const char*)fl_str);
  Array* eval_args = Array::create(state, 1);
  eval_args->append(state, str);
  
  
  Object* result_obj = G(main)->send(state, frame, state->symbol("instance_eval"), eval_args);
  const char* result_c_str = result_obj->to_s(state)->c_str_null_safe(state);

  
  FREObject result_str;
  FRENewObjectFromUTF8(strlen(result_c_str), (const uint8_t*)result_c_str, &result_str);
  return result_str;
}

FREObject FlashRuby_init_vm(FREContext ctx, void* funcData, uint32_t _argc, FREObject _argv[])
{
  int argc = 1;
  char* argv[] = { "/Users/kibiyama/git/flashruby/rubinius/bin/rbx" };
  environment = new rubinius::Environment(1, (char**)argv);
  state = environment->state;
  
  
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
  
  environment->run_file(runtime + "/loader.rbc");
  
  rubinius::Exception* exception1 = state->thread_state()->current_exception();
  const char* message1 = exception1->nil_p() ? NULL : exception1->message_c_str(state);
  const char* trace1 = exception1->nil_p() ? NULL : exception1->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  state->vm()->thread_state()->clear();
  
  rubinius::Exception* exception2 = state->thread_state()->current_exception();
  const char* message2 = exception2->nil_p() ? NULL : exception2->message_c_str(state);
  const char* trace2 = exception2->nil_p() ? NULL : exception2->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  rubinius::Object* loader = G(rubinius)->get_const(state, state->symbol("Loader"));
  if(loader->nil_p()) {
    std::cout << "Unable to find loader!\n";
    exit(127);
  }
  
  rubinius::Exception* exception3 = state->thread_state()->current_exception();
  const char* message3 = exception3->nil_p() ? NULL : exception3->message_c_str(state);
  const char* trace3 = exception3->nil_p() ? NULL : exception3->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  rubinius::OnStack<1> os(state, loader);
  
  rubinius::Object* inst = loader->send(state, 0, state->symbol("new"));
  
  rubinius::OnStack<1> os2(state, inst);
  
  rubinius::Exception* exception4 = state->thread_state()->current_exception();
  const char* message4 = exception4->nil_p() ? NULL : exception4->message_c_str(state);
  const char* trace4 = exception4->nil_p() ? NULL : exception4->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  inst->send(state, 0, state->symbol("preamble"));
  inst->send(state, 0, state->symbol("system_load_path"));
  inst->send(state, 0, state->symbol("signals"));
  inst->send(state, 0, state->symbol("load_compiler"));
  
  rubinius::Exception* exception5 = state->thread_state()->current_exception();
  const char* message5 = exception5->nil_p() ? NULL : exception5->message_c_str(state);
  const char* trace5 = exception5->nil_p() ? NULL : exception5->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);
  
  rubinius::Exception* exception6 = state->thread_state()->current_exception();
  const char* message6 = exception6->nil_p() ? NULL : exception6->message_c_str(state);
  const char* trace6 = exception6->nil_p() ? NULL : exception6->send(state, NULL, state->symbol("backtrace"))->send(state, NULL, state->symbol("inspect"))->to_s(state)->c_str(state);

  return NULL;
}