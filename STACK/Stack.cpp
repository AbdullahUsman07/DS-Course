#include <iostream>

template <typename T>
class Stack
{
private:
    int SIZE; //overall size of stack
    int top;
    T *data;

public:
    Stack(int s)
    {
        top = -1;
        SIZE = s;
        data = new T[SIZE];
    }

    void push(int data) const
    {

        if (this->top == SIZE - 1)
        {
            throw("Stack Overflow");
        }
        this->top++;
        this->data[this->top] = data;
    }

    void pop()
    {
        if (top == -1)
        {
            throw("Stack Underflow!");
        }
        this->top--;
    }

    T top() const
    {
        return this->data[this->top];
    }

    Stack(const Stack & other)
    { 
        this=other;
    }

    // returns the current size of stack 
    int size()
    {
        return this->top +1;
    }

    const Stack & operator =(const Stack &other)
    {
        if(this == &other)
        {
            return *this;
        }

        if(data!=nullptr)
        {
            delete []data;
        }

        top=other.top;
        SIZE=other.SIZE;
        data=new T[SIZE];

        for(int i=0;i<=top;i++){
            data[i]=other.data[i];
        }

        return *this;
    }

    ~Stack()
    {
        if (SIZE != 0)
        {
            delete[] this->data;
        }
    }

    template <typename T>
    friend bool operator==(const Stack &, const Stack &);
    template <typename T>
    friend bool operator!=(const Stack &const Stack &);
    template <typename T>
    friend bool operator<(const Stack &, const Stack &);
    template <typename T>
    friend bool operator<=(const Stack &, const Stack &);
    template <typename T>
    friend bool operator>=(const Stack &, const Stack &);
    template <typename T>
    friend bool operator>(const Stack &, const Stack &);
};

template <typename T>
bool operator==(const Stack<T> &lhs, const Stack<T> &rhs)
{
    if(lhs.size != lhs. size){
        return false;
    }   
    for(int i=0;i< lhs.size;i++)  // we are using the size of Stack on Lhs since both size are same we can use either
    {
        if(lhs.data[i]!=rhs.data[i])
        {
            return false;
        }
    }
    return true;
}


template <typename T>
bool operator!=(const Stack<T> &lhs ,const Stack<T> &rhs){
    return !(lhs==rhs);
}


template <typename T>
bool operator<(const Stack<T> &lhs , const Stack<T> &rhs){
    
}

template <typename T>
bool operator<=(const Stack<T> &lhs, const Stack<T> &rhs){

}
template <typename T>
bool operator>=(const Stack<T> &lhs, const Stack<T> &rhs){

}
template <typename T>
bool operator>(const Stack<T> &lhs, const Stack<T> &rhs){

}