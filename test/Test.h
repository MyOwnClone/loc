//[namespace test]
namespace test {

//[class Foo]
class Foo
{
  public:
    //[ctor()]
    Foo();
    
    virtual ~Foo();
    
    //[method int bar(int, int) const]
    int bar(int x, int y) const;
};

}
