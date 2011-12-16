#include "FlashRuby.h"
#include "insns_info.inc"
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

FREObject FlashRuby_eval(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
{
//  FRENewObjectFromUTF8(8, (const uint8_t*)"success", &fo);
//  RUBY_INIT_STACK;
  ruby_init();
  VALUE rb_bytecode = rb_iseq_compile(rb_str_new_cstr("puts 'hello world'"), rb_str_new_cstr("fake.rb"), INT2FIX(1));
  
  rb_iseq_t *iseqdata;
  GetISeqPtr(rb_bytecode, iseqdata);
  VALUE *iseq = iseqdata->iseq;
  unsigned long size = iseqdata->iseq_size;
  
  FREObject arr;
  FRENewObject((const uint8_t*)"Array", 0, NULL, &arr, NULL);
  
  for (unsigned long i = 0; i < size;)
  {
    VALUE insn = iseq[i];
    int len = insn_len(insn);
    i += len;
    const char *name = insn_name(insn);
    const char *types = insn_op_types(insn);
    FREObject instruction_array;
    FRENewObject((const uint8_t*)"Array", 0, NULL, &instruction_array, NULL);
    FRESetArrayLength(instruction_array, len);
    for (int j = 0; types[j]; j++)
    {
      VALUE operand = insn_operand_intern(iseqdata, insn, j, iseq[i + j + 1], len, i, &iseq[i + j + 2], NULL);
      FREObject str;
      FRENewObjectFromUTF8(RSTRING_LEN(operand), (const uint8_t*)StringValuePtr(operand), &str);
      FRESetArrayElementAt(instruction_array, j, str);
    }
    FRECallObjectMethod(arr, (const uint8_t*)"push", 1, &instruction_array, NULL, NULL);
  }
  return arr;
  
  VALUE rb_disasm = rb_iseq_disasm(rb_bytecode);
  FREObject str;
  FRENewObjectFromUTF8(RSTRING_LEN(rb_disasm), (const uint8_t*)StringValuePtr(rb_disasm), &str);
  return str;
  
  
  
  VALUE rb_bytecode_array = rb_funcall(rb_bytecode, rb_intern("to_a"), 0);
  
  VALUE rb_instructions_array = rb_ary_entry(rb_bytecode_array, RARRAY_LEN(rb_bytecode_array) - 1);
  rb_instructions_array = rb_ary_subseq(rb_instructions_array, 1, RARRAY_LEN(rb_instructions_array) - 1);
  int rb_instructions_array_length = RARRAY_LEN(rb_instructions_array);
  
  FREObject as_instructions_array;
  FRENewObject((const uint8_t*)"Array", 0, NULL, &as_instructions_array, NULL);
  FRESetArrayLength(as_instructions_array, rb_instructions_array_length);
  
  for (int i = 0; i < rb_instructions_array_length; i++)
  {
    VALUE rb_instruction = rb_ary_entry(rb_instructions_array, i); // [:putstring, "hello world"]
    VALUE rb_instruction_inspect = rb_inspect(rb_instruction);
    const char *rb_instruction_inspect_string = StringValuePtr(rb_instruction_inspect);
    
    FREObject as_instruction;
    FRENewObjectFromUTF8(RSTRING_LEN(rb_instruction_inspect), (const uint8_t *)rb_instruction_inspect_string, &as_instruction);
    FRESetArrayElementAt(as_instructions_array, i, as_instruction);
    /*FRENewObject((const uint8_t*)"Array", 0, NULL, &as_instruction, NULL);
    int rb_instruction_length = RARRAY_LEN(rb_instruction);
    FRESetArrayLength(as_instruction, rb_instruction_length);
    for (int j = 0; j < RARRAY_LEN(rb_instruction); j++)
    {
      FREObject instruction_component;
      VALUE rb_instruction_component = rb_ary_entry(rb_instruction, j);
      VALUE rb_instruction_component_string = rb_inspect(rb_instruction_component);
      const char *str = StringValueCStr(rb_instruction_component_string);
      FRENewObjectFromUTF8(sizeof(str), (const uint8_t*)str, &instruction_component);
      FRESetArrayElementAt(as_instruction, j, instruction_component);
    }
    FRESetArrayElementAt(instructions, i, as_instruction);*/
  }
  return as_instructions_array;
//  VALUE bytecode_string = rb_inspect(bytecode_array);
//  const char *result_string = StringValueCStr(bytecode_string);
//  VALUE hello_world = rb_usascii_str_new_cstr("hello world");
//  const char *result_string = StringValueCStr(hello_world);
//  FRENewObjectFromUTF8((unsigned int)strlen(result_string), (const uint8_t*)result_string, &fo);
//  return fo;
}