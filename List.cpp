#include "List.h"
/*
List::List()
{
	head = NULL;
	tail = NULL;
}

void List::addNode(Object& objList)
{
	node* temp = new node;
	temp->obj = objList;
	temp->next = NULL;
	
	if (head == NULL)
	{
		head = temp;
		tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = tail->next;
	}
}

void List::display(node* head, RenderTarget& target)
{
	head->obj.draw(target);
	if (head->next == NULL)
	{
		return;
	}
	else {
		display(head->next, target);
	}
}*/