//#include <iostream>
//#include <string>
//using namespace std;
//
///*--------------Task:1----------------*/

//int main() {
//    string tracks[] = { "SongA", "SongB", "SongC", "SongD", "SongE" };
//    string t;
//    int n = 5, c = 0, f = 0;
//
//    cin >> t;
//    for (int i = 0; i < n; i++) {
//        c++;
//        if (tracks[i] == t) {
//            cout << i << endl;
//            f = 1;
//            break;
//        }
//    }
//    if (f == 0) cout << "Track not available." << endl;
//    cout << c << endl;
//   return 0;
//}
//
///*---------------Task:2-------------*/
//#include <iostream>
//using namespace std;
//
//int main() {
//    int flights[] = { 101, 202, 303, 404, 505, 606, 707, 808 };
//    int n = 8, f, found = 0;
//
//    cin >> f;
//    int low = 0, high = n - 1;
//    while (low <= high) {
//        int mid = (low + high) / 2;
//        cout << flights[mid] << " ";
//        if (flights[mid] == f) {
//            cout << "\nFlight Booked." << endl;
//            found = 1;
//            break;
//        }
//        else if (flights[mid] < f) {
//            low = mid + 1;
//        }
//        else {
//            high = mid - 1;
//        }
//    }
//    if (!found) cout << "\nFlight Not Found." << endl;
//    return 0;
//}
///*---------------------Task:3----------------------*/
//#include <iostream>
//using namespace std;
//
//int main() {
//    int marks[100], n, m, c1 = 0, c2 = 0, s = 0, f = 0;
//
//    cin >> n;
//    for (int i = 0; i < n; i++) cin >> marks[i];
//
//    for (int i = 0; i < n - 1; i++) {
//        for (int j = 0; j < n - i - 1; j++) {
//            c1++;
//            if (marks[j] > marks[j + 1]) {
//                swap(marks[j], marks[j + 1]);
//                s++;
//            }
//        }
//    }
//
//    for (int i = 0; i < n; i++) cout << marks[i] << " ";
//    cout << endl;
//
//    cin >> m;
//    for (int i = 0; i < n; i++) {
//        c2++;
//        if (marks[i] == m) {
//            cout << i << endl;
//            f = 1;
//            break;
//        }
//    }
//    if (!f) cout << "Not Found" << endl;
//    cout << s << " " << c1 + c2 << endl;
//    return 0;
//}
///*---------------------Task:4------------------*/
//#include <iostream>
//#include <iomanip>
//using namespace std;
//
//int main() {
//    float items[100], x;
//    int n = 0;
//
//    while (cin >> x) {
//        int i = n - 1;
//        while (i >= 0 && items[i] > x) {
//            items[i + 1] = items[i];
//            i--;
//        }
//        items[i + 1] = x;
//        n++;
//
//        for (int j = 0; j < n; j++) cout << fixed << setprecision(2) << items[j] << " ";
//        cout << endl;
//
//        if (n > 8) {
//            cout << items[0] << " " << items[1] << " ";
//            cout << items[n - 2] << " " << items[n - 1] << endl;
//        }
//    }
//    return 0;
//}