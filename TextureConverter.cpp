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
    DirectX::ScratchImage mipchain;
    // ミップマップ生成する
    HRESULT hr = DirectX::GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipchain);
    // ミップ生成成功したら
    if (SUCCEEDED(hr))
    {
        // イメージとメタデータを、ミップマップ版で置き換える。
        scratchImage_ = std::move(mipchain);
        metadata_ = scratchImage_.GetMetadata();
    }

    // 圧縮形式に変換する
    DirectX::ScratchImage converted;
    // フォーマットはBC7 ※制約として、縦幅と横幅が4の倍数である必要がある。
    hr = DirectX::Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DXGI_FORMAT_BC7_UNORM_SRGB, DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL, 1.f, converted);
    // ミップ生成成功したら
    if (SUCCEEDED(hr))
    {
        // イメージとメタデータを、ミップマップ版で置き換える。
        scratchImage_ = std::move(converted);
        metadata_ = scratchImage_.GetMetadata();
    }

    // 読み込んだテクスチャをSRGBとして扱う
    metadata_.format = DirectX::MakeSRGB(metadata_.format);
    // 出力ファイル名の設定
    std::wstring wFilePath = path_.replace_extension(".dds").wstring();
    hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, wFilePath.c_str());
    assert(SUCCEEDED(hr));
}
