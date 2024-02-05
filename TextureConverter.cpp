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
    // �~�b�v�}�b�v��������
    HRESULT hr = DirectX::GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, mipchain);
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
