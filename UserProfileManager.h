#include <vector>
#include <string>

using namespace std;

class UserProfile {
    public:
        string username;
        int age;
        double weight;
        double height;
        char gender;
        UserProfile(const string&, int, char, double, double);
};

class UserProfileManager {
    private:
        vector<UserProfile> profiles;
        string profileFileName = "profiles.txt";

    public:
        UserProfileManager(const string&);
        void AddProfile(const UserProfile&);
        void SaveToFile();
        void LoadProfiles();
        void EditProfile(const string&);
        UserProfile GetProfileByUsername(const string&);
};

class Workout {
    public:
        string name;
        int sets, reps;
        double weight;
        Workout() {};
        Workout(string, int, int);
        Workout(string, int, int, double);
        void setVariables(string, int, int);
        void setVariables(string, int, int, double);
};

class WorkoutManager {
    private:
        vector<Workout> workouts;
    public:
        WorkoutManager();
        void AddWorkout(const Workout&);
        void SaveWorkout(UserProfile&, string);
        void printWorkouts();
};