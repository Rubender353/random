#ifndef STACK
#define STACK
class Stack {
    public:
        virtual void push(int newEntry) = 0;
        virtual int pop() = 0;
        virtual int peek() const = 0;
        virtual bool isEmpty() const = 0;
        virtual void makeEmpty() = 0;
};

#endif