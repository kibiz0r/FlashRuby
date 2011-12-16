#ifndef FLASH_RUBY_H
#define FLASH_RUBY_H

#include "FlashRuntimeExtensions.h"
#include "ruby.h"
#include "internal.h"
#include "vm_core.h"

void FlashRubyContextEntryPoint(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet);
void FlashRubyContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet);

FREObject FlashRuby_eval(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);

#endif