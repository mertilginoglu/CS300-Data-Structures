#ifndef TEMPLATED_STACK_H
#define TEMPLATED_STACK_H

//Stack implementation was taken from lecture slides.
template <class Object>
class Stack
{
	public:
		Stack();
		Stack(const Stack & rhs);
		~Stack();

		bool isEmpty() const;
		bool isFull() const;
		void makeEmpty();

		void pop();
		void push(const Object & x);
		Object topAndPop();
		const Object & top() const;
		
		const Stack & operator=(const Stack & rhs);

	private:

		struct ListNode
		{
			Object element;
			ListNode *next;

			ListNode(const Object & theElement, ListNode * n = NULL)
				: element(theElement), next(n) {}
		};

		ListNode *topOfStack;
};

#include "Templated_stack.cpp"

#endif