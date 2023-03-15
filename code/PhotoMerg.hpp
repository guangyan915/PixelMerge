#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <queue>
#include "File.hpp"

#define CHANNEL_3 3					//ͨ��

using namespace cv;
using namespace std;

class Photo {
private:
	Mat* merge_photo;								// �ϲ���ͼƬ
	int merge_index = 0;
	File file_name;									// ͼƬ������
	string photo_directory_path;					// ͼƬ����Ŀ¼·��
	queue<Mat> photo_cache;							// ͼƬ����
	int photo_cache_size;						// ͼƬ�����С 
	vector<vector<vector<unsigned int>>>* photo_pixel_sum;	// ���������غͣ���ͨ����
	int photo_row;
	int photo_column;							// ͼƬ��������
	
public:
	Photo();
	~Photo() {
		delete photo_pixel_sum;
		delete merge_photo;
	}
	void setFileName();
	void setPhotoRow(size_t);
	void setPhotoColumn(size_t);
	void setPhotoRowAndColunm();
	void setPhotoCacheSize(size_t);
	void setOneRow(const Mat&, size_t);
	void setOneColumn(const Mat&, size_t);
	void setOneRowPixelAverage(size_t);
	void setOneColumnPixelAverage(size_t);
private:
	void pushPhotoCacheBackRow(const Mat&, size_t);
	void pushPhotoCacheBackColumn(const Mat&, size_t);
public:
	int initMergePhotoProrertyAndFileName(string path);
	int beginRowMerge();
	int beginColumnMerge();
	int beginRowIntervalAverageMerge();
	int beginColumnIntervalAverageMerge();
	void mergePhotoDerive();
	void showMergePhoto();
};