#include "stdio.h"
#include "stdlib.h"

int main(int argc, char* argv[]) {

    // argc�̐������J��Ԃ�
    for (int i = 0; i < argc; i++)
    {
        // ������arv��i�Ԃ�\��
        printf(argv[i]);
        // ���s
        printf("\n");
    }
    
    system("pause");
    return 0;
}