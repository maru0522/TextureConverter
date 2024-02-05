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

    // コマンドライン引数指定なし
    if (argc < NumArgument)
    {
        TextureConverter::OutputUsage();
        return 0;
    }

    // COMライブラリの初期化
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr));

    int numOptions = argc - NumArgument;
    char** options = argv + NumArgument;

    // コンバーターの宣言と変換
    TextureConverter converter;
    //std::filesystem::path path = static_cast<std::filesystem::path>(argv[(size_t)Argument::kFilePath]);
    std::filesystem::path path = argv[kFilePath];
    converter.ConvertTextureWICToDDS(path,numOptions,options);


    // COMライブラリの終了
    CoUninitialize();

    //// argcの数だけ繰り返す
    //for (int i = 0; i < argc; i++)
    //{
    //    // 文字列arvのi番を表示
    //    printf(argv[i]);
    //    // 改行
    //    printf("\n");
    //}

    //system("pause");
    return 0;
}