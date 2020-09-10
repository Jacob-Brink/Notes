
//create array
int array[40];

//main function
int main()
{
	
	
    //initaliaze first two elements
    array[0] = 0;
    array[1] = 1;
    
	int i;
	
    //loop through rest of elements
    for (i = 2; i < 40; i++) {
        //set current array element to sum of last two elements
        array[i] = array[i-1] + array[i-2];
    }
    
    //terminate program
    return 0;
}
