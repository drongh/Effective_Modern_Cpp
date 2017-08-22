#include <iostream>
#include <vector>

//decltype规则非常简单, 括号内是啥类型就返回啥类型.
//auto规则(模板类型推导规则), 有引用则带引用，没有则不带，不管等号右侧是否有引用

template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) -> decltype(c[i]) //decltype规则
{
    //authenticateUser();
    return c[i]; // int&
}

template<typename Container, typename Index>
auto authAndAccess2(Container& c, Index i) //auto 规则
{
    //authenticateUser();
    return c[i];
}

template<typename Container, typename Index>
decltype(auto) authAndAccess3(Container& c, Index i) //decltype规则
{
    //authenticateUser();
    return c[i];
}

int main(void)
{
    std::vector<int> vec{1,2,3,4,5,6};

    // 注意!!! c[i]的返回类型是T&, 即int&, 
    // 这里根据auto类型推导规则（auto没有带&, 即使等号右侧有&, 变量也没有&），i,j,k均为int
    auto i = authAndAccess(vec, 2);//根据decltype规则,  函数返回int&, pt i=int
    auto j = authAndAccess2(vec, 2);//根据auto规则,     函数返回int,  pt j=int
    auto k = authAndAccess3(vec, 2);//根据decltype规则, 函数返回int&, pt k=int

    authAndAccess(vec, 5) = 10;//anthAndAccess()使用delctype规则,而不是auto和模板推导规则，返回int&
    //authAndAccess2(vec, 5) = 10; //anthAndAccess2()使用auto规则,而不是decltype规则，返回int (c[i] int&的&被忽略)
                                    //compile error! authAndAccess2返回一个右值! 给右值赋值是C++不允许的。
    authAndAccess3(vec, 5) = 10;//anthAndAccess3()使用delctype规则,而不是auto和模板推导规则，返回int&

    return 0;
}




