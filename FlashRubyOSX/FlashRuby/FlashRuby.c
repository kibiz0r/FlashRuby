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
  FRENewObjectFromUTF8(8, (const uint8_t*)"success", &fo);
  return fo;
}