#pragma once
#include "common.hh"

struct SettingsRoyale {
    u64 shrinkEveryNTurns;
};

struct SettingsSquad {
    bool allowBodyCollisions;
    bool sharedElimination;
    bool sharedHealth;
    bool sharedLength;
};

struct Settings {
    i64 foodSpawnChance;
    i64 minimumFood;
    i64 hazardDamagePerTurn;
    string map;
    SettingsRoyale royale;
    SettingsSquad squad;
};

struct Ruleset {
    string name;
    string version;
    Settings settings;
};

struct Game {
    string id;
    Ruleset ruleset;
    i64 timeout; //in milliseconds
    string source;
};

struct Point {
    i64 x, y;
};

struct Customizations {
    string apiversion;
    string author;
    string color;
    string head;
    string tail;
    string version;
};

struct Snake {
    string id;
    string name;
    i64 health;
    string latency;
    vector<Point> body;
    Point head;
    u64 length;
    string shout;
    string squad;
    Customizations customizations;
};

struct Board {
    i64 width, height;
    vector<Point> food;
    vector<Snake> snakes;
    vector<Point> hazards;
};

struct Turn {
    Game game;
    u64 turn;
    Board board;
    Snake you;
};

enum class Direction : u8 {
    Up,
    Down,
    Left,
    Right,
};

struct Move {
    Direction direction;
    string shout;
};
