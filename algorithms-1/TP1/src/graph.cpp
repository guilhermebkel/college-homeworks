#include <math.h>
#include <algorithm>
#include <iostream>
#include "graph.h"

double getEuclideanDistance (Vertice a, Vertice b) {
    double x = (a.x - b.x);
    double y = (a.y - b.y);

    return sqrt(x*x + y*y);
}

float getCurveAngle (Vertice a, Vertice b, Vertice c) {
    float ABx = b.x - a.x;
    float ABy = b.y - a.y;
    float BCx = c.x - b.x;
    float BCy = c.y - b.y;

    float dotProduct = ABx * BCx + ABy * BCy;
    float magnitudeAB = sqrt(ABx * ABx + ABy * ABy);
    float magnitudeBC = sqrt(BCx * BCx + BCy * BCy);

    float angleRad = acos(dotProduct / (magnitudeAB * magnitudeBC));
    float angleDeg = angleRad * 180.0 / M_PI;

    return 180 - angleDeg;
}

void lookupInnerFace (std::vector<Vertice> vertices, std::vector<Vertice> *face, int currentVerticeId) {
    Vertice initialVertice = face->at(0);
    Vertice previousVertice = face->at(face->size() - 1);
    Vertice currentVertice = vertices[currentVerticeId];

    int nextVerticeId = -1;

    for (size_t i = 0; i < currentVertice.neighborVerticesIds.size(); i++) {
        int neighborVerticeId = currentVertice.neighborVerticesIds[i];

        bool isDuplicatedCheck = neighborVerticeId == previousVertice.id && currentVertice.neighborVerticesIds.size() > 1;
        bool nextVerticeIdNeedSetup = nextVerticeId == -1;

        if (!isDuplicatedCheck) {
            if (nextVerticeIdNeedSetup) {
                nextVerticeId = neighborVerticeId;
            } else {
                Vertice nextVertice = vertices[nextVerticeId];
                float nextVerticeEuclideanDistance = getEuclideanDistance(initialVertice, nextVertice);
                float nextVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, nextVertice);

                Vertice neighborVertice = vertices[neighborVerticeId];
                float neighborVerticeEuclideanDistance = getEuclideanDistance(initialVertice, neighborVertice);
                float neighborVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, neighborVertice);

                bool isNeighborVerticeCloserToInitialVertice = neighborVerticeEuclideanDistance < nextVerticeEuclideanDistance;
                bool areAllVerticesEquallyCloseToInitialVertice = neighborVerticeEuclideanDistance == nextVerticeEuclideanDistance;
                bool isNeighborVerticeDirectedToInitialVertice = neighborVerticeCurveAngle < nextVerticeCurveAngle;
                bool neighborVerticeMustBeNextVertice = isNeighborVerticeCloserToInitialVertice || (areAllVerticesEquallyCloseToInitialVertice && isNeighborVerticeDirectedToInitialVertice);

                if (neighborVerticeMustBeNextVertice) {
                    nextVerticeId = neighborVerticeId;
                }
            }
        }
    }

    // std::cout << nextVerticeId << initialVertice.label << " - " << previousVertice.label << " " << currentVertice.label << " " << vertices[nextVerticeId].label << std::endl;

    face->push_back(currentVertice);

    bool reachedEndOfFace = nextVerticeId == initialVertice.id;

    if (reachedEndOfFace) {
        face->push_back(vertices[nextVerticeId]);
    } else {
        lookupInnerFace(vertices, face, nextVerticeId);
    }
}
