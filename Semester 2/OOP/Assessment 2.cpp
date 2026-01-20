#include <iostream>
#include <iomanip>
using namespace std;
class Time 
{
    private:
    int hours, minutes, seconds; 
    public:
    Time(int h = 0, int m = 0, int s = 0) 
    {
        setTime(h, m, s);
    }
    Time(const Time &t) 
    {
        hours = t.hours;
        minutes = t.minutes;
        seconds = t.seconds;
    }
    void setTime(int h, int m, int s) 
    {
        if (h >= 0 && h < 24) 
        hours = h;
        else 
        hours = 0;
        if (m >= 0 && m < 60) 
        minutes = m;
        else 
        minutes = 0;
        if (s >= 0 && s < 60) 
        seconds = s;
        else 
        seconds = 0;
    }
    void increment() 
    {
        seconds++;
        if (seconds == 60) 
        {
            seconds = 0;
            minutes++;
            if (minutes == 60) 
            {
                minutes = 0;
                hours = (hours + 1) % 24;
            }
        }
    }
    void display24() const 
    {
        cout << setfill('0') << setw(2) << hours << ":"
            << setw(2) << minutes << ":" << setw(2) << seconds <<endl;
    }
    void display12() const 
    {
        int h = (hours == 0 || hours == 12) ? 12 : hours % 12;
        string period = (hours < 12) ? "AM" : "PM";
        cout <<setfill('0') <<setw(2) << h << ":"
                  <<setw(2) << minutes << ":" <<setw(2) << seconds << " " << period <<endl;
    }
    int getHours() const 
    {
        return hours; 
    }
    int getMinutes() const 
    { 
        return minutes; 
    }
    int getSeconds() const 
    {
        return seconds; 
    }
    ~Time(){}
};
int main() 
{
    Time t1(23, 59, 58);
    cout << "Initial Time (24-hour format): ";
    t1.display24();
    t1.increment();
    cout << "After Increment (24-hour format): ";
    t1.display24();
    cout << "Time in 12-hour format: ";
    t1.display12();
    return 0;
}
/*Task 2:
class TestScores 
{
    private:
    double score1, score2, score3;
    public:
    TestScores(double s1 = 0, double s2 = 0, double s3 = 0) 
    {
        setScores(s1, s2, s3);
    }
    void setScores(double s1, double s2, double s3) 
    {
        score1 = (s1 >= 0) ? s1 : 0;
        score2 = (s2 >= 0) ? s2 : 0;
        score3 = (s3 >= 0) ? s3 : 0;
    }
    double getScore1() const 
    { 
        return score1; 
    }
    double getScore2() const 
    {
        return score2; 
    }
    double getScore3() const 
    {
        return score3; 
    }
    double getAverage() const 
    {
        return (score1 + score2 + score3) / 3.0;
    }
};
int main() 
{
    double s1,s2,s3;
    cout<<"Enter three test scores: ";
    cin>>s1>>s2>>s3;
    TestScores student(s1, s2, s3);
    cout<<"Average Score: "<<student.getAverage()<<endl;
    return 0;
}*/