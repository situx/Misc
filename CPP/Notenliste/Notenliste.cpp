#include "Notenliste.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
Notenliste::Notenliste(std::string v,std::string n,int m):Vorname(v),Name(n),Matrikelnummer(m){
}
Notenliste::~Notenliste(){
}
void Notenliste::eintragen(std::string Fach, std::string Datum, double Note){
    std::pair<std::string,double> eintrag(Datum,Note);
    if (Fachmap[Fach].empty() || (Fachmap[Fach].size()!=3 && Fachmap[Fach].back().second==5) || Fachmap[Fach].back().second==6)
        Fachmap[Fach].push_back(eintrag);
    else if(Fachmap[Fach].back().second<5)
            std::cout<<"Veranstaltung "<<Fach<<" wurde bereits mit der Note "<<Fachmap[Fach].back().second<<" bestanden!"<<std::endl;
    else if(Fachmap[Fach].size()==3 && Fachmap[Fach].back().second==5)
        std::cout<<"Veranstaltung "<<Fach<<" wurde bereits endgültig nicht bestanden!"<<std::endl;
}

void checkdurch(std::map<std::string,std::list<std::pair<std::string,double> > >::value_type el) {
   if (el.second.back().second==5 && el.second.size()==3)
        std::cout<<"Student ist im Fach "<<el.first<<" durchgefallen!"<<std::endl;
}

void Notenliste::durchgefallen(){
    for_each(Fachmap.begin(),Fachmap.end(),checkdurch);
}

void Notenliste::asHTML(std::string fileName){
    char s[7];
    int sz=0,i=0;
    std::map<std::string,std::list<std::pair<std::string,double> > >::iterator it;
    std::string zeile;
    std::string end("</table></body></html>");
    std::fstream file(fileName.c_str(),std::ios::out);
    std::list<std::pair<std::string,double> >::iterator it2;
    std::string begin("<html><head><title>Notenliste</title></head><body bgcolor=#123456><h1 align=center>Gradelist of ");
    sprintf(s,"%i",Matrikelnummer);
    begin.append(Vorname);
    begin.append(" ");
    begin.append(Name);
    begin.append("<br>Student number: ");
    begin.append(s);
    begin.append("</h1><table border=1 marginheight=0 marginwidth=0 align=center><tr><th bgcolor=blue>Major</th>");
    for(it=Fachmap.begin();it!=Fachmap.end();it++){
        if(it->second.size()>sz){
            while(sz<it->second.size()){
                begin.append("<th bgcolor=blue>Grade ");
                sprintf(s,"%i",++sz);
                begin.append(s);
                begin.append(". Attempt</th><th bgcolor=blue>Date</th>");
            }
        }
    }
    begin.append("</tr>");
    file.write(begin.c_str(),begin.size());
    for(it=Fachmap.begin();it!=Fachmap.end();it++){
        zeile.append("<tr><td>");
        zeile.append(it->first);
        for (it2=it->second.begin();it2!=it->second.end();it2++){
            zeile.append("</td><td>");
            if(it2->second<6){
                sprintf(s,"%.1f",it2->second);
                zeile.append("<b>");
                zeile.append(s);
                zeile.append("</b>");
            }
            else
                zeile.append("<b>Doctors Note</b>");
            zeile.append("</td><td>");
            zeile.append(it2->first);
        }
        i=it->second.size();
        while(i<sz){
            zeile.append("</td><td>");
            i++;
        }
        zeile.append("</td></tr>");
    }
    file.write(zeile.c_str(),zeile.size());
    file.write(end.c_str(),end.size());
    file.close();
    std::cout<<"Output generated"<<std::endl;
}
int main(){
    Notenliste *nl= new Notenliste("user_first","user_second",123456);
    nl->eintragen("Analysis","1.1.1111",2);
    nl->eintragen("Rhetorics","2.2.2222",3);
    nl->eintragen("Law","8.8.8888",5);
    nl->eintragen("Law","9.9.9999",6);
    nl->eintragen("Law","7.7.7777",6);
    nl->eintragen("Law","3.3.3333",3.7);
    nl->eintragen("Law","4.4.4444",2);
    nl->eintragen("Physics","5.5.5555",5);
    nl->eintragen("Physics","5.5.5555",5);
    nl->eintragen("Physics","5.5.5555",5);
    nl->eintragen("Physics","5.5.5555",5);
    nl->durchgefallen();
    nl->asHTML("output.html");
    delete(nl);
return 0;
}
