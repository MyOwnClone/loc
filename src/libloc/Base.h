#pragma once

#pragma warning(disable: 4251)

#if defined(LIBLOC_BUILD_SHARED)
#define LIBLOC_EXPORT __declspec(dllexport)
#else
#define LIBLOC_EXPORT
#endif

#include <memory>
#include <map>

#include "StringUtils.h"
#include "RefString.h"

namespace loc {

}
