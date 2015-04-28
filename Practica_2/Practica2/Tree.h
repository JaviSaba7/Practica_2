#ifndef __TREE_H__
#define __TREE_H__

#include "p2List.h"
#include "Stack.h"

template<class TYPE>
struct Node
{
	TYPE Data;
	Node<TYPE>* Parent;
	p2List<Node<TYPE>*> Children;


	//PreOrder Recursiu
	void PreOrderRecursive(p2List<Node<TYPE>*>* list)
	{
		list->add(this);

		p2List_item<Node*>* tmp = Children.start;

		for (; tmp != NULL; tmp = tmp->next)
			tmp->data->PreOrderRecursive(list);
	}
		
	//PostOrder Recursiu
	void PostOrderRecursive(p2List<Node<TYPE>*>* list)
	{
		p2List_item<Node*>* tmp = Children.start;

		for (; tmp != NULL; tmp = tmp->next)
			tmp->data->PostOrderRecursive(list);

		list->add(this);
	}

	//InOrder Recursiu
	void InOrderRecursive(p2List<Node<TYPE>*>* list)
	{
		p2List_item<Node*>* item = Children.start;
		unsigned int mid = Children.count() / 2;

		for (unsigned int i = 0; i < mid; ++i, item = item->next)
			item->data->InOrderRecursive(list);

		list->add(this);

		for (; item != NULL; item = item->next)
			item->data->InOrderRecursive(list);
	}

};
	


template<class TYPE>
class Tree
{
	public:
		Node<TYPE>* RootNode;
	public:

		//Constructor
		Tree(const TYPE& RootData)
		{
			RootNode = new Node<TYPE>;
			RootNode->Data = RootData;
			RootNode->Parent = NULL;
		}

		//Destructor
		virtual ~Tree()
		{
			
		}
		
		//Add: Create a Node with Data (node information)
		Node<TYPE>* Add(const TYPE& Data)
		{
			Node<TYPE>* NewNode = new Node<TYPE>;
			NewNode->Data = Data;
			RootNode->Children.add(NewNode);
			NewNode->Parent = RootNode;
			return NewNode;
		}
		
		//ParentSearcher: Find the node with the value introduced
		Node<TYPE>* ParentSearcher(const TYPE& DataFind)
		{
			Stack<Node<TYPE>*> s;
			Node<TYPE>* NodeReturn = RootNode;

			while (NodeReturn->Data != DataFind)
			{
				p2List_item<Node<TYPE>*>* tmp = NodeReturn->Children.end;

				while (tmp != NULL)
				{
					s.PushBack(tmp->data);
					tmp = tmp->prev;
				}
				NodeReturn = s.Pop();
			}
			return NodeReturn;
		}
				

		//AddComplex: Create a Node with Data (node information) and Parent
		Node<TYPE>* AddComplex(const TYPE& Data, const TYPE& Parent)
			{
				Node<TYPE>* NewNode = new Node<TYPE>;
				NewNode->Data = Data;
				NewNode->Parent = ParentSearcher(Parent);
				NewNode->Parent->Children.add(NewNode);
				return NewNode;
			}

		//Clear All
		void ClearAll()
		{
			delete Tree;
		}

		//Clear Node
		//ERROR AL MÈTODE
		/*void ClearNode(const TYPE& DeletingNode)
		{
			Stack<Node<TYPE>*> Stack1;
			Node<TYPE>* NodeInfo = ParentSearcher(DeletingNode);

			while (NodeInfo != NULL)
			{
				p2List_item<Node<TYPE>*>* tmp = NodeInfo->Children.end;

				while (tmp != NULL)
				{
					Stack1.PushBack(tmp->data);
					tmp = tmp->prev;
				}
				delete NodeInfo;
				NodeInfo = Stack1.Pop();
			}
		}*/

						
		//PreOrder Recursiu
		void PreOrderRecursive(p2List<Node<TYPE>*>* list) 
		{
			RootNode->PreOrderRecursive(list);
		}

		//PreOrder Recursiu
		void PostOrderRecursive(p2List<Node<TYPE>*>* list)
		{
			RootNode->PostOrderRecursive(list);
		}
		
		//InOrder Recursiu
		void InOrderRecursive(p2List<Node<TYPE>*>* list)
		{
			RootNode->InOrderRecursive(list);
		}

		void PreOrderIterative(p2List<Node<TYPE>*>* list)
		{
			Stack<Node<TYPE>*> Stack1;
			Node<TYPE>* node = RootNode;

			while (node != NULL || Stack1.Pop(node))
			{
				list->add(node);

				p2List_item<Node<TYPE>*>* item = node->Children.end;
				for (; item != node->Children.start; item = item->prev)
					Stack1.PushBack(item->data);

				node = (item != NULL) ? item->data : NULL;
			}
		}

		void PostOrderIterative(p2List<Node<TYPE>*>* list)
		{
			Stack<Node<TYPE>*> Stack1;
			Node<TYPE>* node = RootNode;

			while (node != NULL || Stack1.Pop(node))
			{
				p2List_item<Node<TYPE>*>* item = node->Children.end;

				if (item != NULL && list->Searcher (item->data) == -1)
				{
					Stack1.PushBack(node);
					for (; item != node->Children.start; item = item->prev)
						Stack1.PushBack(item->data);

					node = item->data;
				}
				else
				{
					list->add(node);
					node = NULL;
				}
			}
		}

		/*No he aconseguit fer que aquest mètode em passi el Unit Test
		void InOrderIterative(p2List<Node<TYPE>*>* list)
		{
			Stack<Node<TYPE>*> Stack1;
			Node<TYPE>* node = RootNode;

			while (node != NULL || Stack1.Pop(node))
			{
				list->add(node);
								
				node = (item != NULL) ? item->data : NULL;
			}
		}*/
};
#endif // __TREE_H__

