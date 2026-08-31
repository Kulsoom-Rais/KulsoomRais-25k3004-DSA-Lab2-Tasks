#include <iostream>
#include <cstdlib>

using namespace std;

class Image
{
private:
    int rows;
    int cols;
    int* data;

public:

   
    Image()
    {
        rows = 0;
        cols = 0;
        data = NULL;
    }


 
    Image(int r, int c)
    {
        rows = r;
        cols = c;

        data = new int[rows * cols];

       
        for (int i = 0; i < rows * cols; i++)
        {
            data[i] = 0;
        }
    }

    Image(const Image& other)
    {
        rows = other.rows;
        cols = other.cols;

        if (rows == 0 || cols == 0)
        {
            data = NULL;
        }
        else
        {
            data = new int[rows * cols];

            for (int i = 0; i < rows * cols; i++)
            {
                data[i] = other.data[i];
            }
        }
    }


    Image& operator=(const Image& other)
    {
        
        if (this == &other)
        {
            return *this;
        }

        
        delete[] data;

       
        rows = other.rows;
        cols = other.cols;

        
        if (rows == 0 || cols == 0)
        {
            data = NULL;
        }
        else
        {
            data = new int[rows * cols];

            
            for (int i = 0; i < rows * cols; i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }


  
    ~Image()
    {
        delete[] data;
    }


   
    int& operator()(int row, int col)
    {
        if (row < 0 || row >= rows ||
            col < 0 || col >= cols)
        {
            cout << "Error: Array index out of bounds!" << endl;
            exit(1);
        }

        
        return data[row * cols + col];
    }


    
    int operator()(int row, int col) const
    {
        if (row < 0 || row >= rows ||
            col < 0 || col >= cols)
        {
            cout << "Error: Array index out of bounds!" << endl;
            exit(1);
        }

        return data[row * cols + col];
    }


    
    Image applyKernel()
    {
        
        if (rows < 3 || cols < 3)
        {
            cout << "Error: Image must be at least 3x3!" << endl;
            exit(1);
        }

        
        int newRows = rows - 3 + 1;
        int newCols = cols - 3 + 1;

        
        Image result(newRows, newCols);

        
        for (int i = 0; i < newRows; i++)
        {
            for (int j = 0; j < newCols; j++)
            {
                int sum = 0;

                
                for (int ki = 0; ki < 3; ki++)
                {
                    for (int kj = 0; kj < 3; kj++)
                    {
                        
                        sum = sum + (*this)(i + ki, j + kj);
                    }
                }

                result(i, j) = sum;
            }
        }

        return result;
    }


    
    void display()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << (*this)(i, j) << "\t";
            }

            cout << endl;
        }
    }
};


int main()
{
 

    Image img(5, 5);

    int values[5][5] =
    {
        {11, 22, 33, 44, 55},
        {20, 40, 60, 80, 100},
        {30, 60, 90, 120, 150},
        {40, 80, 120, 160, 200},
        {50, 100, 150, 200, 250}
    };

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            img(i, j) = values[i][j];
        }
    }


    cout << "Original Image (5 x 5):" << endl;

    img.display();


    Image output = img.applyKernel();


    cout << endl;
    cout << "Output Image after 3x3 Kernel (3 x 3):" << endl;

    output.display();

    return 0;
}
