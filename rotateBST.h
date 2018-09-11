#ifndef rotateBST_H
#define rotateBST_H


#include <vector>
#include "bst.h"
using namespace std;

template <typename Key,typename Value>
class BinarySearchTree;

template <typename Key,typename Value>
class rotateBST:public BinarySearchTree<Key,Value>

{
    public:
        int sameKeys(const rotateBST<Key,Value>& t2) const;//if this have all the same keys with t2
        void transform(rotateBST<Key,Value>& t2)const ;
    protected:
        void leftRotate(Node<Key,Value>* r);
        void rightRotate(Node<Key,Value>* r);
    private:
        void recurHelper(Node<Key,Value>* nod1,Node<Key,Value>* nod2,rotateBST<Key,Value>& t2) const;//we make left child .right of nd2 ok
        int UpdateHeight(Node<Key,Value>* nod);

};

template <typename Key,typename Value>
int rotateBST<Key,Value>::sameKeys(const rotateBST<Key,Value>& t2) const
{
    typename rotateBST<Key,Value>::iterator it1(this->getSmallestNode());
    typename rotateBST<Key,Value>::iterator end1(NULL);
    typename rotateBST<Key,Value>::iterator it2(t2.getSmallestNode());
    typename rotateBST<Key,Value>::iterator end2(NULL);
    while(it1!=end1&&it2!=end2)
    {
        if((*it1).first!=(*it2).first)
        {
            return false;
        }
        ++it1;
        ++it2;
    }
    if(it1!=end1||it2!=end2)
    {
        return false;
    }

    return true;
}





template <typename Key,typename Value>
void rotateBST<Key,Value>::transform(rotateBST<Key,Value>& t2) const
{
    if(sameKeys(t2)==false)
    {
        return;
    }


    recurHelper(NULL,NULL,t2);


}

template <typename Key,typename Value>
void rotateBST<Key,Value>::recurHelper(Node<Key,Value>* nod1,Node<Key,Value>* nod2,rotateBST<Key,Value>& t2) const//we make left child .right of nd2 ok
{
    if(nod1==NULL&&nod2==NULL)
    {
        while(t2.mRoot->getLeft()!=NULL)
        {
            t2.rightRotate(t2.mRoot);

        }
        auto p=t2.mRoot;
        while(p->getRight()!=NULL)
        {
            while(p->getRight()->getLeft()!=NULL)
            {
                t2.rightRotate(p->getRight());

            }
            p=p->getRight();

        }
        while(this->mRoot->getKey()!=t2.mRoot->getKey())
        {
            t2.leftRotate(t2.mRoot);
        }
        recurHelper(this->mRoot,t2.mRoot,t2);
    }else
    {
        if(nod2->getLeft()!=NULL)
        {
            //make the left of nod2 linked list
            while(nod2->getLeft()->getLeft()!=NULL)
            {
                t2.rightRotate(nod2->getLeft());
            }
            auto nod=nod2->getLeft();
            while(nod->getRight()!=NULL)
            {
                while(nod->getRight()->getLeft()!=NULL)
                {
                    t2.rightRotate(nod->getRight());
                }
                nod=nod->getRight();
            }

            //make key same
            while(nod2->getLeft()->getKey()!=nod1->getLeft()->getKey())
            {
                t2.leftRotate(nod2->getLeft());
            }
            recurHelper(nod1->getLeft(),nod2->getLeft(),t2);
        }

        if(nod2->getRight()!=NULL)
        {
            //make the left of nod2 linked list
            while(nod2->getRight()->getLeft()!=NULL)
            {
                t2.rightRotate(nod2->getRight());
            }
            auto nod=nod2->getRight();
            while(nod->getRight()!=NULL)
            {
                while(nod->getRight()->getLeft()!=NULL)
                {
                    t2.rightRotate(nod->getRight());
                }
                nod=nod->getRight();
            }

            //make key same
            while(nod2->getRight()->getKey()!=nod1->getRight()->getKey())
            {
                t2.leftRotate(nod2->getRight());
            }
            recurHelper(nod1->getRight(),nod2->getRight(),t2);
        }
        nod2->setHeight(nod1->getHeight());
    }
}



template <typename Key,typename Value>
void rotateBST<Key,Value>::leftRotate(Node<Key,Value>* r)
{
    if(r==NULL) return ;
    Node<Key,Value>* z=r;
    Node<Key,Value>* y=r->getRight();
    if(y==NULL) return ;
    Node<Key,Value>* t2=y->getLeft();
    Node<Key,Value>* p=z->getParent();
    //ok

    //parent
    if(p==NULL) this->mRoot=y;
    else if(p->getLeft()==z) p->setLeft(y);
    else if(p->getRight()==z) p->setRight(y);

    //z
    z->setRight(t2);
    z->setParent(y);

    //y
    y->setParent(p);
    y->setLeft(z);

    //t2
    if(t2!=NULL)
        t2->setParent(z);

    //deal z height
    if(z->getLeft()==NULL&&t2==NULL)
    {
        z->setHeight(1);
    }else if(z->getLeft()==NULL)
    {
        z->setHeight(t2->getHeight()+1);
    }else if(t2==NULL)
    {
        z->setHeight(z->getLeft()->getHeight()+1);
    }else
    {
        z->setHeight(max(z->getLeft()->getHeight(),t2->getHeight())+1);
    }
    if(y->getRight()!=NULL)
    {
        y->setHeight(max(y->getRight()->getHeight(),z->getHeight())+1);
    }else
    {
        y->setHeight(z->getHeight()+1);
    }
    if(p!=NULL)
    {
        if(p->getLeft()!=NULL&&p->getRight()!=NULL)
        {
            p->setHeight(max( p->getLeft()->getHeight(),p->getRight()->getHeight() )+1);
        }else if(p->getLeft()!=NULL)
        {
            p->setHeight(p->getLeft()->getHeight()+1);
        }else if(p->getRight()!=NULL)
        {
            p->setHeight(p->getRight()->getHeight()+1);
        }else
        {
            p->setHeight(1);
        }
    }
    return ;
}

template <typename Key,typename Value>
void rotateBST<Key,Value>::rightRotate(Node<Key,Value>* r)
{
    if(r==NULL) return ;
    Node<Key,Value>* z=r;
    Node<Key,Value>* y=z->getLeft();
    if(y==NULL) return ;
    Node<Key,Value>* t3=y->getRight();
    Node<Key,Value>* p=z->getParent();
    //ok

    //parent
    if(p==NULL) this->mRoot=y;
    else if(p->getLeft()==z) p->setLeft(y);
    else if(p->getRight()==z) p->setRight(y);

    //z
    z->setLeft(t3);
    z->setParent(y);

    //y
    y->setParent(p);
    y->setRight(z);

    //t3
    if(t3!=NULL)
        t3->setParent(z);

    //deal z height
    if(z->getRight()==NULL&&t3==NULL)
    {
        z->setHeight(1);
    }else if(z->getRight()==NULL)
    {
        z->setHeight(t3->getHeight()+1);
    }else if(t3==NULL)
    {
        z->setHeight(z->getRight()->getHeight()+1);
    }else
    {
        z->setHeight(max(z->getLeft()->getHeight(),z->getRight()->getHeight())+1);
    }
    if(y->getLeft()!=NULL)
    {
        y->setHeight(max(y->getLeft()->getHeight(),z->getHeight())+1);
    }else
    {
        y->setHeight(z->getHeight()+1);
    }
    if(p!=NULL)
    {
        if(p->getLeft()!=NULL&&p->getRight()!=NULL)
        {
            p->setHeight(max( p->getLeft()->getHeight(),p->getRight()->getHeight() )+1);
        }else if(p->getLeft()!=NULL)
        {
            p->setHeight(p->getLeft()->getHeight()+1);
        }else if(p->getRight()!=NULL)
        {
            p->setHeight(p->getRight()->getHeight()+1);
        }else
        {
            p->setHeight(1);
        }
    }
    return ;
}


#endif
