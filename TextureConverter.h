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
    void LoadWICTextureFromFile(const std::filesystem::path& filePath);
    void SaveDDSTextureToFile(void);

    // �ϐ�
    DirectX::TexMetadata metadata_;
    DirectX::ScratchImage scratchImage_;

    std::filesystem::path path_;
};

