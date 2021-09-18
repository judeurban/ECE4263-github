
#define BLACK        30
#define RED          31
#define GREEN        32
#define YELLOW       33
#define BLUE         34
#define MAGENTA      35
#define CYAN         36
#define WHITE        37

#define ZIPCODE_COL  58
#define KEY_COL      70
/*

Here, \033 is the ESC character, ASCII 27. It is followed by [, then zero or 
more numbers separated by ;, and finally the letter m. The numbers describe the
colour and format to switch to from that point onwards.

         foreground background
black        30         40
red          31         41
green        32         42
yellow       33         43
blue         34         44
magenta      35         45
cyan         36         46
white        37         47

reset             0  (everything back to normal)
bold/bright       1  (often a brighter shade of the same colour)
underline         4
inverse           7  (swap foreground and background colours)
bold/bright off  21
underline off    24
inverse off      27

*/