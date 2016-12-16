# include "position.hpp"
# include <sstream>
# include <string>

using namespace std;

Position::Position(int x,int y){
	if((x>=0 && x<=7) && (y>=0 && y<=7)){ //validacion out of bounds
		this->x = x;
		this->y = y;
	}
}
string Position::toString()const{
	stringstream str;
	str << "("<<x<<","<<y<<")";
}
const Position& Position::operator=(const Position&pos){ //sobrecarga de operador de asignacion
	this->x = pos.getX();
	this->y = pos.getY();
}
const int Position::getX()const{
	return x;
}
const int Position::getY()const{
	return y;
}
int	Position::setX(int x){
	if((x>=0&&x<=7)){ //validacion out of bounds
		this->x = x;
	}
}
int Position::setY(int y){
	if((y>=0&&y<=7)){ //validacion out of bounds
		this->y = y;
	}
}