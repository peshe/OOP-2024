#include <iostream>
#include <cstring>

int binarySearch(const char* relations[][3], int n, const char* name);
bool searchSorted(const char* relations[][3], int n, const char* name, const char* requestedName);

// The first idea for solution, not using binary search
const char* returnMom(const char* relations[][3], int n, const char* name)
{
    for (int i = 0; i < n; i++) {
        if (strcmp(name, relations[i][0]) == 0) {
            return relations[i][1];
        }
    }

    return nullptr;
}

const char* returnDad(const char* relations[][3], int n, const char* name)
{
    for (int i = 0; i < n; i++) {
        if (strcmp(name, relations[i][0]) == 0) {
            return relations[i][2];
        }
    }
    return nullptr;
}


bool search(const char* relations[][3], int n, const char* name, const char* requestedName)
{
    if (!name || !requestedName)
        return false;

    if (strcmp(name, requestedName) == 0)
        return true;

    // The initial idea, not using the binary search :(
    // Most probably this will be for the half of the points during the exam
    // However, it`s much faster to be written
    const char* currentMom = returnMom(relations, n, name);
    const char* currentDad = returnDad(relations, n, name);

    return search(relations, n, currentMom, requestedName)
           || search(relations, n, currentDad, requestedName);
}


int main()
{
    const char* relations[][3] = {
            {"Ason",  "Bmom1", "dad1"},
            {"Bmom1", "mom2", "dad2"},
            {"dad1", "mom3", "dad3"},
            {"dad2", "mom5", "dad5"},
            {"dad5", "mom55", "dad555"},
            {"zele", "mama", "tate"}
    };

    std::cout << searchSorted(relations, 6, "Ason", "dad5") << std::endl;
    std::cout << searchSorted(relations, 6, "Bmom1", "dad555") << std::endl;
    std::cout << searchSorted(relations, 6, "Bmom1", "zele") << std::endl;

    return 0;
}


bool searchSorted(const char* relations[][3], int n, const char* name, const char* requestedName)
{
    if (!name || !requestedName)
        return false;

    if (strcmp(name, requestedName) == 0)
        return true;

    // Since the names are in alphabetical order we can use binary search
    int currentPos = binarySearch(relations, n, name);

    // Sometimes this is the best way to debug :))))
    // std::cout << name << " is as Position " << currentPos << std::endl;

    if (currentPos < 0)
        return false;

    const char* currentMom = relations[currentPos][1];
    const char* currentDad = relations[currentPos][2];

    return searchSorted(relations, n, currentMom, requestedName)
           || searchSorted(relations, n, currentDad, requestedName);
}


// Standard binary search, nothing special here....
int binarySearch(const char* relations[][3], int n, const char* name)
{
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (!strcmp(name, (relations[m][0])))
            return m;

        if (strcmp(name, relations[m][0]) > 0)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}
