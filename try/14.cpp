#include <iostream>
#include <stdlib.h>
using namespace std;

class Matrix
{
private:
    int row, col;
    int* m;

public:
    Matrix(int r = 0, int c = 0)
    {
        row = r;
        col = c;

        if (row > 0 && col > 0)
        {
            m = new int[row * col];
            for (int i = 0; i < row * col; i++)
                cin >> m[i];
        }
        else
        {
            m = NULL;
        }
    }

    Matrix(const Matrix& B)
    {
        row = B.row;
        col = B.col;

        if (row * col)
        {
            m = new int[row * col];
            for (int i = 0; i < row * col; i++)
                m[i] = B.m[i];
        }
        else
        {
            m = NULL;
        }
    }

    ~Matrix()
    {
        if (m)
            delete[] m;
    }

    Matrix operator+(const Matrix& B)
    {
        if (row != B.row || col != B.col)
        {
            cout << "program terminated!";
            exit(0);
        }

        Matrix temp;
        temp.row = row;
        temp.col = col;
        temp.m = new int[row * col];

        for (int i = 0; i < row * col; i++)
            temp.m[i] = m[i] + B.m[i];

        return temp;
    }

    Matrix& operator=(const Matrix& B)
    {
        if (this == &B)
            return *this;

        delete[] m;

        row = B.row;
        col = B.col;

        if (row * col)
        {
            m = new int[row * col];
            for (int i = 0; i < row * col; i++)
                m[i] = B.m[i];
        }
        else
        {
            m = NULL;
        }

        return *this;
    }

    void disp()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                cout << *(m + i * col + j) << '\t';
            cout << endl;
        }
    }
};

int main()
{
    int row_a, col_a, row_b, col_b;

    cin >> row_a >> col_a;
    Matrix A(row_a, col_a);

    cin >> row_b >> col_b;
    Matrix B(row_b, col_b), C;

    C = A + B;
    C.disp();
    cout << "\n" << endl;
    A = B;
    A.disp();

    return 0;
}