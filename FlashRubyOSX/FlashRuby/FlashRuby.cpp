#include "FlashRuby.h"
#include <stdlib.h>
#include <stdio.h>
#include "ruby.h"
#include "environment.hpp"
#include "builtin/object.hpp"
#include "builtin/class.hpp"
#include "builtin/string.hpp"
#include "builtin/array.hpp"

rubinius::Environment* environment = NULL;

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

FREObject FlashRuby_init_vm(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
{
  const char* args[] = { "/Users/kibiyama/git/flashruby/rubinius/bin/rbx" };
  environment = new rubinius::Environment(1, (char**)args);
  //environment->setup_cpp_terminate();
  environment->run_from_filesystem();
  rubinius::State* state = environment->state;
  rubinius::Object* main = G(main);
  rubinius::Array* argArray = rubinius::Array::create(state, 1);
  argArray->append(state, rubinius::String::create(state, "/Users/kibiyama/git/flashruby/FlashRubyHost/bin-debug/foobar.rb"));
  bool responds = main->respond_to(state, state->symbol("require"), NULL)->true_p();
  rubinius::Object* resultObject = main->send(state, NULL, state->symbol("require"), argArray);
  const char* result = resultObject->to_s(state)->c_str(state);
  return NULL;
}