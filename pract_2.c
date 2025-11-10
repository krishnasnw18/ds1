#include <stdio.h>

void swap(float *xp, float *yp) 
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(float arr[], int n) 
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}
void bubbleSort(float arr[], int n) 
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
void displayTopFiveScores(float arr[], int n) 
{
    printf("\nTop five scores:\n");
   
    int count = (n < 5) ? n : 5; 
    for (int i = n - 1; i >= n - count; i--)
    { 
        printf("%.2f\n", arr[i]);
    }
}
int main() 
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    float percentages[n];

    printf("Enter the first-year percentages for %d students:\n", n);
    for (int i = 0; i < n; i++) 
    {
        printf("Student %d percentage: ", i + 1);
        scanf("%f", &percentages[i]);
    }

    selectionSort(percentages, n);

    printf("\nPercentages after sorting (ascending order):\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%.2f ", percentages[i]);
    }
    printf("\n");

    displayTopFiveScores(percentages, n);

    return 0;
}