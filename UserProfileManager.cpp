#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "UserProfileManager.h"
using namespace std;

        
//UserProfile Constructor
UserProfile::UserProfile(const string& username, int age, char gender, double weight, double height)
            : username(username), age(age), gender(gender), weight(weight), height(height) {}

//UserProfileManager Constructor
UserProfileManager::UserProfileManager(const string& fileName) : profileFileName(fileName) {
    LoadProfiles();
}

void UserProfileManager::AddProfile(const UserProfile& profile) {
    profiles.push_back(profile);
}

void UserProfileManager::SaveToFile() {
    //Saving profile
    ofstream file(profileFileName);
    if (!file) {
        cout << "ERROR: Unable to locate file. \n";
        return;
    }

    for (const UserProfile& profile : profiles) {
        file << profile.username << ','
             << profile.age << ','
             << profile.gender << ','
             << profile.weight << ','
             << profile.height << '\n';
    }
    file.close();
    //Creating workout log file in separate folder
    string folderPath = "C:/Users/edwar/Desktop/Personal Projects/workoutlogs/",
           fileName;
    for (const UserProfile& profile : profiles) {
        fileName = profile.username + "Workouts.txt";
        ofstream file(folderPath + fileName);
        file.close();
    }
}

void UserProfileManager::LoadProfiles() {
    ifstream file(profileFileName);
    if (!file) {
        cout << "ERROR: Unable to open file. \n";
        return;
    }

    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string username;
        int age;
        char gender;
        double weight, height;

        if(getline(ss, username, ',') &&
            (ss >> age) && ss.ignore() &&
            (ss >> gender) && ss.ignore() &&
            (ss >> weight) && ss.ignore() &&
            (ss >> height)) {
                profiles.emplace_back(username, age, gender, weight, height);
        }
        else {
            cout << "ERROR: Invalid data format in profiles file.\n";
        }
    }
            
    file.close();
}

void UserProfileManager::EditProfile(const string& username) {
    for (auto& profile : profiles) {
        if (profile.username == username) {
            cout << "Enter new age: ";
            cin >> profile.age;
            cout << "Enter new weight (in lbs): ";
            cin >> profile.weight;
            cout << "Enter new height (in inches): ";
            cin >> profile.height;

            cout << "Profile updated successfully!\n";

            SaveToFile();

            return;
        }
    }
}

UserProfile UserProfileManager::GetProfileByUsername(const string& username) {
    for (const UserProfile& profile : profiles) {
        if (profile.username == username)
            return profile;
    }

    cout << "ERROR: Username not found\n";
    return UserProfile("", 0, '?', 0.0, 0.0);
}


//Workout constructor
Workout::Workout(string name, int sets, int reps) 
            : name(name), sets(sets), reps(reps) {}

//Workout constructor with weight
Workout::Workout(string name, int sets, int reps, double weight) 
            : name(name), sets(sets), reps(reps), weight(weight) {}

WorkoutManager::WorkoutManager() {}

void WorkoutManager::AddWorkout(const Workout& workout) {
    workouts.push_back(workout);
}

void Workout::setVariables(string name, int sets, int reps) {
    name = name;
    sets = sets;
    reps = reps;
}

void Workout::setVariables(string exerciseName, int exerciseSets, int exerciseReps, double exerciseWeight) {
    name = exerciseName;
    sets = exerciseSets;
    reps = exerciseReps;
    weight = exerciseWeight;
}

void WorkoutManager::printWorkouts() {
    for (const Workout& workout : workouts) {
        cout << workout.name << endl;
        cout << workout.sets << endl;
        cout << workout.reps << endl;
        if(workout.weight != 0)
            cout << workout.weight << endl;
    }
}

void WorkoutManager::SaveWorkout(UserProfile& targetProfile, string date) {
    string folderPath = "C:/Users/edwar/Desktop/Personal Projects/workoutlogs/";
    string fileName = targetProfile.username + "Workouts.txt";
    ofstream file(folderPath + fileName, ios::app);
    if (!file) {
        cout << "ERROR: Unable to locate file. \n";
        return;
    }
    file << date << '\n';
    for (Workout& workout : workouts) {
        file << workout.name << ", "
             << workout.sets << 'x'
             << workout.reps;
             if(workout.weight > 0)
                file << ", " << workout.weight << "lbs" << '\n';
             else
                file << '\n';
    }
    file << '\n';
    file.close();
}