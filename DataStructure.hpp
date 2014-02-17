#ifndef DATASTRUCTURE_HPP_
#define DATASTRUCTURE_HPP_

class DataStructure {

public:
    DataStructure() {
        countAdd = 0;
        countDelete = 0;
        countFind = 0;
    }
    virtual ~DataStructure() {}

    void resetCountAdd() {
        countAdd = 0;
    }
    void resetCountFind() {
        countFind = 0;
    }
    void resetCountDelete() {
        countDelete = 0;
    }

    unsigned getCountAdd() {
        return countAdd;
    }
    unsigned getCountDelete() {
        return countDelete;
    }
    unsigned getCountFind() {
        return countFind;
    }

protected:
    unsigned countAdd;
    unsigned countDelete;
    unsigned countFind;

};

#endif /*DATASTRUCTURE_HPP_*/

