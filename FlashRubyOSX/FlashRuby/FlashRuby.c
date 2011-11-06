#include "FlashRuby.h"
#include <stdlib.h>
#include <stdio.h>

void FlashRubyContextEntryPoint(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet)
{
  *extDataToSet = NULL;
  *ctxInitializerToSet = &FlashRubyContextInitializer;
  *ctxFinalizerToSet = NULL;
}

void FlashRubyContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet)
{
  *numFunctionsToTest = 1;
  FRENamedFunction* funcs = (FRENamedFunction*)malloc(*numFunctionsToTest * sizeof(FRENamedFunction));
  
  funcs[0].name = (const uint8_t*)"eval";
  funcs[0].functionData = NULL;
  funcs[0].function = &FlashRuby_eval;
  
  *functionsToSet = funcs;
}

FLASH_METHOD(FlashRuby_eval)
{
  FREObject fo;
//  FRENewObjectFromUTF8(8, (const uint8_t*)"success", &fo);
//  RUBY_INIT_STACK;
  ruby_init();
  VALUE bytecode = rb_iseq_compile(rb_str_new_cstr("puts 'hello world'"), rb_str_new_cstr("fake.rb"), INT2FIX(1));
  VALUE bytecode_string = rb_inspect(bytecode);
  const char *result_string = StringValueCStr(bytecode_string);
//  VALUE hello_world = rb_usascii_str_new_cstr("hello world");
//  const char *result_string = StringValueCStr(hello_world);
  FRENewObjectFromUTF8((unsigned int)strlen(result_string), (const uint8_t*)result_string, &fo);
  return fo;
}