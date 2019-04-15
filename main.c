#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define INPUT 200                                                //edit input here

typedef struct {
    float left_EP;
    float right_EP;
}intervals;

intervals intervalArray[INPUT];
int start, end, i;
clock_t startTime, finishTime;
double runningTime;
char path[]= "small_overlap.txt";                                   	   //edit address of input file here


void main()
{
    readfile(path);                                                       	//passing the path of the file to read the text file
    startTime = clock();                                                	 //to start the timer
    fuzzySort(intervalArray, 0,INPUT);                                	  	//calling fuzzySort
    finishTime = clock();                                             	 	//ending the clock;
    runningTime=((double) (finishTime - startTime)) / CLOCKS_PER_SEC;
    printarray(intervalArray,runningTime);
}
/*For printing the sorted array and running time
*/
void printarray(intervals intervalArray[], double time){
    printf("%d intervals sorted in %f seconds\n", INPUT,time);
    for (int j=0; j<INPUT; j++){
        printf("%f,%f\n", intervalArray[j].left_EP,intervalArray[j].right_EP);
    }
}
/*For reading the input from text file and storing in intervalArray[]
*/
void readfile(char path[]){
    FILE *file;
    char ch;
    int j=0,t=0;

    file=fopen(path, "r");

    if(!file){
        printf("File not opened");
    }else{
        ch=getc(file);
        while(ch!=EOF && j<INPUT){
        if(t ==0){
            fscanf(file,"%f",&intervalArray[j].left_EP);
            t +=1;
        }
        else{
            fscanf(file,"%f",&intervalArray[j].right_EP);
            t--;
            j++;
        }
    }
    }
    fclose(file);
}
/* For swapping two intervals
*/
void exchange (intervals *a, intervals *b){
intervals tmp = *a;
*a = *b;
*b = tmp;
}
/* Method to perform the partition in the passed intervals arr[]
   using the last element of the intervals arr[]
   returns the Pivot Interval
*/
intervals partition(intervals arr[], int p, int r) {
    intervals intersectingInterval = arr[r-1];

    for (i = p; i < r-1 ; i++) {
        if (intersectingInterval.left_EP <= arr[i].right_EP){
            if(arr[i].left_EP <= intersectingInterval.right_EP){
                    if (arr[i].left_EP > intersectingInterval.left_EP)
                        intersectingInterval.left_EP = arr[i].left_EP;
                    if (arr[i].right_EP < intersectingInterval.right_EP)
                        intersectingInterval.right_EP = arr[i].right_EP;
            }
        }
      }

    // checking values for smaller intervals
    start= p-1;
    for (i = p; i <r-1; i++) {
        if (arr[i].right_EP < intersectingInterval.left_EP) {
            start +=1;
            exchange(&arr[i], &arr[start]);
        }
    }
    exchange(&arr[r-1], &arr[start+1]);

    //checking for intervals that are overlapping and moving them after the start
    end = start + 1;
    i = r-1;
    while (end <= i) {
       if (intersectingInterval.left_EP <= arr[i].right_EP){
           if((arr[i].left_EP <= intersectingInterval.right_EP)){
                exchange(&arr[end], &arr[i]);
            end += 1;
           }
       else {
            i-=1;
        }
       }
         else {
            i -= 1;
        }
    }
    return (intervals) {start+1, end};
}
/* Method to sort the intervalArray[] by calling partition(intervalArray,p,r)
   Then passing the Pivot Interval recursively to sort the intervals further
*/
void fuzzySort(intervals intervalArray[], int p, int r) {
    if (p < r-1) {
        intervals q = partition(intervalArray, p, r);
        fuzzySort(intervalArray, p, q.left_EP);
        fuzzySort(intervalArray, q.right_EP, r);
    }
}
