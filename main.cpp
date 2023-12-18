#include "TextureConverter.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>

enum class Argument
{
    kApplicationPath,
    kFilePath,

    NumArgument,
};

int main(int argc, char* argv[]) {

    assert(argc >= (int)Argument::kApplicationPath);

    // COM���C�u�����̏�����
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr));

    // �R���o�[�^�[�̐錾�ƕϊ�
    TextureConverter converter;
    converter.ConvertTextureWICToDDS(argv[(size_t)Argument::kFilePath]);


    // COM���C�u�����̏I��
    CoUninitialize();

    //// argc�̐������J��Ԃ�
    //for (int i = 0; i < argc; i++)
    //{
    //    // ������arv��i�Ԃ�\��
    //    printf(argv[i]);
    //    // ���s
    //    printf("\n");
    //}

    system("pause");
    return 0;
}