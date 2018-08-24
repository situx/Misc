#ifndef NOTENLISTE_HPP_INCLUDED
#define NOTENLISTE_HPP_INCLUDED
#include <string>
#include <map>
#include <list>
#include <utility>
#include <fstream>
class Notenliste{
std::map<std::string,std::list<std::pair<std::string,double> > > Fachmap;
std::string Vorname;
std::string Name;
std::fstream file;
int Matrikelnummer;
public:
Notenliste(std::string Vorname, std::string Name,int Matrikelnummer);
~Notenliste();
void eintragen(std::string Fach,std::string Datum,double Note);
void durchgefallen();
void asHTML(std::string fileName);
};

#endif // NOTENLISTE_HPP_INCLUDED
