#include <iostream>

using namespace std;

struct node
{
	int data;
	struct node *next;
};

node* createNode()
{
	static int data = 1;
	struct node* newNode =  new node;
	newNode->data = data;
	newNode->next = NULL;
	data++;
	return newNode;
}

struct node *recursiveReverseLL(struct node *list)
{
    struct node *revHead;
    if (list == NULL || list->next == NULL)
    {
        return list;
    }

    revHead = recursiveReverseLL(list->next);
    list->next->next = list;
    list->next = NULL; 

    return revHead;
}


node* craeteList()
{
	struct node *head = createNode();
	/* Add more nodes to the head */
	int listSize = 5;
	struct node* curNode = head;
	
	for(int i=0; i<listSize; i++)
	{
		curNode->next = createNode();
		curNode = curNode->next;
	}
	
	return head;
}

int main()
{	
	struct node* head = craeteList();
	
	struct node* tmp = head;
	while(tmp)
	{
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;	
	
	struct node* reversedList  = recursiveReverseLL(head);
	
	while(reversedList)
	{
		cout << reversedList->data << " ";
		reversedList = reversedList->next;
	}
	cout << endl;	
}
