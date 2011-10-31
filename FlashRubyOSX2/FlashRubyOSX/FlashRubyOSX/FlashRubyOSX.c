/*
 *  FlashRubyOSX.cp
 *  FlashRubyOSX
 *
 *  Created by Michael Harrington on 10/31/11.
 *  Copyright 2011 Atomic Object. All rights reserved.
 *
 */

#include <stdio.h>
#include "FlashRubyOSX.h"

void FlashRubyInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, 
                          FREContextFinalizer* ctxFinalizerToSet);

void ContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, 
                        uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet);

void ContextFinalizer(FREContext ctx);

void FlashRubyInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, 
                           FREContextFinalizer* ctxFinalizerToSet)
{
  *extDataToSet = NULL;
  *ctxInitializerToSet = ContextInitializer;
  *ctxFinalizerToSet = ContextFinalizer;
}

void ContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, 
                        uint32_t* numFunctionsToTest, const FRENamedFunction** functionsToSet)
{
  
}

void ContextFinalizer(FREContext ctx)
{
  
}