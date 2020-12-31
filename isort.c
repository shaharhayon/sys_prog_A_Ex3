#define SIZE 50
#include <stdio.h>
#include <stdlib.h>

void shift_element(int *arr, int i)
{
    for (int idx = i; idx >= 0; idx--)
    {
        *(arr + idx + 1) = *(arr + idx);
    }
    *arr = 0;
}

void insertion_sort(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        int current_item = *(arr + i);
        for (int j = 0; j < i; j++)
        {
            if (current_item < *(arr + j))
            {
                shift_element(arr + j, i - j - 1);
                *(arr + j) = current_item;
                break;
            }
        }
    }
}

int main()
{
    int arr[SIZE];
    printf("Enter %d numbers: ", SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        scanf("%d", arr + i);
    }
    insertion_sort(arr, SIZE);
    for (int i = 0; i < SIZE -1; i++)
    {
        printf("%d,", *(arr + i));
    }
        printf("%d\n", *(arr + SIZE - 1));

}