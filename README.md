
<p align="center">
 <h2 align="center">LargeIntV2</h2>
 <p align="center"></p>
</p>

<p align="center">
 
 <a href="https://en.wikipedia.org/wiki/C%2B%2B">
      <img src="https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=for-the-badge&logo=appveyor"/>
    </a>
    <a href="https://en.wikipedia.org/wiki/Microsoft_Windows">
      <img src="https://img.shields.io/badge/platform-Windows-0078d7.svg?style=for-the-badge&logo=appveyor"/>
    </a>
 
 <a href="https://en.wikipedia.org/wiki/something">
      <img src="https://img.shields.io/badge/arch-x86-red.svg?style=for-the-badge&logo=appveyor"/>
    </a>
 
 <a href="https://en.wikipedia.org/wiki/something">
      <img src="https://img.shields.io/badge/License-MIT-e49eff?style=for-the-badge&logo=appveyor"/>
    </a>
 
 
    
  </p>

## Information

The general method of function is defined through arrays. Each pointer, by default, contains a integer which defines the length of the allocated array within. A positive integer indicates a positive large integer. Likewise, a negative integer indicates a negative large integer. Each allocated byte is split into two sections, "left" and "right". Each byte can hold two places/unit (e.g. 24 is 2 places, 19520 is 5 places); one bit is wasted due to padding because 2^4-1=15, 2^3-1=7 (too small), 2^5-1=31 (too large). The **following** diagram describes the prior explanation:

![Reference](https://raw.githubusercontent.com/vernthedragon/LargeIntV2/refs/heads/main/bits.png)

## Documentation

```C++
//All integers are stored in void*
void* IntCreate(int lengthofarray) //returns an integer
void IntFree(void* integer) //frees/deletes an integer
int IntGetSize(void* integer) //returns the length of the array within an integer
void* IntResize(void* integer, int newsize) //resizes an integer to a new array length
void IntSetSize(void* integer, int newsize) //sets the internal length of the array within an integer, however does not resize the array
void IntSetPlace(void** integer /*reference to the integer*/, int place, unsigned char value) //sets a certain place to a value
//Example of Set Place
IntSetPlace(&integer, 1, 4) //If the previous value of the integer was 196. It will now be 194
IntSetPlace(&integer, 3, 4) //If the previous value of the integer was 196. It will now be 396
unsigned char IntGetPlace(void* integer, int place) //returns the value of a place/unit
bool IntEqual(void* A, void* B) //checks if two integers A and B are equal
bool IntNotEqual(void* A, void* B) //checks if two integers A and B are not equal
void* IntAdd(void* A, void* B) //adds two integers A and B, and stores the result in a newly allocated integer through a void* return
```
## Errors / To Do
*   **IntAdd** - Currently only supports adding positive and positive, or negative and negative integers
*   **IntSubtract** - Implement basic arithmatic
*   **IntMultiply** - Implement basic arithmatic
*   **IntDivide** - Implement basic arithmatic
