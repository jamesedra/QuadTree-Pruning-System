/**
 * @file stats.cpp
 * @description implementation of Stats class used for fast computation of
 *              colour information from rectangular image regions
 *              CPSC 221 2023S PA3
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

#include "stats.h"
#include <algorithm>
#include <cmath>


#define NUMBINS 36 // number of histogram bins

/**
 * Parameterized constructor
 * Initialize the private vectors so that, for each color channel, 
 * (x,y) is the cumulative sum of the the color values from (0,0)
 * to (x,y). 
 * Note that the hue (h) value of each pixel is represented by
 * its cartesian coordinates: X = cos(h) and Y = sin(h). 
 * This is done to simplify distance and average computation.
 */
Stats::Stats(const PNG& im){
    int width = im.width();
    int height = im.height();
    
    sumHueX.resize(width, vector<double>(height));
    sumHueY.resize(width, vector<double>(height));
    sumSat.resize(width, vector<double>(height));
    sumLum.resize(width, vector<double>(height));
    hist.resize(width, vector<vector<unsigned int>>(height, vector<unsigned int>(NUMBINS, 0)));

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            HSLAPixel* pixel = im.getPixel(i, j);
            double hX = cos(pixel->h * M_PI/180.0);
            double hY = sin(pixel->h * M_PI/180.0); 

            if (i == 0 && j == 0) {
                sumHueX[i][j] = hX;
                sumHueY[i][j] = hY;
                sumSat[i][j] = pixel->s;
                sumLum[i][j] = pixel->l;

                hist[i][j][floor(pixel->h/10)]++; 
            } else if (i != 0 && j == 0) {
                sumHueX[i][j] = sumHueX[i-1][j] + hX;
                sumHueY[i][j] = sumHueY[i-1][j] + hY;
                sumSat[i][j] = sumSat[i-1][j] + pixel->s;
                sumLum[i][j] = sumLum[i-1][j] + pixel->l;

                hist[i][j] = hist[i-1][j];
                hist[i][j][floor(pixel->h/10)]++;
            } else if (i == 0 && j != 0) {
                sumHueX[i][j] = sumHueX[i][j-1] + hX;
                sumHueY[i][j] = sumHueY[i][j-1] + hY;
                sumSat[i][j] = sumSat[i][j-1] + pixel->s;
                sumLum[i][j] = sumLum[i][j-1] + pixel->l;

                hist[i][j] = hist[i][j-1];
                hist[i][j][floor(pixel->h/10)]++;
            } else {
                sumHueX[i][j] = sumHueX[i-1][j] + sumHueX[i][j-1] + hX - sumHueX[i-1][j-1];
                sumHueY[i][j] = sumHueY[i-1][j] + sumHueY[i][j-1] + hY - sumHueY[i-1][j-1];
                sumSat[i][j] = sumSat[i-1][j] + sumSat[i][j-1] + pixel->s - sumSat[i-1][j-1];
                sumLum[i][j] = sumLum[i-1][j] + sumLum[i][j-1] + pixel->l - sumLum[i-1][j-1];

                for (int k = 0; k < NUMBINS; k++) {
                    hist[i][j][k] = hist[i-1][j][k] + hist[i][j-1][k] - hist[i-1][j-1][k];
                }

                hist[i][j][floor(pixel->h/10)]++;
            }
        }
    } 
}

/**
 * Given a rectangle, return the number of pixels in the rectangle
 * @param ul is (x,y) of the upper left corner of the rectangle 
 * @param lr is (x,y) of the lower right corner of the rectangle
 */
long Stats::RectArea(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr){
    return (lr.first - ul.first + 1) * (lr.second - ul.second + 1);
}

/**
* Given a rectangle, return the average color value over the rectangle.
* Each color component of the pixel is the average value of that 
* component over the rectangle.
* @param ul is (x,y) of the upper left corner of the rectangle 
* @param lr is (x,y) of the lower right corner of the rectangle
* 
* The average hue is computed from the cumulative X and Y values
* as the arctan(y/x), adjusted to be in the range 0 (inclusive)
* to 360 (non-inclusive).
* You should research the functions for computing arctan in c++.
* Finally, the alpha component of the average should be set to 1.0
*/
HSLAPixel Stats::GetAvg(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr){
    long pixel_count = RectArea(ul,lr);
    int x1 = ul.first;
    int y1 = ul.second;
    int x2 = lr.first;
    int y2 = lr.second;
    
    double hueX_avg = sumHueX[x2][y2];
    double hueY_avg = sumHueY[x2][y2];
    double sat_avg = sumSat[x2][y2];
    double lum_avg = sumLum[x2][y2];

    // if the left-down edge is available
    if (x1-1 >= 0) {
        hueX_avg -= sumHueX[x1-1][y2];
        hueY_avg -= sumHueY[x1-1][y2];
        sat_avg -= sumSat[x1-1][y2];
        lum_avg -= sumLum[x1-1][y2];
    }

    // if the upper-right edge is available
    if (y1-1 >= 0) {
        hueX_avg -= sumHueX[x2][y1-1];
        hueY_avg -= sumHueY[x2][y1-1];
        sat_avg -= sumSat[x2][y1-1];
        lum_avg -= sumLum[x2][y1-1];
    }

    // if the upper-left edge is available
    if (x1-1 >= 0 && y1-1 >= 0) {
        hueX_avg += sumHueX[x1-1][y1-1];
        hueY_avg += sumHueY[x1-1][y1-1];
        sat_avg += sumSat[x1-1][y1-1];
        lum_avg += sumLum[x1-1][y1-1];
    }

    // convert back from radians to degrees
    double hue_avg = atan2(hueY_avg,hueX_avg) * 180 / PI;

    // scale hue_avg
    while (hue_avg < 0) {
        hue_avg += 360;
    }
    while (hue_avg - 360 > 0) {
        hue_avg -= 360;
    }

    sat_avg = sat_avg/pixel_count;
    lum_avg = lum_avg/pixel_count;

    return HSLAPixel(hue_avg, sat_avg,lum_avg);
}

/**
 * Given a rectangle, return the total entropy over that rectangle.
 * @param ul is (x,y) of the upper left corner of the rectangle 
 * @param lr is (x,y) of the lower right corner of the rectangle
 * 
 * Entropy is computed from the hist table, as 
 * follows: E = -Sum(p_i log(p_i)), where p_i is the fraction of
 * pixels in bin i, and the sum is taken over all the bins. 
 * bins holding no pixels should not be included in the sum.
 */
double Stats::Entropy(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr){

    vector<int> distribution(NUMBINS);

    double entropy = 0;
    long area = RectArea(ul,lr);

    /**
    *  Complete your implementation below.
    *  Using private member hist, assemble the distribution over the
    *  given rectangle defined by points ul, and lr into variable distribution.
    *  You will use distribution to compute the entropy over the rectangle.
    *  if any bin in the distribution has frequency 0, then do not add that 
    *  term to the entropy total. see .h file for more details.
    */

    // get the ditribution from the hist
    int ulx = ul.first; int uly = ul.second;
    int lrx = lr.first; int lry = lr.second;

    if (ulx == 0 && uly == 0) { // starts at (0,0)
        for (int k = 0; k < NUMBINS; k++) {
            distribution[k] = hist[lrx][lry][k];
        }
    } else if (ulx != 0 && uly == 0) { // starts at (i,0)
        for (int k = 0; k < NUMBINS; k++) {
            distribution[k] = hist[lrx][lry][k] - hist[ulx-1][lry][k];
        }
    } else if (ulx == 0 && uly != 0) { // starts at (0,i)
        for (int k = 0; k < NUMBINS; k++) {
            distribution[k] = hist[lrx][lry][k] - hist[lrx][uly-1][k];
        }
    } else { // starts at (i,j)
        for (int k = 0; k < NUMBINS; k++) {
            distribution[k] = hist[lrx][lry][k] - hist[ulx-1][lry][k] - hist[lrx][uly-1][k] + hist[ulx-1][uly-1][k];
        }
    }

    /* your code should include the following lines (or something similar):
        if (distribution[i] > 0 ) 
            entropy += ((double) distribution[i]/(double) area) 
                                    * log2((double) distribution[i]/(double) area);
    */
    
    for (int i = 0; i < NUMBINS; i++) {
        if (distribution[i] > 0 ) 
            entropy += ((double) distribution[i]/(double) area) 
                        * log2((double) distribution[i]/(double) area);
    }
    
    return  -1 * entropy;
}

/**
 * Add your private Stats function implementations below
 */
