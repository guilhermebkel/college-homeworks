#include <iostream>
#include <algorithm>
#include <math.h>
#include "graph.h"

double getRelativeInclination (Vertice p, Vertice q) {
    return atan2(q.y - p.y, q.x - p.x);
}

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

int generateFaceUniqueId (Face *face) {
    float uniqueId = 0;

    uniqueId += face->vertices.size();

    for (size_t i = 0; i < face->vertices.size() - 1; i++) {
        Vertice currentVertice = face->vertices[i];
        Vertice nextVertice = face->vertices[i + 1];

        uniqueId += getEuclideanDistance(currentVertice, nextVertice);
        uniqueId += getRelativeInclination(currentVertice, nextVertice);
    }

    return static_cast<int>(uniqueId);
}

int getNextVerticeId (std::vector<Vertice> vertices, Vertice initialVertice, Vertice previousVertice, Vertice currentVertice) {
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

    return nextVerticeId;
}

void lookupInnerGraphFace (std::vector<Vertice> vertices, Face *face, int currentVerticeId) {
    Vertice initialVertice = face->vertices.at(0);
    Vertice previousVertice = face->vertices.at(face->vertices.size() - 1);
    Vertice currentVertice = vertices[currentVerticeId];

    int nextVerticeId = getNextVerticeId(vertices, initialVertice, previousVertice, currentVertice);

    face->vertices.push_back(currentVertice);

    bool isFaceCompleted = nextVerticeId == initialVertice.id;

    if (isFaceCompleted) {
        face->vertices.push_back(vertices[nextVerticeId]);
        face->uniqueId = generateFaceUniqueId(face);
    } else {
        lookupInnerGraphFace(vertices, face, nextVerticeId);
    }
}

bool canComputeGraphFace (std::vector<Face> faces, Face face) {
    auto faceIterator = std::find_if(faces.begin(), faces.end(), [&](const Face& existingFace) { return existingFace.uniqueId == face.uniqueId; });
    bool faceAlreadyExists = faceIterator != faces.end();
    bool canComputeGraphFace = !faceAlreadyExists;

    return canComputeGraphFace;
}
