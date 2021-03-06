#include <iostream>
#include <vector>

#include "tree.h"
using namespace std;

template <class T>
BTree<T>::BTree(int m, bool isLeaf) {
  this->rank = m;
  if (!isLeaf) {
    this->children = new vector<BTree<T> *>;
  } else {
    this->children = NULL;
  }
  this->entities = new vector<BNode<T> *>;
}

template <class T>
BTree<T>::~BTree() {
  if (this->getEntities() != NULL) {
    if (!this->getEntities()->empty()) {
      for (int i = 0; i < this->getEntities()->size(); i++) {
        delete (*(this->getEntities()))[i];
      }
      this->getEntities()->clear();
    }
    delete this->getEntities();
  }

  if (this->getChildren() != NULL) {
    if (!this->getChildren()->empty()) {
      for (int i = 0; i < this->getChildren()->size(); i++) {
        delete (*(this->getChildren()))[i];
      }
      this->getChildren()->clear();
    }
    delete this->getChildren();
  }
}
template <class T>
void insertBigger(BNode<T> *n, BTree<T> **nodePtr, int index) {
  BTree<T> *node = *(nodePtr);
  if (index == node->getEntities()->size() - 1) {
    //最后一个数据点
    if (node->getEntities()->size < node->getRank()) {
      //当前节点数据没有满
      node->getEntities()->push_back(n);
    } else {
      //
    }
    if (node->getChildren() != NULL) {
      //不是叶子节点
    }
  }
}

template <class T>
void BTree<T>::addNode(BNode<T> *n) {
  if (this->entities->empty()) {
    this->entities->push_back(n);
  } else {
    //当前不为空
    for (int i = 0; i < this->entities->size(); i++) {
      BNode<T> *currentNode = this->entities->at(i);
      if (n->compare(currentNode) == 1) {
        // n_key>c_key
        insertBigger(n, &this, i);
      } else if (n->compare(currentNode) == -1) {
        // n_key<c_key
      } else {
        // n_key==c_key
        currentNode->value = n->value;
      }
    }
  }

  cout << "getEntities() size:" << this->getEntities()->size() << endl << endl;
}

template <class T>
void insertNode(vector<BNode<T> *> **nodes, BNode<T> *n) {
  vector<BNode<T> *> *temp = *(n);
  for (int i = 0; i < temp->size(); i++) {
    if (n->key > ((*temp)[i])->key) {
      if (i == temp->size() - 1) {
        break;
      } else {
        i++;
      }

    } else {
      if (i == 0) {
        temp->insert(0, n);
      } else {
        temp->insert(i - 1, n);
      }
    }
  }
}

template <class T>
void BTree<T>::deleteNode(string key) {}

template <class T>
BNode<T> *BTree<T>::search(string key) {
  for (int i = 0; i < this->entities->size(); i++) {
    if (key == (this->entities->at(i))->key) {
      return this->entities->at(i);
    } else if (key < (this->entities->at(i))->key) {
      // search in left children
      if (this->children != NULL) {
        for (int j = 0; j <= i; j++) {
          BNode<T> *node = this->children->at(j)->search(key);
          if (node != NULL && node->key == key) {
            return node;
          }
        }
      }
    } else {
      if (i == this->entities->size() - 1) {
        // search in right children
        if (this->children != NULL) {
          for (int j = i + 1; j < this->children->size(); j++) {
            BNode<T> *node = this->children->at(j)->search(key);
            if (node != NULL && node->key == key) {
              return node;
            }
          }
        }
      }
    }
  }

  return NULL;
}
template <class T>
vector<BNode<T> *> BTree<T>::traverse() {}
template <class T>
BTree<T> *createData() {
  BTree<string> *tree = new BTree<string>(3, false);
  BNode<string> *n4 = new BNode<string>;
  n4->key = "4";
  n4->value = "aaa";
  tree->getEntities()->push_back(n4);
  BNode<string> *n8 = new BNode<string>;
  n8->key = "8";
  n8->value = "bbb";
  tree->getEntities()->push_back(n8);

  BTree<string> *c1 = new BTree<string>(3, false);
  BNode<string> *n1 = new BNode<string>;
  n1->key = "1";
  n1->value = "cccc";
  c1->getEntities()->push_back(n1);
  BNode<string> *n2 = new BNode<string>;
  n2->key = "2";
  n2->value = "dddd";
  c1->getEntities()->push_back(n2);
  tree->getChildren()->push_back(c1);

  BTree<string> *c2 = new BTree<string>(3, false);
  BNode<string> *n5 = new BNode<string>;
  n5->key = "5";
  n5->value = "eeee";
  c2->getEntities()->push_back(n5);
  BNode<string> *n6 = new BNode<string>;
  n6->key = "6";
  n6->value = "ffff";
  c2->getEntities()->push_back(n6);
  tree->getChildren()->push_back(c2);

  BTree<string> *c3 = new BTree<string>(3, false);
  BNode<string> *n9 = new BNode<string>;
  n9->key = "9";
  n9->value = "gggg";
  c3->getEntities()->push_back(n9);
  BNode<string> *n10 = new BNode<string>;
  n10->key = "10";
  n10->value = "ffff";
  c3->getEntities()->push_back(n10);
  tree->getChildren()->push_back(c3);
  return tree;
}

void testSearch() {
  BTree<string> *tree = createData<string>();
  BNode<string> *node = tree->search("1");
  if (node == NULL) {
    cout << "no find" << endl;
  } else {
    cout << node->key << ";" << node->value << endl;
  }
}
