#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class Matrix {
private:
    int row, col;
    T** entr;
public:
    inline Matrix();
    // costruttore di default
    Matrix(int r, int c);
    // costruttore di matrice rxc
    Matrix(int r, int c, T initval);
    // costruttore di matrice rxc con tutte le entrate = initval
    Matrix(int r, int c, T* array);
    // costruttore di matrice rxc con entrate da array[rxc] elencate per righe
    Matrix(const Matrix<T> &m);
    // costruttore di copia da m
    ~Matrix();
    // deallocatore
    inline int Row() { return  row; }
    // ritona il numero delle righe
    inline int Col() { return col; }
    // ritona il numero delle colonne
    inline T*& operator[](int i) { return entr[i]; }
    // consente l'uso della notazione m[i][j] in lettura/scrittura
    Matrix<T>& operator=(const Matrix<T> &m);
    // sovraccarico di =, permette di assegnare matrici a var. di matrici
    template <class S>
    friend ostream& operator<<(ostream &os, const Matrix<S> &m);
    // stampa m per righe con il comando cout << m;
};

template <class T>
inline Matrix<T>::Matrix() {row = 0; col = 0; entr = NULL; }

template <class T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < row; i++)
        delete entr[i];
    delete entr;
}

template <class T>
Matrix<T>::Matrix(int r, int c)
{
    row = r; col = c;
    entr = new T*[row];
    for(int i = 0; i < row; i++)
        entr[i] = new T[col];
}

template <class T>
Matrix<T>::Matrix(int r, int c, T initval)
{
    row = r; col = c;
    entr = new T*[row];
    for(int i = 0; i < row; i++)
        entr[i] = new T[col];
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            entr[i][j] = initval;
}


template <class T>
Matrix<T>::Matrix(int r, int c, T* array)
{
    row = r; col = c;
    entr = new T*[row];
    for(int i = 0; i < row; i++)
        entr[i] = new T[col];
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            entr[i][j] = array[i*col + j];
}

template <class T>
Matrix<T>::Matrix(const Matrix<T> &m)
{
    row = m.row; col = m.col;
    entr = new T*[row];
    for(int i = 0; i < row; i++)
        entr[i] = new T[col];
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            entr[i][j] = m.entr[i][j];
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &m)
{
    for(int i = 0; i < row; i++)
        delete entr[i];
    delete entr;
    row = m.row; col = m.col;
    entr = new T*[row];
    for(int i = 0; i < row; i++)
        entr[i] = new T[col];
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            entr[i][j] = m.entr[i][j];
    return *this;
}

template <class S>
ostream& operator<<(ostream &os, const Matrix<S> &m)
{
    for(int i = 0; i < m.row; i++)
    {
        for(int j = 0; j < m.col; j++)
            os << m.entr[i][j] << '\t';
        os << endl;
    }
    return os;
}