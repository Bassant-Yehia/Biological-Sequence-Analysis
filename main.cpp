// C++ program for building suffix array of a given text
#include <iostream>
#include <cstring>
#include<cstdio>
#include<cstdlib>
//#include <chrono>
#include <algorithm>
using namespace std;
#define DIR "D:\\studying\\3rd year-2nd semester\\Bio seq analysis\\Assignments\\"


void Menu()
{
    cout<<"\t\t\t\t\t ||||*******************************|||| \n";
    cout<<"\t\t\t\t\t ||||          Suffix Array         |||| \n";
    cout<<"\t\t\t\t\t ||||*******************************|||| \n";
    cout<<"\n==========""Menu""==========\n";
    cout<<"1.Naive\n"<<"2.Prefix for 10,000\n"<<"3.Prefix for whole genome\n"<<"4.Some test cases\n"<<"5.Exit";
    cout<<"\n=========================================================================\n";
}


struct suffArrayStruct
{
    // Struct for 1st function (Naive) contains data of the suffix array after read it from file
    char *Leters; //variable to point to leters in the array
    int order; //integer variable contains the indexes of the array that help me in ordering the suffix
};

int x; //variable for storing the result of strcmp function (that compare two letters )

/*bool intial_comparason(struct suffArrayStruct  s1, struct suffArrayStruct  s2)
{  //to creating the initial order of suffix to get  for example : "ant" :-> 0,1,2 t this usual order after calling this func in sort func
	if (strcmp(s1.Leters, s2.Leters) !=0)
	 return true; //so the two leters not equal after that sort func will be applied and the array will be sorted
    else
        return false; //so the two leters are equal after that sort func willnot be applied
*/
// A comparison function used by sort() to compare two suffixes
bool final_comparason(struct suffArrayStruct  s1, struct suffArrayStruct  s2)
{
    //to creating the order of suffix to get sorted for suffix array  after calling this func in sort func
    x=strcmp(s1.Leters, s2.Leters); //string the return of strcmp func in x variable
    if(x < 0) // comparing leter1 with leter2
        return true; //means  ther are not equal
    else
        return false; //they are equal
}


int *CreateSuffix_Naive(char *Input, int Size)
{
    //func that take the string through char of array and the size to creat suffix then get suff arrY
    struct suffArrayStruct  suffixes[Size]; //saving suffix in arr of struct type
// and maintain their old indexes while sorting
    int current=0; //for storing each iteration
    while ( current < Size)
    {
        suffixes[current].order= current;
        suffixes[current].Leters = (Input+current); //shifting
        x++;
    }
    cout<<endl<<endl<<"current = "<<x<<endl;


    //sort(suffixes, suffixes+n, intial_comparason);
    sort(suffixes, suffixes+Size, final_comparason); // Sort the suffixes using the comparison function(that return true or false)
    // Store indexes of all sorted suffixes in the suffix array
    int *suffixArray_naive = new int[Size];
    int i = 0;
    while( i < Size )
    {
        suffixArray_naive[i] = suffixes[i].order;
        i++;
    }
    cout<<endl<<endl<<"i ="<<i<<endl; //print for checking

    // Return the suffix array
    return suffixArray_naive;

    delete []suffixArray_naive; //for deleting dynamic array
}

char *CreateSuffix_char(char *Input, int Size)
{
    //func that take the string through char of array and the size to creat suffix then get suff arrY
    struct suffArrayStruct  suffixes[Size]; //saving suffix in arr of struct type
// and maintain their old indexes while sorting
    int x=0;
    while ( x < Size)
    {
        suffixes[x].order= x; //x describe current index
        suffixes[x].Leters = (Input+x); // for shifting the given char by x and save the old indexes
        x++;
    }
    cout<<endl<<endl<<"x ="<<x<<endl;


    //sort(suffixes, suffixes+n, intial_comparason);
    sort(suffixes, suffixes+Size, final_comparason); // Sort the suffixes using the comparison function


    // Store indexes of all sorted suffixes in the suffix array
    /* char *suffixArr_char [Size];
       int i = 0;
       while( i < Size )
       {
           suffixArr_char[i] = suffixes[i].Leters;
           i++;
       }

       // Return the suffix array
       return *suffixArr_char;*/

}
void Read()
{

    int Count=0;
    char Buffer[20000]; //size more than the required size to handle an error
    FILE* Read_file=fopen(DIR "genome.fasta", "r"); //Read from existed file that found in the given DIR at the begining of the code
    int r=0;
    while(r<10000)
// Print the first 10,000 reads
    {

        if(r==0)

        {
            Buffer[0]=0;
            fscanf(Read_file, "%[^\n\r] ",Buffer);// to skip 1st line
        }

        fscanf(Read_file, "%c ",&Buffer[r]); //read chars
        r+=1;

    }
    cout<<endl<<endl<<"   count of genes is : "<<r<<endl; //to count the genes
    cout<<endl<<"           *The 1st 10,000 chars by naive is*     "<<endl<<"           ---------------------------------      "<<endl<<Buffer<<endl;
    //to print char of array that contain 10000 chars

    cout<<endl<<endl<<endl<<endl;
    fclose(Read_file);
}

// for printing array
void Output_ordring(int ARRAY[], int Size)
{
    int i = 0;
    while (i < Size)
        cout << ARRAY[i] << " ";
    cout << endl;
    i++;
}


int* GetSuffix_Naive()
{

    Read(); //read file and calculte num of genes that it read
    char Buffer[10000];
    int *Suffix_Array_Naive = CreateSuffix_Naive(Buffer,10000); //fun return integer of array and the size to creat suffix then get suff arrY
    //then return numbers of suffix in Suffix_Array
    Output_ordring(Suffix_Array_Naive, 10000); //for printing suffix_array[i]



    delete[] Buffer;//delete dynamic array
    return Suffix_Array_Naive;
}


struct suffix //struct for suffix array to be able to access indexes and order through it
{
    int index; // to save index
    int order[2]; // to save orders for pairs
};




bool Compare(suffix s1, suffix s2) //for return true or false in comparig to use the return in sorting
{
    if(s1.order[0] == s2.order[0])
    {
        if(s1.order[1] < s2.order[1]) // if first pair is smaller than the second return true
            return true;
        else
            return false;
    }
    else if (s1.order[0] < s2.order[0])
        return true ;
    else
        return false;
}


int *CreateSuffix(char *Read, int Size) //takes rhe read (char of array ) and the size of it
{
    struct suffix suffixes[Size];//struct for storing suffixes and their indexes


    int i = 0;
    while (i < Size)
    { //sort the array by the order of the alphbet characters and save their old indexes
        suffixes[i].index = i;
        suffixes[i].order[0] = Read[i] - 97;
        if ((i+1) < Size)
            suffixes[i].order[1] =(Read[i + 1] - 97);
        else
            suffixes[i].order[1] = -1;
        i++;
    }

    // Sort the suffixes using the comparison function
    sort(suffixes, suffixes+Size, Compare);
    int index[Size]; // This array is required for crating the index in suffixes[]
    // from old index The map is required to crate next suffix.
    for (int Map = 4; Map < 2*Size; Map = Map*2)
    {
        // Assigning Order and index to 1st suffix
        int order = 0;
        int old_order = suffixes[0].order[0];
        suffixes[0].order[0] =order;
        index[suffixes[0].index] = 0;

        int i = 1;
        while( i < Size)
        {
            // If first rank and next ranks are same as that of previous
            // suffix in array, assign the same new rank to this suffix
            if (suffixes[i].order[0] == old_order &&suffixes[i].order[1] == suffixes[i-1].order[1])
            {
                old_order= suffixes[i].order[0];
                suffixes[i].order[0] = order;
            }
            else //increase Order
            {
                old_order = suffixes[i].order[0];
                suffixes[i].order[0] = ++order;
            }
            index[suffixes[i].index] = i;
            i++;
        }
        int l = 0;
        while ( l < Size) //storing the next order to each suffix
        {
            int next_index = suffixes[l].index + Map/2;
            if (next_index < Size)
                suffixes[l].order[1] =suffixes[index[next_index]].order[0];
            else
                suffixes[l].order[1] = -1;
                l++;
        }

        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes+Size, Compare);
    }

    // Store indexes of all sorted suffixes in the suffix array
    int *suffixArr = new int[Size];
    for (int i = 0; i < Size; i++)
        suffixArr[i] = suffixes[i].index;

    // Return the suffix array
    return suffixArr;
}




void Read2()
{

    int Count=0;
    char Buffer2[200000];
    FILE* Read_file=fopen(DIR "genome.fasta", "r");
    int i=0;
    while(i<100000)
// Print the first 10000 reads
    {

        if(i==0)

        {
            Buffer2[0]=0;
            fscanf(Read_file, "%[^\n\r] ",Buffer2);// Ignore this line
        }

        fscanf(Read_file, "%c ",&Buffer2[i]); //read chars
        i+=1;
        Count+=1;
        // Ignore this line

    }

    cout<<endl<<"           *The 1st 100,000 genes (chars) by prefix doubling is*     "<<endl<<"           ---------------------------------      "<<endl<<Buffer2<<endl;
    //to print char of array that contain 10000 chars

    cout<<endl<<"   count of genes is : "<<Count<<endl<<endl<<endl;
    fclose(Read_file);
}

int* GetSuffix()
{

    Read(); //read file and calculte num of genes that it read
    char Buffer[10000];
    int *Suffix_Array = CreateSuffix(Buffer,10000); //fun return integer of array and the size to creat suffix then get suff arrY
    //then return numbers of suffix in Suffix_Array
    Output_ordring(Suffix_Array, 10000); //for printing suffix_array[i]


    delete[] Buffer;//delete dynamic array
    return Suffix_Array;
}

int* GetSuffix2()
{

    Read2(); //read file and calculte num of genes that it read
    char Buffer2[200000];
    int *Suffix_Array2 = CreateSuffix(Buffer2,100000); //fun return integer of array and the size to creat suffix then get suff arrY
    //then return numbers of suffix in Suffix_Array
    Output_ordring(Suffix_Array2, 100000); //for printing suffix_array[i]


    delete[] Buffer2;//delete dynamic array
    return Suffix_Array2;
}

void chose1()
{
    //Suffix of first 10,000 char by using Naive then create 1st_task file in the DIR and print the suffix in it
    // Read();
//GetSuffix_Naive(); // execution time : 2.57 s

    cout<<"_____________________________"<<endl;
    cout<<"Creating files start"<<endl;
    cout<<"_____________________________"<<endl;
    FILE * file_to_read = fopen("genome.txt", "r");
    if(file_to_read == NULL)
    {
        cout<<endl<<"Nothing to read"<<endl;
        //  return 0;
    }
    //int point;
    FILE *file_to_write = fopen("1st_file.txt", "w");
    if(file_to_write == NULL)
    {
        cout<<endl<<"Nothing to write"<<endl;
        //return 0;
    }

    int*x=  GetSuffix_Naive(); //return suffix
    for(int i=0; i<10000; i++)
    {
        fprintf(file_to_write,"%d",x[i]); //write 10,000 digits in file call  "First task"
        fprintf(file_to_write,"\n");//to write each digit (gene) in separeted line

    }
    fclose(file_to_write);
    fclose(file_to_read);

}
void chose2()
{
    //Suffix of first 10,000 char by using prefix then create 2nd_task file in the DIR and print the suffix in it
    //Read();
    // GetSuffix(); // execution time : 1.9 s
    cout<<"_____________________________"<<endl;
    cout<<"Creating files start"<<endl;
    cout<<"_____________________________"<<endl;
    FILE * file_to_read = fopen("genome.txt", "r");
    if(file_to_read == NULL)
    {
        cout<<endl<<"Nothing to read"<<endl;
        // return 0;
    }
    //int point;
    FILE *file_to_write = fopen("2nd_task.txt", "w");
    if(file_to_write == NULL)
    {
        cout<<endl<<"Nothing to write"<<endl;
        // return 0;
    }

    int*y= GetSuffix(); //return suffix
    for(int i=0; i<10000; i++)
    {
        fprintf(file_to_write,"%d",y[i]); //write 10,000 digits in file call  "First task"
        fprintf(file_to_write,"\n");//to write each digit (gene) in separeted line

    }
    fclose(file_to_write);
    fclose(file_to_read);

}
void chose3()
{
    //Suffix of first 100,000 char by using prefix then create 3rd_task file in the DIR and print the suffix in it
    //Read2();
    // GetSuffix2(); //   execution time : 23.79 s for 1000000 chars
    cout<<"_____________________________"<<endl;

    cout<<"Creating files start"<<endl;
    cout<<"_____________________________"<<endl;
    FILE * file_to_read = fopen("genome.txt", "r");
    if(file_to_read == NULL)
    {
        cout<<endl<<"Nothing to read"<<endl;
        //return 0;
    }
    //int point;
    FILE *file_to_write = fopen("3rd_task.txt", "w");
    if(file_to_write == NULL)
    {
        cout<<endl<<"Nothing to write"<<endl;
        // return 0;
    }

    int*z=  GetSuffix2(); //return suffix
    for(int i=0; i<100000; i++)
    {
        fprintf(file_to_write,"%d",z[i]); //write 10,000 digits in file call  "First task"
        fprintf(file_to_write,"\n");//to write each digit (gene) in separeted line

    }
    fclose(file_to_write);
    fclose(file_to_read);

}

void Test_cases()
{
    char x[] = "basantyahya";
    int n1 = sizeof(x)-1;
    int *suffix_Array1 =CreateSuffix_Naive(x,n1);
    cout << "The result of 1st test suffix func is " << x << endl;
    Output_ordring(suffix_Array1, n1);


    char y[] = "abcdefghijklmn";
    int n2 = sizeof(y)-1;
    int *suffix_Array2 =CreateSuffix_Naive(y,n2);
    cout << "The result of 2nd test suffix func is " << y << endl;
    Output_ordring(suffix_Array2, n2);


    char z[] = "bananabanana";
    int n3 = sizeof(z)-1;
    int *suffix_Array3 =CreateSuffix_Naive(z,n3);
    cout << "The result of 3rd test suffix func is " << z << endl;
    Output_ordring(suffix_Array3, n3);

    char a[] = "announcement";
    int n4 = sizeof(a)-1;
    int *suffix_Array4 =CreateSuffix_Naive(a,n4);
    cout << "The result of 4rd test suffix func is " << a << endl;
    Output_ordring(suffix_Array4, n4);

    char b[] = "ABCDEFGHIJKLMNO";
    int n5 = sizeof(b)-1;
    int *suffix_Array5 =CreateSuffix_Naive(b,n5);
    cout << "The result of 4rd test suffix func is " << b << endl;
    Output_ordring(suffix_Array5, n5);
}

// Driver program to test above functions
int main()
{





    // Read();
    int chose,again;
    do
    {
        Menu();
        cout<<"\nEnter your choice :\t";
        cin>>chose;
        cout<<endl;
        switch(chose)
        {
        case 1:
            chose1();
            break;
        case 2 :
            chose2();
            break;
        case 3 :
            chose3();
            break;

        case 4:
            Test_cases();
            break;

        case 5:
            EXIT_SUCCESS;
            break;

        default:
            cout<<"wrong choice\n";
        }
        cout<<"\n----------------------\n";
        cout<<"1.Continue\n";
        cout<<"2.Exit\n";
        cout<<"\n----------------------\n";
        cout<<"\nEnter your choice :\t";
        cin>>again;
        cout<<"\n-------------------------------------------\n\n";
        if(again==2)
            EXIT_SUCCESS;
    }
    while (again==1);



// cout<<endl<<"finished"<<endl;

    /*char txt[] = "basant";
    int n =sizeof(txt)-1;

    int *suffixArr = CreateSuffix(txt, n);
    cout << "Following is suffix array for " << txt << endl;
    Output_ordring(suffixArr, n);*/
    return 0;
}
