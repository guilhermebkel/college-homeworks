#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <math.h>
#include "graph.hpp"

CurveType getCurveType (Vertice a, Vertice b, Vertice c) {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);

    if (v < 0) {
        return CurveType::left;
    }
    if (v > 0) {
        return CurveType::right;
    }
    
    return CurveType::straight;
}

float getRelativeInclination (Vertice a, Vertice b) {
    return atan2(b.y - a.y, b.x - a.x);
}

float getCurveAngle (Vertice a, Vertice b, Vertice c, bool use) {
    float ABx = b.x - a.x;
    float ABy = b.y - a.y;
    float BCx = c.x - b.x;
    float BCy = c.y - b.y;

    float dotProduct = ABx * BCx + ABy * BCy;
    float magnitudeAB = sqrt(ABx * ABx + ABy * ABy);
    float magnitudeBC = sqrt(BCx * BCx + BCy * BCy);

    float angleRad = acos(dotProduct / (magnitudeAB * magnitudeBC));
    float angleDeg = angleRad * 180.0 / M_PI;

    float ABinclination = getRelativeInclination(a, b);
    float BCinclination = getRelativeInclination(b, c);

    CurveType curveType = getCurveType(a, b, c);

    std::cout << "[" << a.label << b.label << "] " << ABinclination << " .. ";
    std::cout << "[" << b.label << c.label << "] " << BCinclination << " // ";

    if (
        a.x > b.x && c.x > b.x
    ) {
        return 180 - angleDeg;
    } else {
        return 180 - angleDeg;
    }
}

int calculateInnerNextVerticeId (std::map<int, Vertice> vertices, Face *face, Vertice previousVertice, Vertice currentVertice) {
    int lastCurveType = -1;

    bool faceHasMinCurveTypeCalculationSize = face->vertices.size() >= 3;

    if (faceHasMinCurveTypeCalculationSize) {
        lastCurveType = getCurveType(face->vertices.at(0), previousVertice, currentVertice);
    }

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
                float nextVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, nextVertice, false);
                float nextVerticeCurveType = getCurveType(previousVertice, currentVertice, nextVertice);

                Vertice neighborVertice = vertices[neighborVerticeId];
                float neighborVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, neighborVertice, false);
                float neighborVerticeCurveType = getCurveType(previousVertice, currentVertice, neighborVertice);

                bool isNeighborVerticeCorrectlyCurved = neighborVerticeCurveType == lastCurveType && nextVerticeCurveType != lastCurveType;
                bool isNeighborVerticeMoreDirected = ((neighborVerticeCurveType == nextVerticeCurveType) || (!faceHasMinCurveTypeCalculationSize)) && (neighborVerticeCurveAngle < nextVerticeCurveAngle);
                bool neighborVerticeMustBeNextVertice = isNeighborVerticeCorrectlyCurved || isNeighborVerticeMoreDirected;

                std::cout << "[" << previousVertice.label << currentVertice.label << nextVertice.label << "] " << nextVerticeCurveAngle << " - ";
                std::cout << "[" << previousVertice.label << currentVertice.label << neighborVertice.label << "] " << neighborVerticeCurveAngle << " - ";
                std::cout << std::endl;

                if (neighborVerticeMustBeNextVertice) {
                    nextVerticeId = neighborVerticeId;
                }
            }
        }
    }

    return nextVerticeId;
}

int calculateOuterNextVerticeId (std::map<int, Vertice> vertices, Face *face, Vertice previousVertice, Vertice currentVertice) {
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
                float nextVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, nextVertice, true);

                Vertice neighborVertice = vertices[neighborVerticeId];
                float neighborVerticeCurveAngle = getCurveAngle(previousVertice, currentVertice, neighborVertice, true);

                bool isNeighborCloserToGraphBorder = neighborVerticeCurveAngle > nextVerticeCurveAngle;

                std::cout << "[" << previousVertice.label << currentVertice.label << nextVertice.label << "] " << nextVerticeCurveAngle << " - ";
                std::cout << "[" << previousVertice.label << currentVertice.label << neighborVertice.label << "] " << neighborVerticeCurveAngle << " - ";
                std::cout << std::endl;

                if (isNeighborCloserToGraphBorder) {
                    nextVerticeId = neighborVerticeId;
                }
            }
        }
    }

    return nextVerticeId;
}

void lookupInnerGraphFace (std::map<int, Vertice> vertices, Face *face, int currentVerticeId) {
    Vertice initialVertice = face->vertices.at(0);
    Vertice previousVertice = face->vertices.at(face->vertices.size() - 1);
    Vertice currentVertice = vertices[currentVerticeId];

    addVerticeToFace(face, currentVertice);

    int nextVerticeId = -1;

    if (initialVertice.label == 'a') {
        nextVerticeId = calculateInnerNextVerticeId(vertices, face, previousVertice, currentVertice);
    } else {
        nextVerticeId = calculateInnerNextVerticeId(vertices, face, previousVertice, currentVertice);
    }
    
    bool isFaceCompleted = nextVerticeId == initialVertice.id;

    if (isFaceCompleted) {
        addVerticeToFace(face, vertices[nextVerticeId]);
    } else {
        lookupInnerGraphFace(vertices, face, nextVerticeId);
    }
}

void addVerticeToFace (Face *face, Vertice vertice) {
    bool isEmptyFace = face->vertices.size() == 0;

    if (isEmptyFace) {
        face->uniqueId = 0;
        face->path = "";
    } else {
        face->uniqueId += vertice.id;
    }

    face->vertices.push_back(vertice);
    face->path += std::to_string(vertice.id);
}

bool canComputeGraphFace (std::map<int, Vertice> vertices, std::vector<Face> faces, Face face) {
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
