#include <iostream>
#include <fstream>
#include "UserProfileManager.h"

using namespace std;

UserProfileManager profileManager("profiles.txt");
WorkoutManager workoutManager;

UserProfile createProfile() {
    string username;
    int age;
    char gender;
    double weight;
    double height;

    cout << "Please enter a profile username: ";
    cin >> username;
    cout << "Please enter age: ";
    cin >> age;
    cout << "Please enter gender ('M' or 'F'): ";
    cin >> gender;
    toupper(gender);
    cout << "Please enter weight (in lbs): ";
    cin >> weight;
    cout << "Please enter height (in inches): ";
    cin >> height;

    UserProfile newProfile(username, age, gender, weight, height);
    profileManager.AddProfile(newProfile);
    profileManager.SaveToFile();

    cout << "Profile created and saved. \n";
    cout << endl;

    return newProfile;
}

void calorieCalc(UserProfile targetProfile) {
    int activity;
    cout << "1. Sedentary: little or no exercise\n";
    cout << "2. Lightly active: light exercise/sports 1-3 days/week\n";
    cout << "3. Moderately active: moderate exercise/sports 3-5 days/week\n";
    cout << "4. Very active: hard exercise/sports 6-7 days a week\n";
    cout << "5. Extremely active: very hard exercise/sports & physical " <<
            "job or 2x training\n";
    cout << "Please choose your activity level from above: ";
    cin >> activity;
    cout << endl;

    double weightKG = targetProfile.weight / 2.205;
    double heightCM = targetProfile.height * 2.54;
    int age = targetProfile.age;

    double BMR;

    if(targetProfile.gender == 'M') {
        BMR = (10.0 * weightKG) + (6.25 * heightCM) - (5.0 * age) + 5.0;
    } else {
        BMR = (10.0 * weightKG) + (6.25 * heightCM) - (5.0 * age) - 161.0;
    }

    switch(activity) {
        case 1:
            BMR *= 1.2;
            break;
        case 2:
            BMR *= 1.375;
            break;
        case 3:
            BMR *= 1.55;
            break;
        case 4:
            BMR *= 1.725;
            break;
        case 5:
            BMR *= 1.9;
            break;
    }

    int goal;
    cout << "1. Lose weight (-1lbs/week)\n";
    cout << "2. Maintain current weight\n";
    cout << "3. Gain weight (+1lbs/week)\n";
    cout << "Please choose your goal from above: ";
    cin >> goal;
    cout << endl;

    double calories = BMR;

    switch(goal) {
        case 1:
            calories -= 500;
            cout << "Weight loss: " << calories << " calories/day\n";
            break;
        case 2:
            cout << "Maintain: " << calories << " calories/day\n";
            break;
        case 3:
            calories += 500;
            cout << "Weight gain: " << calories << " calories/day\n";
            break;
    }
}

void logWorkout(UserProfile targetProfile) {
    string workoutDate;
    cout << "Enter date of workout (mm/dd/yyyy): ";
    cin >> workoutDate;

    int numExer;
    cout << "Please enter the number of exercises performed: ";
    cin >> numExer;

    string exerciseName;
    int exerciseSets, exerciseReps;
    double exerciseWeight;
    char recordWeight;
    for(int i = 0; i < numExer; i++) {
        cin.ignore();
        cout << "Enter exercise " << i+1 << " name: ";
        getline(cin, exerciseName);
        cout << "Enter number of sets: ";
        cin >> exerciseSets;
        cout << "Enter number of reps per set: ";
        cin >> exerciseReps;
        cout << "Record weight? ('y' or 'n'): ";
        cin >> recordWeight;

        Workout newWorkout;
        if(recordWeight == 'y') {
            cout << "Enter average/top weight: ";
            cin >> exerciseWeight;
            newWorkout = Workout(exerciseName, exerciseSets, exerciseReps, exerciseWeight);
        } else {
            exerciseWeight = 0;
            newWorkout = Workout(exerciseName, exerciseSets, exerciseReps, exerciseWeight);
        }
        workoutManager.AddWorkout(newWorkout);
    }
    workoutManager.SaveWorkout(targetProfile, workoutDate);
    cout << "Workout saved successfully.";
}

void loginPrompt() {
    cout << "Options:\n";
    cout << "1. Log your workout\n";
    cout << "2. Calculate your calories\n";
    cout << "3. Edit your profile\n";
    cout << "0. Logout of profile\n";
    cout << "Choose an action from the menu above: ";
}

void afterLogin(UserProfile& targetProfile) {
    cout << "Welcome " << targetProfile.username << "!\n";
    loginPrompt();
    int action;
    cin >> action;
    cout << endl;
    while(action != 0) {
        switch(action) {
            case 1:
                logWorkout(targetProfile);
                break;
            case 2: 
                calorieCalc(targetProfile);
                break;
            case 3:
                profileManager.EditProfile(targetProfile.username);
                break;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        cout << endl;

        loginPrompt();
        cin >> action;
        cout << endl;
    }
}

void actionPrompt() {
    cout << "1. Create a new profile\n";
    cout << "2. Login to an existing profile\n";
    cout << "0. Quit program\n";
    cout << "Choose an action from the menu above: ";
}

int main() {
    bool login = false;
    int action;
    actionPrompt();
    cin >> action;
    while (action != 0 ) {
        string targetName;
        char answer;
        UserProfile targetProfile("", 0, '?', 0.0, 0.0);

        switch(action) {
            case 1:
                targetProfile = createProfile();
                afterLogin(targetProfile);
                break;
            case 2:
                cout << "Please enter username: ";
                cin >> targetName;
                targetProfile = profileManager.GetProfileByUsername(targetName);
                while(targetProfile.username == "") {
                    cout << "Please re-enter username: ";
                    cin >> targetName;
                    targetProfile = profileManager.GetProfileByUsername(targetName);
                }
                answer = 'n';
                while(answer != 'y') {
                    cout << endl;
                    cout << "Username: " << targetProfile.username << endl;
                    cout << "Age: " << targetProfile.age << endl;
                    cout << "Gender: " << targetProfile.gender << endl;
                    cout << "Weight: " << targetProfile.weight << endl;
                    cout << "Height: " << targetProfile.height << endl;
                    cout << "Correct profile? ('y' or 'n'): ";
                    cin >> answer;
                    cout << endl;
                    if(answer == 'y') {
                        login = true;
                        afterLogin(targetProfile);
                        break;
                    } 
                    cout << "Please re-enter username: ";
                    cin >> targetName;
                }
                break;
            default:
                cout << "ERROR: Invalid option, please try again.\n";
                break;
        }

        actionPrompt();
        cin >> action;
    }
    cout << "Goodbye :)\n";
    return 0;
}