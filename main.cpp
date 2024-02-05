#include "TextureConverter.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <filesystem>

enum Argument
{
    kApplicationPath,
    kFilePath,

    NumArgument,
};

int main(int argc, char* argv[]) {

    assert(argc >= (int)Argument::kApplicationPath);

    // �R�}���h���C�������w��Ȃ�
    if (argc < NumArgument)
    {
        TextureConverter::OutputUsage();
        return 0;
    }

    // COM���C�u�����̏�����
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr));

    int numOptions = argc - NumArgument;
    char** options = argv + NumArgument;

    // �R���o�[�^�[�̐錾�ƕϊ�
    TextureConverter converter;
    //std::filesystem::path path = static_cast<std::filesystem::path>(argv[(size_t)Argument::kFilePath]);
    std::filesystem::path path = argv[kFilePath];
    converter.ConvertTextureWICToDDS(path,numOptions,options);


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

    //system("pause");
    return 0;
}