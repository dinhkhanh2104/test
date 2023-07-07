#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

void OPT(int n, int *arr, int pageFrame, int **pageFrameArr, char *pageFaultArr)
{
    // gán giá trị đầu tiên của mảng vào page frame
    pageFrameArr[0][0] = arr[0];
    // gán giá trị đầu tiên của mảng vào page fault
    pageFaultArr[0] = '*';
    int i = 1;
    int checkEmpty = false;
    int checkSame = false;
    while (i < n)
    {
        checkEmpty = false;
        checkSame = false;
        for (int j = 0; j < pageFrame; ++j)
        {
            pageFrameArr[j][i] = pageFrameArr[j][i - 1];
        }
        for (int j = 0; j < pageFrame; ++j)
        {
            if (pageFrameArr[j][i] == arr[i])
            {
                checkSame = true;
                break;
            }
            if (pageFrameArr[j][i] == -1)
            {
                checkEmpty = true;
                pageFrameArr[j][i] = arr[i];
                break;
            }
        }
        if (checkEmpty)
        {
            pageFaultArr[i] = '*';
        }
        else
        {
            if (checkSame)
            {
                pageFaultArr[i] = ' ';
            }
            else
            {
                pageFaultArr[i] = '*';
                int *temp = (int *)malloc(pageFrame * sizeof(int));
                for (int z = 0; z < pageFrame; ++z)
                {
                    temp[z] = 10000;
                }
                for (int j = 0; j < pageFrame; ++j)
                {
                    for (int k = i + 1; k < n; ++k)
                    {
                        if (pageFrameArr[j][i] == arr[k])
                        {
                            temp[j] = k;
                            break;
                        }
                    }
                }
                int max = temp[0];
                int index = 0;
                for (int z = 0; z < pageFrame; ++z)
                {
                    if (temp[z] > max)
                    {
                        max = temp[z];
                        index = z;
                    }
                }
                free(temp);
                pageFrameArr[index][i] = arr[i];
            }
        }
        i++;
    }
    // duyệt từ phần tử thứ 2 của mảng
    // 2 1 5 2 0 5 0 4 0 0 7
    // 2 2 2 2 0 0 0 0 0 0 7
    //   1 1 1 1 1 1 4 4 4 4
    //     5 5 5 5 5 5 5 5 5
    // * * *   *     *     *
    // Number of Page Fault: 6
}
