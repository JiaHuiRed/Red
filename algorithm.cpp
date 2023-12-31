#include<string>
#include <iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;
//#pragma warning(disable:4996)
//#define _CRT_SECURE_NO_WARNINGS


/*第一题 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target ，
写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。*/

class Solution {//二分查找思想
public:
	int search(vector<int>& nums, int target) {//引用一个名叫nums的整型容器 
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {//只要循环条件满足
			//int middle = left+((right-left) / 2);//防止溢出，实际上就是 (right+left)/2
			int middle = (right + left) / 2;//整型数据不用考虑溢出精度
			int num = nums[middle];
			if (num > target) {//寻找元素比中间数小，也就是在左半区间寻找
				right = middle - 1;
			}else if (nums[middle] < target) {
				left = middle + 1;
			}else{
				return middle;
			}
		}
		return -1;//失败返回-1
	}
};
/*第二题 给你一个数组 nums 。数组「动态和」的计算公式为：runningSum[i] = sum(nums[0]…nums[i]) 
请返回 nums 的动态和*/
class Solution {
public:
	vector<int> runningSum(vector<int>& nums) {
		int n = nums.size();
		for (int i=1;i < nums.size();i++) {
			nums[i] += nums[i - 1];
		}
	}
};
/*第三题 给你一个整数 n ，找出从 1 到 n 各个整数的 Fizz Buzz 表示，并用字符串数组 answer（下标从 1 开始）返回结果，其中：
answer[i] == "FizzBuzz" 如果 i 同时是 3 和 5 的倍数。
answer[i] == "Fizz" 如果 i 是 3 的倍数。
answer[i] == "Buzz" 如果 i 是 5 的倍数。
answer[i] == i （以字符串形式）如果上述条件全不满足。
*/

class Solution {
public:
	vector<string> fizzBuzz(int n) {
		vector<string> answer;//定义一个string类型的容器叫answer
		for (int i = 1; i <= n; i++) {
			string curr;
			if (i % 3 == 0) {
				curr += "Fizz";
			}
			if (i % 5 == 0) {
				curr += "Buzz";
			}
			if (curr.size() == 0) {  // 如果curr字符串的长度为0，说明它既不是Fizz也不是Buzz，则在curr字符串后面添加当前整数i的字符串表示。
				curr += to_string(i);
			}
			answer.emplace_back(curr);//构造一个对象，并将其直接添加到 vector 的末尾
		}
		return answer;
	}
};

/*第四题 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。
*/
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		while (left <= right) {
			int middle = (left + right) / 2;
			int n = nums[middle];
			if (n >= target) {
				right = middle - 1;
			}else {
				left = middle + 1;
			}
		}
		return left;
	}
};

/*第五题 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。
请你找出给定目标值在数组中的开始位置和结束位置。如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
*/
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int leftBorder = GetLeftBorder(nums, target);//寻找左边界
		int rightBorder = GetRightBorder(nums, target);//寻找右边界
		if (leftBorder == -2 || rightBorder == -2) return { -1, -1 };
		if (rightBorder - leftBorder > 1) return { leftBorder + 1, rightBorder - 1 };
		return { -1, -1 };
	}
private:
	int GetRightBorder(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
		while (left <= right) {
			int middle = (right + left) / 2;
			int n = nums[middle];
			if (n> target) {
				right = middle - 1;
			}
			else { // 寻找右边界，nums[middle] == target的时候更新left
				left = middle + 1;
				rightBorder = left;
			}
		}
		return rightBorder;
	}
	int GetLeftBorder(vector<int>& nums, int target) {
		int left = 0;
		int right = nums.size() - 1;
		int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
		while (left <= right) {
			int middle = (right + left) / 2;
			int n = nums[middle];
			if (n >= target) { // 寻找左边界，nums[middle] == target的时候更新right
				right = middle - 1;
				leftBorder = right;
			}
			else {
				left = middle + 1;
			}
		}
		return leftBorder;
	}
};
//第六题 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
struct ListNode {
	int data;
	ListNode* next;
	ListNode() : data(0), next(nullptr) {}
	ListNode(int x) : data(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : data(x), next(next) {}
};
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		ListNode* dummy = new ListNode(-1), *p= dummy;//定义一个哑结点
		ListNode* p1 = list1, * p2 = list2;
		while (p1 != NULL && p2 != NULL) {
			if (p1->data > p2->data) {
				p->next = p2;
				p2= p2->next;
			}else {
				p -> next = p1;
				p1 = p1->next;
			}
			p = p->next;//p不断前进
		}
		if (p1 != NULL) {
			p->next = p1;
		}
		if (p2 != NULL) {
			p->next = p2;
		}
		return dummy->next;
	}
};
/*第七题 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x** 0.5 。*/

class Solution {//使用exp指数函数
public:
	int mySqrt(int x) {
		if (x <= 0) return 0;
		int ans = exp(0.5 * log(x));
		return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
	}
};
//二分查找
class Solution {
public:
	int mySqrt(int x) {
		int left = 0, right = x, ans = -1;
		while (left <= right) {
			int middle = left + (right - left) / 2;
			if ((long long)middle * middle <= x) {
				ans = middle;
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}
		return ans;
	}
};
/*第八题 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。*/

class Solution {//暴力解法
public:
	int removeElement(vector<int>& nums, int val) {
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			if (nums[i] == val) {
				for (int j = i + 1;j < n;j++) {
					nums[j - 1] = nums[j];
				}
				i--;//因为实际上i后面的元素都往前一位，原本i位置已经是新元素，如果直接for i++，会漏元素
				n--;//相当于删除了一个数组数组，总数-1；
			}
		}
		return n;
	}
};
class Solution {//快慢指针
public:
	int removeElement(vector<int>& nums, int val) {
		int leftIndex = 0;
		int rightIndex = nums.size() - 1;
		while (leftIndex <= rightIndex) {
			// 找左边等于val的元素
			while (leftIndex <= rightIndex && nums[leftIndex] != val) {
				++leftIndex;
			}
			// 找右边不等于val的元素
			while (leftIndex <= rightIndex && nums[rightIndex] == val) {
				--rightIndex;
			}
			// 将右边不等于val的元素覆盖左边等于val的元素
			if (leftIndex < rightIndex) {
				nums[leftIndex++] = nums[rightIndex--];
			}
		}
		return leftIndex;   // leftIndex一定指向了最终数组末尾的下一个元素
	}
};
/*第九题 给你一个非严格递增排列的数组nums ，请你原地删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的相对顺序应该保持一致 。
然后返回 nums 中唯一元素的个数。考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：
更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。
返回 k 。*/

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {

	}
};

//第十题 给你一个按 非递减顺序 排序的整数数组 nums，返回每个数字的平方组成的新数组，要求也按非递减顺序 排序。

class Solution {//暴力解法
public:
	vector<int> sortedSquares(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0;i < n;i++) {
			nums[i] = nums[i] * nums[i];
		}
		sort(nums.begin(), nums.end());//快排
		return nums;
	}
};
//双指针
class Solution {
public:
	vector<int> sortedSquares(vector<int>& nums) {
		int k = nums.size()-1;
		vector<int>result(nums.size(), 0);//创造整型向量，初始长度为0
		for (int i = 0;int j = nums.size()-1;i <= j) {
			if (nums[i] * nums[i] < nums[j] * nums[j]) {
				result[k--] = nums[j] * nums[j];
				j--;
			}else {
				result[k--] = nums[i] * nums[i];
				i++;
			}
		}
		return result;
	}
};

/*//旋转函数
struct Color {
	int r;
	int g;
	int b;
};
class Rotate {
public:
	// 旋转函数
	Color* RotatePic90(int width, int height, Color input[]) {
		Color* rotated = new Color[height * width]; // 分配内存
		int centerX = width / 2;
		int centerY = height / 2;
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				int new_x = centerY - (x - centerX);
				int new_y = centerY + (y - centerY);
				// 确保旋转后的坐标没有越界
				if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
					rotated[new_y * width + new_x] = input[y * width + x];
				}
			}
		}
		return rotated;
	}
};

int main(int argc,char const*argv[]) {
	// 初始化图像数据，这里只是一个示例，实际应用中应该从文件等来源获取
	Color input[400] = {
		// ... 图像数据初始化
	};
	// 创建Reverse类的实例
	Rotate* rev = new Rotate();
	// 调用旋转函数
	Color* rotated = rev->RotatePic90(20, 20, input);
	// 输出旋转后的图像数据以验证
	for (int i = 0; i < 400; ++i) {
		std::cout << "Color(" << rotated[i].r << ", " << rotated[i].g << ", " << rotated[i].b << ")" << std::endl;
	}
	// 释放内存
	delete[] rotated;
	delete rev;
	return 0;
}*/
//寻找元素
/*class Solution {
public:
	int getValue(vector<int>& nums, int n) {//寻找一个可能数量多于一半的主元素
		int i, Major, count = 1;//Major用来保存候选元素
		Major = nums[0];
		for (i = 1;i < n;i++) {
			if (nums[i] == Major) {
				count++;//对数组内元素计数
			}else {
				if (count > 0) {//处理不是主元素的情况
					count--;
				}else {
					Major = nums[i];//更换候选元素，重新计数
					count = 1;
				}
			}
		}
		if (count > 0) {
			for (i = count = 0;i < n;i++) {
				if (nums[i] == Major) {//统计候选元素出现的实际次数
					count++;
				}
			}
		}
		if (count > n / 2) {
			return Major;//确认元素
		}else {
			return 0;//不存在则返回
		}
	}
};//也可以使用计数排序，但是会使用辅助数组，不满足空间尽量小的要求
*/

