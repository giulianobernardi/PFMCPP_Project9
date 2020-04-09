/*
 Project 9: Part 1/1
 Chapter 5 Part 7 Task

 Create a branch named Part1
 
1) read Instructions.cpp

Make the following program work, which makes use of Variadic templates and Recursion

Once it's working: 
Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>

struct Point
{
    Point(float _x, float _y) : x(_x), y(_y) { }
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    std::string toString() const
    {
        std::string str;
        str +="Point { x: ";
        str += std::to_string(x);
        str += ", y: ";
        str += std::to_string(y);
        str += " }";
        return str;
    }
private:
    float x{0}, y{0};
};

// --------------------------------------------------
//               Wrapper class templates
// --------------------------------------------------

// Templated Wrapper struct
template<typename Type>
struct Wrapper
{
    Wrapper(Type&& t) : val(std::move(t)) 
    { 
        std::cout << "TypeID: "; 
        std::cout << "Wrapper(" << typeid(val).name() << ")" << std::endl; 
    }
    void print() 
    {
        std::cout << "Value: "; 
        std::cout << "Wrapper::print(" << val << ")" << std::endl; 
        std::cout << "------------------------" << std::endl; 
    }    

    Type val;

};

// Templated specialization of Wrapper struct for Point
template<>
struct Wrapper<Point>
{
    Wrapper(Point&& t) : val(std::move(t)) 
    { 
        std::cout << "TypeID: "; 
        std::cout << "Wrapper(" << typeid(val).name() << ")" << std::endl; 
    }
    void print() 
    { 
        std::cout << "Value: "; 
        std::cout << "Wrapper::print(" << val.toString() << ")" << std::endl; 
        std::cout << "------------------------" << std::endl; 
    }

    Point val;
};

// --------------------------------------------------
//               Variadic templates
// --------------------------------------------------

// Single-template-parameter version
template<typename T>
void variadicHelper(T first)
{
    Wrapper wrapper ( std::forward<T>(first) ); // Instantiate/fwd first to wrapper
    wrapper.print();
    std::cout << "Last recursive call!" << std::endl;
}

// Variadic-template version
template<typename T, typename ...Args>
void variadicHelper(T first, Args ... everythingElse)
{ 
    
    Wrapper wrapper ( std::forward<T>(first) ); // Instantiate/fwd first to wrapper
    wrapper.print();
    variadicHelper( std::forward<Args>(everythingElse) ... ); // Call variadic helper forwarding everythingElse
}

// --------------------------------------------------
//                      Main
// --------------------------------------------------

int main()
{
    variadicHelper( 3, std::string("burgers"), 2.5, Point{3.f, 0.14f} );
}
