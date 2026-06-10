#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>

namespace board {

  class Point2D {
    private:
      double _x, _y;
      double _nx, _ny; //[ASC] normal vector
    public:
      Point2D ();
      Point2D (double x, double y);
      Point2D (std::vector<double> coordinates) {_x = coordinates[0]; _y = coordinates[1];}; //[ASC] attention aucune protection...
      void move (double x, double y); 
      void setCoordinates(std::vector<double> coordinates);
      std::vector<double> getCoordinates();
  };

  class Point3D : Point2D {
    private:
      double _z;
      double _nz; //[ASC] normal vector
    public:
      Point3D();
      Point3D(double x, double y, double z);
      Point3D(std::vector<double> coordinates);
      void move (double x, double y, double z);
      void setCoordinates(std::vector<double> coordinates);
      std::vector<double> getCoordinates();
      void elevate (double elevation);
  };

  class SquareBox {
    private:
      std::map<std::pair<unsigned int, unsigned int>, board::Point3D> _points;
    public:
      SquareBox();
      SquareBox(std::map<std::pair<unsigned int, unsigned int>, board::Point3D> data);
      void move(std::pair<unsigned int, unsigned int> position);
      std::map<std::pair<unsigned int, unsigned int>, board::Point3D> getPoints() {return _points;}; 
  };

  class Field {
    private:
      unsigned int _width = 1;
      unsigned int _height = 1;
      std::map<std::pair<unsigned int, unsigned int>, board::Point3D> _points;
    public:
      Field(unsigned int width = 1, unsigned int height = 1);
      //Getters
      unsigned int width() {return _width;};
      unsigned int height() {return _height;};
      std::map<std::pair<unsigned int, unsigned int>, board::Point3D> points() {return _points;};
      SquareBox getSquareBox(std::pair<unsigned int, unsigned int> position);
      Point3D getCenter();
      void processElevation(std::map<std::pair<unsigned int, unsigned int>, double> elevation);
  };
};
#endif
