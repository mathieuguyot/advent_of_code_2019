#ifndef DEF_AOC_3_HPP
#define DEF_AOC_3_HPP

#include <vector>
#include <string>
#include <set>

enum direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

struct line_segment {
    direction dir;
    int intensity;

    bool operator==(const line_segment& seg) const 
    {
        return seg.dir == dir && seg.intensity == intensity;
    }
};

struct point {
    int x, y;

    bool operator==(const point& p) const 
    {
        return p.x == x && p.y == y;
    }

    bool operator<(const point& p) const 
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

typedef std::vector<line_segment> line_segments;

typedef std::set<point> points_set;

int find_shortest_manhattan_distance(const points_set& points, const point& central_port);
points_set find_intersection_points(const std::vector<line_segments>& lines, const point& central_port);
std::vector<line_segments> parse_lines_file(const std::string& file_path); 

#endif