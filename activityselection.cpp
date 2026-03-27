#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    string id;
    int start;
    int finish;
};

bool compareActivities(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}
void activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compareActivities);

    cout << "Selected Activities: ";

    int i = 0;
    cout << activities[i].id << " ";
    for (int j = 1; j < activities.size(); j++) {
        if (activities[j].start >= activities[i].finish) {
            cout << activities[j].id << " ";
            i = j;
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    vector<Activity> activities(n);
    cout << "Enter activity ID, start time, and finish time:\n";
    for (int i = 0; i < n; i++) {
        cin >> activities[i].id >> activities[i].start >> activities[i].finish;
    }

    activitySelection(activities);

    return 0;
}