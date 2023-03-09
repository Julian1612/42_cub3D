# Waste Wizard

Waste Wizard is a simple garbage collector that can be used by C programs.


## Explanation

The garbage collector works by providing a wrapper function for malloc, 
which besides allocating memory will also add a pointer to the allocation 
to a static waste list which can then be freed later on in the program.


## Usage

```C
include "waste_wizard.h"

/*
Adds an already allocated object to the waste list.
The second parameter is a pointer to a function that will be used to free 
the allocation later on. If the second parameter is NULL, free() is used.
*/
ww_add_waste(allocation, &free_function);

/*
This is a wrapper for malloc, which will allocate memory of the size specified 
in the parameters and also add the allocation to the static waste list.

Beware: Replacing every malloc in your code with this wrapper can lead to
significant performance slumps because the list of pointers that is managed
by the wizard can become very big. It is recommended to allocate big data
structures like structs, lists or arrays with the normal malloc and to use
ww_add_waste to add the head pointer to the wizard.
*/
ww_malloc_and_add(size, count);

/*
Calling this function will free every allocation in the waste list
by using the provided free function.
*/
ww_free_all_waste();
```
