#include <unistd.h>

int main(void)
{
        int i;
        for(i=0; i<10; i++)
        {
                system("/usr/bin/level5 &");
        }
}
