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

    // COMライブラリの初期化
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    assert(SUCCEEDED(hr));

    // コンバーターの宣言と変換
    TextureConverter converter;
    converter.ConvertTextureWICToDDS(argv[(size_t)Argument::kFilePath]);


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

    system("pause");
    return 0;
}