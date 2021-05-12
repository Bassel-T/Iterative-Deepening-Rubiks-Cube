#include <vector>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream> // For debugging

using namespace std;

vector<string> solved{
    "wbr", "wr", "wgr", "wb", "wg", "wbo", "wo", "wog", // <<== 7
    "rb", "gr", "bo", "og", // <<== 11
    "boy", "oy", "ogy", "by", "gy", "rby", "ry", "gry" // <<== 19
};

int IndexOf(vector<string> haystack, string needle) {
    string n_copy = needle;
    sort(n_copy.begin(), n_copy.end());
    for (int i = 0, s = haystack.size(); i < s; i++) {
        string h_copy = haystack[i];
        sort(n_copy.begin(), n_copy.end());
        if (strcmp(n_copy.c_str(), h_copy.c_str()) == 0) {
            return i;
        }
    }

    return -1;
}

class Node {
    public:
    // Attributes (see below)
    vector<vector<char>> faces;
    string action;
    Node* parent;
    float score;
    int depth;

    Node(string s, string _action) {
        action = _action;
        parent = nullptr;
        score = 0;
        depth = 0;
        for (int i = 0; i < 6; i++) {
            vector<char> face;
            for (int j = 0; j < 9; j++) {
                face.push_back(s[i * 9 + j]);
            }
            faces.push_back(face);
        }
    }

    Node(Node* n) {
        for (int i = 0; i < 6; i++) {
            vector<char> face;
            for (int j = 0; j < 9; j++) {
                face.push_back(n->faces[i][j]);
            }
            faces.push_back(face);
        }

        parent = n;
        depth = parent->depth + 1;
    }

    vector<vector<char>> RotateFace(vector<vector<char>> face, int i) {
        char temp;

        // Turn current face
        temp = face[i][1];
        face[i][1] = face[i][3];
        face[i][3] = face[i][7];
        face[i][7] = face[i][5];
        face[i][5] = temp;
        temp = face[i][0];
        face[i][0] = face[i][6];
        face[i][6] = face[i][8];
        face[i][8] = face[i][2];
        face[i][2] = temp;

        return face;
    }

    Node* RotateWhite(Node* succ, int times) {
        char temp1, temp2, temp3;

        for (int i = 0; i < times; i++) {
            temp1 = succ->faces[1][0];
            temp2 = succ->faces[1][1];
            temp3 = succ->faces[1][2];

            for (int j = 1; j < 4; j++) {
                for (int k = 0; k < 3; k++) {
                    succ->faces[j][k] = succ->faces[j + 1][k];
                }
            }

            succ->faces[4][0] = temp1;
            succ->faces[4][1] = temp2;
            succ->faces[4][2] = temp3;
        }

        return succ;
    }

    Node* RotateBlue(Node* succ, int times) {
        for (int i = 0; i < times; i++) {
            char temp1 = succ->faces[0][0];
            char temp2 = succ->faces[0][3];
            char temp3 = succ->faces[0][6];

            succ->faces[0][0] = succ->faces[4][8];
            succ->faces[0][3] = succ->faces[4][5];
            succ->faces[0][6] = succ->faces[4][2];

            succ->faces[4][8] = succ->faces[5][0];
            succ->faces[4][5] = succ->faces[5][3];
            succ->faces[4][2] = succ->faces[5][6];

            succ->faces[5][0] = succ->faces[2][0];
            succ->faces[5][3] = succ->faces[2][3];
            succ->faces[5][6] = succ->faces[2][6];

            succ->faces[2][0] = temp1;
            succ->faces[2][3] = temp2;
            succ->faces[2][6] = temp3;
        }

        return succ;
    }

    Node* RotateOrange(Node* succ, int times) {
        for (int i = 0; i < times; i++) {
            char temp1 = succ->faces[0][6];
            char temp2 = succ->faces[0][7];
            char temp3 = succ->faces[0][8];

            succ->faces[0][6] = succ->faces[1][8];
            succ->faces[0][7] = succ->faces[1][5];
            succ->faces[0][8] = succ->faces[1][2];

            succ->faces[1][2] = succ->faces[5][0];
            succ->faces[1][5] = succ->faces[5][1];
            succ->faces[1][8] = succ->faces[5][2];

            succ->faces[5][0] = succ->faces[3][6];
            succ->faces[5][1] = succ->faces[3][3];
            succ->faces[5][2] = succ->faces[3][0];

            succ->faces[3][0] = temp1;
            succ->faces[3][3] = temp2;
            succ->faces[3][6] = temp3;
        }

        return succ;
    }

    Node* RotateGreen(Node* succ, int times) {
        for (int i = 0; i < times; i++) {
            char temp1 = succ->faces[0][2];
            char temp2 = succ->faces[0][5];
            char temp3 = succ->faces[0][8];

            succ->faces[0][2] = succ->faces[2][2];
            succ->faces[0][5] = succ->faces[2][5];
            succ->faces[0][8] = succ->faces[2][8];

            succ->faces[2][2] = succ->faces[5][2];
            succ->faces[2][5] = succ->faces[5][5];
            succ->faces[2][8] = succ->faces[5][8];

            succ->faces[5][2] = succ->faces[4][6];
            succ->faces[5][5] = succ->faces[4][3];
            succ->faces[5][8] = succ->faces[4][0];

            succ->faces[4][6] = temp1;
            succ->faces[4][3] = temp2;
            succ->faces[4][0] = temp3;
        }

        return succ;
    }
    
    Node* RotateRed(Node* succ, int times) {
        for (int i = 0; i < times; i++) {
            char temp1 = succ->faces[0][0];
            char temp2 = succ->faces[0][1];
            char temp3 = succ->faces[0][2];

            succ->faces[0][0] = succ->faces[3][2];
            succ->faces[0][1] = succ->faces[3][5];
            succ->faces[0][2] = succ->faces[3][8];

            succ->faces[3][2] = succ->faces[5][8];
            succ->faces[3][5] = succ->faces[5][7];
            succ->faces[3][8] = succ->faces[5][6];

            succ->faces[5][6] = succ->faces[1][0];
            succ->faces[5][7] = succ->faces[1][3];
            succ->faces[5][8] = succ->faces[1][6];

            succ->faces[1][6] = temp1;
            succ->faces[1][3] = temp2;
            succ->faces[1][0] = temp3;
        }

        return succ;
    }

    Node* RotateYellow(Node* succ, int times) {
        for (int i = 0; i < times; i++) {
            char temp1 = succ->faces[4][6];
            char temp2 = succ->faces[4][7];
            char temp3 = succ->faces[4][8];

            for (int j = 4; j > 0; j--) {
                for (int k = 6; k < 9; k++) {
                    succ->faces[j][k] = succ->faces[j - 1][k];
                } 
            }

            succ->faces[1][6] = temp1;
            succ->faces[1][7] = temp2;
            succ->faces[1][8] = temp3;
        }

        return succ;
    }

    vector<Node*> Successors(Node* goal) {
        vector<Node*> toReturn;

        // Clockwise: 0 --> 2 --> 8 --> 6 --> 0, 1 --> 5 --> 7 --> 3 --> 1
        // Countclockwise: Reverse clockwise

        for (int i = 0; i < 18; i++) {
            // Rotate current face
            Node* succ = new Node(this);

            bool matchLast = false;

            // Is the current move another one of the previous move's face
            switch (i) {
                case 0:
                case 6:
                case 12:
                    if (action[0] == 'W') {
                        matchLast = true;
                    }
                    break;
                case 1:
                case 7:
                case 13:
                    if (action[0] == 'B') {
                        matchLast = true;
                    }
                    break;
                case 2:
                case 8:
                case 14:
                    if (action[0] == 'O') {
                        matchLast = true;
                    }
                    break;
                case 3:
                case 9:
                case 15:
                    if (action[0] == 'G') {
                        matchLast = true;
                    }
                    break;
                case 4:
                case 10:
                case 16:
                    if (action[0] == 'R') {
                        matchLast = true;
                    }
                    break;
                case 5:
                case 11:
                case 17:
                    if (action[0] == 'Y') {
                        matchLast = true;
                    }
                    break;
                default:
                    break;
            }

            if (matchLast) {continue;}

            switch (i) {
                case 0:
                    succ = RotateWhite(succ, 1);
                    succ->action = "W1";
                    break;
                case 1:
                    succ = RotateBlue(succ, 1);
                    succ->action = "B1";
                    break;
                case 2:
                    succ = RotateOrange(succ, 1);
                    succ->action = "O1";
                    break;
                case 3:
                    succ = RotateGreen(succ, 1);
                    succ->action = "G1";
                    break;
                case 4:
                    succ = RotateRed(succ, 1);
                    succ->action = "R1";
                    break;
                case 5:
                    succ = RotateYellow(succ, 1);
                    succ->action = "Y1";
                    break;
                case 6:
                    succ->action = "W2";
                    succ = RotateWhite(succ, 2);
                    break;
                case 7:
                    succ->action = "B2";
                    succ = RotateBlue(succ, 2);
                    break;
                case 8:
                    succ->action = "O2";
                    succ = RotateOrange(succ, 2);
                    break;
                case 9:
                    succ->action = "G2";
                    succ = RotateGreen(succ, 2);
                    break;
                case 10:
                    succ->action = "R2";
                    succ = RotateRed(succ, 2);
                    break;
                case 11:
                    succ->action = "Y2";
                    succ = RotateYellow(succ, 2);
                    break;
                case 12:
                    succ->action = "W3";
                    succ = RotateWhite(succ, 3);
                    break;
                case 13:
                    succ->action = "B3";
                    succ = RotateBlue(succ, 3);
                    break;
                case 14:
                    succ->action = "O3";
                    succ = RotateOrange(succ, 3);
                    break;
                case 15:
                    succ->action = "G3";
                    succ = RotateGreen(succ, 3);
                    break;
                case 16:
                    succ->action = "R3";
                    succ = RotateRed(succ, 3);
                    break;
                case 17:
                    succ->action = "Y3";
                    succ = RotateYellow(succ, 3);
                    break;
            }

             succ->faces = RotateFace(succ->faces, i % 6);

            if (i > 5) {
                succ->faces = RotateFace(succ->faces, i % 6);
                if (i > 11) {
                    succ->faces = RotateFace(succ->faces, i % 6);
                }
            }

            succ->CalculateScore();

            toReturn.push_back(succ);
        }

        return toReturn;
    }

    bool IsVariant(string s1, string s2) {
        string c1 = s1;
        string c2 = s2;
        sort(c1.begin(), c1.end());
        sort(c2.begin(), c2.end());

        return strcmp(c1.c_str(), c2.c_str()) == 0;
    }

    void CalculateScore() {
        score = 0;

        vector<string> tiles;

        // Approximating Moves
        string wbr = "" ; wbr += faces[0][0]; wbr += faces[1][0]; wbr += faces[4][2];
        tiles.push_back(wbr);
        string wr = ""; wr += faces[0][1]; wr += faces[4][2];
        tiles.push_back(wr);
        string wgr = "" ; wgr += faces[0][2]; wgr += faces[3][2]; wgr += faces[4][0];
        tiles.push_back(wgr);
        string wb = ""; wb += faces[0][3]; wb += faces[1][2];
        tiles.push_back(wb);
        string wg = ""; wg += faces[0][5]; wg += faces[3][2];
        tiles.push_back(wg);
        string wbo = "" ; wbo += faces[0][6]; wbo += faces[1][2]; wbo += faces[2][0];
        tiles.push_back(wbo);
        string wo = ""; wo += faces[0][7]; wo += faces[2][2];
        tiles.push_back(wo);
        string wog = "" ; wog += faces[0][8]; wog += faces[2][2]; wog += faces[3][0];
        tiles.push_back(wog);

        // Edges
        string rb = ""; rb += faces[4][5]; rb += faces[1][3];
        tiles.push_back(rb);
        string gr = ""; gr += faces[3][5]; gr += faces[4][3];
        tiles.push_back(gr);
        string bo = ""; bo += faces[1][5]; bo += faces[2][3];
        tiles.push_back(bo);
        string og = ""; og += faces[2][5]; og += faces[3][3];
        tiles.push_back(og);

        // Yellow Corners
        string boy = ""; boy += faces[1][8]; boy += faces[2][6]; boy += faces[5][0];
        tiles.push_back(boy);
        string oy = ""; oy += faces[2][7]; oy += faces[5][1];
        tiles.push_back(oy);
        string ogy = ""; ogy += faces[2][8]; ogy += faces[3][6]; ogy += faces[5][2];
        tiles.push_back(ogy);
        string by = ""; by += faces[1][7]; by += faces[5][3];
        tiles.push_back(by);
        string gy = ""; gy += faces[3][7]; gy += faces[5][5];
        tiles.push_back(gy);
        string rby = ""; rby += faces[4][8]; rby += faces[1][6]; rby += faces[5][6];
        tiles.push_back(rby);
        string ry = ""; ry += faces[4][7]; ry += faces[5][7];
        tiles.push_back(ry); 
        string gry = ""; gry += faces[3][8]; gry += faces[4][6]; gry += faces[5][8];
        tiles.push_back(gry);

        for (int i = 0, s = tiles.size(); i < s; i++) {
            int index = IndexOf(solved, tiles[i]);

            // In the right place
            if (index == i) {continue;}

            int currY = (i <= 7) ? 0 : ((i <= 11) ? 1 : 2);
            int targetY = (index <= 7) ? 0 : ((index <= 11) ? 1 : 2);
            score += abs(currY - targetY);

            int currX;

            switch (i) {
                case 0:
                case 1:
                case 2:
                case 8:
                case 9:
                case 12:
                case 13:
                case 14:
                    currX = 0;
                    break;
                case 3:
                case 4:
                case 15:
                case 16:
                    currX = 1;
                    break;
                default:
                    currX = 2;
                    break;
            }

            int targetX;

            switch (index) {
                case 0:
                case 1:
                case 2:
                case 8:
                case 9:
                case 12:
                case 13:
                case 14:
                    targetX = 0;
                    break;
                case 3:
                case 4:
                case 15:
                case 16:
                    targetX = 1;
                    break;
                default:
                    targetX = 2;
                    break;
            }

            score += abs(currX - targetX);

            int currZ;

            switch (i) {
                case 0:
                case 3:
                case 6:
                case 8:
                case 10:
                case 12:
                case 15:
                case 17:
                    currZ = 0;
                    break;
                case 1:
                case 7:
                case 13:
                case 18:
                    currZ = 1;
                    break;
                default:
                    currZ = 2;
                    break;
            }

            int targetZ;

            switch (index) {
                case 0:
                case 3:
                case 6:
                case 8:
                case 10:
                case 12:
                case 15:
                case 17:
                    targetZ = 0;
                    break;
                case 1:
                case 7:
                case 13:
                case 18:
                    targetZ = 1;
                    break;
                default:
                    targetZ = 2;
                    break;
            }

            score += abs(currZ - targetZ);
        }

        score /= 8.0;
    }

    // O(n^2)
    string Hash() {
        string toReturn = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 9; j++) {
                toReturn += faces[i][j];
            }
        }
        return toReturn;
    }

    // Efficient
    bool Equals(Node* other) {
        return strcmp(Hash().c_str(), other->Hash().c_str()) == 0;
    }
    
};