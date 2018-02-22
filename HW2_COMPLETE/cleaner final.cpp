//LOGAN M CAMPBELL    COURSE: PF2    ID: 010 641 227
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <fstream>
using namespace std;

// CAN I USE THE INDEXSIZE?
// DO I HAVE TO CREATE A SEPARTE MEDIAN FUNCTION FOR EACH MEDIAN METHOD?
// IS THERE A WAY TO COUT A STATEMENT FOR IF SORTED FUNCTION?
// IS THE CHOICE SCHEME TOO MUCH?




//S I Z E   
const int  SIZE = 10;
const  int INDEXSIZE = SIZE - 1;

//P R I N T     L O A D
template <typename T>
void loadInfo(const string& filename, T data[])
{
    ifstream loadInfo;
    // OPEN FILE AND CHECK IT'S EXISTIENCE
    loadInfo.open(filename.c_str());
    if (loadInfo.fail())
    {
        cout << "I N V A L I D\t F I L E " << endl;
        exit(1);
    }
    //LOAD ARRAY

    for (int x = 0; x < SIZE; x++)
    {
        getline(loadInfo, data[x]);
    }

    loadInfo.close();

}
template <typename T>
void printInfo(const T data [SIZE])
{
    // TODO: Implement
    for (int x = 0; x < SIZE; x++)
    {
        cout << data[x] << endl;
    }
        cout << endl;
}


// M E N U          F U N C T I O N
void menu()
{
    cout << "\t    S O R T I N G \t  D A T A" << endl;
    cout <<"\t======================================\n" << endl;
    cout << "   SELECT A SORTING ALGORITHM TO PEFORM ON YOUR FILE \n" << endl;
    
    cout << "   1. B A S E L I N E\n";
    cout << "   2. T H R E E - W A Y\n";
    cout << "   3. H Y B R I D \n" ;
    cout << "   4. M E D I A N \n";
    cout << "   5. 3 W A Y + M E D I A N \n";
    cout << "   6. 3 W A Y + H Y B R I D \n";
    cout << "   7. H Y B R I D + M E D I A N \n";
    cout << "   8. 3 W A Y + M E D I A N + H Y B R I D\n";
}



// S O R T E D      C H E C K E R
template <class T>
bool isSorted(T data[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        if (data[i] > data[i + 1])
            return true;
    }
    return false;
    
}




//          D E F A U L T
template <typename T>
void partitionD(T data[], int low, int high, int &mid)
{
    // Select pivot value
    T pivot = data[high];
    int left = low;
    int right = high;
    
    // Partition array into two parts
    while (left < right)
    {
        // Scan left to right
        while ((left < right) && (data[left] < pivot))
        left++;
        // Scan right to left
        while ((left < right) && (data[right] >= pivot))
        right--;
        // Swap data values
        swap(data[left], data[right]);
    }
    
    // Swap pivot to mid
    mid = left;
    data[high] = data[mid];
    data[mid] = pivot;
}
template <typename T>
void quicksortD(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
    // Partition data into two parts
    int mid = 0;
    partitionD(data, low, high, mid);
    // Recursive calls to sort array
    quicksortD(data, low, mid - 1);
    quicksortD(data, mid + 1, high);
    }
}



//          M E D I A N
template <typename T>
T median (T first , T second, T third)
{
    if (first <= second && second <= third)
    
        return second;
    
    
    else if(third <= first && first <= third)
    
        return first;
    
    else  //(first <= third && third <= second)
    
        return third;
    
}
template <typename T>
void partitionM(T data[], int low, int high, int &mid)
{
    // Select pivot value
    int center = (low + high) / 2;
    T pivot    = median(data[low], data[center], data[high]);
    if (pivot == data[low])
        swap(data[low], data[high]);
    else if (pivot == data[center])
        swap(data[center], data[high]);
    
    
    
    int left = low;
    int right = high;

    // Partition array into two parts
    while (left < right)
    {
        // Scan left to right
        while ((left < right) && (data[left] < pivot))
            left++;

        // Scan right to left
        while ((left < right) && (data[right] >= pivot))
            right--;

        // Swap data values
        swap(data[left], data[right]);
    }

    // Swap pivot to mid
    mid = left;
    data[high] = data[mid];
    data[mid] = pivot;
}
template <typename T>
void quicksortM(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        // Partition data into two parts
        int mid = 0;
        partitionM(data, low, high, mid);

        // Recursive calls to sort array
        quicksortM(data, low, mid - 1);
        quicksortM(data, mid + 1, high);
    }
}



//          3 W A Y
template <typename T>
void partition3(T data[], int low, int high, int &left, int &right )
{
    // Select pivot value
    T pivot = data[high];
    left  = low;
    right = high;
    int unsorted = low;
    
   while (unsorted <= right)
    {
        if (data[unsorted] > pivot)
        {
            swap (data[unsorted], data[right]);
             right--; 
        }
        else if (data[unsorted] < pivot)
        {
            swap(data[left], data[unsorted]);
            left++; unsorted++;
        }
       else
                    //(data[unsorted] == pivot)
            unsorted++;

    }
}
template <typename T>
void quicksort3(T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        int left; int right;
        
        partition3(data, low, high,left,right);

        // Recursive calls to sort array
        quicksort3(data, low, left - 1);
        quicksort3(data, right + 1, high);
    }
}



//          H Y B I R D
template <typename T>
void insertionsort ( T array[], int low, int high ) // Hybrid
{
    {
        // Insert each element of unsorted list into sorted list
        for ( int unsorted = low + 1; unsorted <= high; unsorted++ )
        {
            // Select unsorted value to be inserted
            T value = array[unsorted];
            int posn = unsorted;

            // Make room for new data value
            while ( ( posn > 0 ) && ( array[posn - 1] > value ) )
            {
                array[posn] = array[posn - 1];
                posn--;
            }

            // Put new value into array
            array[posn] = value;
        }
    }
}
template <typename T>
void quicksortH ( T data[], int low, int high )
{
    // Check terminating condition
    if ( low < high )
    {
        if (high - low + 1 > 100)
        {
            // Partition data into two parts
            int mid = 0;
            partitionD( data, low, high, mid );
            // Recursive calls to sort array
            quicksortH ( data, low, mid - 1 );
            quicksortH ( data, mid + 1, high );
        }
        else
        {
            insertionsort(data,low,high);
        }
    }
}



//          3 W A Y + M E D I A N
template <typename T>
void partition3M    (T data[], int low, int high, int &left, int &right )
{
    // Select pivot value
    int center = (low + high) / 2;
    T pivot = median(data[low], data[center], data[high]);
    left  = low;
    right = high;
    int unsorted = low;
    
   while (unsorted <= right)
    {
        if (data[unsorted] > pivot)
        {
            swap (data[unsorted], data[right]);
             right--; 
        }
        else if (data[unsorted] < pivot)
        {
            swap(data[left], data[unsorted]);
            left++; unsorted++;
        }
       else
                    //(data[unsorted] == pivot)
            unsorted++;

    }
}
template <typename T>
void quicksort3M    (T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        int left; int right;
        
        partition3M(data, low, high,left,right);

        // Recursive calls to sort array
        quicksort3M(data, low, left - 1);
        quicksort3M(data, right + 1, high);
    }
}



//          3 W A Y + H Y B R I D
template <typename T>
void quicksort3H    (T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        if (high - low + 1 > 100)
        {
            int left; int right;
            
            partition3(data, low, high,left,right);

            // Recursive calls to sort array
            quicksort3H(data, low, left - 1);
            quicksort3H(data, right + 1, high);
        }
        else
            insertionsort(data,low,high);
    }
}



//          M E D I A N + H Y B R I D
template <typename T>
void quicksortMH    (T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        if (high - low + 1 > 100)
        {
            int mid; 
            mid = 0;
            
            partitionM(data, low, high, mid);

            // Recursive calls to sort array
            quicksortMH(data, low, mid - 1);
            quicksortMH(data, mid + 1, high);
        }
        else
            insertionsort(data,low,high);
    }
}



//          3 W A Y + M E D I AN + H Y B R I D
template <typename T>
void partition3MH    (T data[], int low, int high, int &left, int &right )
{
    // Select pivot value
    int center = (low + high) / 2;
    T pivot = median(data[low], data[center], data[high]);
    left  = low;
    right = high;
    int unsorted = low;
    
   while (unsorted <= right)
    {
        if (data[unsorted] > pivot)
        {
            swap (data[unsorted], data[right]);
             right--; 
        }
        else if (data[unsorted] < pivot)
        {
            swap(data[left], data[unsorted]);
            left++; unsorted++;
        }
       else
                    //(data[unsorted] == pivot)
            unsorted++;

    }
}
template <typename T>
void quicksort3MH    (T data[], int low, int high)
{
    // Check terminating condition
    if (low < high)
    {
        if (high - low + 1 > 100)
        {
            int left; int right;
            
            partition3MH(data, low, high,left,right);

            // Recursive calls to sort array
            quicksort3MH(data, low, left - 1);
            quicksort3MH(data, right + 1, high);
        }
        else
        {
            insertionsort(data,low,high);
        }
    }
}


int main()
{
    cout <<"\t  S O R T I N G\tA L G O R I T H M S" << endl;
    cout <<"\t=====================================\n" << endl;
    string information[SIZE];
    cout << "Please enter the name of file: " << endl;
    string filename;    getline(cin, filename);
    cout << endl;
    loadInfo(filename, information);
    cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
    printInfo(information);
    menu();

    int choice;
    cout << endl;
    cout << "   CHOICE : ";
    cin >> choice;
    cout << endl; cout << endl;
    while (choice < 0 || choice > 8)
    {
        cout << "I N V A L I D /t C H O I C E" << endl;
        cout <<" CHOICE : ";
        cin >> choice;
        cout << endl;
    }

    if (choice == 1)
        {
            cout << "\tBASELINE SORT  "    << endl;
            clock_t start1 = clock();
            quicksortD(information,0,INDEXSIZE);
            clock_t end1 = clock();
            double runTime1 = (end1 - start1) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime1 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
    else if (choice == 2)
        {
            cout << "\tTHREE WAY SORT "    << endl;
            clock_t start2 = clock();
            quicksort3(information,0,INDEXSIZE);
            clock_t end2 = clock();
            double runTime2 = (end2 - start2) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime2 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
    else if (choice == 3)
        {
            cout << "\tHYBRID SORT    "    << endl;
            clock_t start3 = clock();
            quicksortH(information,0,INDEXSIZE);
            clock_t end3 = clock();
            double runTime3 = (end3 - start3) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime3 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
    else if (choice == 4)
        {
            cout << "\tMEDIAN SORT    "    << endl;
            clock_t start4 = clock();
            quicksortM(information,0,INDEXSIZE);
            clock_t end4 = clock();
            double runTime4 = (end4 - start4) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime4 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
    else if (choice == 5)
        {
            cout << "\tTHREE WAY + MEDIAN SORT    "    << endl;
            clock_t start5 = clock();
            quicksort3M(information,0,INDEXSIZE);
            clock_t end5 = clock();
            double runTime5 = (end5 - start5) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime5 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
    else if (choice == 6)
        {
            cout << "\tTHREE WAY + HYBRID SORT    "    << endl;
            clock_t start6 = clock();
            quicksort3H(information,0,INDEXSIZE);
            clock_t end6 = clock();
            double runTime6 = (end6 - start6) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime6 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
    else if (choice == 7)
        {
            cout << "\tHYBRID + MEDIAN SORT    "    << endl;
            clock_t start7 = clock();
            quicksortMH(information,0,INDEXSIZE);
            clock_t end7 = clock();
            double runTime7 = (end7 - start7) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime7 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
            
        }
    else if (choice == 8)
        {
            cout << "\tTHEREE WAY + HYBRID + MEDIAN SORT    "    << endl;
            clock_t start8 = clock();
            quicksort3MH(information,0,INDEXSIZE);
            clock_t end8 = clock();
            double runTime8 = (end8 - start8) / (double) CLOCKS_PER_SEC;
            cout << "Run time: (s)" << runTime8 << endl;
            cout << " 0 = sorted | 1 = unsorted : " << isSorted(information,SIZE) << endl;
            printInfo(information);
        }
        
    else
        
    return 0;
}