#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
/**
 * 基类
 */
class Object
{
public:
    Object();
    virtual ~Object(){};
    static bool Register(class ClassInfo * classInfo);
    static Object * CreateObject(string name);
};

using ObjectContructFn = Object* (*)(void);

class ClassInfo
{
public:
    ClassInfo(const string name , ObjectContructFn ctor) :ClassName(name),MyObjectContructor(ctor)
    {
        Object::Register(this); //注入到Object中
    }
    virtual ~ClassInfo(){};
    Object * CreateObject()const
    {
        return (MyObjectContructor());
    }
    const string GetClassName()const { return ClassName;}
    ObjectContructFn GetContruct()const {return MyObjectContructor;}

private:
    string ClassName;
    ObjectContructFn  MyObjectContructor;
};

class DerivedObject : public Object
{
public:
    DerivedObject(){};

    void printTest(){cout<<"Helo world!"<<endl;}
    virtual  ~DerivedObject(){};

    ClassInfo *GetClassInfo() const { return &MyClassInfo; }

    //为什么需要一个静态函数，是因为静态函数有返回值，相对构造函数没有那么特殊，是个非常正常的函数
    static Object* CreateObject()
    {
        return new DerivedObject;
    }

protected:
    static ClassInfo  MyClassInfo;
};

static unordered_map<string , ClassInfo *> * ClassMap  = nullptr;

bool Object::Register(class ClassInfo *classInfo)
{
    if(!ClassMap)
    {
        ClassMap = new unordered_map<string,ClassInfo *>();
    }

    if(classInfo)
    {
        string c_name = classInfo->GetClassName();
        if(ClassMap->find(c_name) == ClassMap->end())//没有注册过
        {
            (*ClassMap)[c_name] = classInfo;
        }
        return true;
    }
    return false;

}

Object* Object::CreateObject(string name)
{
    if(ClassMap->find(name)!=ClassMap->end())
    {
       return  (*ClassMap)[name]->CreateObject();
    }

    return nullptr;
}

ClassInfo DerivedObject::MyClassInfo("DerivedObject",DerivedObject::CreateObject);

int main(int argc,  char ** argv)
{

    Object * obj = Object::CreateObject("DerivedObject");


    return 0;
}
