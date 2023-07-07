#include "LRU.h"
#include "FIFO.h"
#include "OPT.h"

int n;
int *arr;
// 1 2 3 4 1 2 5 1 2 3 4 5
// 1 1 1 4 4 4 5 5 5 5 5 5
//   2 2 2 1 1 1 1 1 3 3 3
//     3 3 3 2 2 2 2 2 4 4
// * * * * * * * * *
// Number of Page Fault: 9
void outputOfAlgorithm(int n, int *arr, int pageFrame, int **pageFrameArr, char *pageFaultArr)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < pageFrame; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (pageFrameArr[i][j] != -1)
                printf("%d\t", pageFrameArr[i][j]);
            else
                printf("\t");
        }
        printf("\n");
    }
    int temp = 0;
    for (int i = 0; i < n; ++i)
    {
        if (pageFaultArr[i] == '*')
            temp++;
        printf("%c\t", pageFaultArr[i]);
    }
    printf("\n");
    printf("Number of Page Fault: %d\n", temp);
}

int main()
{
    int option = -1;
    while (option != 1 && option != 2)
    {
        printf("\n--- Page Replacement algorithm ---\n");
        printf("1. Default referenced sequence\n");
        printf("2. Manual input sequence\n");
        // nhập sự lựa chọn
        printf("Your choice: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
        {
            printf("Default referenced sequence: ");
            // int input[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
            // int input[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
            // int input[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
            int input[] = {2, 1, 5, 2, 0, 5, 0, 4, 0, 0, 7};
            n = sizeof(input) / sizeof(input[0]);
            arr = (int *)malloc(n * sizeof(int));
            memcpy(arr, input, n * sizeof(int));
            for (int i = 0; i < n; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
            break;
        }
        case 2:
        {
            printf("inpur number of array: ");
            scanf("%d", &n);
            // khai báo mảng
            arr = (int *)malloc(n * sizeof(int));
            printf("Input referenced sequence: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            break;
        }
        default:
        {
            printf("Invalid input! try again.\n");
            break;
        }
        }
    }

    // mảng để lưu các page bị thay thế
    char *pageFaultArr = (char *)malloc(n * sizeof(char));

    // nhập số lượng page frame
    int pageFrame;
    printf("\n--- Page Replacement algorithm ---\n");
    printf("Input number of page frame: ");
    scanf("%d", &pageFrame);

    // create mảng 2 chiều để lưu các trang trong page frame
    int **pageFrameArr = (int **)malloc(pageFrame * sizeof(int *));
    for (int i = 0; i < pageFrame; i++)
    {
        pageFrameArr[i] = (int *)malloc(n * sizeof(int));
    }
    // gán tất cả giá trị = -1
    for (int i = 0; i < pageFrame; ++i)
    {
        for (int j = 0; j < n; ++j)
            pageFrameArr[i][j] = -1;
    }

    while (1)
    {
        printf("\n--- Page Replacement algorithm ---\n");
        printf("1. FIFO algorithm\n");
        printf("2. OPT algorithm\n");
        printf("3. LRU algorithm\n");
        int algorithmOption;
        printf("Your algorithm you want to choose: ");
        scanf("%d", &algorithmOption);
        switch (algorithmOption)
        {
        case 1:
        {
            printf("FIFO algorithm: \n");
            FIFO(n, arr, pageFrame, pageFrameArr, pageFaultArr);
            outputOfAlgorithm(n, arr, pageFrame, pageFrameArr, pageFaultArr);
            break;
        }
        case 2:
        {
            printf("OPT algorithm\n");
            OPT(n, arr, pageFrame, pageFrameArr, pageFaultArr);
            outputOfAlgorithm(n, arr, pageFrame, pageFrameArr, pageFaultArr);
            break;
        }
        case 3:
        {
            printf("LRU algorithm\n");
            LRU(n, arr, pageFrame, pageFrameArr, pageFaultArr);
            outputOfAlgorithm(n, arr, pageFrame, pageFrameArr, pageFaultArr);
            break;
        }
        default:
        {
            printf("Invalid input!\n");
            break;
        }
        }
    }

    free(arr);
    free(pageFaultArr);
    for (int i = 0; i < pageFrame; i++)
    {
        free(pageFrameArr[i]);
    }
    free(pageFrameArr);
    return 0;
