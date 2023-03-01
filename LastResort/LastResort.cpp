#include <iostream>
#include <string>
#include <dirent.h>
#include <vector>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <windows.h>

using namespace std;

void printv(vector<string> const& a) {
    cout << "Vector Elements: " << endl;

    for (int i = 0; i < a.size(); i++) {
        cout << a.at(i) << " /// ";
    }
}

void copyFile(vector<string> const& a, const char* FILE, const char* DEST) {
    /*vector<const char*> nameList;
    for (int j = 0; j < a.size(); j++) {
        nameList.push_back(a[j].c_str());
    }*/
    for (int i = 0; i < a.size();) {
        string output;
        string backsl = "\\";
        output = DEST + backsl + a.at(i);
        ofstream(output, ios::binary) << ifstream(FILE, ios::binary).rdbuf();               // Copying file

        cout << "\nOutput file: " << output;
        cout << "\nRenamed file " << FILE << " to " << a[i].c_str();
        cout << "\nCopied file " << FILE << " into " << DEST << " " << i << " times";
        i++;
    }
}

int main(int argc, char** argv) {
    const char* path = argv[1];                     // Images to be replaced
    const char* gbatedImg = argv[2];                // Image to be duplicated

    DIR* dir;
    struct dirent* ent;
    vector<string> allFiles;
    char filepath[256];
    if ((dir = opendir(path)) != NULL) {
        /* adding all files from directory to vector element */
        int count = 0;
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name != "." || ent->d_name != "..") {
                allFiles.insert(allFiles.begin() + count, ("%s\n", ent->d_name));       // Saving any filename in vector

                sprintf_s(filepath, "%s/%s", path, ent->d_name);
                remove(filepath);                                                       // Deleting all files from directory
            }
            else {
                continue;
            }
            count += 1;
        }
        printv(allFiles);
        copyFile(allFiles, gbatedImg, path);

        closedir(dir);
    }
    else {
        perror("");
        return EXIT_FAILURE;
    }

    return 0;
}