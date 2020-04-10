#include <stdio.h>
#include <iostream>

using namespace std;
void show(unsigned char a[10])
{
        for (int i=0;i<10;++i)
        {
                printf("%d ",int(a[i]));
        }
        printf("\n");
}

void genmass(unsigned char a[10])
{
        srand(time(0));
        for (int i=0;i<10;++i)
        {
          a[i] = (unsigned char) (1 + rand() % 10) ;
        }
	show(a);
}

void    sdvig(unsigned char *in, unsigned char *out)
{

 __asm__
        (
	"addl $1, %%eax\n\t"
	"movl (%%eax), %%edx\n\t"
	"movb %%dl, (%%ebx)\n\t"
	"movl $8, %%ecx\n\t"

	"prohod:\n\t"
	"addl $1, %%eax\n\t"
	"addl $1, %%ebx\n\t"
	"movl (%%eax), %%edx\n\t"
	"movb %%dl, (%%ebx)\n\t"
	"decl %%ecx\n\t"
	"cmpl $1, %%ecx\n\t"
	"jge prohod\n\t"

	"vozv:"
        "decl %%eax\n\t"
	"inc %%ecx\n\t"
	"cmpl $9, %%ecx\n\t"
	"jl vozv\n\t"

        "addl $1, %%ebx\n\t"
        "movl (%%eax), %%edx\n\t"
        "movb %%dl, (%%ebx)\n\t"
         :
         : "a"(in), "b"(out)
         :"cc", "memory"
        );

}

int main()
{
        unsigned char mass[10];
        unsigned char mass2[10];
        int shift;
        printf("Ishodnii massiv: \n");
        genmass(mass);
        printf("Vvedite velichinu sdviga: \n");
        scanf("%d",&shift);
        printf("Sdvinutii massiv: \n");
        while (shift>0)
        {
                sdvig(&mass[0], &mass2[0]);
                for (int i = 0; i<10; ++i)
                        mass[i] = mass2[i];
                --shift;
        }
        show(mass2);
        return 0;
}
