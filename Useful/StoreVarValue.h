#ifndef STOREVARVALUE_H
#define STOREVARVALUE_H

/**
 * The class is used as a template, for the tables we would create.
 * @tparam T generic
 */
template<class T>
class StoreVarValue {
    T value;
    bool initialize;
public:
    /**
     * Function name: StoreVarValue
     * The function operation: The function initializes the value to false
     */
    StoreVarValue() {
        this->initialize = false;
    }

    /**
     * Function name: getValue
     * The function operation: The function returns the value, depends
     * on the type
     * @return template variable
     */
    T getValue() { return this->value; }

    /**
     * Function name: checkIfInitialize
     * The function operation: The function returns the initialize value
     * @return bool
     */
    bool checkIfInitialize() { return this->initialize; }

    /**
     * Function name: setValue
     * The function operation: The function sets the value
     * @param value given value
     */
    void setValue(T value) { this->value = value; }

    /**
     * Function name: setInitialize
     * The function operation: The function sets the initialize
     * @param initialize given initialize
     */
    void setInitialize(bool initialize) { this->initialize = initialize; }
};

#endif
