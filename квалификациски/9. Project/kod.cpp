#include <iostream>

using namespace std;

class Project {
protected:
    string name;
    int duration;
public:
    Project(string name = "Project1", int duration = 2) : name(name), duration(duration) {}

    ~Project() {}

    void showInfo() {
        cout << name << " " << duration << " " ;
    }
};

class TeamProject:public Project{
private:
    int teamSize;
public:
    TeamProject(string name = "Project1", int duration = 2, int teamSize=0)
    : Project(name, duration){
        this->teamSize=(teamSize>0 && teamSize<10)? teamSize:5;
    }
    int calculateTotalTeamHours(){
        return duration+teamSize*160;
    }
    void showInfo(){
        Project::showInfo();
        cout<<teamSize<<endl;
    }
};

TeamProject *createTeamProjects(int n) {
    TeamProject *teamProjects = new TeamProject[n];
    string name;
    int duration, teamSize;
    for (int i = 0; i < n; i++) {
        cin >> name >> duration >> teamSize;
        teamProjects[i] = TeamProject(name, duration, teamSize);
    }
    return teamProjects;
}


int main() {
    int testCase;
    cin >> testCase;

    switch (testCase) {
        case 1 : {
            TeamProject teamProject;
            teamProject.showInfo();
            break;
        }
        case 2 : {
            TeamProject teamProject("CS101", 5, 3);
            teamProject.showInfo();
            TeamProject teamProject1("CS102", 7, 2);
            teamProject1.showInfo();
            break;
        }
        case 3 : {
            TeamProject teamProject("CS101", 5, 13);
            teamProject.showInfo();
            TeamProject teamProject1("CS102", 7, 0);
            teamProject1.showInfo();
            break;
        }
        case 4: {
            TeamProject teamProject("CS101", 4, 1);
            cout << teamProject.calculateTotalTeamHours();
            break;
        }
        case 5: {
            int n;
            cin >> n;
            TeamProject *teamProjects = createTeamProjects(n);
            for (int i = 0; i < n; i++) {
                teamProjects[i].showInfo();
            }
            delete [] teamProjects;
            break;
        }
        default: {
            int n;
            cin >> n;
            TeamProject *teamProjects = createTeamProjects(n);
            for (int i = 0; i < n; i++) {
                teamProjects[i].showInfo();
            }
            for (int i = 0; i < n; i++) {
                cout << teamProjects[i].calculateTotalTeamHours() << endl;
            }
            delete [] teamProjects;
            break;
        }
    }
}

