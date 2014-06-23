#pragma once

#include "Base.h"

namespace loc {

template <typename char_traits>
class BasicRefString
{
  public:
    // Declare standard types
    typedef typename char_traits::char_type value_type;
    typedef char_traits traits_type;
    typedef std::allocator<value_type> allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    BasicRefString()
      : _data(getEmptyData())
    {
    
    }

    BasicRefString(const_pointer str)
      : _data(new Data(str))
    {
      
    }

    BasicRefString(const std::basic_string<value_type> &str)
      : _data(new Data(str))
    {
    
    }

    BasicRefString(const BasicRefString &str)
      : _data(str._data)
    {
      _data->ref();
    }

    ~BasicRefString()
    {
      _data->unref();
    }

    void isolate()
    {
      if (_data->getNumReferences() > 1)
      {
        Data *newData = new Data(*_data);
        _data->unref();
        _data = newData;
      }
    }

    size_t size() const { return _data->string.size(); }

    size_t length() const { return size(); }

    pointer data() { isolate(); return _data->string.data(); }

    const_pointer data() const { return _data->string.data(); }

    const_pointer c_str() const { return _data->string.c_str(); }

    std::basic_string<value_type> stl_str() const { return std::basic_string<value_type>(_data); }

    bool empty() const { return _data->string.empty(); }

    reference operator[](size_type index) { isolate(); return _data->string[index]; }

    const_reference operator[](size_type index) const { return _data[index]; }
    
    operator const_pointer() const { return c_str(); }

    BasicRefString &operator=(const_pointer str)
    {
      _data->unref();
      _data = new Data(str);

      return *this;
    }

    BasicRefString &operator=(const std::basic_string<value_type> &str)
    {
      _data->unref();
      _data = new Data(str);

      return *this;
    }

    BasicRefString &operator=(const BasicRefString &str)
    {
      _data->unref();
      _data = str._data;
      _data->ref();

      return *this;
    }

    void clear()
    {
      _data->unref();
      _data = getEmptyData();
    }

    BasicRefString operator+(const_pointer str) const
    {
      std::basic_string<value_type> result = _data->string + str;
      return BasicRefString(result);
    }

    BasicRefString operator+(const std::basic_string<value_type> &str) const
    {
      std::basic_string<value_type> result = _data->string + str;
      return BasicRefString(result);
    }

    BasicRefString operator+(const BasicRefString &str) const
    {
      std::basic_string<value_type> result = _data->string + str._data->string;
      return BasicRefString(result);
    }

    BasicRefString substr(size_t pos = 0, size_t length = std::basic_string<value_type>::npos)
    {
      return BasicRefString(_data->string.substr(pos, length));
    }

    bool operator<(const_pointer str) const { return _data->string < str; }
    bool operator<(const std::basic_string<value_type> &str) const { return _data->string < str; }
    bool operator<(const BasicRefString &str) const { return _data->string < str._data->string; }

    bool operator<=(const_pointer str) const { return _data->string <= str; }
    bool operator<=(const std::basic_string<value_type> &str) const { return _data->string <= str; }
    bool operator<=(const BasicRefString &str) const { return _data->string <= str._data->string; }

    bool operator>(const_pointer str) const { return _data->string > str; }
    bool operator>(const std::basic_string<value_type> &str) const { return _data->string > str; }
    bool operator>(const BasicRefString &str) const { return _data->string > str._data->string; }

    bool operator>=(const_pointer str) const { return _data->string >= str; }
    bool operator>=(const std::basic_string<value_type> &str) const { return _data->string >= str; }
    bool operator>=(const BasicRefString &str) const { return _data->string >= str._data->string; }

    bool operator==(const_pointer str) const { return _data->string == str; }
    bool operator==(const std::basic_string<value_type> &str) const { return _data->string == str; }
    bool operator==(const BasicRefString &str) const { return _data->string == str._data->string; }

    bool operator!=(const_pointer str) const { return _data->string != str; }
    bool operator!=(const std::basic_string<value_type> &str) const { return _data->string != str; }
    bool operator!=(const BasicRefString &str) const { return _data->string != str._data->string; }
    
  private:
    struct Data
    {
      std::basic_string<value_type> string;

      Data()
        : string("")
      {
        refCount = 0;
        ref();
      }

      Data(const_pointer str)
        : string(str)
      {
        refCount = 0;
        ref();
      }

      Data(const std::basic_string<value_type> &str)
        : string(str)
      {
        refCount = 0;
        ref();
      }

      Data(const Data &copy)
        : string(copy.string)
      {
        refCount = 0;
        ref();
      }

      void ref() const
      {
        ++refCount;
      }

      void unref() const
      {
        if ((--refCount) <= 0)
          delete this;
      }

      int getNumReferences() const { return refCount; }

    private:
      mutable int refCount;

      ~Data()
      {
      
      }
    };

    static Data *getEmptyData()
    {
      static Data *empty;

      if (!empty)
        empty = new Data();

      empty->ref();
      return empty;
    }

    Data *_data;
};

typedef BasicRefString<std::char_traits<char>> RefString;
typedef BasicRefString<std::char_traits<wchar_t>> RefWString;

template <typename char_traits>
class BasicRefStringPool
{
  public:
    // Declare standard types
    typedef typename char_traits::char_type value_type;
    typedef char_traits traits_type;
    typedef std::allocator<value_type> allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    typedef BasicRefString<char_traits> String;

    typedef std::map<String, bool> StringMap;

    StringMap &getStringMap() { return _map; }

    const StringMap &getStringMap() const { return _map; }

    String create(const_pointer str)
    {
      StringMap::iterator iter = _map.find(str);
      if (iter != _map.end())
        return iter->first;

      String result = str;
      _map[result] = true;
      return result;
    }

    String create(const std::basic_string<value_type> &str)
    {
      StringMap::iterator iter = _map.find(str);
      if (iter != _map.end())
        return iter->first;

      String result = str;
      _map[result] = true;
      return result;
    }

    String create(const String &str)
    {
      StringMap::iterator iter = _map.find(str);
      if (iter != _map.end())
        return iter->first;

      _map[str] = true;
      return str;
    }

  private:
    StringMap _map;
};

typedef BasicRefStringPool<std::char_traits<char>> RefStringPool;
typedef BasicRefStringPool<std::char_traits<wchar_t>> RefWStringPool;

}
