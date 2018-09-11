#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <exception>
#include <cstdlib>
#include <utility>
#include <queue>

using std::queue;

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO
		bool isBalanced(); //TODO
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;


	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*()
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->()
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO
    mRoot=NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO
    clear();
    mRoot=NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// TODO
    return mRoot==NULL?0:mRoot->getHeight();
}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
    using namespace std;
	// TODO
    if(mRoot==NULL) return true;
    queue<Node<Key,Value>*> que;
    que.push(mRoot);
    while(!que.empty())
    {
        Node<Key,Value>* fnt=que.front();
        que.pop();

        if(fnt->getLeft()!=NULL) que.push(fnt->getLeft());
        if(fnt->getRight()!=NULL) que.push(fnt->getRight());

        if(fnt->getLeft()==NULL&&fnt->getRight()==NULL) continue;


        if(fnt->getLeft()==NULL)
        {
            if(fnt->getRight()->getHeight()==1)
                continue;
            else
            {
                return false;
            }
        }
        if(fnt->getRight()==NULL)
        {
            if(fnt->getLeft()->getHeight()==1)
                continue;
            else
            {
                return false;
            }
        }

        if((fnt->getLeft()->getHeight()==fnt->getRight()->getHeight()+1)||(fnt->getLeft()->getHeight()==fnt->getRight()->getHeight()-1)||(fnt->getLeft()->getHeight()==fnt->getRight()->getHeight()))
            continue;
        else
        {
            return false;
        }
    }
    return true;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	// TODO


    if(mRoot==NULL)
    {
        mRoot=new Node<Key,Value>(keyValuePair.first,keyValuePair.second,NULL);
        return ;
    }


    Node<Key,Value>* nod=mRoot;
    while(nod)
    {
        if(keyValuePair.first<nod->getKey())//go to left
        {
            if(nod->getLeft()==NULL)
            {
                nod->setLeft(new Node<Key,Value>(keyValuePair.first,keyValuePair.second,nod));
                break;
            }else
            {
                nod=nod->getLeft();
            }
        }else if(keyValuePair.first>nod->getKey())//go right
        {
            if(nod->getRight()==NULL)
            {
                nod->setRight(new Node<Key,Value>(keyValuePair.first,keyValuePair.second,nod));
                break;
            }else
            {
                nod=nod->getRight();
            }
        }else if(keyValuePair.first==nod->getKey())//exited
        {
            return ;
        }
    }
    //update height

    while(nod)
    {
        if(nod->getLeft()!=NULL&&nod->getRight()!=NULL)
        {
            nod->setHeight(std::max(nod->getLeft()->getHeight(),nod->getRight()->getHeight())+1);
        }else if(nod->getLeft()==NULL&&nod->getRight()==NULL)
        {
            nod->setHeight(1);
        }else if(nod->getLeft()!=NULL)
        {
            nod->setHeight(nod->getLeft()->getHeight()+1);
        }else
        {
            nod->setHeight(nod->getRight()->getHeight()+1);
        }
        nod=nod->getParent();
    }
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
    if(mRoot==NULL) return ;
    Key k=key;
    Node<Key,Value>* nod=mRoot;
    while(nod)
    {
        if(nod->getKey()>k)
        {
            nod=nod->getLeft();//go left
        }else if(nod->getKey()<k)
        {
            nod=nod->getRight();
        }else
        {
            if(nod->getLeft()==NULL&&nod->getRight()==NULL)//leaf node
            {
                if(nod->getParent()==NULL)//mRoot;
                {
                    mRoot=NULL;
                    delete nod;
                    nod=NULL;
                    break;
                }else
                {

                    Node<Key,Value>* p=nod->getParent();
                    if(p->getLeft()==nod)//nod is p's left child
                    {
                        p->setLeft(NULL);
                        delete nod;
                        nod=p;
                        break;
                    }else if(p->getRight()==nod)//nod is p's right child
                    {
                        p->setRight(NULL);
                        delete nod;
                        nod=p;
                        break;
                    }
                }
            }else if(nod->getLeft()!=NULL)//hvae predecessor
            {
                Node<Key,Value>* pre=nod->getLeft();
                while(pre->getRight()!=NULL)//pre is predecessor now
                {
                    pre=pre->getRight();
                }

                //use the bro to replace nod
                Node<Key,Value>* bro=new Node<Key,Value>(pre->getKey(),pre->getValue(),nod->getParent());
                bro->setLeft(nod->getLeft());
                bro->setRight(nod->getRight());

                if(bro->getParent()==NULL) mRoot=bro;
                else {
                    Node<Key,Value>* p=bro->getParent();
                    if(p->getLeft()==nod)
                    {
                        p->setLeft(bro);
                    }else
                    {
                        p->setRight(bro);
                    }
                }
                Node<Key,Value>* l=nod->getLeft();
                if(l!=NULL)
                {
                    l->setParent(bro);
                }
                Node<Key,Value>* r=nod->getRight();
                if(r!=NULL)
                {
                    r->setParent(bro);
                }

                delete nod;
                k=pre->getKey();

                if(pre->getParent()!=bro)
                {
                    nod=pre->getParent();
                }else
                {
                    nod=bro->getLeft();
                }
            }else//have successor
            {
                Node<Key,Value>* suc=nod->getRight();
                while(suc->getLeft()!=NULL)//suc is successor now
                {
                    suc=suc->getLeft();
                }

                //use the bro to repalce nod
                Node<Key,Value>* bro=new Node<Key,Value>(suc->getKey(),suc->getValue(),nod->getParent());
                bro->setLeft(nod->getLeft());
                bro->setRight(nod->getRight());

                if(bro->getParent()==NULL) mRoot=bro;
                else {
                    Node<Key,Value>* p=bro->getParent();
                    if(p->getLeft()==nod)
                    {
                        p->setLeft(bro);
                    }else
                    {
                        p->setRight(bro);
                    }
                }
                Node<Key,Value>* l=bro->getLeft();
                if(l!=NULL)
                {
                    l->setParent(bro);
                }


                Node<Key,Value>* r=bro->getRight();
                if(r!=NULL)
                {
                    r->setParent(bro);
                }

                delete nod;
                k=suc->getKey();

                if(suc->getParent()!=bro)
                {
                    nod=suc->getParent();
                }else
                {
                    nod=bro->getRight();
                }
            }
        }

    }

    //update height
    while(nod)
    {
        if(nod->getLeft()!=NULL&&nod->getRight()!=NULL)
        {
            nod->setHeight(std::max(nod->getLeft()->getHeight(),nod->getRight()->getHeight())+1);
        }else if(nod->getLeft()==NULL&&nod->getRight()==NULL)
        {
            nod->setHeight(1);
        }else if(nod->getLeft()!=NULL)
        {
            nod->setHeight(nod->getLeft()->getHeight()+1);
        }else
        {
            nod->setHeight(nod->getRight()->getHeight()+1);
        }
        nod=nod->getParent();
    }
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
    if(mRoot==NULL) return ;
    queue<Node<Key,Value>*> que;
    que.push(mRoot);
    while(!que.empty())
    {
        Node<Key,Value>* fnt=que.front();
        que.pop();

        if(fnt->getLeft()) que.push(fnt->getLeft());
        if(fnt->getRight()) que.push(fnt->getRight());

        delete fnt;
    }
    mRoot=NULL;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
    if(mRoot==NULL) return mRoot;
    Node<Key,Value>* nod=mRoot;
    while(nod->getLeft()!=NULL)
    {
        nod=nod->getLeft();
    }
    return nod;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO
    if(mRoot==NULL) return mRoot;
    Node<Key,Value>* nod=mRoot;

    while(nod!=NULL)
    {
        if(key>nod->getKey())
        {
            nod=nod->getRight();
        }else if(key<nod->getKey())
        {
            nod=nod->getLeft();
        }else
        {
            break;
        }
    }
    return nod;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
