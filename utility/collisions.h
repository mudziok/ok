class Collision {
public:
    bool lineLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
        double uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
        double uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

        return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
    }
};