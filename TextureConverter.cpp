#include "TextureConverter.h"

#include <stringapiset.h>

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& filePath)
{
    path_ = filePath;

    LoadWICTextureFromFile(filePath);
    SaveDDSTextureToFile();
}

void TextureConverter::LoadWICTextureFromFile(const std::filesystem::path& filePath)
{
    // szFile
    std::wstring wFilePath = path_.wstring();

    // loading wicTecture
    HRESULT hr = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
    assert(SUCCEEDED(hr));
}

void TextureConverter::SaveDDSTextureToFile(void)
{
    metadata_.format = DirectX::MakeSRGB(metadata_.format);

    // 出力ファイル名の設定
    std::wstring wFilePath = path_.replace_extension(".dds").wstring();
    HRESULT hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, wFilePath.c_str());
    assert(SUCCEEDED(hr));
}
