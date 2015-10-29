#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct Point
{
    float x;
    float y;
    float z;

    Point& operator = (const Point &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    bool operator == (const Point &p)
    {
        return (x == p.x && y == p.y && z == p.z);
    }

    friend std::ostream& operator << (std::ostream &o, const Point &p)
    {
        o << "(" << p.x << "," << p.y << "," << p.z << ")";
        return o;
    }
};

#endif // POINT_H_INCLUDED
