#include <iostream>
#include <SDL2/SDL.h>
#include <time.h>
#include <limits>
#include <chrono>
using namespace std::chrono;
using namespace std;

//Setting up the Dimensions of Window
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

//Allocating number of rectangles according to screen size
const int arr_size = 100;
const int rect_size = 10;

int Array[arr_size];
int Barray[arr_size];

bool complete = false;

//Initialising window and renderer
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

//animation speed
int delay;


void visualise(int swap_rect1 = -1, int swap_rect2 = -1, int finalised_rect = -1){
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j = 0;
    for(int i = 0; i <= WINDOW_WIDTH - rect_size; i += rect_size){
        SDL_PumpEvents();

        SDL_Rect rect = {i, 0, rect_size, Array[j]};
        if(complete){
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        else if(j == swap_rect1 || j == finalised_rect){
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if(j == swap_rect2){
            SDL_SetRenderDrawColor(renderer, 165, 105, 189, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}


//algorithm for bubble sort
void bubble_sort(){
    for(int i = 0; i < arr_size - 1; i++){
        for(int j = 0; j < arr_size - 1 - i; j++){
            
            if(Array[j + 1] < Array[j]){
                int temp = Array[j];
                Array[j] = Array[j + 1];
                Array[j + 1] = temp;

                visualise(j + 1, j, arr_size - i);
            }
            SDL_Delay(delay);
        }
    }
}

//algorithm for Selection sort
void selection_sort()
{
    int minIndex;
    for(int i = 0; i < arr_size - 1; i++)
    {
        minIndex = i;
        for(int j = i + 1; j < arr_size; j++)
        {
            if(Array[j] < Array[minIndex])
            {
                minIndex = j;
                visualise(i, minIndex);
            }
            SDL_Delay(1);
        }
        int temp = Array[i];
        Array[i] = Array[minIndex];
        Array[minIndex] = temp;
    }
}

//algorithm for Insertion sort
void insertion_sort(){
    for(int i = 1; i < arr_size; i++)
        {
            int j = i - 1;
            int temp = Array[i];
            while(j >= 0 && Array[j] > temp)
            {
                Array[j + 1] = Array[j];
                j--;

                visualise(i, j+1);
                SDL_Delay(delay);
            }
            Array[j+1] = temp;
        }
}

//Algorithm for merge sort
void merge2SortedArrays(int a[], int si, int ei);
void mergeSort(int a[], int si, int ei)
{
    if(si>=ei)
    {
        return;
    }
    int mid=(si+ei)/2;

    mergeSort(a, si, mid);
    mergeSort(a, mid+1, ei);

    merge2SortedArrays(a, si, ei);
}

void merge2SortedArrays(int a[], int si, int ei){
    int size_output=(ei-si)+1;
    int* output=new int[size_output];

    int mid=(si+ei)/2;
    int i=si, j=mid+1, k=0;
    while(i<=mid && j<=ei)
    {
        if(a[i]<=a[j])
        {
            output[k]=a[i];
            visualise(i, j);
            i++;
            k++;
        }
        else
        {
            output[k]=a[j];
            visualise(i, j);
            j++;
            k++;
        }

    }
    while(i<=mid)
    {
        output[k]=a[i];
        visualise(-1, i);
        i++;
        k++;
    }
    while(j<=ei)
    {
        output[k]=a[j];
        visualise(-1, j);
        j++;
        k++;
    }
    int x=0;
    for(int l=si; l<=ei; l++)
    {
        a[l]=output[x];
        visualise(l);
        SDL_Delay(delay);
        x++;
    }
    delete []output;
}

//Algorithm for quick sort
int partition_array(int a[], int si, int ei);
void quick_sort(int a[], int si, int ei){
    if(si>=ei)
    {
        return;
    }

    int c = partition_array(a, si, ei);
    quick_sort(a, si, c-1);
    quick_sort(a, c+1, ei);

}

int partition_array(int a[], int si, int ei)
{
    int count_small=0;

    for(int i=(si+1);i<=ei;i++)
    {
        if(a[i]<=a[si])
        {
            count_small++;
        }
    }
    int c=si+count_small;
    int temp=a[c];
    a[c]=a[si];
    a[si]=temp;
    visualise(c, si);

    int i=si, j=ei;

    while(i<c && j>c)
    {
        if(a[i]<= a[c])
        {
            i++;
        }
        else if(a[j]>a[c])
        {
            j--;
        }
        else
        {
            int temp_1=a[j];
            a[j]=a[i];
            a[i]=temp_1;

            visualise(i, j);
            SDL_Delay(delay);

            i++;
            j--;
        }
    }
    return c;
}

//Algorithm for Heap sort
void inplaceHeapSort(int* input, int n)
{
    for(int i=1; i<n; i++)
    {
       int childIndex=i;
       int parentIndex=(childIndex-1)/2;

       while(childIndex>0)
       {
           if(input[childIndex]>input[parentIndex])
           {
               int temp=input[parentIndex];
               input[parentIndex]=input[childIndex];
               input[childIndex]=temp;

           }
           else
           {
               break;
           }

           visualise(parentIndex, childIndex);
           SDL_Delay(delay);

           childIndex=parentIndex;
           parentIndex=(childIndex-1)/2;
       }
    }

    for(int heapLast=n-1; heapLast>=0 ; heapLast--)
    {
        int temp=input[0];
        input[0]=input[heapLast];
        input[heapLast]=temp;

        int parentIndex=0;
        int leftChildIndex=2*parentIndex + 1;
        int rightChildIndex=2*parentIndex + 2;

        while(leftChildIndex<heapLast)
        {
            int maxIndex=parentIndex;

            if(input[leftChildIndex]>input[maxIndex])
            {
                maxIndex=leftChildIndex;
            }
            if(rightChildIndex<heapLast && input[rightChildIndex]>input[maxIndex])
            {
                maxIndex=rightChildIndex;
            }
            if(maxIndex==parentIndex)
            {
                break;
            }

            int temp=input[parentIndex];
            input[parentIndex]=input[maxIndex];
            input[maxIndex]=temp;

            visualise(maxIndex, parentIndex, heapLast);
            SDL_Delay(40);

            parentIndex=maxIndex;
            leftChildIndex=2*parentIndex + 1;
            rightChildIndex=2*parentIndex + 2;
        }
    }
}

int main(int argc, char* args[]){
    
    //initialise everyting on SDL
    if(SDL_Init(SDL_INIT_EVERYTHING != 0)){
        cout << "SDL failed to initialise! " << SDL_GetError() << endl;
        return 1;
    }
    
    //Creating a window
    window = SDL_CreateWindow("SORTING VISUALISER", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                          WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        cout << "SDL failed to create window!" << SDL_GetError() << endl;
        return 1;
    }
    
    //Creating a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        cout << "SDL failed to cerate renderer!" << SDL_GetError() << endl;
        return 1;
    }
    
    cout << "SDL initialised properly." << endl;
    
    //Randamising and saving the array
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);
    for(int i = 0; i < arr_size; i++){
        int random = rand() % (WINDOW_HEIGHT);
        Barray[i] = random;
    }
    
    //load array
    //Here we are copying the array data
    memcpy(Array, Barray, sizeof(int) * arr_size);
    
    //choosing algorithm
    bool loop = true;
        cout << "\nList of Algorithms to pick from:" << endl;
        cout << "1. Bubble sort\n";
        cout << "2. Selection sort\n";
        cout << "3. Insertion sort\n";
        cout << "4. Merge sort\n";
        cout << "5. Quick sort\n";
        cout << "6. Heap sort\n";
        cout << "Press 0 to quit the program." << endl;
        
        cout << "\nEnter animation speed:\n";
        cout << "1. Slow \n2. Medium \n3. Fast\n";
        int speed;
        cin >> speed;
        cout << endl;
        switch(speed){
            case 1:
                delay = 100;
                break;
            case 2:
                delay = 50;
                break;
            case 3:
                delay = 1;
        }
        
    do{
        //Specifying events to end the window
        SDL_Event event;
        bool running = true;
        while(running){
            while(SDL_PollEvent(&event) != 0){
                
                if(event.type == SDL_QUIT){
                    running = false;
                    complete = false;
                    break;
                }
                else if(event.type == SDL_KEYDOWN){
                    switch(event.key.keysym.sym){
                        case SDLK_q:
                        {
                            running = false;
                            break;
                        }
                        case SDLK_1:
                        {
                            memcpy(Array, Barray, sizeof(int) * arr_size);
                            complete = false;
                            auto start = high_resolution_clock::now();
                            bubble_sort();
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                            cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << endl;
                            complete = true;
                            break;
                        }
                        case SDLK_2:
                         
                        {
                            memcpy(Array, Barray, sizeof(int) * arr_size);
                            complete = false;
                            auto start = high_resolution_clock::now();
                            selection_sort();
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                            cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << endl;
                            complete = true;
                            break;
                        }
                        case SDLK_3:
                         
                        {
                            memcpy(Array, Barray, sizeof(int) * arr_size);
                            complete = false;
                            auto start = high_resolution_clock::now();
                            insertion_sort();
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                            cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << endl;
                            complete = true;
                            break;
                        }
                        case SDLK_4:
                        {
                            memcpy(Array, Barray, sizeof(int) * arr_size);
                            complete = false;
                            auto start = high_resolution_clock::now();
                            mergeSort(Array, 0, arr_size-1);
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                          
                            cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << endl;
                            complete = true;
                            break;
                        }
                        case SDLK_5:
                        {

                            memcpy(Array, Barray, sizeof(int) * arr_size);
                            complete = false;
                            auto start = high_resolution_clock::now();
                            quick_sort(Array, 0, arr_size-1);
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                            cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << endl;
                            complete = true;
                            break;
                        }
                        case SDLK_6:
                        {

                            memcpy(Array, Barray, sizeof(int) * arr_size);
                            complete = false;
                            auto start = high_resolution_clock::now();
                            inplaceHeapSort(Array, arr_size);
                            auto stop = high_resolution_clock::now();
                            auto duration = duration_cast<microseconds>(stop - start);
                            cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << endl;
                            complete = true;
                            break;
                        }
                        
                        default:
                            cout << "Choose a correct option." << endl;
                    }
                }
            visualise();
            }
        }
        SDL_DestroyRenderer(renderer);
        renderer=NULL;

        SDL_DestroyWindow(window);
        window=NULL;

        SDL_Quit();
    }while(loop);
    
    return 0;
}
