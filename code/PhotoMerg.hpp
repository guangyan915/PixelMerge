#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <queue>
#include "File.hpp"

#define CHANNEL_3 3					//通道

using namespace cv;
using namespace std;

class Photo {
private:
	Mat* merge_photo;								// 合并的图片
	int merge_index = 0;
	File file_name;									// 图片名容器
	string photo_directory_path;					// 图片所在目录路径
	queue<Mat> photo_cache;							// 图片缓存
	int photo_cache_size;						// 图片缓存大小 
	vector<vector<vector<unsigned int>>>* photo_pixel_sum;	// 缓存里像素和（三通道）
	int photo_row;
	int photo_column;							// 图片像素列数
	
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