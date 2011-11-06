#ifndef FLASH_RUBY_H
#define FLASH_RUBY_H

#include "FlashRuntimeExtensions.h"

#define FLASH_METHOD(name) \
  FREObject (name)(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])

void FlashRubyContextEntryPoint(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet);
void FlashRubyContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet);

FLASH_METHOD(FlashRuby_eval);

#endif