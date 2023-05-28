
#ifndef UTIL_PNG_H
#define UTIL_PNG_H

#include <string>
#include <vector>

#include "RGBAPixel.h"

using namespace std;

namespace util {
    class PNG {
    public:
        PNG();

        PNG(unsigned int width, unsigned int height);

        PNG(PNG const& other);

        ~PNG();

        PNG const& operator=(PNG const& other);

        bool operator==(PNG const& other) const;

        bool operator!=(PNG const& other) const;

        bool readFromFile(string const& fileName);

        bool writeToFile(string const& fileName);

        RGBAPixel* getPixel(unsigned int x, unsigned int y);

        unsigned int width() const;

        unsigned int height() const;

        void resize(unsigned int newWidth, unsigned int newHeight);

        vector<pair<int, int>> drawLine(pair<int, int> p1, pair<int, int> p2, const RGBAPixel& colour);

        void drawHexagon(vector<pair<int, int>> points, const RGBAPixel& edgeColour, const RGBAPixel& fillColour);

        void floodFill(pair<int, int> start, const RGBAPixel& fillColour, const vector<pair<int, int>>& edge_coords);

    private:
        unsigned int width_;   /*< Width of the image */
        unsigned int height_;  /*< Height of the image */
        RGBAPixel* imageData_; /*< Array of pixels */


        void _copy(PNG const& other);
    };
}

#endif
