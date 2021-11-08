struct cpoint {
    vector origPos;
    vector flatPos;
    float K;
    int pointNum;
}

float getKValue(vector points[]) {
    vector p = points[0];
    vector nbrPoints[] = points[1:];

    float alphaSum = 0;
    float areaSum = 0;

    for (int i = 0; i < len(nbrPoints); i++) {
        vector p0 = nbrPoints[i];
        vector p1 = nbrPoints[0];
        if (i < len(nbrPoints)-1) {
            p1 = nbrPoints[i+1];
        }

        vector v1 = p0-p;
        vector v2 = p1-p;

        float v1mag = sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
        float v2mag = sqrt(v2.x*v2.x + v2.y*v2.y + v2.z*v2.z);

        vector v1norm = v1/v1mag;
        vector v2norm = v2/v2mag;

        float res = v1norm.x * v2norm.x + v1norm.y * v2norm.y + v1norm.z * v2norm.z;
        float angle = acos(res);
        alphaSum += angle;

        float area = 0.5 * ( sqrt( pow((v1.y*v2.z - v1.z*v2.y), 2) + pow((v1.z*v2.x - v1.x*v2.z), 2) + pow((v1.x*v2.y - v1.y*v2.x), 2)));
        areaSum += area;
    }
    float val = 3*(2*PI - alphaSum)/areaSum;
    return val;
}

void insertionSort(cpoint points[]; int indexToVisit[]; int size) {
  for (int step = 1; step < size; step++) {
    int keyIndex = indexToVisit[step];
    float key = points[keyIndex].K;
    int j = step - 1;

    while (key > points[indexToVisit[j]].K && j >= 0) {
      indexToVisit[j + 1] = indexToVisit[j];
      --j;
    }
    indexToVisit[j + 1] = keyIndex;
  }
}

int[] orderToVisit(cpoint points[]) {
    int indexOrder[];
    resize(indexOrder, len(points));
    for (int i = 0; i < len(points); i++) {
        indexOrder[i] = i;
    }
    
    insertionSort(points, indexOrder, len(points));
    
    return indexOrder;
}