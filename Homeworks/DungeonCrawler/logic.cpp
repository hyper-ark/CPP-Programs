#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    string test;
    ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        return nullptr;
    }

    file >> maxRow;
    if (file.fail()) {
        return nullptr;
    }

    file >> maxCol;
    if (file.fail()) {
        return nullptr;
    } 

    file >> player.row;
    if (file.fail()) {
        return nullptr;
    } 

    file >> player.col;
    if (file.fail()) {
        return nullptr;
    } 
    
    if (maxRow > 999999 || maxCol > 999999 || maxRow < 1 || maxCol < 1) {
        return nullptr;
    }

    if (maxRow > INT32_MAX / maxCol || maxCol > INT32_MAX / maxRow) {
        return nullptr;
    }
        
    if (player.row < 0 || player.col < 0 || player.row >= maxRow || player.col >= maxCol) {
        return nullptr;
    }
    
    char** level = createMap(maxRow, maxCol);
    int doorCount = 0;

    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {

            file >> level[row][col];
            if (file.fail()) {
                return nullptr;
            } 

            switch (level[row][col]) {
                case TILE_EXIT:
                    doorCount++;
                    break;
                case TILE_DOOR:
                    doorCount++;
                    break;
                case TILE_AMULET:
                case TILE_MONSTER:
                case TILE_OPEN:
                case TILE_PILLAR:
                case TILE_TREASURE:
                    break;
                default:
                    deleteMap(level, maxRow);
                    return nullptr;
            }
        }
    }

    if (doorCount == 0) {
        deleteMap(level, maxRow);
        return nullptr;
    }

    file >> test;

    if (!file.fail()) {
        deleteMap(level, maxRow);
        return nullptr;
    }   

    if (level[player.row][player.col] != TILE_OPEN) {
        deleteMap(level, maxRow);
        return nullptr;
    }

    level[player.row][player.col] = TILE_PLAYER;

    file.close();
    return level;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if (input == MOVE_UP) {
        nextRow--;
    }
    else if (input == MOVE_DOWN) {
        nextRow++;
    }
    else if (input == MOVE_RIGHT) {
        nextCol++;
    }
    else if (input == MOVE_LEFT) {
        nextCol--;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; i++) {
        map[i] = new char[maxCol];
    }
    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {
            map[i][j] = TILE_OPEN;
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map == nullptr) {
        maxRow = 0;
    }
    else {
        for (int i = 0; i < maxRow; i++) {
            delete[] map[i];
        }
        delete[] map;
        map = nullptr;
        maxRow = 0;
    }
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if (map == nullptr) {
        return nullptr;
    }
    if (maxRow > 999999 || maxCol > 999999 || maxRow < 1 || maxCol < 1) {
        return nullptr;
    }
    if (maxRow > INT32_MAX / maxCol || maxCol > INT32_MAX / maxRow) {
        return nullptr;
    }
    if (maxRow > INT32_MAX / 2 || maxCol > INT32_MAX / 2) {
        return nullptr;
    }

    int newMaxRow = maxRow * 2;
    int newMaxCol = maxCol * 2;
    char** newArray = new char*[newMaxRow];

    for (int i = 0; i < newMaxRow; ++i) {
        newArray[i] = new char[newMaxCol];
    }
    
    for (int i = 0; i < newMaxRow; ++i) {
        for (int j = 0; j < newMaxCol; ++j) {
            if (map[i % maxRow][j % maxCol] == TILE_PLAYER && (i >= maxRow || j >= maxCol)) {
                newArray[i][j] = TILE_OPEN;
            }
            else {
                newArray[i][j] = map[i % maxRow][j % maxCol];
            }
        }
    }
    
    deleteMap(map, maxRow);
    map = newArray;
    maxRow = newMaxRow;
    maxCol = newMaxCol;
    return map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    if (nextRow >= maxRow || nextRow < 0 || nextCol >= maxCol || nextCol < 0) {
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }

    char tile = map[nextRow][nextCol];

    if (tile == TILE_PILLAR || tile == TILE_MONSTER) {
        return 0;
    }
    if (tile == TILE_OPEN) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 1;
    }
    if (tile == TILE_TREASURE) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        player.treasure++;
        return 2;
    }
    if (tile == TILE_DOOR) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 4;
    }
    if (tile == TILE_AMULET) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 3;
    }
    if (tile == TILE_EXIT && player.treasure == 0) {
        return 0;
    }
    else if (tile == TILE_EXIT && player.treasure >= 1) {
        map[player.row][player.col] = TILE_OPEN;
        map[nextRow][nextCol] = TILE_PLAYER;
        player.row = nextRow;
        player.col = nextCol;
        return 5;
    }
    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    for (int i = player.row-1; i >= 0; i--) {
        if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i+1][player.col] = TILE_MONSTER;
        }
        if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
    }
    for (int i = player.row+1; i < maxRow; i++) {
        if (map[i][player.col] == TILE_MONSTER) {
            map[i][player.col] = TILE_OPEN;
            map[i-1][player.col] = TILE_MONSTER;
        }
        if (map[i][player.col] == TILE_PILLAR) {
            break;
        }
    }
    for (int i = player.col-1; i >= 0; i--) {
        if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i] = TILE_OPEN;
            map[player.row][i+1] = TILE_MONSTER;
        }
        if (map[player.row][i] == TILE_PILLAR) {
            break;
        }
    }
    for (int i = player.col+1; i < maxCol; i++) {
        if (map[player.row][i] == TILE_MONSTER) {
            map[player.row][i] = TILE_OPEN;
            map[player.row][i-1] = TILE_MONSTER;
        }
        if (map[player.row][i] == TILE_PILLAR) {
            break;
        }
    }

    if (map[player.row][player.col] == TILE_MONSTER) {
        return true;
    }
    return false;
}
