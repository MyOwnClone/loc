#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

#include <string>

namespace liblocCLR {

class MarshalString
{
  public:
    MarshalString(String ^str)
    {
      _ptr = Marshal::StringToHGlobalAnsi(str);
      _string = static_cast<char *>(_ptr.ToPointer());
    }

    ~MarshalString()
    {
      Marshal::FreeHGlobal(_ptr);
    }

    const char *c_str() const { return _string.c_str(); }

    std::string &stl_str() { return _string; }

    const std::string &stl_str() const { return _string; }

    operator const char *() const { return c_str(); }

    size_t size() const { return _string.size(); }

    size_t length() const { return size(); }

    bool empty() const { return _string.empty(); }

  private:
    IntPtr _ptr;

    std::string _string;
};

}
