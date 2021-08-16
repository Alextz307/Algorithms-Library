int det(int xA, int yA, int xB, int yB, int xC, int yC) {
    return xA * yB + xB * yC + yA * xC - yB * xC - yA * xB - xA * yC;
}

int det(int X1, int Y1, int X2, int Y2, int X3, int Y3) {
    return (X2 - X1) * (Y3 - Y1) - (X3 - X1) * (Y2 - Y1);
}
 
int det(pi A, pi B, pi C) {
    return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}