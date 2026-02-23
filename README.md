
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

The general method of function is defined through arrays. Each pointer, by default, contains a integer which defines the length of the allocated array within. A positive integer indicates a positive large integer. Likewise, a negative integer indicates a negative large integer. Each allocated byte is split into two sections, "left" and "right". Each byte can hold two places/unit (e.g. 24 is 2 places, 19520 is 5 places); one bit is wasted due to padding because 2^4-1=15, 2^3-1=7 (too small), 2^5-1=31 (too large). The **following** diagramn describes the prior explanation.
