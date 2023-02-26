//
// Created by hangedfish (bravohangedman@outlook.com) on 2023/2/26.
//

#pragma once

#include <cstdint>

using Il2CppChar = char16_t;
using Il2CppMemoryCallbacks = void;
using Il2CppImage = void;
using Il2CppDomain = void;
using Il2CppException = void;
using Il2CppMethodPointer = void*;
using il2cpp_register_object_callback = void*;
using il2cpp_liveness_reallocate_callback = void*;
using Il2CppBacktraceFunc = void*;
using Il2CppFrameWalkFunc = void*;
using Il2CppSetFindPlugInCallback = void*;
using Il2CppLogCallback = void*;
using Il2CppClass = void;
using Il2CppObject = void;
using Il2CppString = void;
using Il2CppThread = void;
using Il2CppType = void;
using Il2CppArray = void;
using FieldInfo = void;
using MethodInfo = void;
using Il2CppAssembly = void;
using Il2CppReflectionType = void;
using Il2CppReflectionMethod = void;
using EventInfo = void;
using il2cpp_array_size_t = uintptr_t;
using PropertyInfo = void;
using Il2CppStackFrameInfo = void;
using Il2CppManagedMemorySnapshot = void;
using Il2CppDebuggerTransport = void;
using Il2CppMethodDebugInfo = void;
using Il2CppCustomAttrInfo = void;

using Il2CppRuntimeUnhandledExceptionPolicy = int;
using Il2CppStat = int;
using Il2CppGCMode = int;

#if defined(__cplusplus)
extern "C"
{
#endif // __cplusplus
#define DO_API(r, n, p)             r n p;
//#define DO_API_NO_RETURN(r, n, p)   [[noreturn]] r n p;

#include "il2cpp-api-functions.h"

#undef DO_API
#undef DO_API_NO_RETURN
#if defined(__cplusplus)
}
#endif // __cplusplus
