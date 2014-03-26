/****************************************************************************/
/* Includes                                                                 */
/****************************************************************************/
#include "Position.hh"

/****************************************************************************/
/* Implementation                                                           */
/****************************************************************************/

Position::Position() : x(0L), y(0L) {}

Position::Position(double aX, double aY) : x(aX), y(aY) {}

void Position::setX(double aX) {
    this->x = aX;
}

void Position::setY(double aY) {
    this->y = aY;
}

double Position::getX() {
    return this->x;
}

double Position::getY() {
    return this->y;
}

bool Position::operator==(const Position &other) {
	return (this->x == other.x) && (this->y == other.y);
}

bool Position::operator!=(const Position &other) {
	return !(*this == other);
}

std::ostream& operator<< (std::ostream& stream, const Position& p) {
	stream << "Position("<<p.x<<", "<<p.y<<")";
	return stream;
}

Position Position::operator=(const Position &other){

   x = other.x;
   y = other.y;
   return *this;
}
