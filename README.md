Lua Object Compiler
===================

---

~~ ! Work In Progress ! ~~

---

#### What is Lua Object Compiler (LOC)?

LOC is automated Lua wrapper generator for C++. It uses comment based annotations in your source code to quickly create complex Lua wrappers.

#### What do you mean by "comment based annotations"?

```cpp
//[namespace test]
namespace test {

//[class Foo]
class Foo
{
  public:
    //[ctor()]
    Foo();
    
    //[ctor(int)]
    Foo(int value);
    
    //[method void bar(int, int)]
    void bar(int x, int y);
    
    //[set(value) void setValue(int)]
    void setValue(int value);
    
    //[get(value) int value() const]
    int value() const { return _value; }
    
  private:
    int _value;
};

}

```
