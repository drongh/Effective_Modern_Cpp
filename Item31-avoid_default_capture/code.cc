#include <vector>
#include <functional>

using FilterContainer = std::vector<std::function<bool(int)>>; // see Item 9 for "using", Item 2 for std::function
FilterContainer filters;

class Widget {
    public:
        //…                                  // ctors, etc.
        Widget(int i):divisor(i){}
        void addFilter() const;            // add an entry to filters
    private:
        int divisor;                       // used in Widget's filter
};
void Widget::addFilter() const
{
    filters.emplace_back(
            [divisor=divisor](int value) {  // not dangle!
                    return value % divisor == 0; 
                }
            );
}

void addDivisorFilter()
{
    int divisor = 2;
    filters.emplace_back(
            //[](int value){ return value%5 ==0;        // 5 is not flexible
            //[&](int value){ return value%divisor ==0;} // danger! ref to divisor will dangle!
            [&divisor](int value){ 
            return value%divisor ==0;
            } // danger! ref to divisor will dangle!
            );
}

int main(void)
{
    {
        addDivisorFilter();
        bool i = filters[0](4);
        (void)i;
    }

    {
        Widget w(34);
        w.addFilter();
        bool i = filters[1](4);
        (void)i;
    }

    return 0;
}


