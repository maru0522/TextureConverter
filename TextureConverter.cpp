#include "TextureConverter.h"

#include <stringapiset.h>
#include <string>

void TextureConverter::OutputUsage(void)
{
    printf("�摜�t�@�C����WIC�`������DDS�`���ɕϊ����܂��B\n");
    printf("\n");
    printf("TextureConverter [�h���C�u�F][�p�X][�t�@�C����]\n");
    printf("\n");
    printf("[�h���C�u�F][�p�X][�t�@�C����]�F �ϊ�������WIC�`���̉摜�t�@�C�����w�肵�܂��B\n");
    printf("[-ml level]�F �~�b�v���x�����w�肵�܂��B0���w�肷���1x1�܂ł̃t���~�b�v�}�b�v�`�F�[���𐶐����܂�\n");
}

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& filePath, int numOptions, char* options[])
{
    path_ = filePath;

    LoadWICTextureFromFile(filePath);
    SaveDDSTextureToFile(numOptions,options);
}

void TextureConverter::LoadWICTextureFromFile(const std::filesystem::path& filePath)
{
    // szFile
    std::wstring wFilePath = path_.wstring();

    // loading wicTecture
    HRESULT hr = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
    assert(SUCCEEDED(hr));
}

void TextureConverter::SaveDDSTextureToFile(int numOptions, char* options[])
{
    size_t mipLevel = 0;
    // �~�b�v�}�b�v���x���w��̌���
    for (int i = 0; i < numOptions; i++)
    {
        if (std::string(options[i]) == "-ml")
        {
            // mipLevel�w��
            mipLevel = std::stoi(options[i + 1]);
            break;
        }
    }

    DirectX::ScratchImage mipchain;
    // �~�b�v�}�b�v��������
    HRESULT hr = DirectX::GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, mipLevel, mipchain);
    // �~�b�v��������������
    if (SUCCEEDED(hr))
    {
        // �C���[�W�ƃ��^�f�[�^���A�~�b�v�}�b�v�łŒu��������B
        scratchImage_ = std::move(mipchain);
        metadata_ = scratchImage_.GetMetadata();
    }

    // ���k�`���ɕϊ�����
    DirectX::ScratchImage converted;
    // �t�H�[�}�b�g��BC7 ������Ƃ��āA�c���Ɖ�����4�̔{���ł���K�v������B
    hr = DirectX::Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DXGI_FORMAT_BC7_UNORM_SRGB, DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL, 1.f, converted);
    // �~�b�v��������������
    if (SUCCEEDED(hr))
    {
        // �C���[�W�ƃ��^�f�[�^���A�~�b�v�}�b�v�łŒu��������B
        scratchImage_ = std::move(converted);
        metadata_ = scratchImage_.GetMetadata();
    }

    // �ǂݍ��񂾃e�N�X�`����SRGB�Ƃ��Ĉ���
    metadata_.format = DirectX::MakeSRGB(metadata_.format);
    // �o�̓t�@�C�����̐ݒ�
    std::wstring wFilePath = path_.replace_extension(".dds").wstring();
    hr = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DirectX::DDS_FLAGS_NONE, wFilePath.c_str());
    assert(SUCCEEDED(hr));
}
