#include "../include/global.h"

int SparseMatrix(int **M, int **S, int *D)
{
    // Finds max dimensions of the matrix.
    int max = (*D > (*D + 1)) ? *D : *D + 1;

    int nonzero = 0;

    // Iterate through to find non zero elements.
    for (int row = 0; row < *D; row++)
    {
        for (int col = 0; col < *(D + 1); col++)
        {
            if (*(*(M + row) + col) != 0)
            {
                nonzero++;
            }
        }
    };

    // Make sure the nonzero elements are <= max row dimensions.
    if (nonzero > max)
    {
        return -1;
    };

    int count = 0;

    // Next spot in sparse matrix.
    int spot = 0;

    // Iterate through to find non zero elements.
    for (int row = 0; row < *D; row++)
    {
        for (int col = 0; col < *(D + 1); col++)
        {
            if (*(*(M + row) + col) != 0)
            {
                // Add row, col, value into sparse matrix.
                *(*(S + 0) + spot) = row;
                *(*(S + 1) + spot) = col;
                *(*(S + 2) + spot) = *(*(M + row) + col);
                spot++;
                count++;
            }
        }
    };

    return count;
}

int Addition(int **M, int **N, int **A, int *D)
{
    // Dimensions.
    int rowM = *D;
    int colM = *(D + 1);
    int rowN = *(D + 2);
    int colN = *(D + 3);
    int rowA = *(D + 4);
    int colA = *(D + 5);

    // Find smallest dimensions of M and N.
    int colMN = (colM < colN) ? colM : colN;
    int rowMN = (rowM < rowN) ? rowM : rowN;

    // Find smallest dimensions of MN and A.
    int colMNA = (colMN < colA) ? colMN : colA;
    int rowMNA = (rowMN < rowA) ? rowMN : rowA;

    // Iterate through the overlapped portions of matrices M, N, A.
    for (int row = 0; row < rowMNA; row++)
    {
        for (int col = 0; col < colMNA; col++)
        {
            // Add M and N to A.
            *(*(A + row) + col) = (*(*(M + row) + col)) + (*(*(N + row) + col));
        }
    };

    // Case 1: M and N have the same dimensions.
    if (colM == colN && rowM == rowN)
    {
        // A's dimensions are smaller than M and N.
        if (colA < colM || rowA < rowM)
            return -3;

        // A's dimensions are bigger than M and N.
        else if (colA > colM || rowA > rowM)
            return 2;

        // A's dimensions are the same as M and N.
        else
            return 1;
    }

    // Case 2: M and N have different dimensions.
    else
    {
        // A's dimensions cant fit MN.
        if (colA >= colMN && rowA >= rowMN)
            return -1;

        // A's dimensions are smaller than MN.
        else
            return -2;
    }
}

int Multiplication(int **M, int **N, int **A, int *D)
{
    // Dimensions.
    int rowM = *D;
    int colM = *(D + 1);
    int rowN = *(D + 2);
    int colN = *(D + 3);
    int rowA = *(D + 4);
    int colA = *(D + 5);

    // Find the smallest possible combination of M's col dimension and N's row dimension.
    int combo = (colM < rowN) ? colM : rowN;

    // Find the smallest possible combination for A.
    int rowCombo = (rowA < rowM) ? rowA : rowM;
    int colCombo = (colA < colN) ? colA : colN;

    // For each index of A, perform matrix multiplication on M and S.
    for (int row = 0; row < rowCombo; row++)
    {
        for (int col = 0; col < colCombo; col++)
        {
            // Multiply M's corresponding row with S's corresponding column.
            int sum = 0;

            // colM and rowN must be the same size to multiply.
            for (int i = 0; i < combo; i++)
            {
                sum += ((*(*(M + row) + i)) * (*(*(N + i) + col)));
            }

            *(*(A + row) + col) = sum;
        };
    };

    // M and N are compatible.
    if (colM == rowN)
    {
        // A has compatable dimensions with M and N.
        if (rowA == rowM && colA == colN)
            return 1;

        // A has bigger dimensions than M and N.
        else if (rowA > rowM && colA > colN)
            return 2;

        // A has smaller dimensions than M and N.
        else
            return -3;
    }

    // M and N are not compatible.
    else
    {
        // A has bigger dimensions than M and N.
        if (rowA >= rowM && colA >= colN)
            return -1;

        // A has smaller dimensions than M and N.
        else
            return -2;
    }
}

int Transpose(int **A, int **AT, int *D)
{
    // Dimensions.
    int rowA = *D;
    int colA = *(D + 1);
    int rowAT = *(D + 2);
    int colAT = *(D + 3);

    // Find overlapping dimensions.
    int rowCombo = (rowA < colAT) ? rowA : colAT;
    int colCombo = (colA < rowAT) ? colA : rowAT;

    // Iterate through matrix A and flip its rows/columns.
    for (int row = 0; row < rowCombo; row++)
    {
        for (int col = 0; col < colCombo; col++)
        {
            *(*(AT + col) + row) = *(*(A + row) + col);
        }
    }

    // AT dimensions are the same as A.
    if (rowA == colAT && colA == rowAT)
        return 1;

    // AT dimensions are bigger than A.
    else if (rowA < colAT && colA < rowAT)
        return 2;

    // AT dimensions are smaller than A.
    else
        return -1;
}

// Helper functions for Testing
int **initializeMatrix(int n, int m, int *values)
{
    int **ret = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        ret[i] = (int *)malloc(m * sizeof(int));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ret[i][j] = values[i * m + j];
        }
    }
    return ret;
}

void freeMatrix(int n, int **M)
{
    for (int i = 0; i < n; i++)
    {
        free(M[i]);
    }
    free(M);
}
