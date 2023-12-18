#pragma once
#include <string>
#include <filesystem>
#include <DirectXTex.h>

class TextureConverter
{
public:
    // �֐�
    void ConvertTextureWICToDDS(const std::filesystem::path& filePath);

private:
    static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);
    void LoadWICTextureFromFile(const std::filesystem::path& filePath);
    void SaveDDSTextureToFile(void);

    // �ϐ�
    DirectX::TexMetadata metadata_;
    DirectX::ScratchImage scratchImage_;

    std::filesystem::path path_;
};

