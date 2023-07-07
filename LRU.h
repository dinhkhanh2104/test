#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PAGE 100


void LRU(int n, int *arr, int pageFrame, int **pageFrameArr, char *pageFaultArr)  
{
    int ref[MAX_PAGE] = {-1};
    int curr = 0;

    // The first page
    pageFrameArr[0][0] = arr[0];
    ref[arr[0]] = 0;
    pageFaultArr[0] = '*';
    curr++;

    
    // Other pages
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < curr; j++)
            pageFrameArr[j][i] = pageFrameArr[j][i - 1];

        // Check if the page is existing (Yes -> no page fault, No -> page fault)
        bool existing = false;
        for (int j = 0; j < curr; j++)
        {
            if (pageFrameArr[j][i] == arr[i])
                existing = true;
        }

        if (!existing)
        {
            if (curr < pageFrame)
            {
                pageFrameArr[curr][i] = arr[i];
                curr++;
            }
            else
            {
                int minRefIndex = 0;
                for (int j = 1; j < curr; j++)
                {
                    if (ref[pageFrameArr[j][i]] < ref[pageFrameArr[minRefIndex][i]])
                        minRefIndex = j;
                }
                pageFrameArr[minRefIndex][i] = arr[i];
            }

            pageFaultArr[i] = '*';
        }

        // Update reference
        ref[arr[i]] = i;
    }
}