#include "PhotoMerg.hpp"

Photo::Photo(){}

void Photo::setFileName() {
	file_name.setFileNameRes();
}

void Photo::setPhotoRow(size_t n) {
	photo_row = n;
}

void Photo::setPhotoRowAndColunm() {
	Mat img = imread(photo_directory_path + file_name[0]);
	photo_row = img.rows;
	photo_column = img.cols;
}


void Photo::setPhotoColumn(size_t n) {
	photo_column = n;
}
void Photo::setPhotoCacheSize(size_t size) {
	photo_cache_size = size;
}
void Photo::setOneRow(const Mat& image, size_t row) {
	for (size_t col = 0; col < merge_photo->cols; col++)
	{
		merge_photo->at<Vec3b>(row, col)[0] = image.at<Vec3b>(row, col)[0];
		merge_photo->at<Vec3b>(row, col)[1] = image.at<Vec3b>(row, col)[1];
		merge_photo->at<Vec3b>(row, col)[2] = image.at<Vec3b>(row, col)[2];
	}
}
void Photo::setOneColumn(const Mat& image, size_t col) {
	for (size_t row = 0; row < merge_photo->rows; row++)
	{
		merge_photo->at<Vec3b>(row, col)[0] = image.at<Vec3b>(row, col)[0];
		merge_photo->at<Vec3b>(row, col)[1] = image.at<Vec3b>(row, col)[1];
		merge_photo->at<Vec3b>(row, col)[2] = image.at<Vec3b>(row, col)[2];
	}
}

void Photo::setOneRowPixelAverage(size_t row) {
	for (int col = 0; col < photo_column; col++) {
		uchar pixel0 = (*photo_pixel_sum)[row][col][0] / photo_cache_size;
		uchar pixel1 = (*photo_pixel_sum)[row][col][1] / photo_cache_size;
		uchar pixel2 = (*photo_pixel_sum)[row][col][2] / photo_cache_size;

		merge_photo->at<Vec3b>(row, col)[0] = pixel0;
		merge_photo->at<Vec3b>(row, col)[1] = pixel1;
		merge_photo->at<Vec3b>(row, col)[2] = pixel2;
	}
}

void Photo::setOneColumnPixelAverage(size_t col) {
	for (int row = 0; row < photo_row; row++) {
		uchar pixel0 = (*photo_pixel_sum)[row][col][0] / photo_cache_size;
		uchar pixel1 = (*photo_pixel_sum)[row][col][1] / photo_cache_size;
		uchar pixel2 = (*photo_pixel_sum)[row][col][2] / photo_cache_size;

		merge_photo->at<Vec3b>(row, col)[0] = pixel0;
		merge_photo->at<Vec3b>(row, col)[1] = pixel1;
		merge_photo->at<Vec3b>(row, col)[2] = pixel2;
	}
}

int Photo::initMergePhotoProrertyAndFileName(string path) {
	if (!file_name.openDirctory(path)) {
		cout << "文件不存在！" << endl;
		return 1;
	}
	if (path.back() != '\\') photo_directory_path = path + '\\';
	else photo_directory_path = path;
	file_name.setFilePath(path);
	setFileName();

	merge_photo = new Mat(imread(photo_directory_path + file_name[0]));
	
	photo_row = merge_photo->rows;
	photo_column = merge_photo->cols;
	
	for (int i = 0; i < photo_row; i++) {
		for (int j = 0; j < photo_column; j++) {
			merge_photo->at<Vec3b>(i, j)[0] = 0;
			merge_photo->at<Vec3b>(i, j)[1] = 0;
			merge_photo->at<Vec3b>(i, j)[2] = 0;
		}
	}

	photo_pixel_sum = new vector<vector<vector<unsigned int>>>
		(photo_row, vector<vector<unsigned int>>
			(photo_column, vector<unsigned int>
				(CHANNEL_3, 0)));

	return 0;
}

void Photo::pushPhotoCacheBackRow(const Mat& img, size_t index) {
	photo_cache.push(img);
	if (photo_cache.size() <= photo_cache_size) {
		for (int row = 0; row < photo_row; row++) {
			for (int col = 0; col < photo_column; col++) {
				(*photo_pixel_sum)[row][col][0] += img.at<Vec3b>(row, col)[0];
				(*photo_pixel_sum)[row][col][1] += img.at<Vec3b>(row, col)[1];
				(*photo_pixel_sum)[row][col][2] += img.at<Vec3b>(row, col)[2];
			}
		}
		if (photo_cache.size() == photo_cache_size) {
			setOneRowPixelAverage(index - photo_cache_size + 1);
		}
	}
	else {
		for (int row = 0; row < photo_row; row++) {
			for (size_t col = 0; col < photo_column; col++) {
				(*photo_pixel_sum)[row][col][0] -= photo_cache.front().at<Vec3b>(row, col)[0];
				(*photo_pixel_sum)[row][col][1] -= photo_cache.front().at<Vec3b>(row, col)[1];
				(*photo_pixel_sum)[row][col][2] -= photo_cache.front().at<Vec3b>(row, col)[2];
				(*photo_pixel_sum)[row][col][0] += img.at<Vec3b>(row, col)[0];
				(*photo_pixel_sum)[row][col][1] += img.at<Vec3b>(row, col)[1];
				(*photo_pixel_sum)[row][col][2] += img.at<Vec3b>(row, col)[2];
			}
		}
		photo_cache.pop();
		setOneRowPixelAverage(index - photo_cache_size + 1);
	}
}
void Photo::pushPhotoCacheBackColumn(const Mat& img, size_t index) {
	photo_cache.push(img);
	if (photo_cache.size() <= photo_cache_size) {
		for (int row = 0; row < photo_row; row++) {
			for (int col = 0; col < photo_column; col++) {
				(*photo_pixel_sum)[row][col][0] += img.at<Vec3b>(row, col)[0];
				(*photo_pixel_sum)[row][col][1] += img.at<Vec3b>(row, col)[1];
				(*photo_pixel_sum)[row][col][2] += img.at<Vec3b>(row, col)[2];
			}
		}
		if (photo_cache.size() == photo_cache_size) {
			setOneColumnPixelAverage(index - photo_cache_size + 1);
		}
	}
	else {
		for (int row = 0; row < photo_row; row++) {
			for (size_t col = 0; col < photo_column; col++) {
				(*photo_pixel_sum)[row][col][0] -= photo_cache.front().at<Vec3b>(row, col)[0];
				(*photo_pixel_sum)[row][col][1] -= photo_cache.front().at<Vec3b>(row, col)[1];
				(*photo_pixel_sum)[row][col][2] -= photo_cache.front().at<Vec3b>(row, col)[2];
				(*photo_pixel_sum)[row][col][0] += img.at<Vec3b>(row, col)[0];
				(*photo_pixel_sum)[row][col][1] += img.at<Vec3b>(row, col)[1];
				(*photo_pixel_sum)[row][col][2] += img.at<Vec3b>(row, col)[2];
			}
		}
		photo_cache.pop();
		setOneColumnPixelAverage(index - photo_cache_size + 1);
	}
}
int Photo::beginRowMerge() {
	if (file_name.size() < photo_row) return -1;
	for (size_t row = 0; row < photo_row; row++) {
		Mat img = imread(photo_directory_path + file_name[row]);
		setOneRow(img, row);
		cout << "第" << row + 1 << "行像素处理完成！" << file_name[row] << "已载入！" << endl;
	}
	return 0;
}
int Photo::beginColumnMerge() {
	if (file_name.size() < photo_column) return -1;
	for (size_t col = 0; col < photo_column; col++) {
		Mat img = imread(photo_directory_path + file_name[col]);
		setOneColumn(img, col);
		cout << "第" << col + 1 << "列像素处理完成！" << file_name[col] << "已载入！" << endl;
	}
	return 0;
}
int Photo::beginRowIntervalAverageMerge() {
	cout << "请输入区间均值算法区间范围（图片张数）： ";
	size_t n;
	cin >> n;
	photo_cache_size = n;
	if (file_name.size() < photo_row + n) return -1;
	cout << "正在载入..." << endl;
	for (int i = 0; i < photo_row + photo_cache_size - 1; i++) {
		pushPhotoCacheBackRow(imread(photo_directory_path + file_name[i]), i);
		if (i >= photo_cache_size - 1) cout << "第" << i - photo_cache_size + 2 << "行像素处理完成！" << endl;
	}
	cout << "加载完成！" << endl;
	return 0;
}
int Photo::beginColumnIntervalAverageMerge() {
	cout << "请输入区间均值算法区间范围（图片张数）： ";
	size_t n;
	cin >> n;
	photo_cache_size = n;
	if (file_name.size() < photo_column + n) return -1;
	cout << "正在载入..." << endl;
	for (int i = 0; i < photo_column + photo_cache_size - 1; i++) {
		pushPhotoCacheBackColumn(imread(photo_directory_path + file_name[i]), i);
		if (i >= photo_cache_size - 1) cout << "第" << i - photo_cache_size + 2 << "列像素处理完成！" << endl;
	}
	cout << "加载完成！" << endl;
	return 0;
}

void Photo::mergePhotoDerive() {
	cout << "请输入图片存储路径： ";
	string path;
	cin >> path;
	if (path.back() != '\\') path += '\\';
	string name = "merger_picture";
	int i = 1;
	string tail = ".jpg";
	string filepath = path + name + tail;
	while (_access(filepath.c_str(), 0) == 0) {
		filepath = path + name + to_string(i++) + tail;
	}
	showMergePhoto();
	imwrite(filepath, *merge_photo);
	cout << "合成图片已保存到：" << filepath << endl;
}

void Photo::showMergePhoto() {
	imshow("test", *merge_photo);
	waitKey(0);

}
