#include "SkipList.hpp"

/***********************************************************/
/********************** PROVIDED FUNCTIONS *****************/
/***********************************************************/

void SkipList::init(int maxHeight) {
    m_maxHeight = maxHeight;
    m_head = new SkipListNode("", m_maxHeight);
}

SkipList::~SkipList() {
    while (m_head != NULL) {
        SkipListNode* head = m_head;
        m_head = m_head->nextAtLevel(0);
        delete head;
    }
}

int SkipList::add(const Key& key, bool verbose) {
  if (find(key, false)) {
        if (verbose) {
            cout << "Node " << key << " is already in the list." << endl;
        }
        return 0;
    }

    SkipListNode* newNode = new SkipListNode(key, randHeight());
    if (verbose) {
        cout << "Add new node "<< *newNode << " with height "
             << newNode->height() << endl;
    }
    int ret = add(m_head, newNode, m_maxHeight - 1);
    if (ret == 0) {
        return ret;
    }
    return 1;
}

int SkipList::find(const Key& key, bool verbose) {
    SkipListNode* ret = find(m_head, key, m_maxHeight - 1) ;
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<< key << " is not in the list" << endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<< "Node " << key << " is in the list" << endl;
        }
        return 1;
    }

}
int SkipList::del(const Key& key, bool verbose) {
    if (key.length() == 0){
      return 1;
    }
    SkipListNode* toBeDeleted = del(m_head, key, m_maxHeight - 1);

    if (toBeDeleted == NULL) {
        if (verbose) {
            cout<< "Node " << key << " is not in the list" << endl;
        }
    } else {
        delete toBeDeleted;
        if (verbose) {
            cout << "Node " << key << " is deleted from the list" << endl;
        }
    }
    return 1;
}

void SkipList::dump(char sep) {
    int length = -1;
    cout << "Current List: ";
    for (SkipListNode* iter = m_head; iter != NULL; iter = iter->nextAtLevel(0)) {
        length++;
        cout << string(*iter) << " ";
        cout << "(" << iter->height() << ":";
        for (unsigned i = 0; i < iter->height(); i++) {
            if (iter->nextAtLevel(i)) {
                cout << " "<< i << ":" << *(iter->nextAtLevel(i));
                cout.flush();
            }
        }
        cout << ")" << sep;
    }
    cout << length << " nodes in total." << endl;
}


/***********************************************************/
/***************  FUNCTIONS TO BE COMPLETED  ****************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

unsigned int SkipList::randHeight() {
  ////////////// Write your code below  ////////////////////////
  unsigned int i = 1;

  // generates a number between 1 to RAND_MAX
  int t = rand() + 1;
  int j = 2;
  
  // tries to find a height, where the probability is 1/2^j
  for (i = 1; i < m_maxHeight; i++) {
    if (t > (double)RAND_MAX/(double)j) break;
    j = j + j;
  }  
  
  return i;
}


int SkipList::add(SkipListNode* target, SkipListNode* newNode,
                  unsigned level) {
    if (target->nextAtLevel(level) != NULL &&
            *target->nextAtLevel(level) < *newNode) {
        countAdd++;
    }
    ////////////// Write your code below  ////////////////////////
    
    // sets t to be the next node after target at the same level
    SkipListNode* t = target->nextAtLevel(level);

    if (t == NULL || *newNode < *t) {

      // inserts newNode before target t
      if (level < newNode->height()) {
	newNode->setNextAtLevel(level, t);
	target->setNextAtLevel(level, newNode);
      }

      // recurssively adds the node into corresponding lower levels
      if (level > 0) add(target, newNode, level - 1);
      // returns 1 if level == 0
      return 1;
    }
    
    // goes down the node in the same level to try to find the position to add
    add(t, newNode, level);
    return 1;
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::find(SkipListNode* target, const Key& key,
                             unsigned level) {
    if (target->nextAtLevel(level) != NULL &&
            *target->nextAtLevel(level) < key) {
        countFind++;
    }
    ////////////// Write your code below  ////////////////////////

    // trying to find a key from an empty skip list returns null
    if (target == NULL) return NULL;

    if (*target == key) return target;

    SkipListNode * t = target->nextAtLevel(level);

    // if t hits the end of the level or if key is smaller than t
    // go down the level to try to find it
    if (t == NULL || key < *t) {
      if (level == 0) return NULL;
      return find(target, key, level-1);
    }
    // keep going down the list at the same level to find
    return find(t, key, level);
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::del(SkipListNode* target, const Key& key,
                            unsigned level) {
    if (target->nextAtLevel(level) != NULL &&
            *target->nextAtLevel(level) < key) {
        countDelete++;
    }
    ////////////// Write your code below  ////////////////////////

    // deleting from an empty skip list returns null
    if (target == NULL) return NULL;
    
    SkipListNode * t = target->nextAtLevel(level);

    // if hits the end of the current level, goes down the level
    if (t == NULL) {
      // if level is already 0, key is not found
      if (level == 0) return NULL;
      return del(target, key, level-1);
    }

    // node is found 
    if (*t == key) {
      target->setNextAtLevel(level, t->nextAtLevel(level));
      if (level == 0) return t;
      // if level is > 0, recurssively delete its corresponding node at lower levels
      return del(target, key, level-1);
    }

    // if the key is smaller than the node, means it can't be located after the node
    // go down the level to find it
    if (key < *t) {
      return del(target, key, level-1);
    }

    // if the key is larger than the node, keep checking in the same level
    return del(t, key, level);
}

