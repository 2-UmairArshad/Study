#include <iostream>
#include <string>
using namespace std;
//----------------Q1
//int main() {
//	int arr[] = { 12, 5, 7, 3, 9 };
//	int n = 5;
//	for (int i = 0; i < n - 1; i++) {
//		for (int j = 0; j < n - i - 1; j++) {
//			if (arr[j] > arr[j + 1]) {
//				int temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}
//	cout << "Sorted Array: ";
//	for (int i = 0; i < n; i++)
//		cout << arr[i] << " ";
//}
// ------------Q2
//int main() {
//	int arr[] = { 4, 2, 7, 2, 4, 9, 1 };
//	int n = 7;
//	for (int i = 0; i < n - 1; i++) {
//		for (int j = 0; j < n - i - 1; j++) {
//			if (arr[j] > arr[j + 1]) {
//				int temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}
//	cout << "Sorted Array: ";
//	for (int i = 0; i < n; i++)
//	{
//		if (arr[i] == arr[i + 1])
//			{
//				continue;
//			}
//		else
//			cout << arr[i] << " ";
//	}
//}
//-------------Q3
//int main() {
//	int ages[] = { 18, 25, 15, 30, 22, 40, 10, 28 };
//	int n = 8;
//	for (int i = 0; i < n - 1; i++) {
//		int maxIndex = i;
//		for (int j = i + 1; j < n; j++) {
//			if (ages[j] > ages[maxIndex])
//				maxIndex = j;
//		}
//		int temp = ages[i];
//		ages[i] = ages[maxIndex];
//		ages[maxIndex] = temp;
//	}
//	cout << "Sorted Array: ";
//	for (int i = 0; i < n; i++)
//		cout << ages[i] << " ";
//}
//-----------Q4
//int main() {
//	int salaries[] = { 35000, 50000, 25000, 40000, 60000, 30000, 45000 };
//	int n = 7;
//	for (int i = 0; i < n - 1; i++) {
//		int minIndex = i;
//		for (int j = i + 1; j < n; j++) {
//			if (salaries[j] < salaries[minIndex])
//				minIndex = j;
//		}
//		int temp = salaries[i];
//		salaries[i] = salaries[minIndex];
//		salaries[minIndex] = temp;
//	}
//	cout << "Sorted Array: ";
//	for (int i = 0; i < n; i++)
//		cout << salaries[i] << " ";
//	cout << "\nSecond Highest Salary: ";
//	cout << salaries[n - 2];
//}
//-----------------Q5
//int main() {
//	int arr[] = { 12, 4, 7, 9, 2, 15, 10 };
//	int n = 7;
//	for (int i = 1; i < n; i++) {
//		int key = arr[i];
//		int j = i - 1;
//		while (j >= 0 && arr[j] > key) {
//			arr[j + 1] = arr[j];
//			j--;
//		}
//		arr[j + 1] = key;
//	}
//	cout << "Sorted Array: ";
//	for (int i = 0; i < n; i++)
//		cout << arr[i] << " ";
//	int median = arr[n / 2];
//	cout << "Median: " << median;
//}
// ----------------Q6
//struct Student {
//    string name;
//    int marks;
//};
//int main() {
//    Student arr[4] = { {"Ali", 85}, {"Sara", 92}, {"Omar", 75}, {"Hassan", 90} };
//    int n = 4;
//    for (int i = 0; i < n - 1; i++) {
//        for (int j = 0; j < n - i - 1; j++) {
//            if (arr[j].marks < arr[j + 1].marks) {
//                Student temp = arr[j];
//                arr[j] = arr[j + 1];
//                arr[j + 1] = temp;
//            }
//        }
//    }
//    for (int i = 0; i < n; i++) {
//        cout << arr[i].name << " " << arr[i].marks << endl;
//    }
//    return 0;
//}
////-----------------Q7
//int main() {
//	string names[100];
//	for (int i = 0; i < 100; i++)
//	{
//		getline(cin, names[i]);
//	}
//	for (int i = 0; i < 100 - 1; i++) {
//		for (int j = 0; j < 100 - i - 1; j++) {
//			if (names[j] > names[j + 1]) {
//				string temp = names[j];
//				names[j] = names[j + 1];
//				names[j + 1] = temp;
//			}
//		}
//	}
//	cout << "Sorted Names: ";
//	for (int i = 0; i < 100; i++)
//		cout << names[i] << " ";
//}
//int main() {
//    string text;
//    cout << "Enter a paragraph: ";
//    getline(cin, text); 
//    string words[100];  
//    int count = 0;
//    string word = "";
//    for (int i = 0; i <= text.length(); i++) {
//        if (text[i] == ' ' || text[i] == '\0') {
//            if (word != "") {
//                words[count++] = word;
//                word = "";
//            }
//        }
//        else {
//            word += text[i];
//        }
//    }
//    for (int i = 0; i < count - 1; i++) {
//        for (int j = 0; j < count - i - 1; j++) {
//            if (words[j] > words[j + 1]) {
//                string temp = words[j];
//                words[j] = words[j + 1];
//                words[j + 1] = temp;
//            }
//        }
//    }
//    cout << "\nSorted words (alphabetical order):\n";
//    for (int i = 0; i < count; i++) {
//        cout << words[i] << " ";
//    }
//    cout << endl;
//    return 0;
//}
