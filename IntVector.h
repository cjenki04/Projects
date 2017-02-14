/*
 * A replacement for (integer) arrays that lets you say dynamically
 * how big the array should be.
 *
 * Mark A. Sheldon, Tufts University
 * Spring 2013
 *
 */

class IntVector
{
public:
        IntVector(); //constuctor

        //constuctor with init size
        IntVector(int initialSize); 
        //copy constuctor
        IntVector(const IntVector &source);
        //assignment overload
        IntVector& operator=(const IntVector &rhs);
        //destuctor
        ~IntVector();

        /*
         * Makes the vector have a size and capacity of 0 and 
         * recycles heap-allocated storage.
         */
        void destroy();

        /*
         * Return integer value at given index.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        int get(int index) const;

        /*
         * Set array element at given index to newVal.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        void set(int index, int newVal);

        /*
         * Return reference to array slot at given index.
         * This permits subscripted access to vector as 
         * L-value and/or R-value.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        int  &operator[](int index);

        /* Add newVal to end of vector, increasing current size by one. */
        void  add(int newVal);

        /* Return current size of vector. */
        int size() const;

        /* Return current capacity of vector */
        int capacity() const;

private:
        int array_size;
        int array_cap; 
        int *dynamic_array ; 
        void expand();
};
