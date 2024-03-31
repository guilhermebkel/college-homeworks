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

std::string generateFacePath (Face *face) {
    std::string path;

    for (size_t i = 0; i < face->vertices.size(); i++) {
        Vertice currentVertice = face->vertices[i];
        
        path += std::to_string(currentVertice.id);
    }

    return path;
}

int calculateInnerNextVerticeId (std::vector<Vertice> vertices, Vertice initialVertice, Vertice previousVertice, Vertice currentVertice) {
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
                bool isNeighborVerticeDirectedToInitialVertice = (neighborVerticeEuclideanDistance == nextVerticeEuclideanDistance) && (neighborVerticeCurveAngle < nextVerticeCurveAngle);
                bool neighborHasSingleVerticeInside = neighborVertice.neighborVerticesIds.size() == 1;
                bool neighborVerticeMustBeNextVertice = isNeighborVerticeCloserToInitialVertice || isNeighborVerticeDirectedToInitialVertice || neighborHasSingleVerticeInside;

                if (neighborVerticeMustBeNextVertice) {
                    nextVerticeId = neighborVerticeId;
                }

                if (neighborHasSingleVerticeInside) {
                    break;
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

    face->vertices.push_back(currentVertice);

    int nextVerticeId = calculateInnerNextVerticeId(vertices, initialVertice, previousVertice, currentVertice);
    
    bool isFaceCompleted = nextVerticeId == initialVertice.id;

    if (isFaceCompleted) {
        face->vertices.push_back(vertices[nextVerticeId]);
        face->uniqueId = generateFaceUniqueId(face);
        face->path = generateFacePath(face);
    } else {
        lookupInnerGraphFace(vertices, face, nextVerticeId);
    }
}

bool canComputeGraphFace (std::vector<Vertice> vertices, std::vector<Face> faces, Face face) {
    auto faceIterator = std::find_if(faces.begin(), faces.end(), [&](const Face& existingFace) { return existingFace.uniqueId == face.uniqueId; });
    bool wasFaceAlreadyComputed = faceIterator != faces.end();
    
    std::string invertedFacePath = face.path;
    std::reverse(invertedFacePath.begin(), invertedFacePath.end());
    bool isFacePathRecursive = invertedFacePath == face.path;

    std::vector<int> initialFaceVerticeNeighborVerticesIds = face.vertices[0].neighborVerticesIds;
    auto initialFaceVerticeNeihborVerticesIdsIterator = std::find_if(initialFaceVerticeNeighborVerticesIds.begin(), initialFaceVerticeNeighborVerticesIds.end(), [&](int verticeId) { return vertices[verticeId].degree == 1; });
    bool isInitialFaceVerticeConnectedToSingleDegreeVertice = initialFaceVerticeNeihborVerticesIdsIterator != initialFaceVerticeNeighborVerticesIds.end();

    return !wasFaceAlreadyComputed && !isFacePathRecursive && !isInitialFaceVerticeConnectedToSingleDegreeVertice;
}
