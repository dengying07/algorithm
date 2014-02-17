#include "RBST.hpp"
#include <stdlib.h>
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

int RBST::add(const Key& key, bool verbose) {
    unsigned int oldSize = m_size;
    m_head = randomAdd(m_head, key);
    if (m_size > oldSize) {
        if (verbose) {
            cout << "Node " << key << " is added into the tree." << endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout << "Node " << key << " is already in the tree." << endl;
        }
        return 0;
    }
};

int RBST::del(const Key& key, bool verbose) {
    unsigned oldSize = m_size;
    m_head = del(m_head, key);
   if (m_size < oldSize) {
        if (verbose) {
            cout << "Node " << key << " is deleted from the tree." << endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout << "Node " << key << " is not in the tree." << endl;
        }
        return 0;
    }
};

int RBST::find(const Key& key, bool verbose) {
    RBSTNode* ret = find(m_head, key);
    if (ret == NULL) {
        if (verbose) {
            cout << "Node " << key << " is not in the tree." << endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout << "Node " << key << " is in the tree." << endl;
        }
        return 1;
    }
};

int RBST::dump(char sep) {
    int ret = dump(m_head, sep);
    cout << "SIZE: " << ret << endl;
    return ret;
};

int RBST::dump(RBSTNode* target, char sep) {
    if (target == NULL) {
        return 0;
    }
    int ret = dump(target->left(), sep);
    cout << *target << sep;
    ret ++;
    ret += dump(target->right(), sep);
    return ret;
};


/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/


/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

RBSTNode*  RBST::rightRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////

    RBSTNode* left = target->left();
    int s1 = target->getNodeSize();
    int s3 = left->getNodeSize();
    int s4 = left->right() == NULL? 0: left->right()->getNodeSize();
    int new_s1 = s1-s3+s4;
    int new_s3 = s3-s4+new_s1;

    target->setLeft(left->right());
    target->setNodeSize(new_s1);

    left->setRight(target);
    left->setNodeSize(new_s3);
    return left;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////

    RBSTNode* right = target->right();
    int s1 = target->getNodeSize();
    int s3 = right->getNodeSize();
    int s4 = right->left() == NULL? 0: right->left()->getNodeSize();
    int new_s1 = s1-s3+s4;
    int new_s3 = s3-s4+new_s1;

    target->setRight(right->left());
    target->setNodeSize(new_s1);

    right->setLeft(target);
    right->setNodeSize(new_s3);
    return right;
};

RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////

    if(target == NULL){
        this->m_size++;
        target = new RBSTNode(key);
        target->setNodeSize(0);
        is_successful = true;
        return target;
    }

    // if the key is already inside
    if (key == target->getKey()) {
        is_successful = false;
        return target;
    }

    if (key < target->getKey()){
        target->setLeft(addRoot(target->left(), key));
        if(is_successful == true) target->setNodeSize(target->getNodeSize()+1);
        return rightRotate(target);
    }
    else{
        target->setRight(addRoot(target->right(), key));
        if(is_successful == true) target->setNodeSize(target->getNodeSize()+1);
        return leftRotate(target);
    }

    return target;
};

RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////

    is_successful = false;

    if(target == NULL){
        this->m_size++;
        target = new RBSTNode(key);
        target->setNodeSize(0);
        is_successful = true;
        return target;
    }
    int r = rand() % (target->getNodeSize()+1);

    // root insert happens here
    if(r == 1){
        return addRoot(target, key);
    }

    if (key == target->getKey()) {
        is_successful = false;
        return target;
    }

    else {
        if(key < target->getKey()){
            target->setLeft(randomAdd(target->left(), key));
            if (is_successful) target->setNodeSize(target->getNodeSize()+1);
        }
        else{
            target->setRight(randomAdd(target->right(), key));
            if (is_successful) target->setNodeSize(target->getNodeSize()+1);
        }
        return target;
    }
};


/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
    countFind++;
    ////////////// Write your code below  ////////////////////////

    if (target == NULL) return NULL;
    
    if (target->getKey() == key) return target;

    if (key < target->getKey()){
        return find(target->left(), key);
    }
    else{
        return find(target->right(), key);
    }
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
    countDelete++;
    ////////////// Write your code below  ////////////////////////

    /* This follows the algorithm from
       www.algolist.net/Data_structures/Binary_search_tree/Removal */
    //set the flag for successful deletion to false by default
    this->is_successful = false;
    // if trying to delete from null RBST, return null
    if (target == NULL) return NULL;

    // found the note to delete
    if (target->getKey() == key) {
        this->is_successful = true;
        // the target node to be removed is a leaf, has no subtrees
        if (target->left() == NULL && target->right() == NULL) {
            delete target;
            return NULL;
        }

        // the target node to be removed has a left subtree
        if (target->left() != NULL && target->right() == NULL) {
            RBSTNode* left = target -> left();
            delete target;
            return left;
        }

        // the target node to be removed has a right subtree
        if (target->left() == NULL && target->right() != NULL) {
            RBSTNode* right = target->right();
            delete target;
            return right;
        }

        // the target node to be removed has both a left and right subtree
        if (target->left() != NULL && target->right() != NULL) {
            RBSTNode * smallestNode = NULL;
            RBSTNode * subtree = NULL;
            
            // Balancing the tree: the right subtree of the deleting node is larger
            if(target->left()->getNodeSize() < target->right()->getNodeSize()){
                // finds the smallest node from the right subtree of the node to be removed
                smallestNode = findLeftMinNode(target->right());

                // gets the subtree after removing the smallest node
                subtree = removeLeftMinNode(target->right());

                // swaps the smallest node to the position where the node was deleted
                smallestNode->setRight(subtree);
                // links the left subtree of the new node to what the old node was pointing to
                smallestNode->setLeft(target->left());
            }
            // Balancing the tree: the left subtree of the deleting node is larger
            else{
                smallestNode = findRightMinNode(target->left());
                subtree = removeRightMinNode(target->left());
                
                smallestNode->setLeft(subtree);
                
                smallestNode->setRight(target->right());

            }
            // reset the size of the node to a sum of its left and right subtree
            int left_size = (smallestNode->left() == NULL)? 0: smallestNode->left()->getNodeSize();
            int right_size = (smallestNode->right() == NULL)? 0: smallestNode->right()->getNodeSize();
            smallestNode->setNodeSize(left_size + right_size);
            
            // delete the node
            delete target;

            // returns the newNode (that replaced the deleted node) to be linked to
            return smallestNode;

        }

        // after removing one node, the size decreases by 1
        m_size--;
    }
    
    if (key < target->getKey()) {
        RBSTNode * leftNode = del(target->left(), key);
        if(is_successful){
            target->setNodeSize(target->getNodeSize()-1);
        }
        target->setLeft(leftNode);

    }

    else {
        RBSTNode * rightNode = del(target->right(), key);
        if(is_successful){
            target->setNodeSize(target->getNodeSize()-1);
        }
        target->setRight(rightNode);
    }

    // key is not found
    return target;
}

RBSTNode* RBST::findLeftMinNode(RBSTNode* target) {
    if ( target->left() == NULL) return target;
    return findLeftMinNode(target->left());
}

RBSTNode* RBST::findRightMinNode(RBSTNode* target) {
    if ( target->right() == NULL) return target;
    return findRightMinNode(target->right());
}

RBSTNode* RBST::removeLeftMinNode(RBSTNode* target) {

    if (target->left() == NULL) {
        return target->right();
    }
    // node is the next smallest node
    RBSTNode * nextSmallerNode = removeLeftMinNode(target->left());
    target->setLeft(nextSmallerNode);
    target->setNodeSize(target->getNodeSize()-1);
    return target;

}

RBSTNode* RBST::removeRightMinNode(RBSTNode* target) {
    
    if (target->right() == NULL) {
        return target->left();
    }
    // node is the next smallest node
    RBSTNode * nextSmallerNode = removeRightMinNode(target->right());
    target->setRight(nextSmallerNode);
    target->setNodeSize(target->getNodeSize()-1);
    return target;
    
}
