
// FCAI-CU - OOP course - 2022 - Assignment 3
//Program Name : Vector from scratch
// Program Description : this program makes the data structre "vector" from scratch and flexible using many data types
// Author :  Mariam Esmat Ahmed          
// ver3 of Date : 23rd of December 2022

using namespace std;

template <typename mmvector>
class Iteratormm
{

public:
    using ValueType = typename mmvector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

    Iteratormm(PointerType ptr)
    {
        m_ptr = ptr;
    }
    Iteratormm& operator++()
    {
        m_ptr++;
        return *this;
    }

    Iteratormm& operator++(int)
    {
        Iteratormm iter =  *this;
        ++(*this);
        return iter;
    }

    Iteratormm &operator+(int inc)
    {
        for (int i = 0;i<inc;i++)
            ++m_ptr;
        return *this;
    }

    long long  operator-(PointerType dec)
    {
        return (m_ptr - dec);
    }


    ReferenceType operator[](int index)
    {
        return *(m_ptr+index);
    }

    ReferenceType operator*()
    {
        return *m_ptr;
    }

    bool operator == (const Iteratormm& otherItr)const
    {
        return m_ptr == otherItr.m_ptr;
    }

    bool operator != (const Iteratormm& otherItr)const
    {

        return !(m_ptr == otherItr.m_ptr);
    }


private:
    PointerType m_ptr;

};


template<typename T>
class mmVector
{
public:
    using ValueType = T;
    using iterator = Iteratormm<mmVector<T>>;
private:

    T *ptr = nullptr;
    int vecSize = 0;
    int vecCapacity = 0;

    void reAlloc(int newCap) {
        T *newVec = new T[newCap];

        if (newCap < vecSize)
            vecSize = newCap;

        for (int i = 0; i < vecSize; i++)
            newVec[i] = ptr[i];
        delete[] ptr;
        ptr = newVec;
        vecCapacity = newCap;
    }


public:



    mmVector()//empty constructor
    {
        // No content is added, size = 0
        // Assign a default size value
        ptr = new T[1];
        vecCapacity = 1;
        vecSize = 0;
    }


    mmVector (int x)//parametrized constructor
    {
        ptr = new T[x];
        vecCapacity = x;
        vecSize = 0;
    }


    mmVector (T arr[] , int  n ) // Initialize by n items from array
    {
        vecCapacity = n;
        vecSize = n;
        ptr = new T[n];
        for (int i = 0 ; i < n;i++ )
        {
            ptr[i] = arr[i];
        }
    }

    mmVector(const mmVector& myVec ) //copy constructor  Initialize with a copy
    {
        cout<<"copy constrcutor"<<endl;
        vecCapacity = myVec.vecCapacity;
        vecSize = myVec.vecSize;
        ptr = new T[vecCapacity];
        for(int i =0 ; i< myVec.vecSize;i++)
            ptr[i]= myVec.ptr[i];

    }

    ~mmVector()  //deallocating mmvector
    {
        cout << "vector is deleted" << endl;
        delete[] ptr;
    }


    mmVector &operator=(const mmVector& myVec )  // Copy assignment
    {
        cout<<"Copy assignment"<<endl;
        delete[] this->ptr ;
        this->vecCapacity = myVec.vecCapacity;
        this->vecSize = myVec.vecSize;
        this->ptr = new T[vecCapacity];
        // this->reAlloc(myVec.vecCapacity);
        for(int i =0 ; i< myVec.vecSize;i++)
            this->ptr[i]= myVec.ptr[i];

        return *this;
    }


    mmVector& operator=( mmVector&& other) noexcept// Move assignment
    {
        cout<<"Move assignment"<<endl;
        vecCapacity = other.vecCapacity;
        vecSize = other.vecSize;
        delete[] ptr;
        ptr = other.ptr;
        for(int i =0 ; i< other.vecSize;i++)
            ptr[i]= other.ptr[i];
        other.ptr= nullptr;
        other.vecCapacity=0;
        other.vecSize=0;
    }

    // Access operations

    T& operator[](int index) //overloads the [] operator , Access item by reference
    {
        if (index >= vecSize)
        {
            std::cout << "This index is out of bound";
            exit(0);
        }
        else
            return ptr[index];
    }


    // Modifying operations

    void push_back(const T& data) //adds data the end of vector
    {
        // Increase capacity of needed
        if (vecSize >= vecCapacity)
            reAlloc(2*vecCapacity);

        // Inserting data
        ptr[vecSize] = data;
        vecSize++;
    }


    T pop_back()// Remove and return last element in vec
    {
        T popped = this->ptr[vecSize-1];
        if(vecSize>0) {
            vecSize--;
            this->ptr[vecSize-1].~T();
        }
        return popped;
    }



    void erase(iterator i) {// Remove item at index

        long long index = (i - ptr);
        if (index < 0 || index >= vecSize) {
            cout << "Index out of range";
            return;
        }

        for (int i = index; i < vecSize - 1; i++) {
            ptr[i] = ptr[i + 1];
        }
        vecSize--;
    }

    void erase(iterator i1 , iterator i2) {// Remove items in range

        long long index1 = (i1-ptr),index2 = i2-ptr;

        if (index1 < 0 || index1 >= vecSize || index2 < 0 || index2 >= vecSize) {
            cout << "Index out of range";
            return;
        }
        if (index1 > index2) {
            cout << "Invalid range";
            return;
        }
        for (int i = index1; i < vecSize - (index2 - index1 + 1); i++) {
            ptr[i] = ptr[i + (index2 - index1 + 1)];
        }
        vecSize -= (index2 - index1 + 1);
    }

    void clear()  // Delete all vector content
    {
        T* temp = new T[1];
        delete[] ptr;
        ptr = temp;
        vecCapacity = 1;
        vecSize = 0;
    }

    void insert(iterator pos, const T elem) {

        long long index = pos - ptr;

        if (index < 0 || index >= vecSize) {
            cout<< "index out of range\n";
            return ;
        }
        if (vecSize >= vecCapacity) {
            this->resize();
        }
        for (int i = vecSize; i > index; i--) {
            ptr[i] = ptr[i - 1];
        }
        ptr[index] = elem;
        vecSize++;

    }


    // Iterators
    // Supports *, + and ++ operations at least
    // Can use: typedef T* iterator
    // Or u can use std::iterator so you can
    // apply STL algorithms on mmVector




    iterator begin() // Return an iterator (T*)
    {
        return ptr;
    }


    iterator end()// Return an iterator (T*)
    {
        return ptr+vecSize;
    }



    // Comparison operations

    bool operator==(const mmVector<T>&myVec)// Return true if ==
    {
        if(this->vecSize != myVec.vecSize)
            return false;
        else
        {
            for(int i =0 ; i< myVec.vecSize ; i++)
            {
                if(this->ptr[i] != myVec.ptr[i])
                    return false;
            }
            return true;
        }
    }

    bool operator<(const mmVector<T> &v) // Compares item by item
    // Return true if first different item in this is < in other
    {

        int sz = min(v.vecSize, this->vecSize);

        for (int i = 0; i < sz; i++)
        {
            if (this->ptr[i] < v.ptr[i])
                return true;
            else if (this->ptr[i] > v.ptr[i])
                return false;
        }
        return false;
    }


    // Capacity operations
    int size() const// Return current size of vec
    {
        return vecSize;
    }

    int capacity() const// Return size of current allocated array
    {
        return vecCapacity;
    }


    int resize()  // Relocate to bigger space (capacity)
    {
        T* temp = new T[2 * vecCapacity];
        // copying old array elements to new array
        for (int i = 0; i < vecCapacity; i++)
            temp[i] = ptr[i];
        // deleting previous array
        delete[] ptr;
        vecCapacity *= 2;
        ptr = temp;
        delete[] temp;
    }


    bool empty()  // Return true if size is 0
    {
        if(vecSize)
            return false;
        else
            return true;
    }

    // Friends
    friend ostream& operator<< (ostream& out, mmVector<T> &v)
    {
        out << "[";
        for (int i = 0; i < v.vecSize; ++i) {
            out << v[i];
            if (i != v.vecSize - 1)
                out << ", ";
        }
        out << "]\n";
        return out;
    }

};



int main()
{


    //this part is a test for initializing with a size or with another vector(copy constructor) , push back , pop back
    //  capacity , size , << overloading  , [] overloading

    mmVector<int> vec1(4);
    vec1.push_back(1);
    vec1.push_back(3);
    vec1.push_back(0);
    vec1.push_back(8);
    vec1.push_back(7);
    cout << "vec1 capacity = " << vec1.capacity() << endl;
    cout << "vec1 size = " << vec1.size() << endl;
    cout << vec1;
    cout << "the popped element = " << vec1.pop_back() << endl;
    cout << "vec1 capacity after pop back = " << vec1.capacity() << endl;
    cout << "vec1 size after pop back  = " << vec1.size() << endl;
    mmVector<int> vec2(vec1);
    cout << vec2;
    cout << "firts element in vec2 : " << vec2[0] << endl;
    

    //--------------------------------------------++--------------------------------------------------

    //this part is a test for empty , resize , initializing with elements from an array
    /*
    mmVector<int> vec3;
    cout << "check if vec3 is empty aka has no elements : " << vec3.empty() << endl;
    vec3.resize();
    cout << "vec3 capacity after resize = " << vec3.capacity() << endl;
    cout << "vec3 size after resize = " << vec3.size() << endl;
    vec3.push_back(1);
    vec3.push_back(2);
    cout << vec3;

    int arr[4] = {1, 2, 3, 4};
    mmVector<int> vec4(arr, 2);
    cout << "vec4 capacity = " << vec4.capacity() << endl;
    cout << "vec4 size = " << vec4.size() << endl;
    cout << vec4;
    */

    //--------------------------------------------++--------------------------------------------------

    //this part is a test for overloading == , overloading < , deep copy assignment , begin and end iterator
    /*
    mmVector<int> vec5;
    mmVector<int> vec6;
    vec5.push_back(1);
    vec5.push_back(2);
    vec6.push_back(9);
    vec6.push_back(2);
    bool check;
    check = (vec5 == vec6);
    cout << "check if the two vectors are equal : " << check << endl;
    check = (vec5 < vec6);
    cout << "check if vec5 < vec6 : " << check << endl;
    mmVector<int> vec7;
    mmVector<int> vec8;
    vec7.push_back(1);
    vec7.push_back(9);
    vec7.push_back(1);
    vec7.push_back(9);
    vec7.push_back(1);
    vec7.push_back(9);
    //deep copy assignment
    vec8 = vec7;
    for (mmVector<int>::iterator it = vec8.begin(); it != vec8.end(); it++)
      cout << *it <<" ";
    cout <<endl ;
    */

    //--------------------------------------------++--------------------------------------------------

    //this part tests erase(it) ,erase(it,it) , insert at (it)
    /*
    mmVector<int>vec9(4);
    vec9.push_back(1);
    vec9.push_back(2);
    vec9.push_back(3);
    vec9.push_back(4);
    vec9.push_back(5);
    vec9.push_back(6);
    cout<<vec9;

    vec9.erase(vec9.begin()+1 );
    cout<<vec9;

    vec9.erase(vec9.begin()+1, vec9.begin()+3);
    cout<<vec9;
    vec9.insert(vec9.begin()+1 , 8);
    cout<<vec9;
    */

}
