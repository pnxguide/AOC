#include <iostream>
#include <fstream>
using namespace std;

void solve1() {
    int direction = 90;
    int xPos = 0, yPos = 0;

    ifstream infile("input.txt");
    string line;
    while(infile >> line) {
        char cmd = line[0];
        line.erase(0, 1);
        int val = stoi(line);
        
        switch(cmd) {
            case 'N':
                yPos -= val;
                break;
            case 'S':
                yPos += val;
                break;
            case 'E':
                xPos += val;
                break;
            case 'W':
                xPos -= val;
                break;
            case 'L':
                direction -= val;
                direction = (360 + direction) % 360;
                break;
            case 'R':
                direction += val;
                direction = (360 + direction) % 360;
                break;
            case 'F':
                switch(direction) {
                    case 0:
                        yPos -= val;
                        break;
                    case 180:
                        yPos += val;
                        break;
                    case 90:
                        xPos += val;
                        break;
                    case 270:
                        xPos -= val;
                        break;
                }
                break;
        }
    }
    cout << abs(xPos) + abs(yPos) << endl;
}

void solve2() {
    int xWaypointPos = 10, yWaypointPos = -1;
    int xPos = 0, yPos = 0;

    ifstream infile("input.txt");
    string line;
    while(infile >> line) {
        char cmd = line[0];
        line.erase(0, 1);
        int val = stoi(line);
        
        switch(cmd) {
            case 'N':
                yWaypointPos -= val;
                break;
            case 'S':
                yWaypointPos += val;
                break;
            case 'E':
                xWaypointPos += val;
                break;
            case 'W':
                xWaypointPos -= val;
                break;
            case 'L':
                for(int i = 0; i < val/90; i++) {
                    int tmp = yWaypointPos;
                    yWaypointPos = -xWaypointPos;
                    xWaypointPos = tmp;
                }
                break;
            case 'R':
                for(int i = 0; i < val/90; i++) {
                    int tmp = yWaypointPos;
                    yWaypointPos = xWaypointPos;
                    xWaypointPos = -tmp;
                }
                break;
            case 'F':
                xPos += xWaypointPos * val;
                yPos += yWaypointPos * val;
                break;
        }
        cout << xPos << " " << yPos << endl;
    }
    cout << abs(xPos) + abs(yPos) << endl;
}

int main() {
    solve1();
    solve2();
    return 0;
}
