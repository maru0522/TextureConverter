#pragma once
#include <string>
#include <filesystem>
#include <DirectXTex.h>

class TextureConverter
{
public:
    static void OutputUsage(void);

    // �֐�
    void ConvertTextureWICToDDS(const std::filesystem::path& filePath, int numOptions = 0, char* options[] = nullptr);

private:
    void LoadWICTextureFromFile(const std::filesystem::path& filePath);
    void SaveDDSTextureToFile(int numOptions, char* options[]);

    // �ϐ�
    DirectX::TexMetadata metadata_;
    DirectX::ScratchImage scratchImage_;

    std::filesystem::path path_;
};

