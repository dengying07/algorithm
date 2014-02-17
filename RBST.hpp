#ifndef RBST_HPP_
#define RBST_HPP_

#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>
#include "Key.hpp"
#include "DataStructure.hpp"

using namespace std;

class RBSTNode;
class RBSTNode: public Key {

public:
    RBSTNode(const Key& key) : Key(key), m_left(NULL), m_right(NULL) {}
    virtual ~RBSTNode() {}

    string getKey() {
        return *this;
    }

    string setKey(const Key& key) {
        assign(key);
        return Key(key);
    }

    RBSTNode* left() {
        return m_left;
    }

    RBSTNode* right() {
        return m_right;
    }

    RBSTNode* setLeft (RBSTNode* left) {
        m_left = left;
        return this;
    }
    RBSTNode* setRight (RBSTNode* right) {
        m_right = right;
        return this;
    }
    void setNodeSize(int size){
		this->node_size = size;;
	}
	int getNodeSize(){
		return this->node_size;
	}

private:
  RBSTNode() {}
  RBSTNode* m_left;
  RBSTNode* m_right;
  int node_size;

};


class RBST : public DataStructure {

public:
    RBST() : m_head(NULL), m_size(0) {};
    virtual ~RBST() {};

    // ADD FUNCTIONS
    int add(const Key& key, bool verbose=false);

    // FIND FUNCTIONS
    int find(const Key& key, bool verbose=false);

    // DEL FUNCTIONS
    int del(const Key& key, bool verbose=false);

    // DUMP FUNCTIONS
    int dump(char sep = ' ');
    int dump(RBSTNode* target, char sep);

private:
  RBSTNode* randomAdd(RBSTNode* target, const Key& key);
  RBSTNode* addRoot(RBSTNode* target, const Key& key);
  RBSTNode* rightRotate(RBSTNode* target);
  RBSTNode* leftRotate(RBSTNode* target);
  
  RBSTNode* del(RBSTNode* target, const Key& key);
  RBSTNode* find(RBSTNode* target, const Key& key);
  
    /* additional helper function for deletion */
  RBSTNode* findLeftMinNode(RBSTNode* target);
  RBSTNode* removeLeftMinNode(RBSTNode* target);
  RBSTNode* findRightMinNode(RBSTNode* target);
  RBSTNode* removeRightMinNode(RBSTNode* target);
  
  RBSTNode* m_head;
  unsigned int m_size;
    /* additional attribute to record a successful add/del to update node size*/
  bool is_successful;
  

};

#endif /*RBST_HPP_*/

