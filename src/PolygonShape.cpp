#include <vector>
class Point {
public:
    Point() {};
    Point(int x, int y) { this->x = x; this->y = y; };
    int x, y;
};

class PolygonShape {
public:
    PolygonShape(std::vector<Point> vertices);
    ~PolygonShape();
    Point GetCenter(void);
    Point* GetVertices(void);
    int GetNumberOfVertices(void);
private:
    Point* vertices;
    Point center;
    int length;
};
PolygonShape::PolygonShape(std::vector<Point> vertices) {
    int minX = 0xFFFF, minY = 0xFFFF, maxX = 0, maxY = 0;
    this->length = vertices.size();
    this->vertices = new Point[length];
    for (int i = 0; i < this->length; i++) {
        this->vertices[i] = Point(vertices[i].x, vertices[i].y);
        if (this->vertices[i].x > maxX) maxX = this->vertices[i].x;
        if (this->vertices[i].x < minX) minX = this->vertices[i].x;
        if (this->vertices[i].y > maxY) maxY = this->vertices[i].y;
        if (this->vertices[i].y < minY) minY = this->vertices[i].y;
    }
    this->center.x = minX + ((maxX - minX) / 2);
    this->center.y = minY + ((maxY - minY) / 2);
}

PolygonShape::~PolygonShape() {
    delete[] this->vertices;
}

Point PolygonShape::GetCenter(void) {
    return center;
}

Point* PolygonShape::GetVertices(void) {
    return this->vertices;
}

int PolygonShape::GetNumberOfVertices(void) {
    return this->length;
}