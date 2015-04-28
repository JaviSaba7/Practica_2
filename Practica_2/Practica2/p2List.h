#ifndef __p2List_H__
#define __p2List_H__

#define NULL 0

template<class TYPE>
struct p2List_item
{
public:
	TYPE                 data;
	p2List_item<TYPE>*   next;
	p2List_item<TYPE>*   prev;

	inline p2List_item(const TYPE& _data)
	{
		data = _data;
		next = prev = NULL;
	}

	~p2List_item()
	{}
};

template<class TYPE>
class Queue
{
public:
	p2List_item<TYPE>*   start;
	p2List_item<TYPE>*   end;

private:

	unsigned int size;

	void add(const TYPE value)
	{
		p_data_item = new p2List_item <TYPE>(value);
		if (start->next != NULL)
		{
			p_data_item->next = start;
			start = p_data_item;
		}

		else
		{
			start = p_data_item;
			end = p_data_item;
		}
		size++;
	}

	TYPE Extract()
	{
		p2List_item<TYPE>* tmp;
		tmp = end;
		end->prev->next = NULL;
		delete end;
		return tmp->data;
	}

	TYPE Pic(TYPE* position)
	{
		return position->data;
	}
};

/**
* Manages a double linked list
*/
template<class TYPE>
class p2List
{

public:

	p2List_item<TYPE>*   start;
	p2List_item<TYPE>*   end;

private:

	unsigned int  size;

public:

	/**
	* Constructor
	*/
	inline p2List()
	{
		start = end = NULL;
		size = 0;
	}

	/**
	* Destructor
	*/
	~p2List()
	{
		clear();
	}

	/**
	* Get Size
	*/
	unsigned int count()
	{
		return size;
	}

	/**
	* Add new item
	*/
	unsigned int add(const TYPE& item)
	{
		p2List_item<TYPE>*   p_data_item;
		p_data_item = new p2List_item < TYPE >(item);

		if (start == NULL)
		{
			start = end = p_data_item;
		}
		else
		{
			p_data_item->prev = end;
			end->next = p_data_item;
			end = p_data_item;
		}

		return(++size);
	}

	/**
	* Deletes an item from the list
	*/
	bool del(p2List_item<TYPE>* item)
	{
		if (item == NULL)
		{
			return (false);
		}

		// Now reconstruct the list
		if (item->prev != NULL)
		{
			item->prev->next = item->next;

			if (item->next != NULL)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}
		}
		else
		{
			if (item->next)
			{
				item->next->prev = NULL;
				start = item->next;
			}
			else
			{
				start = end = NULL;
			}
		}

		delete item;
		--size;
		return(true);
	}


	void clear()
	{
		p2List_item<TYPE>*   p_data;
		p2List_item<TYPE>*   p_next;
		p_data = start;

		while (p_data != NULL)
		{
			p_next = p_data->next;
			delete p_data;
			p_data = p_next;
		}

		start = end = NULL;
		size = 0;
	}

	//Funció per afegir operadors by Ricard Pillosu
	TYPE& operator[](const unsigned int index)
	{
		long pos;
		p2List_item<TYPE>* p_item;
		pos = 0;
		p_item = start;

		while (p_item != NULL)
		{
			if (pos == index)
			{
				break;
			}
			++pos;
			p_item = p_item->next;
		}
		return(p_item->data);
	}

	int Searcher(const TYPE& data)
	{
		p2List_item<TYPE>* tmp = start;
		int index = 0;

		while (tmp != NULL)
		{
			if (tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}


};
#endif //__p2List_H__