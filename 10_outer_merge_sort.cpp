

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


// 归并排序分三步走
// 用 stringstream 内存字符串模拟文件

void merge1(ostream & fp,istream & fp1,istream & fp2)
{
    char p1 = 0;
    char p2 = 0;
    
    // 三步走 1. 耗尽其一
    fp1.get(p1);
    fp2.get(p2);
    for (; !fp1.fail() && !fp2.fail();)
    {
        if (p1<=p2)
        {
            fp.put(p1);
            fp1.get(p1);
        }
        else
        {
            fp.put(p2);
            fp2.get(p2); // get 有没有成功，看 for 判断
        }
    }


    // 三步走 2. 捡起第一步中漏掉的
    if(!fp1.fail())
    {
        fp.put(p1);
    }
    if (!fp2.fail())
    {
        fp.put(p2);
    }

    // 三步走 3. 把剩下的都耗尽
    for (;fp1.get(p1);)
    {
        fp.put(p1);
    }
    
    for (;fp2.get(p2);)
    {
        fp.put(p2);
    }
}


void merge2_error(ostream & fp,istream & fp1,istream & fp2)
{
    char p1 = 0;
    char p2 = 0;
    
    fp1>>p1;
    fp2>>p2;
    
    // 流输入有没有成功 >> , 要看接下来的 eof() 
    for (;!fp1.eof() && !fp2.eof();)
    {
        if (p1<=p2)
        {
            fp.put(p1);
            fp1>>p1;
        }
        else
        {
            fp.put(p2);
            fp2>>p2;
        }
    }

    for (;!fp1.eof();)
    {
        fp1>>p1;
        fp.put(p1);
    }

    for (;!fp2.eof();)
    {
        fp2>>p2;
        fp.put(p2);
    }
}

void merge2_fix(ostream & fp,istream & fp1,istream & fp2)
{
    // 分 3 步走
    char p1 = 0;
    char p2 = 0;
    
    fp1>>p1;
    fp2>>p2;

    //1. 先把两个中的一个耗尽

    // 流输入有没有成功 >> , 要看接下来的 eof() 
    for (;!fp1.eof() && !fp2.eof();)
    {
        if (p1<=p2)
        {
            fp.put(p1);
            fp1>>p1;
        }
        else
        {
            fp.put(p2);
            fp2>>p2;
        }
    }

    // 2. 耗尽其中一个后，把上面已经获取到的捡漏
    if (!fp1.eof())
    {
        fp.put(p1);
    }
    if(!fp2.eof())
    {
        fp.put(p2);
    }


    // 3. 把还没耗尽的都耗尽
    for (;fp1>>p1;)
    {
        fp.put(p1);
    }

    for (;;)
    {
        // 两种判断结束的方法
        fp2>>p2;
        if (fp2.eof())
        {
            break;
        }
        fp.put(p2);
    }
}

// 用 eof() 不理想
void test_eof()
{
    cout<<"test_eof:"<<endl;
    std::stringstream s("123");

    char c = 0;

    for (;!s.eof();)
    {
        s>>c;
        cout<<c<<" ";
    }
    cout<<endl;
    // output: 1 2 3 3
}

void test_good()
{
    cout<<"test_good:"<<endl;
    std::stringstream s("123");

    char c = 0;

    for (;s.good();)
    {
        s>>c;
        cout<<c<<" ";
    }
    cout<<endl;
    // output: 1 2 3 3
}

void test_get()
{
    cout<<"test_get:"<<endl;
    std::stringstream s("123");

    char c = 0;


    // 这句会有强制转换，调试发现会调用方法
    // operator void *() const
    // {	// test if any stream operation has failed
    //    return (fail() ? 0 : (void *)this);
    // }
    for (;s.get(c);)
    {
        cout<<c<<" ";
    }
    cout<<endl;
    // output : 1 2 3
}

void test_fail()
{
    cout<<"test_fail:"<<endl;
    std::stringstream s("123");

    char c = 0;
    for (;!s.fail();)
    {
        s>>c;
        cout<<c<<" ";
    }
    cout<<endl;
    // output : 1 2 3 3
}

// 不能使用，死循环
void test_bad()
{
    cout<<"test_bad:"<<endl;
    std::stringstream s("123");

    char c = 0;
    for (;!s.bad();)
    {
        s>>c;
        cout<<c<<" ";
    }
    cout<<endl;
    // output : infinit loop 1 2 3 3 3 3 ....
}


void test_merge(const char * s1, const char * s2, void (*func_merge)(ostream & fp,istream & fp1,istream & fp2))
{
    std::stringstream _s1(s1);
    std::stringstream _s2(s2);
    std::stringstream _s;
    func_merge(_s,_s1,_s2);
    cout<<"\t"<<_s1.str() << " + "<<_s2.str() << " = "<< _s.str()<<endl;
}


void test_merge(void (*func_merge)(ostream & fp,istream & fp1,istream & fp2))
{
    test_merge("135","",func_merge);
    test_merge("135","2",func_merge);
    test_merge("135","24",func_merge);
    test_merge("13578","2469",func_merge);
}

int main()
{

    test_eof();
    test_good();
    test_get();
    test_fail();

    cout<<"merge1:"<<endl;
    test_merge(merge1); 
    
    cout<<"merge2_error:"<<endl;
    test_merge(merge2_error); 

    cout<<"merge2_fix:"<<endl;
    test_merge(merge2_fix); 
    
    return 0;
}

/*
merge1:
    135 +  = 135
    135 + 2 = 1235
    135 + 24 = 12345
    13578 + 2469 = 123456789
merge2_error:
    135 +  = 355
    135 + 2 = 1255
    135 + 24 = 12345
    13578 + 2469 = 123456789
merge2_fix:
    135 +  = 135
    135 + 2 = 1235
    135 + 24 = 12345
    13578 + 2469 = 123456789
    */