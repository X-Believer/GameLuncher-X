#include "Creature.h"

//ÓëÉúÎïÅö×²
bool Creature::CreatureCollide(double x, double y, Creature& creature)
{
	return true;
}

//¼ì²âÉÏ·½Åö×²
pair<double, bool> Creature::UpCollide(double lastx, double lasty)
{
	return make_pair(0,true);
}

//¼ì²âÏÂ·½Åö×²
pair<double, bool> Creature::DownCollide(double lastx, double lasty)
{
	return make_pair(0, true);
}

//¼ì²â×óÓÒÅö×²
pair<double, bool> Creature::SideCollide(double lastx, double lasty)
{
	return make_pair(0, true);
}

//ÉèÖÃÎ»ÖÃ
void Creature::SetPos(double x, double y, double width, double height)
{

}

//¼ì²âÅö×²
void Creature::CheckCollide(double lastx, double lasty)
{

}